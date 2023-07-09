#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <iterator>

#include <wchar.h>

#define UNICODE

#define num_bytes 128
#define NUM_WCHARS(num_bytes) ((num_bytes)/sizeof(wchar_t))

extern "C" {
  typedef struct {
    char16_t __surrogate;
    unsigned int __bytesleft;
    char32_t __partial;
    char32_t __lowerbound;
  } __ouma_mbstate_t;
  typedef __ouma_mbstate_t ouma_mbstate_t;

  wchar_t *ouma_wmemchr(const wchar_t *, wchar_t, size_t);
  int ouma_wmemcmp(const wchar_t *, const wchar_t *, size_t);
  wchar_t *ouma_wmemcpy(wchar_t *__restrict, const wchar_t *__restrict, size_t);
  wchar_t *ouma_wmemmove(wchar_t *, const wchar_t *, size_t);
  wchar_t *ouma_wmemset(wchar_t *, wchar_t, size_t);
  wchar_t *ouma_wcpcpy(wchar_t *__restrict, const wchar_t *__restrict);
  wchar_t *ouma_wcpncpy(wchar_t *__restrict, const wchar_t *__restrict, size_t);
  wchar_t *ouma_wcschr(const wchar_t *, wchar_t);
  wchar_t *ouma_wcsrchr(const wchar_t *, wchar_t);
  wchar_t *ouma_wcsncat(wchar_t *__restrict, const wchar_t *__restrict, size_t);
  int ouma_wcsncmp(const wchar_t *, const wchar_t *, size_t);
  wchar_t *ouma_wcsncpy(wchar_t *__restrict, const wchar_t *__restrict, size_t);
  size_t ouma_wcsnlen(const wchar_t *, size_t);
  wchar_t *ouma_wcscat(wchar_t *__restrict, const wchar_t *__restrict);
  wchar_t *ouma_wcscpy(wchar_t *__restrict, const wchar_t *__restrict);
  int ouma_wcscmp(const wchar_t *, const wchar_t *);
  size_t ouma_wcslen(const wchar_t *);
  size_t ouma_wcscspn(const wchar_t *, const wchar_t *);
  size_t ouma_wcsspn(const wchar_t *, const wchar_t *);
  wchar_t *ouma_wcspbrk(const wchar_t *, const wchar_t *);
  wchar_t *ouma_wcsstr(const wchar_t *__restrict, const wchar_t *__restrict);
  wchar_t *ouma_wcstok(wchar_t *__restrict, const wchar_t *__restrict, wchar_t **__restrict);
  int ouma_wcscoll(const wchar_t *, const wchar_t *);
  int ouma_wcscoll_l(const wchar_t *, const wchar_t *, locale_t);
  size_t ouma_wcsxfrm(wchar_t *__restrict, const wchar_t *__restrict, size_t);
  size_t ouma_wcsxfrm_l(wchar_t *__restrict, const wchar_t *__restrict, size_t, locale_t);
  wchar_t *ouma_wcsdup(const wchar_t *);
  int ouma_wctob(wint_t);
  int ouma_mbsinit(const ouma_mbstate_t *);
  size_t ouma_mbrtowc(wchar_t *__restrict, const char *__restrict, size_t, ouma_mbstate_t *__restrict);
  size_t ouma_wcrtomb(char *__restrict, wchar_t, ouma_mbstate_t *__restrict); 
  size_t ouma_mbsnrtowcs(wchar_t *__restrict, const char **__restrict, size_t, size_t, ouma_mbstate_t *__restrict);
  size_t ouma_mbsrtowcs(wchar_t *__restrict, const char **__restrict, size_t, ouma_mbstate_t *__restrict);
  size_t ouma_wcsnrtombs(char *__restrict, const wchar_t **__restrict, size_t, size_t, ouma_mbstate_t *__restrict);
  size_t ouma_wcsrtombs(char *__restrict, const wchar_t **__restrict, size_t, ouma_mbstate_t *__restrict);
  size_t ouma_mbrlen(const char *__restrict, size_t, ouma_mbstate_t *__restrict);
  wint_t ouma_btowc(int);
  int ouma_wcwidth(wchar_t);
  int ouma_wcswidth(const wchar_t *, size_t);

/* When ctype support gets added
  int ouma_wcscasecmp(const wchar_t *, const wchar_t *);
  int ouma_wcscasecmp_l(const wchar_t *, const wchar_t *, locale_t);
  int ouma_wcsncasecmp(const wchar_t *, const wchar_t *, size_t);
  int ouma_wcsncasecmp_l(const wchar_t *, const wchar_t *, size_t, locale_t);
*/

  extern _Thread_local int __oumalibc_errno;
}

