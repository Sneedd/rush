/*
 * testmathevaluation.cpp - Implementation of UnitTest::TestMathEvaluation method
 *
 * This file is part of the rush utility library.
 * Licensed under the terms of Lesser GPL v3.0 (see license.txt).
 * Copyright 2011-2012 - Steffen Ott
 *
 */




#include "unittest.h"
#include <rush/mathevaluation.h>
#include <stdlib.h>
#include <math.h>



//-----------------------------------------------------------------------------
void TestSpeed()
{
    float stdTime = 0.0f;
    float rushTime = 0.0f;
    size_t ticks = 0;
    size_t num = 4000000;

    //----------------------------------------------
    ticks = rush::System::GetTicks();
    for (size_t i=0; i<num; ++i)
    {
        double s=10;
        double t=33;
        double u=22+s*76/t*sin(12);
        u += 1;
    }
    stdTime = (float)(rush::System::GetTicks() - ticks);


    //----------------------------------------------
    rush::MathEvaluation eval;
    eval.SetVariable(_T("s"), 10.0f);
    eval.SetVariable(_T("t"), 33.0f);
    eval.Compile(_T("22+s*76/t*sin(12)"));

    //----------------------------------------------
    ticks = rush::System::GetTicks();
    for (size_t i=0; i<num; ++i)
    {
        eval.Execute();
    }
    rushTime = (float)(rush::System::GetTicks() - ticks);

    printf("MathEvaluator - speed comparison: C++ = %1.1fms rush = %1.1fms\n",
           stdTime, rushTime);
}




//-----------------------------------------------------------------------------
void TestMathEval(UnitTest* test, const rush::String& code, double expected, bool detailed = false)
{
    rush::MathEvaluation eval;
    eval.SetVariable(_T("x"), 3.0d);
    eval.SetVariable(_T("i1"), 1.0d);
    eval.SetVariable(_T("i2"), 2.0d);
    eval.SetVariable(_T("i3"), 3.0d);
    eval.SetVariable(_T("d1"), 0.1d);
    eval.SetVariable(_T("d2"), 0.2d);
    eval.SetVariable(_T("d3"), 0.3d);
    if (detailed) rush::Console::WriteLine(_T("\nTokens.: %s"), eval.GetTokenizerText(code).c_str());
    if (!eval.Compile(code)) {
        rush::Console::WriteLine(_T("Compile Errors:"));
        while (eval.HasErrors()) {
            rush::Console::WriteLine(eval.GetErrorMessage());
        }
    }
    if (detailed) rush::Console::WriteLine(_T("OpCodes: %s"), eval.GetOpcodeText().c_str());
    if (!eval.Execute()) {
        rush::Console::WriteLine(_T("Execute Errors:"));
        while (eval.HasErrors()) {
            rush::Console::WriteLine(eval.GetErrorMessage());
        }
    }
    double result = eval.GetVariable(_T("result"));
    if (detailed)
    {
        if (expected != result)
        {
            rush::Console::WriteLine(_T("Result.: '%f' (Expected: '%f') (Diff: '%e')"),
                                     result, expected, expected-result);
        }
        else
        {
            rush::Console::WriteLine(_T("Result.: '%f' (Expected: '%f')"),
                                     result, expected);
        }
    }
    bool correctedResult = fabs(expected - result) < (1e-10);
    test->Assert(code, !correctedResult);
}





