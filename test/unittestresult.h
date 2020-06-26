/*
 * unittestresult.h - Declaration and implementation of UnitTestResult class
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2011-2012 - Steffen Ott
 *
 */



#ifndef _RUSH_UNITTESTRESULT_H_
#define _RUSH_UNITTESTRESULT_H_


#include <rush/string.h>


class UnitTestResult
{
    public:
        UnitTestResult()
            : m_index(-1), m_description(_T("")), m_failed(false) {}
        UnitTestResult(int index, const rush::String& description, bool failed)
            : m_index(index), m_description(description), m_failed(failed) {}
        ~UnitTestResult() {}

        inline void SetDescription(const rush::String& description)
        { m_description = description; }

        inline void SetIndex(int index)
        { m_index = index; }

        inline void SetFailed(bool failed)
        { m_failed = failed; }

        inline const rush::String& GetDescription() const
        { return (m_description); }

        inline int GetIndex() const
        { return (m_index); }

        inline bool GetFailed() const
        { return (m_failed); }

    private:
        int m_index;
        rush::String m_description;
        bool m_failed;
};


#endif // _RUSH_UNITTESTRESULT_H_



