/*
 * testobjectqueue.cpp - Implementation of UnitTest::TestObjectQueue method
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
void PrintQueue(const rush::ObjectQueue<TestObject>& queue, bool pointer = false)
{
    rush::Console::Write(_T("Queue (Count = %i [%i]) F%i, B%i = { "),
        queue.Count(), queue.Capacity(), queue.GetFrontIndex(), queue.GetBackIndex());
    for (size_t i=0; i<queue.Capacity(); ++i)
    {
        if (queue.ItemDebug(i) == NULL) {
            rush::Console::Write(_T("N"));
        } else if (pointer) {
            rush::Console::Write(_T("%p"), queue.ItemDebug(i));
        } else {
            rush::Console::Write(_T("%i"), queue.ItemDebug(i)->Value);
        }
        if (i != queue.Capacity()-1) rush::Console::Write(_T(", "));
    }
    rush::Console::WriteLine(_T(" }\n"));
}




//-----------------------------------------------------------------------------
void UnitTest::TestObjectQueue()
{
    TestObject* object = NULL;
    rush::ObjectQueue<TestObject> queue;

    this->BeginTest(_T("ObjectQueue"));

    queue.Enqueue(new TestObject(1));
    queue.Enqueue(new TestObject(2));
    queue.Enqueue(new TestObject(3));
    this->Assert(_T("Enqueue1"), queue.Count() != 3);

    object = queue.Dequeue();
    this->Assert(_T("Dequeue1"), queue.Count() != 2);
    this->Assert(_T("Dequeue2"), object->Value != 1);
    delete object;

    queue.Alloc(88);
    this->Assert(_T("Alloc1"), queue.Capacity() != 88);

    queue.Shrink();
    this->Assert(_T("Shrink1"), queue.Capacity() != 2);

    for (int i=4; i<20; ++i) queue.Enqueue(new TestObject(i));
    this->Assert(_T("Alloc2"), queue.Capacity() != 32);
    this->Assert(_T("Alloc3"), queue.Count() != 18);
    this->Assert(_T("Enqueue2"), queue.First()->Value != 2);

    for (int i=0; i<7; ++i) {
        object = queue.Dequeue();
        delete object;
    }
    this->Assert(_T("Dequeue3"), queue.Count() != 11);

    queue.Shrink();
    this->Assert(_T("Shrink2"), queue.Capacity() != queue.Count());

    queue.Clear();
    this->Assert(_T("Clear1"), queue.Count() != 0);

    for (int i=0; i<10; ++i) queue.Enqueue(new TestObject(i));
    for (int i=0; i<4; ++i) {
        object = queue.Dequeue();
        delete object;
    }
    for (int i=1; i<6; ++i) queue.Enqueue(new TestObject(i*111));
    this->Assert(_T("Enqeue3"), queue.GetFrontIndex() != 4 || queue.GetBackIndex() != 4);

    //PrintQueue(queue);

    this->EndTest();
}
