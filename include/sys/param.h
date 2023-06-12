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

#ifndef _SYS_PARAM_H
#define _SYS_PARAM_H

#include <endian.h> /* Define BYTE_ORDER et al.  */
#include <limits.h>
#include <linux/limits.h>
#include <linux/param.h>
#include <signal.h> /* Define NSIG.  */
#include <sys/_null.h>
#include <sys/types.h>

#define MAXPATHLEN PATH_MAX
#define MAXSYMLINKS 8

/* The following are not really correct but it is a value we used for a
   long time and which seems to be usable.  People should not use NOFILE
   and NCARGS anyway.  */
#define NOFILE 256
#define NCARGS 131072

/* BSD names for some <limits.h> values.  */

#define NBBY CHAR_BIT

#if !defined NGROUPS && defined NGROUPS_MAX
#define NGROUPS NGROUPS_MAX
#endif
#if !defined MAXSYMLINKS && defined SYMLOOP_MAX
#define MAXSYMLINKS SYMLOOP_MAX
#endif
#if !defined CANBSIZ && defined MAX_CANON
#define CANBSIZ MAX_CANON
#endif
#if !defined MAXPATHLEN && defined PATH_MAX
#define MAXPATHLEN PATH_MAX
#endif
#if !defined NOFILE && defined OPEN_MAX
#define NOFILE OPEN_MAX
#endif
#if !defined MAXHOSTNAMELEN && defined HOST_NAME_MAX
#define MAXHOSTNAMELEN HOST_NAME_MAX
#endif
#ifndef NCARGS
#ifdef ARG_MAX
#define NCARGS ARG_MAX
#else
/* ARG_MAX is unlimited, but we define NCARGS for BSD programs that want to
   compare against some fixed limit.  */
#define NCARGS INT_MAX
#endif
#endif

/* Magical constants.  */
#ifndef NOGROUP
#define NOGROUP 65535 /* Marker for empty group set member.  */
#endif
#ifndef NODEV
#define NODEV ((dev_t)-1) /* Non-existent device.  */
#endif

/* Unit of `st_blocks'.  */
#ifndef DEV_BSIZE
#define DEV_BSIZE 512
#endif

/* Bit map related macros.  */
#define setbit(a, i) ((a)[(i) / NBBY] |= 1 << ((i) % NBBY))
#define clrbit(a, i) ((a)[(i) / NBBY] &= ~(1 << ((i) % NBBY)))
#define isset(a, i) ((a)[(i) / NBBY] & (1 << ((i) % NBBY)))
#define isclr(a, i) (((a)[(i) / NBBY] & (1 << ((i) % NBBY))) == 0)

/* Macros for counting and rounding.  */
#ifndef howmany
#define howmany(x, y) (((x) + ((y)-1)) / (y))
#endif
#ifdef __GNUC__
#define roundup(x, y)                                                  \
  (__builtin_constant_p(y) && powerof2(y) ? (((x) + (y)-1) & ~((y)-1)) \
                                          : ((((x) + ((y)-1)) / (y)) * (y)))
#else
#define roundup(x, y) ((((x) + ((y)-1)) / (y)) * (y))
#endif
#define powerof2(x) ((((x)-1) & (x)) == 0)

/* Macros for min/max.  */
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

#endif /* !_SYS_PARAM_H */
