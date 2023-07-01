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

#ifndef _SYS__MAINTYPES_H
#define _SYS__MAINTYPES_H

#include <sys/cdefs.h>

/*
 * Basic types upon which most other types are built.
 *
 * Note: It would be nice to simply use the compiler-provided __FOO_TYPE__
 * macros. However, in order to do so we have to check that those match the
 * previous typedefs exactly (not just that they have the same size) since any
 * change would be an ABI break. For example, changing `long` to `long long`
 * results in different C++ name mangling.
 */
typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef short __int16_t;
typedef unsigned short __uint16_t;
typedef int __int32_t;
typedef unsigned int __uint32_t;
#if __SIZEOF_LONG__ == 8
typedef long __int64_t;
typedef unsigned long __uint64_t;
#elif __SIZEOF_LONG__ == 4
__extension__ typedef long long __int64_t;
__extension__ typedef unsigned long long __uint64_t;
#else
#error unsupported long size
#endif

typedef __int8_t __int_least8_t;
typedef __int16_t __int_least16_t;
typedef __int32_t __int_least32_t;
typedef __int64_t __int_least64_t;
typedef __int64_t __intmax_t;
typedef __uint8_t __uint_least8_t;
typedef __uint16_t __uint_least16_t;
typedef __uint32_t __uint_least32_t;
typedef __uint64_t __uint_least64_t;
typedef __uint64_t __uintmax_t;

#if __SIZEOF_POINTER__ == 8
typedef __int64_t __intptr_t;
typedef __int64_t __intfptr_t;
typedef __uint64_t __uintptr_t;
typedef __uint64_t __uintfptr_t;
#elif __SIZEOF_POINTER__ == 4
typedef __int32_t __intptr_t;
typedef __int32_t __intfptr_t;
typedef __uint32_t __uintptr_t;
typedef __uint32_t __uintfptr_t;
#else
#error unsupported pointer size
#endif

#if __SIZEOF_SIZE_T__ == 8
typedef __uint64_t __size_t; /* sizeof() */
typedef __int64_t __ssize_t; /* byte count or error */
#elif __SIZEOF_SIZE_T__ == 4
typedef __uint32_t __size_t;   /* sizeof() */
typedef __int32_t __ssize_t;   /* byte count or error */
#else
#error unsupported size_t size
#endif

#if __SIZEOF_PTRDIFF_T__ == 8
typedef __int64_t __ptrdiff_t; /* ptr1 - ptr2 */
#elif __SIZEOF_PTRDIFF_T__ == 4
typedef __int32_t __ptrdiff_t; /* ptr1 - ptr2 */
#else
#error unsupported ptrdiff_t size
#endif

/*
 * Target-dependent type definitions.
 */
#include <machine/_maintypes.h>

/* Clang already provides these types as built-ins, but only in C++ mode. */
#if !defined(__clang__) || !defined(__cplusplus)
typedef __uint_least16_t __char16_t;
typedef __uint_least32_t __char32_t;
#endif
/* In C++11, char16_t and char32_t are built-in types. */
#if defined(__cplusplus) && __cplusplus >= 201103L
#define _CHAR16_T_DECLARED
#define _CHAR32_T_DECLARED
#endif

/*
 * Linux-specific types
 */
#include <linux/types.h>

/*
 * Standard type definitions.
 */
typedef __kernel_caddr_t __caddr_t;
typedef __uint32_t __blksize_t;     /* file block size */
typedef __uint64_t __blkcnt_t;      /* file block count */
typedef __kernel_clock_t __clock_t; /* clock */
typedef __kernel_clockid_t __clockid_t;
typedef __kernel_daddr_t __daddr_t; /* disk address */
typedef __uint64_t __fsblkcnt_t;
typedef __uint64_t __fsfilcnt_t;
typedef __kernel_gid32_t __gid_t; /* group id */
typedef __uint64_t __dev_t;       /* device number */
typedef __uint32_t __id_t;        /* can hold a gid_t, pid_t, or uid_t */
typedef __kernel_ino_t __ino_t;   /* inode number */
typedef __kernel_key_t __key_t;   /* IPC key (for Sys V IPC) */
typedef __kernel_mode_t __mode_t; /* permissions */
typedef __uint32_t __nlink_t;     /* link count */
typedef __int64_t __off_t;        /* file offset */
typedef __int64_t __loff_t;
typedef __kernel_pid_t __pid_t;             /* process id */
typedef __int64_t __rlim_t;                 /* resource limit - intentionally */
                                            /* signed, because of legacy code */
                                            /* that uses -1 for RLIM_INFINITY */
typedef __uint32_t __useconds_t;            /* microseconds (unsigned) */
typedef __kernel_suseconds_t __suseconds_t; /* microseconds (signed) */
typedef __kernel_time64_t __time_t;
typedef void **__timer_t;         /* timer_gettime()... */
typedef __kernel_uid32_t __uid_t; /* user id */
typedef __int32_t __fd_mask;
typedef __uint32_t __wint_t;

typedef struct {
  __char16_t __surrogate;
  unsigned int __bytesleft;
  __char32_t __partial;
  __char32_t __lowerbound;
} __mbstate_t;

/*
 * Types for varargs. These are all provided by builtin types these
 * days, so centralize their definition.
 */
typedef __builtin_va_list __va_list; /* internally known to gcc */
#if !defined(__GNUC_VA_LIST) && !defined(__NO_GNUC_VA_LIST)
#define __GNUC_VA_LIST
typedef __va_list __gnuc_va_list; /* compatibility w/GNU headers*/
#endif

/*
 * When the following macro is defined, the system uses 64-bit inode numbers.
 * Programs can use this to avoid including <sys/param.h>, with its associated
 * namespace pollution.
 */
#define __INO64

#endif /* !_SYS__MAINTYPES_H */
