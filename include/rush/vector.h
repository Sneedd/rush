/*
 * vector.h - Declaration of the Vector typedefs
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2011-2012 - Steffen Ott
 *
 */



#ifndef _RUSH_VECTOR_H_
#define _RUSH_VECTOR_H_

#include <rush/vector2.h>
#include <rush/vector3.h>


namespace rush {

typedef Vector2<double> Vector2d;
typedef Vector2<float> Vector2f;
typedef Vector2<int> Vector2i;
typedef Vector3<double> Vector3d;
typedef Vector3<float> Vector3f;
typedef Vector3<int> Vector3i;


} // namespace rush


#endif // _RUSH_VECTOR_H_

