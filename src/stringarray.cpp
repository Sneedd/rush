/*
 * stringarray.cpp - Implementation of StringArray class
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2011-2012 - Steffen Ott
 *
 */





#include <rush/stringarray.h>
#include <rush/log.h>
#include <rush/buildinexpect.h>
#include <rush/macros.h>


namespace rush {

//-----------------------------------------------------------------------------
StringArray::StringArray()
/**
 * \brief Standardconstructor, initializes the StringArray object.
 * Initialcapacity is 16 strings.
 **/
{
    m_capacity = 16;
    m_count = 0;
    m_items = new String*[m_capacity];
    memset(m_items, 0, m_capacity*sizeof(String*));
}


//-----------------------------------------------------------------------------
StringArray::StringArray(size_t capacity)
/**
 * \brief Constructor, initializes the StringArray object with the
 * given capacity.
 * \param capacity Initial capacity of the array.
 **/
{
    if (unlikely(capacity < 4)) {
        capacity = 4;
    }
    m_capacity = capacity;
    m_count = 0;
    m_items = new String*[m_capacity];
    memset(m_items, 0, m_capacity*sizeof(String*));
}


//-----------------------------------------------------------------------------
StringArray::StringArray(const StringArray& array)
/**
 * \brief Copyconstructor, shallow copies the given array to this.
 * Note, that the copy will not contain copied strings, if you want a
 * full or deep copy, use Copy().
 **/
{
    m_capacity = array.m_count;
    m_count = array.m_count;
    m_items = new String*[m_capacity];
    m_items = (String**)memcpy(m_items, array.m_items, sizeof(String*)*m_capacity);
}


//-----------------------------------------------------------------------------
StringArray::~StringArray()
/**
 * \brief Destructor. Frees all allocated memory.
 **/
{
    if (likely(m_items != NULL))
    {
        for (size_t i=0; i<m_count; ++i)
        {
            if (m_items[i] != NULL)
            {
                delete m_items[i];
            }
        }
        delete [] m_items;
    }
}


//-----------------------------------------------------------------------------
StringArray& StringArray::operator=(const StringArray& array)
/**
 * \brief Assigment operator, copies the given array to this.
 * \param array String array to copy into this array.
 * \return This array.
 **/
{
    if (likely(m_items != NULL))
    {
        for (size_t i=0; i<m_count; ++i)
        {
            if (m_items[i] != NULL)
            {
                delete m_items[i];
                m_items[i] = NULL;
            }
        }
        delete [] m_items;
    }

    m_capacity = array.m_count;
    m_count = array.m_count;
    m_items = new String*[m_capacity];
    for (size_t i=0; i<m_capacity; ++i)
    {
        m_items[i] = new String(*(array.m_items[i]));
    }
    return (*this);
}


//-----------------------------------------------------------------------------
String& StringArray::operator[](size_t index)
/**
 * \brief Returns the string at the given index.
 * \param index Index.
 * \return String at the index.
 **/
{
    if (unlikely(index >= m_count))
    {
        Log::Error(_T("[StringArray::operator[]] Index out of range."));
        return (*m_items[index]);
    }
    return (*m_items[index]);
}


//-----------------------------------------------------------------------------
const String& StringArray::operator[](size_t index) const
/**
 * \brief Returns the string at the given index.
 * \param index Index.
 * \return String at the index.
 **/
{
    if (unlikely(index >= m_count))
    {
        Log::Error(_T("[StringArray::operator[]] Index out of range."));
        return (*m_items[index]);
    }
    return (*m_items[index]);
}


//-----------------------------------------------------------------------------
String& StringArray::Item(size_t index)
/**
 * \brief Returns the string at the given index.
 * \param index Index.
 * \return String at the index.
 **/
{
    if (unlikely(index >= m_count))
    {
        Log::Error(_T("[StringArray::operator[]] Index out of range."));
        return (*m_items[index]);
    }
    return (*m_items[index]);
}


//-----------------------------------------------------------------------------
const String& StringArray::Item(size_t index) const
/**
 * \brief Returns the string at the given index.
 * \param index Index.
 * \return String at the index.
 **/
{
    if (unlikely(index >= m_count))
    {
        Log::Error(_T("[StringArray::operator[]] Index out of range."));
        return (*m_items[index]);
    }
    return (*m_items[index]);
}


//-----------------------------------------------------------------------------
int StringArray::IndexOf(const String& strg) const
/**
 * \brief Searches for a string in the array and returning its index.
 * \param strg String to search for.
 * \return Index in the array or -1 if the string is not in the array.
 **/
{
    for (size_t i=0; i<m_count; ++i)
    {
        if (m_items[i] != NULL)
        {
            if (*(m_items[i]) == strg)
            {
                return (i);
            }
        }
    }
    return (-1);
}


//-----------------------------------------------------------------------------
StringArray& StringArray::Add(const String& strg)
/**
 * \brief Adds a string to the array.
 * \param strg String.
 * \return This array.
 **/
{
    if (unlikely(m_count >= m_capacity))
    {
		this->Alloc(m_capacity*2);
	}
	m_items[m_count] = new String(strg);
	m_count++;
	return (*this);
}



//-----------------------------------------------------------------------------
StringArray& StringArray::AddFormat(const String& format, ...)
/**
 * \brief Adds a formated string to the array. See printf() for format options.
 * \param format Format string.
 * \return This array.
 **/
{
    va_list args;
    va_start(args,format);
    this->Add(String::FormatV(format, args));
    return (*this);
}



//-----------------------------------------------------------------------------
bool StringArray::Insert(size_t index, const String& strg)
/**
 * \brief Inserts a string at the given index.
 * \param index Index.
 * \param strg String.
 * \return True, if string was successful inserted; otherwise false.
 **/
{
    if (unlikely(index > m_count))
    {
        Log::Error(_T("[PrimitiveArray::Insert] Index out of range."));
        return (false);
    }
    if (unlikely(index == m_count))
    {
        this->Add(strg);
        return (true);
    }
    if (unlikely(m_capacity <= m_count))
    {
        this->Alloc(m_capacity*2);
    }

    memmove(m_items+index+1, m_items+index, (m_count-index)*sizeof(String*));
    m_items[index] = new String(strg);
	m_count++;
    return (true);
}


//-----------------------------------------------------------------------------
bool StringArray::Remove(size_t index)
/**
 * \brief Removes a string from the given index.
 * \param index Index.
 * \return True, if string was successful removed; otherwise false.
 **/
{
    if (unlikely(index >= m_count))
    {
        Log::Error(_T("[PrimitiveArray::Remove] Index out of range."));
        return (false);
    }
    if (m_items[index] != NULL)
    {
        delete m_items[index];
    }
    m_items[index] = NULL;
    memmove(m_items+index, m_items+index+1, (m_count-index)*sizeof(String*));
    m_count--;
    return (true);
}


//-----------------------------------------------------------------------------
void StringArray::Clear()
/**
 * \brief Clears the array and eventually reduces capacity.
 * Reduces capacity only if the current capacity is bigger than 64.
 **/
{
    // Shrinks the array if capacity is to big
    if (unlikely(m_capacity > 64)) {
        this->Alloc(64);
    }

    // Free allocated memory
    for (size_t i=0; i<m_count; ++i)
    {
        if (m_items[i] != NULL)
        {
            delete m_items[i];
            m_items[i] = NULL;
        }
    }

    // Empties array
    m_count = 0;
}


//-----------------------------------------------------------------------------
void StringArray::Shrink()
/**
 * \brief Shrinks the capacity to the number of strings in the array.
 **/
{
    this->Alloc(m_count);
}


//-----------------------------------------------------------------------------
void StringArray::Alloc(size_t capacity)
/**
 * \brief Allocates the array capacity, can extend or shrink the array.
 * \param capacity Capacity.
 **/
{
    if (unlikely(capacity < 4)) {
        capacity = 4;
    }
	if (likely(capacity > m_capacity))
	{
		// Extend array
		String** temp = new String*[capacity];
		temp = (String**)memcpy(temp, m_items, m_capacity*sizeof(String*));
		delete [] m_items;
		m_items = temp;
		m_capacity = capacity;
	}
	else
    {
		if (likely(capacity != m_capacity))
		{
            // Shrink array
            String** temp = new String*[capacity];
            memcpy(temp, m_items, capacity*sizeof(String*));
            for (size_t i=capacity; i<m_count; ++i)
            {
                if (m_items[i] != NULL) {
                    delete m_items[i];  // Free dropping objects
                }
            }
            delete [] m_items;
            m_items = temp;
            m_capacity = capacity;
            m_count = ((m_count < capacity) ? m_count:capacity);
		}
	}
}



//-----------------------------------------------------------------------------
StringArray* StringArray::Split(const String& strg, const String& separator, StringSplitOptions options)
/**
 * \brief Splits a string with the given separator by the given options.
 * Note: The returning string array must be destroyed by the caller.
 * \param strg The string which should be splitted.
 * \param separator The separator string.
 * \param options The split options.
 * \return String array with the splitted strings.
 **/
{
    StringArray* array = new StringArray();
    String split = _T("");

    for (size_t index=0; index<strg.Length(); ++index)
    {
        if (strg[index] == separator[0])
        {
            bool endString = true;
            for (size_t i=1; i<separator.Length(); ++i)
            {
                if (strg[index+i] != separator[i]) {
                    endString = false;
                    break;
                }
                if (separator.Length()-1 <= i) {
                    break;
                }
            }
            if (endString) {
                index += separator.Length()-1;
                if ((options & StringSplitOptions::Trim) == StringSplitOptions::Trim) {
                    split.Trim();
                }
                if ((options & StringSplitOptions::RemoveEmptyEntries) == StringSplitOptions::RemoveEmptyEntries) {
                    if (split.Length() > 0) array->Add(split);
                } else {
                    array->Add(split);
                }
                split.Clear();
            }
            else
            {
                split.Append(strg[index]);
            }
        }
        else
        {
            split.Append(strg[index]);
        }
    }

    if ((options & StringSplitOptions::Trim) == StringSplitOptions::Trim) {
        split.Trim();
    }
    if ((options & StringSplitOptions::RemoveEmptyEntries) == StringSplitOptions::RemoveEmptyEntries) {
        if (split.Length() > 0) array->Add(split);
    } else {
        array->Add(split);
    }

    array->Shrink();
    return (array);
}


} // namespace rush



