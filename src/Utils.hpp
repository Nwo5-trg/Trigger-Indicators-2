#pragma once

inline const cocos2d::ccColor4F emptyCCC4F = {0.0f, 0.0f, 0.0f, 0.0f};
inline const cocos2d::ccColor4F aquaCCC4F = {0.0f, 1.0f, 1.0f, 1.0f};

inline const std::unordered_map<int, cocos2d::ccColor4F> colorMap = {
    {901, {1.0f, 0.0f, 1.0f, 1.0f}}, {3006, {1.0f, 0.0f, 1.0f, 1.0f}}, {3011, {1.0f, 0.0f, 1.0f, 1.0f}},  
    {1616, {0.639f, 0.0f, 0.337f, 1.0f}}, {1006, {1.0f, 1.0f, 0.0f, 1.0f}}, {3010, {1.0f, 1.0f, 0.0f, 1.0f}},  
    {3015, {1.0f, 1.0f, 0.0f, 1.0f}}, {3617, {1.0f, 1.0f, 0.0f, 1.0f}}, {3620, {1.0f, 1.0f, 0.0f, 1.0f}},  
    {2015, {1.0f, 1.0f, 0.0f, 1.0f}}, {1007, {0.0f, 1.0f, 1.0f, 1.0f}}, {3009, {0.0f, 1.0f, 1.0f, 1.0f}},  
    {3014, {0.0f, 1.0f, 1.0f, 1.0f}}, {3615, {0.0f, 1.0f, 1.0f, 1.0f}}, {3619, {0.0f, 1.0f, 1.0f, 1.0f}},  
    {2066, {0.0f, 1.0f, 1.0f, 1.0f}}, {1049, {1.0f, 0.247f, 0.247f, 1.0f}}, {1268, {0.137f, 0.8f, 0.498f, 1.0f}},  
    {1346, {0.498f, 0.498f, 1.0f, 1.0f}}, {3007, {0.498f, 0.498f, 1.0f, 1.0f}}, {3012, {0.498f, 0.498f, 1.0f, 1.0f}},  
    {1913, {0.498f, 0.498f, 1.0f, 1.0f}}, {2067, {0.247f, 0.749f, 1.0f, 1.0f}}, {3008, {0.247f, 0.749f, 1.0f, 1.0f}},  
    {3013, {0.247f, 0.749f, 1.0f, 1.0f}}, {2062, {0.247f, 0.749f, 1.0f, 1.0f}}, {1347, {1.0f, 0.498f, 0.498f, 1.0f}},  
    {1914, {1.0f, 0.498f, 0.498f, 1.0f}}, {1585, {1.0f, 0.717f, 0.0f, 1.0f}}, {1814, {1.0f, 1.0f, 0.498f, 1.0f}},  
    {3016, {0.8f, 1.0f, 0.78f, 1.0f}}, {3660, {0.8f, 1.0f, 0.78f, 1.0f}}, {3661, {0.8f, 1.0f, 0.78f, 1.0f}},  
    {1595, {0.0f, 0.537f, 0.698f, 1.0f}}, {1611, {1.0f, 0.717f, 0.988f, 1.0f}}, {1811, {1.0f, 0.498f, 1.0f, 1.0f}},  
    {2999, {1.0f, 0.498f, 1.0f, 1.0f}}, {3612, {1.0f, 0.498f, 1.0f, 1.0f}}, {1817, {1.0f, 0.427f, 0.0f, 1.0f}},  
    {3618, {1.0f, 0.392f, 0.0f, 1.0f}}, {1912, {0.247f, 0.498f, 1.0f, 1.0f}}, {2068, {0.647f, 0.368f, 1.0f, 1.0f}},  
    {3607, {0.647f, 0.368f, 1.0f, 1.0f}}, {3608, {0.588f, 0.588f, 0.588f, 1.0f}}, {3602, {1.0f, 1.0f, 1.0f, 1.0f}},  
    {3603, {1.0f, 1.0f, 1.0f, 1.0f}}, {3604, {1.0f, 1.0f, 1.0f, 1.0f}}, {1615, {1.0f, 1.0f, 1.0f, 1.0f}},  
    {3613, {1.0f, 1.0f, 1.0f, 1.0f}}, {3662, {1.0f, 1.0f, 1.0f, 1.0f}}, {3640, {1.0f, 1.0f, 1.0f, 0.471f}},  
    {1816, {1.0f, 1.0f, 1.0f, 0.471f}}, {3643, {1.0f, 1.0f, 1.0f, 0.471f}}, {1935, {0.6f, 0.498f, 0.6f, 1.0f}},  
    {1932, {0.396f, 1.0f, 1.0f, 1.0f}}, {3606, {0.498f, 1.0f, 1.0f, 1.0f}}, {1815, {0.325f, 0.259f, 0.98f, 1.0f}},  
    {3609, {0.325f, 0.749f, 1.0f, 1.0f}}, {1812, {0.8f, 0.396f, 0.396f, 1.0f}}, {3600, {0.0f, 0.0f, 0.0f, 1.0f}},  
    {3022, {0.408f, 0.886f, 1.0f, 1.0f}}, {2902, {0.408f, 0.886f, 1.0f, 1.0f}}, {2905, {0.498f, 0.498f, 0.498f, 0.498f}},  
    {2907, {0.498f, 0.498f, 0.498f, 0.498f}}, {2913, {0.498f, 0.498f, 0.498f, 0.498f}}, {2915, {0.498f, 0.498f, 0.498f, 0.498f}},  
    {2916, {0.498f, 0.498f, 0.498f, 0.498f}}, {10001, {0.0f, 1.0f, 0.498f, 1.0f}}
};

inline const std::unordered_set<int> collisionIDTriggers = {
    1815, 3609
};

inline const std::unordered_set<int> itemIDTriggers = {
    1611, 1817, 1811, 3614, 3615, 3617, 3619, 3620, 3641
};

cocos2d::ccColor4F getTriggerCol(int id);
cocos2d::ccColor4F getColWithAlpha(cocos2d::ccColor4F col);

std::vector<std::vector<GameObject*>> getClusters(const std::vector<GameObject*>& objs, float clusterSize);
cocos2d::CCPoint getLineCut(cocos2d::CCPoint triggerPos, cocos2d::CCPoint p1, cocos2d::CCPoint p2);

std::unordered_set<int> parseIntArray(const std::string& input);