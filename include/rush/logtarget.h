/*
 * logtarget.h - Declaration of the LogTarget class
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2012 - Steffen Ott
 *
 */



#ifndef _RUSH_LOGTARGET_H_
#define _RUSH_LOGTARGET_H_

#include <rush/config.h>
#include <rush/string.h>


namespace rush {

/**
 * \brief The LogVerbose enum spezifies the log verbose level.
 **/
enum class LogVerbose
{
    /// \brief Debugging messages.
    Debug    =  0,
    /// \brief Normal messages.
    Message  = 10,
    /// \brief Warning messages.
    Warning  = 20,
    /// \brief Error messages.
    Error    = 30
};


/**
 * \brief The LogTargetType enum declares the log targets which are already
 * implemented. The log target can be created byt LogTraget::Create()
 **/
enum class LogTargetType
{
    None      =  0,
    StdErr    =  1,
    StdOut    =  2,
    File      =  3,
    wxWidgets =  4
};


/**
 * \brief The LogTarget class is a base class for log targets.
 * This class contains a create method to create the implemented
 * log tragets.
 **/
class LogTarget
{
    public:
        static LogTarget* CreateTarget(LogTargetType type);

        LogTarget() {}
        virtual ~LogTarget() {}

        /**
         * \brief Writes the message into the log target. The verbose level should not
         * be used to append informations to the message
         * \param verbose Verbose level.
         * \param message Log message.
         **/
        virtual void Write(LogVerbose verbose, const String& message) = 0;
};



/**
 * \brief The LogTargetFilename class is the implementation of a log target
 * for a file which will opened on write time.
 **/
class LogTargetFilename : public LogTarget
{
    public:
        LogTargetFilename(const String& filename) : m_filename(filename) {}
        ~LogTargetFilename() {}

        void SetFilename(const String& filename);
        void Write(LogVerbose verbose, const String& message);

    private:
        String m_filename;
};


} // namespace rush

#endif // _RUSH_LOGTARGET_H_
