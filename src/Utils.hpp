#pragma once

inline const cocos2d::ccColor4F emptyCCC4F = cocos2d::ccc4f(0.0f, 0.0f, 0.0f, 0.0f);

cocos2d::ccColor4F getTriggerCol(int id);

std::vector<std::vector<GameObject*>> getClusters(const std::vector<GameObject*>& objs, float clusterSize);
cocos2d::CCPoint getLineCut(cocos2d::CCPoint triggerPos, cocos2d::CCPoint p1, cocos2d::CCPoint p2);