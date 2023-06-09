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

#ifndef _ELF_H_
#define _ELF_H_

#include <stdint.h>

typedef uint16_t Elf32_Half;
typedef uint16_t Elf64_Half;

typedef uint32_t Elf32_Word;
typedef int32_t Elf32_Sword;
typedef uint32_t Elf64_Word;
typedef int32_t Elf64_Sword;

typedef uint64_t Elf32_Xword;
typedef int64_t Elf32_Sxword;
typedef uint64_t Elf64_Xword;
typedef int64_t Elf64_Sxword;

typedef uint32_t Elf32_Addr;
typedef uint64_t Elf64_Addr;

typedef uint32_t Elf32_Off;
typedef uint64_t Elf64_Off;

typedef uint16_t Elf32_Section;
typedef uint16_t Elf64_Section;

typedef Elf32_Half Elf32_Versym;
typedef Elf64_Half Elf64_Versym;

#define EI_NIDENT (16)

typedef struct {
  unsigned char e_ident[EI_NIDENT]; /* Magic number and other info */
  Elf32_Half e_type;                /* Object file type */
  Elf32_Half e_machine;             /* Architecture */
  Elf32_Word e_version;             /* Object file version */
  Elf32_Addr e_entry;               /* Entry point virtual address */
  Elf32_Off e_phoff;                /* Program header table file offset */
  Elf32_Off e_shoff;                /* Section header table file offset */
  Elf32_Word e_flags;               /* Processor-specific flags */
  Elf32_Half e_ehsize;              /* ELF header size in bytes */
  Elf32_Half e_phentsize;           /* Program header table entry size */
  Elf32_Half e_phnum;               /* Program header table entry count */
  Elf32_Half e_shentsize;           /* Section header table entry size */
  Elf32_Half e_shnum;               /* Section header table entry count */
  Elf32_Half e_shstrndx;            /* Section header string table index */
} Elf32_Ehdr;

typedef struct {
  unsigned char e_ident[EI_NIDENT]; /* Magic number and other info */
  Elf64_Half e_type;                /* Object file type */
  Elf64_Half e_machine;             /* Architecture */
  Elf64_Word e_version;             /* Object file version */
  Elf64_Addr e_entry;               /* Entry point virtual address */
  Elf64_Off e_phoff;                /* Program header table file offset */
  Elf64_Off e_shoff;                /* Section header table file offset */
  Elf64_Word e_flags;               /* Processor-specific flags */
  Elf64_Half e_ehsize;              /* ELF header size in bytes */
  Elf64_Half e_phentsize;           /* Program header table entry size */
  Elf64_Half e_phnum;               /* Program header table entry count */
  Elf64_Half e_shentsize;           /* Section header table entry size */
  Elf64_Half e_shnum;               /* Section header table entry count */
  Elf64_Half e_shstrndx;            /* Section header string table index */
} Elf64_Ehdr;

#define EI_MAG0 0    /* File identification byte 0 index */
#define ELFMAG0 0x7f /* Magic number byte 0 */

#define EI_MAG1 1   /* File identification byte 1 index */
#define ELFMAG1 'E' /* Magic number byte 1 */

#define EI_MAG2 2   /* File identification byte 2 index */
#define ELFMAG2 'L' /* Magic number byte 2 */

#define EI_MAG3 3   /* File identification byte 3 index */
#define ELFMAG3 'F' /* Magic number byte 3 */

/* Conglomeration of the identification bytes, for easy testing as a word.  */
#define ELFMAG "\177ELF"
#define SELFMAG 4

#define EI_CLASS 4     /* File class byte index */
#define ELFCLASSNONE 0 /* Invalid class */
#define ELFCLASS32 1   /* 32-bit objects */
#define ELFCLASS64 2   /* 64-bit objects */
#define ELFCLASSNUM 3

#define EI_DATA 5     /* Data encoding byte index */
#define ELFDATANONE 0 /* Invalid data encoding */
#define ELFDATA2LSB 1 /* 2's complement, little endian */
#define ELFDATA2MSB 2 /* 2's complement, big endian */
#define ELFDATANUM 3

#define EI_VERSION 6 /* File version byte index */
                     /* Value must be EV_CURRENT */

#define EI_OSABI 7                  /* OS ABI identification */
#define ELFOSABI_NONE 0             /* UNIX System V ABI */
#define ELFOSABI_SYSV 0             /* Alias.  */
#define ELFOSABI_HPUX 1             /* HP-UX */
#define ELFOSABI_NETBSD 2           /* NetBSD.  */
#define ELFOSABI_GNU 3              /* Object uses GNU ELF extensions.  */
#define ELFOSABI_LINUX ELFOSABI_GNU /* Compatibility alias.  */
#define ELFOSABI_SOLARIS 6          /* Sun Solaris.  */
#define ELFOSABI_AIX 7              /* IBM AIX.  */
#define ELFOSABI_IRIX 8             /* SGI Irix.  */
#define ELFOSABI_FREEBSD 9          /* FreeBSD.  */
#define ELFOSABI_TRU64 10           /* Compaq TRU64 UNIX.  */
#define ELFOSABI_MODESTO 11         /* Novell Modesto.  */
#define ELFOSABI_OPENBSD 12         /* OpenBSD.  */
#define ELFOSABI_ARM_AEABI 64       /* ARM EABI */
#define ELFOSABI_ARM 97             /* ARM */
#define ELFOSABI_STANDALONE 255     /* Standalone (embedded) application */

#define EI_ABIVERSION 8 /* ABI version */

#define EI_PAD 9 /* Byte index of padding bytes */

/* Legal values for e_type (object file type).  */

#define ET_NONE 0        /* No file type */
#define ET_REL 1         /* Relocatable file */
#define ET_EXEC 2        /* Executable file */
#define ET_DYN 3         /* Shared object file */
#define ET_CORE 4        /* Core file */
#define ET_NUM 5         /* Number of defined types */
#define ET_LOOS 0xfe00   /* OS-specific range start */
#define ET_HIOS 0xfeff   /* OS-specific range end */
#define ET_LOPROC 0xff00 /* Processor-specific range start */
#define ET_HIPROC 0xffff /* Processor-specific range end */

/* Legal values for e_machine (architecture).  */

#define EM_NONE 0         /* No machine */
#define EM_M32 1          /* AT&T WE 32100 */
#define EM_SPARC 2        /* SUN SPARC */
#define EM_386 3          /* Intel 80386 */
#define EM_68K 4          /* Motorola m68k family */
#define EM_88K 5          /* Motorola m88k family */
#define EM_IAMCU 6        /* Intel MCU */
#define EM_860 7          /* Intel 80860 */
#define EM_MIPS 8         /* MIPS R3000 big-endian */
#define EM_S370 9         /* IBM System/370 */
#define EM_MIPS_RS3_LE 10 /* MIPS R3000 little-endian */
                          /* reserved 11-14 */
#define EM_PARISC 15      /* HPPA */
                          /* reserved 16 */
#define EM_VPP500 17      /* Fujitsu VPP500 */
#define EM_SPARC32PLUS 18 /* Sun's "v8plus" */
#define EM_960 19         /* Intel 80960 */
#define EM_PPC 20         /* PowerPC */
#define EM_PPC64 21       /* PowerPC 64-bit */
#define EM_S390 22        /* IBM S390 */
#define EM_SPU 23         /* IBM SPU/SPC */
                          /* reserved 24-35 */
#define EM_V800 36        /* NEC V800 series */
#define EM_FR20 37        /* Fujitsu FR20 */
#define EM_RH32 38        /* TRW RH-32 */
#define EM_RCE 39         /* Motorola RCE */
#define EM_ARM 40         /* ARM */
#define EM_FAKE_ALPHA 41  /* Digital Alpha */
#define EM_SH 42          /* Hitachi SH */
#define EM_SPARCV9 43     /* SPARC v9 64-bit */
#define EM_TRICORE 44     /* Siemens Tricore */
#define EM_ARC 45         /* Argonaut RISC Core */
#define EM_H8_300 46      /* Hitachi H8/300 */
#define EM_H8_300H 47     /* Hitachi H8/300H */
#define EM_H8S 48         /* Hitachi H8S */
#define EM_H8_500 49      /* Hitachi H8/500 */
#define EM_IA_64 50       /* Intel Merced */
#define EM_MIPS_X 51      /* Stanford MIPS-X */
#define EM_COLDFIRE 52    /* Motorola Coldfire */
#define EM_68HC12 53      /* Motorola M68HC12 */
#define EM_MMA 54         /* Fujitsu MMA Multimedia Accelerator */
#define EM_PCP 55         /* Siemens PCP */
#define EM_NCPU 56        /* Sony nCPU embedded RISC */
#define EM_NDR1 57        /* Denso NDR1 microprocessor */
#define EM_STARCORE 58    /* Motorola Start*Core processor */
#define EM_ME16 59        /* Toyota ME16 processor */
#define EM_ST100 60       /* STMicroelectronic ST100 processor */
#define EM_TINYJ 61       /* Advanced Logic Corp. Tinyj emb.fam */
#define EM_X86_64 62      /* AMD x86-64 architecture */
#define EM_PDSP 63        /* Sony DSP Processor */
#define EM_PDP10 64       /* Digital PDP-10 */
#define EM_PDP11 65       /* Digital PDP-11 */
#define EM_FX66 66        /* Siemens FX66 microcontroller */
#define EM_ST9PLUS 67     /* STMicroelectronics ST9+ 8/16 mc */
#define EM_ST7 68         /* STmicroelectronics ST7 8 bit mc */
#define EM_68HC16 69      /* Motorola MC68HC16 microcontroller */
#define EM_68HC11 70      /* Motorola MC68HC11 microcontroller */
#define EM_68HC08 71      /* Motorola MC68HC08 microcontroller */
#define EM_68HC05 72      /* Motorola MC68HC05 microcontroller */
#define EM_SVX 73         /* Silicon Graphics SVx */
#define EM_ST19 74        /* STMicroelectronics ST19 8 bit mc */
#define EM_VAX 75         /* Digital VAX */
#define EM_CRIS 76        /* Axis Communications 32-bit emb.proc */
#define EM_JAVELIN 77     /* Infineon Technologies 32-bit emb.proc */
#define EM_FIREPATH 78    /* Element 14 64-bit DSP Processor */
#define EM_ZSP 79         /* LSI Logic 16-bit DSP Processor */
#define EM_MMIX 80        /* Donald Knuth's educational 64-bit proc */
#define EM_HUANY 81    /* Harvard University machine-independent object files */
#define EM_PRISM 82    /* SiTera Prism */
#define EM_AVR 83      /* Atmel AVR 8-bit microcontroller */
#define EM_FR30 84     /* Fujitsu FR30 */
#define EM_D10V 85     /* Mitsubishi D10V */
#define EM_D30V 86     /* Mitsubishi D30V */
#define EM_V850 87     /* NEC v850 */
#define EM_M32R 88     /* Mitsubishi M32R */
#define EM_MN10300 89  /* Matsushita MN10300 */
#define EM_MN10200 90  /* Matsushita MN10200 */
#define EM_PJ 91       /* picoJava */
#define EM_OPENRISC 92 /* OpenRISC 32-bit embedded processor */
#define EM_ARC_COMPACT 93    /* ARC International ARCompact */
#define EM_XTENSA 94         /* Tensilica Xtensa Architecture */
#define EM_VIDEOCORE 95      /* Alphamosaic VideoCore */
#define EM_TMM_GPP 96        /* Thompson Multimedia General Purpose Proc */
#define EM_NS32K 97          /* National Semi. 32000 */
#define EM_TPC 98            /* Tenor Network TPC */
#define EM_SNP1K 99          /* Trebia SNP 1000 */
#define EM_ST200 100         /* STMicroelectronics ST200 */
#define EM_IP2K 101          /* Ubicom IP2xxx */
#define EM_MAX 102           /* MAX processor */
#define EM_CR 103            /* National Semi. CompactRISC */
#define EM_F2MC16 104        /* Fujitsu F2MC16 */
#define EM_MSP430 105        /* Texas Instruments msp430 */
#define EM_BLACKFIN 106      /* Analog Devices Blackfin DSP */
#define EM_SE_C33 107        /* Seiko Epson S1C33 family */
#define EM_SEP 108           /* Sharp embedded microprocessor */
#define EM_ARCA 109          /* Arca RISC */
#define EM_UNICORE 110       /* PKU-Unity & MPRC Peking Uni. mc series */
#define EM_EXCESS 111        /* eXcess configurable cpu */
#define EM_DXP 112           /* Icera Semi. Deep Execution Processor */
#define EM_ALTERA_NIOS2 113  /* Altera Nios II */
#define EM_CRX 114           /* National Semi. CompactRISC CRX */
#define EM_XGATE 115         /* Motorola XGATE */
#define EM_C166 116          /* Infineon C16x/XC16x */
#define EM_M16C 117          /* Renesas M16C */
#define EM_DSPIC30F 118      /* Microchip Technology dsPIC30F */
#define EM_CE 119            /* Freescale Communication Engine RISC */
#define EM_M32C 120          /* Renesas M32C */
                             /* reserved 121-130 */
