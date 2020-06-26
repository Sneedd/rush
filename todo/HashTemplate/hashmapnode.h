/*
 * hashmapnode.h - Deklaration und Implementierung der HashMapNode Template Klasse
 *
 * Author: Steffen Ott
 * Datum: 15.09.2007
 * Beschreibung:
 *
 */


#ifndef _TEMPLATE_HASHMAPNODE_H_
#define _TEMPLATE_HASHMAPNODE_H_

#include <string>
#define hash_string std::string

template <class T>
class HashMapNode
{
    private:
        template <class> friend class HashMap;
        HashMapNode() : m_value(NULL), m_next(NULL) {}
        HashMapNode(const hash_string& key, T* value = NULL, HashMapNode<T>* next)
            : m_key(key), m_value(value), m_next(next) {}
        ~HashMapNode() {}

    public:
        HashMapNode<T>* GetNext() const
        { return (m_next); }
        const hash_string& GetKey() const
        { return (m_key); }
        T* GetValue() const
        { return (m_value); }

    private:
        hash_string m_key;
        T* m_value;
        HashMapNode<T>* m_next;
};



#endif // _TEMPLATE_HASHMAPNODE_H_


