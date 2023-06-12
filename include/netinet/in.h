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

#ifndef _NETINET_IN_H
#define _NETINET_IN_H

#include <linux/socket.h>
#include <sys/cdefs.h>
#include <sys/socket.h>
#define __kernel_sockaddr_storage sockaddr_storage
#include <linux/in.h>
#undef __kernel_sockaddr_storage
#include <endian.h>
#include <linux/in6.h>
#include <linux/ipv6.h>

__BEGIN_DECLS
// TODO: implement them in rust
int setipv4sourcefilter(int, struct in_addr, struct in_addr, uint32_t, uint32_t,
                        struct in_addr *);
int getipv4sourcefilter(int, struct in_addr, struct in_addr, uint32_t *,
                        uint32_t *, struct in_addr *);
int setsourcefilter(int, uint32_t, struct sockaddr *, socklen_t, uint32_t,
                    uint32_t, struct sockaddr_storage *);
int getsourcefilter(int, uint32_t, struct sockaddr *, socklen_t, uint32_t *,
                    uint32_t *, struct sockaddr_storage *);
__END_DECLS

#endif /* !_NETINET_IN_H */