TEST(wmemchr, null) {
  ASSERT_EQ(NULL, ouma_wmemchr((wchar_t *)NULL, L'A', 0));
}

TEST(wmemchr, match) {
  wchar_t buf[] = L"Foo bar baz";
  ASSERT_EQ(buf + 5, ouma_wmemchr(buf, L'a', std::size(buf)));
}

TEST(wmemchr, nomatch) {
  wchar_t buf[] = L"Foo bar baz";
  ASSERT_EQ(NULL, ouma_wmemchr(buf, L'x', std::size(buf)));
}

TEST(wmemcmp, null) {
  ASSERT_EQ(0, ouma_wmemcmp(NULL, NULL, 0));
}

TEST(wmemcmp, example) {
  const wchar_t buf1[] = L"Hello";
  const wchar_t buf2[] = L"Helxo";
  ASSERT_EQ(0, ouma_wmemcmp(buf1, buf1, std::size(buf1)));
  ASSERT_GT(0, ouma_wmemcmp(buf1, buf2, std::size(buf1)));
  ASSERT_LT(0, ouma_wmemcmp(buf2, buf1, std::size(buf1)));
}

TEST(wmemcpy, null) {
  ASSERT_EQ((wchar_t *)42, ouma_wmemcpy((wchar_t *)42, (wchar_t *)123, 0));
}

TEST(wmemcpy, example) {
  const wchar_t buf1[8] = L"Foo\0Bar";
  wchar_t buf2[8];
  ASSERT_EQ(buf2, ouma_wmemcpy(buf2, buf1, std::size(buf1)));
  ASSERT_THAT(buf2, testing::ElementsAreArray(buf1));
}

TEST(wmemmove, null) {
  ASSERT_EQ((wchar_t *)42, ouma_wmemmove((wchar_t *)42, (wchar_t *)34, 0));
}

TEST(wmemmove, example1) {
  wchar_t buf[] = L"abcdefghijkl";
  ASSERT_EQ(buf, ouma_wmemmove(buf, buf + 4, 8));
  ASSERT_STREQ(L"efghijklijkl", buf);
}

TEST(wmemmove, example2) {
  wchar_t buf[] = L"abcdefghijkl";
  ASSERT_EQ(buf + 4, ouma_wmemmove(buf + 4, buf, 8));
  ASSERT_STREQ(L"abcdabcdefgh", buf);
}

TEST(wmemset, null) {
  ASSERT_EQ((wchar_t *)5, ouma_wmemset((wchar_t *)5, L'A', 0));
}

TEST(wmemset, example) {
  wchar_t buf[11];
  ASSERT_EQ(buf, ouma_wmemset(buf, L'!', 10));
  buf[10] = L'\0';
  ASSERT_STREQ(L"!!!!!!!!!!", buf);
}

TEST(wcpncpy, null) {
  ASSERT_EQ((wchar_t *)12, ouma_wcpncpy((wchar_t *)12, (wchar_t *)500, 0));
}

TEST(wcpncpy, example1) {
  wchar_t buf[] = L"AAAAAAAAAAAA";
  ASSERT_EQ(buf + 5, ouma_wcpncpy(buf, L"Hello", 12));
  ASSERT_THAT(buf, testing::ElementsAreArray(L"Hello\0\0\0\0\0\0\0"));
}

