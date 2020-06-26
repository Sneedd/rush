/*
 * testarray.cpp - Implementation of UnitTest::TestArray method
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2011-2012 - Steffen Ott
 *
 */



#include "unittest.h"


//-----------------------------------------------------------------------------
void UnitTest::TestArray()
{
    this->BeginTest(_T("Array"));
    rush::Array<int> intArray;

    for (int i=0; i<77; ++i) intArray.Add(i);
    this->Assert(_T("Add1"), intArray.Count() != 77);

    this->Assert(_T("Add2"), intArray[66] != 66);

    intArray[11] = 99;
    this->Assert(_T("Set1"), intArray[11] != 99);

    intArray.Shrink();
    this->Assert(_T("Shrink1"), intArray.Count() != intArray.Capacity());

    intArray.Remove(14);
    this->Assert(_T("Remove1"), intArray[14] != 15);

    this->EndTest();
}
