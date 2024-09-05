#ifndef MISC_FUNCS
#define MISC_FUNCS

#include <algorithm>

////////////////////////////// FUNCTIONS DECLARATIONS ////////////////////////////
double lerp (float, float, float); // search for "lerp functions"
int random_number (int, int);

////////////////////////////// FUNCTIONS DEFINITIONS ///////////////////////////////
double lerp (float initialPos, float targetPos, float lerpSpeed)
{
    return initialPos*(1-lerpSpeed) + targetPos*lerpSpeed;
}

int random_number (int Min, int Max)
{
    return rand () % (Max - Min +1) + Min;
}

#endif