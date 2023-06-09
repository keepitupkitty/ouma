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

#ifndef _ERRNO_H_
#define _ERRNO_H_

#include <linux/errno.h>
#include <sys/cdefs.h>

__BEGIN_DECLS
extern _Thread_local int __oumalibc_errno;

#define errno __oumalibc_errno
__END_DECLS

#endif /* !_ERRNO_H_ */
