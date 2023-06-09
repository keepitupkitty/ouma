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

#ifndef _MACHINE__MAINTYPES_H_
#define _MACHINE__MAINTYPES_H_

#include <sys/cdefs.h>

#include <machine/_limits.h>

#define __NO_STRICT_ALIGNMENT

/*
 * Standard type definitions.
 */
typedef __int32_t __int_fast8_t;
typedef __int32_t __int_fast16_t;
typedef __int32_t __int_fast32_t;
typedef __int64_t __int_fast64_t;
typedef __uint32_t __uint_fast8_t;
typedef __uint32_t __uint_fast16_t;
typedef __uint32_t __uint_fast32_t;
typedef __uint64_t __uint_fast64_t;
typedef int ___wchar_t;

#define __WCHAR_MIN __INT_MIN /* min value for a wchar_t */
#define __WCHAR_MAX __INT_MAX /* max value for a wchar_t */

#endif /* !_MACHINE__MAINTYPES_H_ */