TEST(wcpncpy, example2) {
  wchar_t buf[13];
  ASSERT_EQ(buf + 12, ouma_wcpncpy(buf, L"This is a very long string", 12));
  buf[12] = '\0';
  ASSERT_THAT(buf, testing::ElementsAreArray(L"This is a ve"));
}

TEST(wcpcpy, example) {
  wchar_t buf[] = L"AAAAAAAAAA";
  ASSERT_EQ(buf, ouma_wcpcpy(buf, L""));
  ASSERT_THAT(buf, testing::ElementsAreArray(L"\0AAAAAAAAA"));
  ASSERT_EQ(buf + 5, ouma_wcpcpy(buf, L"Hello"));
  ASSERT_THAT(buf, testing::ElementsAreArray(L"Hello\0AAAA"));
  ASSERT_EQ(buf, ouma_wcpcpy(buf, L""));
  ASSERT_THAT(buf, testing::ElementsAreArray(L"\0ello\0AAAA"));
  ASSERT_EQ(buf + 9, ouma_wcpcpy(buf, L"Example!!"));
  ASSERT_THAT(buf, testing::ElementsAreArray(L"Example!!\0"));
}

TEST(wcsncat, example) {
  wchar_t buf[11] = L"\0AAAAAAAAA";
  ASSERT_EQ(buf, ouma_wcsncat(buf, L"", 0));
  ASSERT_THAT(buf, testing::ElementsAreArray(L"\0AAAAAAAAA"));
  ASSERT_EQ(buf, ouma_wcsncat(buf, L"Hello", 99999));
  ASSERT_THAT(buf, testing::ElementsAreArray(L"Hello\0AAAA"));
  ASSERT_EQ(buf, ouma_wcsncat(buf, L"", 1));
  ASSERT_THAT(buf, testing::ElementsAreArray(L"Hello\0AAAA"));
  ASSERT_EQ(buf, ouma_wcsncat(buf, L"!!!!!!!!!!!!", 3));
  ASSERT_THAT(buf, testing::ElementsAreArray(L"Hello!!!\0A"));
}

TEST(wcscat, example) {
  wchar_t buf[] = L"\0AAAAAAAAA";
  ASSERT_EQ(buf, ouma_wcscat(buf, L""));
  ASSERT_THAT(buf, testing::ElementsAreArray(L"\0AAAAAAAAA"));
  ASSERT_EQ(buf, ouma_wcscat(buf, L"Hello"));
  ASSERT_THAT(buf, testing::ElementsAreArray(L"Hello\0AAAA"));
  ASSERT_EQ(buf, ouma_wcscat(buf, L""));
  ASSERT_THAT(buf, testing::ElementsAreArray(L"Hello\0AAAA"));
  ASSERT_EQ(buf, ouma_wcscat(buf, L"!!!!"));
  ASSERT_THAT(buf, testing::ElementsAreArray(L"Hello!!!!\0"));
}

TEST(wcsncpy, null) {
  ASSERT_EQ((wchar_t *)12, ouma_wcsncpy((wchar_t *)12, (wchar_t *)500, 0));
}

TEST(wcsncpy, example1) {
  wchar_t buf[] = L"AAAAAAAAAAAA";
  ASSERT_EQ(buf, ouma_wcsncpy(buf, L"Hello", 12));
  ASSERT_THAT(buf, testing::ElementsAreArray(L"Hello\0\0\0\0\0\0\0"));
}

TEST(wcsncpy, example2) {
  wchar_t buf[13];
  ASSERT_EQ(buf, ouma_wcsncpy(buf, L"This is a very long string", 12));
  buf[12] = L'\0';
  ASSERT_THAT(buf, testing::ElementsAreArray(L"This is a ve"));
}

