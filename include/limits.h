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

#ifndef _LIMITS_H
#define _LIMITS_H

#include <sys/cdefs.h>

#if __POSIX_VISIBLE
#define _POSIX_ARG_MAX 4096
#define _POSIX_LINK_MAX 8
#define _POSIX_MAX_CANON 255
#define _POSIX_MAX_INPUT 255
#define _POSIX_NAME_MAX 14
#define _POSIX_PIPE_BUF 512
#define _POSIX_SSIZE_MAX 32767
#define _POSIX_STREAM_MAX 8

#if __POSIX_VISIBLE >= 200112
#define _POSIX_CHILD_MAX 25
#define _POSIX_NGROUPS_MAX 8
#define _POSIX_OPEN_MAX 20
#define _POSIX_PATH_MAX 256
#define _POSIX_TZNAME_MAX 6
#else
#define _POSIX_CHILD_MAX 6
#define _POSIX_NGROUPS_MAX 0
#define _POSIX_OPEN_MAX 16
#define _POSIX_PATH_MAX 255
#define _POSIX_TZNAME_MAX 3
#endif

#if __POSIX_VISIBLE >= 200112
#define BC_BASE_MAX 99        /* max ibase/obase values in bc(1) */
#define BC_DIM_MAX 2048       /* max array elements in bc(1) */
#define BC_SCALE_MAX 99       /* max scale value in bc(1) */
#define BC_STRING_MAX 1000    /* max const string length in bc(1) */
#define CHARCLASS_NAME_MAX 14 /* max character class name size */
#define COLL_WEIGHTS_MAX 10   /* max weights for order keyword */
#define EXPR_NEST_MAX 32      /* max expressions nested in expr(1) */
#define LINE_MAX 2048         /* max bytes in an input line */
#define RE_DUP_MAX 255        /* max RE's in interval notation */

#define _POSIX2_BC_BASE_MAX 99
#define _POSIX2_BC_DIM_MAX 2048
#define _POSIX2_BC_SCALE_MAX 99
#define _POSIX2_BC_STRING_MAX 1000
#define _POSIX2_CHARCLASS_NAME_MAX 14
#define _POSIX2_COLL_WEIGHTS_MAX 2
#define _POSIX2_EQUIV_CLASS_MAX 2
#define _POSIX2_EXPR_NEST_MAX 32
#define _POSIX2_LINE_MAX 2048
#define _POSIX2_RE_DUP_MAX 255
#endif
#endif

#if __POSIX_VISIBLE >= 199309
#define _POSIX_AIO_LISTIO_MAX 2
#define _POSIX_AIO_MAX 1
#define _POSIX_DELAYTIMER_MAX 32
#define _POSIX_MQ_OPEN_MAX 8
#define _POSIX_MQ_PRIO_MAX 32
#define _POSIX_RTSIG_MAX 8
#define _POSIX_SEM_NSEMS_MAX 256
#define _POSIX_SEM_VALUE_MAX 32767
#define _POSIX_SIGQUEUE_MAX 32
#define _POSIX_TIMER_MAX 32

#define _POSIX_CLOCKRES_MIN 20000000
#endif

#if __POSIX_VISIBLE >= 199506
#define _POSIX_THREAD_DESTRUCTOR_ITERATIONS 4
#define _POSIX_THREAD_KEYS_MAX 128
#define _POSIX_THREAD_THREADS_MAX 64
#endif

#if __POSIX_VISIBLE >= 200112
#define _POSIX_HOST_NAME_MAX 255
#define _POSIX_LOGIN_NAME_MAX 9
#define _POSIX_SS_REPL_MAX 4
#define _POSIX_SYMLINK_MAX 255
#define _POSIX_SYMLOOP_MAX 8
#define _POSIX_TRACE_EVENT_NAME_MAX 30
#define _POSIX_TRACE_NAME_MAX 8
#define _POSIX_TRACE_SYS_MAX 8
#define _POSIX_TRACE_USER_EVENT_MAX 32
#define _POSIX_TTY_NAME_MAX 9

