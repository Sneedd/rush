/*
 * rect.h - Declaration of the Rect template class and their typedefs
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2011-2012 - Steffen Ott
 *
 */



#ifndef _RUSH_RECT_H_
#define _RUSH_RECT_H_


#include <rush/config.h>



namespace rush {


/**
 * \brief The Rect template class implements a datastructure for rectangle data.
 **/
template <typename Tvalue>
class Rect
{
    public:
        Rect();
        Rect(Tvalue x, Tvalue y, Tvalue w, Tvalue h);
        Rect(const Rect& rect);
        ~Rect();

        Rect& operator=(const Rect& rect);

        void Set(Tvalue x, Tvalue y, Tvalue w, Tvalue h);
        void Set(const Rect& rect);

        inline void SetX(Tvalue x)
        { m_x = x; }

        inline void SetY(Tvalue y)
        { m_y = y; }

        inline void SetWidth(Tvalue width)
        { m_width = width; }

        inline void SetHeight(Tvalue height)
        { m_height = height; }

        inline bool Contains(Tvalue x, Tvalue y) const
        { return (x >= m_x && x <= m_x+m_width && y >= m_y && y <= m_y+m_height); }

        inline Tvalue GetX() const
        { return (m_x); }

        inline Tvalue GetY() const
        { return (m_y); }

        inline Tvalue GetWidth() const
        { return (m_width); }

        inline Tvalue GetHeight() const
        { return (m_height); }

        inline Tvalue GetTop() const
        { return (m_y); }

        inline Tvalue GetBottom() const
        { return (m_y+m_height); }

        inline Tvalue GetLeft() const
        { return (m_x); }

        inline Tvalue GetRight() const
        { return (m_x+m_width); }

    private:
        Tvalue m_x;
        Tvalue m_y;
        Tvalue m_width;
        Tvalue m_height;
};


//-----------------------------------------------------------------------------
template <typename Tvalue>
Rect<Tvalue>::Rect()
/**
 * \brief
 **/
{
    m_x = 0;
    m_y = 0;
    m_width = 0;
    m_height = 0;
}


//-----------------------------------------------------------------------------
template <typename Tvalue>
Rect<Tvalue>::Rect(Tvalue x, Tvalue y, Tvalue width, Tvalue height)
/**
 * \brief
 **/
{
    m_x = x;
    m_y = y;
    m_width = width;
    m_height = height;
}


//-----------------------------------------------------------------------------
template <typename Tvalue>
Rect<Tvalue>::Rect(const Rect& rect)
/**
 * \brief
 **/
{
    m_x = rect.m_x;
    m_y = rect.m_y;
    m_width = rect.m_width;
    m_height = rect.m_height;
}


//-----------------------------------------------------------------------------
template <typename Tvalue>
Rect<Tvalue>::~Rect()
/**
 * \brief
 **/
{
}


//-----------------------------------------------------------------------------
template <typename Tvalue>
Rect<Tvalue>& Rect<Tvalue>::operator=(const Rect<Tvalue>& rect)
/**
 * \brief
 **/
{
    m_x = rect.m_x;
    m_y = rect.m_y;
    m_width = rect.m_width;
    m_height = rect.m_height;
    return (*this);
}


//-----------------------------------------------------------------------------
template <typename Tvalue>
void Rect<Tvalue>::Set(Tvalue x, Tvalue y, Tvalue width, Tvalue height)
/**
 * \brief
 **/
{
    m_x = x;
    m_y = y;
    m_width = width;
    m_height = height;
}


//-----------------------------------------------------------------------------
template <typename Tvalue>
void Rect<Tvalue>::Set(const Rect& rect)
/**
 * \brief
 **/
{
    m_x = rect.m_x;
    m_y = rect.m_y;
    m_width = rect.m_width;
    m_height = rect.m_height;
}




} // namespace rush


#endif // _RUSH_RECT_H_