TEST(wcscpy, example) {
  wchar_t buf[] = L"AAAAAAAAAA";
  ASSERT_EQ(buf, ouma_wcscpy(buf, L""));
  ASSERT_THAT(buf, testing::ElementsAreArray(L"\0AAAAAAAAA"));
  ASSERT_EQ(buf, ouma_wcscpy(buf, L"Hello"));
  ASSERT_THAT(buf, testing::ElementsAreArray(L"Hello\0AAAA"));
  ASSERT_EQ(buf, ouma_wcscpy(buf, L""));
  ASSERT_THAT(buf, testing::ElementsAreArray(L"\0ello\0AAAA"));
  ASSERT_EQ(buf, ouma_wcscpy(buf, L"Example!!"));
  ASSERT_THAT(buf, testing::ElementsAreArray(L"Example!!\0"));
}

TEST(wcsncmp, null) {
  ASSERT_EQ(0, ouma_wcsncmp(NULL, NULL, 0));
}

TEST(wcsncmp, examples) {
  ASSERT_EQ(0, ouma_wcsncmp(L"", L"", 100));
  ASSERT_EQ(0, ouma_wcsncmp(L"Hello", L"Hello", 100));

  ASSERT_EQ(0, ouma_wcsncmp(L"Hello", L"Hello, world", 5));
  ASSERT_GT(0, ouma_wcsncmp(L"Hello", L"Hello, world", 6));
  ASSERT_LT(0, ouma_wcsncmp(L"Hello, world", L"Hello", 100));

  ASSERT_EQ(0, ouma_wcsncmp(L"Hello!", L"Hello.", 5));
  ASSERT_GT(0, ouma_wcsncmp(L"Hello!", L"Hello.", 6));
  ASSERT_LT(0, ouma_wcsncmp(L"Hello.", L"Hello!", 100));
}

TEST(wcsnlen, null) {
  ASSERT_EQ(0, ouma_wcsnlen(NULL, 0));
  ASSERT_EQ(0, ouma_wcsnlen(L"", 100));
  ASSERT_EQ(7, ouma_wcsnlen(L"Σὲ γνωρίζω ἀπὸ τὴν κόψη", 7));
}

TEST(wcslen, example) {
  ASSERT_EQ(22, ouma_wcslen(L"ℕ ⊆ ℕ₀ ⊂ ℤ ⊂ ℚ ⊂ ℝ ⊂ ℂ"));
}

TEST(wcscspn, example) {
  const wchar_t *wcs = L"Hello, world";
  ASSERT_EQ(0, ouma_wcscspn(wcs, L"H"));
  ASSERT_EQ(7, ouma_wcscspn(wcs, L"rdw"));
  ASSERT_EQ(12, ouma_wcscspn(wcs, L"XYZ"));
}

TEST(wcsspn, example) {
  const wchar_t *wcs = L"Hello, world";
  ASSERT_EQ(0, ouma_wcsspn(wcs, L""));
  ASSERT_EQ(0, ouma_wcsspn(wcs, L"Foo"));
  ASSERT_EQ(5, ouma_wcsspn(wcs, L"olHe"));
  ASSERT_EQ(12, ouma_wcsspn(wcs, L"Helo, wrld"));
}

TEST(wcspbrk, example) {
  const wchar_t *wcs = L"Hello, world";
  ASSERT_EQ(wcs, ouma_wcspbrk(wcs, L"H"));
  ASSERT_EQ(wcs + 7, ouma_wcspbrk(wcs, L"rdw"));
  ASSERT_EQ(NULL, ouma_wcspbrk(wcs, L"XYZ"));
}


TEST(wcsstr, examples) {
  const wchar_t *str = (const wchar_t *)0x42;
  ASSERT_EQ(str, ouma_wcsstr(str, L""));

  str = L"Hello world";
  ASSERT_EQ(str + 2, ouma_wcsstr(str, L"ll"));
  ASSERT_EQ(str + 4, ouma_wcsstr(str, L"o worl"));
  ASSERT_EQ(str + 6, ouma_wcsstr(str, L"world"));
  ASSERT_EQ(str + 10, ouma_wcsstr(str, L"d"));
  ASSERT_EQ(NULL, ouma_wcsstr(str, L"word"));
  ASSERT_EQ(NULL, ouma_wcsstr(str, L"world!"));
}


