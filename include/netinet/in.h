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

#define INET_ADDRSTRLEN 16

__BEGIN_DECLS
typedef uint16_t in_port_t;

/* TODO: implement bindresvport in Rust */
int bindresvport(int, struct sockaddr_in*);
__END_DECLS

#endif /* !_NETINET_IN_H */
