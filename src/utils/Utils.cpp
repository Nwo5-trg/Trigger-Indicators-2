#include "Utils.hpp"
#include "../shared/Cache.hpp"

using namespace geode::prelude;

namespace Utils {
    constexpr cocos2d::ccVertex2F vertFromPoint(const cocos2d::CCPoint& p) { return {p.x, p.y}; }

    void drawLine(CCDrawNode* drawNode, CCPoint p1, CCPoint p2, float thickness, const ccColor4F& col) {
        unsigned int vertexCount = 6 * 3;

        if (drawNode->m_nBufferCount + vertexCount > drawNode->m_uBufferCapacity) {
            drawNode->m_uBufferCapacity += MAX(drawNode->m_uBufferCapacity, vertexCount);
            drawNode->m_pBuffer = static_cast<ccV2F_C4B_T2F*>(
                realloc(drawNode->m_pBuffer, drawNode->m_uBufferCapacity * sizeof(ccV2F_C4B_T2F))
            );
        }

        auto n = ccpNormalize(ccpPerp(ccpSub(p2, p1)));
        auto t = ccpPerp(n);

        auto nw = ccpMult(n, thickness);
        auto tw = ccpMult(t, thickness);
        auto v0 = vertFromPoint(ccpSub(p2, ccpAdd(nw, tw)));
        auto v1 = vertFromPoint(ccpAdd(p2, ccpSub(nw, tw)));
        auto v2 = vertFromPoint(ccpSub(p2, nw));
        auto v3 = vertFromPoint(ccpAdd(p2, nw));
        auto v4 = vertFromPoint(ccpSub(p1, nw));
        auto v5 = vertFromPoint(ccpAdd(p1, nw));
        auto v6 = vertFromPoint(ccpSub(p1, ccpSub(nw, tw)));
        auto v7 = vertFromPoint(ccpAdd(p1, ccpAdd(nw, tw)));

        ccV2F_C4B_T2F_Triangle* triangles =
            reinterpret_cast<ccV2F_C4B_T2F_Triangle*>(drawNode->m_pBuffer + drawNode->m_nBufferCount);

        auto col4b = ccc4BFromccc4F(col);

        // this might be against the geneva convention idk
        triangles[0] = {
            {v0, col4b, {}}, {v1, col4b, {}}, {v2, col4b, {}}
        };
        triangles[1] = {
            {v3, col4b, {}}, {v1, col4b, {}}, {v2, col4b, {}}
        };
        triangles[2] = {
            {v3, col4b, {}}, {v4, col4b, {}}, {v2, col4b, {}}
        };
        triangles[3] = {
            {v3, col4b, {}}, {v4, col4b, {}}, {v5, col4b, {}}
        };
        triangles[4] = {
            {v6, col4b, {}}, {v4, col4b, {}}, {v5, col4b, {}}
        };
        triangles[5] = {
            {v6, col4b, {}}, {v7, col4b, {}}, {v5, col4b, {}}
        };

        drawNode->m_nBufferCount += vertexCount;
        drawNode->m_bDirty = true;
    }


    void clusterObjects(const std::vector<GameObject*>& objs, float clusterSize) {
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

    CCPoint getLineCut(CCPoint origin, const CornerRect& rect) {
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
    CCPoint rotatePoint(CCPoint pos, CCPoint pivot, float rad) {
        auto r = pos - pivot;
        float cos = cosf(rad); float sin = sinf(rad);
        float t = r.x;
        r.x = t * cos - r.y * sin + pivot.x;
        r.y = t * sin + r.y * cos + pivot.y;
        return r;
    }

    // would replace w/ an inlined version of geodes function but im lazy and its only 4r settings so
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

    CornerRect getObjectRect(GameObject* obj, float buffer) {
        CornerRect rect;
        auto pos = obj->getPosition();
        auto size = (obj->getContentSize() * ccp(obj->m_scaleX, obj->m_scaleY)) / 2;

        rect.p1 = pos - size;
        rect.p2 = pos + size;

        if (buffer == 0.0f) return rect;

        buffer /= 2; 
        // HEY CCPOINT IS IT THAT HARD TO HAVE YOUR FUCKING OPERATORS WORK WITH FLOATS
        rect.p1.x -= buffer; rect.p1.y -= buffer;
        rect.p2.x += buffer; rect.p2.y += buffer;

        return rect;
    }
    CornerRect getObjectsRect(const std::vector<GameObject*>& objs, float buffer) {
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

        if (buffer == 0.0f) return rect;

        buffer /= 2;
        rect.p1.x -= buffer; rect.p1.y -= buffer;
        rect.p2.x += buffer; rect.p2.y += buffer;

        return rect;
    }

    void getSharedObjectGroups(const std::vector<GameObject*>& objs, std::unordered_set<int>& set) {
        set.clear();
        if (objs.empty()) return;

        auto firstGroups = objs[0]->m_groups;
        if (!firstGroups) return;
    
        set.insert(firstGroups->begin(), firstGroups->end());
        set.erase(0);

        for (auto obj : objs) {
            auto groups = obj->m_groups;
            if (!groups) {
                set.clear(); return;
            }

            Cache::Utils::currentObjGroupsSet.clear();
            Cache::Utils::currentObjGroupsSet.insert(groups->begin(), groups->end());

            for (auto it = set.begin(); it != set.end();) {
                if (!Cache::Utils::currentObjGroupsSet.contains(*it)) it = set.erase(it);
                else it++;
            }

            if (set.empty()) return;
        }
    }

    CCPoint getTriggerBodyPos(GameObject* obj) {
        return ccp(obj->getPositionX(), obj->getPositionY() + (obj->m_scaleY * Constants::triggerBodyYOffset));
    }

    CCPoint getObjectsCenter(const std::vector<GameObject*>& objs) {
        auto rect = getObjectsRect(objs);
        return (rect.p1 + rect.p2) / 2;
    }

    void createLayer(CCLayer*& layer, std::string id, int z) {
        layer = CCLayer::create();
        layer->setPosition(0.0f, 0.0f);
        layer->setZOrder(z);
        layer->setID(id);
        LevelEditorLayer::get()->m_objectLayer->addChild(layer);
    }
    void createDrawNode(CCDrawNode*& drawNode, std::string id, cocos2d::CCNode* parent) {
        drawNode = CCDrawNode::create();
        drawNode->setPosition(0.0f, 0.0f);
        drawNode->setBlendFunc({GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA});
        parent->addChild(drawNode);
    }

    void updateTriggerCol(ccColor4F& col, int id, bool chroma) {
        col = chroma ? Cache::currentChromaCol : triggerColorMap[id];
        col.a = Cache::layerAlphaMultiplier;
    }
}