TEST(wcstok, example) {
  wchar_t line[] = L"LINE  TO BE\t\tSEPARATED\n";
  const wchar_t *split = L" \t\n";
  wchar_t *lastws;
  ASSERT_STREQ(L"LINE", ouma_wcstok(line, split, &lastws));
  ASSERT_STREQ(L"TO", ouma_wcstok(NULL, split, &lastws));
  ASSERT_STREQ(L"BE", ouma_wcstok(NULL, split, &lastws));
  ASSERT_STREQ(L"SEPARATED", ouma_wcstok(NULL, split, &lastws));
  ASSERT_EQ(NULL, ouma_wcstok(NULL, split, &lastws));
}

TEST(wcsdup, hello) {
  wchar_t *copy = ouma_wcsdup(L"Hello");
  ASSERT_STREQ(L"Hello", copy);
  free(copy);
}

TEST(wctob, example) {
  ASSERT_EQ(EOF, ouma_wctob(WEOF));

  for (wint_t i = 0; i < 128; ++i) {
    SCOPED_TRACE(i);
    ASSERT_EQ(i, ouma_wctob(i));
  }
  for (wint_t i = 128; i < 1000; ++i) {
    SCOPED_TRACE(i);
    ASSERT_EQ(EOF, ouma_wctob(i));
  }
}

TEST(mbsinit, init) {
  ASSERT_NE(0, ouma_mbsinit(NULL));
  ouma_mbstate_t initial_mbstate{};
  ASSERT_NE(0, ouma_mbsinit(&initial_mbstate));
}

#ifndef UNICODE
TEST(mbrtowc, ascii) {
  ouma_mbstate_t mbs{};
  wchar_t wc;

  // Valid character.
  ASSERT_EQ(1, ouma_mbrtowc(&wc, "Foo", 3, &mbs));
  ASSERT_EQ(U'F', wc);
  ASSERT_NE(0, ouma_mbsinit(&mbs));

  // Null character.
  ASSERT_EQ(0, ouma_mbrtowc(&wc, "", 1, &mbs));
  ASSERT_EQ(U'\0', wc);
  ASSERT_NE(0, ouma_mbsinit(&mbs));

  // Buffer too short.
  ASSERT_EQ((size_t)-2, ouma_mbrtowc(&wc, "Some text", 0, &mbs));
  ASSERT_NE(0, ouma_mbsinit(&mbs));

  // Invalid character.
  ASSERT_EQ((size_t)-1, ouma_mbrtowc(&wc, "€", 4, &mbs));
  ASSERT_NE(0, ouma_mbsinit(&mbs));
}
#endif

#ifdef UNICODE
TEST(mbrtowc, unicode) {
  ouma_mbstate_t mbs{};
  wchar_t wc;

  // Valid character.
  ASSERT_EQ(1, ouma_mbrtowc(&wc, "Foo", 3, &mbs));
  ASSERT_EQ(U'F', wc);
  ASSERT_NE(0, ouma_mbsinit(&mbs));

  // Piecewise consume an Unicode character.
  ASSERT_EQ((size_t)-2,
            ouma_mbrtowc(&wc, "\xf0\x90", 2, &mbs));
  ASSERT_EQ(0, ouma_mbsinit(&mbs));
  ASSERT_EQ((size_t)-2, ouma_mbrtowc(&wc, "\x90", 1, &mbs));
  ASSERT_EQ(0, ouma_mbsinit(&mbs));
  ASSERT_EQ(1, ouma_mbrtowc(&wc, "\xb7", 1, &mbs));
  ASSERT_EQ(U'𐐷', wc);
  ASSERT_NE(0, ouma_mbsinit(&mbs));

  // Null character.
  ASSERT_EQ(0, ouma_mbrtowc(&wc, "", 1, &mbs));
  ASSERT_EQ(U'\0', wc);
  ASSERT_NE(0, ouma_mbsinit(&mbs));

  // Buffer too short.
  ASSERT_EQ((size_t)-2,
            ouma_mbrtowc(&wc, "Some text", 0, &mbs));
  ASSERT_NE(0, ouma_mbsinit(&mbs));
}
#endif

