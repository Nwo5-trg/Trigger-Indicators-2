#include <Geode/modify/LevelEditorLayer.hpp>
#include "../features/Update.hpp"
#include "../shared/Cache.hpp"
#include "../shared/Settings.hpp"
#include "../utils/Utils.hpp"

using namespace geode::prelude;

class $modify(LevelEditorLayer) {
    bool init(GJGameLevel* p0, bool p1) {	
		if (!LevelEditorLayer::init(p0, p1)) return false;

        Cache::playtesting = false;

        Utils::createLayer(Cache::gridDrawLayer, "grid-layer"_spr, -1500);
        Utils::createDrawNode(Cache::gridDraw, "grid-draw"_spr, Cache::gridDrawLayer);
        Utils::createDrawNode(Cache::dontUpdateGridDraw, "dont-update-grid-draw"_spr, Cache::gridDrawLayer);
        Utils::createLayer(Cache::objectDrawLayer, "object-layer"_spr, 9999);
        Utils::createDrawNode(Cache::objectDraw, "object-draw"_spr, Cache::objectDrawLayer);
        Utils::createDrawNode(Cache::dontUpdateObjectDraw, "dont-update-object-draw"_spr, Cache::objectDrawLayer);

        { // gay node
            Cache::gayNode = CCNodeRGBA::create();
            Cache::gridDrawLayer->addChild(Cache::gayNode);
            auto rgbtqiaplus16mcolultra4khd = CCRepeatForever::create(CCSequence::create( // we on that sillydoggo naming shit yeahhhh
                CCTintTo::create(Settings::sayoDeviceSensitivity, 255, 128, 128), CCTintTo::create(Settings::sayoDeviceSensitivity, 255, 255, 128),
                CCTintTo::create(Settings::sayoDeviceSensitivity, 128, 255, 128), CCTintTo::create(Settings::sayoDeviceSensitivity, 128, 255, 255),
                CCTintTo::create(Settings::sayoDeviceSensitivity, 128, 128, 255), CCTintTo::create(Settings::sayoDeviceSensitivity, 255, 128, 255),
            nullptr));
            Cache::gayNode->runAction(rgbtqiaplus16mcolultra4khd);
        }

        updateTriggers();
        
        return true;
    }

    void updateDebugDraw() {
        LevelEditorLayer::updateDebugDraw();

        int objects = m_objects->count();
        if (objects != Cache::lastObjectCount) {
            updateTriggers();
        }
        Cache::lastObjectCount = objects;

        Update::draw(this);
    }

    void updateTriggers() {
        Cache::triggers.clear();
        for (auto obj : CCArrayExt<GameObject*>(m_objects)) {
            if (obj->m_isTrigger) {
                Cache::triggers.push_back(static_cast<EffectGameObject*>(obj));
            }
        }
    }

    GameObject* createObject(int p0, CCPoint p1, bool p2) {
        auto ret = LevelEditorLayer::createObject(p0, p1, p2);
        // move indicator shenangians
        if (Settings::MoveIndicators::enabled && p0 == 901) {
            ret->m_isIceBlock = Settings::MoveIndicators::enableIndicatorByDefault;
            ret->m_isGripSlope = Settings::MoveIndicators::enableEndPreviewByDefault;
        }
        // area preview shenangians
        if (Settings::AreaPreviews::enabled && Utils::areaTriggers.contains(p0)) {
            ret->m_isIceBlock = Settings::AreaPreviews::enablePreviewsByDefault;
        }
        return ret;
    }

    void onPlaytest() {
        Cache::playtesting = true;
        LevelEditorLayer::onPlaytest();
    }

    void onStopPlaytest() {
        Cache::playtesting = false;
        LevelEditorLayer::onStopPlaytest();
    }
};