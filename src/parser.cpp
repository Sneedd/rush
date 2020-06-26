/*
 * parser.cpp - Implementation of Parser class
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2011-2012 - Steffen Ott
 *
 */



#include <rush/parser.h>
#include <stdlib.h>
#include <math.h>

namespace rush {


//-----------------------------------------------------------------------------
int Parser::ParseNumber(char value)
/**
 * \brief Parses a number in char and returns their real value. If the character
 * isn't a number -1 will be returned.
 * \return Returns 0 to 9 or -1.
 **/
{
    if (value >= 48 && value <= 57)
    {
        return (value - 48);
    }
    return (-1);
}



//-----------------------------------------------------------------------------
double Parser::ParseDouble(const String& text, char decimalSeparator)
/**
 * \brief Parses a double value out of a string and returns it.
 * This method will return zero, if an error occurs.
 **/
{
    double result = 0.0d;
    if (!Parser::TryParseDouble(text, &result, decimalSeparator)) {
        result = 0.0d;
    }
    return (result);
}



//-----------------------------------------------------------------------------
int Parser::ParseInt(const String& text)
/**
 * \brief Parses a integer value out of a string and returns it.
 * This method will return zero, if an error occurs.
 **/
{
    int result = 0;
    if (!Parser::TryParseInt(text, &result)) {
        result = 0;
    }
    return (result);
}




//-----------------------------------------------------------------------------
bool Parser::TryParseDouble(const String& text, double* value, char decimalSeparator)
{
    if (value == NULL) {
        return (false);
    }

    #ifdef _RUSH_UNICODE_
    *value = _wtof(text.c_str());
    #else
    *value = atof(text.c_str());
    #endif
    return (true);

}


//-----------------------------------------------------------------------------
bool Parser::TryParseInt(const String& text, int* value)
{
    if (value == NULL) {
        return (false);
    }

    // TODO: Optimieren mit State Machine
    bool parseError = false;

    int index = 0;
    if (text.Find('-') == 0) index = 1;

    int result = 0, count = 1;
    for (int i = text.Length() - 1; i >= index; --i)
    {
        int number = Parser::ParseNumber(text[i]);
        if (number < 0) parseError |= true;
        result += count * number;
        count *= 10;
    }

    if (index == 1) result *= -1;
    *value = result;
    return (!parseError);
}




} // namespace rush



