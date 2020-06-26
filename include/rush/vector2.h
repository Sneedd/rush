/*
 * vector2.h - Declaration and implementation of the Vector2 template class
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2011-2012 - Steffen Ott
 *
 */


#ifndef _RUSH_VECTOR2_H_
#define _RUSH_VECTOR2_H_

#include <rush/config.h>


namespace rush {


/**
 * \brief The Vector2 template class implements a two dimensional vector.
 * The coordinates x and y are public members. Note that most of the calculations
 * are only usefull for floating point types, integers can have wrong result.
 **/
template <typename Tvalue>
class Vector2
{
	public:
		Vector2();
		Vector2(const Vector2<Tvalue>& vector);
		Vector2(Tvalue x, Tvalue y);
		virtual ~Vector2();

		Vector2<Tvalue>& operator=(const Vector2<Tvalue>& vector);
		bool operator==(const Vector2<Tvalue>& vector) const;
		bool operator!=(const Vector2<Tvalue>& vector) const;

		Vector2<Tvalue>& operator+=(const Vector2<Tvalue>& vector);
		Vector2<Tvalue>& operator+=(Tvalue value);
		Vector2<Tvalue>& operator-=(const Vector2<Tvalue>& vector);
		Vector2<Tvalue>& operator-=(Tvalue value);
		Vector2<Tvalue>& operator*=(const Vector2<Tvalue>& vector);
		Vector2<Tvalue>& operator*=(Tvalue value);
		Vector2<Tvalue>& operator/=(const Vector2<Tvalue>& vector);
		Vector2<Tvalue>& operator/=(Tvalue value);
		Vector2<Tvalue> operator+(const Vector2<Tvalue>& vector);
		Vector2<Tvalue> operator+(Tvalue value);
		Vector2<Tvalue> operator-(const Vector2<Tvalue>& vector);
		Vector2<Tvalue> operator-(Tvalue value);
		Vector2<Tvalue> operator*(const Vector2<Tvalue>& vector);
		Vector2<Tvalue> operator*(Tvalue value);
		Vector2<Tvalue> operator/(const Vector2<Tvalue>& vector);
		Vector2<Tvalue> operator/(Tvalue value);

		bool IsNear(Tvalue x, Tvalue y, Tvalue margin) const;
		bool IsNear(const Vector2<Tvalue>& p, Tvalue margin) const;

        Tvalue GetLength() const;
        Tvalue GetAngleX() const;
        Tvalue GetAngleY() const;
        Tvalue GetDistance(const Vector2<Tvalue>& vector) const;

        void Normalize();
		void Rotate(Tvalue angle);
		void Translate(Tvalue x, Tvalue y);
		void Translate(const Vector2<Tvalue>& vector);
		void Scale(const Vector2<Tvalue>& vector);
		void Scale(Tvalue x, Tvalue y);
		void Scale(Tvalue value);

        void Set(Tvalue xn, Tvalue yn);

