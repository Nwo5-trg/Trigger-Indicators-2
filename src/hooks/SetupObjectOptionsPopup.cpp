#include <Geode/modify/SetupObjectOptionsPopup.hpp>
#include "../shared/Settings.hpp"
#include "../utils/Utils.hpp"

using namespace geode::prelude;

class $modify(SetupObjectOptionsPopup) {
    bool init(GameObject* p0, CCArray* p1, SetGroupIDLayer* p2) {
        if (!SetupObjectOptionsPopup::init(p0, p1, p2)) return false;
        bool moveIndicators = Settings::MoveIndicators::enabled;
        bool areaPreviews = Settings::AreaPreviews::enabled;

        for (auto obj : CCArrayExt<GameObject*>(m_gameObject ? CCArray::createWithObject(m_gameObject) : m_gameObjects)) {
            if (obj->m_objectID != 901) moveIndicators = false;
            if (!Utils::areaTriggers.contains(obj->m_objectID)) moveIndicators = false;
        }

        if (moveIndicators) {        
            m_mainLayer->getChildByType<CCLabelBMFont>(16)->setString("Enable\nIndicators"); // iceblock
            m_mainLayer->getChildByType<CCLabelBMFont>(17)->setString("Enable\nPreview"); // gripslope
        }
        else if (areaPreviews) {
            m_mainLayer->getChildByType<CCLabelBMFont>(16)->setString("Enable\nPreview"); // iceblock
        }

        return true;
    }
};