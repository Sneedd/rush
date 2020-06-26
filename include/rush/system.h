/*
 * system.h - Declaration of the System class
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2011-2012 - Steffen Ott
 *
 */


#ifndef _RUSH_SYSTEM_H_
#define _RUSH_SYSTEM_H_


#include <rush/config.h>
#include <rush/string.h>

namespace rush {

/**
 * \brief The System class contains various system specific functions.
 **/
class System
{
    private:
        System() {}
        ~System() {}

    public:
        static String GetExecutablePath();
        static size_t GetTicks();
        static void Delay(size_t milliSeconds);


};

} // namespace rush

#endif // _RUSH_SYSTEM_H_


