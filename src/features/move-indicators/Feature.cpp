#include "Include.hpp"
#include "../../shared/Cache.hpp"
#include "../../shared/Settings.hpp"

using namespace geode::prelude;
using namespace MoveIndicators;

void MoveIndicators::create(EffectGameObject* trigger) {
    // move trigger
    if(trigger->m_objectID != 901) return; 

    // basically indicator enabled for move triggers, like how clean startpos uses iceblock for freemode iirc
    if (!trigger->m_isIceBlock) return;
    
    int target = trigger->m_targetGroupID;
    if (target == 0) return;

    if ( // culling
        !trigger->m_isSelected 
        && ccpDistanceSQ(Cache::View::relativeCenter, trigger->getPosition()) 
        > Cache::View::cullDistance
    ) return;

    // idc if this could be like slight optimized with a constant might do that later idk prolly not
    if (trigger->m_moveOffset == ccp(0.0f, 0.0f)) return;

    Cache::MoveIndicators::targetObjects.clear();
    getObjects(trigger, target);
    if (Cache::MoveIndicators::targetObjects.empty()) return;

    Cache::MoveIndicators::indicatorCol.a = Cache::layerAlphaMultiplier;
    Cache::MoveIndicators::startCol.a = Cache::layerAlphaMultiplier;
    Cache::MoveIndicators::endCol.a = Cache::layerAlphaMultiplier;
    Cache::MoveIndicators::endPreviewCol.a = Cache::layerAlphaMultiplier;
    // Utils::getSharedObjectGroups(Cache::MoveIndicators::targetObjects, Cache::MoveIndicators::sharedGroups);
    draw(trigger);
}

void MoveIndicators::getObjects(EffectGameObject* trigger, int key) {
    auto objs = static_cast<CCArray*>(Cache::groupDict->objectForKey(key)); 
    if (!objs) return;
    
    Cache::MoveIndicators::targetObjects.reserve(objs->count());

    auto triggerPos = trigger->getPosition();

    for (auto obj : CCArrayExt<GameObject*>(objs)) {
        if (Settings::MoveIndicators::excludeTriggers && obj->isTrigger()) continue;

        if (trigger->m_isSelected || obj->m_isSelected) goto pushBack;
        if (ccpDistanceSQ(obj->getPosition(), triggerPos) > Cache::View::cullDistance) continue;

        pushBack:
        Cache::MoveIndicators::targetObjects.push_back(obj);
    }
}