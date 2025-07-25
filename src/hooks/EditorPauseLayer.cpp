#include <Geode/modify/EditorPauseLayer.hpp>
#include "../shared/Settings.hpp"
#include <Geode/ui/GeodeUI.hpp>

using namespace geode::prelude;

class $modify(EditorPause, EditorPauseLayer) {
    bool init (LevelEditorLayer* p0) {
        if (!EditorPauseLayer::init(p0)) return false;

        auto menu = this->getChildByID("guidelines-menu");
        if (!menu) return true;

        auto indicatorSettingsButton = CCMenuItemSpriteExtra::create(
            CCSprite::create(Settings::settingsButtonTexture.c_str()), 
            this, menu_selector(EditorPause::onTriggerIndicatorSettings)
        );
        indicatorSettingsButton->setScale(0.9f);
        indicatorSettingsButton->m_baseScale = 0.9f;
        menu->addChild(indicatorSettingsButton);
        if (auto layout = typeinfo_cast<AxisLayout*>(menu->getLayout())) layout->setAutoScale(false);
        menu->updateLayout();

        return true;
    }

    void onTriggerIndicatorSettings(CCObject* sender) {
        geode::openSettingsPopup(Mod::get(), false);     
    }
};