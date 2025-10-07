#include "Include.hpp"
#include "../../shared/Cache.hpp"
#include "../../shared/Settings.hpp"

using namespace geode::prelude;

namespace MoveIndicators {
    void create(EffectGameObject* trigger) {
        // move trigger
        if(trigger->m_objectID != 901) return; 

        // basically indicator enabled for move triggers, like how clean startpos uses iceblock for freemode iirc
        if (!trigger->m_isIceBlock) return;
        
        int target = trigger->m_targetGroupID;
        if (target == 0) return;

        if ( // culling
            !trigger->m_isSelected 
            && ccpDistanceSQ(Cache::View::relativeCenter, trigger->getPosition()) 
            > Cache::View::cullDistanceSQ
        ) return;

        // idc if this could be like slight optimized with a constant might do that later idk prolly not
        if (trigger->m_moveOffset == CCPointZero) return;

        Cache::MoveIndicators::targetObjects.clear();
        getObjects(trigger, target);
        if (Cache::MoveIndicators::targetObjects.empty()) return;

        // only some get opacity customization cuz i dont think setting 
        // inidcator or start/end opacity is really needed cuz itll look bad anyway
        Cache::MoveIndicators::indicatorCol.a = Cache::layerAlphaMultiplier;
        Cache::MoveIndicators::centerIndicatorCol.a = Cache::layerAlphaMultiplier 
        * Settings::MoveIndicators::centerIndicatorCol.a;
        Cache::MoveIndicators::startCol.a = Cache::layerAlphaMultiplier;
        Cache::MoveIndicators::endCol.a = Cache::layerAlphaMultiplier;
        Cache::MoveIndicators::endPreviewCol.a = Cache::layerAlphaMultiplier 
        * Settings::MoveIndicators::endPreviewCol.a;

        draw(trigger);
    }

    void getObjects(EffectGameObject* trigger, int key) {
        auto objs = static_cast<CCArray*>(Cache::groupDict->objectForKey(key)); 
        if (!objs) return;
        
        Cache::MoveIndicators::targetObjects.reserve(objs->count());

        auto triggerPos = trigger->getPosition();

        for (auto obj : CCArrayExt<GameObject*>(objs)) {
            if (Settings::MoveIndicators::excludeTriggers && obj->m_isTrigger) continue;

            if (trigger->m_isSelected || obj->m_isSelected) goto pushBack;
            if (ccpDistanceSQ(obj->getPosition(), triggerPos) > Cache::View::cullDistanceSQ) continue;

            pushBack:
            Cache::MoveIndicators::targetObjects.push_back(obj);
        }
    }
}