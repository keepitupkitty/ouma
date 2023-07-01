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

#ifndef _SYS_CDEFS_H
#define _SYS_CDEFS_H

/*
 * Define Ouma libc macro
 */
#ifndef __ouma_
#define __ouma__ 1
#endif
#ifndef __oumalibc__
#define __oumalibc__ 1
#endif
#ifndef __OUMA__
#define __OUMA__ 1
#endif
#ifndef __OUMALIBC__
#define __OUMALIBC__ 1
#endif

/*
 * Testing against Clang-specific extensions.
 */
#ifndef __has_attribute
#define __has_attribute(x) 0
#endif
#ifndef __has_extension
#define __has_extension __has_feature
#endif
#ifndef __has_feature
#define __has_feature(x) 0
#endif
#ifndef __has_include
#define __has_include(x) 0
#endif
#ifndef __has_builtin
#define __has_builtin(x) 0
#endif

#if defined(__GNUC__)
#define __GNUC_PREREQ__(ma, mi) \
  (__GNUC__ > (ma) || __GNUC__ == (ma) && __GNUC_MINOR__ >= (mi))
#else
#define __GNUC_PREREQ__(ma, mi) 0
#endif

#if defined(__cplusplus)
#define __BEGIN_EXTERN_C extern "C" {
#define __END_EXTERN_C }
#else
#define __BEGIN_EXTERN_C
#define __END_EXTERN_C
#endif

#if __GNUC_PREREQ__(4, 0)
#define __dso_public __attribute__((__visibility__("default")))
#define __dso_hidden __attribute__((__visibility__("hidden")))
#define __BEGIN_PUBLIC_DECLS \
  _Pragma("GCC visibility push(default)") __BEGIN_EXTERN_C
#define __END_PUBLIC_DECLS __END_EXTERN_C _Pragma("GCC visibility pop")
#define __BEGIN_HIDDEN_DECLS \
  _Pragma("GCC visibility push(hidden)") __BEGIN_EXTERN_C
#define __END_HIDDEN_DECLS __END_EXTERN_C _Pragma("GCC visibility pop")
#else
#define __dso_public
#define __dso_hidden
#define __BEGIN_PUBLIC_DECLS __BEGIN_EXTERN_C
#define __END_PUBLIC_DECLS __END_EXTERN_C
#define __BEGIN_HIDDEN_DECLS __BEGIN_EXTERN_C
#define __END_HIDDEN_DECLS __END_EXTERN_C
#endif

#define __BEGIN_DECLS __BEGIN_EXTERN_C
#define __END_DECLS __END_EXTERN_C

/*
 * Compiler-dependent macros to help declare dead (non-returning) and
 * pure (no side effects) functions, and unused variables.  They are
 * null except for versions of gcc that are known to support the features
 * properly (old versions of gcc-2 supported the dead and pure features
 * in a different (wrong) way).  If we do not provide an implementation
 * for a given compiler, let the compile fail if it is told to use
 * a feature that we cannot live without.
 */
#define __weak_symbol __attribute__((__weak__))
#if !__GNUC_PREREQ__(2, 5)
#define __dead2
#define __pure2
#define __unused
#endif
#if __GNUC__ == 2 && __GNUC_MINOR__ >= 5 && __GNUC_MINOR__ < 7
#define __dead2 __attribute__((__noreturn__))
#define __pure2 __attribute__((__const__))
#define __unused
/* XXX Find out what to do for __packed, __aligned and __section */
#endif
#if __GNUC_PREREQ__(2, 7)
#define __dead2 __attribute__((__noreturn__))
#define __pure2 __attribute__((__const__))
#define __unused __attribute__((__unused__))
#define __used __attribute__((__used__))
#define __packed __attribute__((__packed__))
#define __aligned(x) __attribute__((__aligned__(x)))
#define __section(x) __attribute__((__section__(x)))
#endif
#if __GNUC_PREREQ__(4, 3) || __has_attribute(__alloc_size__)
#define __alloc_size(x) __attribute__((__alloc_size__(x)))
#define __alloc_size2(n, x) __attribute__((__alloc_size__(n, x)))
#else
#define __alloc_size(x)
#define __alloc_size2(n, x)
#endif
#if __GNUC_PREREQ__(4, 9) || __has_attribute(__alloc_align__)
#define __alloc_align(x) __attribute__((__alloc_align__(x)))
#else
#define __alloc_align(x)
#endif