#define EM_TSK3000 131       /* Altium TSK3000 */
#define EM_RS08 132          /* Freescale RS08 */
#define EM_SHARC 133         /* Analog Devices SHARC family */
#define EM_ECOG2 134         /* Cyan Technology eCOG2 */
#define EM_SCORE7 135        /* Sunplus S+core7 RISC */
#define EM_DSP24 136         /* New Japan Radio (NJR) 24-bit DSP */
#define EM_VIDEOCORE3 137    /* Broadcom VideoCore III */
#define EM_LATTICEMICO32 138 /* RISC for Lattice FPGA */
#define EM_SE_C17 139        /* Seiko Epson C17 */
#define EM_TI_C6000 140      /* Texas Instruments TMS320C6000 DSP */
#define EM_TI_C2000 141      /* Texas Instruments TMS320C2000 DSP */
#define EM_TI_C5500 142      /* Texas Instruments TMS320C55x DSP */
#define EM_TI_ARP32 143      /* Texas Instruments App. Specific RISC */
#define EM_TI_PRU 144        /* Texas Instruments Prog. Realtime Unit */
                             /* reserved 145-159 */
#define EM_MMDSP_PLUS 160    /* STMicroelectronics 64bit VLIW DSP */
#define EM_CYPRESS_M8C 161   /* Cypress M8C */
#define EM_R32C 162          /* Renesas R32C */
#define EM_TRIMEDIA 163      /* NXP Semi. TriMedia */
#define EM_QDSP6 164         /* QUALCOMM DSP6 */
#define EM_8051 165          /* Intel 8051 and variants */
#define EM_STXP7X 166        /* STMicroelectronics STxP7x */
#define EM_NDS32 167         /* Andes Tech. compact code emb. RISC */
#define EM_ECOG1X 168        /* Cyan Technology eCOG1X */
#define EM_MAXQ30 169        /* Dallas Semi. MAXQ30 mc */
#define EM_XIMO16 170        /* New Japan Radio (NJR) 16-bit DSP */
#define EM_MANIK 171         /* M2000 Reconfigurable RISC */
#define EM_CRAYNV2 172       /* Cray NV2 vector architecture */
#define EM_RX 173            /* Renesas RX */
#define EM_METAG 174         /* Imagination Tech. META */
#define EM_MCST_ELBRUS 175   /* MCST Elbrus */
#define EM_ECOG16 176        /* Cyan Technology eCOG16 */
#define EM_CR16 177          /* National Semi. CompactRISC CR16 */
#define EM_ETPU 178          /* Freescale Extended Time Processing Unit */
#define EM_SLE9X 179         /* Infineon Tech. SLE9X */
#define EM_L10M 180          /* Intel L10M */
#define EM_K10M 181          /* Intel K10M */
                             /* reserved 182 */
#define EM_AARCH64 183       /* ARM AARCH64 */
                             /* reserved 184 */
#define EM_AVR32 185         /* Amtel 32-bit microprocessor */
#define EM_STM8 186          /* STMicroelectronics STM8 */
#define EM_TILE64 187        /* Tilera TILE64 */
#define EM_TILEPRO 188       /* Tilera TILEPro */
#define EM_MICROBLAZE 189    /* Xilinx MicroBlaze */
#define EM_CUDA 190          /* NVIDIA CUDA */
#define EM_TILEGX 191        /* Tilera TILE-Gx */
#define EM_CLOUDSHIELD 192   /* CloudShield */
#define EM_COREA_1ST 193     /* KIPO-KAIST Core-A 1st gen. */
#define EM_COREA_2ND 194     /* KIPO-KAIST Core-A 2nd gen. */
#define EM_ARCV2 195         /* Synopsys ARCv2 ISA.  */
#define EM_OPEN8 196         /* Open8 RISC */
#define EM_RL78 197          /* Renesas RL78 */
#define EM_VIDEOCORE5 198    /* Broadcom VideoCore V */
#define EM_78KOR 199         /* Renesas 78KOR */
#define EM_56800EX 200       /* Freescale 56800EX DSC */
#define EM_BA1 201           /* Beyond BA1 */
#define EM_BA2 202           /* Beyond BA2 */
#define EM_XCORE 203         /* XMOS xCORE */
#define EM_MCHP_PIC 204      /* Microchip 8-bit PIC(r) */
#define EM_INTELGT 205       /* Intel Graphics Technology */
                             /* reserved 206-209 */
#define EM_KM32 210          /* KM211 KM32 */
#define EM_KMX32 211         /* KM211 KMX32 */
#define EM_EMX16 212         /* KM211 KMX16 */
#define EM_EMX8 213          /* KM211 KMX8 */
#define EM_KVARC 214         /* KM211 KVARC */
#define EM_CDP 215           /* Paneve CDP */
#define EM_COGE 216          /* Cognitive Smart Memory Processor */
#define EM_COOL 217          /* Bluechip CoolEngine */
#define EM_NORC 218          /* Nanoradio Optimized RISC */
#define EM_CSR_KALIMBA 219   /* CSR Kalimba */
#define EM_Z80 220           /* Zilog Z80 */
#define EM_VISIUM 221        /* Controls and Data Services VISIUMcore */
#define EM_FT32 222          /* FTDI Chip FT32 */
#define EM_MOXIE 223         /* Moxie processor */
#define EM_AMDGPU 224        /* AMD GPU */
                             /* reserved 225-242 */
#define EM_RISCV 243         /* RISC-V */

#define EM_BPF 247       /* Linux BPF -- in-kernel virtual machine */
#define EM_CSKY 252      /* C-SKY */
#define EM_LOONGARCH 258 /* LoongArch */

#define EM_NUM 259

/* Old spellings/synonyms.  */

#define EM_ARC_A5 EM_ARC_COMPACT

#define EM_ALPHA 0x9026

/* Legal values for e_version (version).  */

#define EV_NONE 0    /* Invalid ELF version */
#define EV_CURRENT 1 /* Current version */
#define EV_NUM 2

typedef struct {
  Elf32_Word sh_name;      /* Section name (string tbl index) */
  Elf32_Word sh_type;      /* Section type */
  Elf32_Word sh_flags;     /* Section flags */
  Elf32_Addr sh_addr;      /* Section virtual addr at execution */
  Elf32_Off sh_offset;     /* Section file offset */
  Elf32_Word sh_size;      /* Section size in bytes */
  Elf32_Word sh_link;      /* Link to another section */
  Elf32_Word sh_info;      /* Additional section information */
  Elf32_Word sh_addralign; /* Section alignment */
  Elf32_Word sh_entsize;   /* Entry size if section holds table */
} Elf32_Shdr;

typedef struct {
  Elf64_Word sh_name;       /* Section name (string tbl index) */
  Elf64_Word sh_type;       /* Section type */
  Elf64_Xword sh_flags;     /* Section flags */
  Elf64_Addr sh_addr;       /* Section virtual addr at execution */
  Elf64_Off sh_offset;      /* Section file offset */
  Elf64_Xword sh_size;      /* Section size in bytes */
  Elf64_Word sh_link;       /* Link to another section */
  Elf64_Word sh_info;       /* Additional section information */
  Elf64_Xword sh_addralign; /* Section alignment */
  Elf64_Xword sh_entsize;   /* Entry size if section holds table */
} Elf64_Shdr;

#define SHN_UNDEF 0          /* Undefined section */
#define SHN_LORESERVE 0xff00 /* Start of reserved indices */
#define SHN_LOPROC 0xff00    /* Start of processor-specific */
#define SHN_BEFORE                                                             \
  0xff00 /* Order section before all others                                    \
            (Solaris).  */
#define SHN_AFTER                                                              \
  0xff01                     /* Order section after all others                 \
                                (Solaris).  */
#define SHN_HIPROC 0xff1f    /* End of processor-specific */
#define SHN_LOOS 0xff20      /* Start of OS-specific */
#define SHN_HIOS 0xff3f      /* End of OS-specific */
#define SHN_ABS 0xfff1       /* Associated symbol is absolute */
#define SHN_COMMON 0xfff2    /* Associated symbol is common */
#define SHN_XINDEX 0xffff    /* Index is in extra table.  */
#define SHN_HIRESERVE 0xffff /* End of reserved indices */

/* Legal values for sh_type (section type).  */

#define SHT_NULL 0                    /* Section header table entry unused */
#define SHT_PROGBITS 1                /* Program data */
#define SHT_SYMTAB 2                  /* Symbol table */
#define SHT_STRTAB 3                  /* String table */
#define SHT_RELA 4                    /* Relocation entries with addends */
#define SHT_HASH 5                    /* Symbol hash table */
#define SHT_DYNAMIC 6                 /* Dynamic linking information */
#define SHT_NOTE 7                    /* Notes */
#define SHT_NOBITS 8                  /* Program space with no data (bss) */
#define SHT_REL 9                     /* Relocation entries, no addends */
#define SHT_SHLIB 10                  /* Reserved */
#define SHT_DYNSYM 11                 /* Dynamic linker symbol table */
#define SHT_INIT_ARRAY 14             /* Array of constructors */
#define SHT_FINI_ARRAY 15             /* Array of destructors */
#define SHT_PREINIT_ARRAY 16          /* Array of pre-constructors */
#define SHT_GROUP 17                  /* Section group */
#define SHT_SYMTAB_SHNDX 18           /* Extended section indices */
#define SHT_RELR 19                   /* RELR relative relocations */
#define SHT_NUM 20                    /* Number of defined types.  */
#define SHT_LOOS 0x60000000           /* Start OS-specific.  */
#define SHT_GNU_ATTRIBUTES 0x6ffffff5 /* Object attributes.  */
#define SHT_GNU_HASH 0x6ffffff6       /* GNU-style hash table.  */
#define SHT_GNU_LIBLIST 0x6ffffff7    /* Prelink library list */
#define SHT_CHECKSUM 0x6ffffff8       /* Checksum for DSO content.  */
#define SHT_LOSUNW 0x6ffffffa         /* Sun-specific low bound.  */
#define SHT_SUNW_move 0x6ffffffa
#define SHT_SUNW_COMDAT 0x6ffffffb
#define SHT_SUNW_syminfo 0x6ffffffc
#define SHT_GNU_verdef 0x6ffffffd  /* Version definition section.  */
#define SHT_GNU_verneed 0x6ffffffe /* Version needs section.  */
#define SHT_GNU_versym 0x6fffffff  /* Version symbol table.  */
#define SHT_HISUNW 0x6fffffff      /* Sun-specific high bound.  */
#define SHT_HIOS 0x6fffffff        /* End OS-specific type */
#define SHT_LOPROC 0x70000000      /* Start of processor-specific */
#define SHT_HIPROC 0x7fffffff      /* End of processor-specific */
#define SHT_LOUSER 0x80000000      /* Start of application-specific */
#define SHT_HIUSER 0x8fffffff      /* End of application-specific */

