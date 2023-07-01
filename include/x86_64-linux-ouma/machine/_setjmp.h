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

#define _JB_RBX 0
#define _JB_RBP 1
#define _JB_R12 2
#define _JB_R13 3
#define _JB_R14 4
#define _JB_R15 5
#define _JB_RSP 6
#define _JB_PC 7
#define _JB_SIGFLAG 8
#define _JB_SIGMASK 9
#define _JBLEN 11

#endif /* !_MACHINE__SETJMP_H */
