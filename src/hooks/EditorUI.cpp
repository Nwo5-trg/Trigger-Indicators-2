#include <Geode/modify/EditorUI.hpp>
#include "../shared/Settings.hpp"
#include "../shared/Cache.hpp"
#include "../utils/Utils.hpp"
#include "../features/trigger-indicators/Include.hpp"

using namespace geode::prelude;

class $modify(EditorUIHook, EditorUI) {
    // to avoid camera dragging ill js do wat allium did and noop
    bool ccTouchBegan(CCTouch* p0, CCEvent* p1) {
        resetDragging();

        if (!Settings::Utils::DragTriggers::enabled) {
            return EditorUI::ccTouchBegan(p0, p1);
        }

        // doenst account 4r scale but that could get complicated and this works good enough

        auto touchPos = m_editorLayer->m_objectLayer->convertTouchToNodeSpace(p0);

        auto obj = m_editorLayer->objectAtPosition(
            touchPos - ccp(Constants::triggerIndicatorsExtrasOutputXOffset, 0.0f)
        );
        if (
            !obj || !obj->m_isTrigger 
            || !TriggerIndicators::isValidTrigger(static_cast<EffectGameObject*>(obj))
        ) return EditorUI::ccTouchBegan(p0, p1);

        Cache::Utils::DragTriggers::isCenter = false;

        // this is dumb and stupid but it works
        float distance = Constants::triggerIndicatorsExtrasSize * Constants::triggerIndicatorsExtrasSize * Constants::cullDistanceBuffer;
        if (Utils::triggersWithCenters.contains(obj->m_objectID)) {
            auto outputPos = TriggerIndicators::getOutputPos(obj, false, true);
            if (ccpDistanceSQ(touchPos, outputPos) > distance) {
                outputPos = TriggerIndicators::getOutputPos(obj, true, true);
                if (ccpDistanceSQ(touchPos, outputPos) > distance) {
                    return EditorUI::ccTouchBegan(p0, p1);
                }
                else {
                    Cache::Utils::DragTriggers::isCenter = true;
                }
            }
        }
        else {
            auto outputPos = TriggerIndicators::getOutputPos(obj, false, false);
            if (ccpDistanceSQ(touchPos, outputPos) > distance) {
                return EditorUI::ccTouchBegan(p0, p1);
            }
            Cache::Utils::DragTriggers::isCenter = false;
        }

        Cache::Utils::DragTriggers::target = static_cast<EffectGameObject*>(obj);

        return true;
    }

    void ccTouchMoved(CCTouch* p0, CCEvent* p1) {
        if (!Settings::Utils::DragTriggers::enabled || !Cache::Utils::DragTriggers::target) {
            return EditorUI::ccTouchMoved(p0, p1);
        }

        Cache::Utils::DragTriggers::dragActive = true;
        Cache::Utils::DragTriggers::touchPos = m_editorLayer->m_objectLayer->convertTouchToNodeSpace(p0);
    }

    void ccTouchEnded(CCTouch* p0, CCEvent* p1) {
        if (!Settings::Utils::DragTriggers::enabled || !Cache::Utils::DragTriggers::dragActive) {
            resetDragging();
            return EditorUI::ccTouchEnded(p0, p1);
        }

        handleTriggerDrag(m_editorLayer->m_objectLayer->convertTouchToNodeSpace(p0));
        resetDragging();
    }

    void onPause(CCObject* sender) {
        resetDragging();
        EditorUI::onPause(sender);
    }

    void onPlaytest(CCObject* sender) {
        resetDragging();
        EditorUI::onPlaytest(sender);
    }

    void resetDragging() {
        Cache::Utils::DragTriggers::target = nullptr;
        Cache::Utils::DragTriggers::dragActive = false;
    }

    void handleTriggerDrag(CCPoint release) {
        auto obj = m_editorLayer->objectAtPosition(release);

        if (!obj || (!obj->m_isTrigger && Settings::Utils::DragTriggers::onlyTriggers)) return;
        auto objs = CCArray::createWithObject(obj);
        if (obj->m_isSelected) objs = getSelectedObjects();

        // we get a lil silly :3c
        int& group = Cache::Utils::DragTriggers::isCenter 
            ? Cache::Utils::DragTriggers::target->m_centerGroupID
            : Cache::Utils::DragTriggers::target->m_targetGroupID;
        if (group == 0) {
            group = m_editorLayer->getNextFreeGroupID(m_editorLayer->m_objects);
            if (!Cache::Utils::DragTriggers::isCenter) {
                auto label = Cache::Utils::DragTriggers::target->getObjectLabel();
                if (label) label->setString(numToString(group).c_str());
            }
        }

        bool removing = obj->belongsToGroup(group);
        for (auto obj : CCArrayExt<GameObject*>(objs)) {
            if (Settings::Utils::DragTriggers::onlyTriggers && !obj->m_isTrigger) {
                continue;
            }

            // cant use ghidra rn so im not exactly sure how these functions work but this seems to do the trick
            // from what i can tell the editor layer functions handle adding it to dicts and stuff 
            // and the object functions change memebers
            // god im out of practice when it comes to modding i used to know all of this </3
            if (removing) {
                m_editorLayer->removeFromGroup(obj, group);
                obj->removeFromGroup(group);
            }
            else {
                // i really wanna know what this param does but building takes forever on ts
                m_editorLayer->addToGroup(obj, group, true);
                obj->addToGroup(group);
            }

            if (obj->m_isTrigger) {
                if (removing ? Settings::Utils::DragTriggers::autoSpawnDisable : Settings::Utils::DragTriggers::autoSpawnEnable) {
                    static_cast<EffectGameObject*>(obj)->m_isSpawnTriggered = !removing;
                }
                if (removing ? Settings::Utils::DragTriggers::autoMultiDisable : Settings::Utils::DragTriggers::autoMultiEnable) {
                    static_cast<EffectGameObject*>(obj)->m_isMultiTriggered = !removing;
                }
            }
        }
    }
};