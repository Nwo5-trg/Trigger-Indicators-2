#pragma once

#include "../../utils/Enums.hpp"

namespace AreaPreviews {
    void create(EffectGameObject* trigger);

    void draw(EnterEffectObject* trigger);
    void drawArrow(cocos2d::CCPoint pos, ArrowDirection type);
    void drawDottedLine(cocos2d::CCPoint p1, cocos2d::CCPoint p2, const cocos2d::ccColor4F& col);
}