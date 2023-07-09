#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <wctype.h>
#include <locale.h>

extern "C" {
  struct LocaleCtype {
    ssize_t (*mbtoc32)(char32_t*, const char*, size_t, mbstate_t*);
    ssize_t (*c32tomb)(char*, char32_t, mbstate_t*);
    int mb_cur_max;
  };

  struct LocaleStruct {
    LocaleCtype ctype;
  };

  typedef struct LocaleStruct *ouma_locale_t;

  int ouma_iswalnum(wint_t);
  int ouma_iswalnum_l(wint_t, ouma_locale_t);
  int ouma_iswalpha(wint_t);
  int ouma_iswalpha_l(wint_t, ouma_locale_t);
  int ouma_iswblank(wint_t);
  int ouma_iswblank_l(wint_t, ouma_locale_t);
  int ouma_iswcntrl(wint_t);
  int ouma_iswcntrl_l(wint_t, ouma_locale_t);
  int ouma_iswdigit(wint_t);
  int ouma_iswdigit_l(wint_t, ouma_locale_t);
  int ouma_iswgraph(wint_t);
  int ouma_iswgraph_l(wint_t, ouma_locale_t);
  int ouma_iswlower(wint_t);
  int ouma_iswlower_l(wint_t, ouma_locale_t);
  int ouma_iswprint(wint_t);
  int ouma_iswprint_l(wint_t, ouma_locale_t);
  int ouma_iswpunct(wint_t);
  int ouma_iswpunct_l(wint_t, ouma_locale_t);
  int ouma_iswspace(wint_t);
  int ouma_iswspace_l(wint_t, ouma_locale_t);
  int ouma_iswupper(wint_t);
  int ouma_iswupper_l(wint_t, ouma_locale_t);
  int ouma_iswxdigit(wint_t);
  int ouma_iswxdigit_l(wint_t, ouma_locale_t);
  wint_t ouma_towlower(wint_t);
  wint_t ouma_towlower_l(wint_t, ouma_locale_t);
  wint_t ouma_towupper(wint_t);
  wint_t ouma_towupper_l(wint_t, ouma_locale_t);
  int ouma_iswctype(wint_t, wctype_t);
  int ouma_iswctype_l(wint_t, wctype_t, ouma_locale_t);
  wctrans_t ouma_wctrans(const char *);
  wctrans_t ouma_wctrans_l(const char *, ouma_locale_t);
  wint_t ouma_towctrans(wint_t, wctrans_t);
  wint_t ouma_towctrans_l(wint_t, wctrans_t, ouma_locale_t);
  wctype_t ouma_wctype(const char *);
  wctype_t ouma_wctype_l(const char *, ouma_locale_t);

  void ouma_freelocale(ouma_locale_t);
  ouma_locale_t ouma_newlocale(int, const char *, ouma_locale_t);
}

TEST(iswalnum, examples) {
  ASSERT_FALSE(ouma_iswalnum(WEOF));

  ASSERT_TRUE(ouma_iswalnum(L'0'));
  ASSERT_TRUE(ouma_iswalnum(L'A'));
  ASSERT_TRUE(ouma_iswalnum(L'a'));
  ASSERT_TRUE(ouma_iswalnum(L'Å'));
  ASSERT_TRUE(ouma_iswalnum(L'Ω'));
  ASSERT_TRUE(ouma_iswalnum(L'д'));
  ASSERT_FALSE(ouma_iswalnum(L' '));
  ASSERT_FALSE(ouma_iswalnum(L'.'));
  ASSERT_FALSE(ouma_iswalnum(L'€'));
}

TEST(iswalpha, examples) {
  ASSERT_FALSE(ouma_iswalpha(WEOF));

  ASSERT_TRUE(ouma_iswalpha(L'A'));
  ASSERT_TRUE(ouma_iswalpha(L'a'));
  ASSERT_TRUE(ouma_iswalpha(L'Å'));
  ASSERT_TRUE(ouma_iswalpha(L'Ω'));
  ASSERT_TRUE(ouma_iswalpha(L'д'));
  ASSERT_FALSE(ouma_iswalpha(L'0'));
  ASSERT_FALSE(ouma_iswalpha(L' '));
  ASSERT_FALSE(ouma_iswalpha(L'.'));
  ASSERT_FALSE(ouma_iswalpha(L'€'));
}

