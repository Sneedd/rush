/*
 * testobjectstack.cpp - Implementation of UnitTest::TestObjectStack method
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2011-2012 - Steffen Ott
 *
 */



#include "unittest.h"


//-----------------------------------------------------------------------------
class TestObject
{
    public:
        TestObject(int value) : Value(value) {}
        int Value;
};



//-----------------------------------------------------------------------------
void UnitTest::TestObjectStack()
{
    TestObject* object = NULL;
    rush::ObjectStack<TestObject> stack;


    this->BeginTest(_T("ObjectStack"));

    stack.Push(new TestObject(0));
    stack.Push(new TestObject(1));
    stack.Push(new TestObject(2));
    stack.Push(new TestObject(3));
    stack.Push(new TestObject(4));

    this->Assert(_T("Push1"), stack.Count() != 5);
    this->Assert(_T("Push2"), stack.Peek()->Value != 4);

    object = stack.Pop();
    this->Assert(_T("Pop1"), stack.Count() != 4);
    this->Assert(_T("Pop2"), object->Value != 4);

    delete object;
    stack.Clear();
    this->Assert(_T("Clear1"), stack.Count() != 0);

    for (int i=0; i<512; ++i) stack.Push(new TestObject(i));
    this->Assert(_T("Push3"), stack.Count() != 512);
    this->Assert(_T("Push4"), stack.Peek()->Value != 511);

    this->EndTest();
}



