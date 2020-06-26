/*
 * testrandom.cpp - Implementation of UnitTest::TestRandom method
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2011-2012 - Steffen Ott
 *
 */



#include "unittest.h"


//-----------------------------------------------------------------------------
bool TestRandomNextIntFunction(int min, int max, bool reachTest = false)
{
    int count = 10000;
    if (reachTest) count *= 100;
    bool minReached = false;
    bool maxReached = false;
    for (int i=0; i<count; ++i)
    {
        int value = rush::Random::NextInt(min, max);

        // Swap min max, also done in function
        if (max < min) {
            int value = max;
            max = min;
            min = value;
        }

        if (value < min) return (false);
        if (value > max) return (false);
        if (reachTest)
        {
            if (value == min) minReached = true;
            if (value == max) maxReached = true;
        }
    }
    if (reachTest) return (minReached && maxReached);
    return (true);
}



//-----------------------------------------------------------------------------
bool TestRandomNextFloatFunction()
{
    for (int i=0; i<100000; ++i)
    {
        float value = rush::Random::NextFloat();
        if (value < -1.0f) return (false);
        if (value >  1.0f) return (false);
    }
    return (true);
}


//-----------------------------------------------------------------------------
bool TestRandomNextFloatFunction(float min, float max)
{
    for (int i=0; i<100000; ++i)
    {
        float value = rush::Random::NextFloat(min, max);
        // Swap min max, also done in function
        if (max < min) {
            float value = max;
            max = min;
            min = value;
        }
        if (value < min) return (false);
        if (value > max) return (false);
    }
    return (true);
}





//-----------------------------------------------------------------------------
void UnitTest::TestRandom()
{
    this->BeginTest(_T("Random"));

    // Test Random Functions
    this->Assert(_T("NextInt1"), !TestRandomNextIntFunction(-10, 10));
    this->Assert(_T("NextInt2"), !TestRandomNextIntFunction(10, -10));
    this->Assert(_T("NextInt3"), !TestRandomNextIntFunction(0, 10));
    this->Assert(_T("NextInt4"), !TestRandomNextIntFunction(-10, 0));
    this->Assert(_T("NextInt5"), !TestRandomNextIntFunction(10, 10));
    this->Assert(_T("NextInt6"), !TestRandomNextIntFunction(-2, 2, true));
    this->Assert(_T("NextInt7"), !TestRandomNextIntFunction(0, 2, true));
    this->Assert(_T("NextInt8"), !TestRandomNextIntFunction(-2, 0, true));
    this->Assert(_T("NextInt9"), !TestRandomNextIntFunction(2, 2, true));

    this->Assert(_T("NextFloat1"), !TestRandomNextFloatFunction());
    this->Assert(_T("NextFloat2"), !TestRandomNextFloatFunction(-3.0f, 3.0f));

    this->EndTest();
}


