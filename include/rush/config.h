/*
 * config.h - Contains various configuration information for rush
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2012 - Steffen Ott
 *
 */


#ifndef _RUSH_CONFIG_H_
#define _RUSH_CONFIG_H_


//----------------------------------------------------- Common configuration
//#define _STD_    // rush should support std classes
//#define _WX_     // rush should support wxWidgets classes


//------------------------------------------------- OS configuration
//#define _RUSH_LINUX_
//#define _RUSH_WINDOWS_




// Tells rush to compile in debug mode
#ifdef __DEBUG__
    //#define __ARRAY_DEBUG__
    //#define _RUSH_CHECKMEMORYLEAKS_
#endif

// Tells rush to support std classes
#ifdef _STD_
    #define _RUSH_SUPPORTS_STD_
#endif

// Tells rush to support wxWidgets classes
#ifdef __WXMSW__
    #ifndef _RUSH_SUPPORTS_WXWIDGETS_
    #define _RUSH_SUPPORTS_WXWIDGETS_
    #endif
#endif


#include <rush/memory.h>


#endif // _RUSH_CONFIG_H_


