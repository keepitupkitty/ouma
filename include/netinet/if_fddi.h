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

#ifndef _NETINET_IF_FDDI_H_
#define _NETINET_IF_FDDI_H_

#include <linux/if_fddi.h>
#include <stdint.h>
#include <sys/types.h>

#ifdef _GNU_SOURCE_

struct fddi_header {
  uint8_t fddi_fc;                 /* Frame Control (FC) value */
  uint8_t fddi_dhost[FDDI_K_ALEN]; /* Destination host */
  uint8_t fddi_shost[FDDI_K_ALEN]; /* Source host */
};
#endif /* !_GNU_SOURCE_ */

#endif /* !_NETINET_IF_FDDI_H_ */
