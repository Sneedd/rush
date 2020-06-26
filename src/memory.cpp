/*
 * memory.cpp - Implementation of Memory class
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2011-2012 - Steffen Ott
 *
 */


#include <rush/memory.h>
#include <rush/console.h>
#include <stdio.h>
#include <stdlib.h>


#ifdef _RUSH_CHECKMEMORYLEAKS_
static size_t allocations = 0;
static size_t maxAllocations = 0;
static size_t overallAllocations = 0;
static size_t pointerCount = 8*1024;
static void** pointerArray = NULL;
static bool detectLeaks = false;

//-----------------------------------------------------------------------------
void* operator new(size_t size) throw (std::bad_alloc)
/**
 * \brief
 **/
{
    if (detectLeaks)
    {
        rush::Memory::Initialize();
        void* pointer = malloc(size);
        for (size_t i=0; i<pointerCount; ++i)
        {
            if (pointerArray[i] == NULL)
            {
                pointerArray[i] = pointer;
                break;
            }
        }
        overallAllocations++;
        allocations++;
        if (allocations > maxAllocations) maxAllocations = allocations;
        return (pointer);
    }
    return (malloc(size));
}


//-----------------------------------------------------------------------------
void operator delete (void* pointer) throw()
/**
 * \brief
 **/
{
    if (detectLeaks)
    {
        rush::Memory::Initialize();
        if (pointer != NULL)
        {
            for (size_t i=0; i<pointerCount; ++i)
            {
                if (pointerArray[i] == pointer)
                {
                    pointerArray[i] = NULL;
                    break;
                }
            }
            free(pointer);
        }
        if (allocations != 0) allocations--;
    }
    else
    {
        free(pointer);
    }
}


//-----------------------------------------------------------------------------
void* operator new [](size_t size) throw (std::bad_alloc)
/**
 * \brief
 **/
{
    if (detectLeaks)
    {
        rush::Memory::Initialize();
        void* pointer = malloc(size);
        for (size_t i=0; i<pointerCount; ++i)
        {
            if (pointerArray[i] == NULL)
            {
                pointerArray[i] = pointer;
                break;
            }
        }
        overallAllocations++;
        allocations++;
        if (allocations > maxAllocations) maxAllocations = allocations;
        return (pointer);
    }
    return (malloc(size));
}



//-----------------------------------------------------------------------------
void operator delete [](void* pointer) throw()
/**
 * \brief
 **/
{
    if (detectLeaks)
    {
        rush::Memory::Initialize();
        if (pointer != NULL)
        {
            for (size_t i=0; i<pointerCount; ++i)
            {
                if (pointerArray[i] == pointer)
                {
                    pointerArray[i] = NULL;
                    break;
                }
            }
            free(pointer);
        }
        if (allocations != 0) allocations--;
    }
    else
    {
        free(pointer);
    }
}
#endif // _RUSH_CHECKMEMORYLEAKS_



namespace rush {


//-----------------------------------------------------------------------------
void Memory::Initialize()
{
    #ifdef _RUSH_CHECKMEMORYLEAKS_
    if (pointerArray == NULL)
    {
        pointerArray = (void**)malloc(pointerCount*sizeof(void*));
        memset(pointerArray, 0, pointerCount*sizeof(void*));
    }
    #endif // _RUSH_CHECKMEMORYLEAKS_
}


//-----------------------------------------------------------------------------
void Memory::BeginLeakDetection()
{
    #ifdef _RUSH_CHECKMEMORYLEAKS_
    Initialize();
    memset(pointerArray, 0, pointerCount*sizeof(void*));
    allocations = 0;
    maxAllocations = 0;
    overallAllocations = 0;
    detectLeaks = true;
    #endif // _RUSH_CHECKMEMORYLEAKS_
}

//-----------------------------------------------------------------------------
void Memory::EndLeakDetection()
{
    #ifdef _RUSH_CHECKMEMORYLEAKS_
    detectLeaks = false;
    #endif // _RUSH_CHECKMEMORYLEAKS_
}


//-----------------------------------------------------------------------------
String Memory::GetMemoryLeaksInfo()
/**
 * \brief
 **/
{
    #ifdef _RUSH_CHECKMEMORYLEAKS_
    Memory::Initialize();
    size_t unfreed = 0;
    for (size_t i=0; i<pointerCount; ++i)
    {
        if (pointerArray[i] != NULL)
        {
            unfreed++;
        }
    }
    return (String::Format(_T("Memory Allocations (Overall = %u | Unfreed = %u | Max = %u)"),
        overallAllocations, unfreed, maxAllocations));
    #else
    return (_T(""));
    #endif // _RUSH_CHECKMEMORYLEAKS_
}


} // namespace rush