/* Legal values for sh_flags (section flags).  */

#define SHF_WRITE (1 << 0)      /* Writable */
#define SHF_ALLOC (1 << 1)      /* Occupies memory during execution */
#define SHF_EXECINSTR (1 << 2)  /* Executable */
#define SHF_MERGE (1 << 4)      /* Might be merged */
#define SHF_STRINGS (1 << 5)    /* Contains nul-terminated strings */
#define SHF_INFO_LINK (1 << 6)  /* `sh_info' contains SHT index */
#define SHF_LINK_ORDER (1 << 7) /* Preserve order after combining */
#define SHF_OS_NONCONFORMING                                                   \
  (1 << 8)                       /* Non-standard OS specific handling          \
                                    required */
#define SHF_GROUP (1 << 9)       /* Section is member of a group.  */
#define SHF_TLS (1 << 10)        /* Section hold thread-local data.  */
#define SHF_COMPRESSED (1 << 11) /* Section with compressed data. */
#define SHF_MASKOS 0x0ff00000    /* OS-specific.  */
#define SHF_MASKPROC 0xf0000000  /* Processor-specific */
#define SHF_GNU_RETAIN (1 << 21) /* Not to be GCed by linker.  */
#define SHF_ORDERED                                                            \
  (1 << 30) /* Special ordering requirement                                    \
               (Solaris).  */
#define SHF_EXCLUDE                                                            \
  (1U << 31) /* Section is excluded unless                                     \
                referenced or allocated (Solaris).*/

typedef struct {
  Elf32_Word ch_type;      /* Compression format.  */
  Elf32_Word ch_size;      /* Uncompressed data size.  */
  Elf32_Word ch_addralign; /* Uncompressed data alignment.  */
} Elf32_Chdr;

typedef struct {
  Elf64_Word ch_type; /* Compression format.  */
  Elf64_Word ch_reserved;
  Elf64_Xword ch_size;      /* Uncompressed data size.  */
  Elf64_Xword ch_addralign; /* Uncompressed data alignment.  */
} Elf64_Chdr;

#define ELFCOMPRESS_ZLIB 1            /* ZLIB/DEFLATE algorithm.  */
#define ELFCOMPRESS_ZSTD 2            /* Zstandard algorithm.  */
#define ELFCOMPRESS_LOOS 0x60000000   /* Start of OS-specific.  */
#define ELFCOMPRESS_HIOS 0x6fffffff   /* End of OS-specific.  */
#define ELFCOMPRESS_LOPROC 0x70000000 /* Start of processor-specific.  */
#define ELFCOMPRESS_HIPROC 0x7fffffff /* End of processor-specific.  */

/* Section group handling.  */
#define GRP_COMDAT 0x1 /* Mark group as COMDAT.  */

typedef struct {
  Elf32_Word st_name;     /* Symbol name (string tbl index) */
  Elf32_Addr st_value;    /* Symbol value */
  Elf32_Word st_size;     /* Symbol size */
  unsigned char st_info;  /* Symbol type and binding */
  unsigned char st_other; /* Symbol visibility */
  Elf32_Section st_shndx; /* Section index */
} Elf32_Sym;

typedef struct {
  Elf64_Word st_name;     /* Symbol name (string tbl index) */
  unsigned char st_info;  /* Symbol type and binding */
  unsigned char st_other; /* Symbol visibility */
  Elf64_Section st_shndx; /* Section index */
  Elf64_Addr st_value;    /* Symbol value */
  Elf64_Xword st_size;    /* Symbol size */
} Elf64_Sym;

typedef struct {
  Elf32_Half si_boundto; /* Direct bindings, symbol bound to */
  Elf32_Half si_flags;   /* Per symbol flags */
} Elf32_Syminfo;

typedef struct {
  Elf64_Half si_boundto; /* Direct bindings, symbol bound to */
  Elf64_Half si_flags;   /* Per symbol flags */
} Elf64_Syminfo;

/* Possible values for si_boundto.  */
#define SYMINFO_BT_SELF 0xffff       /* Symbol bound to self */
#define SYMINFO_BT_PARENT 0xfffe     /* Symbol bound to parent */
#define SYMINFO_BT_LOWRESERVE 0xff00 /* Beginning of reserved entries */

/* Possible bitmasks for si_flags.  */
#define SYMINFO_FLG_DIRECT 0x0001   /* Direct bound symbol */
#define SYMINFO_FLG_PASSTHRU 0x0002 /* Pass-through symbol for translator */
#define SYMINFO_FLG_COPY 0x0004     /* Symbol is a copy-reloc */
#define SYMINFO_FLG_LAZYLOAD                                                   \
  0x0008 /* Symbol bound to object to be lazy                                  \
                               loaded */

/* Syminfo version values.  */
#define SYMINFO_NONE 0
#define SYMINFO_CURRENT 1
#define SYMINFO_NUM 2

/* How to extract and insert information held in the st_info field.  */

#define ELF32_ST_BIND(val) (((unsigned char)(val)) >> 4)
#define ELF32_ST_TYPE(val) ((val)&0xf)
#define ELF32_ST_INFO(bind, type) (((bind) << 4) + ((type)&0xf))

/* Both Elf32_Sym and Elf64_Sym use the same one-byte st_info field.  */
#define ELF64_ST_BIND(val) ELF32_ST_BIND(val)
#define ELF64_ST_TYPE(val) ELF32_ST_TYPE(val)
#define ELF64_ST_INFO(bind, type) ELF32_ST_INFO((bind), (type))

#define STB_LOCAL 0       /* Local symbol */
#define STB_GLOBAL 1      /* Global symbol */
#define STB_WEAK 2        /* Weak symbol */
#define STB_NUM 3         /* Number of defined types.  */
#define STB_LOOS 10       /* Start of OS-specific */
#define STB_GNU_UNIQUE 10 /* Unique symbol.  */
#define STB_HIOS 12       /* End of OS-specific */
#define STB_LOPROC 13     /* Start of processor-specific */
#define STB_HIPROC 15     /* End of processor-specific */

/* Legal values for ST_TYPE subfield of st_info (symbol type).  */

#define STT_NOTYPE 0     /* Symbol type is unspecified */
#define STT_OBJECT 1     /* Symbol is a data object */
#define STT_FUNC 2       /* Symbol is a code object */
#define STT_SECTION 3    /* Symbol associated with a section */
#define STT_FILE 4       /* Symbol's name is file name */
#define STT_COMMON 5     /* Symbol is a common data object */
#define STT_TLS 6        /* Symbol is thread-local data object*/
#define STT_NUM 7        /* Number of defined types.  */
#define STT_LOOS 10      /* Start of OS-specific */
#define STT_GNU_IFUNC 10 /* Symbol is indirect code object */
#define STT_HIOS 12      /* End of OS-specific */
#define STT_LOPROC 13    /* Start of processor-specific */
#define STT_HIPROC 15    /* End of processor-specific */

/* Symbol table indices are found in the hash buckets and chain table
   of a symbol hash table section.  This special index value indicates
   the end of a chain, meaning no further symbols are found in that bucket.  */

#define STN_UNDEF 0 /* End of a chain.  */

/* How to extract and insert information held in the st_other field.  */

#define ELF32_ST_VISIBILITY(o) ((o)&0x03)

/* For ELF64 the definitions are the same.  */
#define ELF64_ST_VISIBILITY(o) ELF32_ST_VISIBILITY(o)

/* Symbol visibility specification encoded in the st_other field.  */
#define STV_DEFAULT 0   /* Default symbol visibility rules */
#define STV_INTERNAL 1  /* Processor specific hidden class */
#define STV_HIDDEN 2    /* Sym unavailable in other modules */
#define STV_PROTECTED 3 /* Not preemptible, not exported */

typedef struct {
  Elf32_Addr r_offset; /* Address */
  Elf32_Word r_info;   /* Relocation type and symbol index */
} Elf32_Rel;

typedef struct {
  Elf64_Addr r_offset; /* Address */
  Elf64_Xword r_info;  /* Relocation type and symbol index */
} Elf64_Rel;

typedef struct {
  Elf32_Addr r_offset;  /* Address */
  Elf32_Word r_info;    /* Relocation type and symbol index */
  Elf32_Sword r_addend; /* Addend */
} Elf32_Rela;

typedef struct {
  Elf64_Addr r_offset;   /* Address */
  Elf64_Xword r_info;    /* Relocation type and symbol index */
  Elf64_Sxword r_addend; /* Addend */
} Elf64_Rela;

typedef Elf32_Word Elf32_Relr;
typedef Elf64_Xword Elf64_Relr;

#define ELF32_R_SYM(val) ((val) >> 8)
#define ELF32_R_TYPE(val) ((val)&0xff)
#define ELF32_R_INFO(sym, type) (((sym) << 8) + ((type)&0xff))

#define ELF64_R_SYM(i) ((i) >> 32)
#define ELF64_R_TYPE(i) ((i)&0xffffffff)
#define ELF64_R_INFO(sym, type) ((((Elf64_Xword)(sym)) << 32) + (type))

typedef struct {
  Elf32_Word p_type;   /* Segment type */
  Elf32_Off p_offset;  /* Segment file offset */
  Elf32_Addr p_vaddr;  /* Segment virtual address */
  Elf32_Addr p_paddr;  /* Segment physical address */
  Elf32_Word p_filesz; /* Segment size in file */
  Elf32_Word p_memsz;  /* Segment size in memory */
  Elf32_Word p_flags;  /* Segment flags */
  Elf32_Word p_align;  /* Segment alignment */
} Elf32_Phdr;

typedef struct {
  Elf64_Word p_type;    /* Segment type */
  Elf64_Word p_flags;   /* Segment flags */
  Elf64_Off p_offset;   /* Segment file offset */
  Elf64_Addr p_vaddr;   /* Segment virtual address */
  Elf64_Addr p_paddr;   /* Segment physical address */
  Elf64_Xword p_filesz; /* Segment size in file */
  Elf64_Xword p_memsz;  /* Segment size in memory */
  Elf64_Xword p_align;  /* Segment alignment */
} Elf64_Phdr;

#define PN_XNUM 0xffff

#define PT_NULL 0                  /* Program header table entry unused */
#define PT_LOAD 1                  /* Loadable program segment */
#define PT_DYNAMIC 2               /* Dynamic linking information */
#define PT_INTERP 3                /* Program interpreter */
#define PT_NOTE 4                  /* Auxiliary information */
#define PT_SHLIB 5                 /* Reserved */
#define PT_PHDR 6                  /* Entry for header table itself */
#define PT_TLS 7                   /* Thread-local storage segment */
#define PT_NUM 8                   /* Number of defined types */
#define PT_LOOS 0x60000000         /* Start of OS-specific */
#define PT_GNU_EH_FRAME 0x6474e550 /* GCC .eh_frame_hdr segment */
#define PT_GNU_STACK 0x6474e551    /* Indicates stack executability */
#define PT_GNU_RELRO 0x6474e552    /* Read-only after relocation */
#define PT_GNU_PROPERTY 0x6474e553 /* GNU property */
#define PT_GNU_SFRAME 0x6474e554   /* SFrame segment.  */
#define PT_LOSUNW 0x6ffffffa
#define PT_SUNWBSS 0x6ffffffa   /* Sun Specific segment */
#define PT_SUNWSTACK 0x6ffffffb /* Stack segment */
#define PT_HISUNW 0x6fffffff
#define PT_HIOS 0x6fffffff   /* End of OS-specific */
#define PT_LOPROC 0x70000000 /* Start of processor-specific */
#define PT_HIPROC 0x7fffffff /* End of processor-specific */

