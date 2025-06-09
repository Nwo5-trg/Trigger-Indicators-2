#include "Utils.hpp"
#include "indicators/IndicatorVariables.hpp"

using namespace geode::prelude;

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

std::unordered_set<int> parseIntArray(const std::string& input) {
    std::unordered_set<int> intSet;
    auto start = 0;
    while (true) {
        auto comma = input.find(',', start);
        auto num = std::strtol(input.substr(start, comma - start).c_str(), nullptr, 10);
        if (num != 0) intSet.insert(num);
        if (comma == std::string::npos) break;
        start = comma + 1;
    }
    return intSet;
}