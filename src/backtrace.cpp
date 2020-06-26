/*
 * backtrace.cpp - Imüplementation of the BackTrace class
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2011-2012 - Steffen Ott
 *
 */


#include <rush/backtrace.h>
//#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>

namespace rush {

//-----------------------------------------------------------------------------
String BackTrace::CreateBackTrace()
{
//    void* array[10];
//    size_t size;
//    char** strings;
//    size_t i;
//
//    size = backtrace(array, 10);
//    strings = backtrace_symbols (array, size);
//
//    printf("Obtained %zd stack frames.\n", size);
//
//    for (i = 0; i < size; i++)
//    {
//        printf ("%s\n", strings[i]);
//    }
//
//    free (strings);
    return (_T(""));
}



} // namespace rush


