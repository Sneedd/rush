/*
 * list.h - Definiton und Implementierung der List Template Klasse
 *
 * Author: Steffen Ott
 * Datum: 15.09.2007
 * Beschreibung:
 *   Die Klasse List<T> speichert Daten in einer einfach Verketten
 *   Liste. Die Klasse ListNode<T> ist ein Knoten in der Liste und
 *   enthält die Zeiger auf das jeweilige nächste Element in der
 *   Liste. Die List<T> Klasse ist auch optimiert für den Iterativen
 *   Zugriff auf einzelne Elemente über einen Index. Also die Position
 *   in der Liste.
 */


#ifndef _TEMPLATE_PRIORITYQUEUE_CONTAINER_H_
#define _TEMPLATE_PRIORITYQUEUE_CONTAINER_H_

#include <string.h> // für NULL und size_t
#include "prioqueuenode.h"

#ifndef likely
    #ifdef __GNUC__ // Check if GNUC is used
        #define likely(x)   __builtin_expect((x), 1)
        #define unlikely(x) __builtin_expect((x), 0)
    #else
        #warning No __buildin_expect() macro defined by the compiler
        #define likely(x)   (x)
        #define unlikely(x) (x)
    #endif
#endif



template <class T>
class PriorityQueue
{
    public:
        PriorityQueue();
        ~PriorityQueue();

        void Enqueue(T* element, int priority, int id = 0);
        T* Dequeue(bool remove = true);
        bool IsEmpty() const;

        bool IncreasePriority(T* element, int value = -1);
        bool IncreasePriority(int id, int value = -1);

        PriorityQueueNode<T>* Find(T* element);
        PriorityQueueNode<T>* FindByPriority(int priority);
        PriorityQueueNode<T>* FindById(int id);

        bool RemoveByPriority(int priority);
        bool RemoveById(int id);

        bool Contains(T* element);
        bool Contains(int id);

        void Clear(bool free = true);
        size_t Count() const;


    private:
        PriorityQueueNode<T>*   m_head;
        size_t                  m_size;
};



//-----------------------------------------------------------------
template <class T>
PriorityQueue<T>::PriorityQueue()
/**
 * \brief
 **/
{
    m_head = NULL;
    m_size = 0;
}



//-----------------------------------------------------------------
template <class T>
PriorityQueue<T>::~PriorityQueue()
/**
 * \brief
 **/
{
    Clear(true);
}

//-----------------------------------------------------------------
template <class T>
void PriorityQueue<T>::Enqueue(T* element, int priority, int id)
/**
 * \brief Adds an element to the queue with the given priority
 * and eventual the id. If the queue can handle multible of the same
 * Priority the priority it will be added at the last position of
 * that priority. If not multible priorities are set, the priority
 * will be increased after a free priority slot is found. If
 * priority is negative than the element will be set at the end of
 * the queue, with the appropiate priority.
 *
 **/
{
    if (unlikely(m_head == NULL))
    {
        // Input as first element
        m_head = new PriorityQueueNode<T>(element, priority, id);
        m_head->SetNext(NULL);
    }
    else
    {
        // Find the position
        PriorityQueueNode<T>* temp = m_head;
        PriorityQueueNode<T>* ltemp = temp;
        while (temp->GetNext() != NULL)
        {
            if (temp->GetPriority() < priority)
            {
                if (temp->GetNext() == NULL)
                {   // Add Element at the end
                    PriorityQueueNode<T>* node =
                        new PriorityQueueNode<T>(element, priority, id);
                    node->SetNext(temp->GetNext());
                    temp->SetNext(node);
                    break;
                }
                else
                {   // Go to the next Element and save the previous one
                    ltemp = temp;
                    temp = temp->GetNext();
                }
            }
            else if (temp->GetPriority() == priority)
            {
                temp = temp->GetNext();
            }
            else if (temp->GetPriority() > priority)
            {   // Input the element
                if (temp == head)
                {   // at the head
                    head = new PriorityQueueNode<T>(element, priority, id);
                    head->SetNext(temp);
                    break;
                }
                else
                {   // at the Middle or end
                    PriorityQueueNode<T>* node =
                        new PriorityQueueNode<T>(element, priority, id);
                    ltemp->SetNext(node);
                    node->setNext(temp);
                    break;
                }
            }
        }
        //if (temp == NULL) return 0;
    }
    size++;
}



//-----------------------------------------------------------------
template <class T>
T* PriorityQueue<T>::Dequeue(bool remove)
/**
 * \brief
 **/
{
    if (unlikely(m_head == NULL)) return (NULL);
    T* element = m_head->GetValue();
    if (likely(remove)) {
        // if element should be removed
        PriorityQueueNode<T>* node = m_head;
        m_head = m_head->GetNext();
        delete node;
        size--;
    }
    return (element);
}


//-----------------------------------------------------------------
template <class T>
bool PriorityQueue<T>::IsEmpty() const
/**
 * \brief
 **/
{
    return (m_head == NULL);
}



//-----------------------------------------------------------------
template <class T>
bool PriorityQueue<T>::IncreasePriority(T* element, int value)
/**
 * \brief
 **/
{
    PriorityQueueNode<T>* node = Find(element);
    if (unlikely(node == NULL)) return (false);

//    Remove(element);
//    Enqueue(element, node->GetPriority()+value,  node->GetId());
//    delete node;
}


//-----------------------------------------------------------------
template <class T>
bool PriorityQueue<T>::IncreasePriority(int id, int value)
/**
 * \brief
 **/
{
}



