#include "Indicators.hpp"
#include "DrawIndicators.hpp"
#include "../Variables.hpp"
#include "../Utils.hpp"

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
    int currentLayer = editor->m_currentLayer;

    if (Variables::hasCollisionIDs) {
        Variables::collisionDict->removeAllObjects();
        auto objs = editor->m_collisionBlocks;
        for (auto obj : CCArrayExt<EffectGameObject*>(objs)) {
            int key = obj->m_itemID;
            auto array = Variables::collisionDict->objectForKey(key);
            if (!array) Variables::collisionDict->setObject(CCArray::createWithObject(obj), key);
            else static_cast<CCArray*>(array)->addObject(obj);
        }
    }
    
    std::vector<GameObject*> targetObjects;
    std::vector<GameObject*> centerObjects;

    auto winSize = CCDirector::get()->getWinSize();
    float cullDistance = winSize.width * winSize.width * Variables::cullDistanceMultiplier;
    auto batchLayerPos = Variables::batchLayer->getPosition();
    float zoom = Variables::batchLayer->getScale();
    auto centerPos = ccp(((winSize.width / 2) - batchLayerPos.x) / zoom, ((winSize.height / 2) - batchLayerPos.y) / zoom);

    bool groupedObjSelected = false;
    if (Variables::noCullOnSelect) {
        auto selectedObjs = editor->m_editorUI->getSelectedObjects();
        for (auto obj : CCArrayExt<GameObject*>(selectedObjs)) {
            if (obj->m_groups) { // not really reliable but close enough this is a fucked setting anyway
                groupedObjSelected = true;
                break;
            }
        }
    }

    for (auto trigger : CCArrayExt<EffectGameObject*>(objs)) {
        if (!trigger) continue; // schizo real
        auto triggerPos = trigger->getPosition();
        
        if (Variables::spawnIndicators && trigger->m_isSpawnTriggered) { // no layer fade cuz its more optimised like this but tbf robtops doesnt do it either
            auto triggerScale = std::max(trigger->m_scaleX, trigger->m_scaleY);
            auto triggerBodyPos = ccp(triggerPos.x, triggerPos.y - (5 * triggerScale));
            drawSpawnIndicator(triggerBodyPos, triggerScale, zoom);
        }

        if (Variables::disableIndicators) continue;

        int id = trigger->m_objectID;
        if (Variables::triggerBlacklist.contains(id)) continue;

        if (id == 1006 && trigger->m_pulseTargetType != 1) continue; // only use trigger indicators for pulse if its targeting groups

        bool selected = trigger->m_isSelected;
        if (!selected && !groupedObjSelected && ccpDistanceSQ(centerPos, triggerPos) > (cullDistance / zoom)) continue; // this line of code like 100x performance call ts a crypto scam

        if (!Variables::hasCollisionIDs && collisionIDTriggers.contains(id) && trigger->m_itemID != 0) Variables::hasCollisionIDs = true;
        
        int target = trigger->m_targetGroupID;
        int center = trigger->m_centerGroupID;
        targetObjects.clear();
        centerObjects.clear();

        // item edit weirdness
        if (target != 0 && !Variables::groupBlacklist.contains(target) && id != 3619) pushBackObjects(groupDict, target, targetObjects, selected, triggerPos, false);
        if (center != 0 && !Variables::groupBlacklist.contains(center)) pushBackObjects(groupDict, center, centerObjects, selected, triggerPos, false);
        
        if (collisionIDTriggers.contains(id)) {
            int collisionID = trigger->m_itemID;
            int collisionID2 = trigger->m_itemID2;
            if (collisionID != 0) pushBackObjects(Variables::collisionDict, collisionID, targetObjects, selected, triggerPos, true);
            if (collisionID2 != 0) pushBackObjects(Variables::collisionDict, collisionID2, centerObjects, selected, triggerPos, true);
        }

        if (targetObjects.empty() && centerObjects.empty()) continue;

        Variables::currentLayerMultiplier = 1.0f * (currentLayer == -1 || ((trigger->m_editorLayer == currentLayer) || (trigger->m_editorLayer2 == currentLayer))? 1.0f : 0.5f);
        drawForTrigger(trigger, targetObjects, centerObjects);
    }
};

void pushBackObjects(CCDictionary* dict, int key, std::vector<GameObject*>& vector, bool triggerSelected, CCPoint triggerPos, bool collision) {
    if (auto array = static_cast<CCArray*>(dict->objectForKey(key))) {
        for (auto obj : CCArrayExt<GameObject*>(array)) {
            if (!collision && Variables::onlyTriggers) {
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