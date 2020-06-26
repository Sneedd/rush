/*
 * objectarrayflags.h - Declaration of the ObjectArrayFlags enum
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2007-2012 - Steffen Ott
 *
 */


#ifndef _RUSH_OBJECTARRAYFLAGS_H_
#define _RUSH_OBJECTARRAYFLAGS_H_


#include <rush/config.h>


namespace rush {

/**
 * \brief The ObjectArrayFlags enum, spezifies the behavior of the array.
 **/
enum class ObjectArrayFlags
{
    /// \brief Marks the array as read-only. Functions like Add, Remove, Clear will not work.
    ReadOnly,
    /// \brief Do not delete items only the array. Do not delete items even if free is true.
    DisableDelete
};

/**
 * \brief
 **/
inline ObjectArrayFlags operator|(ObjectArrayFlags a, ObjectArrayFlags b)
{
    return (static_cast<ObjectArrayFlags>(static_cast<int>(a) | static_cast<int>(b)));
}

/**
 * \brief
 **/
inline ObjectArrayFlags operator&(ObjectArrayFlags a, ObjectArrayFlags b)
{
    return (static_cast<ObjectArrayFlags>(static_cast<int>(a) & static_cast<int>(b)));
}



} // namespace rush

#endif // _RUSH_OBJECTARRAYFLAGS_H_