static void test_mbsrtowcs(ouma_mbstate_t* ps) {
  constexpr const char* VALID = "A" "\xc2\xa2" "\xe2\x82\xac" "\xf0\xa4\xad\xa2" "ef";
  constexpr const char* INVALID = "A" "\xc2\x20" "ef";
  constexpr const char* INCOMPLETE = "A" "\xc2";
  wchar_t out[4];
  const char* valid = VALID;
  ASSERT_EQ(4U, ouma_mbsrtowcs(out, &valid, 4, ps));
  ASSERT_EQ(L'A', out[0]);
  ASSERT_EQ(static_cast<wchar_t>(0x00a2), out[1]);
  ASSERT_EQ(static_cast<wchar_t>(0x20ac), out[2]);
  ASSERT_EQ(static_cast<wchar_t>(0x24b62), out[3]);
  ASSERT_EQ('e', *valid);
  wmemset(out, L'x', NUM_WCHARS(sizeof(out)));
  ASSERT_EQ(2U, ouma_mbsrtowcs(out, &valid, 4, ps));
  ASSERT_EQ(L'e', out[0]);
  ASSERT_EQ(L'f', out[1]);
  ASSERT_EQ(L'\0', out[2]);
  ASSERT_EQ(L'x', out[3]);
  ASSERT_EQ(nullptr, valid);
  const char* invalid = INVALID;
  ASSERT_EQ(static_cast<size_t>(-1), ouma_mbsrtowcs(out, &invalid, 4, ps));
  EXPECT_EQ(EILSEQ, __oumalibc_errno);
  ASSERT_EQ('\xc2', *invalid);
  const char* incomplete = INCOMPLETE;
  ASSERT_EQ(static_cast<size_t>(-1), ouma_mbsrtowcs(out, &incomplete, 2, ps));
  EXPECT_EQ(EILSEQ, __oumalibc_errno);
  ASSERT_EQ('\xc2', *incomplete);
  // If dst is null, *src shouldn't be updated.
  const char* mbs = VALID;
  EXPECT_EQ(6U, ouma_mbsrtowcs(nullptr, &mbs, 0, ps));
  EXPECT_EQ(VALID, mbs);
  mbs = INVALID;
  EXPECT_EQ(static_cast<size_t>(-1), ouma_mbsrtowcs(nullptr, &mbs, 0, ps));
  EXPECT_EQ(INVALID, mbs);
  mbs = INCOMPLETE;
  EXPECT_EQ(static_cast<size_t>(-1), ouma_mbsrtowcs(nullptr, &mbs, 0, ps));
  EXPECT_EQ(INCOMPLETE, mbs);
}

TEST(mbsrtowcs, example) {
  ouma_mbstate_t ps;
  memset(&ps, 0, sizeof(ps));
  test_mbsrtowcs(&ps);
  test_mbsrtowcs(nullptr);
  const char* invalid = "\x20";
  wchar_t out;
  ASSERT_EQ(static_cast<size_t>(-2), ouma_mbrtowc(&out, "\xc2", 1, &ps));
  ASSERT_EQ(static_cast<size_t>(-1), ouma_mbsrtowcs(&out, &invalid, 1, &ps));
  EXPECT_EQ(EILSEQ, __oumalibc_errno);
  ASSERT_EQ('\x20', *invalid);
}

#ifndef UNICODE
TEST(wcrtomb, ascii) {
  char c;

  // Valid characters.
  ASSERT_EQ(1, ouma_wcrtomb(&c, U'A', NULL));
  ASSERT_EQ('A', c);
  ASSERT_EQ(1, ouma_wcrtomb(&c, U'\0', NULL));
  ASSERT_EQ('\0', c);

  // Characters cannot be expressed as ASCII.
  ASSERT_EQ((size_t)-1, ouma_wcrtomb(&c, U'€', NULL));
  ASSERT_EQ(EILSEQ, __oumalibc_errno);

  // Surrogate pair. Should not be allowed.
  ASSERT_EQ((size_t)-1, ouma_wcrtomb(&c, 0xd801, NULL));
  ASSERT_EQ(EILSEQ, __oumalibc_errno);
}

