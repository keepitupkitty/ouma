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

#ifndef _ARPA_INET_H
#define _ARPA_INET_H

#include <sys/_maintypes.h>
#include <sys/cdefs.h>

/* Required for byteorder(3) functions. */
#include <machine/endian.h>

#define INET_ADDRSTRLEN 16
#define INET6_ADDRSTRLEN 46

#ifndef _UINT16_T_DECLARED
typedef __uint16_t uint16_t;
#define _UINT16_T_DECLARED
#endif

#ifndef _UINT32_T_DECLARED
typedef __uint32_t uint32_t;
#define _UINT32_T_DECLARED
#endif

#ifndef _IN_ADDR_T_DECLARED
typedef uint32_t in_addr_t;
#define _IN_ADDR_T_DECLARED
#endif

#ifndef _IN_PORT_T_DECLARED
typedef uint16_t in_port_t;
#define _IN_PORT_T_DECLARED
#endif

#if __BSD_VISIBLE
#ifndef _SIZE_T_DECLARED
typedef __size_t size_t;
#define _SIZE_T_DECLARED
#endif
#endif

/*
 * XXX socklen_t is used by a POSIX.1-2001 interface, but not required by
 * POSIX.1-2001.
 */
#ifndef _SOCKLEN_T_DECLARED
typedef __socklen_t socklen_t;
#define _SOCKLEN_T_DECLARED
#endif

#ifndef _STRUCT_IN_ADDR_DECLARED
struct in_addr {
  in_addr_t s_addr;
};
#define _STRUCT_IN_ADDR_DECLARED
#endif

__BEGIN_DECLS
// TODO: implement those in rust
in_addr_t inet_addr(const char *);
in_addr_t inet_lnaof(struct in_addr);
struct in_addr inet_makeaddr(in_addr_t, in_addr_t);
in_addr_t inet_netof(struct in_addr);
in_addr_t inet_network(const char *);
char *inet_ntoa(struct in_addr);
int inet_pton(int, const char *__restrict, void *__restrict);
const char *inet_ntop(int, const void *__restrict, char *__restrict, socklen_t);
__END_DECLS

#endif /* !_ARPA_INET_H */
