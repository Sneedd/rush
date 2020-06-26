/*
 * objectqueue.h - Declaration and implementation of the ObjectQueue template class
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2007-2012 - Steffen Ott
 *
 */


#ifndef _RUSH_OBJECTQUEUE_H_
#define _RUSH_OBJECTQUEUE_H_


#include <rush/config.h>
#include <rush/buildinexpect.h>

namespace rush {


/**
 * \brief The ObjectQueue template class is the implementation of a queue or fifo.
 **/
template <class Tvalue>
class ObjectQueue
{
    public:
        ObjectQueue();
        ObjectQueue(size_t capacity);
        virtual ~ObjectQueue();

        void Enqueue(Tvalue* value);
        Tvalue* Dequeue();
        Tvalue* First() const;
        bool IsEmpty() const;

        void Clear(bool free=true);
        void Alloc(size_t capacity);
        void Shrink();

        #ifdef _RUSH_DEBUG_
        Tvalue* ItemDebug(size_t index) const;
        inline size_t GetFrontIndex() const
        { return (m_frontindex); }
        inline size_t GetBackIndex() const
        { return (m_backindex); }
        #endif

        inline size_t Count() const
        { return (m_count); }

        inline size_t Capacity() const
        { return (m_capacity); }

    private:
        Tvalue** m_items;
        size_t m_count;
        size_t m_capacity;
        size_t m_frontindex;
        size_t m_backindex;
};



//-----------------------------------------------------------------------------
template <class Tvalue>
ObjectQueue<Tvalue>::ObjectQueue()
/**
 * \brief Standardconstructor, initializes the ObjectQueue object.
 * Initializes with the default capacity of 16.
 **/
{
    m_capacity = 16;
    m_items = new Tvalue*[m_capacity];
    m_count = 0;
    m_frontindex = 0;
    m_backindex = 0;
    memset(m_items, 0, m_capacity*sizeof(Tvalue*));
}


//-----------------------------------------------------------------------------
template <class Tvalue>
ObjectQueue<Tvalue>::ObjectQueue(size_t capacity)
/**
 * \brief Constructor, initializes the ObjectQueue object.
 * Initializes with the given capacity, but not lesser than 16.
 * \param capacity Capacity of the queue.
 **/
{
    if (capacity < 16) {
        capacity = 16;
    }
    m_capacity = capacity;
    m_items = new Tvalue*[m_capacity];
    m_count = 0;
    m_frontindex = 0;
    m_backindex = 0;
    memset(m_items, 0, m_capacity*sizeof(Tvalue*));
}


//-----------------------------------------------------------------------------
template <class Tvalue>
ObjectQueue<Tvalue>::~ObjectQueue()
/**
 * \brief Destructor, frees all allocated memory.
 **/
{
    if (m_items != NULL)
    {
        // NOTE : Use capacity and go through all elements
        for (size_t i=0; i<m_capacity; ++i)
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
template <class Tvalue>
void ObjectQueue<Tvalue>::Enqueue(Tvalue* value)
/**
 * \brief Enqeue the given element into the queue. All enqueued elements are
 * placed at the back of the queue.
 * \param value Element which should be enqueued.
 **/
{
    if (m_count >= m_capacity) {
        this->Alloc(m_capacity*2);
    }

    m_items[m_backindex] = value;
    m_backindex += 1;
    if (m_backindex >= m_capacity) m_backindex = 0;
    m_count++;
}


//-----------------------------------------------------------------------------
template <class Tvalue>
Tvalue* ObjectQueue<Tvalue>::Dequeue()
/**
 * \brief Dequeues the first element in the queue. Returns NULL if the queue is
 * empty.
 * \return First element in the queue or NULL.
 **/
{
    Tvalue* value = m_items[m_frontindex];
    m_items[m_frontindex] = NULL;
    m_frontindex += 1;
    if (m_frontindex >= m_capacity) m_frontindex = 0;
    m_count--;
    return (value);
}


//-----------------------------------------------------------------------------
template <class Tvalue>
Tvalue* ObjectQueue<Tvalue>::First() const
/**
 * \brief Returns the first element in the queue. Returns NULL if the queue is
 * empty.
 * \return First element in the queue or NULL.
 **/
{
    if (m_count != 0)
    {
        return (m_items[m_frontindex]);
    }
    return (NULL);
}


//-----------------------------------------------------------------------------
template <class Tvalue>
bool ObjectQueue<Tvalue>::IsEmpty() const
/**
 * \brief Checks if the queue is empty.
 * \return True, if the queue is empty; otherwise false.
 **/
{
    return (m_count == 0);
}


//-----------------------------------------------------------------------------
template <class Tvalue>
void ObjectQueue<Tvalue>::Clear(bool free)
/**
 * \brief Removes all elements from the queue. Frees the memory of the
 * elements if parameter is true.
 * \param free True, if element memory should be freed; otherwise false.
 **/
{
    for (size_t i=0; i<m_capacity; ++i)
    {
        if (m_items[i] != NULL && free)
        {
            delete m_items[i];
        }
        m_items[i] = NULL;
    }
    m_count = 0;
    m_frontindex = 0;
    m_backindex = 0;
}



//-----------------------------------------------------------------------------
template <class Tvalue>
void ObjectQueue<Tvalue>::Alloc(size_t capacity)
/**
 * \brief Allocates the given capacity. Can enlarge or shrink the queue.
 * \param capacity The new capacity.
 **/
{
    if (likely(capacity > m_capacity))
    {
        // Minimum capacity of the array
        if (unlikely(capacity < 16)) {
            capacity = 16;
        }

        // Extend array
        Tvalue** temp = new Tvalue*[capacity];
        memset(temp, 0, capacity*sizeof(Tvalue*));

        // Copy array
        size_t counter = m_frontindex;
        for (size_t i=0; i<m_capacity; ++i)
        {
            temp[i] = m_items[counter];
            counter += 1;
            if (counter >= m_capacity) counter = 0;
        }
        delete [] m_items;
        m_items = temp;
        m_capacity = capacity;
    }
    else
    {
        if (likely(m_capacity != capacity))
        {
            // Shrink array
            Tvalue** temp = new Tvalue*[capacity];
            memset(temp, 0, capacity*sizeof(Tvalue*));

            // Copy array
            size_t counter = m_frontindex;
            for (size_t i=0; i<capacity; ++i)
            {
                temp[i] = m_items[counter];
                counter += 1;
                if (counter >= m_capacity) counter = 0;
            }

            // Free dropping objects
            for (size_t i=capacity; i<m_count; ++i)
            {
                if (m_items[counter] != NULL)
                {
                    delete m_items[counter];
                }
                counter += 1;
                if (counter >= m_capacity) counter = 0;
            }

            delete [] m_items;
            m_items = temp;
            m_capacity = capacity;
            m_count = ((m_count < capacity) ? m_count:capacity);
        }
    }
    m_frontindex = 0;
    m_backindex = m_count;
}


//-----------------------------------------------------------------------------
template <class Tvalue>
void ObjectQueue<Tvalue>::Shrink()
/**
 * \brief Shrinks the queue.
 **/
{
    this->Alloc(m_count);
}



#ifdef _RUSH_DEBUG_
//-----------------------------------------------------------------------------
template <class Tvalue>
Tvalue* ObjectQueue<Tvalue>::ItemDebug(size_t index) const
/**
 * \brief
 **/
{
    return (m_items[index]);
}
#endif


} // namespace rush


#endif // _RUSH_QUEUE_H_



