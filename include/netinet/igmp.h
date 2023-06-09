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

#ifndef _NETINET_IGMP_H_
#define _NETINET_IGMP_H_

#ifdef _GNU_SOURCE_
#include <netinet/in.h>

__BEGIN_DECLS
/*
 * Copyright (c) 1988 Stephen Deering.
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Stephen Deering of Stanford University.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)igmp.h	8.1 (Berkeley) 6/10/93
 *	$FreeBSD$
 */

struct igmp {
  uint8_t igmp_type;         /* IGMP type */
  uint8_t igmp_code;         /* routing code */
  uint16_t igmp_cksum;       /* checksum */
  struct in_addr igmp_group; /* group address */
};

#define IGMP_MINLEN 8

/*
 * Message types, including version number.
 */
#define IGMP_MEMBERSHIP_QUERY 0x11     /* membership query         */
#define IGMP_V1_MEMBERSHIP_REPORT 0x12 /* Ver. 1 membership report */
#define IGMP_V2_MEMBERSHIP_REPORT 0x16 /* Ver. 2 membership report */
#define IGMP_V2_LEAVE_GROUP 0x17       /* Leave-group message	    */

#define IGMP_DVMRP 0x13 /* DVMRP routing message    */
#define IGMP_PIM 0x14   /* PIM routing message      */
#define IGMP_TRACE 0x15

#define IGMP_MTRACE_RESP 0x1e /* traceroute resp.(to sender)*/
#define IGMP_MTRACE 0x1f      /* mcast traceroute messages  */
#define IGMP_MRDISC_ADV 0x30  /* From RFC4286.  */

#define IGMP_MAX_HOST_REPORT_DELAY 10 /* max delay for response to     */
                                      /*  query (in seconds) according */
                                      /*  to RFC1112                   */
#define IGMP_TIMER_SCALE 10           /* denotes that the igmp code field */
                                      /* specifies time in 10th of seconds*/

/*
 * States for the IGMP v2 state table.
 */
#define IGMP_DELAYING_MEMBER 1
#define IGMP_IDLE_MEMBER 2
#define IGMP_LAZY_MEMBER 3
#define IGMP_SLEEPING_MEMBER 4
#define IGMP_AWAKENING_MEMBER 5

/*
 * States for IGMP router version cache.
 */
#define IGMP_v1_ROUTER 1
#define IGMP_v2_ROUTER 2

/*
 * The following four defininitions are for backwards compatibility.
 * They should be removed as soon as all applications are updated to
 * use the new constant names.
 */
#define IGMP_HOST_MEMBERSHIP_QUERY IGMP_MEMBERSHIP_QUERY
#define IGMP_HOST_MEMBERSHIP_REPORT IGMP_V1_MEMBERSHIP_REPORT
#define IGMP_HOST_NEW_MEMBERSHIP_REPORT IGMP_V2_MEMBERSHIP_REPORT
#define IGMP_HOST_LEAVE_MESSAGE IGMP_V2_LEAVE_GROUP
__END_DECLS
#endif /* !_GNU_SOURCE_ */

#endif /* !_NETINET_IGMP_H_ */
