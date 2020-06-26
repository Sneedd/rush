/*
 * list.h - Declaration and implementation of the List template class
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2012 - Steffen Ott
 *
 */


#ifndef _RUSH_LIST_H_
#define _RUSH_LIST_H_


#include <rush/config.h>
#include <rush/macros.h>


namespace rush {


/**
 * \brief The ListNode class represents a single node in a linked list.
 **/
template <class Tvalue>
class ListNode
{
    private:
        template <class> friend class List;
        ListNode()
            : m_next(NULL), m_data(NULL) {}
        ListNode(Tvalue* data, ListNode<Tvalue>* next = NULL)
            : m_next(next), m_data(data) {}
        ListNode(const ListNode<Tvalue>& copy) { }
        ~ListNode() { }

    public:
        /**
         * \brief Returns the next element in the list to this node.
         * \return Next node.
         **/
        inline ListNode<Tvalue>* GetNext() const
        { return (m_next); }

        /**
         * \brief Returns the value of the current node.
         * \return Value.
         **/
        inline Tvalue* GetValue() const
        { return (m_data); }

        /**
         * \brief Sets the value of the current node.
         * \param value Value.
         **/
        inline void SetValue(Tvalue* value)
        { m_data = value; }

    private:
        ListNode<Tvalue>* m_next;
        Tvalue*           m_data;
};



/**
 * \brief The List class ...
 **/
template <class Tvalue>
class List
{
    private:
        List(const List& copy) {}
        List& operator=(const List& list) { return (*this); }

    public:
        List();
        ~List();

        Tvalue* operator[](size_t index);
        ListNode<Tvalue>* GetHead() const;
        ListNode<Tvalue>* GetTail() const;

        void Add(Tvalue* element);
        void AddFirst(Tvalue* element);
        void AddLast(Tvalue* element);
        void AddRange(size_t size);
        void AddRange(Tvalue** elements, size_t size);

        bool Insert(size_t index, Tvalue* element);

        bool Remove(bool free = true);
        bool Remove(Tvalue* element, bool free = true);
        bool RemoveLast(bool free = true);
        bool RemoveAt(size_t index, bool free = true);

        void Clear(bool free = true);

        /**
         * \brief Counts the number of elements in this list.
         * \return Number of elements.
         **/
        inline size_t Count() const
        { return (m_count); }

