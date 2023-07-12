#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <uchar.h>
#include <wchar.h>
#include <errno.h>
#include <stdlib.h>

extern "C" {
  typedef struct {
    char16_t __surrogate;
    unsigned int __bytesleft;
    char32_t __partial;
    char32_t __lowerbound;
  } __ouma_mbstate_t;
  typedef __ouma_mbstate_t ouma_mbstate_t;

  size_t ouma_c16rtomb(char *__restrict, char16_t, ouma_mbstate_t *__restrict);
  size_t ouma_c32rtomb(char *__restrict, char32_t, ouma_mbstate_t *__restrict);
  size_t ouma_mbrtoc16(char16_t *__restrict, const char *__restrict, size_t, ouma_mbstate_t *__restrict);
  size_t ouma_mbrtoc32(char32_t *__restrict, const char *__restrict, size_t, ouma_mbstate_t *__restrict);
  int ouma_mbsinit(const ouma_mbstate_t *);

  extern thread_local int __oumalibc_errno;
}

#ifdef UNICODE

TEST(c16rtomb, unicode) {
  char buf[MB_LEN_MAX];
  ouma_mbstate_t mbs{};
  ASSERT_EQ(1, ouma_c16rtomb(buf, u'A', &mbs));
  ASSERT_EQ('A', buf[0]);
  ASSERT_NE(0, ouma_mbsinit(&mbs));
  ASSERT_EQ(1, ouma_c16rtomb(buf, u'\0', &mbs));
  ASSERT_EQ('\0', buf[0]);
  ASSERT_NE(0, ouma_mbsinit(&mbs));
  ASSERT_EQ(3, ouma_c16rtomb(buf, u'€', &mbs));
  ASSERT_THAT(buf, testing::StartsWith("€"));
  ASSERT_NE(0, ouma_mbsinit(&mbs));
  ASSERT_EQ(0, ouma_c16rtomb(buf, 0xd801, &mbs));
  ASSERT_EQ(0, ouma_mbsinit(&mbs));
  ASSERT_EQ(4, ouma_c16rtomb(buf, 0xdc37, &mbs));
  ASSERT_THAT(buf, testing::StartsWith("𐐷"));
  ASSERT_NE(0, ouma_mbsinit(&mbs));
}

TEST(c32rtomb, unicode) {
  char buf[MB_LEN_MAX];
  ASSERT_EQ(1, ouma_c32rtomb(buf, U'A', NULL));
  ASSERT_EQ('A', buf[0]);
  ASSERT_EQ(1, ouma_c32rtomb(buf, U'\0', NULL));
  ASSERT_EQ('\0', buf[0]);
  ASSERT_EQ(3, ouma_c32rtomb(buf, U'€', NULL));
  ASSERT_THAT(buf, testing::StartsWith("€"));
  ASSERT_EQ((size_t)-1, ouma_c32rtomb(buf, 0xd801, NULL));
  ASSERT_EQ(EILSEQ, __oumalibc_errno);
}

TEST(mbrtoc16, unicode) {
  ouma_mbstate_t mbs{};
  char16_t c16;
  ASSERT_EQ(1, ouma_mbrtoc16(&c16, "Foo", 3, &mbs));
  ASSERT_EQ(u'F', c16);
  ASSERT_NE(0, ouma_mbsinit(&mbs));
  ASSERT_EQ((size_t)-2,
            ouma_mbrtoc16(&c16, "\xf0\x90", 2, &mbs));
  ASSERT_EQ(0, ouma_mbsinit(&mbs));
  ASSERT_EQ((size_t)-2, ouma_mbrtoc16(&c16, "\x90", 1, &mbs));
  ASSERT_EQ(0, ouma_mbsinit(&mbs));
  ASSERT_EQ(1, ouma_mbrtoc16(&c16, "\xb7", 1, &mbs));
  ASSERT_EQ(0xd801, c16);
  ASSERT_EQ(0, ouma_mbsinit(&mbs));
  ASSERT_EQ((size_t)-3, ouma_mbrtoc16(&c16, "AAA", 3, &mbs));
  ASSERT_EQ(0xdc37, c16);
  ASSERT_NE(0, ouma_mbsinit(&mbs));
  ASSERT_EQ(0, ouma_mbrtoc16(&c16, "", 1, &mbs));
  ASSERT_EQ(u'\0', c16);
  ASSERT_NE(0, ouma_mbsinit(&mbs));
  ASSERT_EQ((size_t)-2,
            ouma_mbrtoc16(&c16, "Some text", 0, &mbs));
  ASSERT_NE(0, ouma_mbsinit(&mbs));
}