TEST(wcsrtombs, ascii_ok) {
  // String should be fully converted.
  const wchar_t *src = L"Hello, world";
  char dst[13];
  ouma_mbstate_t mbs{};
  ASSERT_EQ(sizeof(dst) - 1, ouma_wcsrtombs(dst, &src, sizeof(dst), &mbs));
  ASSERT_EQ(NULL, src);
  ASSERT_STREQ("Hello, world", dst);
}

TEST(wcsrtombs, ascii_bad_rightbefore) {
  // Conversion should stop right before the illegal character.
  const wchar_t *src = L"Hello, wørld";
  char dst[9];
  ouma_mbstate_t mbs{};
  ASSERT_EQ(sizeof(dst) - 1, ouma_wcsrtombs(dst, &src, sizeof(dst) - 1, &mbs));
  ASSERT_STREQ(L"ørld", src);
  dst[8] = '\0';
  ASSERT_STREQ("Hello, w", dst);
}

TEST(wcsrtombs, ascii_bad) {
  // Conversion should stop due to the illegal character.
  const wchar_t *src = L"Hello, wørld";
  char dst[9];
  ouma_mbstate_t mbs{};
  ASSERT_EQ((size_t)-1, ouma_wcsrtombs(dst, &src, sizeof(dst), &mbs));
  ASSERT_EQ(EILSEQ, __oumalibc_errno);
  ASSERT_STREQ(L"ørld", src);
}

TEST(wcsrtombs, ascii_null_ok) {
  // Length should be computed. Source should be left unmodified.
  const wchar_t *src = L"Hello, world";
  ouma_mbstate_t mbs{};
  ASSERT_EQ(12, ouma_wcsrtombs(NULL, &src, 0, &mbs));
  ASSERT_STREQ(L"Hello, world", src);
}

TEST(wcsrtombs, ascii_null_bad) {
  // Length cannot be computed. Source should be left unmodified.
  const wchar_t *src = L"Hello, wørld";
  ouma_mbstate_t mbs{};
  ASSERT_EQ((size_t)-1, ouma_wcsrtombs(NULL, &src, 0, &mbs));
  ASSERT_STREQ(L"Hello, wørld", src);
}
#endif

#ifdef UNICODE
TEST(wcrtomb, unicode) {
  char buf[MB_LEN_MAX];

  // Valid characters.
  ASSERT_EQ(1, ouma_wcrtomb(buf, U'A', NULL));
  ASSERT_EQ('A', buf[0]);
  ASSERT_EQ(1, ouma_wcrtomb(buf, U'\0', NULL));
  ASSERT_EQ('\0', buf[0]);
  ASSERT_EQ(3, ouma_wcrtomb(buf, U'€', NULL));
  ASSERT_THAT(buf, testing::StartsWith("€"));

  // Surrogate pair. Should not be allowed.
  ASSERT_EQ((size_t)-1, ouma_wcrtomb(buf, 0xd801, NULL));
  ASSERT_EQ(EILSEQ, __oumalibc_errno);
}

TEST(wcsrtombs, unicode) {
  // String should be fully converted.
  const wchar_t *src = L"ℕ ⊆ ℕ₀ ⊂ ℤ ⊂ ℚ ⊂ ℝ ⊂ ℂ";
  char dst[47];
  ouma_mbstate_t mbs{};
  ASSERT_EQ(sizeof(dst) - 1,
            ouma_wcsrtombs(dst, &src, sizeof(dst), &mbs));
  ASSERT_EQ(NULL, src);
  ASSERT_STREQ("ℕ ⊆ ℕ₀ ⊂ ℤ ⊂ ℚ ⊂ ℝ ⊂ ℂ", dst);
}

