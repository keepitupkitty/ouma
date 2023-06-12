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

#ifndef _ASSERT_H
#define _ASSERT_H

#include <sys/cdefs.h>

#ifdef NDEBUG
#define assert(e) ((void)0)
#define _assert(e) ((void)0)
#else
#define _assert(e) assert(e)
#define assert(e) \
  ((e) ? (void)0 : __oumalibc_assert(__FILE__, __LINE__, __func__, #e))
#endif

/*
 * Static assertions.  In principle we could define static_assert for
 * C++ older than C++11, but this breaks if _Static_assert is
 * implemented as a macro.
 *
 * C++ template parameters may contain commas, even if not enclosed in
 * parentheses, causing the _Static_assert macro to be invoked with more
 * than two parameters.
 */
#if __ISO_C_VISIBLE >= 2011 && !defined(__cplusplus)
#define static_assert _Static_assert
#endif

__BEGIN_DECLS
void __oumalibc_assert(const char *, int, const char *, const char *);
__END_DECLS

#endif /* !_ASSERT_H */
