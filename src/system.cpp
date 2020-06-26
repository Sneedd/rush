/*
 * system.cpp - Implementation of System class
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2011-2012 - Steffen Ott
 *
 */



#include <rush/system.h>


#ifdef _RUSH_WINDOWS_
    #include <windows.h>
#else
    #warning Not implemented.
#endif



namespace rush {


//-----------------------------------------------------------------------------
String System::GetExecutablePath()
/**
 * \brief Returns the full path to the executable.
 * \return Full path to the executable.
 **/
{
    String result = _T("");
    #ifdef _RUSH_WINDOWS_
    #ifdef _RUSH_UNICODE_
        LPWSTR buffer = new WCHAR[512];
        GetModuleFileNameW(NULL, buffer, 512);
        result = buffer;
        delete [] buffer;
    #else
        LPTSTR buffer = new TCHAR[512];
        GetModuleFileName(NULL, buffer, 512);
        result = buffer;
        delete [] buffer;
    #endif
    #endif
    return (result);

    // NOTE: Other OS have other functions
    //    Mac OS X: _NSGetExecutablePath() (man 3 dyld)
    //    Linux: readlink /proc/self/exe
    //    Solaris: getexecname()
    //    FreeBSD: sysctl CTL_KERN KERN_PROC KERN_PROC_PATHNAME -1
    //    BSD with procfs: readlink /proc/curproc/file
    //    Windows: GetModuleFileName() with hModule = NULL
}


//-----------------------------------------------------------------------------
size_t System::GetTicks()
/**
 * \brief Returns the actual ticks in milliseconds of the system.
 * \return Ticks.
 **/
{
    #ifdef _RUSH_WINDOWS_
    return (GetTickCount());
    #endif
    return (0);
}


//-----------------------------------------------------------------------------
void System::Delay(size_t milliSeconds)
/**
 * \brief Delays the execution of this thread for the given amount
 * of milliseconds.
 * \param milliSeconds The delay time in milliseconds.
 **/
{
    #ifdef _RUSH_WINDOWS_
    Sleep(milliSeconds);
    #endif
}


} // namespace rush



