#pragma once

namespace Constants {
    /// really dont see the need to namespace constants
    inline int extrasCircleDetail = 16;
    inline int spawnIndicatorDetail = 32;
    inline int betterParticlesRadialDetail = 96;
    inline int betterParticlesRadial0FallbackDetail = 16;
    inline float extrasSize = 4.0f;
    inline float extrasRadius = 2.0f;
    inline float extrasSizeThicknessMultiplier = 0.5f;
    inline float extrasXOffset = 10.0f;
    inline float targetTypesYOffset = 4.5f;
    inline float triggerBodyYOffset = -5.0f;
    inline float cullDistanceBuffer = 1.25f;
    inline float betterParticlesRadial0FallbackSize = 2.5f;
    inline float sqrt2Over2 = 0.707106f;
    inline float degToRad = 0.017453f; // would use geodes functions but ive already commited to making every constant editable :3c

    inline cocos2d::ccColor4F transparentCCC4F = {0.0f, 0.0f, 0.0f, 0.0f};

    // ts so unnecessary why did i do this
    void loadConstants();

    // ill move over these parsing utils to utils if i ever use json anywhere else in the mod tho i doubt i will
    void setColor(cocos2d::ccColor4F& constant, const matjson::Value& value);
    void setInt(int& constant, const matjson::Value& value);
    void setUInt(int& constant, const matjson::Value& value);
    void setFloat(float& constant, const matjson::Value& value);

    inline const std::unordered_map<std::string, std::function<void(const matjson::Value&)>> setConstantsFunctions = {
        {"spawn-indicator-detail", [] (const matjson::Value& value) { setUInt(spawnIndicatorDetail, value); }},
        {"extras-circle-detail", [] (const matjson::Value& value) { setUInt(extrasCircleDetail, value); }},
        {"better-particles-radial-detail", [] (const matjson::Value& value) { setUInt(betterParticlesRadialDetail, value); }},
        {"better-particles-radial-0-fallback-detail", [] (const matjson::Value& value) { setUInt(betterParticlesRadial0FallbackDetail, value); }},
        {"extras-size", [] (const matjson::Value& value) { setFloat(extrasSize, value); }},
        {"extras-radius", [] (const matjson::Value& value) { setFloat(extrasRadius, value); }},
        {"extras-size-thickness-multiplier", [] (const matjson::Value& value) { setFloat(extrasSizeThicknessMultiplier, value); }},
        {"extras-x-offset", [] (const matjson::Value& value) { setFloat(extrasXOffset, value); }},
        {"target-types-y-offset", [] (const matjson::Value& value) { setFloat(targetTypesYOffset, value); }},
        {"transparent-ccc4f", [] (const matjson::Value& value) { setColor(transparentCCC4F, value); }},
        {"trigger-body-y-offset", [] (const matjson::Value& value) { setFloat(triggerBodyYOffset, value); }},
        {"cull-distance-buffer", [] (const matjson::Value& value) { setFloat(cullDistanceBuffer, value); }},
        {"better-particles-radial-0-fallback-size", [] (const matjson::Value& value) { setFloat(betterParticlesRadial0FallbackSize, value); }},
        {"sqrt-2-over-2", [] (const matjson::Value& value) { setFloat(sqrt2Over2, value); }},
        {"deg-to-rad", [] (const matjson::Value& value) { setFloat(degToRad, value); }}
        // {"", [] (const matjson::Value& value) { set(, value); }},
        // {"", [] (const matjson::Value& value) { set(, value); }},
        // {"", [] (const matjson::Value& value) { set(, value); }},
        // {"", [] (const matjson::Value& value) { set(, value); }},
        // {"", [] (const matjson::Value& value) { set(, value); }},
        // {"", [] (const matjson::Value& value) { set(, value); }},
        // {"", [] (const matjson::Value& value) { set(, value); }},
        // {"", [] (const matjson::Value& value) { set(, value); }},

    };
};