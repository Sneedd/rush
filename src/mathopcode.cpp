/*
 * mathopcode.cpp - Implementation of the MathOpcode class
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2011-2012 - Steffen Ott
 *
 */


#include <rush/mathopcode.h>
#include <rush/console.h>

namespace rush {

//-----------------------------------------------------------------------------
MathOpcode::MathOpcode()
/**
 * \brief Standardconstructor, initializes the MathOpcode object.
 **/
{
    m_type = MathOpcodeType::Nop;
    m_data.Index = 0;
}


//-----------------------------------------------------------------------------
MathOpcode::MathOpcode(MathOpcodeType type)
/**
 * \brief Constructor, initializes the MathOpcode object.
 * \param type Opcode type.
 **/
{
    m_type = type;
    m_data.Index = 0;
}


//-----------------------------------------------------------------------------
MathOpcode::MathOpcode(MathOpcodeType type, double value)
/**
 * \brief Constructor, initializes the MathOpcode object.
 * Note that the only opcode type which expects a double value is
 * the LDC (LoadConstant) opcode.
 * \param type Opcode type.
 * \param value Value.
 **/
{
    m_type = type;
    m_data.Value = value;
}


//-----------------------------------------------------------------------------
MathOpcode::MathOpcode(MathOpcodeType type, size_t index)
/**
 * \brief Constructor, initializes the MathOpcode object.
 * Note that the only opcode types which expect a index is the LDV (LoadVariable),
 * SAV (SaveVariable) and CALL (CallFunction) opcode.
 * \param type Opcode type.
 * \param index Index.
 **/
{
    m_type = type;
    m_data.Index = index;
}



//-----------------------------------------------------------------------------
MathOpcode::MathOpcode(MathOpcodeType type, MathOpcodeArray* array)
/**
 * \brief Constructor, initializes the MathOpcode object.
 * Note that the only opcode type which expects a MathOpcodeArray value is
 * the Opcodes (Nested Opcodes) opcode.
 * \param type Opcode type.
 * \param array Opcodes array.
 **/
{
    m_type = type;
    m_data.Array = array;
}



//-----------------------------------------------------------------------------
MathOpcode::~MathOpcode()
/**
 * \brief Destructor.
 **/
{
    if (m_type == MathOpcodeType::Opcodes)
    {
        if (m_data.Array != NULL)
        {
            m_data.Array->Clear(false);
            delete m_data.Array;
        }
    }
}


//-----------------------------------------------------------------------------
String MathOpcode::ToString() const
/**
 * \brief Returns a string which represents the opcode in a human readable format.
 * \return Opcode as string.
 **/
{
    if (m_type == MathOpcodeType::Add)
    {
        return (_T("ADD "));
    }
    else if (m_type == MathOpcodeType::CallFunction)
    {
        return (String::Format(_T("CALL '%s'"), m_data.Index));
    }
    else if (m_type == MathOpcodeType::Div)
    {
        return (_T("DIV"));
    }
    else if (m_type == MathOpcodeType::Double)
    {
        return (_T("DBL"));
    }
    else if (m_type == MathOpcodeType::LoadConstant)
    {
        return (String::Format(_T("LDC '%1.2f'"), m_data.Value));
    }
    else if (m_type == MathOpcodeType::LoadVariable)
    {
        return (String::Format(_T("LDV '%u'"), m_data.Index));
    }
    else if (m_type == MathOpcodeType::Mul)
    {
        return (_T("MUL"));
    }
    else if (m_type == MathOpcodeType::Neg)
    {
        return (_T("NEG"));
    }
    else if (m_type == MathOpcodeType::Nop)
    {
        return (_T("NOP"));
    }
    else if (m_type == MathOpcodeType::SaveVariable)
    {
        return (String::Format(_T("SAV '%u'"), m_data.Index));
    }
    else if (m_type == MathOpcodeType::Sub)
    {
        return (_T("SUB"));
    }
    else if (m_type == MathOpcodeType::Opcodes)
    {
        if (m_data.Array != NULL) {
            return (String::Format(_T("OPCODES '%u'"), m_data.Array->Count()));
        } else {
            return (_T("OPCODES 'NULL'"));
        }
    }
    return (_T("ERR"));
}



//-----------------------------------------------------------------------------
void MathOpcode::SetType(MathOpcodeType type)
/**
 * \brief Sets the type of the opcode.
 * \param type Opcode type.
 **/
{
    m_type = type;
}


//-----------------------------------------------------------------------------
void MathOpcode::SetValue(double value)
/**
 * \brief Sets the value of the opcode.
 * \param value Value.
 **/
{
    m_data.Value = value;
}


//-----------------------------------------------------------------------------
void MathOpcode::SetIndex(size_t index)
/**
 * \brief Sets the index value of the opcode.
 * \param index Index.
 **/
{
    m_data.Index = index;
}




} // namespace rush


