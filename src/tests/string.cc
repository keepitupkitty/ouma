#include <gmock/gmock.h>
#include <gtest/gtest.h>

extern "C" {
  void *ouma_memccpy(void *__restrict, const void *__restrict, int, size_t);
  void *ouma_memchr(const void *, int, size_t);
  int ouma_memcmp(const void *, const void *, size_t);
  void *ouma_memcpy(void *__restrict, const void *__restrict, size_t);
  void *ouma_memmove(void *, const void *, size_t);
  void *ouma_memset(void *, int, size_t);
  void *ouma_memset_explicit(void *, int, size_t);
  char *ouma_strchr(const char *, int);
  char *ouma_stpcpy(char *__restrict, const char *__restrict);
  char *ouma_stpncpy(char *__restrict, const char *__restrict, size_t);
  char *ouma_strncat(char *__restrict, const char *__restrict, size_t);
  int ouma_strncmp(const char *, const char *, size_t);
  char *ouma_strncpy(char *__restrict, const char *__restrict, size_t);
  char *ouma_strcat(char *__restrict, const char *__restrict);
  int ouma_strcmp(const char *, const char *);
  char *ouma_strcpy(char *__restrict, const char *__restrict);
  size_t ouma_strnlen(const char *, size_t);
  size_t ouma_strlen(const char *);
  size_t ouma_strcspn(const char *, const char *);
  size_t ouma_strspn(const char *, const char *);
  char *ouma_strpbrk(const char *, const char *);
  char *ouma_strrchr(const char *, int);
  char *ouma_strstr(const char *, const char *);
  char *ouma_strtok_r(char *__restrict, const char *__restrict, char **__restrict);
  char *ouma_strtok(char *__restrict, const char *__restrict);
  int ouma_strcoll(const char *, const char *);
  int ouma_strcoll_l(const char *, const char *, locale_t);
  size_t ouma_strxfrm(char *__restrict, const char *__restrict, size_t);
  size_t ouma_strxfrm_l(char *__restrict, const char *__restrict, size_t, locale_t);
  int ouma_strerror_r(int, char *, size_t);
  char *__ouma_gnu_strerror_r(int, char *, size_t);
  char *ouma_strerror(int);
  char *ouma_strerror_l(int, locale_t);
  char *ouma_strsignal(int);

/* When malloc gets added
  char *ouma_strndup(const char *, size_t);
  char *ouma_strdup(const char *);
*/

/* When ctype support gets added
  int ouma_ffs(int);
  int ouma_strcasecmp(const char *, const char *);
  int ouma_strcasecmp_l(const char *, const char *, locale_t);
  int ouma_strncasecmp(const char *, const char *, size_t);
  int ouma_strncasecmp_l(const char *, const char *, size_t, locale_t);
*/

  extern _Thread_local int __oumalibc_errno;
  extern int __oumalibc_current_sigrtmax();
  extern int __oumalibc_current_sigrtmin();
}

TEST(memccpy, null) {
  ASSERT_EQ(NULL, ouma_memccpy((char *)456, (char *)789, 'A', 0));
}

TEST(memccpy, example) {
  const char buf1[13] = "Test\0string!";
  char buf2[] = "AAAAAAAAA";
  ASSERT_EQ(&buf2[8], ouma_memccpy(buf2, buf1, 'r', 9999));
  ASSERT_THAT(buf2, testing::ElementsAreArray("Test\0strA"));
}

TEST(memchr, null) {
  ASSERT_EQ(NULL, ouma_memchr((char *)nullptr, 'A', 0));
}

TEST(memchr, match) {
  char buf[] = "Foo bar baz";
  ASSERT_EQ(buf + 5, ouma_memchr(buf, 'a', sizeof(buf)));
}

TEST(memchr, nomatch) {
  char buf[] = "Foo bar baz";
  ASSERT_EQ(NULL, ouma_memchr(buf, 'x', sizeof(buf)));
}

TEST(memcmp, null) {
  ASSERT_EQ(0, ouma_memcmp(NULL, NULL, 0));
}

TEST(memcmp, example) {
  const char buf1[] = "Hello";
  const char buf2[] = "Helxo";
  ASSERT_EQ(0, ouma_memcmp(buf1, buf1, sizeof(buf1)));
  ASSERT_GT(0, ouma_memcmp(buf1, buf2, sizeof(buf1)));
  ASSERT_LT(0, ouma_memcmp(buf2, buf1, sizeof(buf1)));
}

