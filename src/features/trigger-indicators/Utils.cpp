#include "Include.hpp"
#include "../../shared/Cache.hpp"
#include "../../shared/Settings.hpp"
#include "../../utils/Utils.hpp"

using namespace geode::prelude;

namespace TriggerIndicators {
    bool isValidTrigger(EffectGameObject* trigger) {
        int id = trigger->m_objectID; 
        if (Settings::TriggerIndicators::triggerBlacklist.contains(id)) return false;
        if (id == 1006 && trigger->m_pulseTargetType != 1) return false; // pulse trigger only draw if theyre on group setting
        if (id == 1914 && static_cast<CameraTriggerGameObject*>(trigger)->m_exitStatic) return false; // static camera exit
        
        return true;
    }

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

    CCPoint getInputPos(GameObject* trigger) {
        return ccp(trigger->getPositionX() - 
            (trigger->m_scaleX * Constants::triggerIndicatorsExtrasInputXOffset), Utils::getTriggerBodyPos(trigger).y);
    }

    CCPoint getOutputPos(GameObject* trigger, bool center, bool hasCenter) {
        auto triggerScale = CCSize(trigger->m_scaleX, trigger->m_scaleX);
        auto triggerBodyPos = Utils::getTriggerBodyPos(trigger);

        if (!center || !hasCenter) {
            return hasCenter 
                ? ccp(
                    triggerBodyPos.x + (triggerScale.width * (Constants::triggerIndicatorsExtrasOutputXOffset)), 
                    triggerBodyPos.y + (triggerScale.height * Constants::triggerIndicatorsExtrasOutputYOffset)
                )
                : ccp(
                    triggerBodyPos.x + (triggerScale.width * Constants::triggerIndicatorsExtrasOutputXOffset), 
                    triggerBodyPos.y
                );
        }

        return ccp(
            triggerBodyPos.x + (triggerScale.width * Constants::triggerIndicatorsExtrasOutputXOffset), 
            triggerBodyPos.y - (triggerScale.height * Constants::triggerIndicatorsExtrasOutputYOffset)
        );
    }
}