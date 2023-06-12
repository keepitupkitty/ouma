/*
 * Copyright 2023 rSec Linux
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _STRING_H
#define _STRING_H

#include <sys/_maintypes.h>
#include <sys/_null.h>
#include <sys/cdefs.h>

#if __BSD_VISIBLE
#include <strings.h>
#endif

#ifndef _SIZE_T_DECLARED
typedef __size_t size_t;
#define _SIZE_T_DECLARED
#endif

#if __POSIX_VISIBLE >= 200809
#ifndef _LOCALE_T_DEFINED_
#define _LOCALE_T_DEFINED_
typedef void *locale_t;
#endif
#endif

__BEGIN_DECLS
#if __XSI_VISIBLE >= 600
void *memccpy(void *__restrict, const void *__restrict, int, size_t);
#endif
void *memchr(const void *, int, size_t);
int memcmp(const void *, const void *, size_t);
void *memcpy(void *__restrict, const void *__restrict, size_t);
void *memmove(void *, const void *, size_t);
void *memset(void *, int, size_t);
#if __POSIX_VISIBLE >= 200809
char *stpcpy(char *__restrict, const char *__restrict);
char *stpncpy(char *__restrict, const char *__restrict, size_t);
#endif
char *strcat(char *__restrict, const char *__restrict);
char *strchr(const char *, int);
int strcmp(const char *, const char *);
int strcoll(const char *, const char *);
#if __POSIX_VISIBLE >= 200809
int strcoll_l(const char *, const char *, locale_t);
#endif
char *strcpy(char *__restrict, const char *__restrict);
size_t strcspn(const char *, const char *);
#if __POSIX_VISIBLE >= 200112 || __XSI_VISIBLE
char *strdup(const char *);
#endif
char *strerror(int);
#if __POSIX_VISIBLE >= 200112
int strerror_r(int, char *, size_t);
#endif
size_t strlen(const char *);
char *strncat(char *__restrict, const char *__restrict, size_t);
int strncmp(const char *, const char *, size_t);
char *strncpy(char *__restrict, const char *__restrict, size_t);
#if __POSIX_VISIBLE >= 200809
char *strndup(const char *, size_t);
size_t strnlen(const char *, size_t);
#endif
char *strpbrk(const char *, const char *);
char *strrchr(const char *, int);
#if __POSIX_VISIBLE >= 200809
char *strsignal(int);
#endif
size_t strspn(const char *, const char *);
char *strstr(const char *, const char *);
char *strtok(char *__restrict, const char *__restrict);
#if __POSIX_VISIBLE >= 199506 || __XSI_VISIBLE >= 500
char *strtok_r(char *, const char *, char **);
#endif
size_t strxfrm(char *__restrict, const char *__restrict, size_t);
#if __POSIX_VISIBLE >= 200809
size_t strxfrm_l(char *__restrict, const char *__restrict, size_t, locale_t);
#endif
__END_DECLS

#endif /* !_STRING_H */
