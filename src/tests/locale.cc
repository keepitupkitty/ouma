#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <stdlib.h>

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

  struct lconv *ouma_localeconv(void);
  char *ouma_setlocale(int, const char *);

  ouma_locale_t ouma_duplocale(ouma_locale_t);
  void ouma_freelocale(ouma_locale_t);
  ouma_locale_t ouma_newlocale(int, const char *, ouma_locale_t);
  ouma_locale_t ouma_uselocale(ouma_locale_t);

  // Internal libc objects
  extern _Thread_local int __oumalibc_errno;
  extern LocaleStruct LOCALE_C;
  extern LocaleStruct LOCALE_C_UTF8;
}

#define OUMA_LC_LOCALE_C (&LOCALE_C)
#define OUMA_LC_LOCALE_UTF8 (&LOCALE_C_UTF8)
#define OUMA_LC_THREAD_LOCALE (&ThreadLocale)
#define OUMA_LC_GLOBAL_LOCALE ((ouma_locale_t)-1)

TEST(localeconv, c_standard) {
  EXPECT_STREQ(".", ouma_localeconv()->decimal_point);
  EXPECT_STREQ("", ouma_localeconv()->thousands_sep);
  EXPECT_STREQ("", ouma_localeconv()->grouping);
  EXPECT_STREQ("", ouma_localeconv()->int_curr_symbol);
  EXPECT_STREQ("", ouma_localeconv()->currency_symbol);
  EXPECT_STREQ("", ouma_localeconv()->mon_decimal_point);
  EXPECT_STREQ("", ouma_localeconv()->mon_thousands_sep);
  EXPECT_STREQ("", ouma_localeconv()->mon_grouping);
  EXPECT_STREQ("", ouma_localeconv()->positive_sign);
  EXPECT_STREQ("", ouma_localeconv()->negative_sign);
  EXPECT_EQ(CHAR_MAX, ouma_localeconv()->int_frac_digits);
  EXPECT_EQ(CHAR_MAX, ouma_localeconv()->frac_digits);
  EXPECT_EQ(CHAR_MAX, ouma_localeconv()->p_cs_precedes);
  EXPECT_EQ(CHAR_MAX, ouma_localeconv()->p_sep_by_space);
  EXPECT_EQ(CHAR_MAX, ouma_localeconv()->n_cs_precedes);
  EXPECT_EQ(CHAR_MAX, ouma_localeconv()->n_sep_by_space);
  EXPECT_EQ(CHAR_MAX, ouma_localeconv()->p_sign_posn);
  EXPECT_EQ(CHAR_MAX, ouma_localeconv()->n_sign_posn);
  EXPECT_EQ(CHAR_MAX, ouma_localeconv()->int_p_cs_precedes);
  EXPECT_EQ(CHAR_MAX, ouma_localeconv()->int_p_sep_by_space);
  EXPECT_EQ(CHAR_MAX, ouma_localeconv()->int_n_cs_precedes);
  EXPECT_EQ(CHAR_MAX, ouma_localeconv()->int_n_sep_by_space);
  EXPECT_EQ(CHAR_MAX, ouma_localeconv()->int_p_sign_posn);
  EXPECT_EQ(CHAR_MAX, ouma_localeconv()->int_n_sign_posn);
}

TEST(duplocale, example) {
  ouma_locale_t locale = ouma_duplocale(OUMA_LC_LOCALE_C);
  ASSERT_EQ(OUMA_LC_LOCALE_C, locale);
  ASSERT_NE(OUMA_LC_LOCALE_UTF8, locale);
}

TEST(newlocale, zero) {
  ouma_locale_t locale = ouma_newlocale(0, "Unknown", 0);
  ASSERT_EQ(OUMA_LC_GLOBAL_LOCALE, locale);
  ouma_freelocale(locale);
}

TEST(newlocale, incorrect_mask) {
  ouma_locale_t locale = ouma_newlocale(42069, "Unknown", 0);
  ASSERT_EQ(OUMA_LC_GLOBAL_LOCALE, locale);
  ASSERT_EQ(EINVAL, __oumalibc_errno);
  ouma_freelocale(locale);
}

TEST(newlocale, empty_name) {
  ouma_locale_t locale = ouma_newlocale(LC_ALL_MASK, "", 0);
  ASSERT_EQ(OUMA_LC_GLOBAL_LOCALE, locale);
  ouma_freelocale(locale);
}

TEST(newlocale, unknown) {
  ouma_locale_t locale = ouma_newlocale(LC_ALL_MASK, "Unknown", 0);
  ASSERT_EQ(0, locale);
  ASSERT_EQ(ENOENT, __oumalibc_errno);
  ouma_freelocale(locale);
}

TEST(newlocale, charset_only) {
  ouma_locale_t locale = ouma_newlocale(LC_CTYPE_MASK, ".UTF-8", 0);
  ASSERT_NE(OUMA_LC_GLOBAL_LOCALE, locale);
  ouma_freelocale(locale);
}

TEST(newlocale, messages_only) {
  ouma_locale_t locale = ouma_newlocale(LC_MESSAGES, "yue_HK", 0);
  ASSERT_NE(OUMA_LC_GLOBAL_LOCALE, locale);
  ouma_freelocale(locale);
}

TEST(uselocale, sample) {
  ouma_locale_t original = ouma_uselocale(nullptr);
  ASSERT_NE(original, nullptr);
  ASSERT_EQ(OUMA_LC_GLOBAL_LOCALE, original);
  ouma_locale_t n = ouma_newlocale(LC_ALL, "C", nullptr);
  ASSERT_NE(n, nullptr);
  ASSERT_EQ(n, original);
  ouma_locale_t old = ouma_uselocale(n);
  ASSERT_EQ(old, original);
}

TEST(setlocale, good) {
  ASSERT_STREQ("C", ouma_setlocale(LC_ALL, NULL));
  ASSERT_STREQ("C", ouma_setlocale(LC_CTYPE, ""));
  ASSERT_STREQ("C", ouma_setlocale(LC_MESSAGES, "C"));
  ASSERT_STREQ("C", ouma_setlocale(LC_TIME, "POSIX"));
}

TEST(setlocale, bad) {
  ASSERT_EQ(NULL, ouma_setlocale(LC_ALL, "RealGermanLanguageInSwitzerlandDotUnicodeDashEight"));
}
