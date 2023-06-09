use {
  crate::{
    c_char,
    c_int,
    c_uchar,
    locale_t,
    size_t,
    std::{errno, signal},
    support::streamwriter
  },
  cbitset::BitSet256,
  core::{arch::asm, ffi::c_void, fmt::Write, ptr}
};

#[inline(always)]
fn string_length(string: *const c_char) -> size_t {
  let mut len: size_t = 0;
  let mut s = string;
  unsafe {
    while *s != 0 {
      s = s.wrapping_offset(1);
      len += 1;
    }
  }
  len
}

#[no_mangle]
pub extern "C" fn ouma_memccpy(
  dest: *mut c_void,
  src: *const c_void,
  c: c_int,
  n: size_t
) -> *mut c_void {
  let mut dest1: *mut c_uchar = dest as *mut c_uchar;
  let mut src1: *const c_uchar = src as *const c_uchar;
  let mut i = n;
  while i != 0 {
    let s = src1;
    src1 = src1.wrapping_offset(1);
    let d = dest1;
    dest1 = dest1.wrapping_offset(1);
    unsafe {
      *d = *s;
      if *d == c as c_uchar {
        return dest1 as *mut c_void;
      }
    }
    i -= 1;
  }
  ptr::null_mut()
}

#[no_mangle]
pub extern "C" fn ouma_memchr(
  s: *const c_void,
  c: c_int,
  n: size_t
) -> *mut c_void {
  let mut s1: *const c_uchar = s as *const c_uchar;
  let mut i = n;
  while i != 0 {
    unsafe {
      if *s1 == c as c_uchar {
        return s1 as *mut c_void;
      }
    }
    s1 = s1.wrapping_offset(1);
    i -= 1;
  }
  ptr::null_mut()
}

#[no_mangle]
pub extern "C" fn ouma_memcmp(
  left: *const c_void,
  right: *const c_void,
  n: size_t
) -> c_int {
  let l = left as *const c_uchar;
  let r = right as *const c_uchar;
  let mut i = 0;
  while i < n {
    let a = unsafe { *l.wrapping_offset(i as isize) };
    let b = unsafe { *r.wrapping_offset(i as isize) };
    if a != b {
      return a as c_int - b as c_int;
    }
    i += 1;
  }
  0
}

#[no_mangle]
pub extern "C" fn ouma_memcpy(
  dest: *mut c_void,
  src: *const c_void,
  n: size_t
) -> *mut c_void {
  let mut dest1: *mut c_uchar = dest as *mut c_uchar;
  let mut src1: *const c_uchar = src as *const c_uchar;
  let mut i = 0;
  while i < n {
    let s = src1;
    src1 = src1.wrapping_offset(1);
    let d = dest1;
    dest1 = dest1.wrapping_offset(1);
    unsafe { *d = *s };
    i += 1;
  }
  dest
}

#[no_mangle]
pub extern "C" fn ouma_memmove(
  dest: *mut c_void,
  src: *const c_void,
  n: size_t
) -> *mut c_void {
  let mut dest1: *mut c_uchar = dest as *mut c_uchar;
  let mut src1: *const c_uchar = src as *const c_uchar;
  if (dest1 as *const c_uchar) < src1 {
    let mut i = 0;
    while i < n {
      let s = src1;
      src1 = src1.wrapping_offset(1);
      let d = dest1;
      dest1 = dest1.wrapping_offset(1);
      unsafe { *d = *s };
      i += 1;
    }
  } else if (dest1 as *const c_uchar) > src1 {
    let mut i = n;
    src1 = src1.wrapping_offset(i as isize);
    dest1 = dest1.wrapping_offset(i as isize);

    while i != 0 {
      i -= 1;
      src1 = src1.wrapping_offset(-1);
      dest1 = dest1.wrapping_offset(-1);
      unsafe { *dest1 = *src1 };
    }
  }
  dest
}

#[no_mangle]
pub extern "C" fn ouma_memset(
  s: *mut c_void,
  c: c_int,
  n: size_t
) -> *mut c_void {
  let mut s1: *mut c_char = s as *mut c_char;
  let mut i = 0;
  while i < n {
    let s2 = s1;
    s1 = s1.wrapping_offset(1);
    unsafe {
      *s2 = c as c_char;
    }
    i += 1;
  }
  s
}