#define PF_X (1 << 0)          /* Segment is executable */
#define PF_W (1 << 1)          /* Segment is writable */
#define PF_R (1 << 2)          /* Segment is readable */
#define PF_MASKOS 0x0ff00000   /* OS-specific */
#define PF_MASKPROC 0xf0000000 /* Processor-specific */

#define NT_PRSTATUS 1 /* Contains copy of prstatus struct */
#define NT_PRFPREG                                                             \
  2                     /* Contains copy of fpregset                           \
                           struct.  */
#define NT_FPREGSET 2   /* Contains copy of fpregset struct */
#define NT_PRPSINFO 3   /* Contains copy of prpsinfo struct */
#define NT_PRXREG 4     /* Contains copy of prxregset struct */
#define NT_TASKSTRUCT 4 /* Contains copy of task structure */
#define NT_PLATFORM 5   /* String from sysinfo(SI_PLATFORM) */
#define NT_AUXV 6       /* Contains copy of auxv array */
#define NT_GWINDOWS 7   /* Contains copy of gwindows struct */
#define NT_ASRS 8       /* Contains copy of asrset struct */
#define NT_PSTATUS 10   /* Contains copy of pstatus struct */
#define NT_PSINFO 13    /* Contains copy of psinfo struct */
#define NT_PRCRED 14    /* Contains copy of prcred struct */
#define NT_UTSNAME 15   /* Contains copy of utsname struct */
#define NT_LWPSTATUS 16 /* Contains copy of lwpstatus struct */
#define NT_LWPSINFO 17  /* Contains copy of lwpinfo struct */
#define NT_PRFPXREG 20  /* Contains copy of fprxregset struct */
#define NT_SIGINFO                                                             \
  0x53494749 /* Contains copy of siginfo_t,                                    \
                size might increase */
#define NT_FILE                                                                \
  0x46494c45                   /* Contains information about mapped            \
                                  files */
#define NT_PRXFPREG 0x46e62b7f /* Contains copy of user_fxsr_struct */

#define NT_386_TLS 0x200    /* i386 TLS slots (struct user_desc) */
#define NT_386_IOPERM 0x201 /* x86 io permission bitmap (1=deny) */
#define NT_X86_XSTATE 0x202 /* x86 extended state using xsave */

#define NT_ARM_VFP 0x400         /* ARM VFP/NEON registers */
#define NT_ARM_TLS 0x401         /* ARM TLS register */
#define NT_ARM_HW_BREAK 0x402    /* ARM hardware breakpoint registers */
#define NT_ARM_HW_WATCH 0x403    /* ARM hardware watchpoint registers */
#define NT_ARM_SYSTEM_CALL 0x404 /* ARM system call number */
#define NT_ARM_SVE                                                             \
  0x405 /* ARM Scalable Vector Extension                                       \
           registers */
#define NT_ARM_PAC_MASK                                                        \
  0x406 /* ARM pointer authentication                                          \
           code masks.  */
#define NT_ARM_PACA_KEYS                                                       \
  0x407 /* ARM pointer authentication                                          \
           address keys.  */
#define NT_ARM_PACG_KEYS                                                       \
  0x408 /* ARM pointer authentication                                          \
           generic key.  */
#define NT_ARM_TAGGED_ADDR_CTRL                                                \
  0x409 /* AArch64 tagged address                                              \
           control.  */
#define NT_ARM_PAC_ENABLED_KEYS                                                \
  0x40a                   /* AArch64 pointer authentication                    \
                             enabled keys.  */
#define NT_VMCOREDD 0x700 /* Vmcore Device Dump Note.  */

#define NT_VERSION 1 /* Contains a version string.  */

typedef struct {
  Elf32_Sword d_tag; /* Dynamic entry type */
  union {
    Elf32_Word d_val; /* Integer value */
    Elf32_Addr d_ptr; /* Address value */
  } d_un;
} Elf32_Dyn;

typedef struct {
  Elf64_Sxword d_tag; /* Dynamic entry type */
  union {
    Elf64_Xword d_val; /* Integer value */
    Elf64_Addr d_ptr;  /* Address value */
  } d_un;
} Elf64_Dyn;

#define DT_NULL 0              /* Marks end of dynamic section */
#define DT_NEEDED 1            /* Name of needed library */
#define DT_PLTRELSZ 2          /* Size in bytes of PLT relocs */
#define DT_PLTGOT 3            /* Processor defined value */
#define DT_HASH 4              /* Address of symbol hash table */
#define DT_STRTAB 5            /* Address of string table */
#define DT_SYMTAB 6            /* Address of symbol table */
#define DT_RELA 7              /* Address of Rela relocs */
#define DT_RELASZ 8            /* Total size of Rela relocs */
#define DT_RELAENT 9           /* Size of one Rela reloc */
#define DT_STRSZ 10            /* Size of string table */
#define DT_SYMENT 11           /* Size of one symbol table entry */
#define DT_INIT 12             /* Address of init function */
#define DT_FINI 13             /* Address of termination function */
#define DT_SONAME 14           /* Name of shared object */
#define DT_RPATH 15            /* Library search path (deprecated) */
#define DT_SYMBOLIC 16         /* Start symbol search here */
#define DT_REL 17              /* Address of Rel relocs */
#define DT_RELSZ 18            /* Total size of Rel relocs */
#define DT_RELENT 19           /* Size of one Rel reloc */
#define DT_PLTREL 20           /* Type of reloc in PLT */
#define DT_DEBUG 21            /* For debugging; unspecified */
#define DT_TEXTREL 22          /* Reloc might modify .text */
#define DT_JMPREL 23           /* Address of PLT relocs */
#define DT_BIND_NOW 24         /* Process relocations of object */
#define DT_INIT_ARRAY 25       /* Array with addresses of init fct */
#define DT_FINI_ARRAY 26       /* Array with addresses of fini fct */
#define DT_INIT_ARRAYSZ 27     /* Size in bytes of DT_INIT_ARRAY */
#define DT_FINI_ARRAYSZ 28     /* Size in bytes of DT_FINI_ARRAY */
#define DT_RUNPATH 29          /* Library search path */
#define DT_FLAGS 30            /* Flags for the object being loaded */
#define DT_ENCODING 32         /* Start of encoded range */
#define DT_PREINIT_ARRAY 32    /* Array with addresses of preinit fct*/
#define DT_PREINIT_ARRAYSZ 33  /* size in bytes of DT_PREINIT_ARRAY */
#define DT_SYMTAB_SHNDX 34     /* Address of SYMTAB_SHNDX section */
#define DT_RELRSZ 35           /* Total size of RELR relative relocations */
#define DT_RELR 36             /* Address of RELR relative relocations */
#define DT_RELRENT 37          /* Size of one RELR relative relocaction */
#define DT_NUM 38              /* Number used */
#define DT_LOOS 0x6000000d     /* Start of OS-specific */
#define DT_HIOS 0x6ffff000     /* End of OS-specific */
#define DT_LOPROC 0x70000000   /* Start of processor-specific */
#define DT_HIPROC 0x7fffffff   /* End of processor-specific */
#define DT_PROCNUM DT_MIPS_NUM /* Most used by any processor */

/* DT_* entries which fall between DT_VALRNGHI & DT_VALRNGLO use the
   Dyn.d_un.d_val field of the Elf*_Dyn structure.  This follows Sun's
   approach.  */
#define DT_VALRNGLO 0x6ffffd00
#define DT_GNU_PRELINKED 0x6ffffdf5  /* Prelinking timestamp */
#define DT_GNU_CONFLICTSZ 0x6ffffdf6 /* Size of conflict section */
#define DT_GNU_LIBLISTSZ 0x6ffffdf7  /* Size of library list */
#define DT_CHECKSUM 0x6ffffdf8
#define DT_PLTPADSZ 0x6ffffdf9
#define DT_MOVEENT 0x6ffffdfa
#define DT_MOVESZ 0x6ffffdfb
#define DT_FEATURE_1 0x6ffffdfc /* Feature selection (DTF_*).  */
#define DT_POSFLAG_1                                                           \
  0x6ffffdfd                   /* Flags for DT_* entries, effecting            \
                                  the following DT_* entry.  */
#define DT_SYMINSZ 0x6ffffdfe  /* Size of syminfo table (in bytes) */
#define DT_SYMINENT 0x6ffffdff /* Entry size of syminfo */
#define DT_VALRNGHI 0x6ffffdff
#define DT_VALTAGIDX(tag) (DT_VALRNGHI - (tag)) /* Reverse order! */
#define DT_VALNUM 12

/* DT_* entries which fall between DT_ADDRRNGHI & DT_ADDRRNGLO use the
   Dyn.d_un.d_ptr field of the Elf*_Dyn structure.
   If any adjustment is made to the ELF object after it has been
   built these entries will need to be adjusted.  */
#define DT_ADDRRNGLO 0x6ffffe00
#define DT_GNU_HASH 0x6ffffef5 /* GNU-style hash table.  */
#define DT_TLSDESC_PLT 0x6ffffef6
#define DT_TLSDESC_GOT 0x6ffffef7
#define DT_GNU_CONFLICT 0x6ffffef8 /* Start of conflict section */
#define DT_GNU_LIBLIST 0x6ffffef9  /* Library list */
#define DT_CONFIG 0x6ffffefa       /* Configuration information.  */
#define DT_DEPAUDIT 0x6ffffefb     /* Dependency auditing.  */
#define DT_AUDIT 0x6ffffefc        /* Object auditing.  */
#define DT_PLTPAD 0x6ffffefd       /* PLT padding.  */
#define DT_MOVETAB 0x6ffffefe      /* Move table.  */
#define DT_SYMINFO 0x6ffffeff      /* Syminfo table.  */
#define DT_ADDRRNGHI 0x6ffffeff
#define DT_ADDRTAGIDX(tag) (DT_ADDRRNGHI - (tag)) /* Reverse order! */
#define DT_ADDRNUM 11

/* The versioning entry types.  The next are defined as part of the
   GNU extension.  */
#define DT_VERSYM 0x6ffffff0

#define DT_RELACOUNT 0x6ffffff9
#define DT_RELCOUNT 0x6ffffffa

/* These were chosen by Sun.  */
#define DT_FLAGS_1 0x6ffffffb /* State flags, see DF_1_* below.  */
#define DT_VERDEF                                                              \
  0x6ffffffc                    /* Address of version definition               \
                                   table */
#define DT_VERDEFNUM 0x6ffffffd /* Number of version definitions */
#define DT_VERNEED                                                             \
  0x6ffffffe                     /* Address of table with needed               \
                                    versions */
#define DT_VERNEEDNUM 0x6fffffff /* Number of needed versions */
#define DT_VERSIONTAGIDX(tag) (DT_VERNEEDNUM - (tag)) /* Reverse order! */
#define DT_VERSIONTAGNUM 16

/* Sun added these machine-independent extensions in the "processor-specific"
   range.  Be compatible.  */
