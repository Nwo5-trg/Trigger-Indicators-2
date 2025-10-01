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
        Cache::currentChromaCol = ccc4FFromccc3B(Cache::gayNode->getColor());

        Cache::groupDict = editor->m_groupDict;
        Cache::currentLayer = editor->m_currentLayer;

        for (auto trigger : Cache::triggers) {
            updateLayerAlpha(trigger);

            if (Settings::SpawnIndicators::enabled) SpawnIndicators::create(trigger);
            if (Settings::TriggerIndicators::enabled) TriggerIndicators::create(trigger);
            if (Settings::MoveIndicators::enabled && !Cache::playtesting) MoveIndicators::create(trigger);
            if (Settings::BetterDurationLines::enabled) BetterDurationLines::create(trigger);
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
        // yeah how tf am i supposed to format this might aswell hide it away in a function so update isnt messy
        Cache::layerAlphaMultiplier = Cache::currentLayer == -1 ||
            ((obj->m_editorLayer == Cache::currentLayer)
            || (obj->m_editorLayer2 == Cache::currentLayer))
        ? 1.0f : Settings::layerAlphaMultiplier;
    }

    void updateColorCache() {
        Cache::TriggerIndicators::extrasCol1 = Settings::TriggerIndicators::extrasCol1; 
        Cache::TriggerIndicators::extrasCol2 = Settings::TriggerIndicators::extrasCol2;

        Cache::AreaPreviews::lengthCol = Settings::AreaPreviews::chroma
            ? Cache::currentChromaCol : Settings::AreaPreviews::lengthCol;
        Cache::AreaPreviews::lengthCircleCol = Settings::AreaPreviews::chroma
            ? Cache::currentChromaCol : Settings::AreaPreviews::lengthCircleCol;
        Cache::AreaPreviews::deadzoneCol = Settings::AreaPreviews::chroma
            ? Cache::currentChromaCol : Settings::AreaPreviews::deadzoneCol;
        Cache::AreaPreviews::offsetXCol = Settings::AreaPreviews::chroma
            ? Cache::currentChromaCol : Settings::AreaPreviews::offsetXCol;
        Cache::AreaPreviews::offsetYCol = Settings::AreaPreviews::chroma
            ? Cache::currentChromaCol : Settings::AreaPreviews::offsetYCol;
        
        Cache::BetterParticles::primaryCol = Settings::BetterParticles::chroma 
            ? Cache::currentChromaCol : Settings::BetterParticles::primaryCol;
        Cache::BetterParticles::secondaryCol = Settings::BetterParticles::chroma 
            ? Cache::currentChromaCol : Settings::BetterParticles::secondaryCol;
        Cache::BetterParticles::centerLineCol = Settings::BetterParticles::chroma 
            ? Cache::currentChromaCol : Settings::BetterParticles::centerLineCol;
        Cache::BetterParticles::primaryColFill = Settings::BetterParticles::chroma 
            ? Cache::currentChromaCol : Settings::BetterParticles::primaryCol;
        Cache::BetterParticles::secondaryColFill = Settings::BetterParticles::chroma 
            ? Cache::currentChromaCol : Settings::BetterParticles::secondaryCol;

        Cache::MoveIndicators::indicatorCol = Settings::MoveIndicators::chroma 
            ? Cache::currentChromaCol : Settings::MoveIndicators::indicatorCol;
        Cache::MoveIndicators::centerIndicatorCol = Settings::MoveIndicators::chroma 
            ? Cache::currentChromaCol : Settings::MoveIndicators::centerIndicatorCol;
        Cache::MoveIndicators::startCol = Settings::MoveIndicators::startCol;
        Cache::MoveIndicators::endCol = Settings::MoveIndicators::endCol;
        Cache::MoveIndicators::endPreviewCol = Settings::MoveIndicators::endPreviewCol;
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