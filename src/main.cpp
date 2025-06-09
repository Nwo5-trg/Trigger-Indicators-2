#include <Geode/Geode.hpp>
#include <Geode/modify/LevelEditorLayer.hpp>
#include "indicators/Indicators.hpp"
#include "indicators/IndicatorVariables.hpp"

using namespace geode::prelude;

class $modify(Editor, LevelEditorLayer) {
    bool init(GJGameLevel* p0, bool p1) {	
		if (!LevelEditorLayer::init(p0, p1)) return false;
        
        IndicatorVars::triggerIndicatorDraw = nullptr;
        IndicatorVars::triggerExtraDraw = nullptr;
        IndicatorVars::batchLayer = nullptr;

        IndicatorVars::triggerIndicatorDrawChromaNode = nullptr;

        updateSettings();

        if (auto shaderLayer = this->getChildByType<ShaderLayer>(0)) IndicatorVars::batchLayer = shaderLayer->getChildByType<CCNode>(1)->getChildByType<CCLayer>(0);
        else IndicatorVars::batchLayer = this->getChildByType<CCNode>(1)->getChildByType<CCLayer>(0);

        for (int i = 0; i < 2; i++) { // need 2 cuz indicators should render below triggers, input/output indicators should render above
            auto layer = CCLayer::create();
            layer->setPosition(0.0f, 0.0f);
            layer->setZOrder(i == 0 ? -1500 : 9999);
            layer->setID(i == 0 ? "trigger-indicator-layer" : "trigger-extra-layer");
            IndicatorVars::batchLayer->addChild(layer);

            auto draw = CCDrawNode::create();
            draw->setPosition(0.0f, 0.0f);
            draw->setBlendFunc({GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA});
            layer->addChild(draw);
            if (i == 0) IndicatorVars::triggerIndicatorDraw = draw;
            else IndicatorVars::triggerExtraDraw = draw;
        }

        if (IndicatorVars::chroma) {
            auto gayNode = CCNodeRGBA::create();
            IndicatorVars::triggerIndicatorDraw->addChild(gayNode);
            IndicatorVars::triggerIndicatorDrawChromaNode = gayNode;
            auto rgbtqiaplus16mcolultra4khd = CCRepeatForever::create(CCSequence::create( // we on that sillydoggo naming shit yeahhhh
            CCTintTo::create(IndicatorVars::sayoDeviceSensitivity, 255, 128, 128), CCTintTo::create(IndicatorVars::sayoDeviceSensitivity, 255, 255, 128),
            CCTintTo::create(IndicatorVars::sayoDeviceSensitivity, 128, 255, 128), CCTintTo::create(IndicatorVars::sayoDeviceSensitivity, 128, 255, 255),
            CCTintTo::create(IndicatorVars::sayoDeviceSensitivity, 128, 128, 255), CCTintTo::create(IndicatorVars::sayoDeviceSensitivity, 255, 128, 255),
            nullptr));
            gayNode->runAction(rgbtqiaplus16mcolultra4khd);
        }
        return true;
    }

    void updateSettings() {
        auto mod = Mod::get();
        IndicatorVars::onlySelected = mod->getSettingValue<bool>("only-selected");
        IndicatorVars::onlyTriggers = mod->getSettingValue<bool>("only-triggers");
        auto maxDistance = mod->getSettingValue<double>("max-distance");
        IndicatorVars::maxDistance = maxDistance * maxDistance;
        IndicatorVars::thickness = mod->getSettingValue<double>("thickness");
        IndicatorVars::clusterSize = mod->getSettingValue<double>("cluster-size");
        IndicatorVars::clusterMaxThreshold = mod->getSettingValue<int64_t>("cluster-max-threshold");
        auto indicatorType = mod->getSettingValue<std::string>("indicator-type");
        if (indicatorType == "Individual Lines") IndicatorVars::indicatorType = IndicatorType::IndividualLine;
        else if (indicatorType == "Rect") IndicatorVars::indicatorType = IndicatorType::Rect;
        else IndicatorVars::indicatorType = IndicatorType::Clustered;
        IndicatorVars::extrasCol1 = ccc4FFromccc4B(mod->getSettingValue<ccColor4B>("extras-col-one"));
        IndicatorVars::extrasCol2 = ccc4FFromccc4B(mod->getSettingValue<ccColor4B>("extras-col-two"));

        IndicatorVars::chroma = mod->getSettingValue<bool>("chroma");
        IndicatorVars::sayoDeviceSensitivity = mod->getSettingValue<double>("sayo-device-sensitivity");
    }

    void updateDebugDraw() {
        LevelEditorLayer::updateDebugDraw();
        if (IndicatorVars::triggerIndicatorDraw) updateIndicators(this); // check if shit is valid or wtv (if this is valid everything is)
    }
};