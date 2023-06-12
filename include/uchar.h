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

#ifndef _UCHAR_H
#define _UCHAR_H

#include <sys/_maintypes.h>
#include <sys/cdefs.h>

#ifndef _CHAR16_T_DECLARED
typedef __char16_t char16_t;
#define _CHAR16_T_DECLARED
#endif

#ifndef _CHAR32_T_DECLARED
typedef __char32_t char32_t;
#define _CHAR32_T_DECLARED
#endif

#ifndef _MBSTATE_T_DECLARED
typedef __mbstate_t mbstate_t;
#define _MBSTATE_T_DECLARED
#endif

#ifndef _SIZE_T_DECLARED
typedef __size_t size_t;
#define _SIZE_T_DECLARED
#endif

__BEGIN_DECLS
size_t c16rtomb(char *__restrict, char16_t, mbstate_t *__restrict);
size_t c32rtomb(char *__restrict, char32_t, mbstate_t *__restrict);
size_t mbrtoc16(char16_t *__restrict, const char *__restrict, size_t,
                mbstate_t *__restrict);
size_t mbrtoc32(char32_t *__restrict, const char *__restrict, size_t,
                mbstate_t *__restrict);
__END_DECLS

#endif /* !_UCHAR_H */
