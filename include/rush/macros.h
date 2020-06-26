/*
 * macros.h - Contains various macros for the rush library
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2012 - Steffen Ott
 *
 */


#ifndef _RUSH_MACROS_H_
#define _RUSH_MACROS_H_


#include <rush/config.h>
#include <rush/log.h>



#ifndef RUSH_NOT_IMPLEMENTED_YET
    /**
     * \brief The NOT_IMPLEMENTED_YET() macro just writes an information
     * to the log file, that something is not implemented.
     **/
    #ifdef _RUSH_UNICODE_
        #define RUSH_NOT_IMPLEMENTED_YET() \
            rush::Log::Error(_T("Not implemented yet. File: %s Line: %i\n"), __FILE__, __LINE__);
    #else
        #define RUSH_NOT_IMPLEMENTED_YET() \
            rush::Log::Error("Not implemented yet. File: %s Line: %i\n", __FILE__, __LINE__);
    #endif
#endif


/**
 * \brief Declares a private copy constructor in a class.
 * After using this macro make sure that you switch to public
 * or whatever.
 **/
#define DECLARE_NO_COPY_CONSTRUCTOR(classname) \
    private: \
    classname(classname& source) {}

/**
 * \brief Declares a private assignment operator in a class.
 * After using this macro make sure that you switch to public
 * or whatever.
 **/
#define DECLARE_NO_ASSIGNMENT_OPERATOR(classname) \
    private: \
    classname& operator=(const classname& source) {return (*this);}


#endif // _RUSH_MACROS_H_



