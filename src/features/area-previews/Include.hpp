#pragma once

#include "../../utils/Enums.hpp"

namespace AreaPreviews {
    void create(EffectGameObject* trigger);

    void draw(EnterEffectObject* trigger);
    void drawArrow(cocos2d::CCPoint pos, ArrowDirection type);
}