/*
 * testobjectarray.cpp - Implementation of UnitTest::TestObjectArray method
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
void testMoveToSpeed()
{
    size_t ticks = rush::System::GetTicks();
    rush::ObjectArray<TestObject> array;
    for (int c=0; c<1000; ++c)
    {
        array.Clear();
        for (int i=0; i<10000; ++i)
        {
            if (rush::Random::NextInt(0, 10) < 2) {
                array.Add(NULL);
            } else {
                array.Add(new TestObject(0));
            }
        }
    }
    array.MoveUp();
    ticks = rush::System::GetTicks() - ticks;
    printf("Running %1.2fs %u\n", (float)ticks / 1000.0f, ticks);
}


//-----------------------------------------------------------------------------
void PrintArray(const rush::ObjectArray<TestObject>& array, bool pointer = false)
{
    if (pointer)
    {
        printf("\nArray (Count = %i [%i]) = { ", array.Count(), array.Capacity());
        for (size_t i=0; i<array.Capacity(); ++i)
        {
            if (array.ItemDebug(i) == NULL) {
                printf("N");
            } else {
                printf("%p", array.ItemDebug(i));
            }
            if (i != array.Capacity()-1) printf(", ");
        }
        printf(" }\n");
    }
    else
    {
        printf("\nArray (Count = %i [%i]) = { ", array.Count(), array.Capacity());
        for (size_t i=0; i<array.Capacity(); ++i)
        {
            if (array.ItemDebug(i) == NULL) {
                printf("N");
            } else {
                printf("%i", array.ItemDebug(i)->Value);
            }
            if (i != array.Capacity()-1) printf(", ");
        }
        printf(" }\n");
    }
}


//-----------------------------------------------------------------------------
int TestComparer(const TestObject* a, const TestObject* b)
{
    return (a->Value - b->Value);
}

//-----------------------------------------------------------------------------
void UnitTest::TestObjectArray()
{
    this->BeginTest(_T("ObjectArray"));


    rush::ObjectArray<TestObject> array;
    array.Add(new TestObject(3));
    array.Add(new TestObject(1));
    array.Add(new TestObject(0));
    array.Add(new TestObject(2));
    this->Assert(_T("Init"), array.Count() != 4);

    array.Sort(&TestComparer);
    this->Assert(_T("Sort"), array[0]->Value != 0 || array[1]->Value != 1 || array[2]->Value != 2 || array[3]->Value != 3);

    array.Clear();
    this->Assert(_T("Clear"), array.Count() != 0);

    for (int i=0; i<17; ++i) array.Add(new TestObject(i));
    this->Assert(_T("Alloc"), array.Count() != 17 || array.Capacity() != 32);

    array.Shrink();
    this->Assert(_T("Shrink"), array.Count() != 17 || array.Capacity() != 17);

    array.Alloc(16);
    this->Assert(_T("Alloc"), array.Count() != 16 || array.Capacity() != 16);

    array.Clear();
    array.Add(NULL);
    array.Add(new TestObject(0));
    array.Add(new TestObject(1));
    array.Add(NULL);
    array.Add(new TestObject(2));
    array.Add(NULL);
    array.MoveUp();
    this->Assert(_T("MoveUp"), array.Count() != 3 || array[2]->Value != 2);

    array.Clear();
    array.Add(NULL);
    array.Add(NULL);
    array.Add(NULL);
    array.Add(new TestObject(0));
    array.Add(NULL);
    array.Add(new TestObject(1));
    array.Add(new TestObject(2));
    array.Add(NULL);
    array.Add(NULL);
    array.Add(new TestObject(3));
    array.Add(new TestObject(4));
    array.Add(new TestObject(5));
    array.Add(NULL);
    array.Add(NULL);
    array.Add(NULL);
    array.MoveUp();
    if (array.Count() != 6 || array[5]->Value != 5) printf("Err8 - ");

    array.Clear();
    array.Add(NULL);
    array.Add(NULL);
    array.Add(NULL);
    array.Add(new TestObject(0));
    array.Add(NULL);
    array.Add(new TestObject(1));
    array.Add(new TestObject(2));
    array.Add(new TestObject(3));
    array.MoveUp();
    if (array.Count() != 4 || array[3]->Value != 3) printf("Err9 - ");

    array.Clear();
    array.Add(new TestObject(0));
    array.Add(NULL);
    array.Add(NULL);
    array.MoveUp();
    if (array.Count() != 1 || array[0]->Value != 0) printf("Err10 - ");

    array.Clear();
    array.Add(new TestObject(1));
    array.Add(new TestObject(1));
    array.Add(new TestObject(1));
    array.Distinct(&TestComparer);
    if (array.Count() != 1 || array[0]->Value != 1) printf("Err11 - ");

    //PrintArray(array);

    //testMoveToSpeed();
    this->EndTest();
}
