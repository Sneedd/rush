/*
 * convert.cpp - Implementation of the Convert class
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2011-2012 - Steffen Ott
 *
 */


#include <rush/convert.h>


namespace rush {


//-----------------------------------------------------------------------------
unsigned int Convert::HexToInt(const rush::String& value)
/**
 * \brief Converts a hexadecimal string to an unsigned integer value.
 * Values must be either '0x00112233' or '00112233'.
 * \param value Hexadecimal value.
 * \return Value.
 **/
{
    // Init vars
    size_t startIndex = 0;
    unsigned int result = 0;

    // Jump over '0x' or '0X'
    if (value.StartsWith(_T("0x")) || value.StartsWith(_T("0X"))) {
        startIndex += 2;
    }

    // Loop the hex string
    for (size_t i=startIndex; i<value.Length(); ++i)
    {
        result *= 16; // Note: result start value is zero
        unsigned int single = (int)value[i] - 48;
        if (single > 10) single -= 7;   // Number to alpha
        if (single > 16) single -= 32;  // Upper to lower
        result += single;
    }
    return (result);
}








} // namespace rush


