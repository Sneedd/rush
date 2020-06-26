/*
 * hashmap.h - Definiton und Implementierung der HashMap Template Klasse
 *
 * Author: Steffen Ott
 * Datum: 15.09.2007
 * Beschreibung:
 */


#ifndef _TEMPLATE_HASHMAP_CONTAINER_H_
#define _TEMPLATE_HASHMAP_CONTAINER_H_

#include "hashmapnode.h"

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
class HashMap
{
    private:
        // Kopierkonstruktor und Zuweisung nicht erlaubt
        HashMap(const HashMap& copy);
        HashMap& operator=(const HashMap& map);

    public:
        // Konstruktoren & Destrukor
        HashMap();
        HashMap(size_t size);
        ~HashMap();

        // Iterations-Methoden
        HashMapNode<T>* operator[](size_t index);
        T*& operator[](const hash_string& key);

        // Einfügen und Löschen von Elementen
        void    Add        (const hash_string& key, T* value);
        bool    Remove     (const hash_string& key, bool free = true);
        void    Clear      (bool free = true);

        inline size_t GetSize()
        { return (m_size); }
        inline size_t Count()
        { return (m_size); }

    private:
        void Realloc(size_t size);
        size_t HashFunc(const hash_string& key);
        size_t CreatePrim(size_t size);

    private:
        size_t           m_size;
        size_t           m_actualindex;
        T*               m_empty;
        HashMapNode<T>** m_hashmap;
        size_t           m_mapsize;
};



//----------------------------------------------------------------
template <class T>
HashMap<T>::HashMap()
/**
 * \brief Erstellt eine leere Liste.
 **/
{
    m_head = NULL;
    m_tail = NULL;
    m_size = 0;
    m_actualindex = -1;
    m_actualposition = NULL;
    m_empty = NULL;
    m_hashmap = NULL;
    m_mapsize = 0;
    Realloc(50);
}


//----------------------------------------------------------------
template <class T>
HashMap<T>::HashMap(size_t size)
/**
 * \brief Erstellt eine leere Liste.
 **/
{
    m_head = NULL;
    m_tail = NULL;
    m_size = 0;
    m_actualindex = -1;
    m_actualposition = NULL;
    m_empty = NULL;
    m_hashmap = NULL;
    m_mapsize = 0;
    Realloc(size);
}


//----------------------------------------------------------------
template <class T>
HashMapT>::~HashMap()
/**
 * \brief Löscht alle Elemente aus der Liste und
 * alle Elemente werden im Speicher freigegeben.
 **/
{
    Clear(true);
}


//----------------------------------------------------------------
template <class T>
HashMapNode<T>* HashMap<T>::operator[](size_t index)
/**
 * \brief Liefert das Element mit dem übergebenen Index zurück.
 * \param index Index auf das Element.
 * \return Liefert das Element zurück oder null wenn ein Fehler aufgetreten ist.
 **/
{
    if (unlikely(index < 0 || index >= m_size)) return (m_empty);
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
template <class T>
T*& HashMap<T>::operator[](const hash_string& key)
/**
 * \brief
 **/
{
}


//----------------------------------------------------------------
template <class T>
bool HashMap<T>::Add(const hash_string& key, T* value)
/**
 * \brief Fügt ein Element vor dem Ersten Element ein.
 * \param element Das Element das eingefügt werden soll.
 * \return Liefert false wenn der Schlüssel bereits existiert.
 **/
{
    if (ExistsKey(key)) return (false);
    HashMapNode<T>* node = new HashMapNode(key, value);
    AddHash(m_hashmap, m_size, node);
    m_size++;
    if (unlikely(m_size >= (m_hashmap*1.25))) Realloc(m_size*2);
    return (true);
}



//----------------------------------------------------------------
template <class T>
bool HashMap<T>::Remove(const hash_string& key, bool free)
// Delete the Element
{
    HashMapNode<T>* node = (*this)[key];
    if (likely(node == NULL)) return (false);
    if (free && node->m_value != NULL) delete node->m_value;
    delete node;
    node = NULL;
    return (true);
}





//----------------------------------------------------------------
template <class T>
void HashMap<T>::Clear(bool free)
/**
 * \brief Löscht die gesamte Liste.
 * \param free True wenn der Speicher der Elemente freigegeben werden soll.
 **/
{
    // TODO
}



//----------------------------------------------------------------
template <class T>
void HashMap<T>::Realloc(size_t size)
/**
 * \brief Generiert die Hashmap neu mit der übergebenen Größe,
 * diese wird wiederrum von der Größe angepasst, damit sie eine
 * Primzahl darstellt. Diese Methode ist umfangreich und sollte
 * nur sporadisch verwendet werden, lieber einmal die HashTabelle
 * von der Größe überschätzen, als zu klein wählen. Sie muss alle
 * Hashes für die Elemente in der Tabelle neu berechnen.
 **/
{
    // TODO: Optimieren. Es gibt Verfahren, wo die HashMap nicht neu
    //    angelegt werden muss.
    // Eine Primzahl aus übergebenen Zahl machen
    size = CreatePrim(size);
    if (unlikely(size <= 0 || size == m_mapsize)) return;
    HashMapNode<T>** newmap = NULL;
    if (unlikely(size < m_mapsize))
    {
        // Hashmap verkleinern
        // Die neue Größe darf nicht kleiner sein als die Anzahl der Elemente
        if (unlikely(size < m_size)) return;
        newmap = new HashMapNode<T>*[size];
        for (int i=0; i<size; ++i) newmap[i] = NULL;
    }
    else
    {
        // Hashmap vergrößern
        newmap = new HashMapNode<T>*[size];
        for (int i=0; i<size; ++i) newmap[i] = NULL;
    }

    // Neue Map füllen
    if (unlikely(m_size == 0)) return;
    for (int i=0; i<m_mapsize; ++i)
    {
        if (likley(m_hashmap[i] == NULL)) continue;
        AddHash(newmap, size, m_hashmap[i]);
    }
}


//----------------------------------------------------------------
template <class T>
void HashMap<T>::AddHash(HashMapNode<T>** map, size_t size, HashMapNode<T>* element)
/**
 * \brief
 **/
{
    size_t hash = HashFunc(element->m_key, size);
    for (int i=hash; true; i++)
    {
        if (unlikely(i >= size)) i = 0;
        if (likely(map[i] != NULL)) continue;
        map[i] = element;
        break;
    }
}



//----------------------------------------------------------------
template <class T>
size_t HashMap<T>::HashFunc(const hash_string& key, size_t mapsize)
/**
 * \brief Die HashFunktion, siehe Kommentar im Code.
 **/
{
    unsigned int k = 0;
    int l = key.length();
    for (int i=0;i<l;++i)
    {
        k = ((k<<7) + key[i]) % mapsize;
    }
    return k;
}



//----------------------------------------------------------------
template <class T>
size_t HashMap<T>::CreatePrim(size_t range)
/**
 * \brief Sucht die nächste Primzahl nach range.
 **/
{
    for (;;)
	{
	    bool divisible = false;
        for (int i=2; i<range; ++i)
		{
		    if ((range%i) == 0)
			{
			    divisible = true;
				break;
			}
        }
		if (!divisible) return range;
		range++;
    }
}



#endif //_TEMPLATE_HASHMAP_CONTAINER_H_