#if !__GNUC_PREREQ__(2, 95)
#define __alignof(x) \
  __offsetof(        \
      struct {       \
        char __a;    \
        x __b;       \
      },             \
      __b)
#endif

/*
 * Keywords added in C11.
 */

#if !defined(__STDC_VERSION__) || __STDC_VERSION__ < 201112L

#if !__has_extension(c_alignas)
#if (defined(__cplusplus) && __cplusplus >= 201103L) || \
    __has_extension(cxx_alignas)
#define _Alignas(x) alignas(x)
#else
/* XXX: Only emulates _Alignas(constant-expression); not _Alignas(type-name). */
#define _Alignas(x) __aligned(x)
#endif
#endif

#if defined(__cplusplus) && __cplusplus >= 201103L
#define _Alignof(x) alignof(x)
#else
#define _Alignof(x) __alignof(x)
#endif

#if !defined(__cplusplus) && !__has_extension(c_atomic) && \
    !__has_extension(cxx_atomic) && !__GNUC_PREREQ__(4, 7)
/*
 * No native support for _Atomic(). Place object in structure to prevent
 * most forms of direct non-atomic access.
 */
#define _Atomic(T)    \
  struct {            \
    T volatile __val; \
  }
#endif

#if defined(__cplusplus) && __cplusplus >= 201103L
#define _Noreturn [[noreturn]]
#else
#define _Noreturn __dead2
#endif

#if !__has_extension(c_static_assert)
#if (defined(__cplusplus) && __cplusplus >= 201103L) || \
    __has_extension(cxx_static_assert)
#define _Static_assert(x, y) static_assert(x, y)
#elif __GNUC_PREREQ__(4, 6) && !defined(__cplusplus)
/* Nothing, gcc 4.6 and higher has _Static_assert built-in */
#elif defined(__COUNTER__)
#define _Static_assert(x, y) __Static_assert(x, __COUNTER__)
#define __Static_assert(x, y) ___Static_assert(x, y)
#define ___Static_assert(x, y) typedef char __assert_##y[(x) ? 1 : -1] __unused
#else
#define _Static_assert(x, y) struct __hack
#endif
#endif

#if !__has_extension(c_thread_local)
/*
 * XXX: Some compilers (Clang 3.3, GCC 4.7) falsely announce C++11 mode
 * without actually supporting the thread_local keyword. Don't check for
 * the presence of C++11 when defining _Thread_local.
 */
#if /* (defined(__cplusplus) && __cplusplus >= 201103L) || */ \
    __has_extension(cxx_thread_local)
#define _Thread_local thread_local
#else
#define _Thread_local __thread
#endif
#endif

#endif /* __STDC_VERSION__ || __STDC_VERSION__ < 201112L */

/*
 * Emulation of C11 _Generic().  Unlike the previously defined C11
 * keywords, it is not possible to implement this using exactly the same
 * syntax.  Therefore implement something similar under the name
 * __generic().  Unlike _Generic(), this macro can only distinguish
 * between a single type, so it requires nested invocations to
 * distinguish multiple cases.
 *
 * Note that the comma operator is used to force expr to decay in
 * order to match _Generic().
 */

#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L) || \
    __has_extension(c_generic_selections)
#define __generic(expr, t, yes, no) _Generic(expr, t: yes, default: no)
#elif __GNUC_PREREQ__(3, 1) && !defined(__cplusplus)
#define __generic(expr, t, yes, no) \
  __builtin_choose_expr(            \
      __builtin_types_compatible_p(__typeof((0, (expr))), t), yes, no)
#endif

/*
 * GCC 2.95 provides `__restrict' as an extension to C90 to support the
 * C99-specific `restrict' type qualifier.  We happen to use `__restrict' as
 * a way to define the `restrict' type qualifier without disturbing older
 * software that is unaware of C99 keywords.
 */
#if !(__GNUC__ == 2 && __GNUC_MINOR__ == 95)
#if !defined(__STDC_VERSION__) || __STDC_VERSION__ < 199901
#define __restrict
#else
#define __restrict restrict
#endif
#endif

#if __GNUC_PREREQ__(4, 0)
#define __null_sentinel __attribute__((__sentinel__))
#define __exported __attribute__((__visibility__("default")))
#define __hidden __attribute__((__visibility__("hidden")))
#else
#define __null_sentinel
#define __exported
#define __hidden
#endif