TEST(iswblank, examples) {
  ASSERT_FALSE(ouma_iswblank(WEOF));
  ASSERT_TRUE(ouma_iswblank(L'\t'));
  ASSERT_TRUE(ouma_iswblank(L' '));
  ASSERT_TRUE(ouma_iswblank(L'\u2001'));
  ASSERT_FALSE(ouma_iswblank(L'\n'));
  ASSERT_FALSE(ouma_iswblank(L'\u00a0'));
  ASSERT_FALSE(ouma_iswblank(L'A'));
  ASSERT_FALSE(ouma_iswblank(L'.'));
  ASSERT_FALSE(ouma_iswblank(L'€'));
}

TEST(iswcntrl, examples) {
  ASSERT_FALSE(ouma_iswcntrl(WEOF));
  ASSERT_TRUE(ouma_iswcntrl(L'\0'));
  ASSERT_TRUE(ouma_iswcntrl(L'\n'));
  ASSERT_TRUE(ouma_iswcntrl(L'\t'));
  ASSERT_FALSE(ouma_iswcntrl(L'0'));
  ASSERT_FALSE(ouma_iswcntrl(L'A'));
  ASSERT_FALSE(ouma_iswcntrl(L' '));
  ASSERT_FALSE(ouma_iswcntrl(L'.'));
  ASSERT_FALSE(ouma_iswcntrl(L'€'));
}

TEST(iswctype, good) {
  wctype_t wt = ouma_wctype("upper");
  ASSERT_NE((wctype_t)0, wt);
  ASSERT_TRUE(ouma_iswctype('A', wt));
  ASSERT_FALSE(ouma_iswctype('a', wt));
}

TEST(iswctype, bad) {
  wctype_t wt = wctype("banana");
  ASSERT_EQ((wctype_t)0, wt);
  ASSERT_FALSE(ouma_iswctype('p', wt));
}

TEST(iswdigit, examples) {
  ASSERT_FALSE(ouma_iswdigit(WEOF));
  ASSERT_TRUE(ouma_iswdigit(L'0'));
  ASSERT_TRUE(ouma_iswdigit(L'1'));
  ASSERT_TRUE(ouma_iswdigit(L'2'));
  ASSERT_TRUE(ouma_iswdigit(L'3'));
  ASSERT_TRUE(ouma_iswdigit(L'4'));
  ASSERT_TRUE(ouma_iswdigit(L'5'));
  ASSERT_TRUE(ouma_iswdigit(L'6'));
  ASSERT_TRUE(ouma_iswdigit(L'7'));
  ASSERT_TRUE(ouma_iswdigit(L'8'));
  ASSERT_TRUE(ouma_iswdigit(L'9'));
  ASSERT_FALSE(ouma_iswdigit(L'A'));
  ASSERT_FALSE(ouma_iswdigit(L'①'));
  ASSERT_FALSE(ouma_iswdigit(L'?'));
}

TEST(iswgraph, examples) {
  ASSERT_FALSE(ouma_iswgraph(WEOF));
  ASSERT_TRUE(ouma_iswgraph(L'0'));
  ASSERT_TRUE(ouma_iswgraph(L'A'));
  ASSERT_TRUE(ouma_iswgraph(L'a'));
  ASSERT_TRUE(ouma_iswgraph(L'Å'));
  ASSERT_TRUE(ouma_iswgraph(L'Ω'));
  ASSERT_TRUE(ouma_iswgraph(L'д'));
  ASSERT_TRUE(ouma_iswgraph(L'.'));
  ASSERT_TRUE(ouma_iswgraph(L'€'));
  ASSERT_FALSE(ouma_iswgraph(L' '));
}

TEST(iswgraph, ascii) {
  ouma_locale_t locale = ouma_newlocale(LC_CTYPE_MASK, ".US-ASCII", 0);
  ASSERT_TRUE(ouma_iswgraph_l(L'0', locale));
  ASSERT_TRUE(ouma_iswgraph_l(L'A', locale));
  ASSERT_TRUE(ouma_iswgraph_l(L'a', locale));
  ASSERT_FALSE(ouma_iswgraph_l(L'Å', locale));
  ASSERT_FALSE(ouma_iswgraph_l(L'Ω', locale));
  ASSERT_FALSE(ouma_iswgraph_l(L'д', locale));
  ASSERT_TRUE(ouma_iswgraph_l(L'.', locale));
  ASSERT_FALSE(ouma_iswgraph_l(L'€', locale));
  ASSERT_FALSE(ouma_iswgraph_l(L' ', locale));
  ouma_freelocale(locale);
}