#define DT_AUXILIARY 0x7ffffffd /* Shared object to load before self */
#define DT_FILTER 0x7fffffff    /* Shared object to get values from */
#define DT_EXTRATAGIDX(tag) ((Elf32_Word) - ((Elf32_Sword)(tag) << 1 >> 1) - 1)
#define DT_EXTRANUM 3

/* Values of `d_un.d_val' in the DT_FLAGS entry.  */
#define DF_ORIGIN 0x00000001     /* Object may use DF_ORIGIN */
#define DF_SYMBOLIC 0x00000002   /* Symbol resolutions starts here */
#define DF_TEXTREL 0x00000004    /* Object contains text relocations */
#define DF_BIND_NOW 0x00000008   /* No lazy binding for this object */
#define DF_STATIC_TLS 0x00000010 /* Module uses the static TLS model */

/* State flags selectable in the `d_un.d_val' element of the DT_FLAGS_1
   entry in the dynamic section.  */
#define DF_1_NOW 0x00000001       /* Set RTLD_NOW for this object.  */
#define DF_1_GLOBAL 0x00000002    /* Set RTLD_GLOBAL for this object.  */
#define DF_1_GROUP 0x00000004     /* Set RTLD_GROUP for this object.  */
#define DF_1_NODELETE 0x00000008  /* Set RTLD_NODELETE for this object.*/
#define DF_1_LOADFLTR 0x00000010  /* Trigger filtee loading at runtime.*/
#define DF_1_INITFIRST 0x00000020 /* Set RTLD_INITFIRST for this object*/
#define DF_1_NOOPEN 0x00000040    /* Set RTLD_NOOPEN for this object.  */
#define DF_1_ORIGIN 0x00000080    /* $ORIGIN must be handled.  */
#define DF_1_DIRECT 0x00000100    /* Direct binding enabled.  */
#define DF_1_TRANS 0x00000200
#define DF_1_INTERPOSE 0x00000400  /* Object is used to interpose.  */
#define DF_1_NODEFLIB 0x00000800   /* Ignore default lib search path.  */
#define DF_1_NODUMP 0x00001000     /* Object can't be dldump'ed.  */
#define DF_1_CONFALT 0x00002000    /* Configuration alternative created.*/
#define DF_1_ENDFILTEE 0x00004000  /* Filtee terminates filters search. */
#define DF_1_DISPRELDNE 0x00008000 /* Disp reloc applied at build time. */
#define DF_1_DISPRELPND 0x00010000 /* Disp reloc applied at run-time.  */
#define DF_1_NODIRECT 0x00020000   /* Object has no-direct binding. */
#define DF_1_IGNMULDEF 0x00040000
#define DF_1_NOKSYMS 0x00080000
#define DF_1_NOHDR 0x00100000
#define DF_1_EDITED 0x00200000 /* Object is modified after built.  */
#define DF_1_NORELOC 0x00400000
#define DF_1_SYMINTPOSE 0x00800000 /* Object has individual interposers.  */
#define DF_1_GLOBAUDIT 0x01000000  /* Global auditing required.  */
#define DF_1_SINGLETON 0x02000000  /* Singleton symbols are used.  */
#define DF_1_STUB 0x04000000
#define DF_1_PIE 0x08000000
#define DF_1_KMOD 0x10000000
#define DF_1_WEAKFILTER 0x20000000
#define DF_1_NOCOMMON 0x40000000

/* Flags for the feature selection in DT_FEATURE_1.  */
#define DTF_1_PARINIT 0x00000001
#define DTF_1_CONFEXP 0x00000002

/* Flags in the DT_POSFLAG_1 entry effecting only the next DT_* entry.  */
#define DF_P1_LAZYLOAD 0x00000001 /* Lazyload following object.  */
#define DF_P1_GROUPPERM                                                        \
  0x00000002 /* Symbols from next object are not                               \
                generally available.  */

typedef struct {
  Elf32_Half vd_version; /* Version revision */
  Elf32_Half vd_flags;   /* Version information */
  Elf32_Half vd_ndx;     /* Version Index */
  Elf32_Half vd_cnt;     /* Number of associated aux entries */
  Elf32_Word vd_hash;    /* Version name hash value */
  Elf32_Word vd_aux;     /* Offset in bytes to verdaux array */
  Elf32_Word vd_next;    /* Offset in bytes to next verdef
                            entry */
} Elf32_Verdef;

typedef struct {
  Elf64_Half vd_version; /* Version revision */
  Elf64_Half vd_flags;   /* Version information */
  Elf64_Half vd_ndx;     /* Version Index */
  Elf64_Half vd_cnt;     /* Number of associated aux entries */
  Elf64_Word vd_hash;    /* Version name hash value */
  Elf64_Word vd_aux;     /* Offset in bytes to verdaux array */
  Elf64_Word vd_next;    /* Offset in bytes to next verdef
                            entry */
} Elf64_Verdef;

/* Legal values for vd_version (version revision).  */
#define VER_DEF_NONE 0    /* No version */
#define VER_DEF_CURRENT 1 /* Current version */
#define VER_DEF_NUM 2     /* Given version number */

/* Legal values for vd_flags (version information flags).  */
#define VER_FLG_BASE 0x1 /* Version definition of file itself */
#define VER_FLG_WEAK                                                           \
  0x2 /* Weak version identifier.  Also                                        \
         used by vna_flags below.  */

/* Versym symbol index values.  */
#define VER_NDX_LOCAL 0          /* Symbol is local.  */
#define VER_NDX_GLOBAL 1         /* Symbol is global.  */
#define VER_NDX_LORESERVE 0xff00 /* Beginning of reserved entries.  */
#define VER_NDX_ELIMINATE 0xff01 /* Symbol is to be eliminated.  */

typedef struct {
  Elf32_Word vda_name; /* Version or dependency names */
  Elf32_Word vda_next; /* Offset in bytes to next verdaux
                          entry */
} Elf32_Verdaux;

typedef struct {
  Elf64_Word vda_name; /* Version or dependency names */
  Elf64_Word vda_next; /* Offset in bytes to next verdaux
                          entry */
} Elf64_Verdaux;

typedef struct {
  Elf32_Half vn_version; /* Version of structure */
  Elf32_Half vn_cnt;     /* Number of associated aux entries */
  Elf32_Word vn_file;    /* Offset of filename for this
                            dependency */
  Elf32_Word vn_aux;     /* Offset in bytes to vernaux array */
  Elf32_Word vn_next;    /* Offset in bytes to next verneed
                            entry */
} Elf32_Verneed;

typedef struct {
  Elf64_Half vn_version; /* Version of structure */
  Elf64_Half vn_cnt;     /* Number of associated aux entries */
  Elf64_Word vn_file;    /* Offset of filename for this
                            dependency */
  Elf64_Word vn_aux;     /* Offset in bytes to vernaux array */
  Elf64_Word vn_next;    /* Offset in bytes to next verneed
                            entry */
} Elf64_Verneed;

#define VER_NEED_NONE 0    /* No version */
#define VER_NEED_CURRENT 1 /* Current version */
#define VER_NEED_NUM 2     /* Given version number */

typedef struct {
  Elf32_Word vna_hash;  /* Hash value of dependency name */
  Elf32_Half vna_flags; /* Dependency specific information */
  Elf32_Half vna_other; /* Unused */
  Elf32_Word vna_name;  /* Dependency name string offset */
  Elf32_Word vna_next;  /* Offset in bytes to next vernaux
                           entry */
} Elf32_Vernaux;

typedef struct {
  Elf64_Word vna_hash;  /* Hash value of dependency name */
  Elf64_Half vna_flags; /* Dependency specific information */
  Elf64_Half vna_other; /* Unused */
  Elf64_Word vna_name;  /* Dependency name string offset */
  Elf64_Word vna_next;  /* Offset in bytes to next vernaux
                           entry */
} Elf64_Vernaux;

typedef struct {
  uint32_t a_type; /* Entry type */
  union {
    uint32_t a_val; /* Integer value */
    /* We use to have pointer elements added here.  We cannot do that,
       though, since it does not work when using 32-bit definitions
       on 64-bit platforms and vice versa.  */
  } a_un;
} Elf32_auxv_t;

typedef struct {
  uint64_t a_type; /* Entry type */
  union {
    uint64_t a_val; /* Integer value */
    /* We use to have pointer elements added here.  We cannot do that,
       though, since it does not work when using 32-bit definitions
       on 64-bit platforms and vice versa.  */
  } a_un;
} Elf64_auxv_t;

#define AT_NULL 0    /* End of vector */
#define AT_IGNORE 1  /* Entry should be ignored */
#define AT_EXECFD 2  /* File descriptor of program */
#define AT_PHDR 3    /* Program headers for program */
#define AT_PHENT 4   /* Size of program header entry */
#define AT_PHNUM 5   /* Number of program headers */
#define AT_PAGESZ 6  /* System page size */
#define AT_BASE 7    /* Base address of interpreter */
#define AT_FLAGS 8   /* Flags */
#define AT_ENTRY 9   /* Entry point of program */
#define AT_NOTELF 10 /* Program is not ELF */
#define AT_UID 11    /* Real uid */
#define AT_EUID 12   /* Effective uid */
#define AT_GID 13    /* Real gid */
#define AT_EGID 14   /* Effective gid */
#define AT_CLKTCK 17 /* Frequency of times() */

/* Some more special a_type values describing the hardware.  */
#define AT_PLATFORM 15 /* String identifying platform.  */
#define AT_HWCAP                                                               \
  16 /* Machine-dependent hints about                                          \
        processor capabilities.  */

/* This entry gives some information about the FPU initialization
   performed by the kernel.  */
#define AT_FPUCW 18 /* Used FPU control word.  */

/* Cache block sizes.  */
#define AT_DCACHEBSIZE 19 /* Data cache block size.  */
#define AT_ICACHEBSIZE 20 /* Instruction cache block size.  */
#define AT_UCACHEBSIZE 21 /* Unified cache block size.  */

/* A special ignored value for PPC, used by the kernel to control the
   interpretation of the AUXV. Must be > 16.  */
#define AT_IGNOREPPC 22 /* Entry should be ignored.  */

#define AT_SECURE 23 /* Boolean, was exec setuid-like?  */

#define AT_BASE_PLATFORM 24 /* String identifying real platforms.*/

#define AT_RANDOM 25 /* Address of 16 random bytes.  */

#define AT_HWCAP2                                                              \
  26 /* More machine-dependent hints about                                     \
        processor capabilities.  */

#define AT_RSEQ_FEATURE_SIZE 27 /* rseq supported feature size.  */
#define AT_RSEQ_ALIGN 28        /* rseq allocation alignment.  */

#define AT_EXECFN 31 /* Filename of executable.  */

/* Pointer to the global system page used for system calls and other
   nice things.  */
#define AT_SYSINFO 32
#define AT_SYSINFO_EHDR 33

/* Shapes of the caches.  Bits 0-3 contains associativity; bits 4-7 contains
   log2 of line size; mask those to get cache size.  */
#define AT_L1I_CACHESHAPE 34
#define AT_L1D_CACHESHAPE 35
#define AT_L2_CACHESHAPE 36
#define AT_L3_CACHESHAPE 37

/* Shapes of the caches, with more room to describe them.
   *GEOMETRY are comprised of cache line size in bytes in the bottom 16 bits
   and the cache associativity in the next 16 bits.  */
#define AT_L1I_CACHESIZE 40
#define AT_L1I_CACHEGEOMETRY 41
#define AT_L1D_CACHESIZE 42
#define AT_L1D_CACHEGEOMETRY 43
#define AT_L2_CACHESIZE 44
#define AT_L2_CACHEGEOMETRY 45
#define AT_L3_CACHESIZE 46
#define AT_L3_CACHEGEOMETRY 47

