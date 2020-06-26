/*
 * version.h - Deklaration der Version Klasse
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2007-2012 - Steffen Ott
 *
 */


#ifndef _RUSH_VERSION_H_
#define _RUSH_VERSION_H_


#include <rush/config.h>
#include <rush/string.h>

namespace rush {

/**
 * \brief The Version class contains version information splitt into
 * major, minor and build version. Unlike wxVersionInfo it does not have
 * micro, name, copyright and description properties. Read and write from
 * text information can be done by using the static ReadVersion() and
 * WriteVersion() methods.
 **/
class Version
{
    public:
        Version();
        #ifdef _RUSH_UNICODE_
        Version(int major, int minor, int build, bool unicode=true);
        #else
        Version(int major, int minor, int build, bool unicode=false);
        #endif
        ~Version();

        bool operator==(const Version& version);
        bool operator!=(const Version& version);
        bool operator<=(const Version& version);
        bool operator>=(const Version& version);
        bool operator<(const Version& version);
        bool operator>(const Version& version);

        #ifdef _RUSH_UNICODE_
        void SetVersion(int major, int minor, int build, bool unicode=true);
        #else
        void SetVersion(int major, int minor, int build, bool unicode=false);
        #endif
        String GetVersion(const String& format = _T("%a.%b.%c %u %d")) const;

        void SetMajor(int major);
        int GetMajor() const;

        void SetMinor(int minor);
        int GetMinor() const;

        void SetBuild(int build);
        int GetBuild() const;

        void SetUnicode(bool unicode=true);
        bool IsUnicode() const;

        void SetDebug(bool debug=true);
        bool IsDebug() const;

        static String WriteVersion(const Version& version);
        static Version ReadVersion(const String& version);

    private:
        int m_major;
        int m_minor;
        int m_build;
        bool m_unicode;
        bool m_debug;
};

} // namespace rush

#endif // _RUSH_VERSION_H_
