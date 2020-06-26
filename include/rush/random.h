/*
 * random.h - Declaration of the Random class
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2011-2012 - Steffen Ott
 *
 */


#ifndef _RUSH_RANDOM_H_
#define _RUSH_RANDOM_H_

#include <rush/config.h>

namespace rush {

class Random
{
    private:
        Random() {}
        virtual ~Random() {}

    public:
        static void SetSeed(unsigned int seed = 0);

        static int NextInt();
        static int NextInt(int min, int max);

        static float NextFloat();
        static float NextFloat(float min, float max);

        static double NextDouble();

        static void NextUnitVector2f(float* vector);

        static unsigned char NextByteVariation(unsigned char value, unsigned char variation);
        static float NextFloatVariation(float value, float variation);

        static float Mod(float a, float b);
};


} // namespace rush

#endif // _RUSH_RANDOM_H_

