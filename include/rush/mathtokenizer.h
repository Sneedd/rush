/*
 * mathtokenizer.h - Declaration of MathToken and MathTokenizer class
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2012 - Steffen Ott
 *
 */




#ifndef _RUSH_MATHTOKENIZER_H_
#define _RUSH_MATHTOKENIZER_H_

#include <rush/config.h>
#include <rush/string.h>
#include <rush/stringarray.h>
#include <rush/objectarray.h>


namespace rush {


/**
 * \brief The MathTokenType enum definies the type of a token.
 **/
enum class MathTokenType
{
    /// \brief None marks a undefined token.
    None,
    /// \brief Function name token.
    Function,
    /// \brief Variable name token.
    Variable,
    /// \brief Constant value token.
    Constant,
    /// \brief Operator token.
    Operator,
    /// \brief Assignement variable and operator.
    Assignment,
    /// \brief Bracken open or close.
    Bracket,
    /// \brief End statement token.
    EndStatement,
    /// \brief Comma token.
    Comma
};


/**
 * \brief The MathToken class stores information of one token.
 * The token
 **/
class MathToken
{
    public:
        MathToken()
            : m_type(MathTokenType::None), m_content(_T("")) {}
        MathToken(MathTokenType type, const String& content)
            : m_type(type), m_content(content) {}
        ~MathToken() {}

        inline MathTokenType GetType() const
        { return (m_type); }

        inline const String& GetContent() const
        { return (m_content); }

        inline void SetType(MathTokenType type)
        { m_type = type; }

        inline void SetContent(const String& content)
        { m_content = content; }

        String ToString() const;

    private:
        MathTokenType m_type;
        String m_content;
};


/**
 * \brief
 **/
typedef ObjectArray<MathToken> MathTokenArray;

/**
 * \brief
 * \todo Tokenizer can be send to src. Forward declarations needed in mathevaluation.h
 **/
class MathTokenizer
{
    public:
        MathTokenizer();
        virtual ~MathTokenizer();

        bool Parse(const String& statements, StringArray* errors);
        MathTokenArray* GetTokens() const;

    private:
        int GetInputCode(Char input) const;
        void DoAction(int action, Char input);

    private:
        int m_currentstate;
        ObjectArray<MathToken>* m_tokens;
        String m_currenttoken;
};


} // namespace rush


#endif // _RUSH_MATHTOKENIZER_H_
