/*
 * reverselist.h - Declaration and implementation of the ReverseList template class
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2011-2012 - Steffen Ott
 *
 */





#ifndef _RUSH_REVERSELIST_H_
#define _RUSH_REVERSELIST_H_


#include <rush/config.h>

namespace rush {

/**
 * \brief The ReverseListNode template class stores the data for one list node.
 **/
template <class Tvalue>
class ReverseListNode
{
    private:
        template <class> friend class List;
        ReverseListNode()
            : m_next(NULL), m_prev(NULL), m_data(NULL) {}
        ReverseListNode(Tvalue* data, ReverseListNode<Tvalue>* next = NULL)
            : m_next(next), m_prev(NULL), m_data(data) {}
        ReverseListNode(const ReverseListNode<Tvalue>& copy) { }
        ~ReverseListNode() { }

    public:
        inline ReverseListNode<Tvalue>* GetNext() const
        { return (m_next); }
        inline ReverseListNode<Tvalue>* GetPrevious() const
        { return (m_prev); }
        inline Tvalue* GetValue() const
        { return (m_data); }
        inline void SetValue(Tvalue* value)
        { m_data = value; }

    private:
        inline void SetNext(ReverseListNode<Tvalue>* next)
        { m_next = next; }
        inline void SetPrevious(ReverseListNode<Tvalue>* prev)
        { m_prev = prev; }

    private:
        ReverseListNode<Tvalue>* m_next;
        ReverseListNode<Tvalue>* m_prev;
        Tvalue*                  m_data;
};


/**
 * \brief The ReverseList template class implements a double linked list.
 * Every node has apart from the next pointer also a previous pointer.
 **/
template <class Tvalue>
class ReverseList
{
    private:
        ReverseList(const ReverseList& copy) {}
        ReverseList& operator=(const ReverseList& list) { return (*this); }

    public:
        ReverseList();
        ~ReverseList();

        bool add(Tvalue* element);
        bool addLast(Tvalue* element);

        bool del();
        bool del(Tvalue* element);
        bool delLast();

        inline Tvalue* getFirst()
        { return (head); }
        inline Tvalue* getLast()
        { return (tail); }
        inline size_t getSize()
        { return (size); }


    private:
        Tvalue* head;
        Tvalue* tail;
        size_t size;
};




template <class Tvalue>
ReverseList<Tvalue>::ReverseList()
{
    head = NULL;
    tail = NULL;
    size = 0;
}


template <class Tvalue>
ReverseList<Tvalue>::~ReverseList()
{
    Tvalue* temp = head;
    while (temp != NULL)
    {
        Tvalue* dt = temp;
        temp = temp->getNext();
        if (dt == NULL) break;
        delete dt;
    }
}


template <class Tvalue>
bool ReverseList<Tvalue>::add(Tvalue* element)
// Add Element on the first position
{
    if (element == NULL) return (false);
    if (head == NULL)
    {
        head = element;
        tail = element;
        element->setNext(NULL);
        element->setPrev(NULL);
    }
    else
    {
        element->setNext(head);
        element->setPrev(NULL);
        head = element;
    }
    size++;
    return (true);
}


template <class Tvalue>
bool ReverseList<Tvalue>::addLast(Tvalue* element)
// Add Element on the last position
{
    if (element == NULL) return (false);
    if (tail == NULL)
    {
        head = element;
        tail = element;
        element->setNext(NULL);
        element->setPrev(NULL);
    }
    else
    {
        element->setNext(NULL);
        element->setPrev(tail);
        tail->setNext(element);
        tail = element;
    }
    size++;
    return (true);
}


template <class Tvalue>
bool ReverseList<Tvalue>::del(Tvalue* element)
// Delete the Element
{
    if (head == NULL) return (false);
    if (head == element)
    {
        if (tail == head)
        {
            delete tail;
            tail = NULL;
            head = NULL;
        }
        else
        {
            Tvalue* dt = head;
            head = head->getNext();
            head->setPrev(NULL);
            delete dt;
        }
    }
    else
    {
        Tvalue* temp = head;
        while (temp->getNext() != NULL)
        {
            if (temp->getNext() == element) break;
            temp = temp->getNext();
            if (temp == NULL) return (false);
        }
        if (temp->getNext() == tail)
        {
            temp->setNext(NULL);
            delete tail;
            tail = temp;
        }
        else
        {
            Tvalue* dt = temp->getNext();
            temp->setNext(dt->getNext());
            dt->getNext()->setPrev(temp);
            delete dt;
        }
    }
    size--;
    return (true);
}


template <class Tvalue>
bool ReverseList<Tvalue>::delLast()
// Delete the Last Element
{
    if (head == NULL) return (false);
    if (tail == head)
    {
        delete tail;
        tail = NULL;
        head = NULL;
    }
    else
    {
        Tvalue* temp = head;
        while (temp->getNext() != tail)
        {
            temp = temp->getNext();
            if (temp == NULL) return (false);
        }
        delete tail;
        tail = temp;
        tail->setNext(NULL);
    }
    size--;
    return (true);
}


template <class Tvalue>
bool ReverseList<Tvalue>::del()
// Delete the First Element
{
    if (head == NULL) return (false);
    if (tail == head)
    {
        delete tail;
        tail = NULL;
        head = NULL;
    }
    else
    {
        Tvalue* dt = head;
        head = head->getNext();
        head->setPrev(NULL);
        delete dt;
    }
    size--;
    return (true);
}






} // namespace rush



#endif //_RUSH_REVERSELIST_H_



