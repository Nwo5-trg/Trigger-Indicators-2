#include "Include.hpp"
#include "../../shared/Settings.hpp"
#include "../../shared/Cache.hpp"
#include "../../utils/Constants.hpp"

using namespace geode::prelude;

namespace BetterDurationLines {
    void create(EffectGameObject* trigger) {
        int id = trigger->m_objectID; 
        if (Settings::BetterDurationLines::triggerBlacklist.contains(id)) return;

        auto type = getType(id);
        if (type == DurationLineType::None) return;

        switch (type) {
            case DurationLineType::Generic:
            case DurationLineType::Alpha:
            case DurationLineType::Color:
            case DurationLineType::Shake: {
                Cache::BetterDurationLines::duration = trigger->m_duration;
            break; }
            case DurationLineType::Pulse: {
                Cache::BetterDurationLines::duration = trigger->m_fadeInDuration + trigger->m_holdDuration + trigger->m_fadeOutDuration;
            break; }
            case DurationLineType::Time: {
                auto timer = static_cast<TimerTriggerGameObject*>(trigger);
                Cache::BetterDurationLines::duration = timer->m_stopTimeEnabled 
                    ? std::fabs(timer->m_startTime - timer->m_targetTime) / (timer->m_timeMod == 0 ? 0.001f : timer->m_timeMod)
                    : 0.0f;
            break; }
            case DurationLineType::Sound: {
                auto sfx = static_cast<SFXTriggerGameObject*>(trigger);
                Cache::BetterDurationLines::duration = sfx->m_soundDuration;
                if (sfx->m_start != 0) Cache::BetterDurationLines::duration -= sfx->m_start / 1000.0f;
                if (sfx->m_end != 0) Cache::BetterDurationLines::duration -= sfx->m_end / 1000.0f;
            break; }
            case DurationLineType::None: break;
        }

        if (Cache::BetterDurationLines::duration <= Constants::betterDurationLinesDurationLengthCullThreshold) return;

        Cache::BetterDurationLines::triggerPos = trigger->getPosition();

        float cullDistance = Cache::View::cullDistance + ((Cache::BetterDurationLines::duration * Constants::normalSpeed) / Cache::View::zoom);

        if ( // culling
            !trigger->m_isSelected 
            && ccpDistanceSQ(Cache::View::relativeCenter, Cache::BetterDurationLines::triggerPos) 
            > cullDistance * cullDistance
        ) return;

        float triggerTime = Cache::editor->m_drawGridLayer->timeForPos(
            Cache::BetterDurationLines::triggerPos, 0, 0, false, false, true, 0
        );

        Cache::BetterDurationLines::dontExtendNegative = (trigger->m_isSpawnTriggered || trigger->m_isTouchTriggered)
            && triggerTime == 0.0f;
        
        draw(trigger, type, triggerTime);
    }
}