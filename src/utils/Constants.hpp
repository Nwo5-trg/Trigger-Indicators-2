#pragma once

namespace Constants {
    // ===============================================================
    // haiii the probably 2 ppl ever who will use the constant editing system
    // here r some very shitty comments kinda explaining wat they do :3c
    // ===============================================================

    // how many triangles to use 4r the circles
    inline int triggerIndicatorsExtrasCircleDetail = 16;
    inline int spawnIndicatorDetail = 32;
    inline int betterParticlesRadialDetail = 64;
    inline int betterParticlesRadial0FallbackDetail = 16;
    inline int moveIndicatorsStartCircleDetail = 16;
    inline int moveIndicatorsEndCircleDetail = 16;
    inline int areaPreviewsLengthCircleDetail = 64;
    // its this number wide and twice as high btw
    inline float triggerIndicatorsExtrasSize = 4.0f;
    // self explanitory
    inline float triggerIndicatorsExtrasRadius = 2.5f;
    // awful name that i dont feel like changing, this is js the thickness of the outline 
    inline float triggerIndicatorsExtrasSizeThicknessMultiplier = 0.5f;
    // self explanitory
    inline float triggerIndicatorsExtrasInputXOffset = 10.0f;
    inline float triggerIndicatorsExtrasOutputXOffset = 11.0f;
    // how far apart target and center output extras will b
    inline float triggerIndicatorsExtrasOutputYOffset = 5.0f;
    // duration shorter than this wont render
    inline float betterDurationLinesDurationLengthCullThreshold = 0.01f;
    // max spikey of shake previews
    inline float betterDurationLinesShakeRandomMax = 5.0f;
    // min spikey of shake previews
    inline float betterDurationLinesShakeRandomMin = 0.5f;
    // multiply the in game value by these 4r the preview
    inline float betterDurationLinesShakeIntervalMultiplier = 4.0f;
    inline float betterDurationLinesShakeStrengthMultiplier = 1.5f;
    // lines that extend infinitely will js b this long
    inline float areaPreviewsScreenEdgeLineLength = 25.0f;
    // deadzone wont render if its smaller than this
    inline float areaPreviewsDeadzoneThreshold = 0.01f;
    // if the editor is more zoomed in than this culling distance wont change accordingly (mainly to stop things from dissappearing if u zoom in too much)
    inline float maxZoomCullingClamp = 1.0f;
    // unused 4r now :3c
    inline float bigDumbFloat = 999999.0f;
    // used 4r drawing extras and duration lines i think (i dont care to check :3)
    inline float triggerBodyYOffset = -5.0f;
    // cull distance multiplied by this
    inline float cullDistanceBuffer = 1.25f;
    // self explanitory
    inline float normalSpeed = 311.58f;
    // after dottedLineDotSize is subtracted from dottedLineSegmentSize, thatll b the gap size 4r dotted lines
    inline float dottedLineSegmentSize = 7.5f;
    inline float dottedLineDotSize = 3.0f;
    // if radius == 0, this is how big the circle drawn will b
    inline float betterParticlesRadial0FallbackSize = 2.5f;
    // i dont feel like going into move inidcators code to figure out what i meant by this ;3
    inline float moveIndicatorsStartRadiusMultiplier = 2.0f;
    inline float moveIndicatorsEndSizeMultiplier = 2.0f;
    // math stuffs
    inline float sqrt2Over2 = 0.707106f;
    inline float degToRad = 0.017453f;
    inline float pi = 3.14159f;
    inline float pi2 = 6.28318f;
    // use for easings
    inline float easingCC1 = 1.70158f;
    inline float easingCC2 = 2.59491f;
    inline float easingCC3 = 2.70158f;
    inline float easingCC4 = 2.09440f;
    inline float easingCC5 = 1.39626f;
    // self explanitory
    inline cocos2d::ccColor4F transparentCCC4F = {0.0f, 0.0f, 0.0f, 0.0f};

    // ===============================================================
    // u can ignore the next couple lines until the next block of seperators
    // ===============================================================

    // ts so unnecessary why did i do this
    void loadConstants();

    // ill move over these parsing utils to utils if i ever use json anywhere else in the mod tho i doubt i will
    void setColor(cocos2d::ccColor4F& constant, const matjson::Value& value);
    void setInt(int& constant, const matjson::Value& value);
    void setUInt(int& constant, const matjson::Value& value);
    void setFloat(float& constant, const matjson::Value& value);

