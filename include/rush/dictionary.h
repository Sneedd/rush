/*
 * dictionary.h - Declaration and implementation of the Dictionary class
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2012 - Steffen Ott
 *
 */



#ifndef _RUSH_DICTIONARY_H_
#define _RUSH_DICTIONARY_H_

#include <rush/config.h>
#include <rush/buildinexpect.h>


namespace rush {

template <class Tkey, class Tvalue>
class KeyValue
{
    public:
        KeyValue();
        KeyValue(Tkey* key, Tvalue* value);
        ~KeyValue();

        Tkey* GetKey();
        void SetKey(Tkey* key);
        Tvalue* GetValue();
        void GetValue(Tvalue* value);

    private:
        Tkey* m_key;
        Tvalue* m_value;
};



template <class Tkey, class Tvalue>
class Dictionary
{
    public:
        Dictionary();
        Dictionary(size_t capacity);
        ~Dictionary();

        bool Add(Tkey* key, Tvalue* value);
        void Remove(Tkey* key, bool free=true);
        void RemoveAll(bool free=true);
        void Del(Tkey* key);
        bool Exists(Tkey* key);
        Tvalue* Find(Tkey* key);

        KeyValue<Tkey, Tvalue>* GetFirst();
        KeyValue<Tkey, Tvalue>* GetNext();


        void Count();
        void Lenght();

    private:
    	size_t HashJoaat(unsigned char* key, size_t keyLenght);


    private:
    	KeyValue<Tkey, Tvalue>** m_hashtable;
    	size_t m_capacity;
    	size_t m_count;
    	size_t m_keysize;  // ????

};



template <class KEY, class VALUE>
size_t Dictionary<KEY, VALUE>::HashJoaat(unsigned char* key, size_t keyLenght)
{
     size_t hash = 0;
     for (size_t i = 0; i < keyLenght; i++) {
         hash += key[i];
         hash += (hash << 10);
         hash ^= (hash >> 6);
     }
     hash += (hash << 3);
     hash ^= (hash >> 11);
     hash += (hash << 15);
     return (hash);
}





} // namespace rush

#endif // _RUSH_DICTIONARY_H_


