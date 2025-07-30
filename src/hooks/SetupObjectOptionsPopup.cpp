#include <Geode/modify/SetupObjectOptionsPopup.hpp>
#include "../shared/Settings.hpp"

using namespace geode::prelude;

class $modify(SetupObjectOptionsPopup) {
    bool init(GameObject* p0, CCArray* p1, SetGroupIDLayer* p2) {
        if (!SetupObjectOptionsPopup::init(p0, p1, p2)) return false;
        if ( // more formmating warcrimes (fuck you i will not improve it)
            !Settings::MoveIndicators::enabled 
            || !(m_gameObject 
                ? m_gameObject->m_objectID == 901
                : static_cast<GameObject*>(m_gameObjects->firstObject())->m_objectID == 901
            )
        ) return true;

        m_mainLayer->getChildByType<CCLabelBMFont>(16)->setString("Enable\nIndicators"); // iceblock
        m_mainLayer->getChildByType<CCLabelBMFont>(17)->setString("Enable\nPreview"); // gripslope

        return true;
    }
};