    // ===============================================================
    // the things in quotes r wat u gotta write in the json to change the respective value
    // ===============================================================

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
        {"trigger-indicators-extras-input-x-offset", [] (const matjson::Value& value) { setFloat(triggerIndicatorsExtrasInputXOffset, value); }},
        {"trigger-indicators-extras-output-x-offset", [] (const matjson::Value& value) { setFloat(triggerIndicatorsExtrasInputXOffset, value); }},
        {"trigger-indicators-extras-output-y-offset", [] (const matjson::Value& value) { setFloat(triggerIndicatorsExtrasOutputYOffset, value); }},
        {"better-duration-lines-duration-length-cull-threshold", [] (const matjson::Value& value) { setFloat(betterDurationLinesDurationLengthCullThreshold, value); }},
        {"better-duration-lines-shake-random-max", [] (const matjson::Value& value) { setFloat(betterDurationLinesShakeRandomMax, value); }},
        {"better-duration-lines-shake-random-min", [] (const matjson::Value& value) { setFloat(betterDurationLinesShakeRandomMin, value); }},
        {"better-duration-lines-shake-interval-multiplier", [] (const matjson::Value& value) { setFloat(betterDurationLinesShakeIntervalMultiplier, value); }},
        {"better-duration-lines-shake-strength-multiplier", [] (const matjson::Value& value) { setFloat(betterDurationLinesShakeStrengthMultiplier, value); }},
        {"area-previews-screen-edge-line-length", [] (const matjson::Value& value) { setFloat(areaPreviewsScreenEdgeLineLength, value); }},
        {"area-previews-deadzone-threshold", [] (const matjson::Value& value) { setFloat(areaPreviewsDeadzoneThreshold, value); }},
        {"max-zoom-culling-clamp", [] (const matjson::Value& value) { setFloat(maxZoomCullingClamp, value); }},
        {"big-dumb-float", [] (const matjson::Value& value) { setFloat(bigDumbFloat, value); }},
        {"trigger-body-y-offset", [] (const matjson::Value& value) { setFloat(triggerBodyYOffset, value); }},
        {"cull-distance-buffer", [] (const matjson::Value& value) { setFloat(cullDistanceBuffer, value); }},
        {"normal-speed", [] (const matjson::Value& value) { setFloat(normalSpeed, value); }},
        {"dotted-line-segment-size", [] (const matjson::Value& value) { setFloat(dottedLineSegmentSize, value); }},
        {"dotted-line-dot-size", [] (const matjson::Value& value) { setFloat(dottedLineDotSize, value); }},
        {"better-particles-radial-0-fallback-size", [] (const matjson::Value& value) { setFloat(betterParticlesRadial0FallbackSize, value); }},
        {"move-indicators-start-radius-multiplier", [] (const matjson::Value& value) { setFloat(moveIndicatorsStartRadiusMultiplier, value); }},
        {"move-indicators-end-size-multiplier", [] (const matjson::Value& value) { setFloat(moveIndicatorsEndSizeMultiplier, value); }},
        {"sqrt-2-over-2", [] (const matjson::Value& value) { setFloat(sqrt2Over2, value); }},
        {"deg-to-rad", [] (const matjson::Value& value) { setFloat(degToRad, value); }},
        {"pi", [] (const matjson::Value& value) { setFloat(pi, value); }},
        {"pi-2", [] (const matjson::Value& value) { setFloat(pi2, value); }},
        {"easing-cc1", [] (const matjson::Value& value) { setFloat(easingCC1, value); }},
        {"easing-cc2", [] (const matjson::Value& value) { setFloat(easingCC2, value); }},
        {"easing-cc3", [] (const matjson::Value& value) { setFloat(easingCC3, value); }},
        {"easing-cc4", [] (const matjson::Value& value) { setFloat(easingCC4, value); }},
        {"easing-cc5", [] (const matjson::Value& value) { setFloat(easingCC5, value); }},
        {"transparent-ccc4f", [] (const matjson::Value& value) { setColor(transparentCCC4F, value); }}
        // {"", [] (const matjson::Value& value) { set(, value); }},
        // {"", [] (const matjson::Value& value) { set(, value); }},
        // {"", [] (const matjson::Value& value) { set(, value); }},
        // {"", [] (const matjson::Value& value) { set(, value); }},
        // {"", [] (const matjson::Value& value) { set(, value); }},
        // {"", [] (const matjson::Value& value) { set(, value); }},
        // {"", [] (const matjson::Value& value) { set(, value); }},

    };
};