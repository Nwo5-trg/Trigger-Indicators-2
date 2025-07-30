#pragma once
#include "../utils/Types.hpp"

// some of these are more like shared than cache but wtv 
// i dont wanna make 2 namespaces for pretty much the same thing
namespace Cache {
    namespace Utils {
        inline std::unordered_set<int> currentObjGroupsSet;
        
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
    
    inline bool playtesting;

    inline int currentLayer;

    inline float layerAlphaMultiplier;

    inline cocos2d::CCDrawNode* gridDraw = nullptr;
    inline cocos2d::CCDrawNode* objectDraw = nullptr;

    inline cocos2d::CCDictionary* groupDict = nullptr;
    inline cocos2d::CCArray* triggers = nullptr;
    inline cocos2d::CCArray* moveTriggers = nullptr;

    inline cocos2d::CCNodeRGBA* gayNode = nullptr;
    inline cocos2d::ccColor4F currentChromaCol;

    namespace TriggerIndicators {
        inline float cullDistance;
        inline float thickness;

        inline cocos2d::ccColor4F col;
        inline cocos2d::ccColor4F extrasCol1;
        inline cocos2d::ccColor4F extrasCol2;

        inline std::vector<GameObject*> targetObjects;
        inline std::vector<GameObject*> centerObjects;
        inline std::vector<GameObject*> queuedObjectClusterObjects;
        inline std::vector<GameObject*> queuedTriggerClusterObjects;
    }

    namespace BetterParticles {
        inline float thickness;
        inline float centerLineThickness;
        
        // idk why im caching if im copyinghalf the time anyway but oh well
        inline cocos2d::ccColor4F primaryCol;
        inline cocos2d::ccColor4F secondaryCol;
        inline cocos2d::ccColor4F primaryColFill;
        inline cocos2d::ccColor4F secondaryColFill;
        inline cocos2d::ccColor4F centerLineCol;
    }

    namespace MoveIndicators {
        inline float thickness;
        inline float endPreviewThickness;
        inline float startRadius;
        inline float endSize;

        inline cocos2d::ccColor4F indicatorCol;
        inline cocos2d::ccColor4F centerIndicatorCol;
        inline cocos2d::ccColor4F startCol;
        inline cocos2d::ccColor4F endCol;
        inline cocos2d::ccColor4F endPreviewCol;

        inline std::unordered_set<int> sharedGroups;
        // first is real pos, second is pos after being moved by all the triggers before it
        inline std::vector<CornerRect> objectPreviews;
        inline std::vector<std::pair<cocos2d::CCPoint, cocos2d::CCPoint>> positions;
        inline std::vector<std::pair<cocos2d::CCPoint, cocos2d::CCPoint>> indicatorSegments;
        inline std::vector<GameObject*> targetObjects;
    }
}