#define AT_MINSIGSTKSZ 51 /* Stack needed for signal delivery  */

typedef struct {
  Elf32_Word n_namesz; /* Length of the note's name.  */
  Elf32_Word n_descsz; /* Length of the note's descriptor.  */
  Elf32_Word n_type;   /* Type of the note.  */
} Elf32_Nhdr;

typedef struct {
  Elf64_Word n_namesz; /* Length of the note's name.  */
  Elf64_Word n_descsz; /* Length of the note's descriptor.  */
  Elf64_Word n_type;   /* Type of the note.  */
} Elf64_Nhdr;

/* Solaris entries in the note section have this name.  */
#define ELF_NOTE_SOLARIS "SUNW Solaris"

/* Note entries for GNU systems have this name.  */
#define ELF_NOTE_GNU "GNU"

/* Note entries for freedesktop.org have this name.  */
#define ELF_NOTE_FDO "FDO"

#define ELF_NOTE_PAGESIZE_HINT 1

#define NT_GNU_ABI_TAG 1
#define ELF_NOTE_ABI NT_GNU_ABI_TAG /* Old name.  */

/* Known OSes.  These values can appear in word 0 of an
   NT_GNU_ABI_TAG note section entry.  */
#define ELF_NOTE_OS_LINUX 0
#define ELF_NOTE_OS_GNU 1
#define ELF_NOTE_OS_SOLARIS2 2
#define ELF_NOTE_OS_FREEBSD 3

/* Synthetic hwcap information.  The descriptor begins with two words:
   word 0: number of entries
   word 1: bitmask of enabled entries
   Then follow variable-length entries, one byte followed by a
   '\0'-terminated hwcap name string.  The byte gives the bit
   number to test if enabled, (1U << bit) & bitmask.  */
#define NT_GNU_HWCAP 2

/* Build ID bits as generated by ld --build-id.
   The descriptor consists of any nonzero number of bytes.  */
#define NT_GNU_BUILD_ID 3

/* Version note generated by GNU gold containing a version string.  */
#define NT_GNU_GOLD_VERSION 4

/* Program property.  */
#define NT_GNU_PROPERTY_TYPE_0 5

/* Packaging metadata as defined on
   https://systemd.io/COREDUMP_PACKAGE_METADATA/ */
#define NT_FDO_PACKAGING_METADATA 0xcafe1a7e

/* Note section name of program property.   */
#define NOTE_GNU_PROPERTY_SECTION_NAME ".note.gnu.property"

/* Values used in GNU .note.gnu.property notes (NT_GNU_PROPERTY_TYPE_0).  */

/* Stack size.  */
#define GNU_PROPERTY_STACK_SIZE 1
/* No copy relocation on protected data symbol.  */
#define GNU_PROPERTY_NO_COPY_ON_PROTECTED 2

/* A 4-byte unsigned integer property: A bit is set if it is set in all
   relocatable inputs.  */
#define GNU_PROPERTY_UINT32_AND_LO 0xb0000000
#define GNU_PROPERTY_UINT32_AND_HI 0xb0007fff

/* A 4-byte unsigned integer property: A bit is set if it is set in any
   relocatable inputs.  */
#define GNU_PROPERTY_UINT32_OR_LO 0xb0008000
#define GNU_PROPERTY_UINT32_OR_HI 0xb000ffff

/* The needed properties by the object file.  */
#define GNU_PROPERTY_1_NEEDED GNU_PROPERTY_UINT32_OR_LO

/* Set if the object file requires canonical function pointers and
   cannot be used with copy relocation.  */
#define GNU_PROPERTY_1_NEEDED_INDIRECT_EXTERN_ACCESS (1U << 0)

/* Processor-specific semantics, lo */
#define GNU_PROPERTY_LOPROC 0xc0000000
/* Processor-specific semantics, hi */
#define GNU_PROPERTY_HIPROC 0xdfffffff
/* Application-specific semantics, lo */
#define GNU_PROPERTY_LOUSER 0xe0000000
/* Application-specific semantics, hi */
#define GNU_PROPERTY_HIUSER 0xffffffff

/* AArch64 specific GNU properties.  */
#define GNU_PROPERTY_AARCH64_FEATURE_1_AND 0xc0000000

#define GNU_PROPERTY_AARCH64_FEATURE_1_BTI (1U << 0)
#define GNU_PROPERTY_AARCH64_FEATURE_1_PAC (1U << 1)

/* The x86 instruction sets indicated by the corresponding bits are
   used in program.  Their support in the hardware is optional.  */
#define GNU_PROPERTY_X86_ISA_1_USED 0xc0010002
/* The x86 instruction sets indicated by the corresponding bits are
   used in program and they must be supported by the hardware.   */
#define GNU_PROPERTY_X86_ISA_1_NEEDED 0xc0008002
/* X86 processor-specific features used in program.  */
#define GNU_PROPERTY_X86_FEATURE_1_AND 0xc0000002

/* GNU_PROPERTY_X86_ISA_1_BASELINE: CMOV, CX8 (cmpxchg8b), FPU (fld),
   MMX, OSFXSR (fxsave), SCE (syscall), SSE and SSE2.  */
#define GNU_PROPERTY_X86_ISA_1_BASELINE (1U << 0)
/* GNU_PROPERTY_X86_ISA_1_V2: GNU_PROPERTY_X86_ISA_1_BASELINE,
   CMPXCHG16B (cmpxchg16b), LAHF-SAHF (lahf), POPCNT (popcnt), SSE3,
   SSSE3, SSE4.1 and SSE4.2.  */
#define GNU_PROPERTY_X86_ISA_1_V2 (1U << 1)
/* GNU_PROPERTY_X86_ISA_1_V3: GNU_PROPERTY_X86_ISA_1_V2, AVX, AVX2, BMI1,
   BMI2, F16C, FMA, LZCNT, MOVBE, XSAVE.  */
#define GNU_PROPERTY_X86_ISA_1_V3 (1U << 2)
/* GNU_PROPERTY_X86_ISA_1_V4: GNU_PROPERTY_X86_ISA_1_V3, AVX512F,
   AVX512BW, AVX512CD, AVX512DQ and AVX512VL.  */
#define GNU_PROPERTY_X86_ISA_1_V4 (1U << 3)

/* This indicates that all executable sections are compatible with
   IBT.  */
#define GNU_PROPERTY_X86_FEATURE_1_IBT (1U << 0)
/* This indicates that all executable sections are compatible with
   SHSTK.  */
#define GNU_PROPERTY_X86_FEATURE_1_SHSTK (1U << 1)

typedef struct {
  Elf32_Xword m_value;  /* Symbol value.  */
  Elf32_Word m_info;    /* Size and index.  */
  Elf32_Word m_poffset; /* Symbol offset.  */
  Elf32_Half m_repeat;  /* Repeat count.  */
  Elf32_Half m_stride;  /* Stride info.  */
} Elf32_Move;

typedef struct {
  Elf64_Xword m_value;   /* Symbol value.  */
  Elf64_Xword m_info;    /* Size and index.  */
  Elf64_Xword m_poffset; /* Symbol offset.  */
  Elf64_Half m_repeat;   /* Repeat count.  */
  Elf64_Half m_stride;   /* Stride info.  */
} Elf64_Move;

#define ELF32_M_SYM(info) ((info) >> 8)
#define ELF32_M_SIZE(info) ((unsigned char)(info))
#define ELF32_M_INFO(sym, size) (((sym) << 8) + (unsigned char)(size))

#define ELF64_M_SYM(info) ELF32_M_SYM(info)
#define ELF64_M_SIZE(info) ELF32_M_SIZE(info)
#define ELF64_M_INFO(sym, size) ELF32_M_INFO(sym, size)

#define EF_CPU32 0x00810000

/* AArch64 relocs.  */

#define R_AARCH64_NONE 0 /* No relocation.  */

/* ILP32 AArch64 relocs.  */
#define R_AARCH64_P32_ABS32 1        /* Direct 32 bit.  */
#define R_AARCH64_P32_COPY 180       /* Copy symbol at runtime.  */
#define R_AARCH64_P32_GLOB_DAT 181   /* Create GOT entry.  */
#define R_AARCH64_P32_JUMP_SLOT 182  /* Create PLT entry.  */
#define R_AARCH64_P32_RELATIVE 183   /* Adjust by program base.  */
#define R_AARCH64_P32_TLS_DTPMOD 184 /* Module number, 32 bit.  */
#define R_AARCH64_P32_TLS_DTPREL 185 /* Module-relative offset, 32 bit.  */
#define R_AARCH64_P32_TLS_TPREL 186  /* TP-relative offset, 32 bit.  */
#define R_AARCH64_P32_TLSDESC 187    /* TLS Descriptor.  */
#define R_AARCH64_P32_IRELATIVE 188  /* STT_GNU_IFUNC relocation. */