TEST(iswlower, equality) {
  for (wint_t wc = 0; wc <= 0x10ffff; ++wc) {
    SCOPED_TRACE(wc);
    ASSERT_EQ(wc != ouma_towupper(wc), ouma_iswlower(wc));
  }
}

TEST(iswprint, examples) {
  ASSERT_FALSE(ouma_iswprint(WEOF));
  ASSERT_TRUE(ouma_iswprint(L' '));
  ASSERT_TRUE(ouma_iswprint(L'\u2001'));
  ASSERT_TRUE(ouma_iswprint(L'\u00a0'));
  ASSERT_TRUE(ouma_iswprint(L'A'));
  ASSERT_TRUE(ouma_iswprint(L'.'));
  ASSERT_TRUE(ouma_iswprint(L'€'));
  ASSERT_FALSE(ouma_iswprint(L'\t'));
  ASSERT_FALSE(ouma_iswprint(L'\n'));
}

TEST(iswpunct, examples) {
  ASSERT_FALSE(ouma_iswpunct(WEOF));
  ASSERT_TRUE(ouma_iswpunct(L'\u00a0'));
  ASSERT_TRUE(ouma_iswpunct(L'.'));
  ASSERT_TRUE(ouma_iswpunct(L'€'));
  ASSERT_FALSE(ouma_iswpunct(L'A'));
  ASSERT_FALSE(ouma_iswpunct(L'\t'));
  ASSERT_FALSE(ouma_iswpunct(L' '));
  ASSERT_FALSE(ouma_iswpunct(L'\u2001'));
  ASSERT_FALSE(ouma_iswpunct(L'\n'));
}

TEST(iswspace, examples) {
  ASSERT_FALSE(ouma_iswspace(WEOF));
  ASSERT_TRUE(ouma_iswspace(L'\t'));
  ASSERT_TRUE(ouma_iswspace(L' '));
  ASSERT_TRUE(ouma_iswspace(L'\u2001'));
  ASSERT_TRUE(ouma_iswspace(L'\n'));
  ASSERT_FALSE(ouma_iswspace(L'\u00a0'));
  ASSERT_FALSE(ouma_iswspace(L'A'));
  ASSERT_FALSE(ouma_iswspace(L'.'));
  ASSERT_FALSE(ouma_iswspace(L'€'));
}

TEST(iswupper, equality) {
  for (wint_t wc = 0; wc <= 0x10ffff; ++wc) {
    SCOPED_TRACE(wc);
    ASSERT_EQ(wc != ouma_towlower(wc), ouma_iswupper(wc));
  }
}

TEST(iswxdigit, examples) {
  ASSERT_FALSE(ouma_iswalnum(WEOF));
  ASSERT_TRUE(ouma_iswxdigit(L'0'));
  ASSERT_TRUE(ouma_iswxdigit(L'1'));
  ASSERT_TRUE(ouma_iswxdigit(L'2'));
  ASSERT_TRUE(ouma_iswxdigit(L'3'));
  ASSERT_TRUE(ouma_iswxdigit(L'4'));
  ASSERT_TRUE(ouma_iswxdigit(L'5'));
  ASSERT_TRUE(ouma_iswxdigit(L'6'));
  ASSERT_TRUE(ouma_iswxdigit(L'7'));
  ASSERT_TRUE(ouma_iswxdigit(L'8'));
  ASSERT_TRUE(ouma_iswxdigit(L'9'));
  ASSERT_TRUE(ouma_iswxdigit(L'A'));
  ASSERT_TRUE(ouma_iswxdigit(L'a'));
  ASSERT_TRUE(ouma_iswxdigit(L'B'));
  ASSERT_TRUE(ouma_iswxdigit(L'b'));
  ASSERT_TRUE(ouma_iswxdigit(L'C'));
  ASSERT_TRUE(ouma_iswxdigit(L'c'));
  ASSERT_TRUE(ouma_iswxdigit(L'D'));
  ASSERT_TRUE(ouma_iswxdigit(L'd'));
  ASSERT_TRUE(ouma_iswxdigit(L'E'));
  ASSERT_TRUE(ouma_iswxdigit(L'e'));
  ASSERT_TRUE(ouma_iswxdigit(L'F'));
  ASSERT_TRUE(ouma_iswxdigit(L'f'));
  ASSERT_FALSE(ouma_iswxdigit(L'g'));
  ASSERT_FALSE(ouma_iswxdigit(L'１'));
}

