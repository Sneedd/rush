/*
 * mathevaluation.h - Declaration of the MathEvaluation class
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2012 - Steffen Ott
 *
 */



#ifndef _RUSH_MATHEVALUATION_H_
#define _RUSH_MATHEVALUATION_H_


#include <rush/config.h>
#include <rush/string.h>
#include <rush/objectarray.h>
#include <rush/stringarray.h>
#include <rush/mathopcode.h>
#include <rush/mathtokenizer.h>

namespace rush {

// Forward declaration
class MathVariable;


/**
 * \brief The MathFunction abstract class can be used to add custom functions
 * to the MathEvaluation class. Simply inherit from this class provide a name,
 * the number of arguments in the constructor and implement the Evaluate()
 * Method. The last thing todo is set the function via SetFunction() in the
 * MathEvaluator class. The existing functions can be overridden if the function
 * has the same name and will be set by SetFunction().
 **/
class MathFunction
{
    private:
        MathFunction() {}
    public:
        MathFunction(const String& name, size_t args)
            : m_name(name), m_args(args) {}
        virtual ~MathFunction() {}

        inline const String& GetName() const
        { return (m_name); }

        inline size_t GetArgs() const
        { return (m_args); }

        virtual double Evaluate(double* values, size_t num) = 0;

    private:
        String m_name;
        size_t m_args;
};


/**
 * \brief The MathEvaluation class is a compiler and interpreter for mathematical code.
 * \remarks
 * The following predefined functions exists:
 * - pi(): Pi constant
 * - exp(x): Function e^x
 * - pow(a, b): Power a of b
 * - sqrt(x): Square root of x
 * - root(x, n): n - Root of x
 * - ln(x): Natural logarithmus
 * - log10(x): Logarithmus of x by base 10
 * - log(a, b): Logarithmus of a by base b
 * - fact(a): Factorial of a
 * - mod(a, b): Modulo of a / b
 * - ceil(a): Rounds up to the next interger
 * - floor(a): Rounds down to the next interger
 * - int(a): Interger part of the number
 * - frac(a): Fractional part of the number
 * - sin(x): Sinus of x
 * - cos(x): Cosinus of x
 * - tan(x): Tanges of x
 * - asin(x): Arcus sinus of x
 * - acos(x): Arcus cosinus of x
 * - atan(x): Arcus tanges of x
 **/
class MathEvaluation
{
	public:
        MathEvaluation();
        virtual ~MathEvaluation();

        void SetVariable(const String& name, double value);
        double GetVariable(const String& name) const;
        void ClearVariables();
        StringArray* GetVariableNames() const;

        void SetFunction(MathFunction* function);

        bool HasErrors() const;
        String GetErrorMessage() const;

        bool Compile(const String& function);
        bool Execute();

        #ifdef _RUSH_DEBUG_
        String GetTokenizerText(const String& statements) const;
        String GetOpcodeText() const;
        #endif

    private:
        bool HasHigherPriority(MathOpcodeType a, MathOpcodeType b);
        void PopInput(MathOpcodeArray* code, MathOpcodeDeque* inputs);
        void ResolveOperator(MathOpcodeArray* code, MathOpcodeDeque* operators, MathOpcodeDeque* inputs, bool checkPriority);
        MathOpcodeArray* CompileStep(MathTokenArray* tokens, size_t startIndex, size_t endIndex);
        int GetVariableIndex(const String& name) const;
        int GetFunctionIndex(const String& name) const;
        MathOpcode* CreateOpcode(MathToken* token);
        void OptimizeCode();

    private:
        ObjectArray<MathFunction>* m_functions;
        ObjectArray<MathOpcode>* m_opcodes;
        ObjectArray<MathVariable>* m_variables;
        StringArray* m_errors;
};


} // namespace rush

#endif // _RUSH_MATHEVALUATION_H_