/*
 * Compiler-dependent macros to declare that functions take printf-like
 * or scanf-like arguments.  They are null except for versions of gcc
 * that are known to support the features properly (old versions of gcc-2
 * didn't permit keeping the keywords out of the application namespace).
 */
#if !__GNUC_PREREQ__(2, 7)
#define __printflike(fmtarg, firstvararg)
#define __scanflike(fmtarg, firstvararg)
#else
#define __printflike(fmtarg, firstvararg) \
  __attribute__((__format__(__printf__, fmtarg, firstvararg)))
#define __scanflike(fmtarg, firstvararg) \
  __attribute__((__format__(__scanf__, fmtarg, firstvararg)))
#endif

/*-
 * The following definitions are an extension of the behavior originally
 * implemented in <sys/_posix.h>, but with a different level of granularity.
 * POSIX.1 requires that the macros we test be defined before any standard
 * header file is included.
 *
 * Here's a quick run-down of the versions (and some informal names)
 *  defined(_POSIX_SOURCE)		1003.1-1988
 *					encoded as 198808 below
 *  _POSIX_C_SOURCE == 1		1003.1-1990
 *					encoded as 199009 below
 *  _POSIX_C_SOURCE == 2		1003.2-1992 C Language Binding Option
 *					encoded as 199209 below
 *  _POSIX_C_SOURCE == 199309		1003.1b-1993
 *					(1003.1 Issue 4, Single Unix Spec v1,
 *Unix 93) _POSIX_C_SOURCE == 199506		1003.1c-1995, 1003.1i-1995, and
 *the
 *omnibus ISO/IEC 9945-1: 1996 (1003.1 Issue 5, Single	Unix Spec v2, Unix 95)
 *  _POSIX_C_SOURCE == 200112		1003.1-2001 (1003.1 Issue 6, Unix 03)
 *  _POSIX_C_SOURCE == 200809		1003.1-2008 (1003.1 Issue 7)
 *					IEEE Std 1003.1-2017 (Rev of
 *1003.1-2008) is 1003.1-2008 with two TCs applied with _POSIX_C_SOURCE=200809
 *and _XOPEN_SOURCE=700
 *
 * In addition, the X/Open Portability Guide, which is now the Single UNIX
 * Specification, defines a feature-test macro which indicates the version of
 * that specification, and which subsumes _POSIX_C_SOURCE.
 *
 * Our macros begin with two underscores to avoid namespace screwage.
 */

/* Deal with IEEE Std. 1003.1-1990, in which _POSIX_C_SOURCE == 1. */
#if defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE == 1
#undef _POSIX_C_SOURCE /* Probably illegal, but beyond caring now. */
#define _POSIX_C_SOURCE 199009
#endif

/* Deal with IEEE Std. 1003.2-1992, in which _POSIX_C_SOURCE == 2. */
#if defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE == 2
#undef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 199209
#endif

/* Deal with various X/Open Portability Guides and Single UNIX Spec. */
#ifdef _XOPEN_SOURCE
#if _XOPEN_SOURCE - 0 >= 700
#define __XSI_VISIBLE 700
#undef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200809
#elif _XOPEN_SOURCE - 0 >= 600
#define __XSI_VISIBLE 600
#undef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200112
#elif _XOPEN_SOURCE - 0 >= 500
#define __XSI_VISIBLE 500
#undef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 199506
#endif
#endif

/*
 * Deal with all versions of POSIX.  The ordering relative to the tests above is
 * important.
 */
#if defined(_POSIX_SOURCE) && !defined(_POSIX_C_SOURCE)
#define _POSIX_C_SOURCE 198808
#endif
#ifdef _POSIX_C_SOURCE
#if _POSIX_C_SOURCE >= 200809
#define __POSIX_VISIBLE 200809
#define __ISO_C_VISIBLE 1999
#elif _POSIX_C_SOURCE >= 200112
#define __POSIX_VISIBLE 200112
#define __ISO_C_VISIBLE 1999
#elif _POSIX_C_SOURCE >= 199506
#define __POSIX_VISIBLE 199506
#define __ISO_C_VISIBLE 1990
#elif _POSIX_C_SOURCE >= 199309
#define __POSIX_VISIBLE 199309
#define __ISO_C_VISIBLE 1990
#elif _POSIX_C_SOURCE >= 199209
#define __POSIX_VISIBLE 199209
#define __ISO_C_VISIBLE 1990
#elif _POSIX_C_SOURCE >= 199009
#define __POSIX_VISIBLE 199009
#define __ISO_C_VISIBLE 1990
#else
#define __POSIX_VISIBLE 198808
#define __ISO_C_VISIBLE 0
#endif /* _POSIX_C_SOURCE */
/*
 * Both glibc and OpenBSD enable c11 features when _ISOC11_SOURCE is defined, or
 * when compiling with -stdc=c11. A strict reading of the standard would suggest
 * doing it only for the former. However, a strict reading also requires C99
 * mode only, so building with C11 is already undefined. Follow glibc's and
 * OpenBSD's lead for this non-standard configuration for maximum compatibility.
 */
