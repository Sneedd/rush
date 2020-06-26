/*
 * string.h - Declaration of the String class
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2011-2012 - Steffen Ott
 *
 */




#ifndef _RUSH_STRING_H_
#define _RUSH_STRING_H_

#include <rush/config.h>
#include <string.h>
#include <stdarg.h>


#ifdef _RUSH_SUPPORTS_STD_
    #include <string>
    #include <iostream>
#endif

#ifdef _RUSH_SUPPORTS_WXWIDGETS_
    #include <wx/string.h>
#endif


// String encapsulate definitions
#ifndef rushT
    #ifdef _RUSH_UNICODE_
    #define rushT(x) L ## x
    #else
    #define rushT(x) x
    #endif
#endif

#ifndef _T
    #define _T(x) rushT(x)
#endif

namespace rush {


// Character defintions
#ifdef _RUSH_UNICODE_
typedef wchar_t Char;
#else
typedef char Char;
#endif



/**
 * \brief The String class contains a array of character. The internal
 * Implementation is a standard zero terminated char array. On exception
 * to a normal character array is, that the string could have a bigger
 * capacity than it's size.
 **/
class String
{
    public:
        String();
        String(const String& strg);
        String(const Char* strg);
        String(const Char ch, size_t nr);
        String(size_t capacity);
        #ifdef _RUSH_SUPPORTS_STD_
        String(const std::string& strg);
		#endif
		#ifdef _RUSH_SUPPORTS_WXWIDGETS_
        String(const wxString& strg);
        #endif
		~String();

		String& operator=(const String& strg);
		String& operator=(const Char* strg);
		#ifdef _RUSH_SUPPORTS_WXWIDGETS_
        String& operator=(const wxString& strg);
        #endif
		Char& operator[](size_t index);
		const Char& operator[](size_t index) const;

		#ifdef _RUSH_SUPPORTS_WXWIDGETS_
		explicit operator wxString() const
		{ return (wxString(m_array)); }
		//operator wxString()
		//{ return (wxString(m_array)); }
		#endif

		bool operator==(const String& strg) const;
		bool operator!=(const String& strg) const;

		#ifdef _RUSH_SUPPORTS_STD_
        friend std::ostream& operator<<(std::ostream& sout, const String& a);
        friend String& operator>>(std::istream& sin, const String& a);
        #endif

		String& Append(const String& strg);
		String& Append(const Char* strg);
		String& Append(Char ch);
		String& AppendFormat(const String& format, ...);
		String& AppendFormatV(const String& format, va_list args);
		String& Insert(size_t index, const String& strg);

		int Find(const String& strg) const;
        int Find(Char ch) const;
		int FindFirst(const String& strg) const;
		int FindFirst(Char ch) const;
		int FindLast(const String& strg) const;
        int FindLast(Char ch) const;
		bool Contains(const String& strg) const;
		bool Contains(Char ch) const;
		bool StartsWith(const String& strg) const;
		bool EndsWith(const String& strg) const;

        size_t Replace(Char oldValue, Char newValue);
		size_t Replace(const String& oldValue, const String& newValue);
		size_t Replace(const String& oldValue, const String& newValue, size_t startIndex, size_t length);

		void Remove(size_t index);
		void Remove(size_t index, size_t length);

		int RemoveAll(Char ch);
		int RemoveAll(const String& strg);

		String Substring(size_t index) const;
		String Substring(size_t index, size_t length) const;

		String& Trim();
		String& Trim(Char ch);
		String& Trim(const String& strg);
		String& TrimFirst();
		String& TrimFirst(Char ch);
		String& TrimFirst(const String& strg);
		String& TrimLast();
		String& TrimLast(Char ch);
		String& TrimLast(const String& strg);

		String ToUpper() const;
		String ToLower() const;

		void Clear();

		#ifdef __DEBUG__
        bool IsOk() const;
        void PrintTestString();
        #endif

		inline size_t Length() const
		{ return (m_size); }

		inline size_t Capacity() const
		{ return (m_capacity); }

		inline const Char* c_str() const
		{ return (m_array); }

		void Shrink();
		void Alloc(size_t capacity);

    public:
        static size_t Count(const Char* strg, Char ch);
        static size_t Count(const String& strg, Char ch);
        // TODO Compare
        // TODO Join/Concat
        static String Format(const String& format, ...);
        static String FormatV(const String& format, va_list args);
        static size_t Length(const Char* strg);
        static size_t Length(const String& strg);


    private:
		Char* m_array;
		size_t m_size;
		size_t m_capacity;

};



const String EmptyString = _T("");



} // namespace rush

#endif // _RUSH_STRING_H_

