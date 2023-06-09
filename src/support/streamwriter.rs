use {
  crate::{c_char, size_t, std::string},
  core::{ffi::c_void, fmt, ptr}
};

pub struct StringWriter {
  buf: *mut c_char,
  len: size_t
}

impl StringWriter {
  pub fn new(
    buf: *mut c_char,
    len: size_t
  ) -> Self {
    Self { buf, len }
  }

  pub fn write_char(
    &mut self,
    new_char: c_char
  ) {
    if 1 > self.len {
      return;
    }

    unsafe { *self.buf.wrapping_offset(0) = new_char };
    self.buf = self.buf.wrapping_offset(1);
    self.len -= 1;
  }

  pub fn write_chars(
    &mut self,
    new_char: c_char,
    mut len: size_t
  ) {
    if len > self.len {
      len = self.len;
    }

    if len > 0 {
      string::ouma_memset(self.buf as *mut c_void, new_char as i32, len);
      self.len -= len;
      self.buf = self.buf.wrapping_offset(len as isize);
    }
  }

  pub fn write_strs(
    &mut self,
    s: &str
  ) {
    let mut len = s.len();
    if len > self.len {
      len = self.len;
    }

    if len > 0 {
      string::ouma_memcpy(
        self.buf as *mut c_void,
        s.as_ptr() as *const c_void,
        len
      );
      self.len -= len;
      self.buf = self.buf.wrapping_add(len);
    }
  }

  pub fn write_arr(
    &mut self,
    buf: &[u8]
  ) -> usize {
    if self.len > 1 {
      let sz = buf.len().min(self.len - 1);

      unsafe {
        ptr::copy_nonoverlapping(buf.as_ptr(), self.buf as *mut u8, sz);
      };
      self.len -= sz;
      self.buf = self.buf.wrapping_add(sz);
      unsafe { *self.buf = 0 };
    }

    buf.len()
  }
}

impl fmt::Write for StringWriter {
  fn write_str(
    &mut self,
    s: &str
  ) -> fmt::Result {
    self.write_arr(s.as_bytes());
    Ok(())
  }
}
