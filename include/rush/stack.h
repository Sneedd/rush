/*
 * stack.h - Declaration and implementation of the Stack template class
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2011-2012 - Steffen Ott
 *
 */


#ifndef _RUSH_STACK_H_
#define _RUSH_STACK_H_


#include <rush/config.h>



namespace rush {


/**
 * \brief The Stack template class implements the container stack or LIFO
 * for primitive types.
 **/
template <typename Tvalue>
class Stack
{
    private:
        Stack(const Stack& stack) {}
        Stack& operator=(const Stack& stack) { return (*this); }
    public:
        Stack();
        Stack(size_t capacity);
        virtual ~Stack();

        void Push(Tvalue value);
        Tvalue Pop();
        Tvalue Peek() const;

        void Clear();

        void Alloc(size_t capacity);

        #ifdef _RUSH_DEBUG_
        Tvalue ItemDebug(size_t index) const;
        #endif

        /**
         * \brief Counts the number of objects in this stack.
         * \return Number of objects in this stack.
         **/
        inline size_t Count() const
        { return (m_count); }

    private:
        Tvalue* m_array;
        size_t m_count;
        size_t m_capacity;
};



//-----------------------------------------------------------------------------
template <typename Tvalue>
Stack<Tvalue>::Stack()
/**
 * \brief Standardconstructor, initializes the Stack object.
 **/
{
    m_capacity = 16;
    m_count = 0;
    m_array = new Tvalue[m_capacity];
}


//-----------------------------------------------------------------------------
template <typename Tvalue>
Stack<Tvalue>::Stack(size_t capacity)
/**
 * \brief Constructor, initializes the Stack object.
 * \param capacity
 **/
{
    if (capacity < 16) {
        capacity = 16;
    }
    m_capacity = capacity;
    m_count = 0;
    m_array = new Tvalue[m_capacity];
}


//-----------------------------------------------------------------------------
template <typename Tvalue>
Stack<Tvalue>::~Stack()
/**
 * \brief Destructor, frees the allocated memory.
 **/
{
    if (m_array != NULL)
    {
        delete [] m_array;
    }
}


//-----------------------------------------------------------------------------
template <typename Tvalue>
void Stack<Tvalue>::Push(Tvalue value)
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
template <typename Tvalue>
Tvalue Stack<Tvalue>::Pop()
/**
 * \brief Pops the first element in the stack. Removes the object from the stack
 * and returns it. The object must be destroyd by the user.
 * \return First element in the stack.
 **/
{
    if (unlikely(m_count <= 0))
    {
        return (Tvalue());
    }

    m_count -= 1;
    Tvalue value = m_array[m_count];
    return (value);
}


//-----------------------------------------------------------------------------
template <typename Tvalue>
Tvalue Stack<Tvalue>::Peek() const
/**
 * \brief Peeks the first element in the stack.
 **/
{
    if (unlikely(m_count <= 0))
    {
        return (Tvalue());
    }
    return (m_array[m_count-1]);
}


//-----------------------------------------------------------------------------
template <typename Tvalue>
void Stack<Tvalue>::Clear()
/**
 * \brief Removes all elements from the stack.
 **/
{
    m_count = 0;
}


//-----------------------------------------------------------------------------
template <typename Tvalue>
void Stack<Tvalue>::Alloc(size_t capacity)
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
        Tvalue* temp = new Tvalue[capacity];
        memcpy(temp, m_array, m_capacity*sizeof(Tvalue));
        delete [] m_array;
        m_array = temp;
        m_capacity = capacity;
    }
    else
    {
        if (likely(m_capacity != capacity))
        {
            // Shrink array
            Tvalue* temp = new Tvalue[capacity];
            memcpy(temp, m_array, capacity*sizeof(Tvalue));
            delete [] m_array;
            m_array = temp;
            m_capacity = capacity;
            m_count = ((m_count < capacity) ? m_count:capacity);
        }
    }
}


#ifdef _RUSH_DEBUG_
//-----------------------------------------------------------------------------
template <typename Tvalue>
Tvalue Stack<Tvalue>::ItemDebug(size_t index) const
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


#endif // _RUSH_STACK_H_