//-----------------------------------------------------------------------------
void UnitTest::TestMathEvaluation()
{
    this->BeginTest(_T("MathEvaluation"));

    //TestSpeed();

    // Simple tests
    TestMathEval(this, _T(""), 0.0d);
    TestMathEval(this, _T("result = 1"), 1.0d);
    TestMathEval(this, _T("result = 1+1"), 2.0d);
    TestMathEval(this, _T("result = 111-61"), 50.0d);
    TestMathEval(this, _T("result = 5*3"), 15.0d);
    TestMathEval(this, _T("result = 1/2"), 0.5d);
    TestMathEval(this, _T("result = 55 + 99/33-21+ 13 * 99"), 1324.0d);

    // Priority tests for swapable operators
    TestMathEval(this, _T("result = 1+2*3+4"), 11.0d);
    TestMathEval(this, _T("result = 1*2+3*4"), 14.0d);
    TestMathEval(this, _T("result = 1+2+3*4"), 15.0d);
    TestMathEval(this, _T("result = 1*2+3+4"), 9.0d);
    TestMathEval(this, _T("result = 1+2*3*4"), 25.0d);
    TestMathEval(this, _T("result = 1*2*3+4"), 10.0d);

    // Priority tests for unswapable operators
    TestMathEval(this, _T("result = 1-2/3-4"), -3.66666666666666666666d);
    TestMathEval(this, _T("result = 1/2-3/4"), -0.25d);
    TestMathEval(this, _T("result = 1-2-3/4"), -1.75d);
    TestMathEval(this, _T("result = 1/2-3-4"), -6.5d);
    TestMathEval(this, _T("result = 1-2/3/4"), 0.833333333333333333333d);
    TestMathEval(this, _T("result = 1/2/3-4"), -3.83333333333333333333d);

    // Priority tests for swapable operators multi
    TestMathEval(this, _T("result = 1+2*3+4*5+6*7+8*9+10"), 151.0d);
    TestMathEval(this, _T("result = 1*2+3*4+5*6+7*8+9*10"), 190.0d);
    TestMathEval(this, _T("result = 1*2*3+4+5*6*7+8+9*10"), 318.0d);
    TestMathEval(this, _T("result = 1+2+3*4*5+6+7*8*9+10"), 583.0d);

    // Test with brackets
    TestMathEval(this, _T("result = (2+3)+5*10"), 55.0d);
    TestMathEval(this, _T("result = (2+3)*10"), 50.0d);
    TestMathEval(this, _T("result = 2+(3*10)"), 32.0d);
    TestMathEval(this, _T("result = (1)"), 1.0d);
    TestMathEval(this, _T("result = ((1+2)*3+4)*5"), 65.0d);
    TestMathEval(this, _T("result = ((1+2)*(3+4)*5)*(22)"), 2310.0d);
    TestMathEval(this, _T("result = 60/(12*10)"), 0.5d);
    TestMathEval(this, _T("result = (6*10)/(12*10)"), 0.5d);

    // Tests with variables
    TestMathEval(this, _T("result = i1"), 1.0d);
    TestMathEval(this, _T("result = i1+i2+i3"), 6.0d);

    // Tests with NEG operator
    TestMathEval(this, _T("result = (3+4)+-1"), 6.0d);
    TestMathEval(this, _T("result = (3+4)+ -1"), 6.0d);
    TestMathEval(this, _T("result = 3+(-4*3)"), -9.0d);
    TestMathEval(this, _T("result = -1"), -1.0d);
    TestMathEval(this, _T("result = 21 + 22 + 4 + -1"), 46.0d);
    TestMathEval(this, _T("result = -21 + 22 + 4 + 1"), 6.0d);

    // Tests with functions
    TestMathEval(this, _T("result = pi()"), M_PI);
    TestMathEval(this, _T("result = abs(-3.3)"), 3.3d);
    TestMathEval(this, _T("result = pow(2, 3)"), 8.0d);
    TestMathEval(this, _T("result = exp(ln(2))"), 2.0d);
    TestMathEval(this, _T("result = 3.5+(60/fact(5))"), 4.0d);
    TestMathEval(this, _T("result = fact(5)"), 120.0d);
    TestMathEval(this, _T("result = 60/fact(5)"), 0.5d);

    // Test all functions
    TestMathEval(this, _T("result = pi()"), M_PI);
    TestMathEval(this, _T("result = exp(ln(2))"), 2.0d);
    TestMathEval(this, _T("result = pow(17, 5)"), 1419857.0d);
    TestMathEval(this, _T("result = sqrt(16)"), 4.0d);
    TestMathEval(this, _T("result = root(125, 3)"), 5.0d);
    TestMathEval(this, _T("result = log10(pow(10, 5))"), 5.0d);
    TestMathEval(this, _T("result = log(pow(7, 77), 7)"), 77.0d);
    TestMathEval(this, _T("result = fact(8)"), 40320.0d);
    TestMathEval(this, _T("result = mod(8,6)"), 2.0d);
    TestMathEval(this, _T("result = ceil(8.6)"), 9.0d);
    TestMathEval(this, _T("result = floor(8.6)"), 8.0d);
    TestMathEval(this, _T("result = int(8.6)"), 8.0d);
    TestMathEval(this, _T("result = frac(8.6)"), 0.6d);
    TestMathEval(this, _T("result = sin(pi())"), 0.0d);
    TestMathEval(this, _T("result = cos(pi())"), -1.0d);
    TestMathEval(this, _T("result = tan(pi())"), 0.0d);

    // Test long statements
    TestMathEval(this, _T("result = 1+(x/fact(1))+(pow(x,2)/fact(2))+(pow(x,3)/fact(3))"), 13.0d);

    // Test errorous statements
//    TestMathEval(this, _T("result = sin("), 0.0d, true);
//    TestMathEval(this, _T("result = i1*"), 0.0d, true);

    this->EndTest();
}



