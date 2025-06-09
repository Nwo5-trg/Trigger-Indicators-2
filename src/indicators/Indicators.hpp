#pragma once

void updateIndicators(LevelEditorLayer* editor);
void pushBackObjects(cocos2d::CCDictionary* dict, int key, std::vector<GameObject*>& vector, bool triggerSelected, cocos2d::CCPoint triggerPos);