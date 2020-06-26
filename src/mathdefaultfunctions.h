/*
 * mathdefaultfunction.h - Declaration and implementation of default MathFunction classes
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2011-2012 - Steffen Ott
 *
 */


#ifndef _RUSH_MATHDEFAULTFUNCTIONS_H_
#define _RUSH_MATHDEFAULTFUNCTIONS_H_


#include <rush/mathevaluation.h>
#include <math.h>

namespace rush {


class MathPiFunction : public MathFunction
{
    public:
        MathPiFunction() : MathFunction(_T("pi"), 0) {}

        virtual double Evaluate(double* values, size_t num)
        {
            return (M_PI);
        }
};

class MathAbsFunction : public MathFunction
{
    public:
        MathAbsFunction() : MathFunction(_T("abs"), 1) {}

        virtual double Evaluate(double* values, size_t num)
        {
            return (values[0] < 0 ? -values[0] : values[0]);
        }
};


class MathExpFunction : public MathFunction
{
    public:
        MathExpFunction() : MathFunction(_T("exp"), 1) {}

        virtual double Evaluate(double* values, size_t num)
        {
            return (exp(values[0]));
        }
};



class MathPowFunction : public MathFunction
{
    public:
        MathPowFunction() : MathFunction(_T("pow"), 2) {}

        virtual double Evaluate(double* values, size_t num)
        {
            return (pow(values[0], values[1]));
        }
};



class MathSqrtFunction : public MathFunction
{
    public:
        MathSqrtFunction() : MathFunction(_T("sqrt"), 1) {}

        virtual double Evaluate(double* values, size_t num)
        {
            return (sqrt(values[0]));
        }
};


class MathRootFunction : public MathFunction
{
    public:
        MathRootFunction() : MathFunction(_T("root"), 2) {}

        virtual double Evaluate(double* values, size_t num)
        {
            // NOTE: ln(root(u,n)) == (1/n)*ln(u)
            return (exp(1/values[1]*log(values[0])));
        }
};


class MathLnFunction : public MathFunction
{
    public:
        MathLnFunction() : MathFunction(_T("ln"), 1) {}

        virtual double Evaluate(double* values, size_t num)
        {
            return (log(values[0]));
        }
};



class MathLog10Function : public MathFunction
{
    public:
        MathLog10Function() : MathFunction(_T("log10"), 1) {}

        virtual double Evaluate(double* values, size_t num)
        {
            return (log10(values[0]));
        }
};


class MathLogFunction : public MathFunction
{
    public:
        MathLogFunction() : MathFunction(_T("log"), 2) {}

        virtual double Evaluate(double* values, size_t num)
        {
            return (log(values[0])/log(values[1]));
        }
};


class MathFactFunction : public MathFunction
{
    public:
        MathFactFunction() : MathFunction(_T("fact"), 1) {}

        virtual double Evaluate(double* values, size_t num)
        {
            // NOTE: Only natural numbers
            double value = floor(values[0]);
            if (values[0] == 0) return (1);
            double result = 1.0f;
            for (double i=2; i<=value; i += 1.0d)
            {
                result *= i;
            }
            return (result);
        }
};



class MathModFunction : public MathFunction
{
    public:
        MathModFunction() : MathFunction(_T("mod"), 2) {}

        virtual double Evaluate(double* values, size_t num)
        {
            return (fmod(values[0], values[1]));
        }
};


class MathCeilFunction : public MathFunction
{
    public:
        MathCeilFunction() : MathFunction(_T("ceil"), 1) {}

        virtual double Evaluate(double* values, size_t num)
        {
            return (ceil(values[0]));
        }
};


class MathFloorFunction : public MathFunction
{
    public:
        MathFloorFunction() : MathFunction(_T("floor"), 1) {}

        virtual double Evaluate(double* values, size_t num)
        {
            return (floor(values[0]));
        }
};




class MathFracFunction : public MathFunction
{
    public:
        MathFracFunction() : MathFunction(_T("frac"), 1) {}

        virtual double Evaluate(double* values, size_t num)
        {
            double intpart = 0.0d;
            return (modf(values[0], &intpart));
        }
};



class MathIntFunction : public MathFunction
{
    public:
        MathIntFunction() : MathFunction(_T("int"), 1) {}

        virtual double Evaluate(double* values, size_t num)
        {
            double intpart = 0.0d;
            modf(values[0], &intpart);
            return (intpart);
        }
};



class MathSinFunction : public MathFunction
{
    public:
        MathSinFunction() : MathFunction(_T("sin"), 1) {}

        virtual double Evaluate(double* values, size_t num)
        { return (sin(values[0])); }
};


class MathCosFunction : public MathFunction
{
    public:
        MathCosFunction() : MathFunction(_T("cos"), 1) {}

        virtual double Evaluate(double* values, size_t num)
        { return (cos(values[0])); }
};



class MathTanFunction : public MathFunction
{
    public:
        MathTanFunction() : MathFunction(_T("tan"), 1) {}

        virtual double Evaluate(double* values, size_t num)
        { return (tan(values[0])); }
};




} // namespace rush

#endif // _RUSH_MATHDEFAULTFUNCTIONS_H_