#define _POSIX_RE_DUP_MAX _POSIX2_RE_DUP_MAX
#endif

#include <machine/_limits.h>

#define CHAR_BIT __CHAR_BIT /* number of bits in a char */

#define SCHAR_MAX __SCHAR_MAX /* max value for a signed char */
#define SCHAR_MIN __SCHAR_MIN /* min value for a signed char */

#define UCHAR_MAX __UCHAR_MAX /* max value for an unsigned char */

#ifdef __CHAR_UNSIGNED__
#define CHAR_MAX UCHAR_MAX /* max value for a char */
#define CHAR_MIN 0         /* min value for a char */
#else
#define CHAR_MAX SCHAR_MAX
#define CHAR_MIN SCHAR_MIN
#endif

#define USHRT_MAX __USHRT_MAX /* max value for an unsigned short */
#define SHRT_MAX __SHRT_MAX   /* max value for a short */
#define SHRT_MIN __SHRT_MIN   /* min value for a short */

#define UINT_MAX __UINT_MAX /* max value for an unsigned int */
#define INT_MAX __INT_MAX   /* max value for an int */
#define INT_MIN __INT_MIN   /* min value for an int */

#define ULONG_MAX __ULONG_MAX /* max for an unsigned long */
#define LONG_MAX __LONG_MAX   /* max for a long */
#define LONG_MIN __LONG_MIN   /* min for a long */

#ifdef __LONG_LONG_SUPPORTED
#define ULLONG_MAX __ULLONG_MAX /* max for an unsigned long long */
#define LLONG_MAX __LLONG_MAX   /* max for a long long */
#define LLONG_MIN __LLONG_MIN   /* min for a long long */
#endif

#if __POSIX_VISIBLE || __XSI_VISIBLE
#define SSIZE_MAX __SSIZE_MAX /* max value for an ssize_t */
#endif

#if __POSIX_VISIBLE >= 200112 || __XSI_VISIBLE
#define SIZE_T_MAX __SIZE_T_MAX /* max value for a size_t */

#define OFF_MAX __OFF_MAX /* max value for an off_t */
#define OFF_MIN __OFF_MIN /* min value for an off_t */
#endif

#if __XSI_VISIBLE || __POSIX_VISIBLE >= 200809
#define LONG_BIT __LONG_BIT
#define WORD_BIT __WORD_BIT
#endif

#if __XSI_VISIBLE || __POSIX_VISIBLE >= 200809
#define NL_ARGMAX _POSIX_ARG_MAX /* max # of position args for printf */
#define NL_MSGMAX INT_MAX
#define NL_SETMAX INT_MAX
#define NL_TEXTMAX INT_MAX
#endif

#if __XSI_VISIBLE
#define NL_LANGMAX _POSIX2_LINE_MAX /* max LANG name length */
#endif

#include <linux/limits.h>

#ifdef _GNU_SOURCE
#define _POSIX_FD_SETSIZE _POSIX_OPEN_MAX
#define _POSIX_QLIMIT 1
#define _POSIX_HIWAT _POSIX_PIPE_BUF
#define NL_NMAX INT_MAX
#endif

#define MB_LEN_MAX 16 /* 31-bit UTF-8 */
#define NZERO 20

#define IOV_MAX 1024 /* max elements in i/o vector */
#define MQ_PRIO_MAX 32768
#define SEM_VALUE_MAX 0x3fffffff
#define AIO_PRIO_DELTA_MAX 20

#define PTHREAD_DESTRUCTOR_ITERATIONS 4
#define PTHREAD_KEYS_MAX 128

#undef PTHREAD_THREADS_MAX

#define DELAYTIMER_MAX 2147483647
#define TTY_NAME_MAX 32
#define LOGIN_NAME_MAX 256
#define HOST_NAME_MAX _POSIX_HOST_NAME_MAX

#include <machine/_pthread_stack_min.h>

#endif /* !_LIMITS_H */
