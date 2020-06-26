/*
 * teststringarray.cpp - Implementation of UnitTest::TestStringArray method
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2011-2012 - Steffen Ott
 *
 */


#include "unittest.h"


//-----------------------------------------------------------------------------
void PrintStringSplit(const rush::String& strg, const rush::String& separator,
                      rush::StringSplitOptions options)
{
    rush::StringArray* array = rush::StringArray::Split(strg, separator, options);
    printf("Count = %i   ", array->Count());
    for (size_t i=0; i<array->Count(); ++i)
    {
        #ifdef _RUSH_UNICODE_
        wprintf(_T("'%s' "), array->Item(i).c_str());
        #else
        printf("'%s' ", array->Item(i).c_str());
        #endif
    }
    printf("\n");
    delete array;
}

//-----------------------------------------------------------------------------
bool TestStringSplit(const rush::String& strg, const rush::String& separator,
                     rush::StringSplitOptions options, const rush::StringArray& expected)
{
    bool result = false;
    rush::StringArray* array = rush::StringArray::Split(strg, separator, options);
    if (array->Count() == expected.Count())
    {
        result = true;
        for (size_t i=0; i<array->Count(); ++i)
        {
            if (array->Item(i) != expected.Item(i))
            {
                result = false;
                break;
            }
        }
    }
    delete array;
    return (result);
}


//-----------------------------------------------------------------------------
void UnitTest::TestStringArray()
{
    this->BeginTest(_T("StringArray"));

    rush::StringArray array;
    rush::StringArray expected;

    for (int i=0; i<77; ++i) array.Add(rush::String().AppendFormat(_T("%i"), i));
    this->Assert(_T("Add1"), array.Count() != 77);
    this->Assert(_T("Add2"), array[66] != _T("66"));

    array[11] = _T("99");
    this->Assert(_T("Set1"), array[11] != _T("99"));

    array.Shrink();
    this->Assert(_T("Shrink1"), array.Count() != array.Capacity());

    array.Remove(14);
    this->Assert(_T("Remove"), array[14] != _T("15"));



    rush::StringSplitOptions options = rush::StringSplitOptions::Trim | rush::StringSplitOptions::RemoveEmptyEntries;

    // Split String Tests
    expected.Clear();
    expected.Add(_T("1")).Add(_T("2")).Add(_T("3")).Add(_T("4")).Add(_T("5")).Add(_T("6")).Add(_T("7")).Add(_T("8"));

    this->Assert(_T("Split1"), !TestStringSplit(
        _T("1,2,3,4,5,6,7,8"), _T(","), options, expected));

    this->Assert(_T("Split2"), !TestStringSplit(
        _T("1,.,2,.,3,.,4,.,5,.,6,.,7,.,8"), _T(",.,"), options, expected));

    this->Assert(_T("Split3"), !TestStringSplit(
        _T("1, 2, 3, 4, 5, 6, 7, 8"), _T(","), options, expected));

    this->Assert(_T("Split4"), !TestStringSplit(
        _T("  1 ,cd 2,cd 3 ,cd 4 ,cd 5  ,cd 6,cd 7 ,cd 8  "), _T(",cd"), options, expected));

    expected.Remove(6);
    expected.Remove(6);
    expected.Add(_T("7,,x8"));
    this->Assert(_T("Split5"), !TestStringSplit(
        _T("1,,,2,,,3,,,4,,,5,,,6,,,7,,x8"), _T(",,,"), options, expected));

    expected.Clear();
    this->Assert(_T("Split6"), !TestStringSplit(
        _T(""), _T(","), options, expected));


    expected.Add(_T("")).Add(_T(""));
    this->Assert(_T("Split7"), !TestStringSplit(
        _T("   ,"), _T(","), rush::StringSplitOptions::Trim, expected));

    expected.Add(_T("")).Add(_T(""));
    this->Assert(_T("Split8"), !TestStringSplit(
        _T("   ,,,"), _T(","), rush::StringSplitOptions::Trim, expected));

    expected.Clear();
    expected.Add(_T("111")).Add(_T("222")).Add(_T("333")).Add(_T("444")).Add(_T("555"));
    expected.Add(_T("666")).Add(_T("")).Add(_T("777")).Add(_T("888"));
    this->Assert(_T("Split9"), !TestStringSplit(
        _T("  111  ,-, 222,-, 333,-, 444    ,-,555,-, 666 ,-,,-, 777,-, 888   "),
        _T(",-,"), rush::StringSplitOptions::Trim, expected));

    this->EndTest();
}


