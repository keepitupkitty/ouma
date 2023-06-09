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

#ifndef _STRINGS_H_
#define _STRINGS_H_

#include <sys/_maintypes.h>
#include <sys/cdefs.h>

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
#if __XSI_VISIBLE
int ffs(int) __pure2;
#endif
int strcasecmp(const char *, const char *);
int strncasecmp(const char *, const char *, size_t);
#if __POSIX_VISIBLE >= 200809
int strcasecmp_l(const char *, const char *, locale_t);
int strncasecmp_l(const char *, const char *, size_t, locale_t);
#endif
__END_DECLS

#endif /* !_STRINGS_H_ */