/* LP64 AArch64 relocs.  */
#define R_AARCH64_ABS64 257            /* Direct 64 bit. */
#define R_AARCH64_ABS32 258            /* Direct 32 bit.  */
#define R_AARCH64_ABS16 259            /* Direct 16-bit.  */
#define R_AARCH64_PREL64 260           /* PC-relative 64-bit.	*/
#define R_AARCH64_PREL32 261           /* PC-relative 32-bit.	*/
#define R_AARCH64_PREL16 262           /* PC-relative 16-bit.	*/
#define R_AARCH64_MOVW_UABS_G0 263     /* Dir. MOVZ imm. from bits 15:0.  */
#define R_AARCH64_MOVW_UABS_G0_NC 264  /* Likewise for MOVK; no check.  */
#define R_AARCH64_MOVW_UABS_G1 265     /* Dir. MOVZ imm. from bits 31:16.  */
#define R_AARCH64_MOVW_UABS_G1_NC 266  /* Likewise for MOVK; no check.  */
#define R_AARCH64_MOVW_UABS_G2 267     /* Dir. MOVZ imm. from bits 47:32.  */
#define R_AARCH64_MOVW_UABS_G2_NC 268  /* Likewise for MOVK; no check.  */
#define R_AARCH64_MOVW_UABS_G3 269     /* Dir. MOV{K,Z} imm. from 63:48.  */
#define R_AARCH64_MOVW_SABS_G0 270     /* Dir. MOV{N,Z} imm. from 15:0.  */
#define R_AARCH64_MOVW_SABS_G1 271     /* Dir. MOV{N,Z} imm. from 31:16.  */
#define R_AARCH64_MOVW_SABS_G2 272     /* Dir. MOV{N,Z} imm. from 47:32.  */
#define R_AARCH64_LD_PREL_LO19 273     /* PC-rel. LD imm. from bits 20:2.  */
#define R_AARCH64_ADR_PREL_LO21 274    /* PC-rel. ADR imm. from bits 20:0.  */
#define R_AARCH64_ADR_PREL_PG_HI21 275 /* Page-rel. ADRP imm. from 32:12.  */
#define R_AARCH64_ADR_PREL_PG_HI21_NC 276 /* Likewise; no overflow check.  */
#define R_AARCH64_ADD_ABS_LO12_NC 277     /* Dir. ADD imm. from bits 11:0.  */
#define R_AARCH64_LDST8_ABS_LO12_NC 278   /* Likewise for LD/ST; no check. */
#define R_AARCH64_TSTBR14 279            /* PC-rel. TBZ/TBNZ imm. from 15:2.  */
#define R_AARCH64_CONDBR19 280           /* PC-rel. cond. br. imm. from 20:2. */
#define R_AARCH64_JUMP26 282             /* PC-rel. B imm. from bits 27:2.  */
#define R_AARCH64_CALL26 283             /* Likewise for CALL.  */
#define R_AARCH64_LDST16_ABS_LO12_NC 284 /* Dir. ADD imm. from bits 11:1.  */
#define R_AARCH64_LDST32_ABS_LO12_NC 285 /* Likewise for bits 11:2.  */
#define R_AARCH64_LDST64_ABS_LO12_NC 286 /* Likewise for bits 11:3.  */
#define R_AARCH64_MOVW_PREL_G0 287       /* PC-rel. MOV{N,Z} imm. from 15:0.  */
#define R_AARCH64_MOVW_PREL_G0_NC 288    /* Likewise for MOVK; no check.  */
#define R_AARCH64_MOVW_PREL_G1 289       /* PC-rel. MOV{N,Z} imm. from 31:16. */
#define R_AARCH64_MOVW_PREL_G1_NC 290    /* Likewise for MOVK; no check.  */
#define R_AARCH64_MOVW_PREL_G2 291       /* PC-rel. MOV{N,Z} imm. from 47:32. */
#define R_AARCH64_MOVW_PREL_G2_NC 292    /* Likewise for MOVK; no check.  */
#define R_AARCH64_MOVW_PREL_G3 293       /* PC-rel. MOV{N,Z} imm. from 63:48. */
#define R_AARCH64_LDST128_ABS_LO12_NC 299 /* Dir. ADD imm. from bits 11:4.  */
#define R_AARCH64_MOVW_GOTOFF_G0 300    /* GOT-rel. off. MOV{N,Z} imm. 15:0. */
#define R_AARCH64_MOVW_GOTOFF_G0_NC 301 /* Likewise for MOVK; no check.  */
#define R_AARCH64_MOVW_GOTOFF_G1 302    /* GOT-rel. o. MOV{N,Z} imm. 31:16.  */
#define R_AARCH64_MOVW_GOTOFF_G1_NC 303 /* Likewise for MOVK; no check.  */
#define R_AARCH64_MOVW_GOTOFF_G2 304    /* GOT-rel. o. MOV{N,Z} imm. 47:32.  */
#define R_AARCH64_MOVW_GOTOFF_G2_NC 305 /* Likewise for MOVK; no check.  */
#define R_AARCH64_MOVW_GOTOFF_G3 306    /* GOT-rel. o. MOV{N,Z} imm. 63:48.  */
#define R_AARCH64_GOTREL64 307          /* GOT-relative 64-bit.  */
#define R_AARCH64_GOTREL32 308          /* GOT-relative 32-bit.  */
#define R_AARCH64_GOT_LD_PREL19 309     /* PC-rel. GOT off. load imm. 20:2.  */
#define R_AARCH64_LD64_GOTOFF_LO15 310  /* GOT-rel. off. LD/ST imm. 14:3.  */
#define R_AARCH64_ADR_GOT_PAGE 311      /* P-page-rel. GOT off. ADRP 32:12.  */
#define R_AARCH64_LD64_GOT_LO12_NC 312  /* Dir. GOT off. LD/ST imm. 11:3.  */
#define R_AARCH64_LD64_GOTPAGE_LO15 313 /* GOT-page-rel. GOT off. LD/ST 14:3   \
                                         */
#define R_AARCH64_TLSGD_ADR_PREL21 512  /* PC-relative ADR imm. 20:0.  */
#define R_AARCH64_TLSGD_ADR_PAGE21 513  /* page-rel. ADRP imm. 32:12.  */
#define R_AARCH64_TLSGD_ADD_LO12_NC 514 /* direct ADD imm. from 11:0.  */
#define R_AARCH64_TLSGD_MOVW_G1 515     /* GOT-rel. MOV{N,Z} 31:16.  */
#define R_AARCH64_TLSGD_MOVW_G0_NC 516  /* GOT-rel. MOVK imm. 15:0.  */
#define R_AARCH64_TLSLD_ADR_PREL21 517  /* Like 512; local dynamic model.  */
#define R_AARCH64_TLSLD_ADR_PAGE21 518  /* Like 513; local dynamic model.  */
#define R_AARCH64_TLSLD_ADD_LO12_NC 519 /* Like 514; local dynamic model.  */
#define R_AARCH64_TLSLD_MOVW_G1 520     /* Like 515; local dynamic model.  */
#define R_AARCH64_TLSLD_MOVW_G0_NC 521  /* Like 516; local dynamic model.  */
#define R_AARCH64_TLSLD_LD_PREL19 522   /* TLS PC-rel. load imm. 20:2.  */
#define R_AARCH64_TLSLD_MOVW_DTPREL_G2 523 /* TLS DTP-rel. MOV{N,Z} 47:32.  */
#define R_AARCH64_TLSLD_MOVW_DTPREL_G1 524 /* TLS DTP-rel. MOV{N,Z} 31:16.  */
#define R_AARCH64_TLSLD_MOVW_DTPREL_G1_NC 525 /* Likewise; MOVK; no check.  */
#define R_AARCH64_TLSLD_MOVW_DTPREL_G0 526    /* TLS DTP-rel. MOV{N,Z} 15:0.  */
#define R_AARCH64_TLSLD_MOVW_DTPREL_G0_NC 527 /* Likewise; MOVK; no check.  */
#define R_AARCH64_TLSLD_ADD_DTPREL_HI12 528   /* DTP-rel. ADD imm. from 23:12. \
                                               */
#define R_AARCH64_TLSLD_ADD_DTPREL_LO12 529   /* DTP-rel. ADD imm. from 11:0.   */
#define R_AARCH64_TLSLD_ADD_DTPREL_LO12_NC 530 /* Likewise; no ovfl. check. */
#define R_AARCH64_TLSLD_LDST8_DTPREL_LO12 531  /* DTP-rel. LD/ST imm. 11:0.  */
#define R_AARCH64_TLSLD_LDST8_DTPREL_LO12_NC 532 /* Likewise; no check.  */
#define R_AARCH64_TLSLD_LDST16_DTPREL_LO12 533   /* DTP-rel. LD/ST imm. 11:1.   */
#define R_AARCH64_TLSLD_LDST16_DTPREL_LO12_NC 534 /* Likewise; no check.  */
#define R_AARCH64_TLSLD_LDST32_DTPREL_LO12 535 /* DTP-rel. LD/ST imm. 11:2. */
#define R_AARCH64_TLSLD_LDST32_DTPREL_LO12_NC 536 /* Likewise; no check.  */
#define R_AARCH64_TLSLD_LDST64_DTPREL_LO12 537 /* DTP-rel. LD/ST imm. 11:3. */
#define R_AARCH64_TLSLD_LDST64_DTPREL_LO12_NC 538 /* Likewise; no check.  */
#define R_AARCH64_TLSIE_MOVW_GOTTPREL_G1 539    /* GOT-rel. MOV{N,Z} 31:16.  */
#define R_AARCH64_TLSIE_MOVW_GOTTPREL_G0_NC 540 /* GOT-rel. MOVK 15:0.  */
#define R_AARCH64_TLSIE_ADR_GOTTPREL_PAGE21 541 /* Page-rel. ADRP 32:12.  */
#define R_AARCH64_TLSIE_LD64_GOTTPREL_LO12_NC 542 /* Direct LD off. 11:3.  */
#define R_AARCH64_TLSIE_LD_GOTTPREL_PREL19 543    /* PC-rel. load imm. 20:2.  */
#define R_AARCH64_TLSLE_MOVW_TPREL_G2 544     /* TLS TP-rel. MOV{N,Z} 47:32.  */
#define R_AARCH64_TLSLE_MOVW_TPREL_G1 545     /* TLS TP-rel. MOV{N,Z} 31:16.  */
#define R_AARCH64_TLSLE_MOVW_TPREL_G1_NC 546  /* Likewise; MOVK; no check.  */
#define R_AARCH64_TLSLE_MOVW_TPREL_G0 547     /* TLS TP-rel. MOV{N,Z} 15:0.  */
#define R_AARCH64_TLSLE_MOVW_TPREL_G0_NC 548  /* Likewise; MOVK; no check.  */
#define R_AARCH64_TLSLE_ADD_TPREL_HI12 549    /* TP-rel. ADD imm. 23:12.  */
#define R_AARCH64_TLSLE_ADD_TPREL_LO12 550    /* TP-rel. ADD imm. 11:0.  */
#define R_AARCH64_TLSLE_ADD_TPREL_LO12_NC 551 /* Likewise; no ovfl. check.  */
#define R_AARCH64_TLSLE_LDST8_TPREL_LO12 552  /* TP-rel. LD/ST off. 11:0.  */
#define R_AARCH64_TLSLE_LDST8_TPREL_LO12_NC 553  /* Likewise; no ovfl. check.  \
                                                  */
#define R_AARCH64_TLSLE_LDST16_TPREL_LO12 554    /* TP-rel. LD/ST off. 11:1.  */
#define R_AARCH64_TLSLE_LDST16_TPREL_LO12_NC 555 /* Likewise; no check.  */
#define R_AARCH64_TLSLE_LDST32_TPREL_LO12 556    /* TP-rel. LD/ST off. 11:2.  */
#define R_AARCH64_TLSLE_LDST32_TPREL_LO12_NC 557 /* Likewise; no check.  */
#define R_AARCH64_TLSLE_LDST64_TPREL_LO12 558    /* TP-rel. LD/ST off. 11:3.  */
#define R_AARCH64_TLSLE_LDST64_TPREL_LO12_NC 559 /* Likewise; no check.  */
#define R_AARCH64_TLSDESC_LD_PREL19 560  /* PC-rel. load immediate 20:2.  */
#define R_AARCH64_TLSDESC_ADR_PREL21 561 /* PC-rel. ADR immediate 20:0.  */
#define R_AARCH64_TLSDESC_ADR_PAGE21 562 /* Page-rel. ADRP imm. 32:12.  */
#define R_AARCH64_TLSDESC_LD64_LO12 563  /* Direct LD off. from 11:3.  */
#define R_AARCH64_TLSDESC_ADD_LO12 564   /* Direct ADD imm. from 11:0.  */
#define R_AARCH64_TLSDESC_OFF_G1 565     /* GOT-rel. MOV{N,Z} imm. 31:16.  */
#define R_AARCH64_TLSDESC_OFF_G0_NC 566  /* GOT-rel. MOVK imm. 15:0; no ck.  */
#define R_AARCH64_TLSDESC_LDR 567        /* Relax LDR.  */
#define R_AARCH64_TLSDESC_ADD 568        /* Relax ADD.  */
#define R_AARCH64_TLSDESC_CALL 569       /* Relax BLR.  */
#define R_AARCH64_TLSLE_LDST128_TPREL_LO12 570 /* TP-rel. LD/ST off. 11:4.  */
#define R_AARCH64_TLSLE_LDST128_TPREL_LO12_NC 571 /* Likewise; no check.  */
#define R_AARCH64_TLSLD_LDST128_DTPREL_LO12 572   /* DTP-rel. LD/ST imm. 11:4. \
                                                   */
#define R_AARCH64_TLSLD_LDST128_DTPREL_LO12_NC 573 /* Likewise; no check.  */
#define R_AARCH64_COPY 1024       /* Copy symbol at runtime.  */
#define R_AARCH64_GLOB_DAT 1025   /* Create GOT entry.  */
#define R_AARCH64_JUMP_SLOT 1026  /* Create PLT entry.  */
#define R_AARCH64_RELATIVE 1027   /* Adjust by program base.  */
#define R_AARCH64_TLS_DTPMOD 1028 /* Module number, 64 bit.  */
#define R_AARCH64_TLS_DTPREL 1029 /* Module-relative offset, 64 bit.  */
#define R_AARCH64_TLS_TPREL 1030  /* TP-relative offset, 64 bit.  */
#define R_AARCH64_TLSDESC 1031    /* TLS Descriptor.  */
#define R_AARCH64_IRELATIVE 1032  /* STT_GNU_IFUNC relocation.  */