#[no_mangle]
pub extern "C" fn ouma_memset_explicit(
  s: *mut c_void,
  c: c_int,
  n: size_t
) -> *mut c_void {
  let s = ouma_memset(s, c, n);
  unsafe { asm!("/* {0} */", inout(reg) s => _) };
  s
}

#[no_mangle]
pub extern "C" fn ouma_strchr(
  s: *const c_char,
  c: c_int
) -> *mut c_char {
  let mut s1 = s;
  loop {
    unsafe {
      if *s1 == c as c_char {
        return s1 as *mut c_char;
      }
      if *s1 == 0 {
        return ptr::null_mut();
      }
    }
    s1 = s1.wrapping_offset(1);
  }
}

#[no_mangle]
pub extern "C" fn ouma_strrchr(
  s: *const c_char,
  c: c_int
) -> *mut c_char {
  let mut s1 = s;
  let mut last = ptr::null_mut();
  loop {
    unsafe {
      if *s1 == c as c_char {
        last = s1 as *mut c_char;
      }
      if *s1 == 0 {
        return last;
      }
    }
    s1 = s1.wrapping_offset(1);
  }
}

#[no_mangle]
pub extern "C" fn ouma_stpcpy(
  dest: *mut c_char,
  src: *const c_char
) -> *mut c_char {
  let len = string_length(src) + 1;
  ouma_stpncpy(dest, src, len)
}

#[no_mangle]
pub extern "C" fn ouma_stpncpy(
  dest: *mut c_char,
  src: *const c_char,
  n: size_t
) -> *mut c_char {
  let mut i = n;
  let mut d = dest;
  let mut s = src;
  unsafe {
    while i > 0 && *s != 0 {
      let d1 = d;
      d = d.wrapping_offset(1);
      let s1 = s;
      s = s.wrapping_offset(1);
      *d1 = *s1;
      i = i.wrapping_sub(1);
    }
  }
  let end = d;
  while i > 0 {
    let d1 = d;
    d = d.wrapping_offset(1);
    unsafe {
      *d1 = 0;
    }
    i -= 1;
  }
  end
}

#[no_mangle]
pub extern "C" fn ouma_strcat(
  dest: *mut c_char,
  src: *const c_char
) -> *mut c_char {
  let len = string_length(src) + 1;
  ouma_strncat(dest, src, len)
}

#[no_mangle]
pub extern "C" fn ouma_strncat(
  dest: *mut c_char,
  src: *const c_char,
  n: size_t
) -> *mut c_char {
  let mut i = n;

  if n != 0 {
    let mut d = dest;
    let mut s = src;
    unsafe {
      while *d != 0 {
        d = d.wrapping_offset(1);
      }
    }
    while i != 0 {
      let s1 = s;
      s = s.wrapping_offset(1);
      unsafe {
        *d = *s1;
        if *d == 0 {
          break;
        }
      }
      d = d.wrapping_offset(1);
      i -= 1;
    }
    unsafe { *d = 0 };
  }
  dest
}

#[no_mangle]
pub extern "C" fn ouma_strcmp(
  left: *const c_char,
  right: *const c_char
) -> c_int {
  let len = string_length(right) + 1;
  ouma_strncmp(left, right, len)
}

#[no_mangle]
pub extern "C" fn ouma_strncmp(
  left: *const c_char,
  right: *const c_char,
  n: size_t
) -> c_int {
  let mut l = left;
  let mut r = right;
  let mut i = n;
  while i != 0 {
    let l2 = l;
    l = l.wrapping_offset(1);
    let c1 = unsafe { *l2 as c_uchar };
    let r2 = r;
    r = r.wrapping_offset(1);
    let c2 = unsafe { *r2 as c_uchar };
    if c1 != c2 {
      return c1 as c_int - c2 as c_int;
    }
    if c1 == 0 {
      break;
    }
    i -= 1;
  }
  0
}

#[no_mangle]
pub extern "C" fn ouma_strcpy(
  dest: *mut c_char,
  src: *const c_char
) -> *mut c_char {
  let len = string_length(src) + 1;
  ouma_strncpy(dest, src, len)
}