TEST(towlower, examples) {
  ASSERT_EQ(WEOF, ouma_towlower(WEOF));
  ASSERT_EQ(L' ', ouma_towlower(L' '));
  ASSERT_EQ(L'€', ouma_towlower(L'€'));
  ASSERT_EQ(L'a', ouma_towlower(L'A'));
  ASSERT_EQ(L'a', ouma_towlower(L'a'));
  ASSERT_EQ(L'ä', ouma_towlower(L'Ä'));
  ASSERT_EQ(L'ä', ouma_towlower(L'ä'));
  ASSERT_EQ(L'λ', ouma_towlower(L'Λ'));
  ASSERT_EQ(L'λ', ouma_towlower(L'λ'));
  ASSERT_EQ(L'𐐷', ouma_towlower(L'𐐏'));
  ASSERT_EQ(L'𐐷', ouma_towlower(L'𐐷'));
}

TEST(towupper, examples) {
  ASSERT_EQ(WEOF, ouma_towupper(WEOF));
  ASSERT_EQ(L' ', ouma_towupper(L' '));
  ASSERT_EQ(L'€', ouma_towupper(L'€'));
  ASSERT_EQ(L'A', ouma_towupper(L'A'));
  ASSERT_EQ(L'A', ouma_towupper(L'a'));
  ASSERT_EQ(L'Ä', ouma_towupper(L'Ä'));
  ASSERT_EQ(L'Ä', ouma_towupper(L'ä'));
  ASSERT_EQ(L'Ÿ', ouma_towupper(L'Ÿ'));
  ASSERT_EQ(L'Ÿ', ouma_towupper(L'ÿ'));
  ASSERT_EQ(L'Λ', ouma_towupper(L'Λ'));
  ASSERT_EQ(L'Λ', ouma_towupper(L'λ'));
  ASSERT_EQ(L'𐐏', ouma_towupper(L'𐐏'));
  ASSERT_EQ(L'𐐏', ouma_towupper(L'𐐷'));
}

TEST(wctype, example) {
  EXPECT_TRUE(ouma_wctype("alnum") != 0);
  EXPECT_TRUE(ouma_wctype("alpha") != 0);
  EXPECT_TRUE(ouma_wctype("blank") != 0);
  EXPECT_TRUE(ouma_wctype("cntrl") != 0);
  EXPECT_TRUE(ouma_wctype("digit") != 0);
  EXPECT_TRUE(ouma_wctype("graph") != 0);
  EXPECT_TRUE(ouma_wctype("lower") != 0);
  EXPECT_TRUE(ouma_wctype("print") != 0);
  EXPECT_TRUE(ouma_wctype("punct") != 0);
  EXPECT_TRUE(ouma_wctype("space") != 0);
  EXPECT_TRUE(ouma_wctype("upper") != 0);
  EXPECT_TRUE(ouma_wctype("xdigit") != 0);
  EXPECT_TRUE(ouma_wctype("monkeys") == 0);
}

TEST(wctrans, examples) {
  EXPECT_EQ(wint_t('a'), ouma_towctrans(L'A', ouma_wctrans("tolower")));
  EXPECT_EQ(WEOF, ouma_towctrans(WEOF, ouma_wctrans("tolower")));
  EXPECT_EQ(wint_t('A'), ouma_towctrans(L'a', ouma_wctrans("toupper")));
  EXPECT_EQ(WEOF, ouma_towctrans(WEOF, ouma_wctrans("toupper")));
}

TEST(towctrans, example) {
  EXPECT_TRUE(ouma_wctrans("tolower") != 0);
  EXPECT_TRUE(ouma_wctrans("toupper") != 0);
  EXPECT_TRUE(ouma_wctrans("monkeys") == 0);
}