TEST(memcpy, null) {
  ASSERT_EQ((char *)42, ouma_memcpy((char *)42, (char *)123, 0));
}

TEST(memcpy, example) {
  const char buf1[8] = "Foo\0Bar";
  char buf2[8];
  ASSERT_EQ(buf2, ouma_memcpy(buf2, buf1, sizeof(buf1)));
  ASSERT_THAT(buf2, testing::ElementsAreArray(buf1));
}

TEST(memmove, null) {
  ASSERT_EQ((char *)42, ouma_memmove((char *)42, (char *)34, 0));
}

TEST(memmove, example1) {
  char buf[] = "abcdefghijkl";
  ASSERT_EQ(buf, ouma_memmove(buf, buf + 4, 8));
  ASSERT_STREQ("efghijklijkl", buf);
}

TEST(memmove, example2) {
  char buf[] = "abcdefghijkl";
  ASSERT_EQ(buf + 4, ouma_memmove(buf + 4, buf, 8));
  ASSERT_STREQ("abcdabcdefgh", buf);
}

TEST(memset, null) {
  ASSERT_EQ((char *)5, ouma_memset((char *)5, 'A', 0));
}

TEST(memset, example_small) {
  char buf[11];
  ASSERT_EQ(buf, ouma_memset(buf, '!', 10));
  buf[10] = '\0';
  ASSERT_STREQ("!!!!!!!!!!", buf);
}

TEST(memset, example_large) {
  char buf[101];
  ASSERT_EQ(buf, ouma_memset(buf, '!', 100));
  buf[100] = '\0';
  ASSERT_THAT(buf,
              testing::ElementsAreArray("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
                                        "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
                                        "!!!!!!!!!!!!!!!!!!!!!!!!"));
}

TEST(memset, explicit) {
  char buf[32];
  ouma_memset_explicit(buf, 'x', sizeof(buf));
  ASSERT_TRUE(ouma_memcmp(buf, "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx", sizeof(buf)) == 0);
}

TEST(strchr, examples) {
  const char *str = "Hello, world";
  ASSERT_EQ(NULL, ouma_strchr(str, 'A'));
  ASSERT_EQ(str + 4, ouma_strchr(str, 'o'));
  ASSERT_EQ(str + 12, ouma_strchr(str, '\0'));
}

TEST(strrchr, examples) {
  const char *str = "Hello, world";
  ASSERT_EQ(NULL, ouma_strrchr(str, 'A'));
  ASSERT_EQ(str + 8, ouma_strrchr(str, 'o'));
  ASSERT_EQ(str + 12, ouma_strrchr(str, '\0'));
}

TEST(stpcpy, example) {
  char buf[] = "AAAAAAAAAA";
  ASSERT_EQ(buf, ouma_stpcpy(buf, ""));
  ASSERT_THAT(buf, testing::ElementsAreArray("\0AAAAAAAAA"));
  ASSERT_EQ(buf + 5, ouma_stpcpy(buf, "Hello"));
  ASSERT_THAT(buf, testing::ElementsAreArray("Hello\0AAAA"));
  ASSERT_EQ(buf, ouma_stpcpy(buf, ""));
  ASSERT_THAT(buf, testing::ElementsAreArray("\0ello\0AAAA"));
  ASSERT_EQ(buf + 9, ouma_stpcpy(buf, "Example!!"));
  ASSERT_THAT(buf, testing::ElementsAreArray("Example!!\0"));
}

TEST(stpncpy, null) {
  ASSERT_EQ((char *)12, ouma_stpncpy((char *)12, (char *)500, 0));
}

TEST(stpncpy, example1) {
  char buf[] = "AAAAAAAAAAAA";
  ASSERT_EQ(buf + 5, ouma_stpncpy(buf, "Hello", 12));
  ASSERT_THAT(buf, testing::ElementsAreArray("Hello\0\0\0\0\0\0\0"));
}

TEST(stpncpy, example2) {
  char buf[] = "AAAAAAAAAAAA";
  ASSERT_EQ(buf + 12, ouma_stpncpy(buf, "This is a very long string", 12));
  ASSERT_THAT(buf, testing::ElementsAreArray("This is a ve"));
}

