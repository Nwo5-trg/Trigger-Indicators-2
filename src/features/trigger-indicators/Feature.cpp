#include "Include.hpp"
#include "../../shared/Cache.hpp"
#include "../../shared/Settings.hpp"
#include "../../utils/Utils.hpp"

using namespace geode::prelude;

namespace TriggerIndicators {
    void create(EffectGameObject* trigger) {
        int target = trigger->m_targetGroupID;
        int center = trigger->m_centerGroupID;
        if (target == 0 && center == 0 && !Settings::TriggerIndicators::alwaysDrawExtras) return;

        int id = trigger->m_objectID; 
        if (!isValidTrigger(trigger)) return;

        if ( // culling
            !trigger->m_isSelected 
            && ccpDistanceSQ(Cache::View::relativeCenter, trigger->getPosition()) 
            > Cache::TriggerIndicators::cullDistance
        ) return;

        if (Settings::TriggerIndicators::alwaysDrawExtras) {
            auto triggerScale = CCSize(trigger->m_scaleX, trigger->m_scaleX);
            drawInput(getInputPos(trigger), triggerScale);

            bool drawCenter = Utils::triggersWithCenters.contains(id);
            drawOutput(getOutputPos(trigger, false, drawCenter), triggerScale);
            if (drawCenter) drawOutput(getOutputPos(trigger, true), triggerScale);
        }

        Cache::TriggerIndicators::targetObjects.clear();
        Cache::TriggerIndicators::centerObjects.clear();

        if (target != 0 && !Settings::TriggerIndicators::groupBlacklist.contains(target)) {
            getObjects(trigger, target, Cache::TriggerIndicators::targetObjects);
        }
        if (center != 0 && !Settings::TriggerIndicators::groupBlacklist.contains(center)) {
            getObjects(trigger, center, Cache::TriggerIndicators::centerObjects);
        }
        
        if (trigger->m_activateGroup && id == 1049) id = 10001; // toggle triggers
        Utils::updateTriggerCol(Cache::TriggerIndicators::col, id, Settings::TriggerIndicators::chroma);
        Cache::TriggerIndicators::extrasCol1.a = Cache::layerAlphaMultiplier;
        Cache::TriggerIndicators::extrasCol2.a = Cache::layerAlphaMultiplier;

        bool hasCenter = Utils::triggersWithCenters.contains(id);

        // if drag active is true dragtriggers should b enabled
        if (Cache::Utils::DragTriggers::dragActive && Cache::Utils::DragTriggers::target == trigger) {
            Cache::TriggerIndicators::shouldDrawDotted = Cache::Utils::DragTriggers::isCenter;
            
            drawToPoint(
                getOutputPos(
                    trigger, Cache::Utils::DragTriggers::isCenter, 
                    Utils::triggersWithCenters.contains(id)
                ), 
                Cache::Utils::DragTriggers::touchPos
            );
        }

        Cache::TriggerIndicators::shouldDrawDotted = false;
        draw(trigger, Cache::TriggerIndicators::targetObjects, getOutputPos(trigger, false, hasCenter));
        Cache::TriggerIndicators::shouldDrawDotted = Settings::TriggerIndicators::dottedCenterLines;
        draw(trigger, Cache::TriggerIndicators::centerObjects, getOutputPos(trigger, true));

        //'a'ccc3(150, 50, 255);
        //'b'ccc3(74, 82, 225); move indicators
        //'c'ccc3(255, 255, 150);
        //'d'ccc3(255, 150, 255); trigger indicators
        //'f'ccc3(150, 255, 255);
        //'g'ccc3(64, 227, 72);
        //'j'ccc3(50, 200, 255);
        //'l'ccc3(96, 171, 239); better particles
        //'o'ccc3(255, 165, 75); better duration lines
        //'p'ccc3(255, 0, 255);
        //'r'ccc3(255, 90, 90); area previews
        //'s'ccc3(255, 220, 65);
        //'y'ccc3(255, 255, 0);
    }
}