#pragma once

namespace Constants {
    /// cant be fucked to seperate these

    inline int triggerIndicatorsExtrasCircleDetail = 16;
    inline int spawnIndicatorDetail = 32;
    inline int betterParticlesRadialDetail = 64;
    inline int betterParticlesRadial0FallbackDetail = 16;
    inline int moveIndicatorsStartCircleDetail = 16;
    inline int moveIndicatorsEndCircleDetail = 16;
    inline int areaPreviewsLengthCircleDetail = 64;
    inline float triggerIndicatorsExtrasSize = 4.0f;
    inline float triggerIndicatorsExtrasRadius = 2.0f;
    inline float triggerIndicatorsExtrasSizeThicknessMultiplier = 0.5f;
    inline float triggerIndicatorsExtrasXOffset = 10.0f;
    inline float triggerIndicatorsTargetTypesYOffset = 4.5f;
    inline float betterDurationLinesDurationLengthCullThreshold = 0.1f;
    inline float betterDurationLinesShakeRandomMax = 5.0f;
    inline float betterDurationLinesShakeRandomMin = 0.5f;
    inline float betterDurationLinesShakeIntervalMultiplier = 4.0f;
    inline float betterDurationLinesShakeStrengthMultiplier = 1.5f;
    inline float areaPreviewsDottedLineSegmentSize = 7.5f;
    inline float areaPreviewsDottedLineDotSize = 3.0f;
    inline float areaPreviewsScreenEdgeLineLength = 25.0f;
    inline float areaPreviewsDeadzoneThreshold = 0.01f;
    inline float bigDumbFloat = 999999.0f;
    inline float triggerBodyYOffset = -5.0f;
    inline float cullDistanceBuffer = 1.25f;
    inline float normalSpeed = 311.58f;
    inline float betterParticlesRadial0FallbackSize = 2.5f;
    inline float moveIndicatorsStartRadiusMultiplier = 2.0f;
    inline float moveIndicatorsEndSizeMultiplier = 2.0f;
    inline float sqrt2Over2 = 0.707106f;
    inline float degToRad = 0.017453f;
    inline float pi = 3.14159f;
    inline float easingCC1 = 1.70158f;
    inline float easingCC2 = 2.59491f;
    inline float easingCC3 = 2.70158f;
    inline float easingCC4 = 2.09440f;
    inline float easingCC5 = 1.39626f;
    inline cocos2d::ccColor4F transparentCCC4F = {0.0f, 0.0f, 0.0f, 0.0f};

    // ts so unnecessary why did i do this
    void loadConstants();

    // ill move over these parsing utils to utils if i ever use json anywhere else in the mod tho i doubt i will
    void setColor(cocos2d::ccColor4F& constant, const matjson::Value& value);
    void setInt(int& constant, const matjson::Value& value);
    void setUInt(int& constant, const matjson::Value& value);
    void setFloat(float& constant, const matjson::Value& value);

