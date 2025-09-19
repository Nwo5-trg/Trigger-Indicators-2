#include "Update.hpp"
#include "trigger-indicators/Include.hpp"
#include "spawn-indicators/Include.hpp"
#include "better-particles/Include.hpp"
#include "move-indicators/Include.hpp"
#include "../shared/Cache.hpp"
#include "../shared/Settings.hpp"
#include "../utils/Utils.hpp"

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

        Cache::View::size = CCDirector::get()->getWinSize();
        Cache::View::zoom = editor->m_objectLayer->getScale();

        updateThicknessCache();
        updateColorCache();

        // cill distance stuff
        Cache::View::relativeCenter = (
            (Cache::View::size / 2) - 
            ccp( // objects are offset soo
                editor->m_objectLayer->getPositionX(), 
                editor->m_objectLayer->getPositionY() 
                - editor->m_editorUI->m_toolbarHeight / 2
            )
        ) / Cache::View::zoom;
        Cache::View::cullDistance = Cache::View::size.width / Cache::View::zoom;
        Cache::View::cullDistance = (Cache::View::cullDistance * Cache::View::cullDistance) * Constants::cullDistanceBuffer;
        
        // cull distance for trigger indicators
        Cache::TriggerIndicators::cullDistance = Cache::View::cullDistance * Settings::TriggerIndicators::cullDistanceMultiplier;
        bool isSelectingObjects = editor->m_editorUI->getSelectedObjects()->count() != 0;
        if (isSelectingObjects) Cache::TriggerIndicators::cullDistance *= Settings::TriggerIndicators::selectedCullDistanceMultiplier;
        
        // :3c
        Cache::currentChromaCol = ccc4FFromccc3B(Cache::gayNode->getColor());

        Cache::groupDict = editor->m_groupDict;
        Cache::currentLayer = editor->m_currentLayer;
        Cache::moveTriggers = editor->m_moveTriggers;

        Cache::triggers = editor->m_drawGridLayer->m_effectGameObjects;
        for (auto trigger : CCArrayExt<EffectGameObject*>(Cache::triggers)) {
            updateLayerAlpha(trigger);

            if (Settings::SpawnIndicators::enabled) SpawnIndicators::create(trigger);
            if (Settings::TriggerIndicators::enabled) TriggerIndicators::create(trigger);
            if (Settings::MoveIndicators::enabled) MoveIndicators::create(trigger);
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
        
        Cache::BetterParticles::primaryCol = Settings::BetterParticles::chroma 
        ? Cache::currentChromaCol :Settings::BetterParticles::primaryCol;
        Cache::BetterParticles::secondaryCol = Settings::BetterParticles::chroma 
        ? Cache::currentChromaCol :Settings::BetterParticles::secondaryCol;
        Cache::BetterParticles::centerLineCol = Settings::BetterParticles::chroma 
        ? Cache::currentChromaCol :Settings::BetterParticles::centerLineCol;
        Cache::BetterParticles::primaryColFill = Settings::BetterParticles::chroma 
        ? Cache::currentChromaCol :Settings::BetterParticles::primaryCol;
        Cache::BetterParticles::secondaryColFill = Settings::BetterParticles::chroma 
        ? Cache::currentChromaCol :Settings::BetterParticles::secondaryCol;

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