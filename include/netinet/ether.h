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

#ifndef _NETINET_ETHER_H_
#define _NETINET_ETHER_H_

#include <netinet/if_ether.h>
#include <sys/cdefs.h>

#ifdef _GNU_SOURCE_
// TODO: implement netinet/ether.h in Rust
__BEGIN_DECLS
struct ether_addr *ether_aton(const char *);
struct ether_addr *ether_aton_r(const char *, struct ether_addr *);
char *ether_ntoa(const struct ether_addr *);
char *ether_ntoa_r(const struct ether_addr *, char *);
int ether_ntohost(char *, const struct ether_addr *);
int ether_hostton(const char *, struct ether_addr *);
int ether_line(const char *, struct ether_addr *, char *);
__END_DECLS
#endif /* !_GNU_SOURCE_ */

#endif /* !_NETINET_ETHER_H_ */
