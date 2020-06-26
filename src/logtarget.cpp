/*
 * logtarget.cpp - Implementation of the LogTarget class
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2012 - Steffen Ott
 *
 */


#include <rush/logtarget.h>
#include <rush/system.h>
#include <rush/path.h>

#ifdef _RUSH_UNICODE_
    #undef __STRICT_ANSI__
    #undef _WSTDIO_DEFINED
    //#include <libintl.h>
#endif

#include <stdio.h>
#include <stdlib.h>


namespace rush {

/**
 * \brief The LogTargetStream class is the implementation of a log target
 * for already opend files.
 **/
class LogTargetStream : public LogTarget
{
    public:
        LogTargetStream(FILE* stream) : m_stream(stream) {}
        ~LogTargetStream() {}

        void Write(LogVerbose verbose, const String& message);

    private:
        FILE* m_stream;
};


#ifdef _RUSH_SUPPORT_WXWIDGETS_
/**
 * \brief The LogTargetWidgets class is the implementation of a log target
 * for wxWidgets. This class creates a redirection to wxLogXXX() functions.
 **/
class LogTargetWidgets : public LogTarget
{
    public:
        LogTargetWidgets(FILE* stream) : m_stream(stream) {}
        ~LogTargetWidgets() {}

        void Write(LogVerbose verbose, const String& message);

    private:
        FILE* m_stream;
};
#endif



//-----------------------------------------------------------------------------
void LogTargetStream::Write(LogVerbose verbose, const String& message)
/**
 * \brief Writes the message into the log target. The verbose level should not
 * be used to append informations to the message
 * \param verbose Verbose level.
 * \param message Log message.
 **/
{
    #ifdef _RUSH_UNICODE_
    fwprintf(m_stream, L"%s\n", message.c_str());
    #else
    fprintf(m_stream, "%s\n", message.c_str());
    #endif
    fflush(m_stream);
}


#ifdef _RUSH_SUPPORT_WXWIDGETS_
//-----------------------------------------------------------------------------
void LogTargetWidgets::Write(LogVerbose verbose, const String& message)
/**
 * \brief Writes the message into the log target. The verbose level should not
 * be used to append informations to the message
 * \param verbose Verbose level.
 * \param message Log message.
 **/
{
    if (verbose == LogVerbose::Debug) wxLogDebug((wxString)message);
    else if (verbose == LogVerbose::Message) wxLogMessage((wxString)message);
    else if (verbose == LogVerbose::Warning) wxLogWarning((wxString)message);
    else if (verbose == LogVerbose::Error) wxLogError((wxString)message);
}
#endif


//-----------------------------------------------------------------------------
void LogTargetFilename::SetFilename(const String& filename)
/**
 * \brief Sets the filename of the log file.
 **/
{
    m_filename = filename;
}

//-----------------------------------------------------------------------------
void LogTargetFilename::Write(LogVerbose verbose, const String& message)
/**
 * \brief Writes the message into the log target. The verbose level should not
 * be used to append informations to the message
 * \param verbose Verbose level.
 * \param message Log message.
 **/
{
    #ifdef _RUSH_UNICODE_
    char filename[512];
    wcstombs(filename, m_filename.c_str(), 512);
    FILE* logHandler = fopen(filename, "r+");
    fwprintf(logHandler, L"%s\n", message.c_str());
    fflush(logHandler);
    fclose(logHandler);
    #else
    FILE* logHandler = fopen(m_filename.c_str(), "r+");
    fprintf(logHandler, "%s\n", message.c_str());
    fflush(logHandler);
    fclose(logHandler);
    #endif
}


//-----------------------------------------------------------------------------
LogTarget* LogTarget::CreateTarget(LogTargetType type)
/**
 * \brief Creates an instance ot the given log target type.
 * \param type Log target type.
 * \return New instance of a log target.
 **/
{
    if (type == LogTargetType::StdOut)
    {
        return (new LogTargetStream(stdout));
    }
    else if (type == LogTargetType::StdErr)
    {
        return (new LogTargetStream(stderr));
    }
    #ifdef _RUSH_SUPPORT_WXWIDGETS_
    else if (type == LogTargetType::File)
    {
        String filename = System::GetExecutablePath();
        filename = Path::GetFilename(filename);
        filename = Path::SetExtension((wxString)filename, _T("log"));
        return (new LogTargetFilename(filename));
    }
    else if (type == LogTargetType::wxWidgets)
    {
        return (new LogTargetWidgets());
    }
    #endif
    return (NULL);
}


} // namespace rush


