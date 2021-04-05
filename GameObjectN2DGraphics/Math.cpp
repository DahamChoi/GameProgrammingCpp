#include "Math.h"

const float AMath::PI = 3.14159265f;

float AMath::ToDegree(float radian)
{
    return radian * 180.f / PI;
}

float AMath::ToRadian(float degree)
{
    return degree * PI / 180.f;
}
