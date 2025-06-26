#include "Indicators.hpp"
#include "DrawIndicators.hpp"
#include "../Variables.hpp"

using namespace geode::prelude;

void updateIndicators(LevelEditorLayer* editor) {
    Variables::triggerIndicatorDraw->clear();
    Variables::triggerExtraDraw->clear();
    if (Variables::groupLabels) {
        Variables::triggerIndicatorGroupLayer->setVisible(true);
        Variables::triggerIndicatorGroupLayer->removeAllChildrenWithCleanup(true);
    } else Variables::triggerIndicatorGroupLayer->setVisible(false);

    if (Variables::disableMod) return;
    
    auto objs = editor->m_drawGridLayer->m_effectGameObjects;
    auto groupDict = editor->m_groupDict;
    auto currentLayer = editor->m_currentLayer;
    std::vector<GameObject*> targetObjects;
    std::vector<GameObject*> centerObjects;

    auto winSize = CCDirector::get()->getWinSize();
    auto cullDistance = winSize.width * winSize.width;
    auto batchLayerPos = Variables::batchLayer->getPosition();
    auto zoom = Variables::batchLayer->getScale();
    auto centerPos = ccp(((winSize.width / 2) - batchLayerPos.x) / zoom, ((winSize.height / 2) - batchLayerPos.y) / zoom);

    for (auto trigger : CCArrayExt<EffectGameObject*>(objs)) {
        if (!trigger) continue; // schizo real
        auto triggerPos = trigger->getPosition();
        
        if (Variables::spawnIndicators && trigger->m_isSpawnTriggered) { // no layer fade cuz its more optimised like this but tbf robtops doesnt do it either
            auto triggerScale = trigger->getScale();
            auto triggerBodyPos = ccp(triggerPos.x, triggerPos.y - (5 * triggerScale));
            drawSpawnIndicator(triggerBodyPos, triggerScale, zoom);
        }

        if (Variables::disableIndicators) continue;

        auto id = trigger->m_objectID;
        if (Variables::triggerBlacklist.contains(id)) continue;

        if (id == 1006 && trigger->m_pulseTargetType != 1) continue; // only use trigger indicators for pulse if its targeting groups


        auto selected = trigger->m_isSelected;
        if (!selected && ccpDistanceSQ(centerPos, triggerPos) > (cullDistance / zoom)) continue; // this line of code like 100x performance call ts a crypto scam
        auto target = trigger->m_targetGroupID;
        auto center = trigger->m_centerGroupID;
        targetObjects.clear();
        centerObjects.clear();

        if (target != 0 && !Variables::groupBlacklist.contains(target)) pushBackObjects(groupDict, target, targetObjects, selected, triggerPos);
        if (center != 0 && !Variables::groupBlacklist.contains(center)) pushBackObjects(groupDict, center, centerObjects, selected, triggerPos);

        if (targetObjects.empty() && centerObjects.empty()) continue;

        auto alpha = 1.0f * (currentLayer == -1 || ((trigger->m_editorLayer == currentLayer) || (trigger->m_editorLayer2 == currentLayer))? 1.0f : 0.5f);
        drawForTrigger(trigger, targetObjects, centerObjects, alpha);
    }
};

void pushBackObjects(CCDictionary* dict, int key, std::vector<GameObject*>& vector, bool triggerSelected, CCPoint triggerPos) {
    if (auto array = static_cast<CCArray*>(dict->objectForKey(key))) {
        for (auto obj : CCArrayExt<GameObject*>(array)) {
            if (Variables::onlyTriggers) {
                if (!obj->m_isTrigger) continue; // trigger only
                if (Variables::onlySpawn && !static_cast<EffectGameObject*>(obj)->m_isSpawnTriggered) continue;
            }

            if (!triggerSelected) {
                auto selected = obj->m_isSelected;
                if (selected) goto pushBack; // bite me
                if (Variables::onlySelected) continue; // previous line makes it so anything past this is not selected at all
                auto objPos = obj->getPosition();
                auto distance = ccpDistanceSQ(objPos, triggerPos); // did not know this function existed nice
                if (distance > Variables::maxDistance) continue;
            }
            pushBack:

            vector.push_back(obj);
        }
    }
}