	public:
		Tvalue x;
		Tvalue y;
};



//----------------------------------------------------------------
template <typename Tvalue>
Vector2<Tvalue>::Vector2()
/**
 * \brief Standardconstructor, initializes the Vector2 class.
 **/
{
    x = 0;
    y = 0;
}


//----------------------------------------------------------------
template <typename Tvalue>
Vector2<Tvalue>::Vector2(const Vector2<Tvalue>& vector)
/**
 * \brief Copyconstructor, initializes the Vector2 class with the given vector.
 * \param vector Vector to copy.
 **/
{
    x = vector.x;
    y = vector.y;
}


//----------------------------------------------------------------
template <typename Tvalue>
Vector2<Tvalue>::Vector2(Tvalue xn, Tvalue yn)
/**
 * \brief Constructor, initializes the Vector2 object with the given coordinates.
 * \param xn X coordinate.
 * \param yn Y coordinate.
 **/
{
    x = xn;
    y = yn;
}


//----------------------------------------------------------------
template <typename Tvalue>
Vector2<Tvalue>::~Vector2()
/**
 * \brief Destructor.
 **/
{
}


//----------------------------------------------------------------
template <typename Tvalue>
inline Vector2<Tvalue>& Vector2<Tvalue>::operator=(const Vector2<Tvalue>& vector)
/**
 * \brief Assignmentoperator, assigns the given vector to this vector.
 * \param vector Assign vector.
 * \return This vector.
 **/
{
    x = vector.x;
    y = vector.y;
}


//----------------------------------------------------------------
template <typename Tvalue>
inline bool Vector2<Tvalue>::operator==(const Vector2<Tvalue>& vector) const
/**
 * \brief Equal comparison operator, tests if the given vector and this vector are equal.
 * \param vector Vector.
 * \return True, if the vectors are equal; otherwise false.
 **/
{
    return (x == vector.x && y == vector.y);
}


//----------------------------------------------------------------
template <typename Tvalue>
inline bool Vector2<Tvalue>::operator!=(const Vector2<Tvalue>& vector) const
/**
 * \brief Not equal comparison operator, tests if the given vector and this vector are not equal.
 * \param vector Vector.
 * \return True, if the vectors are not equal; otherwise false.
 **/
{
    return (x != vector.x && y != vector.y);
}


//----------------------------------------------------------------
template <typename Tvalue>
inline Vector2<Tvalue>& Vector2<Tvalue>::operator+=(const Vector2<Tvalue>& vector)
/**
 * \brief Add assigment operator, adds the given vector to this vector.
 * \param vector Vector.
 * \return This vector.
 **/
{
    x += vector.x;
    y += vector.y;
    return (*this);
}


//----------------------------------------------------------------
template <typename Tvalue>
inline Vector2<Tvalue>& Vector2<Tvalue>::operator+=(Tvalue value)
/**
 * \brief Add assigment operator, adds the given value to this vector.
 * \param value Value.
 * \return This vector.
 **/
{
    x += value;
    y += value;
    return (*this);
}


//----------------------------------------------------------------
template <typename Tvalue>
inline Vector2<Tvalue>& Vector2<Tvalue>::operator-=(const Vector2<Tvalue>& vector)
/**
 * \brief Substract assigment operator, substacts the given vector from this vector.
 * \param vector Vector.
 * \return This vector.
 **/
{
    x -= vector.x;
    y -= vector.y;
    return (*this);
}


//----------------------------------------------------------------
template <typename Tvalue>
inline Vector2<Tvalue>& Vector2<Tvalue>::operator-=(Tvalue value)
/**
 * \brief Substract assigment operator, substacts the given value from this vector.
 * \param value Value.
 * \return This vector.
 **/
{
    x -= value;
    y -= value;
    return (*this);
}


//----------------------------------------------------------------
template <typename Tvalue>
inline Vector2<Tvalue>& Vector2<Tvalue>::operator*=(const Vector2<Tvalue>& vector)
/**
 * \brief Multiplicate assigment operator, multiplicates the given vector with this vector.
 * \param vector Vector.
 * \return This vector.
 **/
{
    x *= vector.x;
    y *= vector.y;
    return (*this);
}

//----------------------------------------------------------------
template <typename Tvalue>
inline Vector2<Tvalue>& Vector2<Tvalue>::operator*=(Tvalue value)
/**
 * \brief Multiplicate assigment operator, multiplicates the given value with this vector.
 * \param value Value.
 * \return This vector.
 **/
{
    x *= value;
    y *= value;
    return (*this);
}


//----------------------------------------------------------------
template <typename Tvalue>
inline Vector2<Tvalue>& Vector2<Tvalue>::operator/=(const Vector2<Tvalue>& vector)
/**
 * \brief Division assigment operator, divides the given vector with this vector.
 * \param vector Vector.
 * \return This vector.
 **/
{
    x /= vector.x;
    y /= vector.y;
    return (*this);
}


//----------------------------------------------------------------
template <typename Tvalue>
inline Vector2<Tvalue>& Vector2<Tvalue>::operator/=(Tvalue value)
/**
 * \brief Division assigment operator, divides the given value with this vector.
 * \param value Value.
 * \return This vector.
 **/
{
    x /= value;
    y /= value;
    return (*this);
}


//----------------------------------------------------------------
template <typename Tvalue>
inline Vector2<Tvalue> Vector2<Tvalue>::operator+(const Vector2<Tvalue>& vector)
/**
 * \brief Add operator, adds the given vector to this vector and
 * returns the result.
 * \param vector Vector.
 * \return Result vector.
 **/
{
    Vector2<Tvalue> result;
    result.x = x + vector.x;
    result.y = y + vector.y;
    return (result);
}



//----------------------------------------------------------------
template <typename Tvalue>
inline Vector2<Tvalue> Vector2<Tvalue>::operator+(Tvalue value)
/**
 * \brief Add operator, adds the given value to this vector and
 * returns the result.
 * \param value Value.
 * \return Result vector.
 **/
{
    Vector2<Tvalue> result;
    result.x = x + value;
    result.y = y + value;
    return (result);
}



//----------------------------------------------------------------
template <typename Tvalue>
inline Vector2<Tvalue> Vector2<Tvalue>::operator-(const Vector2<Tvalue>& vector)
/**
 * \brief Substract operator, substacts the given vector from this vector
 * and return the result.
 * \param vector Vector.
 * \return Result vector.
 **/
{
    Vector2<Tvalue> result;
    result.x = x - vector.x;
    result.y = y - vector.y;
    return (result);
}


//----------------------------------------------------------------
template <typename Tvalue>
inline Vector2<Tvalue> Vector2<Tvalue>::operator-(Tvalue value)
/**
 * \brief Substract operator, substacts the given value from this vector
 * and returns the result.
 * \param value Value.
 * \return Result vector.
 **/
{
    Vector2<Tvalue> result;
    result.x = x - value;
    result.y = y - value;
    return (result);
}


//----------------------------------------------------------------
template <typename Tvalue>
inline Vector2<Tvalue> Vector2<Tvalue>::operator*(const Vector2<Tvalue>& vector)
/**
 * \brief Multiplicate operator, multiplicates the given vector with this vector and
 * returns the result.
 * \param vector Vector.
 * \return Result vector.
 **/
{
    Vector2<Tvalue> result;
    result.x = x * vector.x;
    result.y = y * vector.y;
    return (result);
}


//----------------------------------------------------------------
template <typename Tvalue>
inline Vector2<Tvalue> Vector2<Tvalue>::operator*(Tvalue value)
/**
 * \brief Multiplicate operator, multiplicates the given value with this vector
 * and returns the result.
 * \param value Value.
 * \return Result vector.
 **/
{
    Vector2<Tvalue> result;
    result.x = x * value;
    result.y = y * value;
    return (result);
}



//----------------------------------------------------------------
template <typename Tvalue>
inline Vector2<Tvalue> Vector2<Tvalue>::operator/(const Vector2<Tvalue>& vector)
/**
 * \brief Division operator, divides the given vector with this vector and
 * returns the result.
 * \param vector Vector.
 * \return Result vector.
 **/
{
    Vector2<Tvalue> result;
    result.x = x / vector.x;
    result.y = y / vector.y;
    return (result);
}


//----------------------------------------------------------------
template <typename Tvalue>
inline Vector2<Tvalue> Vector2<Tvalue>::operator/(Tvalue value)
/**
 * \brief Division operator, divides the given value with this vector and
 * returns the result.
 * \param value Value.
 * \return Result vector.
 **/
{
    Vector2<Tvalue> result;
    result.x = x / value;
    result.y = y / value;
    return (result);
}


//----------------------------------------------------------------
template <typename Tvalue>
inline bool Vector2<Tvalue>::IsNear(Tvalue xn, Tvalue yn, Tvalue margin) const
/**
 * \brief Tests if the given coordinates are near this vector. Uses the margin
 * to create a theoretically box for the near test.
 * \param xn X coordinate.
 * \param yn Y coordinate.
 * \param margin Margin in all four directions.
 * \return True, if the given coordinates are in the thoretical box; otherwise false.
 **/
{
    return (x >= xn-margin && x <= xn+margin && y >= yn-margin && y <= yn+margin);
}


//----------------------------------------------------------------
template <typename Tvalue>
inline bool Vector2<Tvalue>::IsNear(const Vector2<Tvalue>& vector, Tvalue margin) const
/**
 * \brief Tests if the given vector is near this vector. Uses the margin
 * to create a theoretically box for the near test.
 * \param vector Vector.
 * \param margin Margin in all four directions.
 * \return True, if the given vector is in the thoretical box; otherwise false.
 **/
{
    return (x >= vector.x-margin && x <= vector.x+margin && y >= vector.y-margin && y <= vector.y+margin);
}


//----------------------------------------------------------------
template <typename Tvalue>
inline Tvalue Vector2<Tvalue>::GetLength() const
/**
 * \brief Calculates the length of the vector.
 * \return Vector length.
 **/
{
    return ((Tvalue)sqrt(x*x + y*y));
}


//----------------------------------------------------------------
template <typename Tvalue>
inline Tvalue Vector2<Tvalue>::GetAngleX() const
/**
 * \brief Calculates the angle of the vector, from the x-Axis.
 * \return Angle.
 **/
{
    return ((Tvalue)acos(x/sqrt(x*x + y*y)));
}



//----------------------------------------------------------------
template <typename Tvalue>
inline Tvalue Vector2<Tvalue>::GetAngleY() const
/**
 * \brief Calculates the angle of the vector, from the y-Axis.
 * \return Angle.
 **/
{
    return ((Tvalue)acos(y/sqrt(x*x + y*y)));
}


//----------------------------------------------------------------
template <typename Tvalue>
inline Tvalue Vector2<Tvalue>::GetDistance(const Vector2<Tvalue>& vector) const
/**
 * \brief Calculates the distance between this and the given vector.
 * \param vector Vector.
 * \return Distance.
 **/
{
    Tvalue xdiff = vector.x - x;
    Tvalue ydiff = vector.y - y;
    return ((Tvalue)sqrt(xdiff*xdiff + ydiff*ydiff));
}


//----------------------------------------------------------------
template <typename Tvalue>
inline void Vector2<Tvalue>::Normalize()
/**
 * \brief Normalizes the vector. Doesn't change the direction, only
 * changes the length to 1.
 **/
{
    double length = sqrt(x*x + y*y);
    x /= length;
    y /= length;
}


//----------------------------------------------------------------
template <typename Tvalue>
inline void Vector2<Tvalue>::Rotate(Tvalue angle)
/**
 * \brief Rotates the vector about the given angle.
 * \param angle Angle.
 **/
{
    Tvalue nx = x*cos(angle) - y*sin(angle);
    y = x*sin(angle) + y*cos(angle);
    x = nx;
}


//----------------------------------------------------------------
template <typename Tvalue>
inline void Vector2<Tvalue>::Translate(Tvalue xn, Tvalue yn)
/**
 * \brief Translates the vector by the given values.
 * \param xn Transformation in X.
 * \param yn Transformation in Y.
 **/
{
    x += xn;
    y += yn;
}


//----------------------------------------------------------------
template <typename Tvalue>
inline void Vector2<Tvalue>::Translate(const Vector2<Tvalue>& vector)
/**
 * \brief Translates the vector by the given vector.
 * \param vector Vector.
 **/
{
    x += vector.x;
    y += vector.y;
}

//----------------------------------------------------------------
template <typename Tvalue>
inline void Vector2<Tvalue>::Scale(const Vector2<Tvalue>& vector)
/**
 * \brief Scales the vector by the given vector.
 * \param vector Vector
 **/
{
    x *= vector.x;
    y *= vector.y;
}


//----------------------------------------------------------------
template <typename Tvalue>
inline void Vector2<Tvalue>::Scale(Tvalue xn, Tvalue yn)
/**
 * \brief Scales the vector by the given values.
 * \param xn Scaling value for x.
 * \param yn Scaling value for y.
 **/
{
    x *= xn;
    y *= yn;
}


//----------------------------------------------------------------
template <typename Tvalue>
inline void Vector2<Tvalue>::Scale(Tvalue value)
/**
 * \brief Scales the vector by the given value.
 * \param value Scaling value.
 **/
{
    x *= value;
    y *= value;
}


//----------------------------------------------------------------
template <typename Tvalue>
inline void Vector2<Tvalue>::Set(Tvalue xn, Tvalue yn)
/**
 * \brief Sets the coordinates of the vector.
 * \param xn X coordinate.
 * \param yn Y coordinate.
 **/
{
    x = xn;
    y = yn;
}



} // namespace rush


#endif // _RUSH_POINT_H_