TEST(strcat, example) {
  char buf[] = "\0AAAAAAAAA";
  ASSERT_EQ(buf, ouma_strcat(buf, ""));
  ASSERT_THAT(buf, testing::ElementsAreArray("\0AAAAAAAAA"));
  ASSERT_EQ(buf, ouma_strcat(buf, "Hello"));
  ASSERT_THAT(buf, testing::ElementsAreArray("Hello\0AAAA"));
  ASSERT_EQ(buf, ouma_strcat(buf, ""));
  ASSERT_THAT(buf, testing::ElementsAreArray("Hello\0AAAA"));
  ASSERT_EQ(buf, ouma_strcat(buf, "!!!!"));
  ASSERT_THAT(buf, testing::ElementsAreArray("Hello!!!!\0"));
}

TEST(strncat, example) {
  char buf[] = "\0AAAAAAAAA";
  ASSERT_EQ(buf, ouma_strncat(buf, "", 0));
  ASSERT_THAT(buf, testing::ElementsAreArray("\0AAAAAAAAA"));
  ASSERT_EQ(buf, ouma_strncat(buf, "Hello", 99999));
  ASSERT_THAT(buf, testing::ElementsAreArray("Hello\0AAAA"));
  ASSERT_EQ(buf, ouma_strncat(buf, "", 1));
  ASSERT_THAT(buf, testing::ElementsAreArray("Hello\0AAAA"));
  ASSERT_EQ(buf, ouma_strncat(buf, "!!!!!!!!!!!!", 3));
  ASSERT_THAT(buf, testing::ElementsAreArray("Hello!!!\0A"));
}

TEST(strcmp, examples) {
  ASSERT_EQ(0, ouma_strcmp("", ""));
  ASSERT_EQ(0, ouma_strcmp("Hello", "Hello"));

  ASSERT_GT(0, ouma_strcmp("Hello", "Hello, world"));
  ASSERT_LT(0, ouma_strcmp("Hello, world", "Hello"));

  ASSERT_GT(0, ouma_strcmp("Hello!", "Hello."));
  ASSERT_LT(0, ouma_strcmp("Hello.", "Hello!"));
}

TEST(strncmp, null) {
  ASSERT_EQ(0, ouma_strncmp(NULL, NULL, 0));
}

TEST(strncmp, examples) {
  ASSERT_EQ(0, ouma_strncmp("", "", 100));
  ASSERT_EQ(0, ouma_strncmp("Hello", "Hello", 100));

  ASSERT_EQ(0, ouma_strncmp("Hello", "Hello, world", 5));
  ASSERT_GT(0, ouma_strncmp("Hello", "Hello, world", 6));
  ASSERT_LT(0, ouma_strncmp("Hello, world", "Hello", 100));

  ASSERT_EQ(0, ouma_strncmp("Hello!", "Hello.", 5));
  ASSERT_GT(0, ouma_strncmp("Hello!", "Hello.", 6));
  ASSERT_LT(0, ouma_strncmp("Hello.", "Hello!", 100));
}

TEST(strcpy, example) {
  char buf[] = "AAAAAAAAAA";
  ASSERT_EQ(buf, ouma_strcpy(buf, ""));
  ASSERT_THAT(buf, testing::ElementsAreArray("\0AAAAAAAAA"));
  ASSERT_EQ(buf, ouma_strcpy(buf, "Hello"));
  ASSERT_THAT(buf, testing::ElementsAreArray("Hello\0AAAA"));
  ASSERT_EQ(buf, ouma_strcpy(buf, ""));
  ASSERT_THAT(buf, testing::ElementsAreArray("\0ello\0AAAA"));
  ASSERT_EQ(buf, ouma_strcpy(buf, "Example!!"));
  ASSERT_THAT(buf, testing::ElementsAreArray("Example!!\0"));
}

TEST(strncpy, null) {
  ASSERT_EQ((char *)12, ouma_strncpy((char *)12, (char *)500, 0));
}

TEST(strncpy, example1) {
  char buf[] = "AAAAAAAAAAAA";
  ASSERT_EQ(buf, ouma_strncpy(buf, "Hello", 12));
  ASSERT_THAT(buf, testing::ElementsAreArray("Hello\0\0\0\0\0\0\0"));
}

