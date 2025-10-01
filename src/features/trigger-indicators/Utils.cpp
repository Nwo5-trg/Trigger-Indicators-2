#include "Include.hpp"
#include "../../shared/Cache.hpp"
#include "../../shared/Settings.hpp"

using namespace geode::prelude;

namespace TriggerIndicators {
    void getObjects(EffectGameObject* trigger, int key, std::vector<GameObject*>& vector) {
        auto objs = static_cast<CCArray*>(Cache::groupDict->objectForKey(key)); 
        if (!objs) return;
        
        vector.reserve(objs->count());

        auto triggerPos = trigger->getPosition();

        for (auto obj : CCArrayExt<GameObject*>(objs)) {
            // robtop better not have some fucked obj where istrigger is true on a gameobject or smth
            bool isTrigger = obj->m_isTrigger;
            if (Settings::TriggerIndicators::onlyTriggers && !isTrigger) continue; 
            if (isTrigger && Settings::TriggerIndicators::onlySpawn && !static_cast<EffectGameObject*>(obj)->m_isSpawnTriggered) continue;

            if (trigger->m_isSelected || obj->m_isSelected) goto pushBack; // selected objects also always show connections
            if (Settings::TriggerIndicators::onlySelected) continue; // all selected objects would already be pushed back atp

            if (ccpDistanceSQ(obj->getPosition(), triggerPos) > Settings::TriggerIndicators::maxDistance) continue;

            pushBack:
            vector.push_back(obj);
        }
    }
}