#[no_mangle]
pub extern "C" fn ouma_strncpy(
  dest: *mut c_char,
  src: *const c_char,
  n: size_t
) -> *mut c_char {
  let mut i = n;
  let mut d = dest;
  let mut s = src;
  unsafe {
    while i > 0 && *s != 0 {
      let d1 = d;
      d = d.wrapping_offset(1);
      let s1 = s;
      s = s.wrapping_offset(1);
      *d1 = *s1;
      i = i.wrapping_sub(1);
    }
  }
  while i != 0 {
    let d1 = d;
    d = d.wrapping_offset(1);
    unsafe {
      *d1 = 0;
    }
    i -= 1;
  }
  dest
}

#[no_mangle]
pub extern "C" fn ouma_strlen(s: *const c_char) -> size_t {
  string_length(s)
}

#[no_mangle]
pub extern "C" fn ouma_strnlen(
  s: *const c_char,
  n: size_t
) -> size_t {
  let mut i = 0;
  while i < n {
    unsafe {
      if *s.wrapping_add(i) == 0 {
        break;
      }
    }
    i += 1;
  }
  i as size_t
}

#[no_mangle]
pub extern "C" fn ouma_strcspn(
  src: *const c_char,
  segment: *const c_char
) -> size_t {
  let mut s1 = src;
  let mut s2 = segment;
  let mut bitset = BitSet256::new();
  let mut i = 0;
  unsafe {
    while *s2 != 0 {
      bitset.insert(*s2 as usize);
      s2 = s2.wrapping_offset(1);
    }
    while *s1 != 0 && !bitset.contains(*s1 as usize) {
      i += 1;
      s1 = s1.wrapping_offset(1);
    }
  }
  i
}

#[no_mangle]
pub extern "C" fn ouma_strspn(
  src: *const c_char,
  segment: *const c_char
) -> size_t {
  let mut s1 = src;
  let mut s2 = segment;
  let mut bitset = BitSet256::new();
  let mut i = 0;
  unsafe {
    while *s2 != 0 {
      bitset.insert(*s2 as usize);
      s2 = s2.wrapping_offset(1);
    }
    while *s1 != 0 && bitset.contains(*s1 as usize) {
      i += 1;
      s1 = s1.wrapping_offset(1);
    }
  }
  i
}

#[no_mangle]
pub extern "C" fn ouma_strpbrk(
  src: *const c_char,
  breakset: *const c_char
) -> *mut c_char {
  let mut s1 = src;
  let mut s2 = breakset;
  let mut bitset = BitSet256::new();
  unsafe {
    while *s2 != 0 {
      bitset.insert(*s2 as usize);
      s2 = s2.wrapping_offset(1);
    }
    while *s1 != 0 && !bitset.contains(*s1 as usize) {
      s1 = s1.wrapping_offset(1);
    }
    if *s1 != 0 { s1 as *mut c_char } else { ptr::null_mut() }
  }
}

#[no_mangle]
pub extern "C" fn ouma_strstr(
  haystack: *const c_char,
  needle: *const c_char
) -> *mut c_char {
  let mut h = haystack;
  let len = string_length(needle);
  if len == 0 {
    return h as *mut c_char;
  }
  unsafe {
    while *h.wrapping_offset(0 as isize) != 0 {
      let mut i = 0;
      loop {
        if *needle.wrapping_offset(i as isize) == 0 {
          return h as *mut c_char;
        }
        if *h.wrapping_offset(i as isize) & !0 !=
          *needle.wrapping_offset(i as isize) & !0
        {
          break;
        }
        i += 1;
      }
      h = h.wrapping_offset(1);
    }
  }
  ptr::null_mut()
}

#[no_mangle]
pub extern "C" fn ouma_strtok(
  s: *mut c_char,
  sep: *const c_char
) -> *mut c_char {
  static mut LAST: *mut c_char = ptr::null_mut();
  return unsafe { ouma_strtok_r(s, sep, &mut LAST) };
}

