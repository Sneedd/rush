/*
 * testconvert.cpp - Implementation of UnitTest::TestConvert method
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2011-2012 - Steffen Ott
 *
 */



#include "unittest.h"

//-----------------------------------------------------------------------------
void UnitTest::TestConvert()
{
    this->BeginTest(_T("Convert"));

    unsigned int result = 0;

    result = rush::Convert::HexToInt(_T("0xA"));
    this->Assert(_T("HexUint"), result != 10);

    result = rush::Convert::HexToInt(_T("0XA"));
    this->Assert(_T("HexUint"), result != 10);

    result = rush::Convert::HexToInt(_T(""));
    this->Assert(_T("HexUint"), result != 0);

    result = rush::Convert::HexToInt(_T("A"));
    this->Assert(_T("HexUint"), result != 10);

    result = rush::Convert::HexToInt(_T("a"));
    this->Assert(_T("HexUint"), result != 10);

    result = rush::Convert::HexToInt(_T("00112233"));
    this->Assert(_T("HexUint"), result != 1122867);

    result = rush::Convert::HexToInt(_T("0x00112233"));
    this->Assert(_T("HexUint"), result != 1122867);

    result = rush::Convert::HexToInt(_T("abcdef"));
    this->Assert(_T("HexUint"), result != 11259375);

    result = rush::Convert::HexToInt(_T("ABCDEF"));
    this->Assert(_T("HexUint"), result != 11259375);

    result = rush::Convert::HexToInt(_T("aBcDeF"));
    this->Assert(_T("HexUint"), result != 11259375);

    result = rush::Convert::HexToInt(_T("FFFFFFFF"));
    this->Assert(_T("HexUint"), result != 4294967295u);

    this->EndTest();
}







