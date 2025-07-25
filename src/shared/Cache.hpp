#pragma once

// some of these are more like shared than cache but wtv 
// i dont wanna make 2 namespaces for pretty much the same thing
namespace Cache {
    namespace Utils {
        inline std::vector<std::vector<GameObject*>> clusters;
        inline std::vector<GameObject*> clusterObjQueue;
        inline std::unordered_map<GameObject*, int> clusterMap;
    }

    namespace View {
        inline float zoom;
        inline float cullDistance;
        inline cocos2d::CCSize size;
        inline cocos2d::CCPoint relativeCenter; // to batchlayer
    }

    inline int currentLayer;
    inline float layerAlphaMultiplier;

    inline cocos2d::CCDrawNode* gridDraw = nullptr;
    inline cocos2d::CCDrawNode* objectDraw = nullptr;

    inline cocos2d::CCDictionary* groupDict = nullptr;

    inline cocos2d::CCNodeRGBA* gayNode = nullptr;
    inline cocos2d::ccColor4F currentChromaCol;

    namespace TriggerIndicators {
        inline float cullDistance;
        inline cocos2d::ccColor4F col;
        inline cocos2d::ccColor4F extrasCol1;
        inline cocos2d::ccColor4F extrasCol2;
        inline std::vector<GameObject*> targetObjects;
        inline std::vector<GameObject*> centerObjects;
        inline std::vector<GameObject*> queuedObjectClusterObjects;
        inline std::vector<GameObject*> queuedTriggerClusterObjects;
    }
}