    inline std::unordered_map<std::string, std::function<void(const matjson::Value&)>> setConstantsFunctions = {
        {"spawn-indicator-detail", [] (const matjson::Value& value) { setUInt(spawnIndicatorDetail, value); }},
        {"trigger-indicators-extras-circle-detail", [] (const matjson::Value& value) { setUInt(triggerIndicatorsExtrasCircleDetail, value); }},
        {"better-particles-radial-detail", [] (const matjson::Value& value) { setUInt(betterParticlesRadialDetail, value); }},
        {"better-particles-radial-0-fallback-detail", [] (const matjson::Value& value) { setUInt(betterParticlesRadial0FallbackDetail, value); }},
        {"move-indicators-start-circle-detail", [] (const matjson::Value& value) { setUInt(moveIndicatorsStartCircleDetail, value); }},
        {"move-indicators-end-circle-detail", [] (const matjson::Value& value) { setUInt(moveIndicatorsEndCircleDetail, value); }},
        {"area-previews-length-circle-detail", [] (const matjson::Value& value) { setUInt(areaPreviewsLengthCircleDetail, value); }},
        {"trigger-indicators-extras-size", [] (const matjson::Value& value) { setFloat(triggerIndicatorsExtrasSize, value); }},
        {"trigger-indicators-extras-radius", [] (const matjson::Value& value) { setFloat(triggerIndicatorsExtrasRadius, value); }},
        {"trigger-indicators-extras-size-thickness-multiplier", [] (const matjson::Value& value) { setFloat(triggerIndicatorsExtrasSizeThicknessMultiplier, value); }},
        {"trigger-indicators-extras-x-offset", [] (const matjson::Value& value) { setFloat(triggerIndicatorsExtrasXOffset, value); }},
        {"trigger-indicators-target-types-y-offset", [] (const matjson::Value& value) { setFloat(triggerIndicatorsTargetTypesYOffset, value); }},
        {"better-duration-lines-duration-length-cull-threshold", [] (const matjson::Value& value) { setFloat(betterDurationLinesDurationLengthCullThreshold, value); }},
        {"better-duration-lines-shake-random-max", [] (const matjson::Value& value) { setFloat(betterDurationLinesShakeRandomMax, value); }},
        {"better-duration-lines-shake-random-min", [] (const matjson::Value& value) { setFloat(betterDurationLinesShakeRandomMin, value); }},
        {"better-duration-lines-shake-interval-multiplier", [] (const matjson::Value& value) { setFloat(betterDurationLinesShakeIntervalMultiplier, value); }},
        {"better-duration-lines-shake-strength-multiplier", [] (const matjson::Value& value) { setFloat(betterDurationLinesShakeStrengthMultiplier, value); }},
        {"area-previews-dotted-line-segment-size", [] (const matjson::Value& value) { setFloat(areaPreviewsDottedLineSegmentSize, value); }},
        {"area-previews-dotted-line-dot-size", [] (const matjson::Value& value) { setFloat(areaPreviewsDottedLineDotSize, value); }},
        {"area-previews-screen-edge-line-length", [] (const matjson::Value& value) { setFloat(areaPreviewsScreenEdgeLineLength, value); }},
        {"area-previews-deadzone-threshold", [] (const matjson::Value& value) { setFloat(areaPreviewsDeadzoneThreshold, value); }},
         {"big-dumb-float", [] (const matjson::Value& value) { setFloat(bigDumbFloat, value); }},
        {"transparent-ccc4f", [] (const matjson::Value& value) { setColor(transparentCCC4F, value); }},
        {"trigger-body-y-offset", [] (const matjson::Value& value) { setFloat(triggerBodyYOffset, value); }},
        {"cull-distance-buffer", [] (const matjson::Value& value) { setFloat(cullDistanceBuffer, value); }},
        {"normal-speed", [] (const matjson::Value& value) { setFloat(normalSpeed, value); }},
        {"better-particles-radial-0-fallback-size", [] (const matjson::Value& value) { setFloat(betterParticlesRadial0FallbackSize, value); }},
        {"move-indicators-start-radius-multiplier", [] (const matjson::Value& value) { setFloat(moveIndicatorsStartRadiusMultiplier, value); }},
        {"move-indicators-end-size-multiplier", [] (const matjson::Value& value) { setFloat(moveIndicatorsEndSizeMultiplier, value); }},
        {"sqrt-2-over-2", [] (const matjson::Value& value) { setFloat(sqrt2Over2, value); }},
        {"deg-to-rad", [] (const matjson::Value& value) { setFloat(degToRad, value); }},
        {"pi", [] (const matjson::Value& value) { setFloat(pi, value); }},
        {"easing-cc1", [] (const matjson::Value& value) { setFloat(easingCC1, value); }},
        {"easing-cc2", [] (const matjson::Value& value) { setFloat(easingCC2, value); }},
        {"easing-cc3", [] (const matjson::Value& value) { setFloat(easingCC3, value); }},
        {"easing-cc4", [] (const matjson::Value& value) { setFloat(easingCC4, value); }},
        {"easing-cc5", [] (const matjson::Value& value) { setFloat(easingCC5, value); }}
        // {"", [] (const matjson::Value& value) { set(, value); }},
        // {"", [] (const matjson::Value& value) { set(, value); }},
        // {"", [] (const matjson::Value& value) { set(, value); }},
        // {"", [] (const matjson::Value& value) { set(, value); }},
        // {"", [] (const matjson::Value& value) { set(, value); }},
        // {"", [] (const matjson::Value& value) { set(, value); }},
        // {"", [] (const matjson::Value& value) { set(, value); }},

    };
};