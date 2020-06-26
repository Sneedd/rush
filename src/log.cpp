/*
 * log.cpp - Implementation of the Log class
 *
 * This file is part of the rush utility library.
 * Licensed under the terms of Lesser GPL v3.0 (see license.txt).
 * Copyright 2011-2012 - Steffen Ott
 *
 */


#include <rush/log.h>

#ifdef _RUSH_UNICODE_
    #undef __STRICT_ANSI__
    #undef _WSTDIO_DEFINED
    //#include <libintl.h>
#endif
#include <stdio.h>


/**
 * \brief Defines the buffer size to format a log message.
 **/
#define RUSH_LOG_FORMAT_BUFFER_SIZE 1024


namespace rush {

static LogTarget* staticLogTarget = LogTarget::CreateTarget(LogTargetType::StdOut);
static LogVerbose staticVerbose = LogVerbose::Debug;


//-----------------------------------------------------------------------------
void Log::SetTarget(LogTargetType targetType)
/**
 * \brief Sets the log target where the log messages will be send from now on.
 * \param targetType Log target.
 **/
{
    Log::SetTarget(LogTarget::CreateTarget(targetType));
}


//-----------------------------------------------------------------------------
void Log::SetTarget(LogTarget* target)
/**
 * \brief Sets the log target where the log messages will be send from now on.
 * If NULL is provided the logs will be
 * \param target Log target or NULL.
 **/
{
    if (staticLogTarget != target)
    {
        // Set target directly
        LogTarget* oldTarget = staticLogTarget;
        staticLogTarget = target;

        // Free old target
        if (oldTarget != NULL)
        {
            delete oldTarget;
            oldTarget = NULL;
        }
    }
}


//-----------------------------------------------------------------------------
void Log::SetFilename(const String& filename)
/**
 * \brief Sets the filename of the log file. Only applies if log output is set to file
 * (see SetOutput).
 **/
{
    LogTargetFilename* target = dynamic_cast<LogTargetFilename*>(staticLogTarget);
    if (target != NULL)
    {
        target->SetFilename(filename);
    }
}


//-----------------------------------------------------------------------------
void Log::SetVerbose(LogVerbose verbose)
/**
 * \brief Sets the verbose level of the logs.
 **/
{
    staticVerbose = verbose;
}


//-----------------------------------------------------------------------------
void Log::WriteV(LogVerbose verbose, const String& format, va_list args)
/**
 * \brief Writes the message into a log target.
 * \param verbose Verbose level.
 * \param format Message (see printf).
 * \param args Message arguments.
 **/
{
    if (staticVerbose <= verbose)
    {
        int maxsize = RUSH_LOG_FORMAT_BUFFER_SIZE;
        Char buffer[maxsize];
        #ifdef _RUSH_UNICODE_
        vsnwprintf(buffer,maxsize,format.c_str(),args);
        #else
        vsnprintf(buffer,maxsize,format.c_str(),args);
        #endif
        if (staticLogTarget != NULL)
        {
            staticLogTarget->Write(verbose, buffer);
        }
    }
}



//-----------------------------------------------------------------------------
void Log::Debug(const String& format, ...)
/**
 * \brief Logs the given message as a debug message into the log target.
 * \param format Format (see printf).
 **/
{
    va_list args;
    va_start(args,format);
    Log::WriteV(LogVerbose::Debug, format, args);
}




//-----------------------------------------------------------------------------
void Log::Message(const String& format, ...)
/**
 * \brief Logs the given message as a normal message into the log target.
 * \param format Format (see printf).
 **/
{
    va_list args;
    va_start(args,format);
    Log::WriteV(LogVerbose::Message, format, args);
}



//-----------------------------------------------------------------------------
void Log::Warning(const String& format, ...)
/**
 * \brief Logs the given message as a wrning message into the log target.
 * \param format Format (see printf).
 **/
{
    va_list args;
    va_start(args,format);
    Log::WriteV(LogVerbose::Warning, format, args);
}



//-----------------------------------------------------------------------------
void Log::Error(const String& format, ...)
/**
 * \brief Logs the given message as a error message into the log target.
 * \param format Format (see printf).
 **/
{
    va_list args;
    va_start(args,format);
    Log::WriteV(LogVerbose::Error, format, args);
}


} // namespace rush


