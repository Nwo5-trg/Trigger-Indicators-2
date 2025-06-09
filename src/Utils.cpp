#include "Utils.hpp"
#include "indicators/IndicatorVariables.hpp"

using namespace geode::prelude;

const std::unordered_map<int, cocos2d::ccColor4F> colorMap = {
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

ccColor4F getTriggerCol(int id) { // paranoid about getting an invalid id
    if (IndicatorVars::chroma && IndicatorVars::triggerIndicatorDrawChromaNode) { // just cuz its gay doesnt mean we dont have to null check 3:<
        return ccc4FFromccc3B(IndicatorVars::triggerIndicatorDrawChromaNode->getColor());
    }
    if (colorMap.contains(id)) return colorMap.at(id);
    else return ccc4f(1.0f, 1.0f, 1.0f, 1.0f);
}

std::vector<std::vector<GameObject*>> getClusters(const std::vector<GameObject*>& objs, float clusterSize) {
    std::unordered_map<GameObject*, int> clusterMap;
    std::vector<std::vector<GameObject*>> clusters;

    for (auto obj : objs) {
        if (clusterMap.contains(obj)) continue;

        int currentClusterIndex = clusters.size();
        clusters.emplace_back();
        auto& currentCluster = clusters.back();

        std::vector<GameObject*> objQueue = {
            obj // aww he so alone 3:
        };
        clusterMap[obj] = currentClusterIndex;

        while (!objQueue.empty()) {
            auto obj = objQueue.back();
            auto pos = obj->getPosition();
            objQueue.pop_back();
            currentCluster.push_back(obj);

            for (auto neighbour : objs) {
                if (clusterMap.contains(neighbour)) continue;

                auto neighbourPos = neighbour->getPosition();

                if (fabs(pos.x - neighbourPos.x) <= clusterSize && fabs(pos.y - neighbourPos.y) <= clusterSize) {
                    clusterMap[neighbour] = currentClusterIndex;
                    objQueue.push_back(neighbour);
                }
            }
        }
    }
    return clusters;
}

CCPoint getLineCut(CCPoint triggerPos, CCPoint p1, CCPoint p2) {
        CCPoint centerPos = ccp(p1.x + ((p2.x - p1.x) / 2), p1.y + ((p2.y - p1.y) / 2));
        CCPoint direction = ccp(centerPos.x - triggerPos.x, centerPos.y - triggerPos.y);
        CCPoint intersection = centerPos;
        float cutAtT = 1.0f;

        for (float edge : {p1.x, p2.x}) {
            if (direction.x != 0) {
                float t = (edge - triggerPos.x) / direction.x;
                float y = triggerPos.y + t * direction.y;
                if (t >= 0 && t <= 1 && y >= p1.y && y <= p2.y && t < cutAtT) {
                    intersection = ccp(edge, y);
                    cutAtT = t;
                }
            }
        }

        for (float edge : {p1.y, p2.y}) {
            if (direction.y != 0) {
                float t = (edge - triggerPos.y) / direction.y;
                float x = triggerPos.x + t * direction.x;
                if (t >= 0 && t <= 1 && x >= p1.x && x <= p2.x && t < cutAtT) {
                    intersection = ccp(x, edge);
                    cutAtT = t;
                }
            }
        }

        return intersection;
    }