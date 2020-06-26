/*
 * backtrace.h - Declaration of the BackTrace class
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2011-2012 - Steffen Ott
 *
 */


#ifndef _RUSH_BACKTRACE_H_
#define _RUSH_BACKTRACE_H_

#include <rush/config.h>
#include <rush/string.h>



namespace rush {


/**
 * \brief The BackTrace class
 **/
class BackTrace
{
    private:
        BackTrace() {}
        ~BackTrace() {}

    public:
        static String CreateBackTrace();


};


} // namespace rush

#endif // _RUSH_BACKTRACE_H_
