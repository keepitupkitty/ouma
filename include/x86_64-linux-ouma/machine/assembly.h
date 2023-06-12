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

#ifndef _MACHINE_ASSEMBLY_H
#define _MACHINE_ASSEMBLY_H

#ifdef PIC
#define PIC_PLT(x) x @PLT
#define PIC_GOT(x) x @GOTPCREL(% rip)
#else
#define PIC_PLT(x) x
#endif

/*
 * CNAME and HIDENAME manage the relationship between symbol names in C
 * and the equivalent assembly language names.  CNAME is given a name as
 * it would be used in a C program.  It expands to the equivalent assembly
 * language name.  HIDENAME is given an assembly-language name, and expands
 * to a possibly-modified form that will be invisible to C programs.
 */
#define CNAME(csym) csym
#define HIDENAME(asmsym) .asmsym

#define _START_ENTRY \
  .text;             \
  .p2align 4, 0x90

#define ENTRY(x)             \
  _START_ENTRY;              \
  .globl CNAME(x);           \
  .type CNAME(x), @function; \
  CNAME(x) :;                \
  .cfi_startproc
#define END(x)   \
  .size x, .- x; \
  .cfi_endproc

#endif /* !_MACHINE_ASSEMBLY_H */
