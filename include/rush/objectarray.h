/*
 * objectarray.h - Declaration and implementation of the ObjectArray template class
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2007-2012 - Steffen Ott
 *
 */


#ifndef _RUSH_OBJECTARRAY_TEMPLATE_H_
#define _RUSH_OBJECTARRAY_TEMPLATE_H_


#include <rush/config.h>
#include <rush/buildinexpect.h>
#include <string.h> // for NULL, memcpy(), memset()
#include <rush/comparer.h>
#include <rush/objectarrayflags.h>


namespace rush {




/**
 * \brief The ObjectArray template class is a array implementation.
 * This array implementation only stores pointer to any type.
 * Because this array stores only pointers, it is allowed to
 * store a NULL pointer into this array.
 **/
template <class Tvalue>
class ObjectArray
{
	public:
		ObjectArray();
		~ObjectArray();
    private:
        ObjectArray(ObjectArray& copy);
        ObjectArray& operator=(ObjectArray& copy);
    public:
        Tvalue*& operator[](const size_t index);
        const Tvalue* operator[](const size_t index) const;
        Tvalue* Item(const size_t index);
        const Tvalue* Item(const size_t index) const;
        #ifdef _RUSH_DEBUG_
        Tvalue* ItemDebug(const size_t index);
        const Tvalue* ItemDebug(const size_t index) const;
        #endif

		void Add(Tvalue* element);
		void AddRange(ObjectArray<Tvalue>* element, bool move = false);
		bool Insert(size_t index, Tvalue* element);
		bool Remove(Tvalue*& element, bool free = true);
		bool Remove(size_t index, bool free = true);
		void Clear(bool free = true);

		typedef int (*ObjectArrayComparer)(const Tvalue* a, const Tvalue* b);

        int Find(const Tvalue* value) const;
		bool Swap(size_t indexa, size_t indexb);
		void Sort(ObjectArrayComparer comparer);
		void Sort(const IComparer<Tvalue>& comparer);
		void Distinct(ObjectArrayComparer comparer);
		void Distinct(const IComparer<Tvalue>& comparer);
		void MoveUp();
		void Reverse();
        void CopyTo(Tvalue** values, int index = 0, int count = -1) const;

		void Alloc(size_t size);
		void Shrink();

        void SetFlags(ObjectArrayFlags flags);

        /**
         * \brief Counts the elements in the array.
         * \return Elements count in the array.
         **/
		inline size_t Count() const
		{ return (m_count); }

        /**
         * \brief Returns the capacity of the array.
         * \return The capacity of the array.
         **/
		inline size_t Capacity() const
		{ return (m_capacity); }

