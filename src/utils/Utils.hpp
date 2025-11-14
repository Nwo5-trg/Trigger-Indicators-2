#pragma once

#include "Types.hpp"
#include "Constants.hpp"
#include "Enums.hpp"
#include "Easings.hpp"

namespace Utils {
    // so apparently robtops cocos2d has some scuffed drawsegment optimizations
    // soooo you need to do this so a million ppl stop dming me about shit 
    // randomly disappearing :3c
    // source: preveter like 8 months ago
    void drawLine(cocos2d::CCDrawNode* drawNode, cocos2d::CCPoint p1, cocos2d::CCPoint p2, float thickness, const cocos2d::ccColor4F& col);
    void drawDottedLine(cocos2d::CCDrawNode* drawNode, cocos2d::CCPoint p1, cocos2d::CCPoint p2, float thickness, const cocos2d::ccColor4F& col);
    void drawCircle(
        cocos2d::CCDrawNode* drawNode, cocos2d::CCPoint center, float radius, const cocos2d::ccColor4F& fillCol, 
        float thickness, const cocos2d::ccColor4F& outlineCol, unsigned int segments
    );
    void drawEllipse(
        cocos2d::CCDrawNode* drawNode, cocos2d::CCPoint center, cocos2d::CCSize size, const cocos2d::ccColor4F& fillCol, 
        float thickness, const cocos2d::ccColor4F& outlineCol, unsigned int segments
    );

    // clusters into cache so i dont make like a million vectors every call </3
    std::vector<std::vector<GameObject*>>& clusterObjects(const std::vector<GameObject*>& objs, float clusterSize);
    cocos2d::CCPoint getLineCut(cocos2d::CCPoint origin, const CornerRect& rect);

    cocos2d::CCPoint rotatePoint(cocos2d::CCPoint pos, cocos2d::CCPoint pivot, float rad);

    std::unordered_set<int> parseIntArray(const std::string& input);

    CornerRect getObjectRect(GameObject* obj, float buffer = 0.0f);
    CornerRect getObjectsRect(const std::vector<GameObject*>& objs, float buffer = 0.0f);

    void getSharedObjectGroups(const std::vector<GameObject*>& objs, std::unordered_set<int>& set);

    cocos2d::CCPoint getTriggerBodyPos(GameObject* obj);

    cocos2d::CCPoint getObjectsCenter(const std::vector<GameObject*>& objs);

    void createLayer(cocos2d::CCLayer*& layer, std::string id, int z);
    void createDrawNode(cocos2d::CCDrawNode*& drawNode, std::string id, cocos2d::CCNode* parent);

