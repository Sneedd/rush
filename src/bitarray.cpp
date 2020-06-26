/*
 * bitarray.cpp - Implementation of the BitArray class
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2011-2012 - Steffen Ott
 *
 */

#include <rush/bitarray.h>
#include <rush/buildinexpect.h>

namespace rush {


//-----------------------------------------------------------------------------
BitArray::BitArray()
/**
 * \brief Standartconstruktor, initializes the BitArray object.
 **/
{
    m_array = 0;
}


//-----------------------------------------------------------------------------
BitArray::BitArray(unsigned int array)
/**
 * \brief Construktor, initializes the BitArray object.
 * Setzt alle Bitwerte wie bei dem übergeben Uint32.
 **/
{
    m_array = array;
}


//-----------------------------------------------------------------------------
BitArray::~BitArray()
/**
 * \brief Destructor. Frees allocated memory.
 **/
{
}



//-----------------------------------------------------------------------------
BitArray& BitArray::operator=(const BitArray& array)
/**
 * \brief Assignment operator, copies the given array into this array.
 * \param array Array.
 * \return This array.
 **/
{
    m_array = array.m_array;
    return (*this);
}


//-----------------------------------------------------------------------------
bool BitArray::operator[](size_t index)
/**
 * \brief Accessoperator, accesses single bits of the array.
 * \param index Index.
 * \return True, if the bit at the index is set; otherwise false.
 **/
{
    if (likely(index >= 0 && index < 32))
    {
        return ((m_array>>index)&1);
    }
    return (false);
}


//-----------------------------------------------------------------------------
const bool BitArray::operator[](size_t index) const
/**
 * \brief Accessoperator, accesses single bits of the array.
 * \param index Index.
 * \return True, if the bit at the index is set; otherwise false.
 **/
{
    if (likely(index >= 0 && index < 32))
    {
        return ((m_array>>index)&1);
    }
    return (false);
}


//-----------------------------------------------------------------------------
bool BitArray::operator==(const BitArray& array)
/**
 * \brief Equal comparison operator, tests if the bitarrays are equal.
 * \param array BitArray.
 * \return True, if the bitarrays are equal; otherwise false.
 **/
{
    return (m_array == array.m_array);
}


//-----------------------------------------------------------------------------
bool BitArray::operator!=(const BitArray& array)
/**
 * \brief Not equal comparison operator, tests if the bitarrays are not equal.
 * \param array BitArray.
 * \return True, if the bitarrays are not equal; otherwise false.
 **/
{
    return (m_array != array.m_array);
}


//-----------------------------------------------------------------------------
bool BitArray::GetBit(size_t index) const
/**
 * \brief Returns a bits from the array.
 * \param index Index.
 * \return True, if the bit at the index is set; otherwise false.
 **/
{
    if (likely(index >= 0 && index < 32))
    {
        return ((m_array>>index)&1);
    }
    return (false);
}


//-----------------------------------------------------------------------------
void BitArray::SetBit(size_t index, bool bit)
/**
 * \brief Sets the bit at the given index.
 * \param index Index.
 * \param bit Bit value.
 **/
{
    if (likely(index >= 0 && index < 32))
    {
        bool flag = (m_array >> index) == 1;
        if (!flag && bit)
        {
            m_array |= (1<<index);
        }
        else if (flag && !bit)
        {
            m_array ^= (1<<index);
        }
    }
}


//-----------------------------------------------------------------------------
void BitArray::ClearBit(size_t index)
/**
 * \brief Clears the bit at the given index.
 * \param index Index.
 **/
{
    if (likely(index >= 0 && index < 32))
    {
        if ((m_array >> index) == 1)
        {
            m_array ^= (1<<index);
        }
    }
}


//-----------------------------------------------------------------------------
void BitArray::ToggleBit(size_t index)
/**
 * \brief Toogles the bit at the given index.
 * \param index Index.
 **/
{
    if (likely(index >= 0 && index < 32))
    {
        if ((m_array >> index) == 1)
        {
            m_array |= (1<<index);
        }
        else
        {
            m_array ^= (1<<index);
        }
    }
}



} // namespace rush