#[no_mangle]
pub extern "C" fn ouma_strtok_r(
  s: *mut c_char,
  sep: *const c_char,
  lasts: *mut *mut c_char
) -> *mut c_char {
  let mut s1 = s;
  let mut sep1 = sep;
  let mut bitset = BitSet256::new();
  if s1.is_null() {
    s1 = unsafe { *lasts };
    if s1.is_null() {
      return ptr::null_mut();
    }
  }
  unsafe {
    while *sep1 != 0 {
      bitset.insert(*sep1 as usize);
      sep1 = sep1.wrapping_offset(1);
    }
    while *s1 != 0 && bitset.contains(*s1 as usize) {
      s1 = s1.wrapping_offset(1);
    }
    if *s1 == 0 {
      *lasts = s1;
      return ptr::null_mut();
    }
  }
  let token = s1;
  unsafe {
    while *s1 != 0 {
      if bitset.contains(*s1 as usize) {
        *s1 = 0;
        s1 = s1.wrapping_offset(1);
        break;
      }
      s1 = s1.wrapping_offset(1);
    }
    *lasts = s1;
  }
  token
}

#[no_mangle]
pub extern "C" fn ouma_strcoll(
  s1: *const c_char,
  s2: *const c_char
) -> c_int {
  ouma_strcmp(s1, s2)
}

#[no_mangle]
pub extern "C" fn ouma_strcoll_l(
  s1: *const c_char,
  s2: *const c_char,
  _: locale_t
) -> c_int {
  ouma_strcmp(s1, s2)
}

#[no_mangle]
pub extern "C" fn ouma_strxfrm(
  s1: *mut c_char,
  s2: *const c_char,
  n: size_t
) -> size_t {
  let len = string_length(s2);
  if len < n {
    ouma_strncpy(s1, s2, n);
  }
  len
}

#[no_mangle]
pub extern "C" fn ouma_strxfrm_l(
  s1: *mut c_char,
  s2: *const c_char,
  n: size_t,
  _: locale_t
) -> size_t {
  let len = string_length(s2);
  if len < n {
    ouma_strncpy(s1, s2, n);
  }
  len
}

#[no_mangle]
pub extern "C" fn ouma_strerror_r(
  num: c_int,
  buf: *mut c_char,
  buflen: size_t
) -> c_int {
  let mut w = streamwriter::StringWriter::new(buf, buflen);

  if num >= 0 && num < errno::SYS_ERR_LIST.len() as c_int {
    let _ = w.write_str(errno::SYS_ERR_LIST[num as usize]);
  } else {
    let _ = w.write_fmt(format_args!("Unknown error {}", num));
  }

  0
}

#[no_mangle]
pub extern "C" fn __ouma_gnu_strerror_r(
  num: c_int,
  buf: *mut c_char,
  buflen: size_t
) -> *mut c_char {
  ouma_strerror_r(num, buf, buflen);
  buf
}

#[thread_local]
static mut err_buf: [u8; 255] = [0; 255];

#[no_mangle]
pub extern "C" fn ouma_strerror(num: c_int) -> *mut c_char {
  unsafe {
    if ouma_strerror_r(num, err_buf.as_ptr() as *mut c_char, err_buf.len()) == 0
    {
      errno::set_errno(errno::EINVAL);
    }
    err_buf.as_mut_ptr() as *mut c_char
  }
}

#[no_mangle]
pub extern "C" fn ouma_strerror_l(
  num: c_int,
  _: locale_t
) -> *mut c_char {
  ouma_strerror(num)
}

#[thread_local]
static mut sig_buf: [u8; 255] = [0; 255];

#[inline(always)]
fn inner_strsignal(
  num: c_int,
  buf: *mut c_char,
  len: usize
) -> *const c_char {
  let mut n = num;

  let signame = if n >= 0 && n < signal::NSIG {
    signal::SYS_SIG_LIST[n as usize].as_ptr() as *const c_char
  } else {
    ptr::null_mut()
  };
  if !signame.is_null() {
    return signame;
  }

  let prefix = if n >= signal::SIGRTMIN && n <= signal::SIGRTMAX {
    n -= signal::SIGRTMIN;
    "Real-time"
  } else {
    "Unknown"
  };

  let mut w = streamwriter::StringWriter::new(buf, len);
  let _ = w.write_fmt(format_args!("{} signal {}", prefix, n));

  // TODO: compare fmt len to buflen

  buf
}

#[no_mangle]
pub extern "C" fn ouma_strsignal(num: c_int) -> *mut c_char {
  unsafe {
    inner_strsignal(num, sig_buf.as_ptr() as *mut c_char, sig_buf.len())
      as *mut c_char
  }
}
