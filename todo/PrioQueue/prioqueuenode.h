/*
 * listnode.h - Definiton und Implementierung der ListNode Template Klasse
 *
 * Author: Steffen Ott
 * Datum: 15.09.2007
 * Beschreibung:
 *   Die Klasse ListNode<T> speichert Daten in ihren Memebern. Die
 *   ListNode<T> Klasse ist nur für die List<T> Klasse verfügbar
 *   da alle Elemente in dieser Klasse private sind. Die List<T>
 *   Klasse kann aber über eine "friend" Beziehung auf alle
 *   Elemente dieser Klasse zugreifen.
 */


#ifndef _TEMPLATE_PRIORITYQUEUENODE_H_
#define _TEMPLATE_PRIORITYQUEUENODE_H_

#ifndef _TEMPLATE_PRIORITYQUEUE_CONTAINER_H_
    #include "prioqueue.h"
#endif

template <class T>
class PriorityQueueNode
{
    private:
        template <class> friend class PriorityQueue;
        PriorityQueueNode()
            : m_next(NULL), m_data(NULL), m_id(0), m_prio(0) {}
        PriorityQueueNode(T* data, ListNode<T>* next = NULL)
            : m_next(next), m_data(data) {}
        PriorityQueueNode(T* data, int priority, int id)
            : m_next(NULL), m_data(data), m_id(id), m_prio(priority) {}
        PriorityQueueNode(const ListNode<T>& copy) { }
        ~PriorityQueueNode() { }
    private:
        inline PriorityQueueNode<T>* GetNext() const
        { return (m_next); }
        inline void SetNext(ListNode<T>* next)
        { m_next = next; }
    public:
        inline T* GetValue() const
        { return (m_data); }
        inline void SetValue(T* value)
        { m_data = value; }
        inline int GetPriority() const
        { return (m_prio); }


    private:
        PriorityQueueNode<T>* m_next;
        T*                    m_data;
        int                   m_id;
        int                   m_prio;
};


#endif //_TEMPLATE_PRIORITYQUEUENODE_H_
