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

#ifndef _WCHAR_H
#define _WCHAR_H

#include <sys/_maintypes.h>
#include <sys/_null.h>
#include <sys/cdefs.h>

#if __POSIX_VISIBLE >= 200809 || __XSI_VISIBLE
#ifndef _VA_LIST_DECLARED
typedef __va_list va_list;
#define _VA_LIST_DECLARED
#endif
#endif

#ifndef __cplusplus
#ifndef _WCHAR_T_DECLARED
typedef ___wchar_t wchar_t;
#define _WCHAR_T_DECLARED
#endif
#endif

#ifndef _WINT_T_DECLARED
typedef __wint_t wint_t;
#define _WINT_T_DECLARED
#endif

#ifndef _MBSTATE_T_DEFINED_
#define _MBSTATE_T_DEFINED_
typedef struct __mbstate_t mbstate_t;
#endif

#ifndef _SIZE_T_DEFINED_
#define _SIZE_T_DEFINED_
typedef __size_t size_t;
#endif

#ifndef WEOF
#define WEOF ((wint_t)-1)
#endif

#ifndef WCHAR_MIN
#define WCHAR_MIN __WCHAR_MIN
#endif
#ifndef WCHAR_MAX
#define WCHAR_MAX __WCHAR_MAX
#endif

#if __POSIX_VISIBLE >= 200809
#ifndef _LOCALE_T_DEFINED_
#define _LOCALE_T_DEFINED_
typedef void *locale_t;
#endif
#endif

#endif /* !_WCHAR_H */