TEST(mbrlen, unicode) {
  // Parse all bytes of a Euro symbol separately.
  char euro[] = "€";
  ouma_mbstate_t mbs{};
  ASSERT_EQ((size_t)-2, ouma_mbrlen(&euro[0], 1, &mbs));
  ASSERT_EQ((size_t)-2, ouma_mbrlen(&euro[1], 1, &mbs));
  ASSERT_EQ(1, ouma_mbrlen(&euro[2], 1, &mbs));
  ASSERT_EQ(0, ouma_mbrlen(&euro[3], 1, &mbs));
}
#endif

TEST(btowc, example) {
  // EOF should map to WEOF.
  ASSERT_EQ(WEOF, ouma_btowc(EOF));
  // All lower codepoints should be mapped.
  for (int i = 0; i < 128; ++i) {
    SCOPED_TRACE(i);
    ASSERT_EQ(i, ouma_btowc(i));
  }
  // Everything above should throw WEOF.
  for (int i = 128; i < 256; ++i) {
    SCOPED_TRACE(i);
    ASSERT_EQ(WEOF, ouma_btowc(i));
  }
}

TEST(wcwidth, korean) {
  EXPECT_EQ(2, ouma_wcwidth(L'ㅜ'));
  EXPECT_EQ(2, ouma_wcwidth(L'ㅋ'));
}

TEST(wcwidth, korean_jeongeul_syllables) {
  EXPECT_EQ(2, ouma_wcwidth(0xac00));
  EXPECT_EQ(2, ouma_wcwidth(0xd7a3));
}

TEST(wcswidth, simple) {
  const wchar_t str[] = L"Iñtërnâtiônàlizætiøn";
  ASSERT_EQ(19, ouma_wcswidth(str, std::size(str) - 2));
  ASSERT_EQ(20, ouma_wcswidth(str, std::size(str) - 1));
  ASSERT_EQ(20, ouma_wcswidth(str, std::size(str)));
  ASSERT_EQ(20, ouma_wcswidth(str, std::size(str) + 1));
}

TEST(wcswidth, japanese) {
  const wchar_t str[] = L"コンニチハ";
  ASSERT_EQ(8, ouma_wcswidth(str, std::size(str) - 2));
  ASSERT_EQ(10, ouma_wcswidth(str, std::size(str) - 1));
  ASSERT_EQ(10, ouma_wcswidth(str, std::size(str)));
  ASSERT_EQ(10, ouma_wcswidth(str, std::size(str) + 1));
}

TEST(wcswidth, thai) {
  const wchar_t str[] = L"๏ แผ่นดินฮั่นเสื่อมโทรมแสนสังเวช";
  ASSERT_EQ(24, ouma_wcswidth(str, std::size(str) - 2));
  ASSERT_EQ(25, ouma_wcswidth(str, std::size(str) - 1));
  ASSERT_EQ(25, ouma_wcswidth(str, std::size(str)));
  ASSERT_EQ(25, ouma_wcswidth(str, std::size(str) + 1));
}

TEST(wcswidth, zalgo) {
  const wchar_t str[] = L"T̫̺̳o̬̜ ì̬͎̲̟nv̖̗̻̣̹̕o͖̗̠̜̤k͍͚̹͖̼e̦̗̪͍̪͍ ̬ͅt̕h̠͙̮͕͓e̱̜̗͙̭ ̥͔̫͙̪͍̣͝ḥi̼̦͈̼v҉̩̟͚̞͎e͈̟̻͙̦̤-m̷̘̝̱í͚̞̦̳n̝̲̯̙̮͞d̴̺̦͕̫ ̗̭̘͎͖r̞͎̜̜͖͎̫͢ep͇r̝̯̝͖͉͎̺e̴s̥e̵̖̳͉͍̩̗n̢͓̪͕̜̰̠̦t̺̞̰i͟n҉̮̦̖̟g̮͍̱̻͍̜̳ ̳c̖̮̙̣̰̠̩h̷̗͍̖͙̭͇͈a̧͎̯̹̲̺̫ó̭̞̜̣̯͕s̶̤̮̩̘.̨̻̪̖͔";
  ASSERT_EQ(43, ouma_wcswidth(str, std::size(str)));
}