TEST(strncpy, example2) {
  char buf[13];
  ASSERT_EQ(buf, ouma_strncpy(buf, "This is a very long string", 12));
  buf[12] = '\0';
  ASSERT_THAT(buf, testing::ElementsAreArray("This is a ve"));
}

TEST(strlen, all) {
  ASSERT_EQ(0, ouma_strlen(""));
  ASSERT_EQ(12, ouma_strlen("Hello, world"));
}

TEST(strnlen, null) {
  ASSERT_EQ(0, ouma_strnlen(NULL, 0));
  ASSERT_EQ(0, ouma_strnlen("", 100));
  ASSERT_EQ(7, ouma_strnlen("Hello, world", 7));
}

TEST(strcspn, example) {
  const char *str = "Hello, world";
  ASSERT_EQ(0, ouma_strcspn(str, "H"));
  ASSERT_EQ(7, ouma_strcspn(str, "rdw"));
  ASSERT_EQ(12, ouma_strcspn(str, "XYZ"));
}

TEST(strspn, example) {
  const char *str = "Hello, world";
  ASSERT_EQ(0, ouma_strspn(str, ""));
  ASSERT_EQ(0, ouma_strspn(str, "Foo"));
  ASSERT_EQ(5, ouma_strspn(str, "olHe"));
  ASSERT_EQ(12, ouma_strspn(str, "Helo, wrld"));
}

TEST(strpbrk, example) {
  const char *str = "Hello, world";
  ASSERT_EQ(str, ouma_strpbrk(str, "H"));
  ASSERT_EQ(str + 7, ouma_strpbrk(str, "rdw"));
  ASSERT_EQ(NULL, ouma_strpbrk(str, "XYZ"));
}

TEST(strstr, example) {
  const char* haystack = "big daddy/giant haystacks!";
  const char* some_haystack = "haystack";
  const char* empty_haystack = "";
  ASSERT_EQ(some_haystack, ouma_strstr(some_haystack, ""));
  ASSERT_EQ(empty_haystack, ouma_strstr(empty_haystack, ""));
  ASSERT_EQ(haystack + 0, ouma_strstr(haystack, ""));
  ASSERT_EQ(haystack + 0, ouma_strstr(haystack, "b"));
  ASSERT_EQ(haystack + 0, ouma_strstr(haystack, "bi"));
  ASSERT_EQ(haystack + 0, ouma_strstr(haystack, "big"));
  ASSERT_EQ(haystack + 0, ouma_strstr(haystack, "big "));
  ASSERT_EQ(haystack + 0, ouma_strstr(haystack, "big d"));
  ASSERT_EQ(haystack + 2, ouma_strstr(haystack, "g"));
  ASSERT_EQ(haystack + 10, ouma_strstr(haystack, "gi"));
  ASSERT_EQ(haystack + 10, ouma_strstr(haystack, "gia"));
  ASSERT_EQ(haystack + 10, ouma_strstr(haystack, "gian"));
  ASSERT_EQ(haystack + 10, ouma_strstr(haystack, "giant"));
  ASSERT_EQ(haystack + 25, ouma_strstr(haystack, "!"));
  ASSERT_EQ(haystack + 24, ouma_strstr(haystack, "s!"));
  ASSERT_EQ(haystack + 23, ouma_strstr(haystack, "ks!"));
  ASSERT_EQ(haystack + 22, ouma_strstr(haystack, "cks!"));
  ASSERT_EQ(haystack + 21, ouma_strstr(haystack, "acks!"));
}

TEST(strtok, NoTokenFound) {
  char empty[] = "";
  ASSERT_STREQ(ouma_strtok(empty, ""), nullptr);
  ASSERT_STREQ(ouma_strtok(empty, "_"), nullptr);

  char single[] = "_";
  ASSERT_STREQ(ouma_strtok(single, ""), "_");

  char multiple[] = "1,2";
  ASSERT_STREQ(ouma_strtok(multiple, ":"), "1,2");
}

TEST(strtok, DelimiterAsFirstCharacterShouldBeIgnored) {
  char src[] = ".123";
  ASSERT_STREQ(ouma_strtok(src, "."), "123");
}

TEST(strtok, DelimiterIsMiddleCharacter) {
  char src[] = "12,34";
  ASSERT_STREQ(ouma_strtok(src, ","), "12");
}

