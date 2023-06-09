# Steps to implement libc
## Headers
 * Add locales support
 * Add ctype and wctype support
 * Add uchar support
 * Add malloc support
 * Finish string.h and add strings.h
 * Add signal and setjmp support
 * Add wchar support
 * Add threading support (pthread, spawn, semaphore and C11 threads)
 * Add stdlib
 * Add stdio support, regular and wide character
 * Add fenv support
 * The rest will be POSIX implementation and GNU extensions

## Functionality
 * Add ELF Thread-local storage support
 * Add LLVM safestack support
 * Add LLVM shadow call stack support
 * Add Smash Stack Guard support
 * Add HWAsan
 * Backtracing and execinfo.h
 * .eh_frame support
 * _FORTIFY_SOURCE support

## Dynamic linking functionality
 * Add support for ELF Thread-local storage support
 * Add support for LLVM Cross-DSO CFI
