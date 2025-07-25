#include "Update.hpp"
#include "trigger-indicators/Include.hpp"
#include "spawn-indicators/Include.hpp"
#include "better-particles/Include.hpp"
#include "../shared/Cache.hpp"
#include "../shared/Settings.hpp"
#include "../utils/Utils.hpp"

using namespace geode::prelude;

void Update::draw(LevelEditorLayer* editor) {
    if (!Settings::enabled) return;
    Cache::gridDraw->clear();
    Cache::objectDraw->clear();

    // culling stuff
    Cache::View::size = CCDirector::get()->getWinSize();
    Cache::View::zoom = editor->m_objectLayer->getScale();

    Cache::BetterParticles::thickness = Settings::BetterParticles::thickness 
    / (Settings::BetterParticles::scaleWithZoom ? Cache::View::zoom : 1.0f);
    Cache::BetterParticles::centerLineThickness = Settings::BetterParticles::centerLineThickness
    / (Settings::BetterParticles::scaleWithZoom ? Cache::View::zoom : 1.0f);


    Cache::View::relativeCenter = (
        (Cache::View::size / 2) - 
        ccp(
            editor->m_objectLayer->getPositionX(), 
            editor->m_objectLayer->getPositionY() - 90 // -90 cuz objects are offset +90
        )
    ) / Cache::View::zoom;
    Cache::View::cullDistance = Cache::View::size.width / Cache::View::zoom;
    Cache::View::cullDistance = ((Cache::View::cullDistance *Cache::View::cullDistance) / Cache::View::zoom) * Constants::cullDistanceBuffer;
    
    Cache::TriggerIndicators::cullDistance = Cache::View::cullDistance * Settings::TriggerIndicators::cullDistanceMultiplier;
    bool isSelectingObjects = editor->m_editorUI->getSelectedObjects()->count() != 0;
    if (isSelectingObjects) Cache::TriggerIndicators::cullDistance *= Settings::TriggerIndicators::selectedCullDistanceMultiplier;
    
    // :3c
    Cache::currentChromaCol = ccc4FFromccc3B(Cache::gayNode->getColor());

    Cache::groupDict = editor->m_groupDict;
    Cache::currentLayer = editor->m_currentLayer;

    auto triggers = editor->m_drawGridLayer->m_effectGameObjects;
    for (auto trigger : CCArrayExt<EffectGameObject*>(triggers)) {
        Utils::updateLayerAlpha(trigger);

        if (Settings::SpawnIndicators::enabled) SpawnIndicators::create(trigger);
        if (Settings::TriggerIndicators::enabled) TriggerIndicators::create(trigger);
    }

    if (editor->m_hideParticleIcons || editor->m_alwaysHideParticleIcons) return;
    auto particles = editor->m_particleObjects;
    for (auto particle : CCArrayExt<ParticleGameObject*>(particles)) {
        Utils::updateLayerAlpha(particle);

        if (Settings::BetterParticles::enabled) BetterParticles::create(particle);
    }
}