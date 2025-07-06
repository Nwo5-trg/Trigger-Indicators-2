#pragma once

void drawForTrigger(
    EffectGameObject* trigger, std::vector<GameObject*>& targetObjects, // no const cuz of drawindividuallines refactoring
    std::vector<GameObject*>& centerObjects
);

void drawIndividualLines( // holy shit thats a long params list
    const std::vector<GameObject*>& vector, cocos2d::CCPoint posO,
    cocos2d::ccColor4F indicatorCol, cocos2d::ccColor4F extrasCol1, cocos2d::ccColor4F extrasCol2,
    bool useClusterVector, std::vector<GameObject*>& clusterVector, // cant have a default value for this so bool
    int group
);

void drawIndicator(cocos2d::CCPoint triggerPos, cocos2d::CCPoint targetPos, cocos2d::ccColor4F col, int group);
void drawIndicatorWithRect(cocos2d::CCPoint triggerPos, const std::vector<GameObject*>& objs, cocos2d::ccColor4F col, int group);

void drawExtras(cocos2d::CCPoint objPos, float scale, int type, cocos2d::ccColor4F col, cocos2d::ccColor4F col2);
void drawExtrasOutput(cocos2d::CCPoint pos, float scale, cocos2d::ccColor4F col1, cocos2d::ccColor4F col2);

void drawSpawnIndicator(cocos2d::CCPoint objPos, float scale, float zoom);