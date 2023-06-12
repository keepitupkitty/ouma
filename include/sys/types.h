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

#ifndef _SYS_TYPES_H
#define _SYS_TYPES_H

#include <stddef.h>
#include <stdint.h>
#include <sys/cdefs.h>

#if __BSD_VISIBLE
typedef unsigned char u_char;
typedef unsigned short u_short;
typedef unsigned int u_int;
typedef unsigned long u_long;
#endif

#include <sys/_maintypes.h>

typedef __uint8_t u_int8_t; /* unsigned integrals (deprecated) */
typedef __uint16_t u_int16_t;
typedef __uint32_t u_int32_t;
typedef __uint64_t u_int64_t;

#ifndef _CADDR_T_DECLARED
typedef __caddr_t caddr_t;
#define _CADDR_T_DECLARED
#endif

#ifndef _BLKSIZE_T_DECLARED
typedef __blksize_t blksize_t;
#define _BLKSIZE_T_DECLARED
#endif

#ifndef _BLKCNT_T_DECLARED
typedef __blkcnt_t blkcnt_t;
#define _BLKCNT_T_DECLARED
#endif

#ifndef _CLOCK_T_DECLARED
typedef __clock_t clock_t;
#define _CLOCK_T_DECLARED
#endif

#ifndef _CLOCKID_T_DECLARED
typedef __clockid_t clockid_t;
#define _CLOCKID_T_DECLARED
#endif

#ifndef _DADDR_T_DECLARED
typedef __daddr_t daddr_t; /* disk address */
#define _DADDR_T_DECLARED
#endif

#ifndef _DEV_T_DECLARED
typedef __dev_t dev_t; /* device number or struct cdev */
#define _DEV_T_DECLARED
#endif

#ifndef _FSBLKCNT_T_DECLARED /* for statvfs() */
typedef __fsblkcnt_t fsblkcnt_t;
typedef __fsfilcnt_t fsfilcnt_t;
#define _FSBLKCNT_T_DECLARED
#endif

#ifndef _GID_T_DECLARED
typedef __gid_t gid_t; /* group id */
#define _GID_T_DECLARED
#endif

#ifndef _IN_ADDR_T_DECLARED
typedef __uint32_t in_addr_t; /* base type for internet address */
#define _IN_ADDR_T_DECLARED
#endif

#ifndef _IN_PORT_T_DECLARED
typedef __uint16_t in_port_t;
#define _IN_PORT_T_DECLARED
#endif

#ifndef _ID_T_DECLARED
typedef __id_t id_t; /* can hold a uid_t or pid_t */
#define _ID_T_DECLARED
#endif

#ifndef _INO_T_DECLARED
typedef __ino_t ino_t; /* inode number */
#define _INO_T_DECLARED
#endif

#ifndef _KEY_T_DECLARED
typedef __key_t key_t; /* IPC key (for Sys V IPC) */
#define _KEY_T_DECLARED
#endif

#ifndef _MODE_T_DECLARED
typedef __mode_t mode_t; /* permissions */
#define _MODE_T_DECLARED
#endif

#ifndef _NLINK_T_DECLARED
typedef __nlink_t nlink_t; /* link count */
#define _NLINK_T_DECLARED
#endif

#ifndef _OFF_T_DECLARED
typedef __off_t off_t; /* file offset */
#define _OFF_T_DECLARED
#endif

#ifndef _LOFF_T_DECLARED
typedef __loff_t loff_t;
#define _LOFF_T_DECLARED
#endif

#ifndef _PID_T_DECLARED
typedef __pid_t pid_t; /* process id */
#define _PID_T_DECLARED
#endif

#ifndef _RLIM_T_DECLARED
typedef __rlim_t rlim_t; /* resource limit */
#define _RLIM_T_DECLARED
#endif

#ifndef _SIZE_T_DECLARED
typedef __size_t size_t;
#define _SIZE_T_DECLARED
#endif

#ifndef _SSIZE_T_DECLARED
typedef __ssize_t ssize_t;
#define _SSIZE_T_DECLARED
#endif

#ifndef _SUSECONDS_T_DECLARED
typedef __suseconds_t suseconds_t; /* microseconds (signed) */
#define _SUSECONDS_T_DECLARED
#endif

#ifndef _TIME_T_DECLARED
typedef __time_t time_t;
#define _TIME_T_DECLARED
#endif

#ifndef _TIMER_T_DECLARED
typedef __timer_t timer_t;
#define _TIMER_T_DECLARED
#endif

#ifndef _UID_T_DECLARED
typedef __uid_t uid_t; /* user id */
#define _UID_T_DECLARED
#endif

#ifndef _USECONDS_T_DECLARED
typedef __useconds_t useconds_t; /* microseconds (unsigned) */
#define _USECONDS_T_DECLARED
#endif

#ifndef _FD_MASK_DECLARED
typedef __fd_mask fd_mask;
#define _FD_MASK_DECLARED
#endif

typedef struct {
  int __val[2];
} fsid_t;

#endif /* _SYS_TYPES_H */
