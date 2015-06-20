/*
    Copyright (c) 2014 Robert Lodico

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.
*/

#ifndef H_PORTABLE
#define H_PORTABLE

/* Drown Microsoft's stupid compiler warnings encouraging
the usage of platform-locked fopen_s() instead of fopen(). */
#define _CRT_SECURE_NO_WARNINGS

/* BEGIN: Portable Types */
#if defined(__cplusplus)
namespace portable {
#endif
    /* 64-bit */
    #ifdef _MSC_VER
    #define INT64 __int64
    #else
    #define INT64 long long
    #endif

    /* Normal */
    typedef          char  int8;
    typedef          short int16;
    typedef          int   int32;
    typedef          INT64 int64;

    /* Unsigned */
    typedef unsigned char  uint8;
    typedef unsigned short uint16;
    typedef unsigned int   uint32;
    typedef unsigned INT64 uint64;

    /* Signed */
    typedef signed   char  sint8;
    typedef signed   short sint16;
    typedef signed   int   sint32;
    typedef signed   INT64 sint64;

    /* Aliases */
    typedef unsigned char  byte;
    typedef unsigned char  uchar;
    typedef unsigned short ushort;
    typedef unsigned int   uint;
    typedef unsigned INT64 ulong;
#if defined(__cplusplus)
}
#endif
/* END: Portable Types */

/* BEGIN: Platform Detection */
/* Operating System Defines */
#define OS_UNKNOWN -1 /* If we legitimately have no clue. */
#define OS_U_UNIX  -2 /* If we know it's Unix, but we don't know which. */
#define OS_U_APPLE -3 /* If we know it's Apple-crap, but don't know which. */
#define OS_LINUX    0
#define OS_ANDROID  1
#define OS_WINDOWS  2
#define OS_OSX      3
#define OS_IOS      4
#define OS_BSD      5

/* Define our detected platform as our
default value, unknown. */

/* Unix Children */
#if defined(__unix__)
    #define PLATFORM_UNIX

    /* Linux */
    #if defined(__linux__)
        #define PLATFORM_LINUX
        #define DETECTED_PLATFORM OS_LINUX
    /* Android */
    #elif defined(__ANDROID__)
        #define PLATFORM_ANDROID
        #define DETECTED_PLATFORM OS_ANDROID
    /* BSD */
    #elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)
        #define PLATFORM_BSD
        #define DETECTED_PLATFORM OS_BSD
    /* Unknown/unsupported Unix */
    #else
        #define DETECTED_PLATFORM OS_U_UNIX
    #endif

/* Windows */
#elif defined(_WIN32)
    #define PLATFORM_WINDOWS
    #define DETECTED_PLATFORM OS_WINDOWS

    #ifndef NOMINMAX
        #define NOMINMAX
    #endif
/* Apple */
#elif defined(__APPLE__) && defined(__MACH__)
    #define PLATFORM_APPLE

    #include "TargetConditionals.h"

    /* iOS */
    #if TARGET_OS_IPHONE || TARGET_OS_IPHONE_SIMULATOR
        #define PLATFORM_IOS
        #define DETECTED_PLATFORM OS_IOS
    /* OSX */
    #elif TARGET_OS_MAC
        #define PLATFORM_OSX
        #define DETECTED_PLATFORM OS_OSX
    /* Unknown/unsupported Apple-crap */
    #else
        #define DETECTED_PLATFORM OS_U_APPLE
    #endif
/* Unknown */
#else
    #define DETECTED_PLATFORM OS_UNKNOWN
#endif
/* END: Platform Detection */

/* BEGIN: Export/Import Macros */
#if !defined(PORTABLE_STATIC)
    /* VC needs specific keywords for exporting/importing symbols */
    #if defined(PLATFORM_WINDOWS)
        #define PORTABLE_EXPORT __declspec(dllexport)
        #define PORTABLE_IMPORT __declspec(dllimport)

        #if defined(_MSC_VER)
            #pragma warning(disable : 4251)
        #endif
    /* GCC >= 4 has special keywords for exporting/importing symbols */
    #elif __GNUC__ >= 4
        #define PORTABLE_EXPORT __attribute__ ((__visibility__ ("default")))
        #define PORTABLE_IMPORT __attribute__ ((__visibility__ ("default")))
    /* Assume GCC < 4, everything is exported by default */
    #else
        #define PORTABLE_EXPORT
        #define PORTABLE_IMPORT
    #endif
/* Static libraries do not need exports/imports */
#else
    #define PORTABLE_EXPORT
    #define PORTABLE_IMPORT
#endif
/* END: Export/Import Macros */

#endif//H_PORTABLE
