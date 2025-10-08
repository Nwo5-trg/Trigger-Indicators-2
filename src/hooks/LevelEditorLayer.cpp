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

        { // gay node :3c (i am not making this better if it works it works)
            std::pair<ccColor3B, CCNodeRGBA**> gayArray[] = {
                {{255, 128, 128}, &Cache::gayNode0},
                {{255, 255, 128}, &Cache::gayNode1},
                {{128, 255, 128}, &Cache::gayNode2},
                {{128, 255, 255}, &Cache::gayNode3},
                {{128, 128, 255}, &Cache::gayNode4},
                {{255, 128, 255}, &Cache::gayNode5},
            };

            for (int i = 0; i < 6; i++) {
                auto gayNode = CCNodeRGBA::create();
                Cache::gridDrawLayer->addChild(gayNode);

                gayNode->runAction(CCRepeatForever::create(
                    CCSequence::create(
                        CCTintTo::create(
                            Settings::sayoDeviceSensitivity, gayArray[(i + 0) % 6].first.r,
                            gayArray[(i + 0) % 6].first.g, gayArray[(i + 0) % 6].first.b
                        ),
                        CCTintTo::create(
                            Settings::sayoDeviceSensitivity, gayArray[(i + 1) % 6].first.r,
                            gayArray[(i + 1) % 6].first.g, gayArray[(i + 1) % 6].first.b
                        ),
                        CCTintTo::create(
                            Settings::sayoDeviceSensitivity, gayArray[(i + 2) % 6].first.r,
                            gayArray[(i + 2) % 6].first.g, gayArray[(i + 2) % 6].first.b
                        ),
                        CCTintTo::create(
                            Settings::sayoDeviceSensitivity, gayArray[(i + 3) % 6].first.r,
                            gayArray[(i + 3) % 6].first.g, gayArray[(i + 3) % 6].first.b
                        ),
                        CCTintTo::create(
                            Settings::sayoDeviceSensitivity, gayArray[(i + 4) % 6].first.r,
                            gayArray[(i + 4) % 6].first.g, gayArray[(i + 4) % 6].first.b
                        ),
                        CCTintTo::create(
                            Settings::sayoDeviceSensitivity, gayArray[(i + 5) % 6].first.r,
                            gayArray[(i + 5) % 6].first.g, gayArray[(i + 5) % 6].first.b
                        ), nullptr
                    )
                ));
                *gayArray[i].second = gayNode;
            }
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