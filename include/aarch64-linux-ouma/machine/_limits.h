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

#ifndef _MACHINE__LIMITS_H_
#define _MACHINE__LIMITS_H_

#include <sys/cdefs.h>

#define __CHAR_BIT 8 /* number of bits in a char */

#define __SCHAR_MAX 0x7f        /* max value for a signed char */
#define __SCHAR_MIN (-0x7f - 1) /* min value for a signed char */

#define __UCHAR_MAX 0xff /* max value for an unsigned char */

#define __USHRT_MAX 0xffff       /* max value for an unsigned short */
#define __SHRT_MAX 0x7fff        /* max value for a short */
#define __SHRT_MIN (-0x7fff - 1) /* min value for a short */

#define __UINT_MAX 0xffffffff       /* max value for an unsigned int */
#define __INT_MAX 0x7fffffff        /* max value for an int */
#define __INT_MIN (-0x7fffffff - 1) /* min value for an int */

#define __ULONG_MAX 0xffffffffffffffffUL      /* max for an unsigned long */
#define __LONG_MAX 0x7fffffffffffffffL        /* max for a long */
#define __LONG_MIN (-0x7fffffffffffffffL - 1) /* min for a long */

/* Long longs have the same size but not the same type as longs. */
/* max for an unsigned long long */
#define __ULLONG_MAX 0xffffffffffffffffULL
#define __LLONG_MAX 0x7fffffffffffffffLL        /* max for a long long */
#define __LLONG_MIN (-0x7fffffffffffffffLL - 1) /* min for a long long */

#define __SSIZE_MAX __LONG_MAX /* max value for a ssize_t */

#define __SIZE_T_MAX __ULONG_MAX /* max value for a size_t */

#define __OFF_MAX __LONG_MAX /* max value for an off_t */
#define __OFF_MIN __LONG_MIN /* min value for an off_t */

#define __LONG_BIT 64
#define __WORD_BIT 32

#endif /* !_MACHINE__LIMITS_H_ */
