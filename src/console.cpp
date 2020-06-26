/*
 * console.cpp - Implementation of the Console class
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2011-2012 - Steffen Ott
 *
 */


#include <rush/console.h>
#include <rush/system.h>
#include <rush/log.h>

#include <stdarg.h>
#include <stdio.h>

#if defined _RUSH_WINDOWS_
    #include <windows.h>
#elif defined _RUSH_LINUX_
    #warning Not implemented
#else
    #warning No operation system spezified.
#endif

#ifdef _RUSH_UNICODE_
    //#include <wchar.h>
#endif


namespace rush {


#ifdef _RUSH_WINDOWS_
static HANDLE consoleOutputHandle = NULL;
static HANDLE consoleInputHandle = NULL;
#endif


//-----------------------------------------------------------------------------
void Console::Initialize()
/**
 * \brief Initializes the class and needed static variables. Second call
 * does nothing.
 **/
{
    #ifdef _RUSH_WINDOWS_
    if (consoleOutputHandle == NULL)
    {
        consoleOutputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    }
    if (consoleInputHandle == NULL)
    {
        consoleInputHandle = GetStdHandle(STD_INPUT_HANDLE);
    }
    #endif
}


//-----------------------------------------------------------------------------
void Console::SetTextColor(ConsoleColors color)
/**
 * \brief Sets the text color of the console output.
 * \param color Text color.
 **/
{
    Console::Initialize();

    // Check for valid colors
    int textColor = (int)color;
    int backColor = (int)Console::GetBackgroundColor();
    if (textColor < 0 || textColor > 15 || backColor < 0 || backColor > 15) {
        return;
    }

    // Set the color
    #ifdef _RUSH_WINDOWS_
    SetConsoleTextAttribute(consoleOutputHandle, textColor + (backColor*16));
    #endif
}


//-----------------------------------------------------------------------------
ConsoleColors Console::GetTextColor()
/**
 * \brief Gets the text color of the console output.
 * \return text color.
 **/
{
    Console::Initialize();

    // Get color
    int color = 7;
    #ifdef _RUSH_WINDOWS_
    CONSOLE_SCREEN_BUFFER_INFO info;
    if (!GetConsoleScreenBufferInfo(consoleOutputHandle, &info)) {
        color = info.wAttributes & (FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY);
    }
    #endif

    return ((ConsoleColors)color);
}


//-----------------------------------------------------------------------------
void Console::SetBackgroundColor(ConsoleColors color)
/**
 * \brief Sets the background color of the console output.
 * \param color Background color.
 **/
{
    Console::Initialize();

    // Check for valid colors
    int textColor = (int)Console::GetTextColor();
    int backColor = (int)color;
    if (textColor < 0 || textColor > 15 || backColor < 0 || backColor > 15) {
        return;
    }

    // Set the color
    #ifdef _RUSH_WINDOWS_
    SetConsoleTextAttribute(consoleOutputHandle, textColor + (backColor*16));
    #endif
}


//-----------------------------------------------------------------------------
ConsoleColors Console::GetBackgroundColor()
/**
 * \brief Gets the background color of the console output.
 * \return Background color.
 **/
{
    Console::Initialize();

    int color = 0;
    #ifdef _RUSH_WINDOWS_
    CONSOLE_SCREEN_BUFFER_INFO info;
    if (!GetConsoleScreenBufferInfo(consoleOutputHandle, &info)) {
        color = info.wAttributes & (BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_BLUE|BACKGROUND_INTENSITY);
    }
    #endif

    return ((ConsoleColors)color);
}


//-----------------------------------------------------------------------------
void Console::Flush()
/**
 * \brief Flush the standard output (stdout).
 **/
{
    fflush(stdout);
}


//-----------------------------------------------------------------------------
void Console::Pause(const String& message)
/**
 * \brief Writes the message to the console and wait for a keypress.
 * \param message Message.
 **/
{
    Console::WriteLine(message);
    while (!Console::IsKeyPressed())
    {
        System::Delay(100);
    }
}


//-----------------------------------------------------------------------------
bool Console::IsKeyPressed()
/**
 * \brief Checks if a key in the console window was pressed.
 * \return True, if a key was pressed; otherwise false.
 **/
{
    Console::Initialize();

    #if defined _RUSH_WINDOWS_
    INPUT_RECORD record;
    DWORD events[1];
    if (!ReadConsoleInputW(consoleInputHandle, &record, 1, events))
    {
        return (false);
    }
    if (!PeekConsoleInputW(consoleInputHandle, &record, 1, events))
    {
        return (false);
    }
    if (events == 0)
    {
       return (false);
    }
    if (record.EventType == KEY_EVENT)
    {
        if (record.Event.KeyEvent.bKeyDown)
        {
            return (true);
        }
    }
    #else
        #warning Not implemented.
    #endif
    return (false);
}


//-----------------------------------------------------------------------------
void Console::Write(const String& format, ...)
/**
 * \brief Writes the given formated text to the console.
 * \param format Format (see printf)
 **/
{
    va_list args;
    va_start(args,format);
    #ifdef _RUSH_UNICODE_
    vwprintf(format.c_str(),args);
    #else
    vprintf(format.c_str(),args);
    #endif
}


//-----------------------------------------------------------------------------
void Console::WriteLine(const String& format, ...)
/**
 * \brief Writes the given formated text to the console and adds a newline.
 * \param format Format (see printf)
 **/
{
    va_list args;
    va_start(args,format);
    #ifdef _RUSH_UNICODE_
    vwprintf(format.c_str(),args);
    wprintf(L"\n");
    #else
    vprintf(format.c_str(),args);
    printf("\n");
    #endif
}


//-----------------------------------------------------------------------------
void Console::WriteLine()
/**
 * \brief Writes a new line to the console.
 **/
{
    #ifdef _RUSH_UNICODE_
    wprintf(L"\n");
    #else
    printf("\n");
    #endif
}


} // namespace rush