TEST(strtok, DelimiterAsLastCharacterShouldBeIgnored) {
  char src[] = "1234:";
  ASSERT_STREQ(ouma_strtok(src, ":"), "1234");
}

TEST(strtok, MultipleDelimiters) {
  char src[] = "12,.34";
  ASSERT_STREQ(ouma_strtok(src, "."), "12,");
  ASSERT_STREQ(ouma_strtok(src, ".,"), "12");
  ASSERT_STREQ(ouma_strtok(src, ",."), "12");
  ASSERT_STREQ(ouma_strtok(src, ":,."), "12");
}

TEST(strtok, ShouldNotGoPastNullTerminator) {
  char src[] = {'1', '2', '\0', ',', '3'};
  ASSERT_STREQ(ouma_strtok(src, ","), "12");
}

TEST(strtok, SubsequentCallsShouldFindFollowingDelimiters) {
  char src[] = "12,34.56";
  char *token = ouma_strtok(src, ",.");
  ASSERT_STREQ(token, "12");
  token = ouma_strtok(nullptr, ",.");
  ASSERT_STREQ(token, "34");
  token = ouma_strtok(nullptr, ",.");
  ASSERT_STREQ(token, "56");
  token = ouma_strtok(nullptr, "_:,_");
  ASSERT_STREQ(token, nullptr);
  token = ouma_strtok(nullptr, "_:,_");
  ASSERT_STREQ(token, nullptr);
}

TEST(strtok, DelimitersShouldNotBeIncludedInToken) {
  char src[] = "__ab__:_cd__:__ef__:__";
  char *token = ouma_strtok(src, "_:");
  ASSERT_STREQ(token, "ab");
  token = ouma_strtok(nullptr, ":_");
  ASSERT_STREQ(token, "cd");
  token = ouma_strtok(nullptr, "_:,");
  ASSERT_STREQ(token, "ef");
  token = ouma_strtok(nullptr, "_:,_");
  ASSERT_STREQ(token, nullptr);
}

TEST(strtok_r, NoTokenFound) {
  {
    char empty[] = "";
    char *reserve = nullptr;
    ASSERT_STREQ(ouma_strtok_r(empty, "", &reserve), nullptr);
    ASSERT_STREQ(ouma_strtok_r(empty, "", &reserve), nullptr);
    ASSERT_STREQ(ouma_strtok_r(nullptr, "", &reserve), nullptr);
  }
  {
    char empty[] = "";
    char *reserve = nullptr;
    ASSERT_STREQ(ouma_strtok_r(empty, "_", &reserve), nullptr);
    ASSERT_STREQ(ouma_strtok_r(empty, "_", &reserve), nullptr);
    ASSERT_STREQ(ouma_strtok_r(nullptr, "_", &reserve), nullptr);
  }
  {
    char single[] = "_";
    char *reserve = nullptr;
    ASSERT_STREQ(ouma_strtok_r(single, "_", &reserve), nullptr);
    ASSERT_STREQ(ouma_strtok_r(single, "_", &reserve), nullptr);
    ASSERT_STREQ(ouma_strtok_r(nullptr, "_", &reserve), nullptr);
  }
  {
    char multiple[] = "1,2";
    char *reserve = nullptr;
    ASSERT_STREQ(ouma_strtok_r(multiple, ":", &reserve), "1,2");
    ASSERT_STREQ(ouma_strtok_r(multiple, ":", &reserve), "1,2");
    ASSERT_STREQ(ouma_strtok_r(nullptr, ":", &reserve), nullptr);
  }
}

TEST(strtok_r, DelimiterAsFirstCharacterShouldBeIgnored) {
  char src[] = ".123";
  char *reserve = nullptr;
  ASSERT_STREQ(ouma_strtok_r(src, ".", &reserve), "123");
  ASSERT_STREQ(ouma_strtok_r(src, ".", &reserve), "123");
  ASSERT_STREQ(ouma_strtok_r(nullptr, ".", &reserve), nullptr);
}

TEST(strtok_r, DelimiterIsMiddleCharacter) {
  char src[] = "12,34";
  char *reserve = nullptr;
  ASSERT_STREQ(ouma_strtok_r(src, ",", &reserve), "12");
  ASSERT_STREQ(ouma_strtok_r(src, ",", &reserve), "12");
  ASSERT_STREQ(ouma_strtok_r(nullptr, ",", &reserve), nullptr);
}

