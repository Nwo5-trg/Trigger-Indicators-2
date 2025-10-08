#include "Update.hpp"
#include "trigger-indicators/Include.hpp"
#include "spawn-indicators/Include.hpp"
#include "better-particles/Include.hpp"
#include "move-indicators/Include.hpp"
#include "better-duration-lines/Include.hpp"
#include "area-previews/Include.hpp"
#include "../shared/Cache.hpp"
#include "../shared/Settings.hpp"
#include "../utils/Constants.hpp"

using namespace geode::prelude;

namespace Update {
    void draw(LevelEditorLayer* editor) {
        if (Settings::dontUpdateWhenPlaytesting && Cache::playtesting) return;
        Cache::gridDraw->clear();
        Cache::objectDraw->clear();
        if (!Cache::playtesting) {
            Cache::dontUpdateGridDraw->clear();
            Cache::dontUpdateObjectDraw->clear();
        }

        if (!Settings::enabled) return;

        Cache::editor = editor;

        Cache::View::size = CCDirector::get()->getWinSize();
        Cache::View::zoom = editor->m_objectLayer->getScale();

        updateThicknessCache();
        updateColorCache();

        // cull distance stuff
        Cache::View::relativeCenter = (
            (Cache::View::size / 2) - editor->m_objectLayer->getPosition()
        ) / Cache::View::zoom;
        Cache::View::cullDistance = Cache::View::size.width / Cache::View::zoom;
        Cache::View::cullDistanceSQ = (Cache::View::cullDistance * Cache::View::cullDistance) * Constants::cullDistanceBuffer;
        
        // cull distance for trigger indicators
        Cache::TriggerIndicators::cullDistance = Cache::View::cullDistanceSQ * Settings::TriggerIndicators::cullDistanceMultiplier;
        bool isSelectingObjects = editor->m_editorUI->getSelectedObjects()->count() != 0;
        if (isSelectingObjects) Cache::TriggerIndicators::cullDistance *= Settings::TriggerIndicators::selectedCullDistanceMultiplier;

        // better duration lines
        if (Settings::BetterDurationLines::enabled) GameManager::sharedState()->setGameVariable("0058", false);

        // :3c
        Cache::chromaCol0 = ccc4FFromccc3B(Cache::gayNode0->getColor());
        Cache::chromaCol1 = ccc4FFromccc3B(Cache::gayNode1->getColor());
        Cache::chromaCol2 = ccc4FFromccc3B(Cache::gayNode2->getColor());
        Cache::chromaCol3 = ccc4FFromccc3B(Cache::gayNode3->getColor());
        Cache::chromaCol4 = ccc4FFromccc3B(Cache::gayNode4->getColor());
        Cache::chromaCol5 = ccc4FFromccc3B(Cache::gayNode5->getColor());

        Cache::groupDict = editor->m_groupDict;
        Cache::currentLayer = editor->m_currentLayer;

        for (auto trigger : Cache::triggers) {
            updateLayerAlpha(trigger);

            if (Settings::SpawnIndicators::enabled) SpawnIndicators::create(trigger);
            if (Settings::TriggerIndicators::enabled) TriggerIndicators::create(trigger);
            if (Settings::MoveIndicators::enabled && !Cache::playtesting) MoveIndicators::create(trigger);
            if (Settings::BetterDurationLines::enabled && (!Settings::BetterDurationLines::hideWhilePlaytesting || !Cache::playtesting)) BetterDurationLines::create(trigger);
            if (Settings::AreaPreviews::enabled) AreaPreviews::create(trigger);
        }

        if (editor->m_hideParticleIcons || editor->m_alwaysHideParticleIcons) return;
        
        auto particles = editor->m_particleObjects;
        for (auto particle : CCArrayExt<ParticleGameObject*>(particles)) {
            updateLayerAlpha(particle);

            if (Settings::BetterParticles::enabled) BetterParticles::create(particle);
        }
    }

    void updateLayerAlpha(GameObject* obj) {
        if (Cache::currentLayer == -1 || Cache::playtesting) {
            Cache::layerAlphaMultiplier = 1.0f;
        }
        else if (obj->m_editorLayer2 != 0 && obj->m_editorLayer2 == Cache::currentLayer) {
            Cache::layerAlphaMultiplier = 1.0f;
        }
        else {
            Cache::layerAlphaMultiplier = obj->m_editorLayer == Cache::currentLayer 
                ? 1.0f : Settings::layerAlphaMultiplier;
        }
    }

