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

#ifndef _SETJMP_H
#define _SETJMP_H

#include <machine/_setjmp.h>
#include <sys/cdefs.h>

typedef long sigjmp_buf[_JBLEN + 1];
typedef long jmp_buf[_JBLEN];

__BEGIN_DECLS
#if __XSI_VISIBLE >= 600
void _longjmp(jmp_buf, int) __dead2;
int _setjmp(jmp_buf) __returns_twice;
#endif
void longjmp(jmp_buf, int) __dead2;
int setjmp(jmp_buf) __returns_twice;
#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L)
#define setjmp(__env) setjmp(__env)
#endif
#if __POSIX_VISIBLE || __XSI_VISIBLE
void siglongjmp(sigjmp_buf, int) __dead2;
int sigsetjmp(sigjmp_buf, int) __returns_twice;
#endif
__END_DECLS

#endif /* !_SETJMP_H */
