/*
 * testobjectdeque.cpp - Implementation of UnitTest::TestObjectDeque method
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
void PrintDeque(const rush::ObjectDeque<TestObject>& deque, bool pointer = false)
{
//    rush::Console::Write(_T("Queue (Count = %i [%i]) F%i, B%i = { "),
//        queue.Count(), queue.Capacity(), queue.GetFrontIndex(), queue.GetBackIndex());
//    for (size_t i=0; i<queue.Capacity(); ++i)
//    {
//        if (queue.ItemDebug(i) == NULL) {
//            rush::Console::Write(_T("N"));
//        } else if (pointer) {
//            rush::Console::Write(_T("%p"), queue.ItemDebug(i));
//        } else {
//            rush::Console::Write(_T("%i"), queue.ItemDebug(i)->Value);
//        }
//        if (i != queue.Capacity()-1) rush::Console::Write(_T(", "));
//    }
//    rush::Console::WriteLine(_T(" }"));
}


//-----------------------------------------------------------------------------
void UnitTest::TestObjectDeque()
{
    this->BeginTest(_T("ObjectDeque"));

    rush::ObjectDeque<TestObject> deque;

    deque.Push(new TestObject(0));
    this->Assert(_T("Push1"), deque.Peek()->Value != 0);

    deque.Enqueue(new TestObject(1));
    this->Assert(_T("Enqueue1"), deque.First()->Value != 0);

    this->EndTest();
}








