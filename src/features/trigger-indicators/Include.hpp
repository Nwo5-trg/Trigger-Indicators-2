#pragma once

struct CornerRect;

namespace TriggerIndicators {
    void create(EffectGameObject* trigger);

    void draw(EffectGameObject* trigger, const std::vector<GameObject*>& objs, cocos2d::CCPoint outputPos);
    void drawClusters(cocos2d::CCPoint outputPos, bool isTrigger);
    void drawToObject(cocos2d::CCPoint outputPos, GameObject* obj, bool isTrigger);
    void drawToRect(cocos2d::CCPoint outputPos, const CornerRect& rect);
    void drawToPoint(cocos2d::CCPoint outputPos, cocos2d::CCPoint pos);
    void drawInput(cocos2d::CCPoint pos, cocos2d::CCSize scale);
    void drawOutput(cocos2d::CCPoint pos, cocos2d::CCSize scale);

    void getObjects(EffectGameObject* trigger, int key, std::vector<GameObject*>& vector);
}