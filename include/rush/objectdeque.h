/*
 * objectdeque.h - Declaration and implementation of the ObjectDeque template class
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2007-2012 - Steffen Ott
 *
 */


#ifndef _RUSH_OBJECTDEQUE_H_
#define _RUSH_OBJECTDEQUE_H_


#include <rush/config.h>


namespace rush {

/**
 * \brief The ObjectDequeNode template class represents a node in the ObjectDeque class.
 * Because the ObjectDeque is implemented as double linked list this node contains a next
 * and previous pointer to their nearby nodes. This class should not be used directly.
 **/
template <class Tvalue>
class ObjectDequeNode
{
    private:
        template <class> friend class ObjectDeque;
        ObjectDequeNode();
        ObjectDequeNode(ObjectDequeNode* next, ObjectDequeNode* prev = NULL, Tvalue* value = NULL);
        ~ObjectDequeNode();

        inline void SetNext(ObjectDequeNode* next)
        { m_next = next; }

        inline void SetPrev(ObjectDequeNode* prev)
        { m_prev = prev; }

        inline void SetValue(Tvalue* value)
        { m_value = value; }

    public:
        inline ObjectDequeNode* GetNext() const
        { return (m_next); }

        inline ObjectDequeNode* GetPrev() const
        { return (m_prev); }

        inline Tvalue* GetValue() const
        { return (m_value); }

    private:
        ObjectDequeNode* m_next;
        ObjectDequeNode* m_prev;
        Tvalue* m_value;
};


/**
 * \brief The ObjectDeque template class implements double ended queue, which is the
 * combination of a stack and a queue. The naming convention named the methods like
 * they are used in the single stack or queue classes. The implementation is
 * internally as a double linked list.
 **/
template <class Tvalue>
class ObjectDeque
{
    public:
        ObjectDeque();
        virtual ~ObjectDeque();

        void Push(Tvalue* value);
        void PushFront(Tvalue* value);
        Tvalue* Pop();
        Tvalue* Peek() const;

        void Enqueue(Tvalue* value);
        Tvalue* Dequeue();
        Tvalue* First() const;

        void Clear(bool free = true);

        #ifdef _RUSH_DEBUG_
        const ObjectDequeNode<Tvalue>* GetHead() const;
        const ObjectDequeNode<Tvalue>* GetTail() const;
        #endif

        /**
         * \brief Checks if the Deque is empty.
         * \return True, if the Deque is empty; otherwise false.
         **/
        inline bool IsEmpty() const
        { return (m_count == 0); }

        /**
         * \brief Counts the elements in this Deque.
         * \return Number of elements.
         **/
        inline size_t Count() const
        { return (m_count); }

