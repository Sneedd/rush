/*
 * console.h - Declaration of the Console class
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2012 - Steffen Ott
 *
 */



#ifndef _RUSH_CONSOLE_H_
#define _RUSH_CONSOLE_H_


#include <rush/config.h>
#include <rush/string.h>



namespace rush {

/**
 * \brief The ConsoleColors enum spezifies the console colors.
 **/
enum class ConsoleColors : unsigned char
{
    Black        =  0,
    DarkBlue     =  1,
    DarkGreen    =  2,
    DarkCyan     =  3,
    DarkRed      =  4,
    DarkMagenta  =  5,
    DarkYellow   =  6,
    Gray         =  7,
    DarkGray     =  8,
    Blue         =  9,
    Green        = 10,
    Cyan         = 11,
    Red          = 12,
    Magenta      = 13,
    Yellow       = 14,
    White        = 15
};


/**
 * \brief The Console class implements functions to write to the console.
 **/
class Console
{
    private:
        Console() {}
        ~Console() {}
        static void Initialize();

    public:
        static void SetTextColor(ConsoleColors color);
        static ConsoleColors GetTextColor();
        static void SetBackgroundColor(ConsoleColors color);
        static ConsoleColors GetBackgroundColor();

        static void Flush();
        static void Pause(const String& message = _T("Press any key to continue ..."));
        static bool IsKeyPressed();

        static void Write(const String& text, ...);
        static void WriteLine(const String& text, ...);
        static void WriteLine();
};


} // namespace rush


#endif // _RUSH_CONSOLE_H_


