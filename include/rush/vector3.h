/*
 * vector3.h - Declaration and implementation of the Vector3 template class
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2011-2012 - Steffen Ott
 *
 */


#ifndef _RUSH_VECTOR3_H_
#define _RUSH_VECTOR3_H_

#include <rush/config.h>
#include <rush/macros.h>

namespace rush {


/**
 * \brief The Vector3 template class implements a three dimensional vector.
 * The coordinates x, y and z are public members. Note that most of the calculations
 * are only usefull for floating point types, integers can have wrong result.
 **/
template <typename Tvalue>
class Vector3
{
	public:
		Vector3();
		Vector3(const Vector3<Tvalue>& vector);
		Vector3(Tvalue x, Tvalue y, Tvalue z);
		virtual ~Vector3();

		Vector3<Tvalue>& operator=(const Vector3<Tvalue>& vector);
		bool operator==(const Vector3<Tvalue>& vector) const;
		bool operator!=(const Vector3<Tvalue>& vector) const;

		Vector3<Tvalue>& operator+=(const Vector3<Tvalue>& vector);
		Vector3<Tvalue>& operator+=(Tvalue value);
		Vector3<Tvalue>& operator-=(const Vector3<Tvalue>& vector);
		Vector3<Tvalue>& operator-=(Tvalue value);
		Vector3<Tvalue>& operator*=(const Vector3<Tvalue>& vector);
		Vector3<Tvalue>& operator*=(Tvalue value);
		Vector3<Tvalue>& operator/=(const Vector3<Tvalue>& vector);
		Vector3<Tvalue>& operator/=(Tvalue value);
		Vector3<Tvalue> operator+(const Vector3<Tvalue>& vector);
		Vector3<Tvalue> operator+(Tvalue value);
		Vector3<Tvalue> operator-(const Vector3<Tvalue>& vector);
		Vector3<Tvalue> operator-(Tvalue value);
		Vector3<Tvalue> operator*(const Vector3<Tvalue>& vector);
		Vector3<Tvalue> operator*(Tvalue value);
		Vector3<Tvalue> operator/(const Vector3<Tvalue>& vector);
		Vector3<Tvalue> operator/(Tvalue value);

		bool IsNear(Tvalue x, Tvalue y, Tvalue z, Tvalue margin) const;
		bool IsNear(const Vector3<Tvalue>& p, Tvalue margin) const;

        Tvalue GetLength() const;
        Tvalue GetAngleX() const;
        Tvalue GetAngleY() const;
        Tvalue GetAngleZ() const;
        Tvalue GetDistance(const Vector3<Tvalue>& vector) const;

        void Normalize();
		void Rotate(Tvalue angle);
		void Translate(Tvalue x, Tvalue y, Tvalue z);
		void Translate(const Vector3<Tvalue>& vector);
		void Scale(const Vector3<Tvalue>& vector);
		void Scale(Tvalue x, Tvalue y, Tvalue z);
		void Scale(Tvalue value);

        void Set(Tvalue x, Tvalue y, Tvalue z);

