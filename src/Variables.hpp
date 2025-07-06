#pragma once

enum class IndicatorType {
    IndividualLine = 0,
    Rect = 1,
    Clustered = 2
};

namespace Variables {
    inline cocos2d::CCDrawNode* triggerIndicatorDraw = nullptr;
    inline cocos2d::CCDrawNode* triggerExtraDraw = nullptr;
    inline cocos2d::CCLayer* triggerIndicatorGroupLayer = nullptr;
    inline cocos2d::CCLayer* batchLayer = nullptr;

    inline cocos2d::CCDictionary* collisionDict;

    inline bool hasCollisionIDs;
    inline float currentLayerMultiplier;

    inline bool disableMod;
    inline bool disableIndicators;

    inline bool onlySelected;
    inline bool onlyTriggers;
    inline bool onlySpawn;
    inline bool spawnIndicators;
    inline bool groupLabels;
    inline bool itemIDs;
    inline bool collisionIDs;

    inline float maxDistance; // squaring cuz the distance function squares its results
    inline float thickness;
    inline float spawnIndicatorThickness;
    inline float groupLabelsSize;
    inline float clusterSize;

    inline int clusterMaxThreshold;

    inline IndicatorType indicatorType = IndicatorType::Clustered;

    inline cocos2d::ccColor4F extrasCol1;
    inline cocos2d::ccColor4F extrasCol2;

    inline std::unordered_set<int> groupBlacklist;
    inline std::unordered_set<int> triggerBlacklist;

    inline std::string settingsButtonTexture;

    // the silly zone
    inline bool chroma;
    inline float sayoDeviceSensitivity;
    inline float cullDistanceMultiplier;
    inline cocos2d::CCNodeRGBA* triggerIndicatorDrawChromaNode = nullptr;

    void updateSettings();
}