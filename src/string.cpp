/*
 * string.cpp - Implementation of String class
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2011-2012 - Steffen Ott
 *
 */


#include <rush/string.h>
#include <rush/log.h>
#include <rush/buildinexpect.h>
#include <rush/macros.h>


#ifdef _RUSH_UNICODE_
    #undef __STRICT_ANSI__
    #undef _WSTDIO_DEFINED
    //#include <libintl.h>
#endif

#include <stdio.h>

#define RUSH_STRING_FORMAT_BUFFER_SIZE 1024

namespace rush {


//-----------------------------------------------------------------------------
String::String()
/**
 * \brief Standardconstructor, initializes the string class.
 * Initializes an empty string and an initial capacity of 32.
 **/
{
	m_capacity = 32;  // Initial capacity
	m_array = new Char[m_capacity];
	m_size = 0;
	m_array[0] = '\0';
}


//-----------------------------------------------------------------------------
String::String(const String& strg)
/**
 * Kopierkonstruktor. Initialisiert den String mit dem gleichen
 * Inhalt des übergebenen Strings und einer erweiterten Kapazität
 * zur Größe des Strings.
 **/
{
	m_size = strg.m_size;
	m_capacity = strg.m_capacity;
	m_array = new Char[m_capacity];
	m_array = (Char*)memcpy(m_array, strg.m_array, sizeof(Char)*m_size);
	m_array[m_size] = '\0';
}


//-----------------------------------------------------------------------------
String::String(const Char* strg)
/**
 * Konstruktor der Char* Strings übernimmt. Initalisiert den String
 * mit dem gleichen Inhalt des übergebenen Strings und einer erweiterten
 * Kapazität zur Größe des Strings.
 **/
{
    // Empty string if null
	if (strg == NULL) this->Clear();

	// Count the characters
	m_size = 0;
	while (likely(strg[m_size++] != '\0'));
	m_size--;
    m_capacity = m_size+1;

    // Copy the string
	m_array = new Char[m_capacity];
	m_array = (Char*)memcpy(m_array, strg, sizeof(Char)*m_size);
	m_array[m_size] = '\0';
}


//-----------------------------------------------------------------------------
String::String(Char character, size_t count)
/**
 * \brief Constructor, intializes the String class.
 * Creates a string which contains count times the given character.
 **/
{
	m_size = count;
	m_capacity = m_size+1;
	m_array = new Char[m_capacity];
	for (size_t i=0; i<count; ++i)
    {
        m_array[i] = character;
    }
	m_array[m_size] = '\0';
}


//-----------------------------------------------------------------------------
String::String(size_t capacity)
/**
 * \brief Constructor, initializes the string object with the given capacity.
 * Always extends the capacity with one, so that the string doesnot need to reallocate
 * when the capacity is set the count of another string, because of the terminating '\0'.
 **/
{
	m_size = 0;
	if (capacity < 8) capacity = 8;
	m_capacity = capacity+1;
	m_array = new Char[capacity];
	m_array[0] = '\0';
}


#ifdef _RUSH_SUPPORTS_STD_
//-----------------------------------------------------------------------------
String::String(const std::string& strg)
{
    RUSH_NOT_IMPLEMENTED_YET();
}
#endif


#ifdef _RUSH_SUPPORTS_WXWIDGETS_
//-----------------------------------------------------------------------------
String::String(const wxString& strg)
{
    const Char* text = strg.c_str();
    m_size = strg.length();
    m_capacity = m_size+1;
	m_array = new Char[m_capacity];
	m_array = (Char*)memcpy(m_array, text, sizeof(Char)*m_size);
	m_array[m_size] = '\0';
}
#endif



//-----------------------------------------------------------------------------
String::~String()
/**
 * Destruktor. Gibt allen reservierten Speicher frei.
 **/
{
	if (m_array != NULL)
    {
        delete [] m_array;
    }
}


//-----------------------------------------------------------------------------
String& String::operator=(const String& strg)
/**
 * Zuweisungsoperator für String&. Kopiert den String eins zu eins
 * in diesen String.
 **/
{
	if (likely(m_array != NULL)) {
		delete [] m_array;
	}

	m_size = strg.m_size;
	m_capacity = strg.m_capacity;
	m_array = new Char[m_capacity];
	m_array = (Char*)memcpy(m_array, strg.m_array, sizeof(Char)*m_size);
	m_array[m_size] = '\0';
	return (*this);
}


//-----------------------------------------------------------------------------
String& String::operator=(const Char* strg)
/**
 * Zuweisungsoperator für Char*. Kopiert den String eins zu eins
 * in diesen String.
 **/
{
    // Empty string if null
	if (strg == NULL) {
        this->Clear();
        return (*this);
	}

	// Count the characters
	m_size = 0;
	while (likely(strg[m_size++] != '\0'));
	m_size--;
    m_capacity = m_size+1;

    // Delete old string data
	if (likely(m_array != NULL)) {
		delete [] m_array;
	}

    // Copy the string
	m_array = new Char[m_capacity];
	m_array = (Char*)memcpy(m_array, strg, sizeof(Char)*m_size);
	m_array[m_size] = '\0';

	return (*this);
}

#ifdef _RUSH_SUPPORTS_WXWIDGETS_
//-----------------------------------------------------------------------------
String& String::operator=(const wxString& strg)
{
    const Char* text = strg.c_str();
	m_size = strg.length();
    m_capacity = m_size+1;

    // Delete old string data
	if (likely(m_array != NULL))
    {
		delete [] m_array;
	}

    // Copy the string
	m_array = new Char[m_capacity];
	m_array = (Char*)memcpy(m_array, text, sizeof(Char)*m_size);
	m_array[m_size] = '\0';

	return (*this);
}
#endif


//-----------------------------------------------------------------------------
Char& String::operator[](const size_t index)
/**
 * Zugriffsoperator für Zugriff auf jedes einzelne Element im
 * String. Wird ein zu großer Index angegeben wird, ein Exception
 * geworfen. Ansonten wird einfach 0 zurück geliefert.
 **/
{
	if (unlikely(index >= m_size))
	{
	    int* test = NULL;
	    test[0] = 0;
	    Log::Error(_T("[String::operator[]] Index out of range."));
		return (m_array[0]); // TODO : TEST
	}
	return (m_array[index]);
}

//-----------------------------------------------------------------------------
const Char& String::operator[](size_t index) const
/**
 * \brief
 **/
{
    if (unlikely(index >= m_size))
	{
	    int* test = NULL;
	    test[0] = 0;
	    Log::Error(_T("[String::operator[]] Index out of range."));
		return (m_array[0]); // TODO : TEST
	}
	return (m_array[index]);
}


//-----------------------------------------------------------------------------
bool String::operator==(const String& strg) const
{
    if (m_size != strg.m_size) {
        return (false);
    }
//    for (size_t i=0; i<m_size; ++i)
//    {
//        if (m_array[i] != strg.m_array[i])
//        {
//            return (false);
//        }
//    }
//    return (true);
    return (memcmp(m_array, strg.m_array, m_size*sizeof(Char)) == 0);
}


//-----------------------------------------------------------------------------
bool String::operator!=(const String& strg) const
{
    if (m_size != strg.m_size) {
        return (true);
    }
//    if (m_size == 0) {
//        return (false);
//    }
//    for (size_t i=0; i<m_size; ++i)
//    {
//        if (m_array[i] == strg.m_array[i])
//        {
//            return (false);
//        }
//    }
//    return (true);
    return (memcmp(m_array, strg.m_array, m_size*sizeof(Char)) != 0);
}


#ifdef _RUSH_SUPPORTS_STD_
//-----------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& sout, const String& a)
/**
 * Output Stream Operator.
 **/
{
    NOT_IMPLEMENTED_YET();
}
#endif


#ifdef _RUSH_SUPPORTS_STD_
//-----------------------------------------------------------------------------
String& operator>>(std::istream& sin, const String& a)
/**
 * Input Stream Operator.
 **/
{
	NOT_IMPLEMENTED_YET();
}
#endif // _SCL_SUPPORT_STD_



//-----------------------------------------------------------------------------
String& String::Append(Char ch)
/**
 * Fügt ein Charakter an den String an und erweitert damit den
 * String um eins.
 **/
{
	if (unlikely(m_size+2 > m_capacity))
    {
		this->Alloc(m_capacity*2);
	}
	m_array[m_size] = ch;
	m_size++;
	m_array[m_size] = '\0';
	return (*this);
}


//-----------------------------------------------------------------------------
String& String::Append(const String& strg)
/**
 * Fügt ein String am Ende dieses Strings an. Es wird der
 * zusammengefügte String zurückgeliefert.
 **/
{
    if (unlikely(strg.Length() == 0)) return (*this);

    // Check if capacity must be increased
	if (unlikely(strg.m_size+m_size+1 > m_capacity))
    {
        // Increase capacity always with power of two
        size_t capacity = m_capacity*2;
        while (strg.m_size+m_size+1 > capacity) capacity *= 2;
		this->Alloc(capacity);
	}

	// Copy the string data into this string
	memcpy(m_array+m_size, strg.m_array, strg.m_size*sizeof(Char));
	m_size += strg.m_size;
	m_array[m_size] = '\0';
	return (*this);
}



//-----------------------------------------------------------------------------
String& String::Append(const Char* strg)
/**
 * Fügt ein String am Ende dieses Strings an. Es wird der
 * zusammengefügte String zurückgeliefert.
 **/
{
	if (unlikely(strg == NULL)) return (*this);

	// Calculate string size
	size_t strgLen = 0;
	while (strg[strgLen++] != '\0') ;
	strgLen--;

	// Check if capacity must be increased
	if (unlikely(strgLen+m_size+1 > m_capacity))
    {
        // Increase capacity always with power of two
        size_t capacity = m_capacity*2;
        while (strgLen+m_size+1 > capacity) capacity *= 2;
		this->Alloc(capacity);
	}

	// Copy the string data into this string
	memcpy(m_array+m_size, strg, strgLen*(sizeof(Char)));
	m_size += strgLen;
	m_array[m_size] = '\0';
	return (*this);
}


//-----------------------------------------------------------------------------
String& String::AppendFormat(const String& format, ...)
/**
 * \brief Formats a string similar to the printf function.
 * Note: The maximal size of the appended string is 1024 characters.
 * \param format Format string.
 **/
{

    va_list args;
    va_start(args,format);
    int maxsize = RUSH_STRING_FORMAT_BUFFER_SIZE;
    Char buffer[maxsize];
    #ifdef _RUSH_UNICODE_
    vsnwprintf(buffer,RUSH_STRING_FORMAT_BUFFER_SIZE,format.c_str(),args);
    #else
    vsnprintf(buffer,RUSH_STRING_FORMAT_BUFFER_SIZE,format.c_str(),args);
    #endif
    this->Append(buffer);
    return (*this);
}


//-----------------------------------------------------------------------------
String& String::AppendFormatV(const String& format, va_list args)
/**
 * \brief Formats a string similar to the pringf function and appends it.
 * Note: The maximal size of the appended string is 1024 characters.
 * \param format Format string.
 * \param args Argument list.
 * \return This string.
 **/
{
    int maxsize = RUSH_STRING_FORMAT_BUFFER_SIZE;
    Char buffer[maxsize];
    #ifdef _RUSH_UNICODE_
    vsnwprintf(buffer,RUSH_STRING_FORMAT_BUFFER_SIZE,format.c_str(),args);
    #else
    vsnprintf(buffer,RUSH_STRING_FORMAT_BUFFER_SIZE,format.c_str(),args);
    #endif
    this->Append(buffer);
    return (*this);
}


//-----------------------------------------------------------------------------
String& String::Insert(size_t index, const String& strg)
/**
 * Fügt ein String an einer gegebenen Stelle ein.
 **/
{
    if (strg.m_size == 0) return (*this);
	if (unlikely(index > m_size))
    {
        Log::Error(_T("[String::Insert] Index out of range."));
		return (*this);
	}

	// Check if capacity must be increased
	if (unlikely(strg.m_size+m_size+1 > m_capacity))
    {
        // Increase capacity always with power of two
        size_t capacity = m_capacity*2;
        while (strg.m_size+m_size+1 > capacity) capacity *= 2;
		this->Alloc(capacity);
	}

    // Create the empty space for the insert
    if (index < m_size)
    {
        for (int i=m_size-index-1; i>=0; --i)
        {
			m_array[i+index+strg.m_size] = m_array[i+index];
		}
    }

    // Copy the given string in this string
	memcpy(m_array+index, strg.m_array, strg.m_size*sizeof(Char));
	m_size += strg.m_size;
	m_array[m_size] = '\0';
	return (*this);
}



//-----------------------------------------------------------------------------
int String::Find(const String& strg) const
/**
 * Sucht nach dem ersten auftreten eines Strings und liefert dessen erste
 * Position zurück oder -1 wenn der String nicht gefunden wurde.
 **/
{
	if (unlikely(m_array == NULL || strg.m_array == NULL || strg.m_size > m_size))
    {
		return (-1);
	}

	for (size_t i=0; i<m_size; ++i)
	{
		if (unlikely(m_array[i] == strg.m_array[0]))
		{
			if (unlikely(strg.m_size == 1))
            {
				return (i);
			}
			for (size_t j=1; likely(j<strg.m_size); j++)
			{
				if (likely((m_array[i+j] == strg.m_array[j]) && ((i+j) < m_size)))
				{
					if (unlikely(j>=strg.m_size-1)) {
						return ((int)i);
					}
				} else {
					break;
				}
			}
		}
	}
	return (-1);
}


//-----------------------------------------------------------------------------
int String::Find(Char ch) const
/**
 * \brief Searches for the first occurence of the given character in this string.
 * If this method doesn't find the character in the string, it will return -1.
 **/
{
    for (size_t i=0; i<m_size; ++i)
    {
        if (m_array[i] == ch) return (i);
    }
    return (-1);
}



//-----------------------------------------------------------------------------
int String::FindFirst(const String& strg) const
/**
 * Sucht nach dem ersten auftreten eines Strings und liefert dessen erste
 * Position zurück oder -1 wenn der String nicht gefunden wurde.
 **/
{
	return (this->Find(strg));
}


//-----------------------------------------------------------------------------
int String::FindFirst(Char ch) const
/**
 * \brief Searches for the first occurence of the given character in this string.
 * If this method doesn't find the character in the string, it will return -1.
 **/
{
    return (this->Find(ch));
}


//-----------------------------------------------------------------------------
int String::FindLast(const String& strg) const
/**
 * Sucht nach dem letzten Auftreten eines Strings und liefert dessen erste
 * Position zurück oder -1 wenn der String nicht gefunden wurde.
 **/
{
    RUSH_NOT_IMPLEMENTED_YET();
    return (-1);
}


//-----------------------------------------------------------------------------
int String::FindLast(Char ch) const
/**
 * \brief Searches for the first occurence of the given character in this string
 * starting from the end of the string.
 * If this method doesn't find the character in the string, it will return -1.
 **/
{
    for (int i=m_size-1; i>=0; --i)
    {
        if (m_array[i] == ch) return (i);
    }
    return (-1);
}


//-----------------------------------------------------------------------------
bool String::Contains(const String& strg) const
/**
 * Sucht nach Auftreten des übegebenen Strings und liefert
 * true wenn dieser gefunden wurde. Ansonsten false. Diese Methode
 * hat einen gewissen Geschwindigkeitsvorteil gegenüber findOccurence()
 * da nach dem ersten Auftreten die Suche beendet wird.
 **/
{
	return (this->Find(strg) != -1);
}


//-----------------------------------------------------------------------------
bool String::Contains(Char ch) const
/**
 * \brief
 **/
{
    return (this->Find(ch) != -1);
}


//-----------------------------------------------------------------------------
bool String::StartsWith(const String& strg) const
/**
 * \brief
 **/
{
    for (size_t i=0; i<m_size; ++i)
    {
        if (strg.m_array[i] != m_array[i]) return (false);
        if (strg.m_size-1 <= i) return (true);
    }
    return (true);
}


//-----------------------------------------------------------------------------
bool String::EndsWith(const String& strg) const
/**
 * \brief
 **/
{
    int diff = m_size - strg.m_size;
    for (int i=m_size-1; i>=0; --i)
    {
        if (strg.m_array[i-diff] != m_array[i]) return (false);
        if (i-diff <= 0) return (true);
    }
    return (true);
}


//-----------------------------------------------------------------------------
size_t String::Replace(Char oldValue, Char newValue)
{
    size_t count = 0;
    for (size_t i=0; i<m_size; ++i)
    {
        if (m_array[i] == oldValue) {
            m_array[i] = newValue;
            count += 1;
        }
    }
    return (count);
}


//-----------------------------------------------------------------------------
size_t String::Replace(const String& oldValue, const String& newValue)
/**
 * Tauscht alle vorkommenden Zeichenketten aus "part" mit denen aus
 * "replacement" aus und liefert die Anzahl der Ersetzungen.
 **/
{
	return (this->Replace(oldValue, newValue, 0, m_size));
}


//-----------------------------------------------------------------------------
size_t String::Replace(const String& oldValue, const String& newValue, size_t startindex, size_t length)
/**
 * Tauscht alle vorkommenden Zeichenkette aus "part" mit denen aus "replacement"
 * aus in dem Bereich von startindex bis lenght.
 **/
{
	RUSH_NOT_IMPLEMENTED_YET();
	return (0);
}



//-----------------------------------------------------------------------------
void String::Remove(size_t index)
/**
 * Löscht ab dem gegebenen Index alle restlichen Zeichen weg.
 **/
{
    if (index < m_size+1)
    {
        m_size = index;
        m_array[m_size] = '\0';
    }
}


//-----------------------------------------------------------------------------
void String::Remove(size_t index, size_t length)
/**
 * Löscht ab dem gegebenen Index bis zur angegebenen Länge alle
 * Zeichen weg.
 **/
{
	if (unlikely(index > m_size || index+length > m_size))
    {
        Log::Error(_T("[String::Remove] Index out of range."));
		return;
	}

    // Create the empty space for the insert
    if (index < m_size)
    {
        for (size_t i=index+length; i<m_size; ++i)
        {
			m_array[i-length] = m_array[i];
		}
    }

    m_size -= length;
    m_array[m_size] = '\0';
}



//-----------------------------------------------------------------------------
int String::RemoveAll(Char ch)
/**
 * Löscht alle Vorkommen des Übergebenen Zeichens aus dem String.
 * Kapazität des Strings bleibt erhalten.
 **/
{
    RUSH_NOT_IMPLEMENTED_YET();
    return (0);
}


//-----------------------------------------------------------------------------
int String::RemoveAll(const String& strg)
/**
 * Löscht alle Vorkommen des Übergebenen Strings aus dem String.
 * Kapazität des Strings bleibt erhalten.
 **/
{
    RUSH_NOT_IMPLEMENTED_YET();
    return (0);
}


//-----------------------------------------------------------------------------
String String::Substring(size_t index) const
{
    if (index >= m_size)
    {
        Log::Error(_T("[String::Substring] Index out of range."));
        return (_T(""));
    }
    return (String(m_array+index));
}


//-----------------------------------------------------------------------------
String String::Substring(size_t index, size_t length) const
{
    if (index + length >= m_size)
    {
        Log::Error(_T("[String::Substring] Index out of range."));
        return (_T(""));
    }
    String result(length);
    result.m_array = (Char*)memcpy(result.m_array, m_array+index, length+sizeof(Char));
    result.m_array[length] = '\0';
    result.m_size = length;
    return (result);
}


//-----------------------------------------------------------------------------
String& String::Trim()
/**
 * Löscht am Anfang und Ende des Strings alle vorkommen
 * von Whitespace und NewLines. Siehe Char::IsWhitespace() für die
 * Definition von Whitespace Zeichen und Char::IsNewLine() für
 * NewLine Zeichen.
 **/
{
    return (this->Trim(_T(" \t\n\r")));
}


//-----------------------------------------------------------------------------
String& String::Trim(Char ch)
/**
 * Löscht am Anfang und Ende des Strings alle Vorkommen
 * des übergeben Zeichens weg.
 **/
{
    // TODO : Optimize
    return (this->TrimFirst(ch).TrimLast(ch));
}



//-----------------------------------------------------------------------------
String& String::Trim(const String& strg)
{
    // TODO : Optimize
    return (this->TrimFirst(strg).TrimLast(strg));
}



//-----------------------------------------------------------------------------
String& String::TrimFirst()
{
    return (this->TrimFirst(_T(" \t\n\r")));
}



//-----------------------------------------------------------------------------
String& String::TrimFirst(Char ch)
{
    for (size_t index=0; index<m_size; ++index)
    {
        if (m_array[index] != ch) {
            this->Remove(0, index);
            break;
        }
    }
    return (*this);
}



//-----------------------------------------------------------------------------
String& String::TrimFirst(const String& strg)
{
    for (size_t index=0; index<m_size; ++index)
    {
        if (strg.Find(m_array[index]) == -1) {
            this->Remove(0, index);
            break;
        }
    }
    return (*this);
}



//-----------------------------------------------------------------------------
String& String::TrimLast()
{
    return (this->TrimLast(_T(" \t\n\r")));
}



//-----------------------------------------------------------------------------
String& String::TrimLast(Char ch)
{
    for (size_t index=m_size-1; index>=0; --index)
    {
        if (m_array[index] != ch) {
            this->Remove(index+1);
            break;
        }
    }
    return (*this);
}



//-----------------------------------------------------------------------------
String& String::TrimLast(const String& strg)
{
    for (size_t index=m_size-1; index>=0; --index)
    {
        if (strg.Find(m_array[index]) == -1) {
            this->Remove(index+1);
            break;
        }
    }
    return (*this);
}




//-----------------------------------------------------------------------------
String String::ToUpper() const
/**
 * \brief Copies this string and convert all lower case characters in
 * upper case characters.
 * Note: Only ASCII characters will be used, means 'a' to 'z'.
 **/
{
    String result(*this);
    for (size_t i=0; i<result.m_size; ++i)
    {
        Char ch = result.m_array[i];
        if (ch >= 'a' && ch <= 'z')
        {
            result.m_array[i] -= 32;
        }
    }
    return (result);
}


//-----------------------------------------------------------------------------
String String::ToLower() const
/**
 * \brief Copies this string and convert all upper case characters in
 * lower case characters.
 * Note: Only ASCII characters will be used, means 'a' to 'z'.
 **/
{
    String result(*this);
    for (size_t i=0; i<result.m_size; ++i)
    {
        Char ch = result.m_array[i];
        if (ch >= 'A' && ch <= 'Z')
        {
            result.m_array[i] += 32;
        }
    }
    return (result);
}


//-----------------------------------------------------------------------------
void String::Clear()
/**
 * Löscht den String und iniatlisiert die Kapazität neu.
 **/
{
    // Shrinks the string if capacity is to big
    if (unlikely(m_capacity > 64)) {
        this->Alloc(64);
    }

    // Empties array
    m_array[0] = '\0';
    m_size = 0;
}


#ifdef __DEBUG__
//-----------------------------------------------------------------------------
bool String::IsOk() const
{
    #ifdef _RUSH_UNICODE_
    return (m_array[m_size] == '\0' &&
            m_size < m_capacity &&
            wcslen(m_array) == m_size);
    #else
    return (m_array[m_size] == '\0' &&
            m_size < m_capacity &&
            strlen(m_array) == m_size);
    #endif
}
#endif



#ifdef __DEBUG__
//-----------------------------------------------------------------------------
void String::PrintTestString()
{
    #ifdef _RUSH_UNICODE_
    fwprintf(stdout, _T("\nsize=%i(%i) cap=%i array='%s'\n"),
        m_size, wcslen(m_array), m_capacity, m_array);
    #else
    fprintf(stdout, _T("\nsize=%i(%i) cap=%i array='%s'\n"),
        m_size, strlen(m_array), m_capacity, m_array);
    #endif
}
#endif



//-----------------------------------------------------------------------------
void String::Shrink()
/**
 * Schrumpft ein String auf dessen Länge. Die Kapazität ist
 * nach dieser Funktion genau so groß wie die Länge.
 **/
{
	if (likely(m_capacity+1 > m_size))
    {
		Char* temp = new Char[m_size+1];
		temp = (Char*)memcpy(temp, m_array, m_size*sizeof(Char));
		delete [] m_array;
		m_array = temp;
        m_array[m_size] = '\0';
		m_capacity = m_size+1;
	}
}


//-----------------------------------------------------------------------------
void String::Alloc(size_t capacity)
/**
 * Reserviert mehr Speicher für den String, um die übergebene Anzahl
 * von Zeichen. Bzw. kann aber auch die Anzahl der Zeichen verringern wenn
 * eine Größe angegeben wird, die kleiner ist als die jetztige Größe
 * des Strings. Also theoretisch ein Resize, nur das die Kapazität des
 * Strings verringert oder erhöht wird.
 **/
{
    if (capacity < 2) {
        capacity = 2;
    }
	if (likely(capacity > m_capacity))
    {
		// Extend string
		Char* temp = new Char[capacity];
		temp = (Char*)memcpy(temp, m_array, m_capacity*sizeof(Char));
		delete [] m_array;
		m_array = temp;
		m_capacity = capacity;
	}
	else
    {
		if (likely(capacity != m_capacity))
		{
            // Shrink string
            Char* temp = new Char[capacity];
            temp = (Char*)memcpy(temp, m_array,capacity*sizeof(Char));
            delete [] m_array;
            m_array = temp;
            m_capacity = capacity;
            m_size = ((m_size < capacity) ? m_size:capacity);
		}
	}
}


//-----------------------------------------------------------------------------
size_t String::Count(const Char* strg, Char ch)
{
    size_t count = 0;
    while (*strg != '\0')
    {
        if (*strg == ch) count++;
        strg++;
    }
    return (count);
}


//-----------------------------------------------------------------------------
size_t String::Count(const String& strg, Char ch)
{
    return (String::Count(strg.m_array, ch));
}



//-----------------------------------------------------------------------------
String String::Format(const String& format, ...)
/**
 * \brief Formats a string similar to the printf function and returns it.
 * Note: The maximal size of a appended string format string is 1024 characters.
 **/
{
    int maxsize = RUSH_STRING_FORMAT_BUFFER_SIZE;
    Char buffer[maxsize];
    va_list args;
    va_start(args,format);
    #ifdef _RUSH_UNICODE_
    vsnwprintf(buffer,RUSH_STRING_FORMAT_BUFFER_SIZE,format.c_str(),args);
    #else
    vsnprintf(buffer,RUSH_STRING_FORMAT_BUFFER_SIZE,format.c_str(),args);
    #endif
    return (rush::String(buffer));
}


//-----------------------------------------------------------------------------
String String::FormatV(const String& format, va_list args)
{
    int maxsize = RUSH_STRING_FORMAT_BUFFER_SIZE;
    Char buffer[maxsize];
    #ifdef _RUSH_UNICODE_
    vsnwprintf(buffer,RUSH_STRING_FORMAT_BUFFER_SIZE,format.c_str(),args);
    #else
    vsnprintf(buffer,RUSH_STRING_FORMAT_BUFFER_SIZE,format.c_str(),args);
    #endif
    return (rush::String(buffer));
}

//-----------------------------------------------------------------------------
size_t String::Length(const Char* strg)
{
	size_t size = 0;
	if (strg != NULL)
    {
        while (likely(strg[size++] != '\0'));
        size--;
    }
    return (size);
}


//-----------------------------------------------------------------------------
size_t String::Length(const String& strg)
{
    return (strg.Length());
}



} // namespace rush