    private:
        ListNode<Tvalue>*    m_head;
        ListNode<Tvalue>*    m_tail;
        size_t               m_count;
        ListNode<Tvalue>*    m_actualposition;
        size_t               m_actualindex;
};



//----------------------------------------------------------------
template <class Tvalue>
List<Tvalue>::List()
/**
 * \brief Standardconstructor, initializes the List object.
 **/
{
    m_head = NULL;
    m_tail = NULL;
    m_count = 0;
    m_actualindex = -1;
    m_actualposition = NULL;
}



//----------------------------------------------------------------
template <class Tvalue>
List<Tvalue>::~List()
/**
 * \brief Destructor. Frees all allocated memory.
 **/
{
    this->Clear(true);
}


//----------------------------------------------------------------
template <class Tvalue>
Tvalue* List<Tvalue>::operator[](size_t index)
/**
 * \brief Liefert das Element mit dem übergebenen Index zurück.
 * \param index Index auf das Element.
 * \return Liefert das Element zurück oder null wenn ein Fehler aufgetreten ist.
 **/
{
    if (unlikely(index < 0 || index >= m_count)) return (NULL);
    if (unlikely(index < m_actualindex || m_actualposition == NULL))
    {
        // Beginne wieder von vorne und zähle hoch bis zum
        // Element mit dem Index
        m_actualindex = 0;
        m_actualposition = m_head;
    }

    // Laufe bis zum Element mit dem jeweiligen Index
    while (m_actualindex != index)
    {
        m_actualindex++;
        m_actualposition = m_actualposition->m_next;
    }
    return (m_actualposition->m_data);
}





//----------------------------------------------------------------
template <class Tvalue>
ListNode<Tvalue>* List<Tvalue>::GetHead() const
{
    return (m_head);
}


//----------------------------------------------------------------
template <class Tvalue>
ListNode<Tvalue>* List<Tvalue>::GetTail() const
{
    return (m_tail);
}


//----------------------------------------------------------------
template <class Tvalue>
void List<Tvalue>::Add(Tvalue* element)
/**
 * \brief Adds an element at the end of the list.
 * \param element Element to be added.
 **/
{
    this->AddLast(element);
}



//----------------------------------------------------------------
template <class Tvalue>
void List<Tvalue>::AddFirst(Tvalue* element)
/**
 * \brief Fügt ein Element vor dem Ersten Element ein.
 * \param element Das Element das eingefügt werden soll.
 **/
{
    ListNode<Tvalue>* node = new ListNode<Tvalue>(element);
    if (unlikely(m_head == NULL))
    {
        // Liste ist leer
        m_head = node;
        m_tail = node;
        node->m_next = NULL;
    }
    else
    {
        // Liste enthält Knoten
        if (unlikely(m_head == m_actualposition)) m_actualindex++;
        node->m_next = m_head;
        m_head = node;
    }
    m_count++;
}




//----------------------------------------------------------------
template <class Tvalue>
void List<Tvalue>::AddLast(Tvalue* element)
/**
 * \brief Adds an element at the end of the list.
 * \param element Element to be added.
 **/
{
    ListNode<Tvalue>* node = new ListNode<Tvalue>(element);
    if (m_tail == NULL)
    {
        // Liste ist Leer
        m_head = node;
        m_tail = node;
        node->m_next = NULL;
        m_actualposition = m_head;
        m_actualindex = 0;
    }
    else
    {
        // Liste enthält weitere Knoten
        node->m_next = NULL;
        m_tail->m_next = node;
        m_tail = node;
    }
    m_count++;
}



//----------------------------------------------------------------
template <class Tvalue>
void List<Tvalue>::AddRange(size_t size)
/**
 * \brief Fügt eine angegebene Anzahl Elemente in die Liste ein
 * und setzt deren Werte auf NULL.
 * \param size Anzahl der hinzufügenden Elemente.
 * \return False wenn ein Fehler aufgetreten ist.
 **/
{
    if (unlikely(size <= 0)) return;
    // Alter Head sichern
    ListNode<Tvalue>* thead = m_head;
    m_count += size;
    m_head = new ListNode<Tvalue>(NULL, NULL);
    m_actualposition = m_head;
    for (size_t i=1; i<size; ++i)
    {
        m_actualposition->m_next = new ListNode<Tvalue>(NULL, NULL);
        m_actualposition = m_actualposition->m_next;
    }
    if (thead == NULL) m_tail = m_actualposition;
    m_actualposition->m_next = thead;
    m_actualindex = 0;
    m_actualposition = m_head;
}


//----------------------------------------------------------------
template <class Tvalue>
void List<Tvalue>::AddRange(Tvalue** elements, size_t size)
/**
 * \brief Fügt eine angegebene Anzahl an Elementen in die Liste
 * die Anzahl der Elemente in dem Array MUSS mit der Größen angabe
 * übereinstimmen. Das Array muss von der aufrufenden Funktion
 * gelöscht werden, aber nicht den Inhalt des Arrays.
 * \param elements Das Array mit den Elementen die hinzugefügt werden sollen
 * \param size Die Anzahl der Elemente in dem Array
 **/
{
    if (unlikely(size <= 0)) return;
    // Alter Head sichern
    ListNode<Tvalue>* thead = m_head;
    m_count += size;
    m_head = new ListNode<Tvalue>(elements[0], NULL);
    m_actualposition = m_head;
    for (size_t i=1; i<size; ++i)
    {
        m_actualposition->m_next = new ListNode<Tvalue>(elements[i], NULL);
        m_actualposition = m_actualposition->m_next;
    }
    if (thead == NULL) m_tail = m_actualposition;
    m_actualposition->m_next = thead;
    m_actualindex = 0;
    m_actualposition = m_head;
}


//----------------------------------------------------------------
template <class Tvalue>
bool List<Tvalue>::Insert(size_t index, Tvalue* element)
/**
 * \brief Fügt ein neues Element an der jeweiligen Stelle
 * hinzu. Der Index muss innerhalb der List sein. Alle Elemente
 * dahinter werden um eins verschoben. Ist es egal wo das
 * Element eingehängt wird, sollte Add() oder AddLast()
 * verwendet werden.
 * \param index Position des Elements.
 * \param element Das Elemt das eingefügt werden soll.
 * \return True wenn kein Fehler aufgetreten ist.
 **/
{
    RUSH_NOT_IMPLEMENTED_YET();
    return (false);
}



//----------------------------------------------------------------
template <class Tvalue>
bool List<Tvalue>::Remove(bool free)
/**
 * \brief Löscht das erste Element aus der Liste.
 * \param free True wenn der Speicher freigegeben werden soll.
 * \return True wenn kein Fehler aufgetreten.
 **/
{
    if (m_head == NULL) return (false);
    if (m_tail == m_head)
    {
        // Liste enthält einen Knoten
        if (free && m_tail->m_data != NULL) delete m_tail->m_data;
        delete m_tail;
        m_tail = NULL;
        m_head = NULL;
        m_actualposition = NULL;
        m_actualindex = -1;
    }
    else
    {
        // Liste enthält mehr als einen Knoten
        ListNode<Tvalue>* temp = m_head;
        m_head = m_head->m_next;
        if (free && temp->m_data != NULL) delete temp->m_data;
        delete temp;
        m_actualposition = m_head;
        m_actualindex = 0;
    }
    m_count--;
    return (true);
}





//----------------------------------------------------------------
template <class Tvalue>
bool List<Tvalue>::Remove(Tvalue* element, bool free)
// Delete the Element
{
    // TODO: m_actual verwalten
    if (unlikely(m_head == NULL)) return (false);
    if (unlikely(m_head->m_data == element))
    {
        // Zu löschendes Element ist das erste Element
        if (m_tail == m_head)
        {
            // Liste Enthält nur ein Element
            if (free && m_tail->m_data != NULL) delete m_tail->m_data;
            delete m_tail;
            m_tail = NULL;
            m_head = NULL;
        }
        else
        {
            ListNode<Tvalue>* temp = m_head;
            m_head = m_head->m_next;
            if (free && temp->m_data != NULL) delete temp->m_data;
            delete temp;
        }
    }
    else
    {
        ListNode<Tvalue>* temp = m_head;
        while (temp->m_next != NULL)
        {
            if (temp->m_next == element) break;
            temp = temp->m_next;
            if (temp == NULL) return (false);
        }
        if (temp->m_next == m_tail)
        {
            temp->m_next;
            if (free && m_tail->m_data != NULL) delete m_tail->m_data;
            delete m_tail;
            m_tail = temp;
        }
        else
        {
            ListNode<Tvalue>* dt = temp->m_next;
            temp->m_next = dt->m_next;
            if (free && dt->m_data != NULL) delete dt->m_data;
            delete dt;
        }
    }
    m_count--;
    return (true);
}



//----------------------------------------------------------------
template <class Tvalue>
bool List<Tvalue>::RemoveLast(bool free)
/**
 * \brief Löscht das letzte Element in der Liste. Diese Methode
 * ist nicht so schnell wie Remove().
 * \param free True wenn der Speicher freigegeben werden soll.
 * \return True wenn kein Fehler aufgetreten.
 **/
{
    if (unlikely(m_head == NULL)) return (false);
    if (unlikely(m_tail == m_head))
    {
        // Liste enthält ein Element
        if (free && m_tail->m_data != NULL) delete m_tail->m_data;
        delete m_tail;
        m_tail = NULL;
        m_head = NULL;
        m_actualposition = NULL;
        m_actualindex = -1;
    }
    else
    {
        // Liste enthält mehrere Elemente
        ListNode<Tvalue>* temp = m_head;
        while (temp->m_next != m_tail)
        {
            temp = temp->m_next;
            if (temp == NULL) return (false);
        }
        if (unlikely(m_actualposition == m_tail)) {
            m_actualposition = temp;
            m_actualindex--;
        }
        if (free && m_tail->m_data != NULL) delete m_tail->m_data;
        delete m_tail;
        m_tail = temp;
        m_tail->m_next = NULL;
    }
    m_count--;
    return (true);
}





//----------------------------------------------------------------
template <class Tvalue>
bool List<Tvalue>::RemoveAt(size_t index, bool free)
{
    RUSH_NOT_IMPLEMENTED_YET();
    return (false);
}




//----------------------------------------------------------------
template <class Tvalue>
void List<Tvalue>::Clear(bool free)
/**
 * \brief Löscht die gesamte Liste.
 * \param free True wenn der Speicher der Elemente freigegeben werden soll.
 **/
{
    ListNode<Tvalue>* temp = m_head;
    while (temp != NULL)
    {
        ListNode<Tvalue>* dt = temp;
        if (dt == NULL) break;
        temp = temp->m_next;
        if (free && dt->m_data != NULL) delete dt->m_data;
        delete dt;
    }
    m_actualindex = -1;
    m_actualposition = NULL;
}






} // namespace rush



#endif // _RUSH_LIST_H_