    private:
        ObjectDequeNode<Tvalue>* m_head;
        ObjectDequeNode<Tvalue>* m_tail;
        size_t m_count;
};


//----------------------------------------------------------------
template <class Tvalue>
ObjectDequeNode<Tvalue>::ObjectDequeNode()
{
    m_next = NULL;
    m_prev = NULL;
    m_value = NULL;
}


//----------------------------------------------------------------
template <class Tvalue>
ObjectDequeNode<Tvalue>::ObjectDequeNode(ObjectDequeNode* next, ObjectDequeNode* prev, Tvalue* value)
{
    m_next = next;
    m_prev = prev;
    m_value = value;
}


//----------------------------------------------------------------
template <class Tvalue>
ObjectDequeNode<Tvalue>::~ObjectDequeNode()
{
    if (m_value != NULL)
    {
        delete m_value;
    }
}


//----------------------------------------------------------------
template <class Tvalue>
ObjectDeque<Tvalue>::ObjectDeque()
/**
 * \brief Standardconstructor, initializes the ObjectDeque object.
 **/
{
    m_head = NULL;
    m_tail = NULL;
    m_count = 0;
}


//----------------------------------------------------------------
template <class Tvalue>
ObjectDeque<Tvalue>::~ObjectDeque()
/**
 * \brief Destructor, frees all memory.
 **/
{
    ObjectDequeNode<Tvalue>* temp = m_head;
    while (temp != NULL)
    {
        ObjectDequeNode<Tvalue>* node = temp;
        temp = temp->GetNext();
        delete node;
    }
}


//----------------------------------------------------------------
template <class Tvalue>
void ObjectDeque<Tvalue>::Push(Tvalue* value)
/**
 * \brief Pushes the value at the end of the deque.
 * \param value Value
 **/
{
    ObjectDequeNode<Tvalue>* node = new ObjectDequeNode<Tvalue>();
    node->SetNext(NULL);
    node->SetPrev(m_tail);
    node->SetValue(value);

    if (m_tail == NULL)
    {
        m_head = node;
        m_tail = node;
    }
    else
    {
        m_tail->SetNext(node);
        m_tail = node;
    }
    m_count++;
}

//----------------------------------------------------------------
template <class Tvalue>
void ObjectDeque<Tvalue>::PushFront(Tvalue* value)
/**
 * \brief Pushes the value at the front of the deque.
 * \param value Value
 **/
{
    ObjectDequeNode<Tvalue>* node = new ObjectDequeNode<Tvalue>();
    node->SetNext(m_head);
    node->SetPrev(NULL);
    node->SetValue(value);

    if (m_head == NULL)
    {
        m_head = node;
        m_tail = node;
    }
    else
    {
        m_head->SetPrev(node);
        m_head = node;
    }
    m_count++;
}



//----------------------------------------------------------------
template <class Tvalue>
Tvalue* ObjectDeque<Tvalue>::Pop()
/**
 * \brief Pops the value from the end of the deque. Removes the
 * value from the deque.
 * \return Returns the value or NULL if the deque is empty.
 **/
{
    if (m_tail == NULL)
    {
        return (NULL);
    }

    ObjectDequeNode<Tvalue>* node = m_tail;
    if (m_tail == m_head)
    {
        m_tail = NULL;
        m_head = NULL;
    }
    else
    {
        m_tail = m_tail->GetPrev();
        m_tail->SetNext(NULL);
    }

    Tvalue* value = node->GetValue();
    node->SetValue(NULL);
    delete node;
    m_count--;
    return (value);
}


//----------------------------------------------------------------
template <class Tvalue>
Tvalue* ObjectDeque<Tvalue>::Peek() const
/**
 * \brief Returns the value from the end of the deque. Does not
 * remove the value from the deque.
 * \return Returns the value or NULL if the deque is empty.
 **/
{
    if (m_tail == NULL)
    {
        return (NULL);
    }
    return (m_tail->GetValue());
}


//----------------------------------------------------------------
template <class Tvalue>
void ObjectDeque<Tvalue>::Enqueue(Tvalue* value)
/**
 * \brief Equeues the value at the end of the deque.
 * \param value Value
 **/
{
    this->Push(value);
}


//----------------------------------------------------------------
template <class Tvalue>
Tvalue* ObjectDeque<Tvalue>::Dequeue()
/**
 * \brief Dequeues the value from the front of the deque. Removes the
 * value from the deque.
 * \return Returns the value or NULL if the deque is empty.
 **/
{
    if (m_head == NULL)
    {
        return (NULL);
    }

    ObjectDequeNode<Tvalue>* node = m_head;
    if (m_head == m_tail)
    {
        m_head = NULL;
        m_tail = NULL;
    }
    else
    {
        m_head = m_head->GetNext();
        m_head->SetPrev(NULL);
    }

    Tvalue* value = node->GetValue();
    node->SetValue(NULL);
    delete node;
    m_count--;
    return (value);
}


//----------------------------------------------------------------
template <class Tvalue>
Tvalue* ObjectDeque<Tvalue>::First() const
/**
 * \brief Returns the value from the front of the deque. Does not
 * remove the value from the deque.
 * \return Returns the value or NULL if the deque is empty.
 **/
{
    if (m_head == NULL)
    {
        return (NULL);
    }
    return (m_head->GetValue());
}


//----------------------------------------------------------------
template <class Tvalue>
void ObjectDeque<Tvalue>::Clear(bool free)
/**
 * \brief Removes all values from the deque.
 * \param free True, frees the allocated memory for the values; otherwise false.
 **/
{
    ObjectDequeNode<Tvalue>* temp = m_head;
    while (temp != NULL)
    {
        ObjectDequeNode<Tvalue>* node = temp;
        temp = temp->GetNext();
        if (!free) node->SetValue(NULL);
        delete node;
    }
    m_head = NULL;
    m_tail = NULL;
}




#ifdef _RUSH_DEBUG_
//----------------------------------------------------------------
template <class Tvalue>
const ObjectDequeNode<Tvalue>* ObjectDeque<Tvalue>::GetHead() const
{
    return (m_head);
}
#endif



#ifdef _RUSH_DEBUG_
//----------------------------------------------------------------
template <class Tvalue>
const ObjectDequeNode<Tvalue>* ObjectDeque<Tvalue>::GetTail() const
{
    return (m_tail);
}
#endif


} // namespace rush

#endif // _RUSH_OBJECTDEQUE_H_


