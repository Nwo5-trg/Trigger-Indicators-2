#include <Geode/modify/LevelEditorLayer.hpp>
#include "../features/Update.hpp"
#include "../shared/Cache.hpp"
#include "../shared/Settings.hpp"

using namespace geode::prelude;

class $modify(LevelEditorLayer) {
    bool init(GJGameLevel* p0, bool p1) {	
		if (!LevelEditorLayer::init(p0, p1)) return false;

        for (int i = 0; i < 2; i++) {
            auto layer = CCLayer::create();
            layer->setPosition(0.0f, 0.0f);
            layer->setZOrder(i == 0 ? -1500 : 9999);
            layer->setID(i == 0 ? "grid-layer"_spr : "object-layer"_spr);
            m_objectLayer->addChild(layer);
            
            auto draw = CCDrawNode::create();
            draw->setPosition(0.0f, 0.0f);
            draw->setBlendFunc({GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA});
            layer->addChild(draw);
            if (i == 0) Cache::gridDraw = draw;
            else Cache::objectDraw = draw;
        }

        { // gay node
            auto gayNode = CCNodeRGBA::create();
            Cache::gridDraw->addChild(gayNode);
            Cache::gayNode = gayNode;
            auto rgbtqiaplus16mcolultra4khd = CCRepeatForever::create(CCSequence::create( // we on that sillydoggo naming shit yeahhhh
            CCTintTo::create(Settings::sayoDeviceSensitivity, 255, 128, 128), CCTintTo::create(Settings::sayoDeviceSensitivity, 255, 255, 128),
            CCTintTo::create(Settings::sayoDeviceSensitivity, 128, 255, 128), CCTintTo::create(Settings::sayoDeviceSensitivity, 128, 255, 255),
            CCTintTo::create(Settings::sayoDeviceSensitivity, 128, 128, 255), CCTintTo::create(Settings::sayoDeviceSensitivity, 255, 128, 255),
            nullptr));
            gayNode->runAction(rgbtqiaplus16mcolultra4khd);
        }
        
        return true;
    }

    void updateDebugDraw() {
        LevelEditorLayer::updateDebugDraw();
        Update::draw(this);
    }
};