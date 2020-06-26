/*
 * random.cpp - Implementation of Random class
 *
 * This file is part of the rush utility library.
 * Licenced unter the terms of Lesser GPL v3.0 (see licence.txt).
 * Copyright 2012 - Steffen Ott
 *
 */


#include <rush/random.h>
#include <stdlib.h>  // for srand() and rand()
#include <time.h>    // for time()
#include <math.h>    // for floor()


namespace rush {





//-----------------------------------------------------------------------------
void Random::SetSeed(unsigned int seed)
/**
 * \brief Sets the random seed number.
 * Note that using 0 as seed randomizes the seed number and using 1
 * restarts the last seed.
 **/
{
    if (seed == 0)
    {
        srand(time(NULL));
    }
    else
    {
        srand(seed);
    }
}

//-----------------------------------------------------------------------------
int Random::NextInt()
/**
 * \brief Returns a random number between 0 and (32768*32768).
 **/
{
    return (rand()*rand());
}


//-----------------------------------------------------------------------------
int Random::NextInt(int min, int max)
{
    if (max < min) {
        int value = max;
        max = min;
        min = value;
    }
    if (max - min == 0) {
        return (max);
    }
    int randValue = rand()*rand();
    randValue %= (max+1-min);
    return (randValue + min);
}


//-----------------------------------------------------------------------------
float Random::NextFloat()
{
    float randValue = (float)((rand()*rand()) % 2000000);
    randValue /= 1000000.0f;
    return (randValue - 1.0f);
}



//-----------------------------------------------------------------------------
float Random::NextFloat(float min, float max)
{
    if (max < min) {
        float value = max;
        max = min;
        min = value;
    }
    if (max - min == 0) {
        return (max);
    }

    // TODO : Precicison beachten
    float randValue = (float)(rand()*rand());
    randValue = fmod(randValue, (max-min)*1000000);
    randValue /= 1000000.0f;
    return (randValue + min);
}



//-----------------------------------------------------------------------------
double Random::NextDouble()
/**
 * \brief
 **/
{
    // TODO
    return (Random::NextFloat());
}


//-----------------------------------------------------------------------------
void Random::NextUnitVector2f(float* vector)
/**
 * \brief
 **/
{
}


//-----------------------------------------------------------------------------
unsigned char Random::NextByteVariation(unsigned char value, unsigned char variation)
/**
 * \brief
 **/
{
    return (Random::NextInt(value-variation, value+variation));
}


//-----------------------------------------------------------------------------
float Random::NextFloatVariation(float value, float variation)
/**
 * \brief
 **/
{
    return (Random::NextFloat(value-variation, value+variation));
}



} // namespace rush