/* MTE memory tag segment type.  */
#define PT_AARCH64_MEMTAG_MTE (PT_LOPROC + 2)

/* AArch64 specific values for the Dyn d_tag field.  */
#define DT_AARCH64_BTI_PLT (DT_LOPROC + 1)
#define DT_AARCH64_PAC_PLT (DT_LOPROC + 3)
#define DT_AARCH64_VARIANT_PCS (DT_LOPROC + 5)
#define DT_AARCH64_NUM 6

/* AArch64 specific values for the st_other field.  */
#define STO_AARCH64_VARIANT_PCS 0x80

/* AMD x86-64 relocations.  */
#define R_X86_64_NONE 0      /* No reloc */
#define R_X86_64_64 1        /* Direct 64 bit  */
#define R_X86_64_PC32 2      /* PC relative 32 bit signed */
#define R_X86_64_GOT32 3     /* 32 bit GOT entry */
#define R_X86_64_PLT32 4     /* 32 bit PLT address */
#define R_X86_64_COPY 5      /* Copy symbol at runtime */
#define R_X86_64_GLOB_DAT 6  /* Create GOT entry */
#define R_X86_64_JUMP_SLOT 7 /* Create PLT entry */
#define R_X86_64_RELATIVE 8  /* Adjust by program base */
#define R_X86_64_GOTPCREL                                                      \
  9                          /* 32 bit signed PC relative                      \
                                offset to GOT */
#define R_X86_64_32 10       /* Direct 32 bit zero extended */
#define R_X86_64_32S 11      /* Direct 32 bit sign extended */
#define R_X86_64_16 12       /* Direct 16 bit zero extended */
#define R_X86_64_PC16 13     /* 16 bit sign extended pc relative */
#define R_X86_64_8 14        /* Direct 8 bit sign extended  */
#define R_X86_64_PC8 15      /* 8 bit sign extended pc relative */
#define R_X86_64_DTPMOD64 16 /* ID of module containing symbol */
#define R_X86_64_DTPOFF64 17 /* Offset in module's TLS block */
#define R_X86_64_TPOFF64 18  /* Offset in initial TLS block */
#define R_X86_64_TLSGD                                                         \
  19 /* 32 bit signed PC relative offset                                       \
        to two GOT entries for GD symbol */
#define R_X86_64_TLSLD                                                         \
  20                         /* 32 bit signed PC relative offset               \
                                to two GOT entries for LD symbol */
#define R_X86_64_DTPOFF32 21 /* Offset in TLS block */
#define R_X86_64_GOTTPOFF                                                      \
  22                         /* 32 bit signed PC relative offset               \
                                to GOT entry for IE symbol */
#define R_X86_64_TPOFF32 23  /* Offset in initial TLS block */
#define R_X86_64_PC64 24     /* PC relative 64 bit */
#define R_X86_64_GOTOFF64 25 /* 64 bit offset to GOT */
#define R_X86_64_GOTPC32                                                       \
  26                      /* 32 bit signed pc relative                         \
                             offset to GOT */
#define R_X86_64_GOT64 27 /* 64-bit GOT entry offset */
#define R_X86_64_GOTPCREL64                                                    \
  28                         /* 64-bit PC relative offset                      \
                                to GOT entry */
#define R_X86_64_GOTPC64 29  /* 64-bit PC relative offset to GOT */
#define R_X86_64_GOTPLT64 30 /* like GOT64, says PLT entry needed */
#define R_X86_64_PLTOFF64                                                      \
  31                                /* 64-bit GOT relative offset              \
                                       to PLT entry */
#define R_X86_64_SIZE32 32          /* Size of symbol plus 32-bit addend */
#define R_X86_64_SIZE64 33          /* Size of symbol plus 64-bit addend */
#define R_X86_64_GOTPC32_TLSDESC 34 /* GOT offset for TLS descriptor.  */
#define R_X86_64_TLSDESC_CALL                                                  \
  35                           /* Marker for call through TLS                  \
                                  descriptor.  */
#define R_X86_64_TLSDESC 36    /* TLS descriptor.  */
#define R_X86_64_IRELATIVE 37  /* Adjust indirectly by program base */
#define R_X86_64_RELATIVE64 38 /* 64-bit adjust by program base */
                               /* 39 Reserved was R_X86_64_PC32_BND */
                               /* 40 Reserved was R_X86_64_PLT32_BND */
#define R_X86_64_GOTPCRELX                                                     \
  41 /* Load from 32 bit signed pc relative                                    \
        offset to GOT entry without REX                                        \
        prefix, relaxable.  */
#define R_X86_64_REX_GOTPCRELX                                                 \
  42 /* Load from 32 bit signed pc relative                                    \
        offset to GOT entry with REX prefix,                                   \
        relaxable.  */
#define R_X86_64_NUM 43

/* x86-64 sh_type values.  */
#define SHT_X86_64_UNWIND 0x70000001 /* Unwind information.  */

/* RISC-V ELF Flags */
#define EF_RISCV_RVC 0x0001
#define EF_RISCV_FLOAT_ABI 0x0006
#define EF_RISCV_FLOAT_ABI_SOFT 0x0000
#define EF_RISCV_FLOAT_ABI_SINGLE 0x0002
#define EF_RISCV_FLOAT_ABI_DOUBLE 0x0004
#define EF_RISCV_FLOAT_ABI_QUAD 0x0006
#define EF_RISCV_RVE 0x0008
#define EF_RISCV_TSO 0x0010

/* RISC-V relocations.  */
#define R_RISCV_NONE 0
#define R_RISCV_32 1
#define R_RISCV_64 2
#define R_RISCV_RELATIVE 3
#define R_RISCV_COPY 4
#define R_RISCV_JUMP_SLOT 5
#define R_RISCV_TLS_DTPMOD32 6
#define R_RISCV_TLS_DTPMOD64 7
#define R_RISCV_TLS_DTPREL32 8
#define R_RISCV_TLS_DTPREL64 9
#define R_RISCV_TLS_TPREL32 10
#define R_RISCV_TLS_TPREL64 11
#define R_RISCV_BRANCH 16
#define R_RISCV_JAL 17
#define R_RISCV_CALL 18
#define R_RISCV_CALL_PLT 19
#define R_RISCV_GOT_HI20 20
#define R_RISCV_TLS_GOT_HI20 21
#define R_RISCV_TLS_GD_HI20 22
#define R_RISCV_PCREL_HI20 23
#define R_RISCV_PCREL_LO12_I 24
#define R_RISCV_PCREL_LO12_S 25
#define R_RISCV_HI20 26
#define R_RISCV_LO12_I 27
#define R_RISCV_LO12_S 28
#define R_RISCV_TPREL_HI20 29
#define R_RISCV_TPREL_LO12_I 30
#define R_RISCV_TPREL_LO12_S 31
#define R_RISCV_TPREL_ADD 32
#define R_RISCV_ADD8 33
#define R_RISCV_ADD16 34
#define R_RISCV_ADD32 35
#define R_RISCV_ADD64 36
#define R_RISCV_SUB8 37
#define R_RISCV_SUB16 38
#define R_RISCV_SUB32 39
#define R_RISCV_SUB64 40
#define R_RISCV_GNU_VTINHERIT 41
#define R_RISCV_GNU_VTENTRY 42
#define R_RISCV_ALIGN 43
#define R_RISCV_RVC_BRANCH 44
#define R_RISCV_RVC_JUMP 45
#define R_RISCV_RVC_LUI 46
#define R_RISCV_GPREL_I 47
#define R_RISCV_GPREL_S 48
#define R_RISCV_TPREL_I 49
#define R_RISCV_TPREL_S 50
#define R_RISCV_RELAX 51
#define R_RISCV_SUB6 52
#define R_RISCV_SET6 53
#define R_RISCV_SET8 54
#define R_RISCV_SET16 55
#define R_RISCV_SET32 56
#define R_RISCV_32_PCREL 57
#define R_RISCV_IRELATIVE 58

#define R_RISCV_NUM 59

/* RISC-V specific values for the st_other field.  */
#define STO_RISCV_VARIANT_CC                                                   \
  0x80 /* Function uses variant calling                                        \
          convention */

/* RISC-V specific values for the sh_type field.  */
#define SHT_RISCV_ATTRIBUTES (SHT_LOPROC + 3)

/* RISC-V specific values for the p_type field.  */
#define PT_RISCV_ATTRIBUTES (PT_LOPROC + 3)

/* RISC-V specific values for the d_tag field.  */
#define DT_RISCV_VARIANT_CC (DT_LOPROC + 1)

/* BPF specific declarations.  */

#define R_BPF_NONE 0 /* No reloc */
#define R_BPF_64_64 1
#define R_BPF_64_32 10

/* Xtensa-specific declarations */

/* Xtensa values for the Dyn d_tag field.  */
#define DT_XTENSA_GOT_LOC_OFF (DT_LOPROC + 0)
#define DT_XTENSA_GOT_LOC_SZ (DT_LOPROC + 1)
#define DT_XTENSA_NUM 2

/* Xtensa relocations.  */
#define R_XTENSA_NONE 0
#define R_XTENSA_32 1
#define R_XTENSA_RTLD 2
#define R_XTENSA_GLOB_DAT 3
#define R_XTENSA_JMP_SLOT 4
#define R_XTENSA_RELATIVE 5
#define R_XTENSA_PLT 6
#define R_XTENSA_OP0 8
#define R_XTENSA_OP1 9
#define R_XTENSA_OP2 10
#define R_XTENSA_ASM_EXPAND 11
#define R_XTENSA_ASM_SIMPLIFY 12
#define R_XTENSA_GNU_VTINHERIT 15
#define R_XTENSA_GNU_VTENTRY 16
#define R_XTENSA_DIFF8 17
#define R_XTENSA_DIFF16 18
#define R_XTENSA_DIFF32 19
#define R_XTENSA_SLOT0_OP 20
#define R_XTENSA_SLOT1_OP 21
#define R_XTENSA_SLOT2_OP 22
#define R_XTENSA_SLOT3_OP 23
#define R_XTENSA_SLOT4_OP 24
#define R_XTENSA_SLOT5_OP 25
#define R_XTENSA_SLOT6_OP 26
#define R_XTENSA_SLOT7_OP 27
#define R_XTENSA_SLOT8_OP 28
#define R_XTENSA_SLOT9_OP 29
#define R_XTENSA_SLOT10_OP 30
#define R_XTENSA_SLOT11_OP 31
#define R_XTENSA_SLOT12_OP 32
#define R_XTENSA_SLOT13_OP 33
#define R_XTENSA_SLOT14_OP 34
#define R_XTENSA_SLOT0_ALT 35
#define R_XTENSA_SLOT1_ALT 36
#define R_XTENSA_SLOT2_ALT 37
#define R_XTENSA_SLOT3_ALT 38
#define R_XTENSA_SLOT4_ALT 39
#define R_XTENSA_SLOT5_ALT 40
#define R_XTENSA_SLOT6_ALT 41
#define R_XTENSA_SLOT7_ALT 42
#define R_XTENSA_SLOT8_ALT 43
#define R_XTENSA_SLOT9_ALT 44
#define R_XTENSA_SLOT10_ALT 45
#define R_XTENSA_SLOT11_ALT 46
#define R_XTENSA_SLOT12_ALT 47
#define R_XTENSA_SLOT13_ALT 48
#define R_XTENSA_SLOT14_ALT 49
/* Keep this the last entry.  */
#define R_XTENSA_NUM 50

#endif /* !_ELF_H_ */
