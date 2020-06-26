/*
 * priorityqueue.h - Declaration and implementation of the PriorityQueue template class
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2011-2012 - Steffen Ott
 *
 */




#ifndef _RUSH_PRIORITYQUEUE_H_
#define _RUSH_PRIORITYQUEUE_H_


#include <rush/config.h>

namespace rush {


// TODO: Änderung in eine Queue in der mehrere gleichen IDs
//       vorkommen können. OK!!!
// TODO: Test!!!!!!!
//
//namespace scl {
//
//template <class T>
//class Queue_Aid
//{
//    public:
//        Queue_Aid();
//        ~Queue_Aid();
//
//        Uint32 add(T* element);
//        bool del(Uint32 id);
//
//
//        T* front() const;
//        bool remove();
//        bool empty() const;
//
//        void update();
//        inline Uint32 getSize()
//        { return (size); }
//
//
//    private:
//        T* head;
//        Uint32 size;
//};
//
//
//
//template <class T>
//Queue_Aid<T>::Queue_Aid()
//{
//    head = NULL;
//    size = 0;
//}
//
//
//
//template <class T>
//Queue_Aid<T>::~Queue_Aid()
//{
//    T* temp = head;
//    while (temp != NULL)
//    {
//        T* dt = temp;
//        temp = temp->getNext();
//        if (dt == NULL) break;
//        delete dt;
//    }
//}
//
//
//template <class T>
//Uint32 Queue_Aid<T>::add(T* element)
//// Adds a element and returns its Number if the number
//// thats set is the same as another. if the returned number
//// is 0 there is an error. If adding an element with the id
//// is 0 the element will be added somewhere
//{
//    if (head != NULL)
//    {
//        T* temp = head;
//        T* tlast = head;
//        while (element->getID() > temp->getID())
//        {
//            tlast = temp;
//            temp = temp->getNext();
//            if (temp == NULL) break;
//        }
//        if (tlast != temp)
//        {// In der Mitte oder Hinten einfügen
//            element->setNext(temp);
//            tlast->setNext(element);
//        }
//        else
//        {// Ganz vorne einfügen
//            element->setNext(head);
//            head = element;
//        }
//    }
//    else
//    {
//        head = element;
//        head->setNext(NULL);
//    }
//    size++;
//    return (element->getID());
//}
//
//template <class T>
//bool Queue_Aid<T>::del(Uint32 id)
//// Deletes the Element with id and not reconfigure the ids
//// so this will be one id witch is free then for the next
//// add()
//{
//    if (head->getID() == id)
//    {
//        T* dt = head;
//        head = head->getNext();
//        delete dt;
//    }
//    else
//    {
//        T* temp = head;
//        while (temp->getNext() != NULL)
//        {
//            if (temp->getNext()->getID() == id) break;
//            temp = temp->getNext();
//            if (temp == NULL) return (false);
//        }
//        T* dt = temp->getNext();
//        temp->setNext(dt->getNext());
//        delete dt;
//    }
//    size--;
//    return (true);
//}
//
//
//
//
//
//template <class T>
//T* Queue_Aid<T>::front() const
//// Returns pointer of the first element
//{
//    return (head);
//}
//
//
//
//template <class T>
//bool Queue_Aid<T>::remove()
//// Deletes the first element and don't change the
//// other priority numbers
//{
//    if (head == NULL) return (false);
//    T* dt = head;
//    head = head->getNext();
//    delete dt;
//    size--;
//    return (true);
//}
//
//
//
//template <class T>
//bool Queue_Aid<T>::empty() const
//// Tests if queue is empty
//{
//    if (head == NULL) return (true);
//    return (false);
//}
//
//
//
//
//
//} // namespace scl


///**
// * \brief The Queue template class implements the container queue or FIFO.
// **/
//template <class Tvalue>
//class Queue
//{
//    public:
//        Queue();
//        ~Queue();
//
//        Uint32 add(Tvalue* element);
//        bool del(Uint32 id);
//
//        Tvalue* front() const;
//        bool remove();
//        bool empty() const;
//
//        void update();
//        inline Uint32 getSize()
//        { return (size); }
//
//    private:
//        Tvalue* head;
//        Uint32 size;
//};
//
//
////-----------------------------------------------------------------------------
//template <class Tvalue>
//Queue<Tvalue>::Queue()
//{
//    head = NULL;
//    size = 0;
//}
//
//
//
////-----------------------------------------------------------------------------
//template <class Tvalue>
//Queue<Tvalue>::~Queue()
//{
//    T* temp = head;
//    while (temp != NULL)
//    {
//        T* dt = temp;
//        temp = temp->getNext();
//        if (dt == NULL) break;
//        delete dt;
//    }
//}
//
//
//
////-----------------------------------------------------------------------------
//template <class Tvalue>
//Uint32 Queue<Tvalue>::add(T* element)
//// Adds a element and returns its Number if the number
//// thats set is the same as another. if the returned number
//// is 0 there is an error. If adding an element with the id
//// is 0 the element will be added somewhere
//{
//    if (head == NULL)
//    {
//        // Input as first element
//        head = element;
//        element->setNext(NULL);
//    }
//    else
//    {
//        // Find the position
//        T* temp = head;
//        T* ltemp = temp;
//        while (temp != NULL)
//        {
//            if (temp->getID() < element->getID())
//            {
//                if (temp->getNext() == NULL)
//                {   // Add Element at the end
//                    element->setNext(temp->getNext());
//                    temp->setNext(element);
//                    break;
//                }
//                else
//                {   // Go to the next Element and save the previous one
//                    ltemp = temp;
//                    temp = temp->getNext();
//                }
//            }
//            else if (temp->getID() == element->getID())
//            {   // Increase the id if id is already set in queue
//                element->setID(element->getID()+1);
//            }
//            else if (temp->getID() > element->getID())
//            {   // Input the element
//                if (temp == head)
//                {   // at the head
//                    head = element;
//                    element->setNext(temp);
//                    break;
//                }
//                else
//                {   // at the Middle or end
//                    ltemp->setNext(element);
//                    element->setNext(temp);
//                    break;
//                }
//            }
//        }
//        //if (temp == NULL) return 0;
//    }
//    size++;
//    return (element->getID());
//}
//
//
////-----------------------------------------------------------------------------
//template <class Tvalue>
//bool Queue<Tvalue>::del(Uint32 id)
//// Deletes the Element with id and not reconfigure the ids
//// so this will be one id witch is free then for the next
//// add()
//{
//    if (head->getID() == id)
//    {
//        T* dt = head;
//        head = head->getNext();
//        delete dt;
//    }
//    else
//    {
//        T* temp = head;
//        while (temp->getNext() != NULL)
//        {
//            if (temp->getNext()->getID() == id) break;
//            temp = temp->getNext();
//            if (temp == NULL) return (false);
//        }
//        T* dt = temp->getNext();
//        temp->setNext(dt->getNext());
//        delete dt;
//    }
//    size--;
//    return (true);
//}
//
//
//
//
//
//
////-----------------------------------------------------------------------------
//template <class Tvalue>
//T* Queue<Tvalue>::front() const
//// Returns pointer of the first element
//{
//    return (head);
//}
//
//
//
////-----------------------------------------------------------------------------
//template <class Tvalue>
//bool Queue<Tvalue>::remove()
//// Deletes the first element and don't change the
//// other priority numbers
//{
//    if (head == NULL) return (false);
//    T* dt = head;
//    head = head->getNext();
//    delete dt;
//    size--;
//    return (true);
//}
//
//
//
////-----------------------------------------------------------------------------
//template <class Tvalue>
//bool Queue<Tvalue>::empty() const
//// Tests if queue is empty
//{
//    if (head == NULL) return (true);
//    return (false);
//}
//



} // namespace rush


#endif // _RUSH_PRIORITYQUEUE_H_


