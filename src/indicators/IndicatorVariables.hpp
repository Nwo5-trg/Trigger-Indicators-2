#pragma once

enum class IndicatorType {
    IndividualLine = 0,
    Rect = 1,
    Clustered = 2
};

namespace IndicatorVars { // im paranoid so everything gets a value
    inline cocos2d::CCDrawNode* triggerIndicatorDraw = nullptr;
    inline cocos2d::CCDrawNode* triggerExtraDraw = nullptr;
    inline cocos2d::CCLayer* triggerIndicatorGroupLayer = nullptr;
    inline cocos2d::CCLayer* batchLayer = nullptr;

    inline bool disableMod = false;
    inline bool disableIndicators = false;

    inline bool onlySelected = false;
    inline bool onlyTriggers = false;
    inline bool onlySpawn = false;
    inline bool spawnIndicators = false;
    inline bool groupLabels = true;
    inline float maxDistance = 300.0f * 300.0f; // squaring cuz the distance function squares its results
    inline float thickness = 1.0f;
    inline float spawnIndicatorThickness = 1.0f;
    inline float groupLabelsSize = 1.0f;
    inline float clusterSize = 1.0f;
    inline int clusterMaxThreshold = 1;
    inline IndicatorType indicatorType = IndicatorType::Clustered;
    inline cocos2d::ccColor4F extrasCol1 ={1.0f, 1.0f, 1.0f, 1.0f};
    inline cocos2d::ccColor4F extrasCol2 = {1.0f, 1.0f, 1.0f, 1.0f};
    inline std::unordered_set<int> groupBlacklist = {
        1, 2, 3, 4, 5
    };
    inline std::unordered_set<int> triggerBlacklist = {
        1, 2, 3, 4, 5
    };
    inline std::string settingsButtonTexture = "uwu";

    // the silly zone
    inline bool chroma = false;
    inline float sayoDeviceSensitivity = 1.0f;
    inline cocos2d::CCNodeRGBA* triggerIndicatorDrawChromaNode = nullptr;

    void updateSettings();
}