	public:
	    ObjectArrayFlags m_flags;
        Tvalue** m_array;
        size_t m_count;
        size_t m_capacity;
};




//----------------------------------------------------------------
template <class Tvalue>
ObjectArray<Tvalue>::ObjectArray()
/**
 * \brief Constructor, initializes the ObjectArray<Tvalue> object.
 **/
{
    // Initialize values
	m_count = 0;
    m_capacity = 16;
	m_array = new Tvalue*[m_capacity];
	// Initialize array
	m_array = (Tvalue**)memset((void*)m_array, 0, m_capacity*sizeof(Tvalue*));
}



//----------------------------------------------------------------
template <class Tvalue>
ObjectArray<Tvalue>::~ObjectArray()
/**
 * \brief Destructor.
 **/
{
	this->Clear(true);
	if (m_array != NULL)
	{
        delete [] m_array;
	}
}


//----------------------------------------------------------------
template <class Tvalue>
ObjectArray<Tvalue>::ObjectArray(ObjectArray<Tvalue>& copy)
/**
 * \brief Copyconstructor (private).
 **/
{
	// Unused
}


//----------------------------------------------------------------
template <class Tvalue>
ObjectArray<Tvalue>& ObjectArray<Tvalue>::operator=(ObjectArray<Tvalue>& copy)
/**
 * \brief Assignment operator (private).
 **/
{
	// Unused
	return (*this);
}


//----------------------------------------------------------------
template <class Tvalue>
Tvalue*& ObjectArray<Tvalue>::operator[](const size_t index)
/**
 * \brief Index operator, returns a element by its index.
 * \param index Index of an element in the array.
 * \return Found element or empty (see SetEmptyItem()).
 **/
{
    // TODO : Index out of range ?????
	if (index < 0 || index >= m_count) return (m_array[0]);
	return (m_array[index]);
}


//----------------------------------------------------------------
template <class Tvalue>
const Tvalue* ObjectArray<Tvalue>::operator[](const size_t index) const
/**
 * \brief Index operator, returns a element by its index.
 * \param index Index of an element in the array.
 * \return Found element or empty (see SetEmptyItem()).
 **/
{
	if (index < 0 || index >= m_count) return (NULL);
	return (m_array[index]);
}


//----------------------------------------------------------------
template <class Tvalue>
Tvalue* ObjectArray<Tvalue>::Item(const size_t index)
/**
 * \brief Returns a pointer to a element by its index.
 * \param index Index of an element in the array.
 * \return Found element or empty (see SetEmptyItem()).
 **/
{
	if (index < 0 || index >= m_count) return (NULL);
	return (m_array[index]);
}


//----------------------------------------------------------------
template <class Tvalue>
const Tvalue* ObjectArray<Tvalue>::Item(const size_t index) const
/**
 * \brief Returns a pointer to a element by its index.
 * \param index Index of an element in the array.
 * \return Found element or empty (see SetEmptyItem()).
 **/
{
	if (index < 0 || index >= m_count) return (NULL);
	return (m_array[index]);
}


#ifdef _RUSH_DEBUG_
//----------------------------------------------------------------
template <class Tvalue>
Tvalue* ObjectArray<Tvalue>::ItemDebug(const size_t index)
/**
 * \brief Returns a pointer to a element by its index.
 * \param index Index of an element in the array.
 * \return Found element or empty (see SetEmptyItem()).
 **/
{
	return (m_array[index]);
}
#endif


#ifdef _RUSH_DEBUG_
//----------------------------------------------------------------
template <class Tvalue>
const Tvalue* ObjectArray<Tvalue>::ItemDebug(const size_t index) const
/**
 * \brief Returns a pointer to a element by its index.
 * \param index Index of an element in the array.
 * \return Found element or empty (see SetEmptyItem()).
 **/
{
	return (m_array[index]);
}
#endif



//----------------------------------------------------------------
template <class Tvalue>
void ObjectArray<Tvalue>::Add(Tvalue* element)
/**
 * \brief Adds a new element to the end of the array.
 * \param element The element which should be added.
 */
{
	if (unlikely(m_count >= m_capacity)) {
		this->Alloc(m_capacity*2);
	}
	m_array[m_count] = element;
	m_count++;
}


//----------------------------------------------------------------
template <class Tvalue>
void ObjectArray<Tvalue>::AddRange(ObjectArray<Tvalue>* elements, bool move)
/**
 * \brief Adds the elements from the array into this array.
 * Does not copy the elements and does not remove the elements from the source array
 * until parameter move is true.
 * \param elements The elements which should be added to this array.
 * \param move True, if the elements in the source array should be removed,
 * but not freed; otherwise false.
 **/
{
    if ((m_count+elements->Count()) >= m_capacity)
    {
        size_t newCapacity = m_capacity;
        while ((m_count+elements->Count()) >= newCapacity)
        {
            newCapacity *= 2;
        }
        this->Alloc(newCapacity);
    }

    for (size_t i=0; i<elements->m_count; ++i)
    {
        m_array[m_count+i] = elements->m_array[i];
    }
    m_count += elements->Count();
    if (move) elements->Clear(false);
}


//----------------------------------------------------------------
template <class Tvalue>
bool ObjectArray<Tvalue>::Insert(size_t index, Tvalue* element)
/**
 * \brief Inserts a new element to the spezified index
 * into the array.
 * \param index Index of the new element.
 * \param element The element which should be added.
 * \return True on success; false otherwise.
 **/
{
    if (unlikely(index < 0 || index > m_count)) {
        return (false);
    }
    if (unlikely(index == m_count)) {
        Add(element);
        return (true);
    }
    if (unlikely(m_capacity <= m_count)) {
        this->Alloc(m_capacity*2);
    }
    size_t typesize = sizeof(Tvalue*);
    memcpy(m_array+index+1, m_array+index, (m_count-index)*typesize);
    m_array[index] = element;
	m_count++;
    return (true);
}



//----------------------------------------------------------------
template <class Tvalue>
bool ObjectArray<Tvalue>::Remove(Tvalue*& element, bool free)
/**
 * \brief Removes a element from the array.
 * \param element The element which should be removed.
 * \param free True if the memory of the element should be freed; otherwise false.
 * \return True on success; false otherwise.
 **/
{
    if (unlikely(element == NULL))
    {
        return (false);
    }

    int index = this->Find(element);
    if (index >= 0)
    {
        this->Remove((size_t)index, free);
        element = NULL;
        return (true);
    }
    return (false);
}


//----------------------------------------------------------------
template <class Tvalue>
bool ObjectArray<Tvalue>::Remove(size_t index, bool free)
/**
 * \brief Removes a element from the array.
 * \param index The index of the element which should be deleted.
 * \param free True if the memory of the element should be freed; otherwise false.
 * \return True on success; false otherwise.
 **/
{
    if (index < 0 || index >= m_count)
    {
        return (false);
    }
    if (free && m_array[index] != NULL)
    {
        if ((m_flags & ObjectArrayFlags::DisableDelete) != ObjectArrayFlags::DisableDelete)
        {
            delete m_array[index];
        }
    }
    memcpy(m_array+index, m_array+index+1, (m_count-index)*sizeof(Tvalue*));
    m_count--;
    m_array[m_count] = NULL;
    return (true);
}



//----------------------------------------------------------------
template <class Tvalue>
void ObjectArray<Tvalue>::Clear(bool free)
/**
 * \brief Removes all elements from the array.
 * \param free True if the memory of the element should be freed; otherwise false.
 */
{
    if (likely(m_array != NULL && free))
    {
        if ((m_flags & ObjectArrayFlags::DisableDelete) == ObjectArrayFlags::DisableDelete)
        {
            for (size_t i=0; i<m_count; i++)
            {
                m_array[i] = NULL;
            }
        }
        else
        {
            for (size_t i=0; i<m_count; i++)
            {
                if (likely(m_array[i] != NULL))
                {
                    delete m_array[i];
                    m_array[i] = NULL;
                }
            }
        }
    }
    m_count = 0;
}


//----------------------------------------------------------------
template <class Tvalue>
int ObjectArray<Tvalue>::Find(const Tvalue* value) const
/**
 * \brief Gets the index of the first element with the same pointer as in
 * the given value pointer.
 * \param value Value pointer to find.
 * \return Returns the index of the first found element; otherwise false.
 **/
{
    for (size_t i=0; i<m_count; ++i)
    {
        if (m_array[i] == value) return (i);
    }
    return (-1);
}


//----------------------------------------------------------------
template <class Tvalue>
bool ObjectArray<Tvalue>::Swap(size_t indexa, size_t indexb)
/**
 * \brief
 **/
{
    if (indexa < 0 || indexa >= m_count || indexb < 0 || indexb >= m_count)
    {
        return (false);
    }
    Tvalue* itema = m_array[indexa];
    m_array[indexa] = m_array[indexb];
    m_array[indexb] = itema;
    return (true);
}


//----------------------------------------------------------------
template <class Tvalue>
void ObjectArray<Tvalue>::Sort(ObjectArrayComparer comparer)
/**
 * \brief Sorts this array with the given comparer.
 **/
{
    // TODO : Implement Quicksort or better Introsort or better MergeInsertion
    //        Current Bubble Sort :(
    for (int i=m_count; i>1; i--)
    {
        for (int j=0; j<i-1; j++)
        {
            int compareResult = comparer(m_array[j], m_array[j+1]);
            if (compareResult > 0)
            {
                this->Swap(j, j+1);
            }
        }
    }
}


//----------------------------------------------------------------
template <class Tvalue>
void ObjectArray<Tvalue>::Sort(const IComparer<Tvalue>& comparer)
{
    // TODO : Implement Quicksort or better Introsort or better MergeInsertion
    //        Current Bubble Sort :(
    for (int i=m_count; i>1; i--)
    {
        for (int j=0; j<i-1; j++)
        {
            int compareResult = comparer.Compare(*(m_array[j]), *(m_array[j+1]));
            if (compareResult > 0)
            {
                this->Swap(j, j+1);
            }
        }
    }
}


//----------------------------------------------------------------
template <class Tvalue>
void ObjectArray<Tvalue>::Distinct(ObjectArrayComparer comparer)
{
    if (m_count > 0)
    {
        // Sort
        this->Sort(comparer);

        // Nulling the double values
        Tvalue* value = m_array[0];
        for (size_t i = 1; i < m_count; ++i)
        {
            if (comparer(value, m_array[i]) != 0)
            {
                value = m_array[i];
            }
            else
            {
                if (m_array[i] != NULL)
                {
                    delete m_array[i];
                }
                m_array[i] = NULL;
            }
        }

        // Moving up
        this->MoveUp();
    }
}


//----------------------------------------------------------------
template <class Tvalue>
void ObjectArray<Tvalue>::Distinct(const IComparer<Tvalue>& comparer)
{
    if (m_count > 0)
    {
        // Sort
        this->Sort(comparer);

        // Nulling the double values
        Tvalue* value = m_array[0];
        for (size_t i = 1; i < m_count; ++i)
        {
            if (comparer.Compare(*value, *(m_array[i])) != 0)
            {
                value = m_array[i];
            }
            else
            {
                if (m_array[i] != NULL)
                {
                    delete m_array[i];
                }
                m_array[i] = NULL;
            }
        }

        // Moving up
        this->MoveUp();
    }
}


//----------------------------------------------------------------
template <class Tvalue>
void ObjectArray<Tvalue>::MoveUp()
/**
 * \brief Removes the empty elements an move the other elements up.
 * Example: Array before MoveUp() : null, 000, 111, null, 222
 *          Array after MoveUp()  : 000, 111, 222
 **/
{
    size_t index = 0;
    Tvalue** temp = new Tvalue*[m_capacity];
    for (size_t i=0; i<m_count; ++i)
    {
        if (m_array[i] != NULL)
        {
            temp[index++] = m_array[i];
        }
    }
    m_count = index;
    delete [] m_array;
    m_array = temp;
}


//----------------------------------------------------------------
template <class Tvalue>
void ObjectArray<Tvalue>::Reverse()
/**
 * \brief Reverse the array elements in this array.
 **/
{
    // TODO
}

//----------------------------------------------------------------
template <class Tvalue>
void ObjectArray<Tvalue>::CopyTo(Tvalue** values, int index, int count) const
{
    // TODO
}




//----------------------------------------------------------------
template <class Tvalue>
void ObjectArray<Tvalue>::Alloc(size_t capacity)
/**
 * \brief Allocates the array with the given size. Increases and
 * decreases the array and copies all of its contents. Will free
 * automatically items which will drop if array size will be decreased.
 * \param capacity The new capacity of the array.
 */
{
    if (likely(capacity > m_capacity))
    {
        // Minimum capacity of the array
        if (unlikely(capacity < 16)) {
            capacity = 16;
        }

        // Extend array
        Tvalue** temp = new Tvalue*[capacity];
        memset(temp, 0, capacity*sizeof(Tvalue*));
        memcpy(temp, m_array, m_capacity*sizeof(Tvalue*));
        delete [] m_array;
        m_array = temp;
        m_capacity = capacity;
    }
    else
    {
        if (likely(m_capacity != capacity))
        {
            // Shrink array
            Tvalue** temp = new Tvalue*[capacity];
            memcpy(temp, m_array, capacity*sizeof(Tvalue*));
            if ((m_flags & ObjectArrayFlags::DisableDelete) != ObjectArrayFlags::DisableDelete)
            {
                for (size_t i=capacity; i<m_count; ++i)
                {
                    if (m_array[i] != NULL) {
                        delete m_array[i];  // Free dropping objects
                    }
                }
            }
            delete [] m_array;
            m_array = temp;
            m_capacity = capacity;
            m_count = ((m_count < capacity) ? m_count:capacity);
        }
    }
}



//----------------------------------------------------------------
template <class Tvalue>
void ObjectArray<Tvalue>::Shrink()
/**
 * Decreases the capacity of the dynamic array until it has the size
 * of the actual number of items in the array.
 */
{
    this->Alloc(m_count);
}


//----------------------------------------------------------------
template <class Tvalue>
void ObjectArray<Tvalue>::SetFlags(ObjectArrayFlags flags)
/**
 * \brief Sets the flags of the array and to change it's behavior.
 * Use with caution, some settings can result in memory leaks.
 * \param flags Flags.
 **/
{
    m_flags = flags;
}


} // namespace rush


#endif // _RUSH_OBJECTARRAY_TEMPLATE_H_


