/*
 * stringarray.h - Declaration of the StringArray class
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2011-2012 - Steffen Ott
 *
 */



#ifndef _RUSH_STRINGARRAY_H_
#define _RUSH_STRINGARRAY_H_

#include <rush/config.h>
#include <rush/string.h>


namespace rush {


/**
 * \brief The StringSplitOptions enum defines Options for the StringArray::Split
 * Method. This enum conatains flags.
 **/
enum class StringSplitOptions
{
    None = 0x00,
    Trim = 0x01,
    RemoveEmptyEntries = 0x02
};



/**
 * \brief
 **/
inline StringSplitOptions operator|(StringSplitOptions a, StringSplitOptions b)
{
    return (static_cast<StringSplitOptions>(static_cast<int>(a) | static_cast<int>(b)));
}

/**
 * \brief
 **/
inline StringSplitOptions operator&(StringSplitOptions a, StringSplitOptions b)
{
    return (static_cast<StringSplitOptions>(static_cast<int>(a) & static_cast<int>(b)));
}


/**
 * \brief The StringArray class is an array which contains strings.
 * This container has some special methods to handle strings.
 * \code {.cpp}
 * // The resulting string array will contain "1", "2" and "3".
 * StringArray* array = StringArray::Split(_T("1,2,3"), _T(","));
 * \endcode
 **/
class StringArray
{
    public:
        StringArray();
        StringArray(size_t capacity);
        StringArray(const StringArray& array);
        ~StringArray();

        StringArray& operator=(const StringArray& array);
        String& operator[](size_t index);
        const String& operator[](size_t index) const;

        String& Item(size_t index);
        const String& Item(size_t index) const;

        int IndexOf(const String& strg) const;

        StringArray& Add(const String& strg);
        StringArray& AddFormat(const String& format, ...);
        bool Insert(size_t index, const String& strg);
		bool Remove(size_t index);
        void Clear();

		void Shrink();
		void Alloc(size_t capacity);

        /**
         * \brief Counts the strings in this array.
         * \return Number of strings in this array.
         **/
        inline size_t Count() const
        { return (m_count); }

        /**
         * \brief Capacity of this array.
         * \return Capacity.
         **/
        inline size_t Capacity() const
        { return (m_capacity); }

    public:
        static StringArray* Split(const String& strg, const String& separator,
            StringSplitOptions options = StringSplitOptions::Trim | StringSplitOptions::RemoveEmptyEntries);

    private:
        String** m_items;
        size_t m_count;
        size_t m_capacity;
};


} // namespace rush


#endif // _RUSH_STRINGARRAY_H_