TEST(mbrtoc32, unicode) {
  ouma_mbstate_t mbs{};
  char32_t c32;
  ASSERT_EQ(1, ouma_mbrtoc32(&c32, "Foo", 3, &mbs));
  ASSERT_EQ(U'F', c32);
  ASSERT_NE(0, ouma_mbsinit(&mbs));
  ASSERT_EQ((size_t)-2,
            ouma_mbrtoc32(&c32, "\xf0\x90", 2, &mbs));
  ASSERT_EQ(0, ouma_mbsinit(&mbs));
  ASSERT_EQ((size_t)-2, ouma_mbrtoc32(&c32, "\x90", 1, &mbs));
  ASSERT_EQ(0, ouma_mbsinit(&mbs));
  ASSERT_EQ(1, ouma_mbrtoc32(&c32, "\xb7", 1, &mbs));
  ASSERT_EQ(U'𐐷', c32);
  ASSERT_NE(0, ouma_mbsinit(&mbs));
  ASSERT_EQ(0, ouma_mbrtoc32(&c32, "", 1, &mbs));
  ASSERT_EQ(U'\0', c32);
  ASSERT_NE(0, ouma_mbsinit(&mbs));
  ASSERT_EQ((size_t)-2,
            ouma_mbrtoc32(&c32, "Some text", 0, &mbs));
  ASSERT_NE(0, ouma_mbsinit(&mbs));
}

#else

TEST(c16rtomb, ascii) {
  char c;
  ouma_mbstate_t mbs{};
  ASSERT_EQ(1, ouma_c16rtomb(&c, u'A', &mbs));
  ASSERT_EQ('A', c);
  ASSERT_NE(0, ouma_mbsinit(&mbs));
  ASSERT_EQ(1, ouma_c16rtomb(&c, u'\0', &mbs));
  ASSERT_EQ('\0', c);
  ASSERT_NE(0, ouma_mbsinit(&mbs));
  ASSERT_EQ((size_t)-1, ouma_c16rtomb(&c, u'€', &mbs));
  ASSERT_EQ(EILSEQ, __oumalibc_errno);
  ASSERT_NE(0, ouma_mbsinit(&mbs));
  ASSERT_EQ(0, ouma_c16rtomb(&c, 0xd801, &mbs));
  ASSERT_EQ(0, ouma_mbsinit(&mbs));
  ASSERT_EQ((size_t)-1, ouma_c16rtomb(&c, 0xdc37, &mbs));
  ASSERT_EQ(EILSEQ, __oumalibc_errno);
  ASSERT_EQ(0, ouma_mbsinit(&mbs));
}

TEST(c32rtomb, ascii) {
  char c;
  ASSERT_EQ(1, ouma_c32rtomb(&c, U'A', NULL));
  ASSERT_EQ('A', c);
  ASSERT_EQ(1, ouma_c32rtomb(&c, U'\0', NULL));
  ASSERT_EQ('\0', c);
  ASSERT_EQ((size_t)-1, ouma_c32rtomb(&c, U'€', NULL));
  ASSERT_EQ(EILSEQ, __oumalibc_errno);
  ASSERT_EQ((size_t)-1, ouma_c32rtomb(&c, 0xd801, NULL));
  ASSERT_EQ(EILSEQ, __oumalibc_errno);
}

TEST(mbrtoc16, ascii) {
  ouma_mbstate_t mbs{};
  char16_t c16;
  ASSERT_EQ(1, ouma_mbrtoc16(&c16, "Foo", 3, &mbs));
  ASSERT_EQ(u'F', c16);
  ASSERT_NE(0, ouma_mbsinit(&mbs));
  ASSERT_EQ((size_t)-2, ouma_mbrtoc16(&c16, "Some text", 0, &mbs));
  ASSERT_NE(0, ouma_mbsinit(&mbs));
  ASSERT_EQ((size_t)-1, ouma_mbrtoc16(&c16, "€", 4, &mbs));
  ASSERT_EQ(EILSEQ, __oumalibc_errno);
  ASSERT_NE(0, ouma_mbsinit(&mbs));
}

TEST(mbrtoc32, ascii) {
  ouma_mbstate_t mbs{};
  char32_t c32;
  ASSERT_EQ(1, ouma_mbrtoc32(&c32, "Foo", 3, &mbs));
  ASSERT_EQ(U'F', c32);
  ASSERT_NE(0, ouma_mbsinit(&mbs));
  ASSERT_EQ(0, ouma_mbrtoc32(&c32, "", 1, &mbs));
  ASSERT_EQ(U'\0', c32);
  ASSERT_NE(0, ouma_mbsinit(&mbs));
  ASSERT_EQ((size_t)-2, ouma_mbrtoc32(&c32, "Some text", 0, &mbs));
  ASSERT_NE(0, ouma_mbsinit(&mbs));
  ASSERT_EQ((size_t)-1, ouma_mbrtoc32(&c32, "€", 4, &mbs));
  ASSERT_EQ(EILSEQ, __oumalibc_errno);
  ASSERT_NE(0, ouma_mbsinit(&mbs));
}

#endif
