/*
 * array.h - Declaration of the Array template class.
 *
 * This file is parto of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2010-2012 - Steffen Ott
 *
 */



#ifndef _RUSH_ARRAY_H_
#define _RUSH_ARRAY_H_

#include <rush/config.h>
#include <rush/buildinexpect.h>
#include <rush/log.h>
#include <string.h> // für memcpy(), ...



namespace rush {


/**
 * \brief The Array class template is a spezialized array for primitive data types.
 * Primitive data types are int, float, bool, rush::String and others.
 **/
template <typename Tvalue>
class Array
{
    public:
        Array();
        Array(size_t capacity);
        Array(const Array& array);
        virtual ~Array();

        Array& operator=(const Array& array);
        Tvalue& operator[](size_t index);
        const Tvalue& operator[](size_t index) const;

        Tvalue& Item(size_t index);

		void Add(Tvalue value);
		bool Insert(size_t index, Tvalue value);
		bool Remove(size_t index);

		void Shrink();
		void Alloc(size_t capacity);
		void Clear();

		void SetAll(Tvalue value);

        inline size_t Count() const
        { return (m_count); }

		inline size_t Capacity() const
		{ return (m_capacity); }


    protected:
        Tvalue* m_items;
        size_t m_count;
        size_t m_capacity;
};


//-----------------------------------------------------------------------------
template <typename Tvalue>
Array<Tvalue>::Array()
/**
 * \brief
 **/
{
    m_capacity = 64;
    m_count = 0;
    m_items = new Tvalue[m_capacity];
}


//-----------------------------------------------------------------------------
template <typename Tvalue>
Array<Tvalue>::Array(size_t capacity)
/**
 * \brief
 **/
{
    if (unlikely(capacity < 16)) {
        capacity = 16;
    }
    m_capacity = capacity;
    m_count = 0;
    m_items = new Tvalue[m_capacity];
}


//-----------------------------------------------------------------------------
template <typename Tvalue>
Array<Tvalue>::Array(const Array& array)
/**
 * \brief Copyconstructor, intializes this class with the copy of the given class.
 * Copies the array exact, meaning there will no capacity left (Count == Capacity).
 **/
{
    m_capacity = array.m_count;
    m_count = array.m_count;
    m_items = new Tvalue[m_capacity];
    m_items = memcpy(m_items, array.m_items, sizeof(Tvalue)*m_capacity);
}


//-----------------------------------------------------------------------------
template <typename Tvalue>
Array<Tvalue>::~Array()
/**
 * \brief Destructor, frees all allocated memory.
 **/
{
    if (likely(m_items != NULL))
    {
        delete [] m_items;
    }
}


//-----------------------------------------------------------------------------
template <typename Tvalue>
Array<Tvalue>& Array<Tvalue>::operator=(const Array<Tvalue>& array)
/**
 * \brief Assignment operator, copies the given class into this.
 * Copies the array exact, meaning there will no capacity left (Count == Capacity).
 **/
{
    if (likely(m_items != NULL))
    {
        delete [] m_items;
    }
    m_capacity = array.m_count;
    m_count = array.m_count;
    m_items = new Tvalue[m_capacity];
    m_items = memcpy(m_items, array.m_items, sizeof(Tvalue)*m_capacity);

    return (*this);
}


//-----------------------------------------------------------------------------
template <typename Tvalue>
Tvalue& Array<Tvalue>::operator[](size_t index)
/**
 * \brief
 **/
{
    if (unlikely(index >= m_count))
    {
        Log::Error(_T("[Array::operator[]] Index out of range."));
        return (m_items[0]);
    }
    return (m_items[index]);
}


//-----------------------------------------------------------------------------
template <typename Tvalue>
const Tvalue& Array<Tvalue>::operator[](size_t index) const
/**
 * \brief
 **/
{
    if (unlikely(index >= m_count))
    {
        Log::Error(_T("[Array::operator[]] Index out of range."));
        return (Tvalue());
    }
    return (m_items[index]);
}


//-----------------------------------------------------------------------------
template <typename Tvalue>
Tvalue& Array<Tvalue>::Item(size_t index)
/**
 * \brief
 **/
{
    if (unlikely(index >= m_count))
    {
        Log::Error(_T("[Array::operator[]] Index out of range."));
        return (Tvalue());
    }
    return (m_items[index]);
}


//-----------------------------------------------------------------------------
template <typename Tvalue>
void Array<Tvalue>::Add(Tvalue value)
/**
 * \brief
 **/
{
    if (unlikely(m_count >= m_capacity))
    {
		this->Alloc(m_capacity*2);
	}
	m_items[m_count] = value;
	m_count++;
}


//-----------------------------------------------------------------------------
template <typename Tvalue>
bool Array<Tvalue>::Insert(size_t index, Tvalue value)
/**
 * \brief
 **/
{
    if (unlikely(index > m_count))
    {
        Log::Error(_T("[Array::Insert] Index out of range."));
        return (false);
    }
    if (unlikely(index == m_count))
    {
        this->Add(value);
        return (true);
    }
    if (unlikely(m_capacity <= m_count))
    {
        this->Alloc(m_capacity*2);
    }

    memmove(m_items+index+1, m_items+index, (m_count-index)*sizeof(Tvalue));
    m_items[index] = value;
	m_count++;
    return (true);
}


//-----------------------------------------------------------------------------
template <typename Tvalue>
bool Array<Tvalue>::Remove(size_t index)
/**
 * \brief
 **/
{
    if (unlikely(index >= m_count))
    {
        Log::Error(_T("[Array::Remove] Index out of range."));
        return (false);
    }

    memmove(m_items+index, m_items+index+1, (m_count-index)*sizeof(Tvalue));
    m_count--;
    return (true);
}


//-----------------------------------------------------------------------------
template <typename Tvalue>
void Array<Tvalue>::Shrink()
/**
 * \brief
 **/
{
    this->Alloc(m_count);
}


//-----------------------------------------------------------------------------
template <typename Tvalue>
void Array<Tvalue>::Alloc(size_t capacity)
/**
 * \brief
 **/
{
    if (unlikely(capacity < 4)) {
        capacity = 4;
    }
	if (likely(capacity > m_capacity))
	{
		// Extend array
		Tvalue* temp = new Tvalue[capacity];
		temp = (Tvalue*)memcpy(temp, m_items, m_capacity*sizeof(Tvalue));
		delete [] m_items;
		m_items = temp;
		m_capacity = capacity;
	}
	else
    {
        // Shrink array
		if (likely(capacity != m_capacity))
		{
            // Array verkleinern und rest Daten kopieren
            Tvalue* temp = new Tvalue[capacity];
            temp = (Tvalue*)memcpy((void*)temp,(void*)m_items,capacity*sizeof(Tvalue));
            delete [] m_items;
            m_items = temp;
            m_capacity = capacity;
            m_count = ((m_count < capacity) ? (m_count):(capacity)); // Min()
		}
	}
}


//-----------------------------------------------------------------------------
template <typename Tvalue>
void Array<Tvalue>::Clear()
/**
 * \brief Clears the array and eventually reduces capacity.
 * Reduces capacity only if the current capacity is bigger than 64.
 **/
{
    // Shrinks the array if capacity is to big
    if (unlikely(m_capacity > 64)) {
        this->Alloc(64);
    }

    // Empties array
    m_count = 0;
}


//-----------------------------------------------------------------------------
template <typename Tvalue>
void Array<Tvalue>::SetAll(Tvalue value)
/**
 * \brief Sets all values in this array at once.
 **/
{
    for (size_t i=0; i<m_count; ++i)
    {
        m_items[i] = value;
    }
}



} // namespace rush


#endif // _RUSH_ARRAY_H_
