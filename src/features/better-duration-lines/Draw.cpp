#include "Include.hpp"
#include "../../shared/Settings.hpp"
#include "../../shared/Cache.hpp"
#include "../../utils/Utils.hpp"

using namespace geode::prelude;

namespace BetterDurationLines {
    void draw(EffectGameObject* trigger, DurationLineType type, float start) {
        switch (type) {
            case DurationLineType::Generic: {
                Utils::updateTriggerCol(
                    Cache::BetterDurationLines::col, trigger->m_objectID, 
                    Settings::BetterDurationLines::chroma
                );
                drawDurationLine(start, start + Cache::BetterDurationLines::duration);
            break; }
            case DurationLineType::Alpha: {
                float segmentLength = Cache::BetterDurationLines::duration / Settings::BetterDurationLines::previewSteps;
                float startOpacity = getStartOpacity(trigger->m_targetGroupID);
                float opacityStep = trigger->m_opacity - startOpacity;

                for (float i = 0.0f; i < Settings::BetterDurationLines::previewSteps; i++) {
                    float time = i / (Settings::BetterDurationLines::previewSteps - 1);
                    float alpha = startOpacity + (opacityStep * time);

                    if (Settings::BetterDurationLines::chroma) {
                        Cache::BetterDurationLines::col = Cache::chromaCol0;
                        Cache::BetterDurationLines::col.a *= alpha;
                    }
                    else Cache::BetterDurationLines::col = {1.0f, 1.0f, 1.0f, alpha};

                    drawDurationLine(start, start + segmentLength);
                    start += segmentLength;
                }
            break; }
            case DurationLineType::Pulse: {
                float end = start;
                if ((end += trigger->m_fadeInDuration) != start) {
                    Cache::BetterDurationLines::col = Settings::BetterDurationLines::pulseInCol;
                    drawDurationLine(start, end); 
                    start = end;
                }
                if ((end += trigger->m_holdDuration) != start) {
                    Cache::BetterDurationLines::col = Settings::BetterDurationLines::pulseHoldCol;
                    drawDurationLine(start, end); 
                    start = end;
                }
                if ((end += trigger->m_fadeOutDuration) != start) {
                    Cache::BetterDurationLines::col = Settings::BetterDurationLines::pulseOutCol;
                    drawDurationLine(start, end); 
                    start = end;
                }
            break; }
            case DurationLineType::Color: {
                getStartColor(trigger->m_targetGroupID);
                Cache::BetterDurationLines::endCol = ccc4FFromccc3B(trigger->m_triggerTargetColor);
                Cache::BetterDurationLines::endCol.a = trigger->m_opacity;

                float segmentLength = trigger->m_duration / Settings::BetterDurationLines::previewSteps;

                for (float i = 0.0f; i < Settings::BetterDurationLines::previewSteps; i++) {
                    float time = i / (Settings::BetterDurationLines::previewSteps - 1);
                    interpolateColor(time);

                    drawDurationLine(start, start + segmentLength);
                    start += segmentLength;
                }
            break; }
            case DurationLineType::Time: {
                Utils::updateTriggerCol(
                    Cache::BetterDurationLines::col, trigger->m_objectID, 
                    Settings::BetterDurationLines::chroma
                );
                drawDurationLine(start, start + Cache::BetterDurationLines::duration);
            break; }
            case DurationLineType::Sound: {
                auto sfx = static_cast<SFXTriggerGameObject*>(trigger);
                float speed = std::powf(2.0f, sfx->m_speed / 12.0f);
                Cache::BetterDurationLines::duration *= speed;
                float in = (sfx->m_fadeIn / 1000.0f) * speed;
                float out = (sfx->m_fadeOut / 1000.0f) * speed;
                Cache::BetterDurationLines::duration -= in + out;

                float end = start;
                if ((end += in) != start) {
                    Cache::BetterDurationLines::col = Settings::BetterDurationLines::pulseInCol;
                    drawDurationLine(start, end); 
                    start = end;
                }
                if ((end += Cache::BetterDurationLines::duration) != start) {
                    Cache::BetterDurationLines::col = Settings::BetterDurationLines::pulseHoldCol;
                    drawDurationLine(start, end); 
                    start = end;
                }
                if ((end += out) != start) {
                    Cache::BetterDurationLines::col = Settings::BetterDurationLines::pulseOutCol;
                    drawDurationLine(start, end); 
                    start = end;
                }
            break; }
            case DurationLineType::Shake: {
                Utils::updateTriggerCol(
                    Cache::BetterDurationLines::col, trigger->m_objectID, 
                    Settings::BetterDurationLines::chroma
                );
                Cache::BetterDurationLines::col.a *= Cache::layerAlphaMultiplier;

                int steps = std::floorf(Cache::BetterDurationLines::duration / std::clamp(
                        (trigger->m_shakeInterval * Constants::betterDurationLinesShakeIntervalMultiplier), 0.04f, 1.0f
                ));
                float segmentLength = Cache::BetterDurationLines::duration / steps / 2;
                float intensity = trigger->m_shakeStrength * Constants::betterDurationLinesShakeStrengthMultiplier;
                uint32_t unique = trigger->m_uniqueID;

                bool up = true;

                for (float i = 0.0f; i < steps; i++) {
                    float offset = generateRandom(unique, i) * intensity;

                    float y = Cache::BetterDurationLines::triggerPos.y + (up ? offset : -offset);

                    drawDurationLineShake({start, Cache::BetterDurationLines::triggerPos.y}, {start + segmentLength, y});
                    drawDurationLineShake({start + segmentLength, y}, {start + segmentLength + segmentLength, Cache::BetterDurationLines::triggerPos.y});

                    up = !up;
                    start += segmentLength + segmentLength;
                }
            break; }
            case DurationLineType::None: break;
        }
    }
}