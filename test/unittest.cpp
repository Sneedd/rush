/*
 * unittest.cpp - Implementation of UnitTest class
 *
 * This file is part of the rush utility library.
 * Licensed under the terms of Lesser GPL v3.0 (see license.txt).
 * Copyright 2011-2012 - Steffen Ott
 *
 */



#include "unittest.h"


//-----------------------------------------------------------------------------
UnitTest::UnitTest()
{
    m_results = new rush::ObjectArray<UnitTestResult>();
    m_alwaysshowresult = true;
}


//-----------------------------------------------------------------------------
UnitTest::~UnitTest()
{
    if (m_results != NULL)
    {
        delete m_results;
    }
}


//-----------------------------------------------------------------------------
void UnitTest::TestAll()
{
//    this->TestArray();
//    this->TestConvert();
//    this->TestList();
//    this->TestMathEvaluation();
//    this->TestObjectArray();
//    this->TestObjectDeque();
//    this->TestObjectQueue();
//    this->TestObjectStack();
//    this->TestParser();
    this->TestPath();
//    this->TestRandom();
//    this->TestString();
//    this->TestStringArray();
//    this->TestVector();
//    this->TestVersion();
}


//-----------------------------------------------------------------------------
void UnitTest::BeginTest(const rush::String& testName)
{
    m_index = 0;
    m_currenttest = testName;
    m_results->Clear();

    rush::String filler('=', 59 - testName.Length());
    rush::Console::WriteLine(_T("%s %s"), m_currenttest.c_str(), filler.c_str());

}


//-----------------------------------------------------------------------------
void UnitTest::EndTest()
{

    size_t countFailed = 0;
    for (size_t i=0; i<m_results->Count(); ++i)
    {
        if (m_results->Item(i)->GetFailed())
        {
            countFailed += 1;
        }
    }
    if (countFailed > 0) rush::Console::SetTextColor(rush::ConsoleColors::Red);
    rush::Console::WriteLine(_T("Tests %i of %i failed."), countFailed, m_results->Count());
    if (countFailed > 0) rush::Console::SetTextColor(rush::ConsoleColors::Gray);
    rush::String filler('-', 60);
    rush::Console::WriteLine(_T("%s\n"), filler.c_str());
}


//-----------------------------------------------------------------------------
void UnitTest::Assert(const rush::String& description, bool failed)
/**
 * \brief
 **/
{
    int index = m_index++;
    m_results->Add(new UnitTestResult(index, description, failed));

    if (failed) {
        if (m_alwaysshowresult) {
            rush::Console::SetTextColor(rush::ConsoleColors::Red);
        }
        rush::Console::WriteLine(_T("Test [%i] '%s' failed."), index, description.c_str());
        rush::Console::Flush();
        if (m_alwaysshowresult) {
            rush::Console::SetTextColor(rush::ConsoleColors::Gray);
        }
    } else {
        if (m_alwaysshowresult) {
            rush::Console::WriteLine(_T("Test [%i] '%s' successful."), index, description.c_str());
            rush::Console::Flush();
        }
    }
}


