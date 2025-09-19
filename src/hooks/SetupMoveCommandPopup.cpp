#include <Geode/modify/SetupMoveCommandPopup.hpp>
#include "../shared/Settings.hpp"

using namespace geode::prelude;

class $modify(MoveTriggerPopup, SetupMoveCommandPopup) {
    struct Fields {
        std::vector<EffectGameObject*> triggers;
    };

    bool init(EffectGameObject* p0, CCArray* p1) {
        if (!SetupMoveCommandPopup::init(p0, p1)) return false;
        if (!Settings::MoveIndicators::enabled) return true;

        auto fields = m_fields.self();
        if (p0) fields->triggers.push_back(p0);
        else for (auto obj : CCArrayExt<EffectGameObject*>(p1)) fields->triggers.push_back(obj);

        for (int i = 0; i < 2; i++) {
            auto pos = ccp(i == 0 ? 105.0f : 167.5f, 265.0f);
            auto toggler = CCMenuItemToggler::create(
                CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png"),
                CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png"), 
                this, menu_selector(MoveTriggerPopup::onMoveIndicatorToggler)
            );
            toggler->setID(i == 0 ? "enable-indicators-toggle"_spr : "enable-preview-toggle"_spr);
            toggler->setTag(i);
            toggler->setPosition(pos);
            toggler->setScale(0.55f);
            bool toggle = true;
            for (auto obj : fields->triggers) {
                if (i == 0 ? !obj->m_isIceBlock : !obj->m_isGripSlope) {
                    toggle = false; break;
                }
            }
            toggler->toggle(toggle);
            m_buttonMenu->addChild(toggler);
            
            auto label = CCLabelBMFont::create(
                i == 0 ? "Enable\nIndicators" : "Enable\nPreview",
                "bigFont.fnt"
            );
            label->setID(i == 0 ? "enable-indicators-label"_spr : "enable-preview-label"_spr);
            label->setPosition(ccp(pos.x + 12.5f, pos.y) + m_buttonMenu->getPosition());
            label->setScale(0.225f);
            label->setAnchorPoint({0.0f, 0.5f});
            m_mainLayer->addChild(label);
        }

        return true;
    }

    void onMoveIndicatorToggler(CCObject* sender) {
        auto fields = m_fields.self();
        bool toggle = !static_cast<CCMenuItemToggler*>(sender)->m_toggled;

        if (sender->getTag() == 0) {
            for (auto obj : fields->triggers) {
                obj->m_isIceBlock = toggle;
            }
        } else {
            for (auto obj : fields->triggers) {
                obj->m_isGripSlope = toggle;
            }
        }
    }
};