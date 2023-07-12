use {
  crate::{
    c_char,
    c_int,
    char32_t,
    locale_t,
    malloc,
    mbstate_t,
    size_t,
    std::{stdio, stdlib, string, uchar},
    support::locale,
    wchar_t,
    wint_t
  },
  cbitset::BitSet256,
  core::{ffi::c_void, mem, ptr}
};

pub const WEOF: wint_t = 0xFFFF_FFFFu32;

#[inline(always)]
fn wstring_length(string: *const wchar_t) -> size_t {
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
pub extern "C" fn ouma_btowc(c: c_int) -> wint_t {
  if c == stdio::EOF {
    return WEOF;
  }
  let buf = c as c_char;
  // TODO: mutex lock
  static mut PRIV: mbstate_t = mbstate_t::new();
  let mut wc: wchar_t = 0;
  let status =
    unsafe { ouma_mbrtowc(&mut wc, &buf as *const c_char, 1, &mut PRIV) };
  if status == usize::max_value() || status == usize::max_value() - 1 {
    return WEOF;
  }
  wc as wint_t
}

#[no_mangle]
pub extern "C" fn ouma_wmemchr(
  ws: *const wchar_t,
  wc: wchar_t,
  n: size_t
) -> *mut wchar_t {
  let mut ws1 = ws;
  let mut i = n;
  while i != 0 {
    unsafe {
      if *ws1 == wc {
        return ws1 as *mut wchar_t;
      }
    }
    ws1 = ws1.wrapping_offset(1);
    i -= 1;
  }
  ptr::null_mut()
}

#[no_mangle]
pub extern "C" fn ouma_wmemcmp(
  left: *const wchar_t,
  right: *const wchar_t,
  n: size_t
) -> c_int {
  let mut i = 0;
  while i < n {
    let a = unsafe { *left.wrapping_offset(i as isize) };
    let b = unsafe { *right.wrapping_offset(i as isize) };
    if a != b {
      return a as c_int - b as c_int;
    }
    i += 1;
  }
  0
}

#[no_mangle]
pub extern "C" fn ouma_wmemcpy(
  dest: *mut wchar_t,
  src: *const wchar_t,
  n: size_t
) -> *mut wchar_t {
  let mut dest1 = dest;
  let mut src1 = src;
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
pub extern "C" fn ouma_wmemmove(
  dest: *mut wchar_t,
  src: *const wchar_t,
  n: size_t
) -> *mut wchar_t {
  let mut dest1 = dest;
  let mut src1 = src;
  if (dest1 as *const wchar_t) < src1 {
    let mut i = 0;
    while i < n {
      let s = src1;
      src1 = src1.wrapping_offset(1);
      let d = dest1;
      dest1 = dest1.wrapping_offset(1);
      unsafe { *d = *s };
      i += 1;
    }
  } else if (dest1 as *const wchar_t) > src1 {
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
pub extern "C" fn ouma_wmemset(
  ws: *mut wchar_t,
  wc: wchar_t,
  n: size_t
) -> *mut wchar_t {
  let mut ws1 = ws;
  let mut i = 0;
  while i < n {
    let ws2 = ws1;
    ws1 = ws1.wrapping_offset(1);
    unsafe {
      *ws2 = wc;
    }
    i += 1;
  }
  ws
}

#[no_mangle]
pub extern "C" fn ouma_wcpcpy(
  dest: *mut wchar_t,
  src: *const wchar_t
) -> *mut wchar_t {
  let len = wstring_length(src) + 1;
  ouma_wcpncpy(dest, src, len)
}

#[no_mangle]
pub extern "C" fn ouma_wcpncpy(
  dest: *mut wchar_t,
  src: *const wchar_t,
  n: size_t
) -> *mut wchar_t {
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
pub extern "C" fn ouma_wcschr(
  ws: *const wchar_t,
  wc: wchar_t
) -> *mut wchar_t {
  let mut ws1 = ws;
  loop {
    unsafe {
      if *ws1 == wc {
        return ws1 as *mut wchar_t;
      }
      if *ws1 == 0 {
        return ptr::null_mut();
      }
    }
    ws1 = ws1.wrapping_offset(1);
  }
}

#[no_mangle]
pub extern "C" fn ouma_wcsrchr(
  ws: *const wchar_t,
  wc: wchar_t
) -> *mut wchar_t {
  let mut ws1 = ws;
  let mut last = ptr::null_mut();
  loop {
    unsafe {
      if *ws1 == wc {
        last = ws1 as *mut wchar_t;
      }
      if *ws1 == 0 {
        return last;
      }
    }
    ws1 = ws1.wrapping_offset(1);
  }
}

#[no_mangle]
pub extern "C" fn ouma_wcscat(
  dest: *mut wchar_t,
  src: *const wchar_t
) -> *mut wchar_t {
  let len = wstring_length(src) + 1;
  ouma_wcsncat(dest, src, len)
}

#[no_mangle]
pub extern "C" fn ouma_wcsncat(
  dest: *mut wchar_t,
  src: *const wchar_t,
  n: size_t
) -> *mut wchar_t {
  let mut i = n;

  if n != 0 {
    let mut wd = dest;
    let mut ws = src;
    unsafe {
      while *wd != 0 {
        wd = wd.wrapping_offset(1);
      }
    }
    while i != 0 {
      let ws1 = ws;
      ws = ws.wrapping_offset(1);
      unsafe {
        *wd = *ws1;
        if *wd == 0 {
          break;
        }
      }
      wd = wd.wrapping_offset(1);
      i -= 1;
    }
    unsafe { *wd = 0 };
  }
  dest
}

#[no_mangle]
pub extern "C" fn ouma_wcscmp(
  left: *const wchar_t,
  right: *const wchar_t
) -> c_int {
  let len = wstring_length(right) + 1;
  ouma_wcsncmp(left, right, len)
}

#[no_mangle]
pub extern "C" fn ouma_wcsncmp(
  left: *const wchar_t,
  right: *const wchar_t,
  n: size_t
) -> c_int {
  let mut l = left;
  let mut r = right;
  let mut i = n;
  while i != 0 {
    let l2 = l;
    l = l.wrapping_offset(1);
    let c1 = unsafe { *l2 as wchar_t };
    let r2 = r;
    r = r.wrapping_offset(1);
    let c2 = unsafe { *r2 as wchar_t };
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
pub extern "C" fn ouma_wcscpy(
  dest: *mut wchar_t,
  src: *const wchar_t
) -> *mut wchar_t {
  let len = wstring_length(src) + 1;
  ouma_wcsncpy(dest, src, len)
}

#[no_mangle]
pub extern "C" fn ouma_wcsncpy(
  dest: *mut wchar_t,
  src: *const wchar_t,
  n: size_t
) -> *mut wchar_t {
  let mut i = n;
  let mut wd = dest;
  let mut ws = src;
  unsafe {
    while i > 0 && *ws != 0 {
      let wd1 = wd;
      wd = wd.wrapping_offset(1);
      let ws1 = ws;
      ws = ws.wrapping_offset(1);
      *wd1 = *ws1;
      i = i.wrapping_sub(1);
    }
  }
  while i != 0 {
    let wd1 = wd;
    wd = wd.wrapping_offset(1);
    unsafe {
      *wd1 = 0;
    }
    i -= 1;
  }
  dest
}

#[no_mangle]
pub extern "C" fn ouma_wcslen(ws: *const wchar_t) -> size_t {
  wstring_length(ws)
}

#[no_mangle]
pub extern "C" fn ouma_wcsnlen(
  ws: *const wchar_t,
  n: size_t
) -> size_t {
  let mut i = 0;
  while i < n {
    unsafe {
      if *ws.wrapping_add(i) == 0 {
        break;
      }
    }
    i += 1;
  }
  i as size_t
}

#[no_mangle]
pub extern "C" fn ouma_wcscspn(
  src: *const wchar_t,
  segment: *const wchar_t
) -> size_t {
  let mut ws1 = src;
  let mut ws2 = segment;
  let mut bitset = BitSet256::new();
  let mut i = 0;
  unsafe {
    while *ws2 != 0 {
      bitset.insert(*ws2 as usize);
      ws2 = ws2.wrapping_offset(1);
    }
    while *ws1 != 0 && !bitset.contains(*ws1 as usize) {
      i += 1;
      ws1 = ws1.wrapping_offset(1);
    }
  }
  i
}

#[no_mangle]
pub extern "C" fn ouma_wcsspn(
  src: *const wchar_t,
  segment: *const wchar_t
) -> size_t {
  let mut ws1 = src;
  let mut ws2 = segment;
  let mut bitset = BitSet256::new();
  let mut i = 0;
  unsafe {
    while *ws2 != 0 {
      bitset.insert(*ws2 as usize);
      ws2 = ws2.wrapping_offset(1);
    }
    while *ws1 != 0 && bitset.contains(*ws1 as usize) {
      i += 1;
      ws1 = ws1.wrapping_offset(1);
    }
  }
  i
}

#[no_mangle]
pub extern "C" fn ouma_wcspbrk(
  src: *const wchar_t,
  breakset: *const wchar_t
) -> *mut wchar_t {
  let mut ws1 = src;
  let mut ws2 = breakset;
  let mut bitset = BitSet256::new();
  unsafe {
    while *ws2 != 0 {
      bitset.insert(*ws2 as usize);
      ws2 = ws2.wrapping_offset(1);
    }
    while *ws1 != 0 && !bitset.contains(*ws1 as usize) {
      ws1 = ws1.wrapping_offset(1);
    }
    if *ws1 != 0 { ws1 as *mut wchar_t } else { ptr::null_mut() }
  }
}

#[no_mangle]
pub extern "C" fn ouma_wcsstr(
  haystack: *const wchar_t,
  needle: *const wchar_t
) -> *mut wchar_t {
  let mut wh = haystack;
  let len = wstring_length(needle);
  if len == 0 {
    return wh as *mut wchar_t;
  }
  unsafe {
    while *wh.wrapping_offset(0 as isize) != 0 {
      let mut i = 0;
      loop {
        if *needle.wrapping_offset(i as isize) == 0 {
          return wh as *mut wchar_t;
        }
        if *wh.wrapping_offset(i as isize) & !0 !=
          *needle.wrapping_offset(i as isize) & !0
        {
          break;
        }
        i += 1;
      }
      wh = wh.wrapping_offset(1);
    }
  }
  ptr::null_mut()
}

#[no_mangle]
pub extern "C" fn ouma_wcstok(
  ws: *mut wchar_t,
  wsep: *const wchar_t,
  lasts: *mut *mut wchar_t
) -> *mut wchar_t {
  let mut ws1 = ws;
  let mut wsep1 = wsep;
  let mut bitset = BitSet256::new();
  if ws1.is_null() {
    ws1 = unsafe { *lasts };
    if ws1.is_null() {
      return ptr::null_mut();
    }
  }
  unsafe {
    while *wsep1 != 0 {
      bitset.insert(*wsep1 as usize);
      wsep1 = wsep1.wrapping_offset(1);
    }
    while *ws1 != 0 && bitset.contains(*ws1 as usize) {
      ws1 = ws1.wrapping_offset(1);
    }
    if *ws1 == 0 {
      *lasts = ws1;
      return ptr::null_mut();
    }
  }
  let token = ws1;
  unsafe {
    while *ws1 != 0 {
      if bitset.contains(*ws1 as usize) {
        *ws1 = 0;
        ws1 = ws1.wrapping_offset(1);
        break;
      }
      ws1 = ws1.wrapping_offset(1);
    }
    *lasts = ws1;
  }
  token
}

#[no_mangle]
pub extern "C" fn ouma_wcsdup(s: *const wchar_t) -> *mut wchar_t {
  let len = wstring_length(s) + 1;
  let c: *mut wchar_t =
    unsafe { malloc::malloc(len * mem::size_of::<wchar_t>()) as *mut wchar_t };
  if c.is_null() {
    return ptr::null_mut();
  }
  ouma_wmemcpy(c, s, len);
  c
}

#[no_mangle]
pub extern "C" fn ouma_wcscoll(
  s1: *const wchar_t,
  s2: *const wchar_t
) -> c_int {
  ouma_wcscmp(s1, s2)
}

#[no_mangle]
pub extern "C" fn ouma_wcscoll_l(
  s1: *const wchar_t,
  s2: *const wchar_t,
  _loc: locale_t
) -> c_int {
  ouma_wcscmp(s1, s2)
}

#[no_mangle]
pub extern "C" fn ouma_wcsxfrm(
  s1: *mut wchar_t,
  s2: *const wchar_t,
  n: size_t
) -> size_t {
  let len = wstring_length(s2);
  if len < n {
    ouma_wcsncpy(s1, s2, n);
  }
  len
}

#[no_mangle]
pub extern "C" fn ouma_wcsxfrm_l(
  s1: *mut wchar_t,
  s2: *const wchar_t,
  n: size_t,
  _loc: locale_t
) -> size_t {
  let len = wstring_length(s2);
  if len < n {
    ouma_wcsncpy(s1, s2, n);
  }
  len
}

#[no_mangle]
pub extern "C" fn ouma_wctob(c: wint_t) -> c_int {
  if c <= 0x7F { c as c_int } else { stdio::EOF }
}

#[no_mangle]
pub extern "C" fn ouma_mbsinit(ps: *const mbstate_t) -> c_int {
  c_int::from(locale::mbstate_get_init(ps))
}

#[no_mangle]
pub extern "C" fn ouma_mbrlen(
  s: *const c_char,
  n: size_t,
  ps: *mut mbstate_t
) -> size_t {
  let mut wc: wchar_t = 0;
  ouma_mbrtowc(&mut wc, s, n, ps)
}

#[no_mangle]
pub extern "C" fn ouma_mbrtowc(
  pwc: *mut wchar_t,
  s: *const c_char,
  n: size_t,
  ps: *mut mbstate_t
) -> size_t {
  uchar::ouma_mbrtoc32(pwc as *mut char32_t, s, n, ps)
}

#[no_mangle]
extern "C" fn ouma_mbsnrtowcs(
  dst: *mut wchar_t,
  src: *mut *const c_char,
  nmc: size_t,
  len: size_t,
  ps: *mut mbstate_t
) -> size_t {
  let loc = unsafe { *locale::get_thread_locale() };
  let mut sb: *const c_char = unsafe { *src };
  let mut nms = nmc;
  let mut i = len;
  if dst.is_null() {
    let mut ret = 0;
    loop {
      let mut c32: char32_t = 0;
      let l = (loc.ctype.mbtoc32).unwrap()(&mut c32, sb, nms, ps);
      match l {
        | -1 => {
          return -1isize as usize;
        },
        | -2 => {
          return ret;
        },
        | _ => {
          if c32 == 0 {
            return ret;
          }
          sb = sb.wrapping_add(l as usize);
          nms = nms.wrapping_sub(l as usize);
          ret = ret.wrapping_add(1);
        }
      }
    }
  } else {
    let mut db = dst;
    while i > 0 {
      let l = (loc.ctype.mbtoc32).unwrap()(db as *mut char32_t, sb, nms, ps);
      match l {
        | -1 => {
          unsafe { *src = sb };
          return -1isize as usize;
        },
        | -2 => unsafe {
          *src = sb.wrapping_add(nms);
          return db.offset_from(dst) as size_t;
        },
        | _ => {
          unsafe {
            if *db == 0 {
              *src = ptr::null_mut();
              return db.offset_from(dst) as size_t;
            }
          }
          sb = sb.wrapping_add(l as usize);
          nms = nms.wrapping_sub(l as usize);
          db = db.wrapping_add(1);
        }
      }
      i = i.wrapping_sub(1);
    }
    unsafe {
      *src = sb;
      return db.offset_from(dst) as size_t;
    }
  }
}

#[no_mangle]
extern "C" fn ouma_mbsrtowcs(
  dst: *mut wchar_t,
  src: *mut *const c_char,
  len: size_t,
  ps: *mut mbstate_t
) -> size_t {
  ouma_mbsnrtowcs(dst, src, size_t::max_value(), len, ps)
}

#[no_mangle]
pub extern "C" fn ouma_wcrtomb(
  s: *mut c_char,
  wc: wchar_t,
  ps: *mut mbstate_t
) -> size_t {
  uchar::ouma_c32rtomb(s, wc as char32_t, ps)
}

#[no_mangle]
pub extern "C" fn ouma_wcsnrtombs(
  dst: *mut c_char,
  src: *mut *const wchar_t,
  nwc: size_t,
  len: size_t,
  ps: *mut mbstate_t
) -> size_t {
  let mut r: usize;
  let mut dsto: usize = 0;
  let mut srco: usize = 0;
  let s1 = unsafe { *src };
  let buf: [c_char; stdlib::MB_LEN_MAX as usize] =
    [0; stdlib::MB_LEN_MAX as usize];

  if dst.is_null() {
    while srco < nwc {
      let wc: wchar_t = unsafe { *s1.wrapping_offset(dsto as isize) };

      if wc < 0x80 {
        if wc == 0 {
          return srco;
        }

        r = 1;
      } else {
        r = ouma_wcrtomb(buf.as_ptr() as *mut c_char, wc, ps);
        if r == -1isize as usize {
          return r;
        }
      }

      dsto += 1;
      srco += r;
    }
  }

  while dsto < len && srco < nwc {
    let wc: wchar_t = unsafe { *s1.wrapping_offset(dsto as isize) };

    if wc < 0x80 {
      unsafe { *dst.wrapping_offset(srco as isize) = wc as c_char };

      if wc == 0 {
        unsafe { *src = ptr::null_mut() };
        return srco;
      }

      r = 1;
    } else if (len - srco) >= buf.len() {
      r = ouma_wcrtomb(dst.wrapping_add(srco), wc, ps);
      if r == -1isize as usize {
        unsafe {
          *src = s1.wrapping_add(srco);
        }
        return r;
      }
    } else {
      r = ouma_wcrtomb(buf.as_ptr() as *mut c_char, wc, ps);
      if r == -1isize as usize {
        unsafe {
          *src = s1.wrapping_add(srco);
        }
        return r;
      }
      if r > len - srco {
        break;
      }

      string::ouma_memcpy(
        dst.wrapping_add(srco) as *mut c_void,
        buf.as_ptr() as *const c_void,
        r
      );
    }

    dsto += 1;
    srco += r;
  }

  unsafe {
    *src = s1.wrapping_add(srco);
  }
  dsto
}

#[no_mangle]
pub extern "C" fn ouma_wcsrtombs(
  dst: *mut c_char,
  src: *mut *const wchar_t,
  len: size_t,
  ps: *mut mbstate_t
) -> size_t {
  ouma_wcsnrtombs(dst, src, size_t::max_value(), len, ps)
}

#[no_mangle]
extern "C" fn ouma_wcwidth(wc: wchar_t) -> c_int {
  const EXTENTS: [u32; 1399] = [
    0x00000000, 0x0001025e, 0x0005020c, 0x00056800, 0x000573ff, 0x00157251,
    0x0018006f, 0x001b8207, 0x001bd205, 0x001c2206, 0x001c6200, 0x001c7213,
    0x001d1adf, 0x00241806, 0x002452a5, 0x00298a25, 0x002aca31, 0x002c6a02,
    0x002c882c, 0x002df200, 0x002df800, 0x002e0200, 0x002e0801, 0x002e1a00,
    0x002e2001, 0x002e3200, 0x002e3800, 0x002e821a, 0x002f7a05, 0x00300005,
    0x00303209, 0x0030800a, 0x0030da00, 0x0030e000, 0x0030ea2d, 0x00325814,
    0x0033020f, 0x00338000, 0x00338a64, 0x0036b007, 0x0036f200, 0x0036f805,
    0x00372a01, 0x00373801, 0x00374a00, 0x00375003, 0x0037721f, 0x00387800,
    0x00388200, 0x00388800, 0x0038921d, 0x0039801a, 0x003a6a58, 0x003d300a,
    0x003d8a00, 0x003e022a, 0x003f5808, 0x003fa206, 0x003fe800, 0x003ff217,
    0x0040b003, 0x0040d200, 0x0040d808, 0x00412200, 0x00412802, 0x00414200,
    0x00414804, 0x0041820e, 0x00420218, 0x0042c802, 0x0042f200, 0x0043020a,
    0x0043821e, 0x00448001, 0x0044c007, 0x00450229, 0x00465038, 0x00481a36,
    0x0049d000, 0x0049da00, 0x0049e000, 0x0049ea03, 0x004a0807, 0x004a4a03,
    0x004a6800, 0x004a7202, 0x004a8806, 0x004ac209, 0x004b1001, 0x004b221c,
    0x004c0800, 0x004c1201, 0x004c2a07, 0x004c7a01, 0x004c9a15, 0x004d5206,
    0x004d9200, 0x004db203, 0x004de000, 0x004dea03, 0x004e0803, 0x004e3a01,
    0x004e5a01, 0x004e6800, 0x004e7200, 0x004eba00, 0x004ee201, 0x004efa02,
    0x004f1001, 0x004f3217, 0x004ff000, 0x00500801, 0x00501a00, 0x00502a05,
    0x00507a01, 0x00509a15, 0x00515206, 0x00519201, 0x0051aa01, 0x0051c201,
    0x0051e000, 0x0051f202, 0x00520801, 0x00523801, 0x00525802, 0x00528800,
    0x0052ca03, 0x0052f200, 0x00533209, 0x00538001, 0x00539202, 0x0053a800,
    0x0053b200, 0x00540801, 0x00541a00, 0x00542a08, 0x00547a02, 0x00549a15,
    0x00555206, 0x00559201, 0x0055aa04, 0x0055e000, 0x0055ea03, 0x00560804,
    0x00563801, 0x00564a00, 0x00565a01, 0x00566800, 0x00568200, 0x00570201,
    0x00571001, 0x0057320b, 0x0057ca00, 0x0057d005, 0x00580800, 0x00581201,
    0x00582a07, 0x00587a01, 0x00589a15, 0x00595206, 0x00599201, 0x0059aa04,
    0x0059e000, 0x0059ea01, 0x0059f800, 0x005a0200, 0x005a0803, 0x005a3a01,
    0x005a5a01, 0x005a6800, 0x005aa801, 0x005aba00, 0x005ae201, 0x005afa02,
    0x005b1001, 0x005b3211, 0x005c1000, 0x005c1a00, 0x005c2a05, 0x005c7202,
    0x005c9203, 0x005cca01, 0x005ce200, 0x005cf201, 0x005d1a01, 0x005d4202,
    0x005d720b, 0x005df201, 0x005e0000, 0x005e0a01, 0x005e3202, 0x005e5202,
    0x005e6800, 0x005e8200, 0x005eba00, 0x005f3214, 0x00600000, 0x00600a02,
    0x00602000, 0x00602a07, 0x00607202, 0x00609216, 0x0061520f, 0x0061e000,
    0x0061ea00, 0x0061f002, 0x00620a03, 0x00623002, 0x00625003, 0x0062a801,
    0x0062c202, 0x0062ea00, 0x00630201, 0x00631001, 0x00633209, 0x0063ba09,
    0x00640800, 0x0064120a, 0x00647202, 0x00649216, 0x00655209, 0x0065aa04,
    0x0065e000, 0x0065ea01, 0x0065f800, 0x00660204, 0x00663000, 0x00663a01,
    0x00665201, 0x00666001, 0x0066aa01, 0x0066ea01, 0x00670201, 0x00671001,
    0x00673209, 0x00678a02, 0x00680001, 0x0068120a, 0x00687202, 0x00689228,
    0x0069d801, 0x0069ea03, 0x006a0803, 0x006a3202, 0x006a5202, 0x006a6800,
    0x006a7201, 0x006aa20d, 0x006b1001, 0x006b3219, 0x006c0800, 0x006c1201,
    0x006c2a11, 0x006cd217, 0x006d9a08, 0x006dea00, 0x006e0206, 0x006e5000,
    0x006e7a02, 0x006e9002, 0x006eb000, 0x006ec207, 0x006f3209, 0x006f9202,
    0x00700a2f, 0x00718800, 0x00719201, 0x0071a006, 0x0071fa07, 0x00723807,
    0x00727a0c, 0x00740a01, 0x00742200, 0x00743204, 0x00746217, 0x00752a00,
    0x00753a09, 0x00758800, 0x00759201, 0x0075a008, 0x0075ea00, 0x00760204,
    0x00763200, 0x00764006, 0x00768209, 0x0076e203, 0x00780217, 0x0078c001,
    0x0078d21a, 0x0079a800, 0x0079b200, 0x0079b800, 0x0079c200, 0x0079c800,
    0x0079d20d, 0x007a4a23, 0x007b880d, 0x007bfa00, 0x007c0004, 0x007c2a00,
    0x007c3001, 0x007c4204, 0x007c680a, 0x007cc823, 0x007df207, 0x007e3000,
    0x007e3a05, 0x007e720c, 0x0080022c, 0x00816803, 0x00818a00, 0x00819005,
    0x0081c200, 0x0081c801, 0x0081da01, 0x0081e801, 0x0081fa18, 0x0082c001,
    0x0082d203, 0x0082f002, 0x00830a0f, 0x00838803, 0x0083aa0c, 0x00841000,
    0x00841a01, 0x00842801, 0x00843a05, 0x00846800, 0x0084720e, 0x0084e800,
    0x0084f227, 0x00863a00, 0x00866a00, 0x0086822f, 0x0088045f, 0x008b02e8,
    0x00925203, 0x00928206, 0x0092c200, 0x0092d203, 0x00930228, 0x00945203,
    0x00948220, 0x00959203, 0x0095c206, 0x00960200, 0x00961203, 0x0096420e,
    0x0096c238, 0x00989203, 0x0098c242, 0x009ae802, 0x009b021c, 0x009c0219,
    0x009d0255, 0x009fc205, 0x00a003ff, 0x00b0029c, 0x00b50258, 0x00b80211,
    0x00b89002, 0x00b8aa00, 0x00b8fa12, 0x00b99001, 0x00b9a202, 0x00ba0211,
    0x00ba9001, 0x00bb020c, 0x00bb7202, 0x00bb9001, 0x00bc0233, 0x00bda001,
    0x00bdb200, 0x00bdb806, 0x00bdf207, 0x00be3000, 0x00be3a01, 0x00be480a,
    0x00bea208, 0x00bee800, 0x00bf0209, 0x00bf8209, 0x00c0020a, 0x00c05804,
    0x00c08209, 0x00c10258, 0x00c40204, 0x00c42801, 0x00c43a21, 0x00c54800,
    0x00c55200, 0x00c58245, 0x00c8021e, 0x00c90002, 0x00c91a03, 0x00c93801,
    0x00c94a02, 0x00c98201, 0x00c99000, 0x00c99a05, 0x00c9c802, 0x00ca0200,
    0x00ca2229, 0x00cb8204, 0x00cc022b, 0x00cd8219, 0x00ce820a, 0x00cef238,
    0x00d0b801, 0x00d0ca01, 0x00d0d800, 0x00d0f237, 0x00d2b000, 0x00d2ba00,
    0x00d2c006, 0x00d30000, 0x00d30a00, 0x00d31000, 0x00d31a01, 0x00d32807,
    0x00d36a05, 0x00d39809, 0x00d3f800, 0x00d40209, 0x00d48209, 0x00d5020d,
    0x00d5801e, 0x00d80003, 0x00d8222f, 0x00d9a000, 0x00d9aa00, 0x00d9b004,
    0x00d9da00, 0x00d9e000, 0x00d9ea04, 0x00da1000, 0x00da1a09, 0x00da821a,
    0x00db5808, 0x00dba20a, 0x00dc0001, 0x00dc121f, 0x00dd1003, 0x00dd3201,
    0x00dd4001, 0x00dd5200, 0x00dd5802, 0x00dd7237, 0x00df3000, 0x00df3a00,
    0x00df4001, 0x00df5202, 0x00df6800, 0x00df7200, 0x00df7802, 0x00df9201,
    0x00dfe22f, 0x00e16007, 0x00e1a201, 0x00e1b001, 0x00e1da0e, 0x00e26a3b,
    0x00e4822a, 0x00e5ea0a, 0x00e68002, 0x00e69a00, 0x00e6a00c, 0x00e70a00,
    0x00e71006, 0x00e74a03, 0x00e76800, 0x00e77205, 0x00e7a000, 0x00e7aa02,
    0x00e7c001, 0x00e7d200, 0x00e802bf, 0x00ee003f, 0x00f00315, 0x00f8c205,
    0x00f90225, 0x00fa4205, 0x00fa8207, 0x00faca00, 0x00fada00, 0x00faea00,
    0x00fafa1e, 0x00fc0234, 0x00fdb20e, 0x00fe320d, 0x00feb205, 0x00feea12,
    0x00ff9202, 0x00ffb208, 0x0100020a, 0x01005804, 0x01008217, 0x01015004,
    0x01017a30, 0x01030004, 0x01033009, 0x01038201, 0x0103a21a, 0x0104820c,
    0x01050220, 0x01068020, 0x0108028b, 0x010c8389, 0x0118d401, 0x0118e20c,
    0x01194c01, 0x01195abd, 0x011f4c03, 0x011f6a02, 0x011f8400, 0x011f8a01,
    0x011f9c00, 0x011fa232, 0x0122020a, 0x0123039c, 0x012fec01, 0x012ffa14,
    0x0130a401, 0x0130b231, 0x0132440b, 0x0132a22a, 0x0133fc00, 0x01340212,
    0x01349c00, 0x0134a20c, 0x01350c00, 0x01351207, 0x01355401, 0x01356210,
    0x0135ec01, 0x0135fa04, 0x01362401, 0x01363207, 0x01367400, 0x01367a04,
    0x0136a400, 0x0136aa14, 0x01375400, 0x01375a06, 0x01379401, 0x0137a200,
    0x0137ac00, 0x0137b203, 0x0137d400, 0x0137da01, 0x0137ec00, 0x0137f206,
    0x01382c00, 0x01383203, 0x01385401, 0x0138621b, 0x01394400, 0x01394a22,
    0x013a6400, 0x013a6a00, 0x013a7400, 0x013a7a03, 0x013a9c02, 0x013ab200,
    0x013abc00, 0x013ac23c, 0x013cac02, 0x013cc217, 0x013d8400, 0x013d8a0d,
    0x013dfc00, 0x013e03ff, 0x014e035a, 0x0158dc01, 0x0158ea32, 0x015a8400,
    0x015a8a03, 0x015aac00, 0x015ab21d, 0x015bb21f, 0x015cbb57, 0x01677802,
    0x01679201, 0x0167ca2c, 0x01693a00, 0x01696a00, 0x01698237, 0x016b7a01,
    0x016bf800, 0x016c0216, 0x016d0206, 0x016d4206, 0x016d8206, 0x016dc206,
    0x016e0206, 0x016e4206, 0x016e8206, 0x016ec206, 0x016f001f, 0x0170025d,
    0x01740419, 0x0174dc58, 0x017804d5, 0x017f840b, 0x01800429, 0x01815003,
    0x01817410, 0x0181fa00, 0x01820c55, 0x0184c801, 0x0184dc64, 0x01882c2a,
    0x01898c5d, 0x018c8453, 0x018f842e, 0x01910427, 0x01924207, 0x019285b0,
    0x026dfc00, 0x026e023f, 0x02700400, 0x04fffdff, 0x050ffdff, 0x051ffc8d,
    0x05248436, 0x0526835b, 0x0532022e, 0x05337803, 0x05339a00, 0x0533a009,
    0x0533f21f, 0x0534f001, 0x0535024f, 0x05378001, 0x05379205, 0x053802ca,
    0x053e8201, 0x053e9a00, 0x053eaa04, 0x053f920f, 0x05401000, 0x05401a02,
    0x05403000, 0x05403a03, 0x05405800, 0x05406218, 0x05412801, 0x05413a04,
    0x05416000, 0x05418209, 0x05420237, 0x05440243, 0x05462001, 0x0546720b,
    0x05470011, 0x0547920c, 0x0547f800, 0x05480225, 0x05493007, 0x05497218,
    0x054a380a, 0x054a9201, 0x054afa00, 0x054b041c, 0x054c0002, 0x054c1a2f,
    0x054d9800, 0x054da201, 0x054db003, 0x054dd201, 0x054de001, 0x054df20f,
    0x054e7a0a, 0x054ef206, 0x054f2800, 0x054f3218, 0x05500228, 0x05514805,
    0x05517a01, 0x05518801, 0x05519a01, 0x0551a801, 0x05520202, 0x05521800,
    0x05522207, 0x05526000, 0x05526a00, 0x05528209, 0x0552e21f, 0x0553e000,
    0x0553ea32, 0x05558000, 0x05558a00, 0x05559002, 0x0555aa01, 0x0555b801,
    0x0555ca04, 0x0555f001, 0x05560200, 0x05560800, 0x05561200, 0x0556da10,
    0x05576001, 0x05577207, 0x0557b000, 0x05580a05, 0x05584a05, 0x05588a05,
    0x05590206, 0x05594206, 0x0559823b, 0x055b8274, 0x055f2800, 0x055f3201,
    0x055f4000, 0x055f4a03, 0x055f6800, 0x055f8209, 0x05600400, 0x06bd1c00,
    0x06bd8216, 0x06be5a30, 0x06c00200, 0x06dbfa01, 0x06dffa01, 0x06fffa01,
    0x07c7fa00, 0x07c8056d, 0x07d38469, 0x07d80206, 0x07d89a04, 0x07d8ea00,
    0x07d8f000, 0x07d8fa17, 0x07d9c204, 0x07d9f200, 0x07da0201, 0x07da1a01,
    0x07da327c, 0x07de9bbc, 0x07ec9235, 0x07ee7a00, 0x07ef820f, 0x07f0000f,
    0x07f08409, 0x07f1000f, 0x07f18422, 0x07f2a412, 0x07f34403, 0x07f38204,
    0x07f3b286, 0x07f7f800, 0x07f80c5f, 0x07fb0a5d, 0x07fe1205, 0x07fe5205,
    0x07fe9205, 0x07fed202, 0x07ff0406, 0x07ff4206, 0x07ffc802, 0x07ffe201,
    0x0800020b, 0x08006a19, 0x08014212, 0x0801e201, 0x0801fa0e, 0x0802820d,
    0x0804027a, 0x08080202, 0x08083a2c, 0x0809ba57, 0x080c820c, 0x080d0200,
    0x080e822c, 0x080fe800, 0x0814021c, 0x08150230, 0x08170000, 0x08170a1a,
    0x08180223, 0x08196a1d, 0x081a8225, 0x081bb004, 0x081c021d, 0x081cfa24,
    0x081e420d, 0x0820029d, 0x08250209, 0x08258223, 0x0826c223, 0x08280227,
    0x08298233, 0x082b7a0b, 0x082be20e, 0x082c6206, 0x082ca201, 0x082cba0a,
    0x082d1a0e, 0x082d9a06, 0x082dda01, 0x08300336, 0x083a0215, 0x083b0207,
    0x083c0205, 0x083c3a29, 0x083d9208, 0x08400205, 0x08404200, 0x0840522b,
    0x0841ba01, 0x0841e200, 0x0841fa16, 0x0842ba47, 0x08453a08, 0x08470212,
    0x0847a201, 0x0847da20, 0x0848fa1a, 0x0849fa00, 0x084c0237, 0x084de213,
    0x084e922e, 0x08500802, 0x08502801, 0x08506003, 0x08508203, 0x0850aa02,
    0x0850ca1c, 0x0851c002, 0x0851f800, 0x08520208, 0x08528208, 0x0853023f,
    0x08560224, 0x08572801, 0x08575a0b, 0x08580235, 0x0859ca1c, 0x085ac21a,
    0x085bc219, 0x085cca03, 0x085d4a06, 0x08600248, 0x08640232, 0x08660232,
    0x0867d229, 0x08692003, 0x08698209, 0x0873021e, 0x08740229, 0x08755801,
    0x08756a00, 0x08758201, 0x0877e802, 0x08780227, 0x08798215, 0x087a300a,
    0x087a8a08, 0x087b8211, 0x087c1003, 0x087c3203, 0x087d821b, 0x087f0216,
    0x08800200, 0x08800800, 0x08801235, 0x0881c00e, 0x08823a06, 0x0882921d,
    0x08838000, 0x08838a01, 0x08839801, 0x0883aa00, 0x0883f802, 0x08841230,
    0x08859803, 0x0885ba01, 0x0885c801, 0x0885da01, 0x0885e800, 0x0885f203,
    0x08861000, 0x08866800, 0x08868218, 0x08878209, 0x08880002, 0x08881a23,
    0x08893804, 0x08896200, 0x08896807, 0x0889b211, 0x088a8222, 0x088b9800,
    0x088ba202, 0x088c0001, 0x088c1233, 0x088db008, 0x088dfa09, 0x088e4803,
    0x088e6a01, 0x088e7800, 0x088e820f, 0x088f0a13, 0x08900211, 0x08909a1b,
    0x08917802, 0x08919201, 0x0891a000, 0x0891aa00, 0x0891b001, 0x0891c205,
    0x0891f000, 0x0891fa01, 0x08920800, 0x08940206, 0x08944200, 0x08945203,
    0x08947a0e, 0x0894fa0a, 0x0895822e, 0x0896f800, 0x08970202, 0x08971807,
    0x08978209, 0x08980001, 0x08981201, 0x08982a07, 0x08987a01, 0x08989a15,
    0x08995206, 0x08999201, 0x0899aa04, 0x0899d801, 0x0899ea02, 0x089a0000,
    0x089a0a03, 0x089a3a01, 0x089a5a02, 0x089a8200, 0x089aba00, 0x089aea06,
    0x089b3006, 0x089b8004, 0x08a00237, 0x08a1c007, 0x08a20201, 0x08a21002,
    0x08a22a00, 0x08a23000, 0x08a23a14, 0x08a2ea00, 0x08a2f000, 0x08a2fa02,
    0x08a40232, 0x08a59805, 0x08a5ca00, 0x08a5d000, 0x08a5da03, 0x08a5f801,
    0x08a60a00, 0x08a61001, 0x08a62203, 0x08a68209, 0x08ac0231, 0x08ad9003,
    0x08adc203, 0x08ade001, 0x08adf200, 0x08adf801, 0x08ae0a1a, 0x08aee001,
    0x08b00232, 0x08b19807, 0x08b1da01, 0x08b1e800, 0x08b1f200, 0x08b1f801,
    0x08b20a03, 0x08b28209, 0x08b3020c, 0x08b4022a, 0x08b55800, 0x08b56200,
    0x08b56800, 0x08b57201, 0x08b58005, 0x08b5b200, 0x08b5b800, 0x08b5c201,
    0x08b60209, 0x08b8021a, 0x08b8e802, 0x08b90201, 0x08b91003, 0x08b93200,
    0x08b93804, 0x08b98216, 0x08c0022e, 0x08c17808, 0x08c1c200, 0x08c1c801,
    0x08c1da00, 0x08c50252, 0x08c7fa07, 0x08c84a00, 0x08c86207, 0x08c8aa01,
    0x08c8c21d, 0x08c9ba01, 0x08c9d801, 0x08c9ea00, 0x08c9f000, 0x08c9fa03,
    0x08ca1800, 0x08ca2202, 0x08ca8209, 0x08cd0207, 0x08cd5229, 0x08cea003,
    0x08ced001, 0x08cee203, 0x08cf0000, 0x08cf0a03, 0x08d00200, 0x08d00809,
    0x08d05a27, 0x08d19805, 0x08d1ca01, 0x08d1d803, 0x08d1fa07, 0x08d23800,
    0x08d28200, 0x08d28805, 0x08d2ba01, 0x08d2c802, 0x08d2e22d, 0x08d4500c,
    0x08d4ba00, 0x08d4c001, 0x08d4d208, 0x08d58248, 0x08d80209, 0x08e00208,
    0x08e05225, 0x08e18006, 0x08e1c005, 0x08e1f200, 0x08e1f800, 0x08e20205,
    0x08e2821c, 0x08e3821f, 0x08e49015, 0x08e54a00, 0x08e55006, 0x08e58a00,
    0x08e59001, 0x08e5a200, 0x08e5a801, 0x08e80206, 0x08e84201, 0x08e85a25,
    0x08e98805, 0x08e9d000, 0x08e9e001, 0x08e9f806, 0x08ea3200, 0x08ea3800,
    0x08ea8209, 0x08eb0205, 0x08eb3a01, 0x08eb5224, 0x08ec8001, 0x08ec9a01,
    0x08eca800, 0x08ecb200, 0x08ecb800, 0x08ecc200, 0x08ed0209, 0x08f70212,
    0x08f79801, 0x08f7aa03, 0x08f80001, 0x08f8120e, 0x08f89223, 0x08f9b004,
    0x08f9f201, 0x08fa0000, 0x08fa0a00, 0x08fa1000, 0x08fa1a16, 0x08fd8200,
    0x08fe0231, 0x08fffbff, 0x090ffb9a, 0x0920026e, 0x09238204, 0x092402c3,
    0x097c8262, 0x098003ff, 0x099003ff, 0x09a0022f, 0x09a18010, 0x09a20a05,
    0x09a2380e, 0x0a2003ff, 0x0a300246, 0x0b4003ff, 0x0b500238, 0x0b52021e,
    0x0b530209, 0x0b537250, 0x0b560209, 0x0b56821d, 0x0b578004, 0x0b57aa00,
    0x0b58022f, 0x0b598006, 0x0b59ba0e, 0x0b5a8209, 0x0b5ada06, 0x0b5b1a14,
    0x0b5bea12, 0x0b72025a, 0x0b78024a, 0x0b7a7800, 0x0b7a8237, 0x0b7c7803,
    0x0b7c9a0c, 0x0b7f0403, 0x0b7f2000, 0x0b7f8401, 0x0b800400, 0x0c3fbc00,
    0x0c4005ff, 0x0c5005ff, 0x0c6004d5, 0x0c680400, 0x0c684400, 0x0d7f8403,
    0x0d7fac06, 0x0d7fec01, 0x0d800522, 0x0d899400, 0x0d8a8402, 0x0d8aac00,
    0x0d8b2403, 0x0d8b858b, 0x0de0026a, 0x0de3820c, 0x0de40208, 0x0de48209,
    0x0de4e200, 0x0de4e801, 0x0de4fa00, 0x0de50003, 0x0e78002d, 0x0e798016,
    0x0e7a8273, 0x0e8002f5, 0x0e880226, 0x0e894a3d, 0x0e8b3802, 0x0e8b5208,
    0x0e8b980f, 0x0e8c1a01, 0x0e8c2806, 0x0e8c621d, 0x0e8d5003, 0x0e8d723c,
    0x0e900241, 0x0e921002, 0x0e922a00, 0x0e960213, 0x0e970213, 0x0e980256,
    0x0e9b0218, 0x0ea00254, 0x0ea2b246, 0x0ea4f201, 0x0ea51200, 0x0ea52a01,
    0x0ea54a03, 0x0ea5720b, 0x0ea5da00, 0x0ea5ea06, 0x0ea62a40, 0x0ea83a03,
    0x0ea86a07, 0x0ea8b206, 0x0ea8f21b, 0x0ea9da03, 0x0eaa0204, 0x0eaa3200,
    0x0eaa5206, 0x0eaa9353, 0x0eb54323, 0x0ebe73ff, 0x0ece7231, 0x0ed00036,
    0x0ed1ba03, 0x0ed1d831, 0x0ed36a07, 0x0ed3a800, 0x0ed3b20d, 0x0ed42000,
    0x0ed42a06, 0x0ed4d804, 0x0ed5080e, 0x0ef8021e, 0x0ef92a05, 0x0f000006,
    0x0f004010, 0x0f00d806, 0x0f011801, 0x0f013004, 0x0f01823d, 0x0f047800,
    0x0f08022c, 0x0f098006, 0x0f09ba06, 0x0f0a0209, 0x0f0a7201, 0x0f14821d,
    0x0f157000, 0x0f16022b, 0x0f176003, 0x0f178209, 0x0f17fa00, 0x0f26821b,
    0x0f276003, 0x0f278209, 0x0f3f0206, 0x0f3f4203, 0x0f3f6a01, 0x0f3f820e,
    0x0f4002c4, 0x0f463a08, 0x0f468006, 0x0f480243, 0x0f4a2006, 0x0f4a5a00,
    0x0f4a8209, 0x0f4af201, 0x0f638a43, 0x0f680a3c, 0x0f700203, 0x0f702a1a,
    0x0f710a01, 0x0f712200, 0x0f713a00, 0x0f714a09, 0x0f71a203, 0x0f71ca00,
    0x0f71da00, 0x0f721200, 0x0f723a00, 0x0f724a00, 0x0f725a00, 0x0f726a02,
    0x0f728a01, 0x0f72a200, 0x0f72ba00, 0x0f72ca00, 0x0f72da00, 0x0f72ea00,
    0x0f72fa00, 0x0f730a01, 0x0f732200, 0x0f733a03, 0x0f736206, 0x0f73a203,
    0x0f73ca03, 0x0f73f200, 0x0f740209, 0x0f745a10, 0x0f750a02, 0x0f752a04,
    0x0f755a10, 0x0f778201, 0x0f800203, 0x0f802400, 0x0f802a26, 0x0f818263,
    0x0f85020e, 0x0f858a0e, 0x0f860a0d, 0x0f867c00, 0x0f868a24, 0x0f88028d,
    0x0f8c7400, 0x0f8c7a01, 0x0f8c8c09, 0x0f8cda12, 0x0f8f3219, 0x0f900402,
    0x0f90842b, 0x0f920408, 0x0f928401, 0x0f930405, 0x0f980420, 0x0f990a0b,
    0x0f996c08, 0x0f99b200, 0x0f99bc45, 0x0f9bea00, 0x0f9bf415, 0x0f9ca20b,
    0x0f9d042a, 0x0f9e5a03, 0x0f9e7c04, 0x0f9ea20b, 0x0f9f0410, 0x0f9f8a02,
    0x0f9fa400, 0x0f9faa02, 0x0f9fc446, 0x0fa1fa00, 0x0fa20400, 0x0fa20a00,
    0x0fa214ba, 0x0fa7ea01, 0x0fa7fc3e, 0x0fa9f20c, 0x0faa5c03, 0x0faa7a00,
    0x0faa8417, 0x0fab4211, 0x0fabd400, 0x0fabda19, 0x0facac01, 0x0facba0c,
    0x0fad2400, 0x0fad2a55, 0x0fafdc54, 0x0fb2822f, 0x0fb40445, 0x0fb63205,
    0x0fb66400, 0x0fb66a02, 0x0fb68402, 0x0fb69a01, 0x0fb6ac02, 0x0fb6e403,
    0x0fb7020a, 0x0fb75c01, 0x0fb78203, 0x0fb7a408, 0x0fb80276, 0x0fbbda5e,
    0x0fbf040b, 0x0fbf8400, 0x0fc0020b, 0x0fc08237, 0x0fc28209, 0x0fc30227,
    0x0fc4821d, 0x0fc58201, 0x0fc8020b, 0x0fc8642e, 0x0fc9da00, 0x0fc9e409,
    0x0fca3200, 0x0fca3cb8, 0x0fd00253, 0x0fd3020d, 0x0fd3840c, 0x0fd40408,
    0x0fd4842d, 0x0fd5fc06, 0x0fd6740d, 0x0fd70408, 0x0fd78408, 0x0fd80292,
    0x0fdca236, 0x0fdf8209, 0x10000400, 0x1536fc00, 0x15380400, 0x15b9cc00,
    0x15ba0400, 0x15c0ec00, 0x15c10400, 0x16750c00, 0x16758400, 0x175f0400,
    0x17c005ff, 0x17d0041d, 0x18000400, 0x189a5400, 0x189a8400, 0x191d7c00,
    0x70000800, 0x7001005f, 0x700800ef, 0x78000200, 0x7fffea00, 0x80000200,
    0x87ffea00
  ];
  let ch: u32 = wc as u32;
  let key: u32 = (ch << 11) | 0x7ff;
  let mut min: usize = 0;
  let mut max: usize = EXTENTS.len() - 1;
  loop {
    let mid: usize = (min + max + 1) / 2;
    if key < EXTENTS[mid] {
      max = mid - 1;
    } else {
      min = mid;
    }
    if !(min < max) {
      break;
    }
  }
  if ch >= (EXTENTS[min] >> 11) &&
    ch <= (EXTENTS[min] >> 11) + (EXTENTS[min] & 0x1ff)
  {
    ((EXTENTS[min] >> 9) & 0x3) as c_int
  } else {
    -1
  }
}

#[no_mangle]
pub extern "C" fn ouma_wcswidth(
  pwcs: *const wchar_t,
  n: size_t
) -> c_int {
  let mut i = n;
  let mut p = pwcs;
  let mut len = 0;
  unsafe {
    while i > 0 && *p != 0 {
      let p1 = p;
      p = p.wrapping_offset(1);
      let l = ouma_wcwidth(*p1);
      if l == -1 {
        return 1;
      }
      len += l;
      i -= 1;
    }
  }
  len
}
