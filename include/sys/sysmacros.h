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

#ifndef _SYS_SYSMACROS_H_
#define _SYS_SYSMACROS_H_

#define major(x)                                                               \
  ((unsigned)((((x) >> 31 >> 1) & 0xfffff000) | (((x) >> 8) & 0x00000fff)))
#define minor(x) ((unsigned)((((x) >> 12) & 0xffffff00) | ((x)&0x000000ff)))

#define makedev(x, y) ( \
        (((x)&0xfffff000ULL) << 32) | \
	(((x)&0x00000fffULL) << 8) | \
        (((y)&0xffffff00ULL) << 12) | \
	(((y)&0x000000ffULL))

#endif /* !_SYS_SYSMACROS_H_ */
