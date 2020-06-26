/*
 * memory.h - Declarations of the Memory class and other functions
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2012 - Steffen Ott
 *
 */


#ifndef _RUSH_MEMORY_H_
#define _RUSH_MEMORY_H_


#include <rush/config.h>

#include <rush/string.h>


#ifdef _RUSH_CHECKMEMORYLEAKS_
#include <new>         // für size_t und std::bad_alloc
void* operator new(size_t size) throw (std::bad_alloc);
void* operator new [](size_t size) throw (std::bad_alloc);
void operator delete (void* pointer) throw();
void operator delete [](void* pointer) throw();
#endif // _RUSH_CHECKMEMORYLEAKS_



namespace rush {

class String;


class Memory
{
    private:
        Memory() {}
        ~Memory() {}

    public:
        static void Initialize();
        static void BeginLeakDetection();
        static void EndLeakDetection();
        static String GetMemoryLeaksInfo();
};

} // namespace rush


#endif // _RUSH_MEMORY_H_
