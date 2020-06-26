/*
 * bitarray.h - Declaration of the BitArray class
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2011-2012 - Steffen Ott
 *
 */


#ifndef _RUSH_BINARYARRAY_H_
#define _RUSH_BINARYARRAY_H_

#include <rush/config.h>
#include <string.h>

namespace rush {


/**
 * \brief The BitArray class conatins a unsigned int which will be used
 * as a 32-bit array.
 **/
class BitArray
{
	public:
        BitArray();
        BitArray(unsigned int array);
        BitArray(const BitArray& array);
        ~BitArray();

        BitArray& operator=(const BitArray& array);

        bool operator[](size_t index);
        const bool operator[](size_t index) const;

        bool operator==(const BitArray& array);
        bool operator!=(const BitArray& array);

        bool GetBit(size_t index) const;
        void SetBit(size_t index, bool bit);
        void ClearBit(size_t index);
        void ToggleBit(size_t index);

    private:
        unsigned int m_array;
};



} // namespace rush

#endif // _RUSH_BINARYARRAY_H_