TEST(strtok_r, DelimiterAsLastCharacterShouldBeIgnored) {
  char src[] = "1234:";
  char *reserve = nullptr;
  ASSERT_STREQ(ouma_strtok_r(src, ":", &reserve), "1234");
  ASSERT_STREQ(ouma_strtok_r(src, ":", &reserve), "1234");
  ASSERT_STREQ(ouma_strtok_r(nullptr, ":", &reserve), nullptr);
}

TEST(strtok_r, ShouldNotGoPastNullTerminator) {
  char src[] = {'1', '2', '\0', ',', '3'};
  char *reserve = nullptr;
  ASSERT_STREQ(ouma_strtok_r(src, ",", &reserve), "12");
  ASSERT_STREQ(ouma_strtok_r(src, ",", &reserve), "12");
  ASSERT_STREQ(ouma_strtok_r(nullptr, ",", &reserve), nullptr);
}

TEST(strtok_r,
     ShouldReturnNullptrWhenBothSrcAndSaveptrAreNull) {
  char *src = nullptr;
  char *reserve = nullptr;
  ASSERT_STREQ(ouma_strtok_r(src, ",", &reserve), nullptr);
  ASSERT_STREQ(src, nullptr);
  ASSERT_STREQ(reserve, nullptr);
}

TEST(strtok_r,
     SubsequentCallsShouldFindFollowingDelimiters) {
  char src[] = "12,34.56";
  char *reserve = nullptr;
  char *token = ouma_strtok_r(src, ",.", &reserve);
  ASSERT_STREQ(token, "12");
  token = ouma_strtok_r(nullptr, ",.", &reserve);
  ASSERT_STREQ(token, "34");
  token = ouma_strtok_r(nullptr, ",.", &reserve);
  ASSERT_STREQ(token, "56");
  token = ouma_strtok_r(nullptr, "_:,_", &reserve);
  ASSERT_STREQ(token, nullptr);
  token = ouma_strtok_r(nullptr, "_:,_", &reserve);
  ASSERT_STREQ(token, nullptr);
}

TEST(strtok_r, DelimitersShouldNotBeIncludedInToken) {
  char src[] = "__ab__:_cd__:__ef__:__";
  char *reserve = nullptr;
  char *token = ouma_strtok_r(src, "_:", &reserve);
  ASSERT_STREQ(token, "ab");
  token = ouma_strtok_r(nullptr, ":_", &reserve);
  ASSERT_STREQ(token, "cd");
  token = ouma_strtok_r(nullptr, "_:,", &reserve);
  ASSERT_STREQ(token, "ef");
  token = ouma_strtok_r(nullptr, "_:,_", &reserve);
  ASSERT_STREQ(token, nullptr);
}

