/*
 * objectstack.h - Declaration and implementation of the ObjectStack template class
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2011-2012 - Steffen Ott
 *
 */


#ifndef _RUSH_OBJECTSTACK_H_
#define _RUSH_OBJECTSTACK_H_

#include <rush/config.h>


namespace rush {


/**
 * \brief The ObjectStack template class implements the container stack or LIFO for objects.
 **/
template <class Tvalue>
class ObjectStack
{
    private:
        ObjectStack(const ObjectStack& stack) {}
        ObjectStack& operator=(const ObjectStack& stack) { return (*this); }
    public:
        ObjectStack();
        ObjectStack(size_t capacity);
        virtual ~ObjectStack();

        void Push(Tvalue* value);
        Tvalue* Pop();
        Tvalue* Peek() const;

        void Clear(bool free = true);

        void Alloc(size_t capacity);

        #ifdef _RUSH_DEBUG_
        Tvalue* ItemDebug(size_t index) const;
        #endif

        /**
         * \brief Counts the number of objects in this stack.
         * \return Number of objects in this stack.
         **/
        inline size_t Count() const
        { return (m_count); }

    private:
        Tvalue** m_array;
        size_t m_count;
        size_t m_capacity;
};



//-----------------------------------------------------------------------------
template <class Tvalue>
ObjectStack<Tvalue>::ObjectStack()
/**
 * \brief Standardconstructor, initializes the ObjectStack object.
 **/
{
    m_capacity = 16;
    m_count = 0;
    m_array = new Tvalue*[m_capacity];
}


//-----------------------------------------------------------------------------
template <class Tvalue>
ObjectStack<Tvalue>::ObjectStack(size_t capacity)
/**
 * \brief Constructor, initializes the ObjectStack object.
 * \param capacity
 **/
{
    if (capacity < 16) {
        capacity = 16;
    }
    m_capacity = capacity;
    m_count = 0;
    m_array = new Tvalue*[m_capacity];
}


//-----------------------------------------------------------------------------
template <class Tvalue>
ObjectStack<Tvalue>::~ObjectStack()
/**
 * \brief Destructor, frees the allocated memory.
 **/
{
    if (m_array != NULL)
    {
        for (size_t i=0; i<m_count; ++i)
        {
            if (m_array[i] != NULL)
            {
                delete m_array[i];
            }
        }
        delete [] m_array;
    }
}


//-----------------------------------------------------------------------------
template <class Tvalue>
void ObjectStack<Tvalue>::Push(Tvalue* value)
/**
 * \brief Pushes a element onto the stack.
 * \param value Element to push onto the stack.
 **/
{
    if (unlikely(m_count >= m_capacity))
    {
        this->Alloc(m_capacity*2);
    }

    m_array[m_count] = value;
    m_count += 1;
}


//-----------------------------------------------------------------------------
template <class Tvalue>
Tvalue* ObjectStack<Tvalue>::Pop()
/**
 * \brief Pops the first element in the stack. Removes the object from the stack
 * and returns it. The object must be destroyd by the user.
 * \return First element in the stack.
 **/
{
    if (unlikely(m_count <= 0))
    {
        return (NULL);
    }

    m_count -= 1;
    Tvalue* value = m_array[m_count];
    m_array[m_count] = NULL;
    return (value);
}


//-----------------------------------------------------------------------------
template <class Tvalue>
Tvalue* ObjectStack<Tvalue>::Peek() const
/**
 * \brief Peeks the first element in the stack.
 **/
{
    return (m_array[m_count-1]);
}


//-----------------------------------------------------------------------------
template <class Tvalue>
void ObjectStack<Tvalue>::Clear(bool free)
/**
 * \brief Removes all elements from the stack.
 * \param free True, if memory of the objects in the stack should
 * be freed; otherwise false.
 **/
{
    for (size_t i=0; i<m_count; ++i)
    {
        if (m_array[i] != NULL && free)
        {
            delete m_array[i];
        }
        m_array[i] = NULL;
    }
    m_count = 0;
}


//-----------------------------------------------------------------------------
template <class Tvalue>
void ObjectStack<Tvalue>::Alloc(size_t capacity)
/**
 * \brief Allocates the given amount of elements to the stack.
 * Enlarges or shinks the array which contains the stack elements.
 * If the stack capacity shinks the dropped element will be freed.
 * \param capacity Capacity of element in the stack.
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
        memcpy(temp, m_array, m_capacity*sizeof(Tvalue*));
        delete [] m_array;
        m_array = temp;
        m_capacity = capacity;
    }
    else
    {
        if (likely(m_capacity != capacity))
        {
            // Shrink array
            Tvalue** temp = new Tvalue*[capacity];
            memcpy(temp, m_array, capacity*sizeof(Tvalue*));
            for (size_t i=capacity; i<m_count; ++i)
            {
                if (m_array[i] != NULL) {
                    delete m_array[i];  // Free dropping objects
                }
            }
            delete [] m_array;
            m_array = temp;
            m_capacity = capacity;
            m_count = ((m_count < capacity) ? m_count:capacity);
        }
    }
}


#ifdef _RUSH_DEBUG_
//-----------------------------------------------------------------------------
template <class Tvalue>
Tvalue* ObjectStack<Tvalue>::ItemDebug(size_t index) const
/**
 * \brief Returns a item without index testing.
 * Does not remove the element. Only for debugging purposes.
 * \param index Index of element in stack.
 * \return Element in stack.
 **/
{
    return (m_array[index]);
}
#endif



} // namespace rush


#endif // _RUSH_OBJECTSTACK_H_



