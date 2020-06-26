/*
 * convert.h - Declaration and implementation of the Convert class
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2012 - Steffen Ott
 *
 */


#ifndef _RUSH_CONVERT_H_
#define _RUSH_CONVERT_H_

#include <rush/config.h>
#include <rush/string.h>


namespace rush {

/**
 * \brief The Convert class is a static class with various convert functions.
 **/
class Convert
{
    private:
        Convert() {}
        ~Convert() {}

    public:
        static unsigned int HexToInt(const rush::String& value);

};


} // namespace rush

#endif // _RUSH_CONVERT_H_


