#pragma once

namespace Update {
    void draw(LevelEditorLayer* editor);

    void updateLayerAlpha(GameObject* obj);
    void updateColorCache();
    void updateThicknessCache();
}