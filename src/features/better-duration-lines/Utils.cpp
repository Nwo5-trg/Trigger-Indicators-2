#include "Include.hpp"
#include "../../shared/Settings.hpp"
#include "../../shared/Cache.hpp"
#include "../../utils/Utils.hpp"

using namespace geode::prelude;

namespace BetterDurationLines {
    DurationLineType getType(int id) {
        if (!durationTriggers.contains(id)) return DurationLineType::None;
        
        if (Settings::BetterDurationLines::inlinePreviews) {
            if (!inlinePreviewTypeMap.contains(id)) return DurationLineType::Generic;
            return inlinePreviewTypeMap[id];
        }
        else {
            if (!typeMap.contains(id)) return DurationLineType::Generic;
            return typeMap[id];
        }
    }

    void drawDurationLine(float start, float end) {
        Cache::BetterDurationLines::col.a *= Cache::layerAlphaMultiplier * Settings::BetterDurationLines::opacity;

        drawDurationLineFixTime(start, end);

        if (Settings::BetterDurationLines::alphaFix) {
            Cache::gridDraw->drawSegment(
                {start, Cache::BetterDurationLines::triggerPos.y}, 
                {end, Cache::BetterDurationLines::triggerPos.y}, 
                Cache::BetterDurationLines::thickness,
                Cache::BetterDurationLines::col
            );
        }
        else {
            Utils::drawLine(
                Cache::gridDraw, 
                {start, Cache::BetterDurationLines::triggerPos.y}, 
                {end, Cache::BetterDurationLines::triggerPos.y}, 
                Cache::BetterDurationLines::thickness, 
                Cache::BetterDurationLines::col
            );
        }
    }
    void drawDurationLineShake(CCPoint start, CCPoint end) {
        drawDurationLineFixTime(start.x, end.x);

        Utils::drawLine(
            Cache::gridDraw, start, end,
            Cache::BetterDurationLines::thickness, 
            Cache::BetterDurationLines::col
        );
    }
    void drawDurationLineFixTime(float& start, float& end) {
        if (Cache::BetterDurationLines::dontExtendNegative) {
            start = (start * Constants::normalSpeed) + Cache::BetterDurationLines::triggerPos.x;
            end = (end * Constants::normalSpeed) + Cache::BetterDurationLines::triggerPos.x;
        }
        else {
            start = posForTime(start);
            end = posForTime(end);
            if (start == 0.0f) {
                start += Cache::BetterDurationLines::triggerPos.x;
            }
        }
    }

    float getStartOpacity(int group) {
        float closestPos = -FLT_MAX;
        EffectGameObject* closestObj = nullptr;

        for (auto obj : CCArrayExt<EffectGameObject>(Cache::editor->m_alphaTriggers)) {
            if (obj->m_targetGroupID != group) continue;
            float objX = obj->getPositionX();
            if (objX >= closestPos && objX < Cache::BetterDurationLines::triggerPos.x) {
                closestPos = objX;
                closestObj = obj;
            }
        }

        return closestObj ? closestObj->m_opacity : 1.0f;
    }
    void getStartColor(int channel) {
        float closestPos = -FLT_MAX;
        EffectGameObject* closestObj = nullptr;

        for (auto obj : CCArrayExt<EffectGameObject*>(Cache::editor->m_colorTriggers)) {
            if (obj->m_targetGroupID != channel) continue;
            float objX = obj->getPositionX();
            if (objX > closestPos && objX < Cache::BetterDurationLines::triggerPos.x) {
                closestPos = objX;
                closestObj = obj;
            }
        }
        if (!closestObj) {
            auto action = Cache::editor->m_effectManager->getColorAction(channel);
            Cache::BetterDurationLines::startCol = ccc4FFromccc3B(action->m_fromColor);
            Cache::BetterDurationLines::startCol.a = action->m_fromOpacity;
            return;
        }

        Cache::BetterDurationLines::startCol = ccc4FFromccc3B(closestObj->m_triggerTargetColor);
        Cache::BetterDurationLines::startCol.a = closestObj->m_opacity;
    }

    void interpolateColor(float time) {
        Cache::BetterDurationLines::col = {
            Cache::BetterDurationLines::startCol.r + (Cache::BetterDurationLines::endCol.r - Cache::BetterDurationLines::startCol.r) * time,
            Cache::BetterDurationLines::startCol.g + (Cache::BetterDurationLines::endCol.g - Cache::BetterDurationLines::startCol.g) * time,
            Cache::BetterDurationLines::startCol.b + (Cache::BetterDurationLines::endCol.b - Cache::BetterDurationLines::startCol.b) * time,
            Cache::BetterDurationLines::startCol.a + (Cache::BetterDurationLines::endCol.a - Cache::BetterDurationLines::startCol.a) * time
        };
    }

    float generateRandom(uint32_t x, uint32_t i) {
        // random hashing stuff online even tho std prolly has smth cuz i went down a rabbit hole :3
        x ^= i + 0x9e3779b9;
        x = (x ^ 61) ^ (x >> 16);
        x += (x << 3);
        x ^= (x >> 4);
        x *= 0x27d4eb2d;
        x ^= (x >> 15);
        return Constants::betterDurationLinesShakeRandomMin + (x / (float)UINT32_MAX) *
            (Constants::betterDurationLinesShakeRandomMax - Constants::betterDurationLinesShakeRandomMin);
    }

    float posForTime(float time) {
        // yoinked from goodgrid
        return LevelTools::posForTimeInternal(
            time,
            Cache::editor->m_drawGridLayer->m_speedObjects,
            (int)Cache::editor->m_levelSettings->m_startSpeed,
            Cache::editor->m_isPlatformer,
            false,
            true,
            Cache::editor->m_gameState.m_rotateChannel,
            false
        ).x;
    };
}