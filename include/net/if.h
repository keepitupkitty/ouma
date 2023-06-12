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

#ifndef _NET_IF_H
#define _NET_IF_H

#if __BSD_VISIBLE
enum {
  IFF_UP = 0x1,
#define IFF_UP IFF_UP
  IFF_BROADCAST = 0x2,
#define IFF_BROADCAST IFF_BROADCAST
  IFF_DEBUG = 0x4,
#define IFF_DEBUG IFF_DEBUG
  IFF_LOOPBACK = 0x8,
#define IFF_LOOPBACK IFF_LOOPBACK
  IFF_POINTOPOINT = 0x10,
#define IFF_POINTOPOINT IFF_POINTOPOINT
  IFF_NOTRAILERS = 0x20,
#define IFF_NOTRAILERS IFF_NOTRAILERS
  IFF_RUNNING = 0x40,
#define IFF_RUNNING IFF_RUNNING
  IFF_NOARP = 0x80,
#define IFF_NOARP IFF_NOARP
  IFF_PROMISC = 0x100,
#define IFF_PROMISC IFF_PROMISC

  IFF_ALLMULTI = 0x200,
#define IFF_ALLMULTI IFF_ALLMULTI

  IFF_MASTER = 0x400,
#define IFF_MASTER IFF_MASTER
  IFF_SLAVE = 0x800,
#define IFF_SLAVE IFF_SLAVE

  IFF_MULTICAST = 0x1000,
#define IFF_MULTICAST IFF_MULTICAST

  IFF_PORTSEL = 0x2000,
#define IFF_PORTSEL IFF_PORTSEL
  IFF_AUTOMEDIA = 0x4000,
#define IFF_AUTOMEDIA IFF_AUTOMEDIA
  IFF_DYNAMIC = 0x8000
#define IFF_DYNAMIC IFF_DYNAMIC
};

struct ifaddr {
  struct sockaddr ifa_addr;
  union {
    struct sockaddr ifu_broadaddr;
    struct sockaddr ifu_dstaddr;
  } ifa_ifu;
  struct iface *ifa_ifp;
  struct ifaddr *ifa_next;
};

#define ifa_broadaddr ifa_ifu.ifu_broadaddr
#define ifa_dstaddr ifa_ifu.ifu_dstaddr

struct ifmap {
  unsigned long int mem_start;
  unsigned long int mem_end;
  unsigned short int base_addr;
  unsigned char irq;
  unsigned char dma;
  unsigned char port;
};

struct ifreq {
#define IFHWADDRLEN 6
#define IFNAMSIZ IF_NAMESIZE
  union {
    char ifrn_name[IFNAMSIZ];
  } ifr_ifrn;

  union {
    struct sockaddr ifru_addr;
    struct sockaddr ifru_dstaddr;
    struct sockaddr ifru_broadaddr;
    struct sockaddr ifru_netmask;
    struct sockaddr ifru_hwaddr;
    short int ifru_flags;
    int ifru_ivalue;
    int ifru_mtu;
    struct ifmap ifru_map;
    char ifru_slave[IFNAMSIZ];
    char ifru_newname[IFNAMSIZ];
    __caddr_t ifru_data;
  } ifr_ifru;
};

#define ifr_name ifr_ifrn.ifrn_name
#define ifr_hwaddr ifr_ifru.ifru_hwaddr
#define ifr_addr ifr_ifru.ifru_addr
#define ifr_dstaddr ifr_ifru.ifru_dstaddr
#define ifr_broadaddr ifr_ifru.ifru_broadaddr
#define ifr_netmask ifr_ifru.ifru_netmask
#define ifr_flags ifr_ifru.ifru_flags
#define ifr_metric ifr_ifru.ifru_ivalue
#define ifr_mtu ifr_ifru.ifru_mtu
#define ifr_map ifr_ifru.ifru_map
#define ifr_slave ifr_ifru.ifru_slave
#define ifr_data ifr_ifru.ifru_data
#define ifr_ifindex ifr_ifru.ifru_ivalue
#define ifr_bandwidth ifr_ifru.ifru_ivalue
#define ifr_qlen ifr_ifru.ifru_ivalue
#define ifr_newname ifr_ifru.ifru_newname
#define _IOT_ifreq _IOT(_IOTS(char), IFNAMSIZ, _IOTS(char), 16, 0, 0)
#define _IOT_ifreq_short _IOT(_IOTS(char), IFNAMSIZ, _IOTS(short), 1, 0, 0)
#define _IOT_ifreq_int _IOT(_IOTS(char), IFNAMSIZ, _IOTS(int), 1, 0, 0)

struct ifconf {
  int ifc_len;
  union {
    __caddr_t ifcu_buf;
    struct ifreq *ifcu_req;
  } ifc_ifcu;
};

#define ifc_buf ifc_ifcu.ifcu_buf
#define ifc_req ifc_ifcu.ifcu_req
#define _IOT_ifconf _IOT(_IOTS(struct ifconf), 1, 0, 0, 0, 0)
#endif /* !__BSD_VISIBLE */

__BEGIN_DECLS
// TODO: implement those in rust
void if_freenameindex(struct if_nameindex *);
char *if_indextoname(unsigned int, char *);
struct if_nameindex *if_nameindex(void);
unsigned int if_nametoindex(const char *);
__END_DECLS
#endif /* !_NET_IF_H */
