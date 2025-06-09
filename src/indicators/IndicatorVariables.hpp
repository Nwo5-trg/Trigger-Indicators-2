#pragma once

enum class IndicatorType {
    IndividualLine = 0,
    Rect = 1,
    Clustered = 2
};

namespace IndicatorVars {
    inline cocos2d::CCDrawNode* triggerIndicatorDraw = nullptr;
    inline cocos2d::CCDrawNode* triggerExtraDraw = nullptr;
    inline cocos2d::CCLayer* batchLayer = nullptr;

    inline bool onlySelected = false;
    inline bool onlyTriggers = false;
    inline float maxDistance = 300.0f * 300.0f; // squaring cuz the distance function squares its results
    inline float thickness = 1.0f;
    inline float clusterSize = 60.0f;
    inline int clusterMaxThreshold = 60;
    inline IndicatorType indicatorType = IndicatorType::Clustered;
    inline cocos2d::ccColor4F extrasCol1 = cocos2d::ccc4f(1.0f, 1.0f, 1.0f, 1.0f);
    inline cocos2d::ccColor4F extrasCol2 = cocos2d::ccc4f(0.0f, 0.0f, 0.0f, 1.0f);

    // the silly zone
    inline bool chroma = false;
    inline float sayoDeviceSensitivity = 0.25f;
    inline cocos2d::CCNodeRGBA* triggerIndicatorDrawChromaNode = nullptr;
}