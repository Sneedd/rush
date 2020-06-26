/*
 * version.cpp - Implementierung der Version Klasse
 *
 * This file is part of the penv framework.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2007-2012 - Steffen Ott
 *
 */



#include <rush/version.h>


namespace rush {


//-----------------------------------------------------------------------------
Version::Version()
/**
 * \brief Constructor, initialize the version with 0.0.0.
 **/
{
    m_major = 0;
    m_minor = 0;
    m_build = 0;
    m_unicode = false;
    #if defined(_RUSH_DEBUG_)
    m_debug = true;
    #else
    m_debug = false;
    #endif
}



//-----------------------------------------------------------------------------
Version::Version(int major, int minor, int build, bool unicode)
/**
 * \brief Constructor, initialize the version with the given
 * version numbers.
 * \param major Major version number.
 * \param minor Minor version number.
 * \param build Build version number.
 * \param unicode is this build a unicode build. The default
 * value is the build version of the wxWidgets framework.
 **/
{
    SetVersion(major, minor, build, unicode);
    #if defined(_RUSH_DEBUG_)
    m_debug = true;
    #else
    m_debug = false;
    #endif
}


//-----------------------------------------------------------------------------
Version::~Version()
/**
 * \brief Destructor.
 **/
{
    // Nothing to do.
}



//-----------------------------------------------------------------------------
bool Version::operator==(const Version& version)
/**
 * \brief Compares two versions if they are equal. Just compares
 * the version numbers and unicode, it does not compare debug.
 * \param version Version to compare with this object.
 * \return True if the versions are equal; false otherwise.
 **/
{
    return (m_major == version.m_major &&
        m_minor == version.m_minor &&
        m_build == version.m_build);
}



//-----------------------------------------------------------------------------
bool Version::operator!=(const Version& version)
/**
 * \brief Compares two versions if they are unequal. Just compares
 * the version numbers and unicode, it does not compare debug.
 * \param version Version to compare with this object.
 * \return True if the versions are unequal; false otherwise.
 **/
{
    return (!(m_major != version.m_major &&
        m_minor != version.m_minor &&
        m_build != version.m_build));
}


//-----------------------------------------------------------------------------
bool Version::operator<=(const Version& version)
/**
 * \brief Compares two versions if they are smaller or equal.
 * Just compares the version numbers and unicode, it does not
 * compare debug.
 * \param version Version to compare with this object.
 * \return True if the versions are smaller or equal; false otherwise.
 **/
{
    return (!(*this > version));
}


//-----------------------------------------------------------------------------
bool Version::operator>=(const Version& version)
/**
 * \brief Compares two versions if they are bigger or equal.
 * Just compares the version numbers and unicode, it does not
 * compare debug.
 * \param version Version to compare with this object.
 * \return True if the versions are bigger or equal; false otherwise.
 **/
{
    return (!(*this < version));
}


//-----------------------------------------------------------------------------
bool Version::operator<(const Version& version)
/**
 * \brief Compares two versions if they are smaller.
 * Just compares the version numbers and unicode, it does not
 * compare debug.
 * \param version Version to compare with this object.
 * \return True if the versions are smaller; false otherwise.
 **/
{
    if (m_major < version.m_major)
    {
       return(true);
    }
    if(m_major == version.m_major)
    {
        if(m_minor < version.m_minor)
        {
            return(true);
        }
        if(m_minor == version.m_minor)
        {
            if(m_build < version.m_build)
            {
                return (true);
            }
        }
    }
    return (false);
}


//-----------------------------------------------------------------------------
bool Version::operator>(const Version& version)
/**
 * \brief Compares two versions if they are bigger.
 * Just compares the version numbers and unicode, it does not
 * compare debug.
 * \param version Version to compare with this object.
 * \return True if the versions are bigger; false otherwise.
 **/
{
    if (m_major > version.m_major)
    {
        return (true);
    }
    if (m_major == version.m_major)
    {
        if (m_minor > version.m_minor)
        {
            return (true);
        }
        if (m_minor == version.m_minor)
        {
            if(m_build > version.m_build)
            {
                return(true);
            }
        }
    }
    return (false);
}



//-----------------------------------------------------------------------------
void Version::SetVersion(int major, int minor, int build, bool unicode)
/**
 * \brief Sets the version of this object.
 * \param major Major version number.
 * \param minor Minor version number.
 * \param build Build version number.
 * \param unicode is this build a unicode build. The default
 * value is the build version of the wxWidgets framework.
 **/
{
    m_major = major;
    m_minor = minor;
    m_build = build;
    m_unicode = unicode;
}


//-----------------------------------------------------------------------------
String Version::GetVersion(const String& format) const
/**
 * \brief Returns a version string with the delivered format.
 * The following placeholder are available: <br>
 * <ul>
 * <li> %a = major version number</li>
 * <li> %b = minor version number</li>
 * <li> %c = build version number</li>
 * <li> %u = if unicode build, 'unicode' will be written at this point</li>
 * <li> %d = if debug build, 'debug' will be written at this point</li>
 * </ul>
 * <br>Example:<br>
 * <code>
 * wxString format = version.GetVersion(_T("%a.%b.%c %u %d"));<br>
 * // Possible returns a string like this: "1.0.1018 unicode debug"<br>
 * </code>
 * \param format format of the version string.
 * \return Version string.
 **/
{
    // Parsen des Format Strings
    String version;
    for (size_t i=0; i<format.Length(); ++i)
    {
        if (format[i] == '%') {
            i++;
            if (format[i] == 'a') version.AppendFormat(_T("%i"),m_major);
            if (format[i] == 'b') version.AppendFormat(_T("%i"),m_minor);
            if (format[i] == 'c') version.AppendFormat(_T("%i"),m_build);
            if (format[i] == 'u') version.Append(_T("unicode"));
            if (format[i] == 'd') version.Append(_T("debug"));
        } else {
            version.Append(format[i]);
        }
    }
    return (version);
}


//-----------------------------------------------------------------------------
void Version::SetMajor(int major)
/**
 * \brief Sets the major version number.
 * \param major Major version number.
 **/
{
    m_major = major;
}


//-----------------------------------------------------------------------------
int Version::GetMajor() const
/**
 * \brief Returns the major version number.
 * \return Major version number.
 **/
{
    return (m_major);
}


//-----------------------------------------------------------------------------
void Version::SetMinor(int minor)
/**
 * \brief Sets the minor version number.
 * \param minor Minor version number.
 **/

{
    m_minor = minor;
}


//-----------------------------------------------------------------------------
int Version::GetMinor() const
/**
 * \brief Returns the minor version number.
 * \return Minor version number.
 **/
{
    return (m_minor);
}


//-----------------------------------------------------------------------------
void Version::SetBuild(int build)
/**
 * \brief Sets the build version number.
 * \param build Build version number.
 **/

{
    m_build = build;
}


//-----------------------------------------------------------------------------
int Version::GetBuild() const
/**
 * \brief Returns the build version number.
 * \return Build version number.
 **/
{
    return (m_build);
}


//-----------------------------------------------------------------------------
void Version::SetUnicode(bool unicode)
/**
 * \brief Sets the versions unicode information.
 * \param unicode True if this version is unicode.
 **/
{
    m_unicode = unicode;
}

//-----------------------------------------------------------------------------
bool Version::IsUnicode() const
/**
 * \brief Returns if this version is a unicode build.
 * \return True if this version is a unicode build; otherwise false.
 **/
{
    return (m_unicode);
}


//-----------------------------------------------------------------------------
void Version::SetDebug(bool debug)
/**
 * \brief Sets if the version is a debug build.
 * \param debug True if this version is a debug build; otherwise false.
 **/
{
    m_debug = debug;
}


//-----------------------------------------------------------------------------
bool Version::IsDebug() const
/**
 * \brief Returns if this version is a debug build.
 * \return True if this version is a debug build; otherwise false.
 **/
{
    return (m_debug);
}


//-----------------------------------------------------------------------------
String Version::WriteVersion(const Version& version)
/**
 * \brief
 **/
{
    return (_T("0.0.0"));
}


//-----------------------------------------------------------------------------
Version Version::ReadVersion(const String& version)
/**
 * \brief Parses a version string like '%a.%b.%c' and writes it
 * into this class. See GetVersion() for more information.
 * \param version Version string.
 * \return True on success; false otherwise;
 **/
{
    return (Version(0,0,0));
//    String number;
//    int which = 0; // 0 = major, 1 = minor, 2 = build
//    bool error = false;
//    for (size_t i=0; i<versionstring.Length(); ++i)
//    {
//        if (versionstring[i] == ' '  || versionstring[i] == '\n' ||
//            versionstring[i] == '\r' || versionstring[i] == '\t') {
//            continue;
//        }
//        if (versionstring[i] >= '0' || versionstring[i] <= '9') {
//            number.Append(versionstring[i]);
//        }
//        if (versionstring[i] == '.') {
//            if (which == 0) {
//                error = error && Parser::TryParseInt(number, &m_major);
//            } else if (which == 1) {
//                error = error && Parser::TryParseInt(number, &m_minor);
//            }
//            which++;
//        }
//    }
//    if (which == 0) {
//        return (false);
//    }
//    if (which == 1) {
//        m_build = 0;
//        error = error && Parser::TryParseInt(&m_minor);
//    }
//    if (which == 2) {
//        error = error && Parser::TryParseInt(&m_build);
//    }
//    return (error);
}





} // namespace rush



