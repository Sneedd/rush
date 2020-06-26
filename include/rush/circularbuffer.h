/*
 * circularbuffer.h - Deklaration and implementation of the CircularBuffer class
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2011-2012 - Steffen Ott
 *
 */


#ifndef _RUSH_CIRCULARBUFFER_H_
#define _RUSH_CIRCULARBUFFER_H_


namespace rush {


/**
 * \brief The CircluarBuffer class is the implementation of a circular buffer.
 * The buffer is internal implementated as an array for pointers. The buffer
 * overrides a existing values, if the buffer is full(can be tested with IsFull()).
 **/
template <typename Tvalue>
class CircularBuffer
{
    public:
        CircularBuffer();
        CircularBuffer(size_t size);
        virtual ~CircularBuffer();

        bool IsEmpty() const;
        bool IsFull() const;
        size_t Count() const;

        void Enqueue(Tvalue* item);
        Tvalue* Dequeue();
        void Clear(bool free = true);

    private:
        Tvalue** m_items;
        size_t m_count;
        size_t m_maxsize;
        size_t m_startindex;
        size_t m_endindex;
};


//-----------------------------------------------------------------------------
template <typename Tvalue>
CircularBuffer<Tvalue>::CircularBuffer()
/**
 * \brief Standardconstructor, initializes the CirularBuffer object.
 * The buffer size will be set to 128 entries.
 **/
{
    m_maxsize = 128;
    m_count = 0;
    m_items = new Tvalue*[m_maxsize];
    m_startindex = 0;
    m_endindex = 0;
}

//-----------------------------------------------------------------------------
template <typename Tvalue>
CircularBuffer<Tvalue>::CircularBuffer(size_t size)
/**
 * \brief Constructor, initializes the CirularBuffer object.
 * \param size The size of the buffer.
 **/
{
    if (size == 0) size = 128;
    m_maxsize = size;
    m_count = 0;
    m_items = new Tvalue*[m_maxsize];
    m_startindex = 0;
    m_endindex = 0;
}

//-----------------------------------------------------------------------------
template <typename Tvalue>
CircularBuffer<Tvalue>::~CircularBuffer()
/**
 * \brief Destructor, frees all allocated memory.
 **/
{
    this->Clear(true);
    if (m_items != NULL)
    {
        delete [] m_items;
    }
}

//-----------------------------------------------------------------------------
template <typename Tvalue>
bool CircularBuffer<Tvalue>::IsEmpty() const
/**
 * \brief Returns true, if the buffer does not contain any elements;
 * or false, if at least one element exists in the buffer.
 * \return True if the buffer is empty; otherwise false.
 **/
{
    return (m_count == 0);
}

//-----------------------------------------------------------------------------
template <typename Tvalue>
bool CircularBuffer<Tvalue>::IsFull() const
/**
 * \brief Returns true, if the buffer is full; otherwise false.
 * \return True, if the buffer is full; otherwise false.
 **/
{
    return (m_count == m_maxsize);
}

//-----------------------------------------------------------------------------
template <typename Tvalue>
size_t CircularBuffer<Tvalue>::Count() const
/**
 * \brief Counts the number of elements in the buffer.
 * \return Number of elements in the buffer.
 **/
{
    return (m_count);
}

//-----------------------------------------------------------------------------
template <typename Tvalue>
bool CircularBuffer<Tvalue>::Enqueue(Tvalue* item)
/**
 * \brief Adds an element to the end of the circular buffer. Overrides the
 * last element if the buffer it is full.
 * \param item Element which should be enqueued to the buffer.
 * \return True if the element was successfully enqueued; or false, if
 * the element overrides a existing element.
 **/
{
    size_t endIndex = (m_startindex + m_count) % m_maxsize;
    m_items[endIndex] = item;
    if (m_count == m_maxsize)
    {
        // Circular buffer is full -> override
        m_startindex = (m_startindex + 1) % m_maxsize;
        return (false);
    }
    else
    {
        m_count++;
    }
    return (true);
}

//-----------------------------------------------------------------------------
template <typename Tvalue>
Tvalue* CircularBuffer<Tvalue>::Dequeue()
/**
 * \brief Removes an element from the start of the circular buffer.
 * Returns NULL if the there are no elements in the buffer.
 * \return Returns the first element in the buffer or NULL.
 **/
{
    Tvalue* value = NULL;
    if (m_count != 0) {
        value = m_items[m_startindex];
        m_items[m_startindex] = NULL;
        m_startindex = (m_startindex + 1) % m_maxsize;
        m_count--;
    }
    return (value);
}


//-----------------------------------------------------------------------------
template <typename Tvalue>
void CircularBuffer<Tvalue>::Clear(bool free)
/**
 * \brief Removes all elements from the buffer.
 * \param free True, if the removing elements should be deleted;
 * otherwise false.
 **/
{
    if (free)
    {
        for (size_t i=0; i<m_maxsize; ++i)
        {
            if (m_items[i] != NULL)
            {
                delete m_items[i];
                m_items[i] = NULL;
            }
        }
    }
    else
    {
        for (size_t i=0; i<m_maxsize; ++i)
        {
            m_items[i] = NULL;
        }
    }
}



} // namespace rush

#endif // _RUSH_CIRCULARBUFFER_H_