    inline std::unordered_map<int, cocos2d::ccColor4F> triggerColorMap {
        {901, {1.0f, 0.0f, 1.0f, 1.0f}}, {3006, {1.0f, 0.0f, 1.0f, 1.0f}}, {3011, {1.0f, 0.0f, 1.0f, 1.0f}},  
        {1616, {0.639f, 0.0f, 0.337f, 1.0f}}, {1006, {1.0f, 1.0f, 0.0f, 1.0f}}, {3010, {1.0f, 1.0f, 0.0f, 1.0f}},  
        {3015, {1.0f, 1.0f, 0.0f, 1.0f}}, {3617, {1.0f, 1.0f, 0.0f, 1.0f}}, {3620, {1.0f, 1.0f, 0.0f, 1.0f}},  
        {2015, {1.0f, 1.0f, 0.0f, 1.0f}}, {1007, {0.0f, 1.0f, 1.0f, 1.0f}}, {3009, {0.0f, 1.0f, 1.0f, 1.0f}},  
        {3014, {0.0f, 1.0f, 1.0f, 1.0f}}, {3615, {0.0f, 1.0f, 1.0f, 1.0f}}, {3619, {0.0f, 1.0f, 1.0f, 1.0f}},  
        {2066, {0.0f, 1.0f, 1.0f, 1.0f}}, {1049, {1.0f, 0.247f, 0.247f, 1.0f}}, {1268, {0.137f, 0.8f, 0.5f, 1.0f}},  
        {1346, {0.5f, 0.5f, 1.0f, 1.0f}}, {3007, {0.5f, 0.5f, 1.0f, 1.0f}}, {3012, {0.5f, 0.5f, 1.0f, 1.0f}},  
        {1913, {0.5f, 0.5f, 1.0f, 1.0f}}, {2067, {0.247f, 0.749f, 1.0f, 1.0f}}, {3008, {0.247f, 0.749f, 1.0f, 1.0f}},  
        {3013, {0.247f, 0.749f, 1.0f, 1.0f}}, {2062, {0.247f, 0.749f, 1.0f, 1.0f}}, {1347, {1.0f, 0.5f, 0.5f, 1.0f}},  
        {1914, {1.0f, 0.5f, 0.5f, 1.0f}}, {1585, {1.0f, 0.717f, 0.0f, 1.0f}}, {1814, {1.0f, 1.0f, 0.5f, 1.0f}},  
        {3016, {0.8f, 1.0f, 0.78f, 1.0f}}, {3660, {0.8f, 1.0f, 0.78f, 1.0f}}, {3661, {0.8f, 1.0f, 0.78f, 1.0f}},  
        {1595, {0.0f, 0.537f, 0.698f, 1.0f}}, {1611, {1.0f, 0.717f, 1.0f, 1.0f}}, {1811, {1.0f, 0.5f, 1.0f, 1.0f}},  
        {2999, {1.0f, 0.5f, 1.0f, 1.0f}}, {3612, {1.0f, 0.5f, 1.0f, 1.0f}}, {1817, {1.0f, 0.427f, 0.0f, 1.0f}},  
        {3618, {1.0f, 0.392f, 0.0f, 1.0f}}, {1912, {0.247f, 0.5f, 1.0f, 1.0f}}, {2068, {0.647f, 0.368f, 1.0f, 1.0f}},  
        {3607, {0.647f, 0.368f, 1.0f, 1.0f}}, {3608, {0.588f, 0.588f, 0.588f, 1.0f}}, {3602, {1.0f, 1.0f, 1.0f, 1.0f}},  
        {3603, {1.0f, 1.0f, 1.0f, 1.0f}}, {3604, {1.0f, 1.0f, 1.0f, 1.0f}}, {1615, {1.0f, 1.0f, 1.0f, 1.0f}},  
        {3613, {1.0f, 1.0f, 1.0f, 1.0f}}, {3662, {1.0f, 1.0f, 1.0f, 1.0f}}, {3640, {1.0f, 1.0f, 1.0f, 0.471f}},  
        {1816, {1.0f, 1.0f, 1.0f, 0.471f}}, {3643, {1.0f, 1.0f, 1.0f, 0.471f}}, {1935, {0.6f, 0.5f, 0.6f, 1.0f}},  
        {1932, {0.396f, 1.0f, 1.0f, 1.0f}}, {3606, {0.5f, 1.0f, 1.0f, 1.0f}}, {1815, {0.325f, 0.259f, 1.0f, 1.0f}},  
        {3609, {0.325f, 0.749f, 1.0f, 1.0f}}, {1812, {0.8f, 0.396f, 0.396f, 1.0f}}, {3600, {0.0f, 0.0f, 0.0f, 1.0f}},  
        {3022, {0.408f, 0.886f, 1.0f, 1.0f}}, {2902, {0.408f, 0.886f, 1.0f, 1.0f}}, {2905, {0.5f, 0.5f, 0.5f, 0.5f}},  
        {2907, {0.5f, 0.5f, 0.5f, 0.5f}}, {2913, {0.5f, 0.5f, 0.5f, 0.5f}}, {2915, {0.5f, 0.5f, 0.5f, 0.5f}},  
        {2916, {0.5f, 0.5f, 0.5f, 0.5f}}, {1520, {1.0f, 1.0f, 1.0f, 1.0f}}, {10001, {0.0f, 1.0f, 0.5f, 1.0f}}
    };

    inline std::unordered_map<Speed, float> speedMap {
        {Speed::Slow, 251.16f}, {Speed::Normal, 311.58f}, {Speed::Fast, 387.42f}, {Speed::Faster, 468.0f}, {Speed::Fastest, 576.0f}
    };

    inline std::unordered_set<int> areaTriggers {
        3006, 3007, 3008, 3009, 3010
    };

    // im just trusting when i did this chore for group label shenanigans
    inline std::unordered_set<int> triggersWithCenters {
        1346, 2067, 3016, 3006, 3007, 3008, 3009, 3010, 3608, 3613, 1912, 1914
    };

    // ditto
    inline std::unordered_set<int> noTargetTriggers {
        1817, 3641, 3614, 3615, 3617, 22, 24, 23, 25, 26, 27, 28, 55, 56, 57, 
        58, 59, 1915, 3017, 3019, 3018, 3020, 3021, 3023, 3033, 2903, 1934, 3602, 
        899, 1913, 2015, 2925, 1916, 2901, 2999, 3606, 1935, 2068, 3607, 2900, 
        1917, 3612, 33, 32, 1613, 1612, 1818, 1819, 1932, 2899, 2066, 2904, 2905, 
        2907, 2909, 2910, 2911, 2912, 2916, 2917, 2920, 2921, 2922, 2923, 2924, 
        1520, 3029, 3030, 3031, 31, 3619
    };

    void updateTriggerCol(cocos2d::ccColor4F& col, int id, bool chroma);
}