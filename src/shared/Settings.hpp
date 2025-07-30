#pragma once

#include "../utils/Enums.hpp"

namespace Settings {
    inline geode::Mod* mod;

    inline bool enabled;
    
    inline bool updateWhenPlaytesting;
    
    inline float layerAlphaMultiplier;

    inline std::string settingsButtonTexture;

    namespace TriggerIndicators {
        inline bool enabled;

        inline bool onlySelected;
        inline bool onlyTriggers;
        inline bool onlySpawn;
        inline bool clusterObjects;
        inline bool clusterTriggers;
        inline bool clusterFallbackIndividualObjects;
        inline bool clusterFallbackIndividualTriggers;
        inline bool boxLineObjects;
        inline bool boxLineTriggers;
        inline bool scaleWithZoom;

        inline int clusterObjectsMaxThreshold;
        inline int clusterTriggersMaxThreshold;

        inline float maxDistance;
        inline float thickness;
        inline float clusterObjectsSize;
        inline float clusterTriggersSize;

        inline cocos2d::ccColor4F extrasCol1;
        inline cocos2d::ccColor4F extrasCol2;

        inline std::unordered_set<int> groupBlacklist;
        inline std::unordered_set<int> triggerBlacklist;

        inline bool chroma;
        
        inline float cullDistanceMultiplier;
        inline float selectedCullDistanceMultiplier;
    }

    namespace SpawnIndicators {
        inline bool enabled;

        inline float thickness;
        inline float size;

        inline cocos2d::ccColor4F col;
    }

    namespace BetterParticles {
        inline bool enabled;

        inline bool fillForRect;
        inline bool linesToCenter;
        inline bool hideOnDifferentLayer;
        inline bool scaleWithZoom;

        inline float thickness;
        inline float centerLineThickness;
        inline float fillOpacity;

        inline cocos2d::ccColor4F primaryCol;
        inline cocos2d::ccColor4F secondaryCol;
        inline cocos2d::ccColor4F centerLineCol;

        inline bool chroma;
    }

    namespace MoveIndicators {
        inline bool enabled;

        inline bool enableIndicatorByDefault;
        inline bool enableEndPreviewByDefault;
        inline bool excludeTriggers;
        inline bool previewEasing;
        inline bool scaleWithZoom;

        inline int easingSteps;
        inline int clusterMaxThreshold;

        inline MoveIndicatorMode objectGroupingMode;
        inline MoveIndicatorMode clusterFallbackType;

        inline float thickness;
        inline float endPreviewThickness;
        inline float clusterSize;

        inline cocos2d::ccColor4F indicatorCol;
        inline cocos2d::ccColor4F centerIndicatorCol;
        inline cocos2d::ccColor4F startCol;
        inline cocos2d::ccColor4F endCol;
        inline cocos2d::ccColor4F endPreviewCol;

        inline bool chroma;

        inline std::unordered_map<std::string, MoveIndicatorMode> objectGroupingModeMap {
            {"On Trigger", MoveIndicatorMode::OnTrigger}, 
            {"Rect", MoveIndicatorMode::Rect}, 
            {"Cluster", MoveIndicatorMode::Cluster}
        };

        inline std::unordered_map<std::string, MoveIndicatorMode> clusterFallbackTypeMap {
            {"On Trigger", MoveIndicatorMode::OnTrigger},
            {"Rect", MoveIndicatorMode::Rect},
            {"Disable", MoveIndicatorMode::Disable}
        };
    }

    inline float sayoDeviceSensitivity;
 
    void updateSettings();

    void set(bool& setting, const char* key);
    void set(int& setting, const char* key);
    void set(float& setting, const char* key);
    void set(cocos2d::ccColor4F& setting, const char* key);
    void set(std::unordered_set<int>& setting, const char* key);
}