#if _ISOC11_SOURCE || (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L)
#undef __ISO_C_VISIBLE
#define __ISO_C_VISIBLE 2011
#endif
#else
/*-
 * Deal with _ANSI_SOURCE:
 * If it is defined, and no other compilation environment is explicitly
 * requested, then define our internal feature-test macros to zero.  This
 * makes no difference to the preprocessor (undefined symbols in preprocessing
 * expressions are defined to have value zero), but makes it more convenient for
 * a test program to print out the values.
 *
 * If a program mistakenly defines _ANSI_SOURCE and some other macro such as
 * _POSIX_C_SOURCE, we will assume that it wants the broader compilation
 * environment (and in fact we will never get here).
 */
#if defined(_ANSI_SOURCE) /* Hide almost everything. */
#define __POSIX_VISIBLE 0
#define __XSI_VISIBLE 0
#define __BSD_VISIBLE 0
#define __ISO_C_VISIBLE 1990
#define __EXT1_VISIBLE 0
#elif defined(_C99_SOURCE) /* Localism to specify strict C99 env. */
#define __POSIX_VISIBLE 0
#define __XSI_VISIBLE 0
#define __BSD_VISIBLE 0
#define __ISO_C_VISIBLE 1999
#define __EXT1_VISIBLE 0
#elif defined(_C11_SOURCE) /* Localism to specify strict C11 env. */
#define __POSIX_VISIBLE 0
#define __XSI_VISIBLE 0
#define __BSD_VISIBLE 0
#define __ISO_C_VISIBLE 2011
#define __EXT1_VISIBLE 0
#else /* Default environment: show everything. */
#define __POSIX_VISIBLE 200809
#define __XSI_VISIBLE 700
#define __BSD_VISIBLE 1
#define __ISO_C_VISIBLE 2011
#define __EXT1_VISIBLE 1
#endif
#endif

/*
 * Function or variable should not be sanitized, e.g., by AddressSanitizer.
 * GCC has the nosanitize attribute, but as a function attribute only, and
 * warns on use as a variable attribute.
 */
#if __has_attribute(no_sanitize) && defined(__clang__)
#define __nosanitizeaddress __attribute__((no_sanitize("address")))
#define __nosanitizememory __attribute__((no_sanitize("memory")))
#define __nosanitizethread __attribute__((no_sanitize("thread")))
#else
#define __nosanitizeaddress
#define __nosanitizememory
#define __nosanitizethread
#endif

/*
 * Make it possible to opt out of stack smashing protection.
 */
#if __has_attribute(no_stack_protector)
#define __nostackprotector __attribute__((no_stack_protector))
#else
#define __nostackprotector __attribute__((__optimize__("-fno-stack-protector")))
#endif

/* Guard variables and structure members by lock. */
#define __guarded_by(x) __lock_annotate(guarded_by(x))
#define __pt_guarded_by(x) __lock_annotate(pt_guarded_by(x))

/* Alignment builtins for better type checking and improved code generation. */
/* Provide fallback versions for other compilers (GCC/Clang < 10): */
#if !__has_builtin(__builtin_is_aligned)
#define __builtin_is_aligned(x, align) (((__uintptr_t)x & ((align)-1)) == 0)
#endif
#if !__has_builtin(__builtin_align_up)
#define __builtin_align_up(x, align) \
  ((__typeof__(x))(((__uintptr_t)(x) + ((align)-1)) & (~((align)-1))))
#endif
#if !__has_builtin(__builtin_align_down)
#define __builtin_align_down(x, align) ((__typeof__(x))((x) & (~((align)-1))))
#endif

#define __align_up(x, y) __builtin_align_up(x, y)
#define __align_down(x, y) __builtin_align_down(x, y)
#define __is_aligned(x, y) __builtin_is_aligned(x, y)

#endif /* !_SYS_CDEFS_H */
