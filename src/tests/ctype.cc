#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <locale.h>

extern "C" {
  struct LocaleCtype {
    const char *codeset;
    ssize_t (*mbtoc32)(char32_t*, const char*, size_t, mbstate_t*);
    ssize_t (*c32tomb)(char*, char32_t, mbstate_t*);
    int mb_cur_max;
  };

  struct LocaleStruct {
    LocaleCtype ctype;
  };

  typedef struct LocaleStruct *ouma_locale_t;

  int ouma_isalnum(int);
  int ouma_isalnum_l(int, ouma_locale_t);
  int ouma_isalpha(int);
  int ouma_isalpha_l(int, ouma_locale_t);
  int ouma_isascii(int);
  int ouma_isblank(int);
  int ouma_isblank_l(int, ouma_locale_t);
  int ouma_iscntrl(int);
  int ouma_iscntrl_l(int, ouma_locale_t);
  int ouma_isdigit(int);
  int ouma_isdigit_l(int, ouma_locale_t);
  int ouma_isgraph(int);
  int ouma_isgraph_l(int, ouma_locale_t);
  int ouma_islower(int);
  int ouma_islower_l(int, ouma_locale_t);
  int ouma_isprint(int);
  int ouma_isprint_l(int, ouma_locale_t);
  int ouma_ispunct(int);
  int ouma_ispunct_l(int, ouma_locale_t);
  int ouma_isspace(int);
  int ouma_isspace_l(int, ouma_locale_t);
  int ouma_isupper(int);
  int ouma_isupper_l(int, ouma_locale_t);
  int ouma_isxdigit(int);
  int ouma_isxdigit_l(int, ouma_locale_t);
  int ouma_toascii(int);
  int ouma_tolower(int);
  int ouma_tolower_l(int, ouma_locale_t);
  int ouma_toupper(int);
  int ouma_toupper_l(int, ouma_locale_t);
  int ouma_iswalnum(wint_t);
  int ouma_iswalpha(wint_t);
  int ouma_iswblank(wint_t);
  int ouma_iswcntrl(wint_t);
  int ouma_iswdigit(wint_t);
  int ouma_iswgraph(wint_t);
  int ouma_iswlower(wint_t);
  int ouma_iswprint(wint_t);
  int ouma_iswpunct(wint_t);
  int ouma_iswspace(wint_t);
  int ouma_iswupper(wint_t);
  int ouma_iswxdigit(wint_t);

  void ouma_freelocale(ouma_locale_t);
  ouma_locale_t ouma_newlocale(int, const char *, ouma_locale_t);
}

TEST(ctype, eof) {
  ASSERT_EQ(0, ouma_isalnum(EOF));
  ASSERT_EQ(0, ouma_isalpha(EOF));
  ASSERT_FALSE(ouma_isascii(EOF));
  ASSERT_EQ(0, ouma_isblank(EOF));
  ASSERT_EQ(0, ouma_iscntrl(EOF));
  ASSERT_EQ(0, ouma_isdigit(EOF));
  ASSERT_EQ(0, ouma_isgraph(EOF));
  ASSERT_EQ(0, ouma_islower(EOF));
  ASSERT_EQ(0, ouma_isprint(EOF));
  ASSERT_EQ(0, ouma_ispunct(EOF));
  ASSERT_EQ(0, ouma_isspace(EOF));
  ASSERT_EQ(0, ouma_isupper(EOF));
  ASSERT_EQ(0, ouma_isxdigit(EOF));
  ASSERT_EQ(EOF, ouma_tolower(EOF));
  ASSERT_EQ(EOF, ouma_toupper(EOF));
}

TEST(ctype, ascii_to_wchar) {
  for (int ch = 0; ch <= 127; ++ch) {
    SCOPED_TRACE(ch);

    ASSERT_EQ(ouma_iswalnum(ch), ouma_isalnum(ch));
    ASSERT_EQ(ouma_iswalpha(ch), ouma_isalpha(ch));
    ASSERT_TRUE(ouma_isascii(ch));
    ASSERT_EQ(ouma_iswblank(ch), ouma_isblank(ch));
    ASSERT_EQ(ouma_iswcntrl(ch), ouma_iscntrl(ch));
    ASSERT_EQ(ouma_iswdigit(ch), ouma_isdigit(ch));
    ASSERT_EQ(ouma_iswgraph(ch), ouma_isgraph(ch));
    ASSERT_EQ(ouma_iswlower(ch), ouma_islower(ch));
    ASSERT_EQ(ouma_iswprint(ch), ouma_isprint(ch));
    ASSERT_EQ(ouma_iswpunct(ch), ouma_ispunct(ch));
    ASSERT_EQ(ouma_iswspace(ch), ouma_isspace(ch));
    ASSERT_EQ(ouma_iswupper(ch), ouma_isupper(ch));
    ASSERT_EQ(ouma_iswxdigit(ch), ouma_isxdigit(ch));
    ASSERT_EQ(towlower(ch), ouma_tolower(ch));
    ASSERT_EQ(towupper(ch), ouma_toupper(ch));
  }

  for (int ch = 128; ch <= 255; ++ch) {
    SCOPED_TRACE(ch);

    ASSERT_EQ(0, ouma_isalnum(ch));
    ASSERT_EQ(0, ouma_isalpha(ch));
    ASSERT_FALSE(ouma_isascii(ch));
    ASSERT_EQ(0, ouma_isblank(ch));
    ASSERT_EQ(0, ouma_iscntrl(ch));
    ASSERT_EQ(0, ouma_isdigit(ch));
    ASSERT_EQ(0, ouma_isgraph(ch));
    ASSERT_EQ(0, ouma_islower(ch));
    ASSERT_EQ(0, ouma_isprint(ch));
    ASSERT_EQ(0, ouma_ispunct(ch));
    ASSERT_EQ(0, ouma_isspace(ch));
    ASSERT_EQ(0, ouma_isupper(ch));
    ASSERT_EQ(0, ouma_isxdigit(ch));
    ASSERT_EQ(ch, ouma_tolower(ch));
    ASSERT_EQ(ch, ouma_toupper(ch));
  }
}
