#pragma once

using EasingFunction = float(*)(float, float);

namespace Utils {
    EasingFunction getEasingFunction(EasingType type);

    float easeLinear(float x, float e);
    float easeInOut(float x, float e);
    float easeIn(float x, float e);
    float easeOut(float x, float e);
    float easeElasticInOut(float x, float e);
    float easeElasticIn(float x, float e);
    float easeElasticOut(float x, float e);
    float easeBounceInOut(float x, float e);
    float easeBounceIn(float x, float e);
    float easeBounceOut(float x, float e);
    float easeExponentialInOut(float x, float e);
    float easeExponentialIn(float x, float e);
    float easeExponentialOut(float x, float e);
    float easeSineInOut(float x, float e);
    float easeSineIn(float x, float e);
    float easeSineOut(float x, float e);
    float easeBackInOut(float x, float e);
    float easeBackIn(float x, float e);
    float easeBackOut(float x, float e);
}