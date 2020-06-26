/*
 * buildin_expect.h
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2005-2012 - Steffen Ott
 *
 */


#ifndef _RUSH_BUILDIN_EXPECT_H_
#define _RUSH_BUILDIN_EXPECT_H_


#include <rush/config.h>


#ifndef likely
    #ifdef __GNUC__ // Check if GNUC is used
        #define likely(x)   __builtin_expect((x), 1)
        #define unlikely(x) __builtin_expect((x), 0)
    #else
        #warning No __buildin_expect() macro defined by the compiler
        #define likely(x)   (x)
        #define unlikely(x) (x)
    #endif
#endif



/*
 *
 * Defines two macros about the if branch optimisation. For example: If a argument
 * normally true then you should use likely(). If not you should use unlikely() this
 * speeds up a little bit because many error detecting if-statements should mainly be
 * unlikely(), because they only be called when an error occured. And this should
 * not be called.
 *
 * I have taken the idea for this from the linux kernel (klibc) found on
 * www.kernel.org
 *
 */

/*
 * Here is the documentation for __buildin_expect:
 *
 * long __builtin_expect (long exp, long c)
 *
 * You may use __builtin_expect to provide the compiler with branch prediction
 * information. In general, you should prefer to use actual profile feedback
 * for this (`-fprofile-arcs'), as programmers are notoriously bad at predicting
 * how their programs actually perform. However, there are applications in which
 * this data is hard to collect.
 *
 * The return value is the value of exp, which should be an integral expression.
 * The value of c must be a compile-time constant. The semantics of the built-in
 * are that it is expected that exp == c. For example:
 *
 *    if (__builtin_expect (x, 0))
 *        foo ();
 *
 * would indicate that we do not expect to call foo, since we expect x to be zero.
 * Since you are limited to integral expressions for exp, you should use
 * constructions such as
 *
 *    if (__builtin_expect (ptr != NULL, 1))
 *        error ();
 *
 * when testing pointer or floating-point values.
 *
 */


#endif // _RUSH_BUILDIN_EXPECT_H_