    void updateColorCache() {
        Cache::TriggerIndicators::extrasCol1 = Settings::TriggerIndicators::extrasCol1; 
        Cache::TriggerIndicators::extrasCol2 = Settings::TriggerIndicators::extrasCol2;

        Cache::AreaPreviews::lengthCol = Settings::AreaPreviews::chroma
            ? Cache::chromaCol0 : Settings::AreaPreviews::lengthCol;
        Cache::AreaPreviews::lengthCircleCol = Settings::AreaPreviews::chroma
            ? Cache::chromaCol1 : Settings::AreaPreviews::lengthCircleCol;
        Cache::AreaPreviews::deadzoneCol = Settings::AreaPreviews::chroma
            ? Cache::chromaCol2 : Settings::AreaPreviews::deadzoneCol;
        Cache::AreaPreviews::offsetXCol = Settings::AreaPreviews::chroma
            ? Cache::chromaCol3 : Settings::AreaPreviews::offsetXCol;
        Cache::AreaPreviews::offsetYCol = Settings::AreaPreviews::chroma
            ? Cache::chromaCol4 : Settings::AreaPreviews::offsetYCol;
        
        Cache::BetterParticles::primaryCol = Settings::BetterParticles::chroma 
            ? Cache::chromaCol0 : Settings::BetterParticles::primaryCol;
        Cache::BetterParticles::secondaryCol = Settings::BetterParticles::chroma 
            ? Cache::chromaCol1 : Settings::BetterParticles::secondaryCol;
        Cache::BetterParticles::centerLineCol = Settings::BetterParticles::chroma 
            ? Cache::chromaCol2 : Settings::BetterParticles::centerLineCol;
        Cache::BetterParticles::primaryColFill = Settings::BetterParticles::chroma 
            ? Cache::chromaCol3 : Settings::BetterParticles::primaryCol;
        Cache::BetterParticles::secondaryColFill = Settings::BetterParticles::chroma 
            ? Cache::chromaCol4 : Settings::BetterParticles::secondaryCol;

        Cache::MoveIndicators::indicatorCol = Settings::MoveIndicators::chroma 
            ? Cache::chromaCol0 : Settings::MoveIndicators::indicatorCol;
        Cache::MoveIndicators::centerIndicatorCol = Settings::MoveIndicators::chroma 
            ? Cache::chromaCol1 : Settings::MoveIndicators::centerIndicatorCol;
        Cache::MoveIndicators::startCol = Settings::MoveIndicators::chroma 
            ? Cache::chromaCol2 : Settings::MoveIndicators::startCol;
        Cache::MoveIndicators::endCol = Settings::MoveIndicators::chroma 
            ? Cache::chromaCol3 : Settings::MoveIndicators::endCol;
        Cache::MoveIndicators::endPreviewCol = Settings::MoveIndicators::chroma 
            ? Cache::chromaCol4 : Settings::MoveIndicators::endPreviewCol;
    }

    void updateThicknessCache() {
        Cache::TriggerIndicators::thickness = Settings::TriggerIndicators::thickness
        / (Settings::TriggerIndicators::scaleWithZoom ? Cache::View::zoom : 1.0f);

        Cache::BetterDurationLines::thickness = Settings::BetterDurationLines::thickness
        / (Settings::BetterDurationLines::scaleWithZoom 
            ? std::min(Cache::View::zoom, Settings::BetterDurationLines::zoomClamp) : 1.0f);

        Cache::AreaPreviews::thickness = Settings::AreaPreviews::thickness
        / (Settings::AreaPreviews::scaleWithZoom ? Cache::View::zoom : 1.0f);


        Cache::BetterParticles::thickness = Settings::BetterParticles::thickness 
        / (Settings::BetterParticles::scaleWithZoom ? Cache::View::zoom : 1.0f);
        Cache::BetterParticles::centerLineThickness = Settings::BetterParticles::centerLineThickness
        / (Settings::BetterParticles::scaleWithZoom ? Cache::View::zoom : 1.0f);
        
        Cache::MoveIndicators::thickness = Settings::MoveIndicators::thickness
        / (Settings::MoveIndicators::scaleWithZoom ? Cache::View::zoom : 1.0f);
        Cache::MoveIndicators::endPreviewThickness = Settings::MoveIndicators::endPreviewThickness
        / (Settings::MoveIndicators::scaleWithZoom ? Cache::View::zoom : 1.0f);
        Cache::MoveIndicators::startRadius = Constants::moveIndicatorsStartRadiusMultiplier
        / (Settings::MoveIndicators::scaleWithZoom ? Cache::View::zoom : 1.0f);
        Cache::MoveIndicators::endSize = Constants::moveIndicatorsEndSizeMultiplier
        / (Settings::MoveIndicators::scaleWithZoom ? Cache::View::zoom : 1.0f);
    }
}