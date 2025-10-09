#pragma once

#include "../../utils/Enums.hpp"

namespace BetterDurationLines {
    void create(EffectGameObject* trigger);

    void draw(EffectGameObject* trigger, DurationLineType type, float start);

    DurationLineType getType(int id);
    void drawDurationLine(float start, float end);
    void drawDurationLineShake(cocos2d::CCPoint start, cocos2d::CCPoint end);
    void drawDurationLineFixTime(float& start, float& end);

    float getStartOpacity(int group);
    void getStartColor(EffectGameObject* trigger);
    
    void interpolateColor(float time);
    
    float generateRandom(uint32_t x, uint32_t i);

    float posForTime(float time);

    inline std::unordered_set<int> durationTriggers = {
        901, 1346, 2067, 1347, 1814, 3012, 3011, 3013, 3014, 3015, 1913, 1914, 1916, 2015, 3603, 2999, 3606, 
        3612, 1007, 1006, 899, 3614, 3602, 1520
    };
    
    inline std::unordered_map<int, DurationLineType> typeMap = {
        {1006, DurationLineType::Pulse},

        {3614, DurationLineType::Time},

        {3602, DurationLineType::Sound},
    };

    inline std::unordered_map<int, DurationLineType> inlinePreviewTypeMap = {
        {1007, DurationLineType::Alpha},

        {1006, DurationLineType::Pulse},

        {899, DurationLineType::Color},

        {3614, DurationLineType::Time},

        {3602, DurationLineType::Sound},

        {1520, DurationLineType::Shake}
    };
}