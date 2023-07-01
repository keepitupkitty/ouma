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

#ifndef _MACHINE__SETJMP_H
#define _MACHINE__SETJMP_H

#include <sys/cdefs.h>

#define _JBLEN (32 * sizeof(_BSD_JBSLOT_T_) / sizeof(long))
#define _JB_MAGIC 0
#define _JB_SP 1
#define _JB_X19 2
#define _JB_X20 3
#define _JB_X21 4
#define _JB_X22 5
#define _JB_X23 6
#define _JB_X24 7
#define _JB_X25 8
#define _JB_X26 9
#define _JB_X27 10
#define _JB_X28 11
#define _JB_X29 12
#define _JB_X30 13
#define _JB_D8 16
#define _JB_D9 17
#define _JB_D10 18
#define _JB_D11 19
#define _JB_D12 20
#define _JB_D13 21
#define _JB_D14 22
#define _JB_D15 23
#define _JB_SIGMASK	24

#endif /* !_MACHINE__SETJMP_H */
