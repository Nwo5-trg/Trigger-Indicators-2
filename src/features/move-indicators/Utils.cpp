#include "Include.hpp"
#include "../../shared/Cache.hpp"
#include "../../shared/Settings.hpp"
#include "../../utils/Utils.hpp"

using namespace geode::prelude;
using namespace MoveIndicators;

void MoveIndicators::getPositions(EffectGameObject* trigger, MoveIndicatorMode mode) {
    switch (mode) {
        case MoveIndicatorMode::Cluster: {
            Cache::MoveIndicators::positions.reserve(Cache::MoveIndicators::targetObjects.size());

            if (Cache::MoveIndicators::targetObjects.size() > Settings::MoveIndicators::clusterMaxThreshold) {
                return getPositions(trigger, Settings::MoveIndicators::clusterFallbackType);
            }

            Utils::clusterObjects(Cache::MoveIndicators::targetObjects, Settings::MoveIndicators::clusterSize);

            for (const auto& cluster : Cache::Utils::clusters) {
                auto pos = Utils::getObjectsCenter(cluster);
                Cache::MoveIndicators::positions.emplace_back(pos, getObjectMovedPos(pos, trigger));
            }

            return;
        }
        case MoveIndicatorMode::OnTrigger: {
            Cache::MoveIndicators::positions.reserve(1);
            auto pos = Utils::getTriggerBodyPos(trigger);
            Cache::MoveIndicators::positions.emplace_back(pos, getObjectMovedPos(pos, trigger));
            return;
        }
        case MoveIndicatorMode::Rect: {
            Cache::MoveIndicators::positions.reserve(1);
            auto pos = Utils::getObjectsCenter(Cache::MoveIndicators::targetObjects);
            Cache::MoveIndicators::positions.emplace_back(pos, getObjectMovedPos(pos, trigger));
            return;
        }
        case MoveIndicatorMode::Disable: {
            return;
        }
    }
}

void MoveIndicators::getObjectPreview(CCPoint offset) {
    Cache::MoveIndicators::objectPreviews.clear();
    Cache::MoveIndicators::objectPreviews.reserve(Cache::MoveIndicators::targetObjects.size());
    for (auto obj : Cache::MoveIndicators::targetObjects) {
        Cache::MoveIndicators::objectPreviews.push_back(Utils::getObjectRect(obj) += offset);
    }
}

CCPoint MoveIndicators::getObjectMovedPos(CCPoint pos, EffectGameObject* target) {
    // when i add better duration lines add the triggers duration to this so 
    // any move triggers on the path also get accounted for
    auto triggerX = target->getPositionX();
    for (auto trigger : CCArrayExt<EffectGameObject*>(Cache::moveTriggers)) {
        if (
            trigger->getPositionX() >= triggerX 
                || !Cache::MoveIndicators::sharedGroups.contains(trigger->m_targetGroupID)
                || trigger->m_isSpawnTriggered
                || trigger->m_isTouchTriggered
        ) continue;

        pos += trigger->m_moveOffset;
    }

    return pos;
}