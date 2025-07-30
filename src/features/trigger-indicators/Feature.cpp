#include "Include.hpp"
#include "../../shared/Cache.hpp"
#include "../../shared/Settings.hpp"
#include "../../utils/Utils.hpp"

using namespace geode::prelude;
using namespace TriggerIndicators;

void TriggerIndicators::create(EffectGameObject* trigger) {
    int target = trigger->m_targetGroupID;
    int center = trigger->m_centerGroupID;
    if (target == 0 && center == 0) return;

    int id = trigger->m_objectID; 
    if (Settings::TriggerIndicators::triggerBlacklist.contains(id)) return;
    if (id == 1006 && trigger->m_pulseTargetType != 1) return; // pulse trigger only draw if theyre on group setting

    if ( // culling
        !trigger->m_isSelected 
        && ccpDistanceSQ(Cache::View::relativeCenter, trigger->getPosition()) 
        > Cache::TriggerIndicators::cullDistance
    ) return;

    Cache::TriggerIndicators::targetObjects.clear();
    Cache::TriggerIndicators::centerObjects.clear();

    if (target != 0 && !Settings::TriggerIndicators::groupBlacklist.contains(target)) { // item edit uses target group id
        getObjects(trigger, target, Cache::TriggerIndicators::targetObjects);
    }
    if (center != 0 && !Settings::TriggerIndicators::groupBlacklist.contains(center)) {
        getObjects(trigger, center, Cache::TriggerIndicators::centerObjects);
    }

    auto triggerScale = CCSize(trigger->m_scaleX, trigger->m_scaleX);
    auto triggerPos = trigger->getPosition();
    auto triggerBodyPos = Utils::getTriggerBodyPos(trigger);

    auto targetOffset = Cache::TriggerIndicators::centerObjects.empty() 
        ? ccp(
            triggerBodyPos.x + (triggerScale.width * (Constants::triggerIndicatorsExtrasXOffset + Constants::triggerIndicatorsExtrasSize)), 
            triggerBodyPos.y
        )
        : ccp(
            triggerBodyPos.x + (triggerScale.width * (Constants::triggerIndicatorsExtrasXOffset + Constants::triggerIndicatorsExtrasSize)), 
            triggerBodyPos.y + (triggerScale.height * Constants::triggerIndicatorsTargetTypesYOffset)
        );
    auto centerOffset = ccp(
        triggerBodyPos.x + (triggerScale.width * (Constants::triggerIndicatorsExtrasXOffset + Constants::triggerIndicatorsExtrasSize)), 
        triggerBodyPos.y - (triggerScale.height * Constants::triggerIndicatorsTargetTypesYOffset)
    );
    
    if (trigger->m_activateGroup && id == 1049) id = 10001; // toggle triggers
    Utils::updateTriggerCol(Cache::TriggerIndicators::col, id, Settings::TriggerIndicators::chroma);
    Cache::TriggerIndicators::extrasCol1.a = Cache::layerAlphaMultiplier;
    Cache::TriggerIndicators::extrasCol2.a = Cache::layerAlphaMultiplier;

    draw(trigger, Cache::TriggerIndicators::targetObjects, targetOffset);
    draw(trigger, Cache::TriggerIndicators::centerObjects, centerOffset);
}

void TriggerIndicators::getObjects(EffectGameObject* trigger, int key, std::vector<GameObject*>& vector) {
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