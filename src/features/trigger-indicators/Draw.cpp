#include "Include.hpp"
#include "../../utils/Utils.hpp"
#include "../../shared/Cache.hpp"
#include "../../shared/Settings.hpp"

using namespace geode::prelude;
using namespace TriggerIndicators;

// im very on the fence about caching output pos idk
// maybeeeeeee sometime dont wanna rewrite shit now

void TriggerIndicators::draw(EffectGameObject* trigger, const std::vector<GameObject*>& objs, CCPoint outputPos) {
    if (objs.empty()) return;
    
    Cache::TriggerIndicators::queuedObjectClusterObjects.clear();
    Cache::TriggerIndicators::queuedObjectClusterObjects.reserve(objs.size());
    Cache::TriggerIndicators::queuedTriggerClusterObjects.clear();
    Cache::TriggerIndicators::queuedTriggerClusterObjects.reserve(objs.size());

    drawOutput(outputPos, {trigger->m_scaleX, trigger->m_scaleY});

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

void TriggerIndicators::drawClusters(CCPoint outputPos, bool isTrigger) {
    const auto& objs = isTrigger 
        ? Cache::TriggerIndicators::queuedTriggerClusterObjects 
        : Cache::TriggerIndicators::queuedObjectClusterObjects;
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
            drawToRect(outputPos, Utils::getObjectsRect(objs, Settings::TriggerIndicators::thickness));
        }
        return;
    }
    Utils::clusterObjects(objs, size);
    for (const auto& cluster : Cache::Utils::clusters) {
        drawToRect(outputPos, Utils::getObjectsRect(cluster, Settings::TriggerIndicators::thickness));
    }
}

void TriggerIndicators::drawToObject(CCPoint outputPos, GameObject* obj, bool isTrigger) {
    // draw boxes
    if (isTrigger ? Settings::TriggerIndicators::boxLineTriggers : Settings::TriggerIndicators::boxLineObjects) {
        drawToRect(outputPos, Utils::getObjectRect(obj, Settings::TriggerIndicators::thickness));
    } else {
        auto pos = isTrigger
            ? ccp(obj->getPositionX() - (obj->m_scaleX * Constants::extrasXOffset), Utils::getTriggerBodyPos(obj).y)
            : obj->getPosition();

        drawToPoint(outputPos, pos);

        if (isTrigger) drawInput(pos, {obj->m_scaleX, obj->m_scaleY});
    }
}

void TriggerIndicators::drawToRect(CCPoint outputPos, const CornerRect& rect) {
    Cache::gridDraw->drawRect(
        rect.p1, rect.p2, 
        Constants::transparentCCC4F, 
        Settings::TriggerIndicators::thickness, 
        Cache::TriggerIndicators::col
    );
    drawToPoint(outputPos, Utils::getLineCut(outputPos, rect));
}

void TriggerIndicators::drawToPoint(CCPoint outputPos, CCPoint pos) {
    Utils::drawLine(
        Cache::gridDraw, outputPos, pos, 
        Settings::TriggerIndicators::thickness, 
        Cache::TriggerIndicators::col
    );
}

void TriggerIndicators::drawInput(CCPoint pos, CCSize scale) {
    float maxScale = std::max(scale.width, scale.height);
    Cache::objectDraw->drawCircle(
        pos, 
        maxScale * Constants::extrasRadius, 
        Cache::TriggerIndicators::extrasCol1, 
        maxScale * Constants::extrasSizeThicknessMultiplier, 
        Cache::TriggerIndicators::extrasCol2, 
        Constants::extrasCircleDetail
    );
}

void TriggerIndicators::drawOutput(CCPoint pos, CCSize scale) {
    CCPoint v[] = {
        ccp(pos.x, pos.y),
        ccp(pos.x - (scale.width * Constants::extrasSize), pos.y + (scale.height * Constants::extrasSize)),
        ccp(pos.x - (scale.width * Constants::extrasSize), pos.y - (scale.height * Constants::extrasSize)),
    };
    Cache::objectDraw->drawPolygon(
        v, 3, 
        Cache::TriggerIndicators::extrasCol1, 
        std::max(scale.width, scale.height) * Constants::extrasSizeThicknessMultiplier, 
        Cache::TriggerIndicators::extrasCol2
    );
}
