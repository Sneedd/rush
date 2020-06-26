/*
 * log.h - Declaration of the Log class
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2012 - Steffen Ott
 *
 */



#ifndef _RUSH_LOG_H_
#define _RUSH_LOG_H_

#include <rush/config.h>
#include <rush/string.h>
#include <rush/logtarget.h>
#include <stdarg.h>


namespace rush {


/**
 * \brief The Log class conatins static methods to log messages into a log target.
 * The default log target is the standard output (stdout), but can be changed with
 * SetTarget().
 **/
class Log
{
    private:
        Log() {}
        ~Log() {}

    public:
        static void SetTarget(LogTargetType targetType);
        static void SetTarget(LogTarget* target);
        static void SetFilename(const String& filename);
        static void SetVerbose(LogVerbose verbose);

        static void WriteV(LogVerbose verbose, const String& format, va_list args);
        static void Debug(const String& format, ...);
        static void Message(const String& format, ...);
        static void Warning(const String& format, ...);
        static void Error(const String& format, ...);

};

} // namespace rush


#endif // _RUSH_LOG_H_


