#include "Easings.hpp"
#include "Utils.hpp"

using namespace Utils;
using namespace Constants;

EasingFunction Utils::getEasingFunction(EasingType type) {
    switch (type) {
        case EasingType::None: return easeLinear;
        case EasingType::EaseIn: return easeIn;
        case EasingType::EaseOut: return easeOut;
        case EasingType::EaseInOut: return easeInOut;
        case EasingType::ElasticInOut: return easeElasticInOut;
        case EasingType::ElasticIn: return easeElasticIn;
        case EasingType::ElasticOut: return easeElasticOut;
        case EasingType::BounceInOut: return easeBounceInOut;
        case EasingType::BounceIn: return easeBounceIn;
        case EasingType::BounceOut: return easeBounceOut;
        case EasingType::ExponentialInOut: return easeExponentialInOut;
        case EasingType::ExponentialIn: return easeExponentialIn;
        case EasingType::ExponentialOut: return easeExponentialOut;
        case EasingType::SineInOut: return easeSineInOut;
        case EasingType::SineIn: return easeSineIn;
        case EasingType::SineOut: return easeSineOut;
        case EasingType::BackInOut: return easeBackInOut;
        case EasingType::BackIn: return easeBackIn;
        case EasingType::BackOut: return easeBackOut;
        default: return easeLinear;
    }
}

float Utils::easeLinear(float x, float e) {
    return x;
}
float Utils::easeInOut(float x, float e) {
    if (x < 0.5f) return 0.5f * powf(2 * x, e);
    else return 1 - (0.5f * powf(2 * (1 - x), e));
}
float Utils::easeIn(float x, float e) {
    return powf(x, e);
}
float Utils::easeOut(float x, float e) {
    return 1 - powf(1 - x, e);
}
float Utils::easeElasticInOut(float x, float e) {
    if (x == 0 || x == 1) return x;
    float expo = 10.0f * e;
    if (x < 0.5f) return -0.5f * powf(2, expo * 2 * x - expo) * sinf(((expo * 2 * x) - expo + 0.25f) * easingCC5);
    else return 0.5f * powf(2, -expo * 2 * (x - 0.5f)) * sinf(((expo * 2 * (x - 0.5f)) - 0.75f) * easingCC5) + 1;
}
float Utils::easeElasticIn(float x, float e) {
    if (x == 0 || x == 1) return x;
    float expo = 10.0f * e;
    return -powf(2, expo * x - expo) * sinf(((x * expo) - expo + 0.25f) * easingCC4);
}
float Utils::easeElasticOut(float x, float e) {
    if (x == 0 || x == 1) return x;
    float expo = 10.0f * e;
    return powf(2, -expo * x) * sinf(((x * expo) - 0.75f) * easingCC4) + 1;
}
float Utils::easeBounceInOut(float x, float e) {
    if(x < 0.5f) return 8 * powf(2, 8 * (x - 1)) * abs(sinf((x * pi) * 7));
    else return 1 - (8 * powf( 2, -8 * x) * abs(sinf((x * pi) * 7)));
}
float Utils::easeBounceIn(float x, float e) {
    return powf(2, 6 * (x - 1)) * abs(sinf((x * pi) * 3.5f));
}
float Utils::easeBounceOut(float x, float e) {
    return 1 - (powf(2, -6 * x) * abs(cosf((x * pi) * 3.5f)));
}
float Utils::easeExponentialInOut(float x, float e) {
    if (x == 0 || x == 1) return x;
    if (x < 0.5f) return powf(2, (20 * x) - 10) / 2;
    else return (2 - powf(2, (-20 * x) + 10)) / 2;
}
float Utils::easeExponentialIn(float x, float e) {
    if (x == 0) return x; 
    else return powf(2, 10 * (x - 1));
}
float Utils::easeExponentialOut(float x, float e) {
    if (x == 1) return x;
    else return 1 - powf(2, -10 * x);
}
float Utils::easeSineInOut(float x, float e) {
    return -(cosf(pi * x) - 1) / 2;
}
float Utils::easeSineIn(float x, float e) {
    return 1 - cosf((x * pi) / 2);
}
float Utils::easeSineOut(float x, float e) {
    return sinf((x * pi) / 2);
}
float Utils::easeBackInOut(float x, float e) {
    if (x < 0.5f) return (powf(((2 * x)), 2)) * ((((easingCC2 + 1) * ((2 * x))) - easingCC2)) / 2;
    else return (((powf((((2 * x) - 2)), 2)) * (((easingCC2 + 1) * (((2 * x) - 2))) + easingCC2)) + 2) / 2;
}
float Utils::easeBackIn(float x, float e) {
    return (easingCC3 * powf(x, 3)) - (easingCC1 * powf(x, 2));
}
float Utils::easeBackOut(float x, float e) {
    return 1 + ((easingCC3 * powf(x - 1, 3)) + (easingCC1 * powf(x - 1, 2)));
}