/*
 * mathtokenizer.cpp - Implementation of MathToken and MathTokenizer class
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2011-2012 - Steffen Ott
 *
 */



#include <rush/mathtokenizer.h>
#include <rush/console.h>

namespace rush {


//-----------------------------------------------------------------------------
const int stateMatrix[10][6] = {
    {  0,  2,  2, -1,  2, -1 },  // 0
    { -1,  5,  2, -1,  5,  5 },  // 1
    {  0,  1,  3,  3,  1,  1 },  // 2
    { -1,  5, -1, -1,  5,  5 },  // 3
    { -1,  1,  1,  1,  1, -1 },  // 4
    { -1,  1,  1,  1,  1,  1 },  // 5
    { -1,  4,  4,  4,  4,  4 },  // 6
    {  1, -1, -1, -1, -1, -1 },  // 7
    { -1,  0,  0,  0, -1,  0 },  // 8
    { -1,  1,  1, -1, -1,  1 }}; // 9


//-----------------------------------------------------------------------------
const int actionMatrix[10][6] = {
    {  1,  1,  1,  0, 10,  0 },  // 0
    {  0,  1,  1,  0, 10,  1 },  // 1
    {  0,  0,  0,  0,  5,  4 },  // 2
    {  0,  1,  0,  0, 10,  1 },  // 3
    {  0, 11, 12, 12, 13,  0 },  // 4
    {  0, 11, 14, 14, 13, 15 },  // 5
    {  0,  1, 16, 16,  1, 19 },  // 6
    {  6,  0,  0,  0,  0,  0 },  // 7
    {  0, 17, 18, 18,  0, 20 },  // 8
    {  0, 21, 22,  0,  0, 23 }}; // 9



//-----------------------------------------------------------------------------
String MathToken::ToString() const
{
    if (m_type == MathTokenType::Assignment)
    {
        return (String::Format(_T("%s="), m_content.c_str()));
    }
    else if (m_type == MathTokenType::Bracket)
    {
        return (m_content.c_str());
    }
    else if (m_type == MathTokenType::Constant)
    {
        return (m_content.c_str());
    }
    else if (m_type == MathTokenType::EndStatement)
    {
        return (m_content.c_str());
    }
    else if (m_type == MathTokenType::Function)
    {
        return (m_content.c_str());
    }
    else if (m_type == MathTokenType::Operator)
    {
        return (m_content.c_str());
    }
    else if (m_type == MathTokenType::Variable)
    {
        return (m_content.c_str());
    }
    else if (m_type == MathTokenType::Comma)
    {
        return (m_content.c_str());
    }
    return (_T("Unknown token type"));
}

//-----------------------------------------------------------------------------
MathTokenizer::MathTokenizer()
{
    m_currentstate = 0;
    m_tokens = new MathTokenArray();
    m_currenttoken = _T("");
}


//-----------------------------------------------------------------------------
MathTokenizer::~MathTokenizer()
{
    if (m_tokens != NULL)
    {
        delete m_tokens;
    }
}


//-----------------------------------------------------------------------------
bool MathTokenizer::Parse(const String& statements, StringArray* errors)
{
    m_currentstate = 0;
    m_tokens->Clear();
    m_currenttoken.Clear();
    int line = 0;
    int column = 0;

    for (size_t i=0; i<statements.Length(); ++i)
    {
        int inputCode = this->GetInputCode(statements[i]);
        if (inputCode == '\n') {
            column = 0;
            line += 1;
        }
        if (inputCode < 0) {
            errors->Add(String::Format(_T("Unexpected character '%c' in line '%i' at column '%i'."),
                                       statements[i], line, column));
            return (false);
        }
        this->DoAction(actionMatrix[inputCode][m_currentstate], statements[i]);
        m_currentstate = stateMatrix[inputCode][m_currentstate];
        if (m_currentstate < 0)
        {
            errors->Add(String::Format(_T("Unexpected character '%c' in line '%i' at column '%i'."),
                                       statements[i], line, column));
            return (false);
        }
        column += 1;
    }
    this->DoAction(actionMatrix[2][m_currentstate], '_');
    this->DoAction(actionMatrix[8][m_currentstate], ';');
    return (true);
}


//-----------------------------------------------------------------------------
MathTokenArray* MathTokenizer::GetTokens() const
{
    return (m_tokens);
}



//-----------------------------------------------------------------------------
int MathTokenizer::GetInputCode(Char input) const
{
    if ((input >= 'a' && input <= 'z') || (input >= 'A' && input <= 'Z') || input == '_') {
        return (0);
    }
    else if (input >= '0' && input <= '9') {
        return (1);
    }
    else if (input == ' ' || input == '\t' || input == '\r' || input == '\n') {
        return (2);
    }
    else if (input == '.') {
        return (3);
    }
    else if (input == '(') {
        return (4);
    }
    else if (input == ')') {
        return (5);
    }
    else if (input == '+' || input == '-' || input == '*' || input == '/') {
        return (6);
    }
    else if (input == '=') {
        return (7);
    }
    else if (input == ';') {
        return (8);
    }
    else if (input == ',') {
        return (9);
    }
    return (-1);
}


//-----------------------------------------------------------------------------
void MathTokenizer::DoAction(int action, Char input)
{
    if (action == 0)
    {
        return;
    }
    else if (action == 1)
    {
        m_currenttoken.Append(input);
    }
    else if (action == 2)
    {
        m_tokens->Add(new MathToken(MathTokenType::Function, m_currenttoken));
        m_currenttoken.Clear();
    }
    else if (action == 3)
    {
        m_tokens->Add(new MathToken(MathTokenType::Variable, m_currenttoken));
        m_currenttoken.Clear();
    }
    else if (action == 4)
    {
        m_tokens->Add(new MathToken(MathTokenType::Constant, m_currenttoken));
        m_currenttoken.Clear();
    }
    else if (action == 5)
    {
        m_tokens->Add(new MathToken(MathTokenType::Operator, m_currenttoken));
        m_currenttoken.Clear();
    }
    else if (action == 6)
    {
        m_tokens->Add(new MathToken(MathTokenType::Assignment, m_currenttoken));
        m_currenttoken.Clear();
    }
    else if (action == 7)
    {
        m_tokens->Add(new MathToken(MathTokenType::Bracket, m_currenttoken));
        m_currenttoken.Clear();
    }
    else if (action == 8)
    {
        m_tokens->Add(new MathToken(MathTokenType::EndStatement, m_currenttoken));
        m_currenttoken.Clear();
    }
    else if (action == 9)
    {
        m_tokens->Add(new MathToken(MathTokenType::Comma, m_currenttoken));
        m_currenttoken.Clear();
    }
    else if (action == 10)
    {
        this->DoAction(5, '\0');
        this->DoAction(1, input);
    }
    else if (action == 11)
    {
        this->DoAction(1, input);
        this->DoAction(7, '\0');
    }
    else if (action == 12)
    {
        this->DoAction(2, '\0');
        this->DoAction(1, input);
        this->DoAction(7, '\0');
    }
    else if (action == 13)
    {
        this->DoAction(5, '\0');
        this->DoAction(1, input);
        this->DoAction(7, '\0');
    }
    else if (action == 14)
    {
        this->DoAction(3, '\0');
        this->DoAction(1, input);
        this->DoAction(7, '\0');
    }
    else if (action == 15)
    {
        this->DoAction(4, '\0');
        this->DoAction(1, input);
        this->DoAction(7, '\0');
    }
    else if (action == 16)
    {
        this->DoAction(3, '\0');
        this->DoAction(1, input);
    }
    else if (action == 17)
    {
        this->DoAction(1, input);
        this->DoAction(8, '\0');
    }
    else if (action == 18)
    {
        this->DoAction(3, '\0');
        this->DoAction(1, input);
        this->DoAction(8, '\0');
    }
    else if (action == 19)
    {
        this->DoAction(4, '\0');
        this->DoAction(1, input);
    }
    else if (action == 20)
    {
        this->DoAction(4, '\0');
        this->DoAction(1, input);
        this->DoAction(8, '\0');
    }
    else if (action == 21)
    {
        this->DoAction(1, input);
        this->DoAction(9, '\0');
    }
    else if (action == 22)
    {
        this->DoAction(3, '\0');
        this->DoAction(1, input);
        this->DoAction(9, '\0');
    }
    else if (action == 23)
    {
        this->DoAction(4, '\0');
        this->DoAction(1, input);
        this->DoAction(9, '\0');
    }
    else
    {
        Console::WriteLine(_T("Error"));
    }
}




} // namespace rush



