/*
 * unittest.h - Declaration of UnitTest class
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2011-2012 - Steffen Ott
 *
 */


#ifndef _RUSH_UTILITY_LIB_TEST_H_
#define _RUSH_UTILITY_LIB_TEST_H_

#include <stdio.h>
#include <rush/rush.h>
#include "unittestresult.h"




class UnitTest
{
    public:
        UnitTest();
        ~UnitTest();

        void TestAll();

        void TestArray();
        void TestConvert();
        void TestList();
        void TestMathEvaluation();
        void TestObjectArray();
        void TestObjectDeque();
        void TestObjectQueue();
        void TestObjectStack();
        void TestParser();
        void TestPath();
        void TestRandom();
        void TestString();
        void TestStringArray();
        void TestVector();
        void TestVersion();

        void BeginTest(const rush::String& testName);
        void EndTest();
        void Assert(const rush::String& description, bool fail);

    private:
        bool m_alwaysshowresult;
        int m_index;
        rush::String m_currenttest;
        rush::ObjectArray<UnitTestResult>* m_results;

};


#endif // _RUSH_UTILITY_LIB_TEST_H_
