#include "Settings.hpp"
#include "Cache.hpp"
#include "../utils/Utils.hpp"
#include "../utils/Constants.hpp"

using namespace geode::prelude;
using namespace Settings;

void Settings::updateSettings() {
    mod = Mod::get();

    Constants::loadConstants();

    set(enabled, "features-enabled-mod");
    set(layerAlphaMultiplier, "general-layer-alpha-multiplier");

    settingsButtonTexture = "nwo5.trigger_indicators_v2/" 
        + mod->getSettingValue<std::string>("general-settings-button-texture") 
        + ".png";

    { // trigger indicators
        set(TriggerIndicators::enabled, "features-enabled-trigger-indicators");

        set(TriggerIndicators::onlySelected, "trigger-indicators-only-selected");
        set(TriggerIndicators::onlyTriggers, "trigger-indicators-only-triggers");
        set(TriggerIndicators::onlySpawn, "trigger-indicators-only-spawn");
        set(TriggerIndicators::clusterObjects, "trigger-indicators-cluster-objects");
        set(TriggerIndicators::clusterTriggers, "trigger-indicators-cluster-triggers");
        set(TriggerIndicators::clusterFallbackIndividualObjects, "trigger-indicators-cluster-fallback-individual-objects");
        set(TriggerIndicators::clusterFallbackIndividualTriggers,"trigger-indicators-cluster-fallback-individual-triggers");

        set(TriggerIndicators::clusterObjectsMaxThreshold, "trigger-indicators-cluster-objects-max-threshold");
        set(TriggerIndicators::clusterTriggersMaxThreshold, "trigger-indicators-cluster-triggers-max-threshold");
        int maxClusterThreshold = std::max(
            TriggerIndicators::clusterObjectsMaxThreshold, TriggerIndicators::clusterTriggersMaxThreshold
        );
        Cache::Utils::clusters.reserve(maxClusterThreshold);
        Cache::Utils::clusterObjQueue.reserve(maxClusterThreshold);

        set(TriggerIndicators::maxDistance, "trigger-indicators-max-distance"); 
        TriggerIndicators::maxDistance *= TriggerIndicators::maxDistance;
        set(TriggerIndicators::thickness, "trigger-indicators-thickness");
        set(TriggerIndicators::clusterObjectsSize, "trigger-indicators-cluster-objects-size");
        set(TriggerIndicators::clusterTriggersSize, "trigger-indicators-cluster-triggers-size");

        set(TriggerIndicators::extrasCol1, "trigger-indicators-extras-col-one");
        set(TriggerIndicators::extrasCol2, "trigger-indicators-extras-col-two");
        // so i dont have to make new cccolor4fs every frame for every trigger like i was doing :3c
        Cache::TriggerIndicators::extrasCol1 = TriggerIndicators::extrasCol1; 
        Cache::TriggerIndicators::extrasCol2 = TriggerIndicators::extrasCol2; 

        set(TriggerIndicators::groupBlacklist, "trigger-indicators-group-blacklist");
        set(TriggerIndicators::triggerBlacklist, "trigger-indicators-trigger-blacklist");

        set(TriggerIndicators::chroma, "trigger-indicators-chroma");

        set(TriggerIndicators::cullDistanceMultiplier, "trigger-indicators-cull-distance-multiplier");
        set(TriggerIndicators::selectedCullDistanceMultiplier, "trigger-indicators-selected-cull-distance-multiplier");
    }

    { // spawn indicators
        set(SpawnIndicators::enabled, "features-enabled-spawn-indicators");

        set(SpawnIndicators::thickness, "spawn-indicators-thickness");
        set(SpawnIndicators::size, "spawn-indicators-size");
        
        set(SpawnIndicators::col, "spawn-indicators-col");
    }

    { // better particles
        set(BetterParticles::enabled, "features-enabled-better-particles");

        set(BetterParticles::fillForRect, "better-particles-fill-for-rect");
        set(BetterParticles::linesToCenter, "better-particles-lines-to-center");
        set(BetterParticles::hideOnDifferentLayer, "better-particles-hide-on-different-layer");
        set(BetterParticles::scaleWithZoom, "better-particles-scale-with-zoom");

        set(BetterParticles::thickness, "better-particles-thickness");
        set(BetterParticles::centerLineThickness, "better-particles-center-line-thickness");
        set(BetterParticles::fillOpacity, "better-particles-fill-opacity");

        set(BetterParticles::primaryCol, "better-particles-primary-col");
        set(BetterParticles::secondaryCol, "better-particles-secondary-col");
        if (mod->getSettingValue<bool>("better-particles-primary-col-for-center-lines")) {
            BetterParticles::centerLineCol = BetterParticles::primaryCol;
        } else {
            set(BetterParticles::centerLineCol, "better-particles-center-line-col");
        }
        Cache::BetterParticles::primaryCol = BetterParticles::primaryCol;
        Cache::BetterParticles::secondaryCol = BetterParticles::secondaryCol;
        Cache::BetterParticles::centerLineCol = BetterParticles::centerLineCol;
        Cache::BetterParticles::primaryColFill = BetterParticles::primaryCol;
        Cache::BetterParticles::secondaryColFill = BetterParticles::secondaryCol;
    }

    set(sayoDeviceSensitivity, "silly-sayo-device-sensitivity");
}

void Settings::set(bool& setting, const char* key) {
    setting = mod->getSettingValue<bool>(key);
}
void Settings::set(int& setting, const char* key) {
    setting = mod->getSettingValue<int64_t>(key);
}
void Settings::set(float& setting, const char* key) {
    setting = mod->getSettingValue<double>(key);
}
void Settings::set(ccColor4F& setting, const char* key) {
    setting = ccc4FFromccc4B(mod->getSettingValue<ccColor4B>(key));
}
void Settings::set(std::unordered_set<int>& setting, const char* key) {
    setting = Utils::parseIntArray(mod->getSettingValue<std::string>(key));
}

$on_mod(Loaded) {
    updateSettings();
    
    listenForAllSettingChangesV3([] (std::shared_ptr<geode::SettingV3>){
        updateSettings();
    });
}