TEST(strerror, example) {
  ASSERT_STREQ(ouma_strerror(0), "Success");

  const char *message_array[] = {
      "Success",
      "Operation not permitted",
      "No such file or directory",
      "No such process",
      "Interrupted system call",
      "Input/output error",
      "No such device or address",
      "Argument list too long",
      "Exec format error",
      "Bad file descriptor",
      "No child processes",
      "Resource temporarily unavailable",
      "Cannot allocate memory",
      "Permission denied",
      "Bad address",
      "Block device required",
      "Device or resource busy",
      "File exists",
      "Invalid cross-device link",
      "No such device",
      "Not a directory",
      "Is a directory",
      "Invalid argument",
      "Too many open files in system",
      "Too many open files",
      "Inappropriate ioctl for device",
      "Text file busy",
      "File too large",
      "No space left on device",
      "Illegal seek",
      "Read-only file system",
      "Too many links",
      "Broken pipe",
      "Numerical argument out of domain",
      "Numerical result out of range",
      "Resource deadlock avoided",
      "File name too long",
      "No locks available",
      "Function not implemented",
      "Directory not empty",
      "Too many levels of symbolic links",
      "Unknown error 41", // Unknown
      "No message of desired type",
      "Identifier removed",
      "Channel number out of range",
      "Level 2 not synchronized",
      "Level 3 halted",
      "Level 3 reset",
      "Link number out of range",
      "Protocol driver not attached",
      "No CSI structure available",
      "Level 2 halted",
      "Invalid exchange",
      "Invalid request descriptor",
      "Exchange full",
      "No anode",
      "Invalid request code",
      "Invalid slot",
      "Unknown error 58", // Unknown
      "Bad font file format",
      "Device not a stream",
      "No data available",
      "Timer expired",
      "Out of streams resources",
      "Machine is not on the network",
      "Package not installed",
      "Object is remote",
      "Link has been severed",
      "Advertise error",
      "Srmount error",
      "Communication error on send",
      "Protocol error",
      "Multihop attempted",
      "RFS specific error",
      "Bad message",
      "Value too large for defined data type",
      "Name not unique on network",
      "File descriptor in bad state",
      "Remote address changed",
      "Can not access a needed shared library",
      "Accessing a corrupted shared library",
      ".lib section in a.out corrupted",
      "Attempting to link in too many shared libraries",
      "Cannot exec a shared library directly",
      "Invalid or incomplete multibyte or wide character",
      "Interrupted system call should be restarted",
      "Streams pipe error",
      "Too many users",
      "Socket operation on non-socket",
      "Destination address required",
      "Message too long",
      "Protocol wrong type for socket",
      "Protocol not available",
      "Protocol not supported",
      "Socket type not supported",
      "Operation not supported",
      "Protocol family not supported",
      "Address family not supported by protocol",
      "Address already in use",
      "Cannot assign requested address",
      "Network is down",
      "Network is unreachable",
      "Network dropped connection on reset",
      "Software caused connection abort",
      "Connection reset by peer",
      "No buffer space available",
      "Transport endpoint is already connected",
      "Transport endpoint is not connected",
      "Cannot send after transport endpoint shutdown",
      "Too many references: cannot splice",
      "Connection timed out",
      "Connection refused",
      "Host is down",
      "No route to host",
      "Operation already in progress",
      "Operation now in progress",
      "Stale file handle",
      "Structure needs cleaning",
      "Not a XENIX named type file",
      "No XENIX semaphores available",
      "Is a named type file",
      "Remote I/O error",
      "Disk quota exceeded",
      "No medium found",
      "Wrong medium type",
      "Operation canceled",
      "Required key not available",
      "Key has expired",
      "Key has been revoked",
      "Key was rejected by service",
      "Owner died",
      "State not recoverable",
      "Operation not possible due to RF-kill",
      "Memory page has hardware error",
  };

  for (size_t i = 0; i < (sizeof(message_array) / sizeof(char *)); ++i) {
    EXPECT_STREQ(ouma_strerror(static_cast<int>(i)), message_array[i]);
  }

  ASSERT_STREQ(ouma_strerror(-1), "Unknown error -1");
  ASSERT_STREQ(ouma_strerror(134), "Unknown error 134");
  ASSERT_STREQ(ouma_strerror(2147483647), "Unknown error 2147483647");
  ASSERT_STREQ(ouma_strerror(-2147483648), "Unknown error -2147483648");
}

TEST(strerror_r, null) {
  __oumalibc_errno = 1234;
  ASSERT_EQ(0, ouma_strerror_r(EINVAL, NULL, 0));
  ASSERT_EQ(1234, __oumalibc_errno);
}

TEST(strerror_r, one) {
  char buf = 'A';
  __oumalibc_errno = 1234;
  ASSERT_EQ(0, ouma_strerror_r(EINVAL, &buf, 1));
  ASSERT_EQ(1234, __oumalibc_errno);
}

TEST(strerror_r, partial) {
  char buf[12];
  __oumalibc_errno = 1234;
  ASSERT_EQ(0, ouma_strerror_r(EINVAL, buf, sizeof(buf)));
  ASSERT_EQ(1234, __oumalibc_errno);
  ASSERT_STREQ("Invalid arg", buf);
}

TEST(strerror_r, full) {
  char buf[21] = "AAAAAAAAAAAAAAAAAAAA";
  __oumalibc_errno = 1234;
  ASSERT_EQ(0, ouma_strerror_r(EINVAL, buf, sizeof(buf)));
  ASSERT_EQ(1234, __oumalibc_errno);
  ASSERT_THAT(buf, testing::ElementsAreArray("Invalid argument\x00"
                                             "AAA"));
}

