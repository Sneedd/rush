/*
 * teststring.cpp - Implementation of UnitTest::TestString method
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2011-2012 - Steffen Ott
 *
 */


#include "unittest.h"




//-----------------------------------------------------------------------------
void UnitTest::TestString()
{
    // Variables
    rush::String strg;
    int index = 0;
    bool test = false;
    size_t count = 0;



    this->BeginTest(_T("String"));

    strg = _T("Hello World");
    strg.Append('!');
    this->Assert(_T("Append1"), !strg.IsOk() || strg != _T("Hello World!"));

    strg.Clear();
    this->Assert(_T("Clear1"), !strg.IsOk() || strg.Length() != 0);

    strg.Append(_T("What's")).Append(_T(" up!"));
    this->Assert(_T("Append2"), !strg.IsOk() || strg != _T("What's up!"));

    index = strg.Find(_T("up"));
    this->Assert(_T("Find1"), !strg.IsOk() || index != 7);

    index = strg.Find(_T("Up"));
    this->Assert(_T("Find2"), !strg.IsOk() || index != -1);

    strg.Remove(7);
    this->Assert(_T("Remove1"), !strg.IsOk() || strg != _T("What's "));

    strg.Remove(10);
    this->Assert(_T("Remove2"), !strg.IsOk() || strg != _T("What's "));

    strg.TrimLast();
    this->Assert(_T("TrimLast1"), !strg.IsOk() || strg != _T("What's"));

    strg = rush::String('-', 4);
    this->Assert(_T("Ctor1"), !strg.IsOk() || strg != _T("----"));

    strg.TrimLast('-');
    this->Assert(_T("TrimLast2"), !strg.IsOk() || strg != _T(""));

    strg.AppendFormat(_T("%i"), 1234);
    this->Assert(_T("Append3"), !strg.IsOk() || strg != _T("1234"));

    strg.Append(rush::String('x', 256));
    strg.Clear();
    this->Assert(_T("Clear2"), !strg.IsOk() || strg != _T(""));

    strg.Append(_T("1234"));
    this->Assert(_T("Append4"), !strg.IsOk() || strg[2] != '3');

    strg[2] = '9';
    this->Assert(_T("Set1"), !strg.IsOk() || strg[2] != '9');

    strg = _T("abCDef");
    strg = strg.ToLower();
    this->Assert(_T("ToLower1"), !strg.IsOk() || strg != _T("abcdef"));

    strg = _T("abCDef");
    strg = strg.ToUpper();
    this->Assert(_T("ToUpper1"), !strg.IsOk() || strg != _T("ABCDEF"));

    strg = _T("AC");
    strg.Insert(1, _T("B"));
    this->Assert(_T("Insert1"), !strg.IsOk() || strg != _T("ABC"));

    strg.Insert(3, _T("D"));
    this->Assert(_T("Insert2"), !strg.IsOk() || strg != _T("ABCD"));

    strg.Insert(0, _T("x"));
    this->Assert(_T("Insert3"), !strg.IsOk() || strg != _T("xABCD"));

    strg = _T("ABCDEFGHIJKL");
    strg.Insert(1, _T("ttt"));
    this->Assert(_T("Insert4"), !strg.IsOk() || strg != _T("AtttBCDEFGHIJKL"));

    strg.Insert(10, _T("----------------------"));
    this->Assert(_T("Insert5"), !strg.IsOk() || strg != _T("AtttBCDEFG----------------------HIJKL"));

    strg = _T("ABC");
    strg.Remove(1, 1);
    this->Assert(_T("Remove3"), !strg.IsOk() || strg != _T("AC"));

    strg.Remove(0, 1);
    this->Assert(_T("Remove4"), !strg.IsOk() || strg != _T("C"));

    strg = _T("ABC");
    strg.Remove(2, 1);
    this->Assert(_T("Remove5"), !strg.IsOk() || strg != _T("AB"));

    strg = _T("ABCDEFGHIJK");
    strg.Remove(2, 4);
    this->Assert(_T("Remove6"), !strg.IsOk() || strg != _T("ABGHIJK"));

    strg = _T("ABCDEFGHIJK");
    strg.Remove(0, 4);
    this->Assert(_T("Remove7"), !strg.IsOk() || strg != _T("EFGHIJK"));

    strg = _T("ABCDEFGHIJK");
    strg.Remove(8, 3);
    this->Assert(_T("Remove8"), !strg.IsOk() || strg != _T("ABCDEFGH"));

    strg = _T("\t\n   \r    W   ");
    strg.TrimFirst();
    this->Assert(_T("TrimFirst1"), !strg.IsOk() || strg != _T("W   "));

    strg = _T("1234 local ");
    strg.TrimFirst(_T("1234"));
    this->Assert(_T("TrimFirst2"), !strg.IsOk() || strg != _T(" local "));

    strg.TrimFirst(' ');
    this->Assert(_T("TrimFirst3"), !strg.IsOk() || strg != _T("local "));

    strg.Append(rush::String('=', 128));
    this->Assert(_T("Ctor2"), !strg.IsOk() || strg.Length() != 134);

    strg.Remove(32);
    this->Assert(_T("Remove9"), !strg.IsOk() || strg.Length() != 32);

    strg.Shrink();
    this->Assert(_T("Shrink1"), !strg.IsOk() || strg.Capacity() != 33);

    strg = _T("012340567890");
    strg.Replace('0', 'x');
    this->Assert(_T("Replace1"), !strg.IsOk() || strg != _T("x1234x56789x"));

    test = strg.StartsWith(_T("x123"));
    this->Assert(_T("StartsWith1"), !strg.IsOk() || !test);

    test = strg.StartsWith(_T("x123xx"));
    this->Assert(_T("StartsWith2"), !strg.IsOk() || test);

    count = rush::String::Count(_T("x123xx32xx"), 'x');
    this->Assert(_T("Count1"), count != 5);

    count = rush::String::Count(rush::String(_T("x123xx32xx")), 'x');
    this->Assert(_T("Count2"), count != 5);

    strg = _T("5678xxght");
    test = strg.EndsWith(_T("8xxght"));
    this->Assert(_T("EndsWith1"), !strg.IsOk() || !test);

    test = strg.EndsWith(_T("8xght"));
    this->Assert(_T("EndsWith2"), !strg.IsOk() || test);

    strg = _T("zyx");
    index = strg.FindLast('y');
    this->Assert(_T("FindLast1"), !strg.IsOk() || index != 1);

    strg = _T("Look");
    strg = strg.Substring(1, 2);
    this->Assert(_T("Substring1"), !strg.IsOk() || strg != _T("oo"));

    strg = _T("Hallo Welt");
    strg = strg.Substring(6);
    this->Assert(_T("Substring2"), !strg.IsOk() || strg != _T("Welt"));

    strg = (rush::Char*)NULL;
    this->Assert(_T("Assign1"), !strg.IsOk() || strg != _T(""));

    #ifdef _RUSH_SUPPORTS_WXWIDGETS_
    strg = _T("Hallo Welt");
    wxString wxtest = (wxString)strg;
    strg.Clear();
    this->Assert(_T("wxStrg1"), !strg.IsOk() || strg != _T(""));

    strg = wxtest;
    this->Assert(_T("wxStrg2"), !strg.IsOk() || strg != _T("Hallo Welt"));
    #endif

    strg = _T("i1");
    this->Assert(_T("Equals1"), !strg.IsOk() || !(strg == _T("i1")));


    this->EndTest();
}

