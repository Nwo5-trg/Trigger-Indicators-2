#include "Include.hpp"
#include "../../shared/Cache.hpp"
#include "../../shared/Settings.hpp"
#include "../../utils/Utils.hpp"

using namespace geode::prelude;

void SpawnIndicators::create(EffectGameObject* trigger) {
    if (!trigger->m_isSpawnTriggered) return;
    if (Cache::layerAlphaMultiplier != 1.0f) return;

    auto pos = Utils::getTriggerBodyPos(trigger);

    if ( // culling
        !trigger->m_isSelected 
        && ccpDistanceSQ(Cache::View::relativeCenter, pos) 
        > Cache::View::cullDistance
    ) return;

    Cache::objectDraw->drawCircle(
        pos, // idc if i get scale twice fuck you if you lag cuz of this shit u got bigger problems
        (Settings::SpawnIndicators::size * std::max(trigger->m_scaleX, trigger->m_scaleY)) / 2, 
        Constants::transparentCCC4F, 
        Settings::SpawnIndicators::thickness / Cache::View::zoom, 
        Settings::SpawnIndicators::col, 
        Constants::spawnIndicatorDetail
    );
}