//-----------------------------------------------------------------
template <class T>
PriorityQueueNode<T>* PriorityQueue<T>::Find(T* element)
/**
 * \brief
 **/
{
    PriorityQueueNode<T>* node = m_head;
    while (node != NULL)
    {
        if (unlikely(node->GetValue() == element)) return (node);
        node = node->GetNext();
    }
    return (NULL);
}


//-----------------------------------------------------------------
template <class T>
PriorityQueueNode<T>* PriorityQueue<T>::FindByPriority(int priority)
/**
 * \brief
 **/
{
    PriorityQueueNode<T>* node = m_head;
    while (node != NULL)
    {
        if (unlikely(node->GetPriority() == priority)) return (node);
        node = node->GetNext();
    }
    return (NULL);
}


//-----------------------------------------------------------------
template <class T>
PriorityQueueNode<T>* PriorityQueue<T>::FindById(int id)
/**
 * \brief
 **/
{
    PriorityQueueNode<T>* node = m_head;
    while (node != NULL)
    {
        if (unlikely(node->GetId() == id)) return (node);
        node = node->GetNext();
    }
    return (NULL);

}



//-----------------------------------------------------------------
template <class T>
bool PriorityQueue<T>::RemoveByPriority(int priority)
/**
 * \brief
 **/
{
}


//-----------------------------------------------------------------
template <class T>
bool PriorityQueue<T>::RemoveById(int id)
/**
 * \brief
 **/
{
}



//-----------------------------------------------------------------
template <class T>
bool PriorityQueue<T>::Contains(T* element)
/**
 * \brief
 **/
{
    PriorityQueueNode<T>* node = m_head;
    while (node != NULL)
    {
        if (unlikely(node->GetValue() == element)) return (true);
        node = node->GetNext();
    }
    return (false);
}


//-----------------------------------------------------------------
template <class T>
bool PriorityQueue<T>::Contains(int id)
/**
 * \brief
 **/
{
    PriorityQueueNode<T>* node = m_head;
    while (node != NULL)
    {
        if (unlikely(node->GetId() == id)) return (true);
        node = node->GetNext();
    }
    return (false);
}



//-----------------------------------------------------------------
template <class T>
void PriorityQueue<T>::Clear(bool free)
/**
 * \brief
 **/
{
    if (m_head != NULL) {
        PriorityQueueNode<T>* temp = m_head;
        while (temp != NULL)
        {
            PriorityQueueNode<T>* node = temp;
            temp = temp->GetNext();
            if (node == NULL) break;
            if (node->GetValue() != NULL && free)
            {
                T* value = node->GetValue();
                delete value;
            }
            delete node;
        }
    }
    m_head = NULL;
    m_size = 0;
}


//-----------------------------------------------------------------
template <class T>
size_t PriorityQueue<T>::Count() const
/**
 * \brief
 **/
{
    return (m_size);
}






template <class T>
Uint32 Queue<T>::add(T* element)
// Adds a element and returns its Number if the number
// thats set is the same as another. if the returned number
// is 0 there is an error. If adding an element with the id
// is 0 the element will be added somewhere
{
    if (head == NULL)
    {
        // Input as first element
        head = element;
        element->setNext(NULL);
    }
    else
    {
        // Find the position
        T* temp = head;
        T* ltemp = temp;
        while (temp != NULL)
        {
            if (temp->getID() < element->getID())
            {
                if (temp->getNext() == NULL)
                {   // Add Element at the end
                    element->setNext(temp->getNext());
                    temp->setNext(element);
                    break;
                }
                else
                {   // Go to the next Element and save the previous one
                    ltemp = temp;
                    temp = temp->getNext();
                }
            }
            else if (temp->getID() == element->getID())
            {   // Increase the id if id is already set in queue
                element->setID(element->getID()+1);
            }
            else if (temp->getID() > element->getID())
            {   // Input the element
                if (temp == head)
                {   // at the head
                    head = element;
                    element->setNext(temp);
                    break;
                }
                else
                {   // at the Middle or end
                    ltemp->setNext(element);
                    element->setNext(temp);
                    break;
                }
            }
        }
        //if (temp == NULL) return 0;
    }
    size++;
    return (element->getID());
}


template <class T>
bool Queue<T>::del(Uint32 id)
// Deletes the Element with id and not reconfigure the ids
// so this will be one id witch is free then for the next
// add()
{
    if (head->getID() == id)
    {
        T* dt = head;
        head = head->getNext();
        delete dt;
    }
    else
    {
        T* temp = head;
        while (temp->getNext() != NULL)
        {
            if (temp->getNext()->getID() == id) break;
            temp = temp->getNext();
            if (temp == NULL) return (false);
        }
        T* dt = temp->getNext();
        temp->setNext(dt->getNext());
        delete dt;
    }
    size--;
    return (true);
}






template <class T>
T* Queue<T>::front() const
// Returns pointer of the first element
{
    return (head);
}



template <class T>
bool Queue<T>::remove()
// Deletes the first element and don't change the
// other priority numbers
{
    return (head);
    if (head == NULL) return (false);
    T* dt = head;
    head = head->getNext();
    delete dt;
    size--;
    return (true);
}



template <class T>
bool Queue<T>::empty() const
// Tests if queue is empty
{
    if (head == NULL) return (true);
    return (false);
}








#endif //_TEMPLATE_PRIORITYQUEUE_CONTAINER_H_




