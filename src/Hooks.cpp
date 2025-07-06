#include <Geode/Geode.hpp>
#include <Geode/modify/LevelEditorLayer.hpp>
#include <Geode/modify/EditorPauseLayer.hpp>
#include "indicators/Indicators.hpp"
#include "Variables.hpp"
#include <Geode/ui/GeodeUI.hpp>

using namespace geode::prelude;

class $modify(LevelEditorLayer) {
    bool init(GJGameLevel* p0, bool p1) {	
		if (!LevelEditorLayer::init(p0, p1)) return false;
        
        Variables::triggerIndicatorDraw = nullptr;
        Variables::triggerExtraDraw = nullptr;
        Variables::triggerIndicatorGroupLayer = nullptr;
        Variables::batchLayer = nullptr;

        Variables::collisionDict = nullptr;
        Variables::collisionDict = CCDictionary::create();

        Variables::triggerIndicatorDrawChromaNode = nullptr;

        Variables::updateSettings();

        if (auto shaderLayer = this->getChildByType<ShaderLayer>(0)) Variables::batchLayer = shaderLayer->getChildByType<CCNode>(1)->getChildByType<CCLayer>(0);
        else Variables::batchLayer = this->getChildByType<CCNode>(1)->getChildByType<CCLayer>(0);

        for (int i = 0; i < 3; i++) { // need 2 cuz indicators should render below triggers, input/output indicators should render above
            auto layer = CCLayer::create();
            layer->setPosition(0.0f, 0.0f);
            layer->setZOrder(i == 1 ? 9999 : -1500);
            layer->setID(i == 0 ? "trigger-indicator-layer" : i == 1 ? "trigger-extra-layer" : "trigger-indicator-group-layer");
            Variables::batchLayer->addChild(layer);
            if (i == 2) Variables::triggerIndicatorGroupLayer = layer;
            
            if (i < 2) {
                auto draw = CCDrawNode::create();
                draw->setPosition(0.0f, 0.0f);
                draw->setBlendFunc({GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA});
                layer->addChild(draw);
                if (i == 0) Variables::triggerIndicatorDraw = draw;
                else Variables::triggerExtraDraw = draw;
            }
        }

        { // silly stuff, has to always be active cuz u can change settings in editor now
            auto gayNode = CCNodeRGBA::create();
            Variables::triggerIndicatorDraw->addChild(gayNode);
            Variables::triggerIndicatorDrawChromaNode = gayNode;
            auto rgbtqiaplus16mcolultra4khd = CCRepeatForever::create(CCSequence::create( // we on that sillydoggo naming shit yeahhhh
            CCTintTo::create(Variables::sayoDeviceSensitivity, 255, 128, 128), CCTintTo::create(Variables::sayoDeviceSensitivity, 255, 255, 128),
            CCTintTo::create(Variables::sayoDeviceSensitivity, 128, 255, 128), CCTintTo::create(Variables::sayoDeviceSensitivity, 128, 255, 255),
            CCTintTo::create(Variables::sayoDeviceSensitivity, 128, 128, 255), CCTintTo::create(Variables::sayoDeviceSensitivity, 255, 128, 255),
            nullptr));
            gayNode->runAction(rgbtqiaplus16mcolultra4khd);
        }
        
        return true;
    }

    void updateDebugDraw() {
        LevelEditorLayer::updateDebugDraw();
        if (Variables::triggerIndicatorDraw) updateIndicators(this); // check if shit is valid or wtv (if this is valid everything is prolly)
    }
};

class $modify(EditorPause, EditorPauseLayer) {
    bool init (LevelEditorLayer* p0) {
        if (!EditorPauseLayer::init(p0)) return false;

        auto menu = this->getChildByID("guidelines-menu");
        if (!menu) return true;

        auto indicatorSettingsButton = CCMenuItemSpriteExtra::create(CCSprite::create(Variables::settingsButtonTexture.c_str()), this, menu_selector(EditorPause::onTriggerIndicatorSettings));
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

    void onResume(CCObject* sender) {
        Variables::updateSettings();
        EditorPauseLayer::onResume(sender);
    }
};