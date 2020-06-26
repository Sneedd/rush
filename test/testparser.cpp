/*
 * testparser.cpp - Implementation of UnitTest::TestParser method
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2011-2012 - Steffen Ott
 *
 */



#include "unittest.h"

#include <stdlib.h>


//-----------------------------------------------------------------------------
void TestParserSpeed(size_t num)
{
    float stdTime = 0.0f;
    float rushTime = 0.0f;
    size_t ticks = 0;

    //----------------------------------------------
    ticks = rush::System::GetTicks();
    for (size_t i=0; i<num; ++i)
    {
        atoi("12345678");
    }
    stdTime = (float)(rush::System::GetTicks() - ticks);
    ticks = rush::System::GetTicks();
    for (size_t i=0; i<num; ++i)
    {
        rush::Parser::ParseInt(_T("12345678"));
    }
    rushTime = (float)(rush::System::GetTicks() - ticks);
    printf("Speed test comparison: atoi() = %1.1fms rush::Parser::ParseInt() = %1.1fms\n",
           stdTime, rushTime);

    //----------------------------------------------
    ticks = rush::System::GetTicks();
    for (size_t i=0; i<num; ++i)
    {
        atof("12345678");
    }
    stdTime = (float)(rush::System::GetTicks() - ticks);
    ticks = rush::System::GetTicks();
    for (size_t i=0; i<num; ++i)
    {
        rush::Parser::ParseDouble(_T("123.45678"));
    }
    rushTime = (float)(rush::System::GetTicks() - ticks);
    printf("Speed test comparison: atof() = %1.1fms rush::Parser::ParseDouble() = %1.1fms\n",
           stdTime, rushTime);

}



//-----------------------------------------------------------------------------
void UnitTest::TestParser()
{
    int result = 0;
    double real = 0.0f;

    this->BeginTest(_T("Parser"));
    //TestParserSpeed(1000000);

    result = rush::Parser::ParseInt(_T("10"));
    this->Assert(_T("ParseInt1"), result != 10);

    result = rush::Parser::ParseInt(_T("1234567"));
    this->Assert(_T("ParseInt2"), result != 1234567);

    result = rush::Parser::ParseInt(_T("-10"));
    this->Assert(_T("ParseInt3"), result != -10);

    result = rush::Parser::ParseInt(_T("0"));
    this->Assert(_T("ParseInt4"), result != 0);

    real = rush::Parser::ParseDouble(_T("10.1"));
    this->Assert(_T("ParseFloat1"), real != 10.1d);

    real = rush::Parser::ParseDouble(_T("-1.0"));
    this->Assert(_T("ParseFloat2"), real != -1.0d);

    real = rush::Parser::ParseDouble(_T("3.32"));
    this->Assert(_T("ParseFloat3"), real != 3.32d);

    real = rush::Parser::ParseDouble(_T("0.15"));
    this->Assert(_T("ParseFloat4"), real != 0.15d);

    real = rush::Parser::ParseDouble(_T("0.0"));
    this->Assert(_T("ParseFloat5"), real != 0.0d);


    this->EndTest();
}
