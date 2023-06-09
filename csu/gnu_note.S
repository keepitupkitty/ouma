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

	.section ".note.ABI-tag", "a"
	.p2align 2
	.long 1f - 0f		/* name length */
	.long 3f - 2f		/* data length */
	.long  1		/* note type */
0:	.asciz "GNU"		/* vendor name */
1:	.p2align 2
2:	.long 0			/* note data: the ABI tag */
	.long 6, 1, 0
3:	.p2align 2		/* pad out section */
