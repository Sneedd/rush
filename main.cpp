/*
 * main.cpp - Implementation of main function
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2011-2012 - Steffen Ott
 *
 */



#include "test/unittest.h"


void DoTesting()
{
    UnitTest test;
    test.TestAll();
    //test.TestArray();
    //test.TestConvert();
    //test.TestList();
    //test.TestObjectArray();
    //test.TestObjectStack();
    //test.TestStringArray();
    //test.TestParser();
    //test.TestString();
    //test.TestObjectQueue();
    //test.TestMathEvaluation();
}

int main(int argc, char** argv)
{
    rush::Memory::BeginLeakDetection();
    DoTesting();
    rush::Memory::EndLeakDetection();
    rush::Console::WriteLine(rush::Memory::GetMemoryLeaksInfo());
}
