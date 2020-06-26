/*
 * mathvariable.h - Declaration and implementation of MathVariable class
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2011-2012 - Steffen Ott
 *
 */



#ifndef _RUSH_MATHVARIABLE_H_
#define _RUSH_MATHVARIABLE_H_


namespace rush {


/**
 * \brief The MathVariable class is a container for a variable used in MathEvaluation.
 **/
class MathVariable
{
    private:
        MathVariable() {}
    public:
        MathVariable(const String& name, double value = 0.0d)
            : m_name(name), m_value(value) {}
        ~MathVariable() {}

        /**
         * \brief Returns the name of the variable.
         **/
        inline const String& GetName() const
        { return (m_name); }

        /**
         * \brief Returns the value of the variable.
         **/
        inline double GetValue() const
        { return (m_value); }

        /**
         * \brief Sets the value of the variable.
         **/
        inline void SetValue(double value)
        { m_value = value; }

    private:
        String m_name;
        double m_value;
};

} // namespace rush

#endif // _RUSH_MATHVARIABLE_H_


