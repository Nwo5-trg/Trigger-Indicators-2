#include "Include.hpp"
#include "../../utils/Utils.hpp"
#include "../../shared/Cache.hpp"
#include "../../shared/Settings.hpp"

using namespace geode::prelude;

// im very on the fence about caching output pos idk
// maybeeeeeee sometime dont wanna rewrite shit now

namespace TriggerIndicators {
    void draw(EffectGameObject* trigger, const std::vector<GameObject*>& objs, CCPoint outputPos) {
        if (objs.empty()) return;
        
        Cache::TriggerIndicators::queuedObjectClusterObjects.clear();
        Cache::TriggerIndicators::queuedObjectClusterObjects.reserve(objs.size());
        Cache::TriggerIndicators::queuedTriggerClusterObjects.clear();
        Cache::TriggerIndicators::queuedTriggerClusterObjects.reserve(objs.size());

        if (!Settings::TriggerIndicators::alwaysDrawExtras) drawOutput(outputPos, {trigger->m_scaleX, trigger->m_scaleY});

        for (auto obj : objs) {
            bool isTrigger = obj->m_isTrigger;
            
            if (isTrigger ? Settings::TriggerIndicators::clusterTriggers : Settings::TriggerIndicators::clusterObjects) {
                if (isTrigger) Cache::TriggerIndicators::queuedTriggerClusterObjects.push_back(obj);
                else Cache::TriggerIndicators::queuedObjectClusterObjects.push_back(obj);
                continue;
            }

            drawToObject(outputPos, obj, isTrigger);
        }

        drawClusters(outputPos, false);
        drawClusters(outputPos, true);
    }

    void drawClusters(CCPoint outputPos, bool isTrigger) {
        const auto& objs = isTrigger 
            ? Cache::TriggerIndicators::queuedTriggerClusterObjects 
            : Cache::TriggerIndicators::queuedObjectClusterObjects;
        if (objs.empty()) return;

        float size = isTrigger
            ? Settings::TriggerIndicators::clusterTriggersSize
            : Settings::TriggerIndicators::clusterObjectsSize;
        int limit = isTrigger 
            ? Settings::TriggerIndicators::clusterTriggersMaxThreshold
            : Settings::TriggerIndicators::clusterObjectsMaxThreshold;

        if (objs.size() > limit) {
            bool fallbackToIndividual = isTrigger
                ? Settings::TriggerIndicators::clusterFallbackIndividualTriggers
                : Settings::TriggerIndicators::clusterFallbackIndividualObjects;
            
            if (fallbackToIndividual) {
                for (auto obj : objs) drawToObject(outputPos, obj, isTrigger);
            } else {
                drawToRect(outputPos, Utils::getObjectsRect(objs, Cache::TriggerIndicators::thickness));
            }
            return;
        }
        
        for (const auto& cluster : Utils::clusterObjects(objs, size)) {
            if (cluster.size() == 1) {
                drawToObject(outputPos, cluster[0], isTrigger);
                continue;
            }

            drawToRect(outputPos, Utils::getObjectsRect(cluster, Cache::TriggerIndicators::thickness));
        }
    }

    void drawToObject(CCPoint outputPos, GameObject* obj, bool isTrigger) {
        // draw boxes
        if (isTrigger ? Settings::TriggerIndicators::boxLineTriggers : Settings::TriggerIndicators::boxLineObjects) {
            drawToRect(outputPos, Utils::getObjectRect(obj, Cache::TriggerIndicators::thickness));
        } 
        else {
            auto pos = isTrigger ? getInputPos(obj) : obj->getPosition();

            drawToPoint(outputPos, pos);

            if (isTrigger && !Settings::TriggerIndicators::alwaysDrawExtras) {
                drawInput(pos, {obj->m_scaleX, obj->m_scaleY});
            }
        }
    }

    void drawToRect(CCPoint outputPos, const CornerRect& rect) {
        if (Cache::TriggerIndicators::shouldDrawDotted) {
            // i actually cant b bothered fuck you
            Utils::drawDottedLine(
                Cache::gridDraw, rect.p1, {rect.p1.x, rect.p2.y},
                Cache::TriggerIndicators::thickness, Cache::TriggerIndicators::col
            );
            Utils::drawDottedLine(
                Cache::gridDraw, {rect.p1.x, rect.p2.y}, rect.p2,
                Cache::TriggerIndicators::thickness, Cache::TriggerIndicators::col
            );
            Utils::drawDottedLine(
                Cache::gridDraw, rect.p2, {rect.p2.x, rect.p1.y},
                Cache::TriggerIndicators::thickness, Cache::TriggerIndicators::col
            );
            Utils::drawDottedLine(
                Cache::gridDraw, {rect.p2.x, rect.p1.y}, rect.p1,
                Cache::TriggerIndicators::thickness, Cache::TriggerIndicators::col
            );
        }
        else {
            Cache::gridDraw->drawRect(
                rect.p1, rect.p2, 
                Constants::transparentCCC4F, 
                Cache::TriggerIndicators::thickness, 
                Cache::TriggerIndicators::col
            );
        }

        drawToPoint(outputPos, Utils::getLineCut(outputPos, rect));
    }

    void drawToPoint(CCPoint outputPos, CCPoint pos) {
        if (Cache::TriggerIndicators::shouldDrawDotted) {
            Utils::drawDottedLine(
                Cache::gridDraw, outputPos, pos,
                Cache::TriggerIndicators::thickness,
                Cache::TriggerIndicators::col
            );
        }
        else {
            Utils::drawLine(
                Cache::gridDraw, outputPos, pos, 
                Cache::TriggerIndicators::thickness, 
                Cache::TriggerIndicators::col
            );
        }
    }

    void drawInput(CCPoint pos, CCSize scale) {
        float maxScale = std::max(scale.width, scale.height);
        Utils::drawCircle(
            Cache::objectDraw, pos, 
            maxScale * Constants::triggerIndicatorsExtrasRadius, 
            Cache::TriggerIndicators::extrasCol1, 
            maxScale * Constants::triggerIndicatorsExtrasSizeThicknessMultiplier, 
            Cache::TriggerIndicators::extrasCol2, 
            Constants::triggerIndicatorsExtrasCircleDetail
        );
        // Cache::objectDraw->drawDot(pos, maxScale * Constants::triggerIndicatorsExtrasRadius, Cache::chromaCol0);
    }

    void drawOutput(CCPoint pos, CCSize scale) {
        if (Settings::TriggerIndicators::circleOutputExtras) {
            // i love this little returning void trick i learned by ~~stealing~~ from allium
            pos.x += Constants::triggerIndicatorsExtrasInputXOffset - Constants::triggerIndicatorsExtrasOutputXOffset;
            return drawInput(pos, scale);
        }

        CCSize size = {
            scale.width * (Constants::triggerIndicatorsExtrasSize / 2),
            scale.height * Constants::triggerIndicatorsExtrasSize
        };
        CCPoint v[] = {
            ccp(pos.x - size.width, pos.y + size.height),
            ccp(pos.x - size.width, pos.y - size.height),
            ccp(pos.x + size.width, pos.y),
        };
        Cache::objectDraw->drawPolygon(
            v, 3, 
            Cache::TriggerIndicators::extrasCol1, 
            std::max(scale.width, scale.height) * Constants::triggerIndicatorsExtrasSizeThicknessMultiplier, 
            Cache::TriggerIndicators::extrasCol2
        );
    }
}