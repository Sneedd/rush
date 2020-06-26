/*
 * comparer.h - Deklaration and implementation of the ICallback and Callback classes
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2012 - Steffen Ott
 *
 */


#ifndef _RUSH_COMPARER_TEMPLATE_H_
#define _RUSH_COMPARER_TEMPLATE_H_

#include <rush/config.h>


namespace rush {

/**
 * \brief The IComparer interface is the base class for storing comparer
 * methods. It can be used to implement a comparer class or can be used
 * to call a class method which does the compare by utilizing Comparer<T,S>.
 **/
template<class Targs>
class IComparer
{
    public:
        /// \brief Standardconstructor, initializes the ICallback object.
        IComparer() {}

        /// \brief Destructor.
        virtual ~IComparer() {}

        /// \brief Compares two objects with eachother and returns zero if they
        /// are equal; otherwise a negative or positive value.
        /// \param a Object which will be tested with this.
        /// \param b Object which will be tested with this.
        /// \return Returns zero if equal; otherwise a negative or positive value.
        virtual inline int Compare(const Targs* a, const Targs* b) const
        {
            if (a != NULL && b != NULL) return (this->Compare(*a, *b));
            if (a == b) return (0);
            if (a == NULL) return (-1);
            return (+1);
        }

        /// \brief Compares two objects with eachother and returns zero if they
        /// are equal; otherwise a negative or positive value.
        /// \param a Object which will be tested with this.
        /// \param b Object which will be tested with this.
        /// \return Returns zero if equal; otherwise a negative or positive value.
        virtual int Compare(const Targs& a, const Targs& b) const = 0;
};




/**
 * \brief The Comparer class is the implementation to store a comparer class method pointer callback.
 **/
template<class Tvalue, class Targs>
class Comparer : public IComparer<Targs>
{
    private:
        Comparer() {}
        Comparer(const Comparer& object) {}
        Comparer& operator=(const Comparer& object) {}

    public:
        typedef int (Tvalue::*ComparerFunction)(const Targs& a, const Targs& b);

        /// \brief Constructor, initializes the Comparer class.
        Comparer(Tvalue* object, ComparerFunction method)
        { m_object = object; m_method = method; }

        /// \brief Destructor.
        ~Comparer() {}

        /// \brief Compares two objects with eachother and returns zero if they
        /// are equal; otherwise a negative or positive value.
        /// \param a Object which will be tested with this.
        /// \param b Object which will be tested with this.
        /// \return Returns zero if equal; otherwise a negative or positive value.
        virtual inline int Compare(const Targs& a, const Targs& b) const
        {
            return (m_method(a, b));
        }

    private:
        Tvalue* m_object;
        ComparerFunction m_method;
};


} // namespace rush

#endif // _RUSH_COMPARER_TEMPLATE_H_





