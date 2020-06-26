/*
 * parser.h - Declaration of the Parser class
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2011-2012 - Steffen Ott
 *
 */



#ifndef _RUSH_PARSER_H_
#define _RUSH_PARSER_H_


#include <rush/config.h>
#include <rush/string.h>
#include <rush/array.h>


namespace rush {

/**
 * \brief The Parser class contains various functions to parse text into
 * other datatypes.
 **/
class Parser
{
    private:
        Parser() {}
        ~Parser() {}

    public:
        static int ParseNumber(char value);
        static double ParseDouble(const String& text, char decimalSeparator = '.');
        static int ParseInt(const String& text);

        static bool TryParseDouble(const String& text, double* value, char decimalSeparator = '.');
        static bool TryParseInt(const String& text, int* value);

};


} // namespace rush

#endif // _RUSH_PARSER_H_


