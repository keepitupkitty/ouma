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

#ifndef NULL

#if !defined(__cplusplus)
#define NULL ((void *)0)
#else
#if __cplusplus >= 201103L
#define NULL nullptr
#elif defined(__GNUG__) && defined(__GNUC__) && __GNUC__ >= 4
#define NULL __null
#else
#if defined(__LP64__)
#define NULL (0L)
#else
#define NULL 0
#endif /* __LP64__ */
#endif /* __GNUG__ */
#endif /* !__cplusplus */

#endif