	public:
		Tvalue x;
		Tvalue y;
		Tvalue z;
};



//----------------------------------------------------------------
template <typename Tvalue>
Vector3<Tvalue>::Vector3()
/**
 * \brief Standardconstructor, initializes the Vector3 class.
 **/
{
    x = 0;
    y = 0;
    z = 0;
}


//----------------------------------------------------------------
template <typename Tvalue>
Vector3<Tvalue>::Vector3(const Vector3<Tvalue>& vector)
/**
 * \brief Copyconstructor, initializes the Vector3 class with the given vector.
 * \param vector Vector to copy.
 **/
{
    x = vector.x;
    y = vector.y;
    z = vector.z;
}


//----------------------------------------------------------------
template <typename Tvalue>
Vector3<Tvalue>::Vector3(Tvalue xn, Tvalue yn, Tvalue zn)
/**
 * \brief Constructor, initializes the Vector3 object with the given coordinates.
 * \param xn X coordinate.
 * \param yn Y coordinate.
 * \param zn Z coordinate.
 **/
{
    x = xn;
    y = yn;
    z = zn;
}


//----------------------------------------------------------------
template <typename Tvalue>
Vector3<Tvalue>::~Vector3()
/**
 * \brief Destructor.
 **/
{
}


//----------------------------------------------------------------
template <typename Tvalue>
inline Vector3<Tvalue>& Vector3<Tvalue>::operator=(const Vector3<Tvalue>& vector)
/**
 * \brief Assignmentoperator, assigns the given vector to this vector.
 * \param vector Assign vector.
 * \return This vector.
 **/
{
    x = vector.x;
    y = vector.y;
    z = vector.z;
}


//----------------------------------------------------------------
template <typename Tvalue>
inline bool Vector3<Tvalue>::operator==(const Vector3<Tvalue>& vector) const
/**
 * \brief Equal comparison operator, tests if the given vector and this vector are equal.
 * \param vector Vector.
 * \return True, if the vectors are equal; otherwise false.
 **/
{
    return (x == vector.x && y == vector.y, && z == vector.z);
}


//----------------------------------------------------------------
template <typename Tvalue>
inline bool Vector3<Tvalue>::operator!=(const Vector3<Tvalue>& vector) const
/**
 * \brief Not equal comparison operator, tests if the given vector and this vector are not equal.
 * \param vector Vector.
 * \return True, if the vectors are not equal; otherwise false.
 **/
{
    return (x != vector.x && y != vector.y && z != vector.z);
}


//----------------------------------------------------------------
template <typename Tvalue>
inline Vector3<Tvalue>& Vector3<Tvalue>::operator+=(const Vector3<Tvalue>& vector)
/**
 * \brief Add assigment operator, adds the given vector to this vector.
 * \param vector Vector.
 * \return This vector.
 **/
{
    x += vector.x;
    y += vector.y;
    z += vector.z;
    return (*this);
}


//----------------------------------------------------------------
template <typename Tvalue>
inline Vector3<Tvalue>& Vector3<Tvalue>::operator+=(Tvalue value)
/**
 * \brief Add assigment operator, adds the given value to this vector.
 * \param value Value.
 * \return This vector.
 **/
{
    x += value;
    y += value;
    z += value;
    return (*this);
}


//----------------------------------------------------------------
template <typename Tvalue>
inline Vector3<Tvalue>& Vector3<Tvalue>::operator-=(const Vector3<Tvalue>& vector)
/**
 * \brief Substract assigment operator, substacts the given vector from this vector.
 * \param vector Vector.
 * \return This vector.
 **/
{
    x -= vector.x;
    y -= vector.y;
    z -= vector.z;
    return (*this);
}


//----------------------------------------------------------------
template <typename Tvalue>
inline Vector3<Tvalue>& Vector3<Tvalue>::operator-=(Tvalue value)
/**
 * \brief Substract assigment operator, substacts the given value from this vector.
 * \param value Value.
 * \return This vector.
 **/
{
    x -= value;
    y -= value;
    z -= value;
    return (*this);
}


//----------------------------------------------------------------
template <typename Tvalue>
inline Vector3<Tvalue>& Vector3<Tvalue>::operator*=(const Vector3<Tvalue>& vector)
/**
 * \brief Multiplicate assigment operator, multiplicates the given vector with this vector.
 * \param vector Vector.
 * \return This vector.
 **/
{
    x *= vector.x;
    y *= vector.y;
    z *= vector.z;
    return (*this);
}

//----------------------------------------------------------------
template <typename Tvalue>
inline Vector3<Tvalue>& Vector3<Tvalue>::operator*=(Tvalue value)
/**
 * \brief Multiplicate assigment operator, multiplicates the given value with this vector.
 * \param value Value.
 * \return This vector.
 **/
{
    x *= value;
    y *= value;
    z *= value;
    return (*this);
}


//----------------------------------------------------------------
template <typename Tvalue>
inline Vector3<Tvalue>& Vector3<Tvalue>::operator/=(const Vector3<Tvalue>& vector)
/**
 * \brief Division assigment operator, divides the given vector with this vector.
 * \param vector Vector.
 * \return This vector.
 **/
{
    x /= vector.x;
    y /= vector.y;
    z /= vector.z;
    return (*this);
}


//----------------------------------------------------------------
template <typename Tvalue>
inline Vector3<Tvalue>& Vector3<Tvalue>::operator/=(Tvalue value)
/**
 * \brief Division assigment operator, divides the given value with this vector.
 * \param value Value.
 * \return This vector.
 **/
{
    x /= value;
    y /= value;
    z /= value;
    return (*this);
}


//----------------------------------------------------------------
template <typename Tvalue>
inline Vector3<Tvalue> Vector3<Tvalue>::operator+(const Vector3<Tvalue>& vector)
/**
 * \brief Add operator, adds the given vector to this vector and
 * returns the result.
 * \param vector Vector.
 * \return Result vector.
 **/
{
    Vector3<Tvalue> result;
    result.x = x + vector.x;
    result.y = y + vector.y;
    result.z = z + vector.z;
    return (result);
}



//----------------------------------------------------------------
template <typename Tvalue>
inline Vector3<Tvalue> Vector3<Tvalue>::operator+(Tvalue value)
/**
 * \brief Add operator, adds the given value to this vector and
 * returns the result.
 * \param value Value.
 * \return Result vector.
 **/
{
    Vector3<Tvalue> result;
    result.x = x + value;
    result.y = y + value;
    result.z = z + value;
    return (result);
}



//----------------------------------------------------------------
template <typename Tvalue>
inline Vector3<Tvalue> Vector3<Tvalue>::operator-(const Vector3<Tvalue>& vector)
/**
 * \brief Substract operator, substacts the given vector from this vector
 * and return the result.
 * \param vector Vector.
 * \return Result vector.
 **/
{
    Vector3<Tvalue> result;
    result.x = x - vector.x;
    result.y = y - vector.y;
    result.z = z - vector.z;
    return (result);
}


//----------------------------------------------------------------
template <typename Tvalue>
inline Vector3<Tvalue> Vector3<Tvalue>::operator-(Tvalue value)
/**
 * \brief Substract operator, substacts the given value from this vector
 * and returns the result.
 * \param value Value.
 * \return Result vector.
 **/
{
    Vector3<Tvalue> result;
    result.x = x - value;
    result.y = y - value;
    result.z = z - value;
    return (result);
}


//----------------------------------------------------------------
template <typename Tvalue>
inline Vector3<Tvalue> Vector3<Tvalue>::operator*(const Vector3<Tvalue>& vector)
/**
 * \brief Multiplicate operator, multiplicates the given vector with this vector and
 * returns the result.
 * \param vector Vector.
 * \return Result vector.
 **/
{
    Vector3<Tvalue> result;
    result.x = x * vector.x;
    result.y = y * vector.y;
    result.z = z * vector.z;
    return (result);
}


//----------------------------------------------------------------
template <typename Tvalue>
inline Vector3<Tvalue> Vector3<Tvalue>::operator*(Tvalue value)
/**
 * \brief Multiplicate operator, multiplicates the given value with this vector
 * and returns the result.
 * \param value Value.
 * \return Result vector.
 **/
{
    Vector3<Tvalue> result;
    result.x = x * value;
    result.y = y * value;
    result.z = z * value;
    return (result);
}



//----------------------------------------------------------------
template <typename Tvalue>
inline Vector3<Tvalue> Vector3<Tvalue>::operator/(const Vector3<Tvalue>& vector)
/**
 * \brief Division operator, divides the given vector with this vector and
 * returns the result.
 * \param vector Vector.
 * \return Result vector.
 **/
{
    Vector3<Tvalue> result;
    result.x = x / vector.x;
    result.y = y / vector.y;
    result.z = z / vector.z;
    return (result);
}


//----------------------------------------------------------------
template <typename Tvalue>
inline Vector3<Tvalue> Vector3<Tvalue>::operator/(Tvalue value)
/**
 * \brief Division operator, divides the given value with this vector and
 * returns the result.
 * \param value Value.
 * \return Result vector.
 **/
{
    Vector3<Tvalue> result;
    result.x = x / value;
    result.y = y / value;
    result.z = z / value;
    return (result);
}


//----------------------------------------------------------------
template <typename Tvalue>
inline bool Vector3<Tvalue>::IsNear(Tvalue xn, Tvalue yn, Tvalue zn, Tvalue margin) const
/**
 * \brief Tests if the given coordinates are near this vector. Uses the margin
 * to create a theoretically box for the near test.
 * \param xn X coordinate.
 * \param yn Y coordinate.
 * \param zn Z coordinate.
 * \param margin Margin in all four directions.
 * \return True, if the given coordinates are in the thoretical box; otherwise false.
 **/
{
    return (x >= xn-margin && x <= xn+margin &&
            y >= yn-margin && y <= yn+margin &&
            z >= zn-margin && z <= zn+margin);
}


//----------------------------------------------------------------
template <typename Tvalue>
inline bool Vector3<Tvalue>::IsNear(const Vector3<Tvalue>& vector, Tvalue margin) const
/**
 * \brief Tests if the given vector is near this vector. Uses the margin
 * to create a theoretically box for the near test.
 * \param vector Vector.
 * \param margin Margin in all four directions.
 * \return True, if the given vector is in the thoretical box; otherwise false.
 **/
{
    return (x >= vector.x-margin && x <= vector.x+margin &&
            y >= vector.y-margin && y <= vector.y+margin &&
            z >= vector.z-margin && z <= vector.z+margin);
}


//----------------------------------------------------------------
template <typename Tvalue>
inline Tvalue Vector3<Tvalue>::GetLength() const
/**
 * \brief Calculates the length of the vector.
 * \return Vector length.
 **/
{
    return ((Tvalue)sqrt(x*x + y*y + z*z));
}


//----------------------------------------------------------------
template <typename Tvalue>
inline Tvalue Vector3<Tvalue>::GetAngleX() const
/**
 * \brief Calculates the angle of the vector, from the x-Axis.
 * \return Angle.
 **/
{
    return ((Tvalue)acos(x/sqrt(x*x + y*y + z*z)));
}



//----------------------------------------------------------------
template <typename Tvalue>
inline Tvalue Vector3<Tvalue>::GetAngleY() const
/**
 * \brief Calculates the angle of the vector, from the y-Axis.
 * \return Angle.
 **/
{
    return ((Tvalue)acos(y/sqrt(x*x + y*y + z*z)));
}


//----------------------------------------------------------------
template <typename Tvalue>
inline Tvalue Vector3<Tvalue>::GetDistance(const Vector3<Tvalue>& vector) const
/**
 * \brief Calculates the distance between this and the given vector.
 * \param vector Vector.
 * \return Distance.
 **/
{
    Tvalue xdiff = vector.x - x;
    Tvalue ydiff = vector.y - y;
    Tvalue zdiff = vector.z - z;
    return ((Tvalue)sqrt(xdiff*xdiff + ydiff*ydiff + zdiff*zdiff));
}


//----------------------------------------------------------------
template <typename Tvalue>
inline void Vector3<Tvalue>::Normalize()
/**
 * \brief Normalizes the vector. Doesn't change the direction, only
 * changes the length to 1.
 **/
{
    double length = sqrt(x*x + y*y + z*z);
    x /= length;
    y /= length;
    z /= length;
}


//----------------------------------------------------------------
template <typename Tvalue>
inline void Vector3<Tvalue>::Rotate(Tvalue angle)
/**
 * \brief Rotates the vector about the given angle.
 * \param angle Angle.
 **/
{
    RUSH_NOT_IMPLEMENTED_YET();
}


//----------------------------------------------------------------
template <typename Tvalue>
inline void Vector3<Tvalue>::Translate(Tvalue xn, Tvalue yn, Tvalue zn)
/**
 * \brief Translates the vector by the given values.
 * \param xn Transformation in X.
 * \param yn Transformation in Y.
 * \param zn Transformation in Z.
 **/
{
    x += xn;
    y += yn;
    z += zn;
}


//----------------------------------------------------------------
template <typename Tvalue>
inline void Vector3<Tvalue>::Translate(const Vector3<Tvalue>& vector)
/**
 * \brief Translates the vector by the given vector.
 * \param vector Vector.
 **/
{
    x += vector.x;
    y += vector.y;
    z += vector.z;
}

//----------------------------------------------------------------
template <typename Tvalue>
inline void Vector3<Tvalue>::Scale(const Vector3<Tvalue>& vector)
/**
 * \brief Scales the vector by the given vector.
 * \param vector Vector
 **/
{
    x *= vector.x;
    y *= vector.y;
    z *= vector.z;
}


//----------------------------------------------------------------
template <typename Tvalue>
inline void Vector3<Tvalue>::Scale(Tvalue xn, Tvalue yn, Tvalue zn)
/**
 * \brief Scales the vector by the given values.
 * \param xn Scaling value for x.
 * \param yn Scaling value for y.
 * \param zn Scaling value for z.
 **/
{
    x *= xn;
    y *= yn;
    z *= zn;
}


//----------------------------------------------------------------
template <typename Tvalue>
inline void Vector3<Tvalue>::Scale(Tvalue value)
/**
 * \brief Scales the vector by the given value.
 * \param value Scaling value.
 **/
{
    x *= value;
    y *= value;
    z *= value;
}



//----------------------------------------------------------------
template <typename Tvalue>
inline void Vector3<Tvalue>::Set(Tvalue xn, Tvalue yn, Tvalue zn)
/**
 * \brief Sets the coordinates of the vector.
 * \param xn X coordinate.
 * \param yn Y coordinate.
 * \param zn Z coordinate.
 **/
{
    x = xn;
    y = yn;
    z = zn;
}


} // namespace rush


#endif // _RUSH_POINT_H_


