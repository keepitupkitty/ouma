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

#define LENTRY(sym)     \
  .text;                \
  .align 2;             \
  .type sym, #function; \
  sym:                  \
  .cfi_startproc
#define ENTRY(sym) \
  .globl sym;      \
  LENTRY(sym)
#define LEND(sym) \
  .ltorg;         \
  .cfi_endproc;   \
  .size sym, .- sym
#define END(sym) LEND(sym)

#if defined(PIC)
#define PIC_SYM(x, y) x##@##y
#else
#define PIC_SYM(x, y) x
#endif

/* Alias for link register x30 */
#define lr x30

#endif /* !_MACHINE_ASSEMBLY_H */
