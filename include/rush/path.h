/*
 * path.h - Declaration of the Path class
 *
 * This file is part of the rush utility library.
 * Licensed under the terms of Lesser GPL v3.0 (see license.txt).
 * Copyright 2011-2012 - Steffen Ott
 *
 */


#ifndef _RUSH_PATH_H_
#define _RUSH_PATH_H_

#include <rush/config.h>

#ifdef _RUSH_SUPPORTS_WXWIDGETS_
#include <wx/string.h>
#include <wx/arrstr.h>
#endif

namespace rush {

class Path
{
    private:
        Path() {}
        virtual ~Path() {}

    public:
        #ifdef _RUSH_SUPPORTS_WXWIDGETS_
        static bool IsAbsolute(const wxString& path);
        static wxString Combine(const wxString& path, const wxString& appendpath);
        static wxString Combine(const wxString& path, const wxArrayString& parts, size_t index = 0, int count = -1);
        static wxString Combine(const wxArrayString& parts, size_t index = 0, int count = -1);
        static wxArrayString Split(const wxString& path);
        static wxString MakeRelative(const wxString& referencepath, const wxString& absolutepath);
        static wxString RemoveLastEntry(const wxString& path);
        static wxString GetLastEntry(const wxString& path);
        static wxString Normalize(const wxString& path);
        static bool Create(const wxString& path);
        static wxString GetExtension(const wxString& path);
        static wxString SetExtension(const wxString& path, const wxString& extension);
        static wxString GetFilename(const wxString& path);
        #endif

		static String GetFilename(const String& path) { return (path); }

};

} // namespace rush

#endif // _RUSH_PATH_H_


