/*
 * testvector.cpp - Implementation of UnitTest::TestVector method
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2011-2012 - Steffen Ott
 *
 */




#include "unittest.h"


//-----------------------------------------------------------------------------
void UnitTest::TestVector()
{
    this->BeginTest(_T("Vector"));

    rush::Vector2f vec(2.0f, 1.0f);
    this->Assert(_T("Vector"), vec.x != 2.0f || vec.y != 1.0f);

    this->EndTest();
}


