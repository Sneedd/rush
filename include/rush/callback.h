/*
 * callback.h - Deklaration and implementation of the ICallback and Callback classes
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2011-2012 - Steffen Ott
 *
 */


#ifndef _RUSH_CALLBACK_TEMPLATE_H_
#define _RUSH_CALLBACK_TEMPLATE_H_


#include <rush/config.h>

namespace rush {

/**
 * \brief The ICallback interface is the base class for storing an calling callbacks.
 * This interface is actually an abstract class due to the compare method.
 **/
template<class Targs>
class ICallback
{
    public:
        /// \brief Standardconstructor, initializes the ICallback object.
        ICallback() {}

        /// \brief Destructor.
        virtual ~ICallback() {}

        /// \brief Compares this object with the one in the argument.
        /// \param callback Object which will be tested with this.
        /// \return True, if callbacks are equal; otherwise false.
        inline bool Compare(const ICallback* callback)
        { return (this->GetObject() == callback->GetObject() && this->GetMethod() == callback->GetMethod()); }

        /// \brief Executes the callback.
        virtual void Execute(const Targs& args) = 0;

    protected:
        /// \brief Returns the pointer of the object.
        virtual const void* GetObject() const = 0;

        /// \brief Returns the pointer of the method.
        virtual const void* GetMethod() const = 0;
};

/**
 * \brief The Callback class is the implementation to store any class method pointer callbacks.
 **/
template<class Tvalue, class Targs>
class Callback : public ICallback<Targs>
{
    private:
        Callback() {}
        Callback(const Callback& object) {}
        Callback& operator=(const Callback& object) {}

    public:
        typedef void (Tvalue::*CallbackFunction)(const Targs&);

        /// \brief Constructor, initializes the Callback class.
        Callback(Tvalue* object, CallbackFunction method)
        { m_object = object; m_method = method; }

        /// \brief Destructor.
        ~Callback() {}

        /// \brief Executes the callback.
        inline void Execute(const Targs& args)
        { (m_object->*m_method)(args); }

    protected:
        /// \brief Returns the pointer of the object.
        inline const void* GetObject() const
        { return ((void*)m_object); }

        /// \brief Returns the pointer of the method.
        inline const void* GetMethod() const
        { return (*((void**)(&m_method))); }

    private:
        Tvalue* m_object;
        CallbackFunction m_method;
};


} // namespace rush

#endif // _RUSH_CALLBACK_TEMPLATE_H_




