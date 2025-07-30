#pragma once

enum class MoveIndicatorMode;

namespace MoveIndicators {
    void create(EffectGameObject* trigger);
    void getObjects(EffectGameObject* trigger, int key);

    void draw(EffectGameObject* trigger);
    void drawIndicator(EffectGameObject* trigger, const std::pair<cocos2d::CCPoint, cocos2d::CCPoint>& pair);
    
    void getPositions(EffectGameObject* trigger, MoveIndicatorMode mode);
    void getObjectPreview(cocos2d::CCPoint offset);
    cocos2d::CCPoint getObjectMovedPos(cocos2d::CCPoint pos, EffectGameObject* target);
}