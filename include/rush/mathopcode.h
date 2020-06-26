/*
 * mathopcode.h - Declaration of the MathOpcode class and typedefs
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2012 - Steffen Ott
 *
 */



#ifndef _RUSH_MATHOPCODE_H_
#define _RUSH_MATHOPCODE_H_


#include <rush/config.h>
#include <rush/string.h>
#include <rush/objectarray.h>
#include <rush/objectdeque.h>


namespace rush {

/**
 * \brief The MathOpcodeType enum descriptes the type of the opcode.
 **/
enum class MathOpcodeType
{
    /// \brief Loads a constant value into the stack.
    LoadConstant,
    /// \brief Loads a variable into the stack.
    LoadVariable,
    /// \brief Saves the first value from the stack into a variable.
    SaveVariable,
    /// \brief Calls a function.
    CallFunction,
    /// \brief Adds two values from the stack and pushes the result into the stack.
    Add,
    /// \brief Substracts two values from the stack and pushes the result into the stack.
    Sub,
    /// \brief Multiplies two values from the stack and pushes the result into the stack.
    Mul,
    /// \brief Dividess two values from the stack and pushes the result into the stack.
    Div,
    /// \brief Negates one value from the stack and pushes the result into the stack.
    Neg,
    /// \brief Pops a value from the stack and pushes the value twice into the stack.
    Double,
    /// \brief No operation. Does nothing.
    Nop,
    /// \brief Opcode which contains multible other opcodes.
    Opcodes
};


// Forward declaration
class MathOpcode;

/**
 * \brief The MathOpcodeArray typedef stores MathOpcodes in a ObjectArray.
 **/
typedef ObjectArray<MathOpcode> MathOpcodeArray;


/**
 * \brief The MathOpcodeDeque typedef stores MathOpcodes in a ObjectDeque.
 **/
typedef ObjectDeque<MathOpcode> MathOpcodeDeque;




/**
 * \brief The MathOpcode class contains information about an opcode. Please be cautions
 * using MathOpcodeType::Opcodes. The array will be freed, but not the opcodes in the array!
 **/
class MathOpcode
{
    public:
        MathOpcode();
        MathOpcode(MathOpcodeType type);
        MathOpcode(MathOpcodeType type, double value);
        MathOpcode(MathOpcodeType type, size_t index);
        MathOpcode(MathOpcodeType type, MathOpcodeArray* array);
        ~MathOpcode();

        /**
         * \brief Returns the opcode type.
         * \return Opcode type.
         **/
        inline MathOpcodeType GetType() const
        { return (m_type); }

        /**
         * \brief Returns the opcode value.
         * \return Value.
         **/
        inline double GetValue() const
        { return (m_data.Value); }

        /**
         * \brief Returns the opcode index value.
         * \return Index.
         **/
        inline size_t GetIndex() const
        { return (m_data.Index); }

        /**
         * \brief Returns the opcode array in this opcode.
         * \return Opcode array.
         **/
        inline MathOpcodeArray* GetArray() const
        { return (m_data.Array); }

        String ToString() const;

    private:
        void SetType(MathOpcodeType type);
        void SetValue(double value);
        void SetIndex(size_t index);

    private:
        union Data
        {
            double Value;
            size_t Index;
            MathOpcodeArray* Array;
        } m_data;
        MathOpcodeType m_type;
};



} // namespace rush

#endif // _RUSH_MATHOPCODE_H_
