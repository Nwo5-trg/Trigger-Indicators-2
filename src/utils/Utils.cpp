#include "Utils.hpp"
#include "../shared/Cache.hpp"
#include "../shared/Settings.hpp"

using namespace geode::prelude;

void Utils::drawLine(CCDrawNode* drawNode, CCPoint p1, CCPoint p2, float thickness, ccColor4F col) {
    // see taking like 3 weeks learning opengl payed off for smth 
    auto dir = ccpNormalize(p2 - p1);
    auto perp = ccp(-dir.y, dir.x) * (thickness / 2);
    CCPoint v[] {
        (p1 + perp), (p2 + perp), (p2 - perp), (p1 - perp)
    };
    drawNode->drawPolygon(v, 4, col, 0.0f, col);
}

void Utils::clusterObjects(const std::vector<GameObject*>& objs, float clusterSize) {
    Cache::Utils::clusters.clear();
    Cache::Utils::clusterMap.clear();

    for (auto obj : objs) {
        if (Cache::Utils::clusterMap.contains(obj)) continue;

        int currentClusterIndex = Cache::Utils::clusters.size();
        Cache::Utils::clusters.emplace_back();
        auto& currentCluster = Cache::Utils::clusters.back();

        Cache::Utils::clusterObjQueue.clear();
        Cache::Utils::clusterObjQueue.push_back(obj);
        Cache::Utils::clusterMap[obj] = currentClusterIndex;

        while (!Cache::Utils::clusterObjQueue.empty()) {
            auto obj = Cache::Utils::clusterObjQueue.back();
            auto pos = obj->getPosition();
            Cache::Utils::clusterObjQueue.pop_back();
            currentCluster.push_back(obj);

            for (auto neighbour : objs) {
                if (Cache::Utils::clusterMap.contains(neighbour)) continue;

                auto neighbourPos = neighbour->getPosition();

                if (fabs(pos.x - neighbourPos.x) <= clusterSize && fabsf(pos.y - neighbourPos.y) <= clusterSize) {
                    Cache::Utils::clusterMap[neighbour] = currentClusterIndex;
                    Cache::Utils::clusterObjQueue.push_back(neighbour);
                }
            }
        }
    }
}

CCPoint Utils::getLineCut(CCPoint origin, const CornerRect& rect) {
    auto direction = ((rect.p1 + (rect.p2 - rect.p1) / 2) - origin);
    auto intersection = origin + direction;
    float cutAt = 1.0f;

    for (float edge : {rect.p1.x, rect.p2.x}) {
        if (direction.x == 0.0f) continue;
        float t = (edge - origin.x) / direction.x;
        float y = origin.y + t * direction.y;
        if (t >= 0.0f && t <= 1.0f && y >= rect.p1.y && y <= rect.p2.y && t < cutAt) {
            intersection = ccp(edge, y);
            cutAt = t;
        }
    }

    for (float edge : {rect.p1.y, rect.p2.y}) {
        if (direction.y == 0.0f) continue;
        float t = (edge - origin.y) / direction.y;
        float x = origin.x + t * direction.x;
        if (t >= 0.0f && t <= 1.0f && x >= rect.p1.x && x <= rect.p2.x && t < cutAt) {
            intersection = ccp(x, edge);
            cutAt = t;
        }
    }

    return intersection;
}

// ccprotatebyangle give me an error for some reason idk so this is just ripped from there
CCPoint Utils::rotatePoint(CCPoint pos, CCPoint pivot, float rad) {
    auto r = pos - pivot;
	float cos = cosf(rad); float sin = sinf(rad);
	float t = r.x;
	r.x = t * cos - r.y * sin + pivot.x;
	r.y = t * sin + r.y * cos + pivot.y;
	return r;
}

std::unordered_set<int> Utils::parseIntArray(const std::string& input) {
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

CornerRect Utils::getObjectRect(GameObject* obj, float buffer) {
    CornerRect rect;
    auto pos = obj->getPosition();
    auto size = (obj->getContentSize() * ccp(obj->m_scaleX, obj->m_scaleY)) / 2;
    // HEY CCPOINT IS IT THAT HARD TO HAVE YOUR FUCKING OPERATORS WORK WITH FLOATS
    auto bufferPoint = ccp(buffer, buffer) / 2;
    rect.p1 = pos - size + bufferPoint;
    rect.p2 = pos + size + bufferPoint;
    return rect;
}
CornerRect Utils::getObjectsRect(const std::vector<GameObject*>& objs, float buffer) {
    if (objs.empty()) return {};
    CornerRect rect = {{FLT_MAX, FLT_MAX}, {-FLT_MAX, -FLT_MAX}};
    for (auto obj : objs) {
        auto pos = obj->getPosition();
        auto size = (obj->getContentSize() * ccp(obj->m_scaleX, obj->m_scaleY)) / 2;
        auto p1 = pos - size;
        auto p2 = pos + size;
        if (p1.x < rect.p1.x) rect.p1.x = p1.x;
        if (p1.y < rect.p1.y) rect.p1.y = p1.y;
        if (p2.x > rect.p2.x) rect.p2.x = p2.x;
        if (p2.y > rect.p2.y) rect.p2.y = p2.y;
    }
    auto bufferPoint = ccp(buffer, buffer) / 2;
    rect.p1 -= bufferPoint; 
    rect.p2 += bufferPoint;
    return rect;
}

CCPoint Utils::getTriggerBodyPos(GameObject* obj) {
    return ccp(obj->getPositionX(), obj->getPositionY() + (obj->m_scaleY * Constants::triggerBodyYOffset));
}

void Utils::updateLayerAlpha(GameObject* obj) {
    // yeah how tf am i supposed to format this might aswell hide it away in a function so update isnt messy
    Cache::layerAlphaMultiplier = Cache::currentLayer == -1 ||
        ((obj->m_editorLayer == Cache::currentLayer)
        || (obj->m_editorLayer2 == Cache::currentLayer))
    ? 1.0f : Settings::layerAlphaMultiplier;
}

void Utils::updateTriggerCol(ccColor4F& col, int id, bool chroma) {
    col = chroma ? Cache::currentChromaCol : triggerColorMap[id];
    col.a = Cache::layerAlphaMultiplier;
}
// technically i could still optimize duration lines like trigger indicators but ehhhhh
ccColor4F Utils::getTriggerCol(int id, bool alpha, bool chroma) {
    ccColor4F col;
    col = chroma ? Cache::currentChromaCol : triggerColorMap[id];
    if (alpha) col.a = Cache::layerAlphaMultiplier;
    return col;
}