TEST(strerror_r, gnu) {
  char buf[256];
  // Note that glibc doesn't necessarily write into the buffer.
  // Valid.
  ASSERT_STREQ("Success", __ouma_gnu_strerror_r(0, buf, sizeof(buf)));
  ASSERT_STREQ("Success", buf);
  ASSERT_STREQ("Operation not permitted", __ouma_gnu_strerror_r(1, buf, sizeof(buf)));
  ASSERT_STREQ("Operation not permitted", buf);
  // Invalid.
  ASSERT_STREQ("Unknown error -1", __ouma_gnu_strerror_r(-1, buf, sizeof(buf)));
  ASSERT_STREQ("Unknown error -1", buf);
  ASSERT_STREQ("Unknown error 1234", __ouma_gnu_strerror_r(1234, buf, sizeof(buf)));
  ASSERT_STREQ("Unknown error 1234", buf);
  // Buffer too small.
  __oumalibc_errno = 0;
  memset(buf, 0, sizeof(buf));
  ASSERT_EQ(buf, __ouma_gnu_strerror_r(4567, buf, 2));
  ASSERT_STREQ("U", buf);
  // The GNU strerror_r doesn't set errno (the POSIX one sets it to ERANGE).
  ASSERT_EQ(0, __oumalibc_errno);
}

TEST(strsignal, example) {
  ASSERT_STREQ(ouma_strsignal(1), "Hangup");

  const char *message_array[] = {
      "Unknown signal 0",
      "Hangup",
      "Interrupt",
      "Quit",
      "Illegal instruction",
      "Trace/breakpoint trap",
      "Aborted",
      "Bus error",
      "Floating point exception",
      "Killed",
      "User defined signal 1",
      "Segmentation fault",
      "User defined signal 2",
      "Broken pipe",
      "Alarm clock",
      "Terminated",
      "Stack fault",
      "Child exited",
      "Continued",
      "Stopped (signal)",
      "Stopped",
      "Stopped (tty input)",
      "Stopped (tty output)",
      "Urgent I/O condition",
      "CPU time limit exceeded",
      "File size limit exceeded",
      "Virtual timer expired",
      "Profiling timer expired",
      "Window changed",
      "I/O possible",
      "Power failure",
      "Bad system call",
  };

  for (size_t i = 0; i < (sizeof(message_array) / sizeof(char *)); ++i) {
    ASSERT_EQ(static_cast<size_t>(static_cast<int>(i)), i);
    EXPECT_STREQ(ouma_strsignal(static_cast<int>(i)), message_array[i]);
  }

  // There are supposed to be 32 of these, but sometimes SIGRTMIN is shifted to
  // reserve some.
  const char *rt_message_array[] = {
      "Real-time signal 0",  "Real-time signal 1",  "Real-time signal 2",
      "Real-time signal 3",  "Real-time signal 4",  "Real-time signal 5",
      "Real-time signal 6",  "Real-time signal 7",  "Real-time signal 8",
      "Real-time signal 9",  "Real-time signal 10", "Real-time signal 11",
      "Real-time signal 12", "Real-time signal 13", "Real-time signal 14",
      "Real-time signal 15", "Real-time signal 16", "Real-time signal 17",
      "Real-time signal 18", "Real-time signal 19", "Real-time signal 20",
      "Real-time signal 21", "Real-time signal 22", "Real-time signal 23",
      "Real-time signal 24", "Real-time signal 25", "Real-time signal 26",
      "Real-time signal 27", "Real-time signal 28", "Real-time signal 29",
      "Real-time signal 30", "Real-time signal 31", "Real-time signal 32",
  };

//  for (int i = 0; i < __oumalibc_current_sigrtmax() - __oumalibc_current_sigrtmin(); ++i) {
//    EXPECT_STREQ(ouma_strsignal(i + __oumalibc_current_sigrtmin()), rt_message_array[i]);
//  }

  ASSERT_STREQ(ouma_strsignal(-1), "Unknown signal -1");
  ASSERT_STREQ(ouma_strsignal(65), "Unknown signal 65");
  ASSERT_STREQ(ouma_strsignal(2147483647), "Unknown signal 2147483647");
  ASSERT_STREQ(ouma_strsignal(-2147483648),
               "Unknown signal -2147483648");
}
