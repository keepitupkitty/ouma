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

#ifndef _NETINET_IF_FDDI_H
#define _NETINET_IF_FDDI_H

#include <linux/if_fddi.h>
#include <stdint.h>
#include <sys/types.h>

#if defined(__BSD_VISIBLE_)
struct fddi_header {
  uint8_t fddi_fc;
  uint8_t fddi_dhost[FDDI_K_ALEN];
  uint8_t fddi_shost[FDDI_K_ALEN];
};
#endif

#endif /* !_NETINET_IF_FDDI_H */
