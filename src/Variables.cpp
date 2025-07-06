#include "Variables.hpp"
#include "Utils.hpp"

using namespace geode::prelude;
using namespace Variables;

void Variables::updateSettings() { // kinda randomly sorted but its an organised mess so good enough
    auto mod = Mod::get();
    hasCollisionIDs = false;

    disableMod = mod->getSettingValue<bool>("disable-mod");
    disableIndicators = mod->getSettingValue<bool>("disable-indicators");

    onlySelected = mod->getSettingValue<bool>("only-selected");
    onlyTriggers = mod->getSettingValue<bool>("only-triggers");
    onlySpawn = mod->getSettingValue<bool>("only-spawn");
    
    auto maxDistanceSetting = mod->getSettingValue<double>("max-distance");
    maxDistance = maxDistanceSetting * maxDistanceSetting;

    thickness = mod->getSettingValue<double>("thickness");
    spawnIndicatorThickness = mod->getSettingValue<double>("spawn-indicator-thickness");

    clusterSize = mod->getSettingValue<double>("cluster-size");
    clusterMaxThreshold = mod->getSettingValue<int64_t>("cluster-max-threshold");
    
    auto indicatorTypeSetting = mod->getSettingValue<std::string>("indicator-type");
    if (indicatorTypeSetting == "Individual Lines") indicatorType = IndicatorType::IndividualLine;
    else if (indicatorTypeSetting == "Rect") indicatorType = IndicatorType::Rect;
    else indicatorType = IndicatorType::Clustered;
    
    extrasCol1 = ccc4FFromccc4B(mod->getSettingValue<ccColor4B>("extras-col-one"));
    extrasCol2 = ccc4FFromccc4B(mod->getSettingValue<ccColor4B>("extras-col-two"));

    groupBlacklist = parseIntArray(mod->getSettingValue<std::string>("group-blacklist"));
    triggerBlacklist = parseIntArray(mod->getSettingValue<std::string>("trigger-blacklist") 
    + "," + mod->getSettingValue<std::string>("forced-trigger-blacklist")); // saves checking 2 diff sets
    
    itemIDs = mod->getSettingValue<bool>("item-ids");
    collisionIDs = mod->getSettingValue<bool>("collision-ids");
    spawnIndicators = mod->getSettingValue<bool>("spawn-indicators");
    
    settingsButtonTexture = "nwo5.trigger_indicators_v2/" + mod->getSettingValue<std::string>("settings-button-texture") + ".png";

    groupLabels = mod->getSettingValue<bool>("group-labels");
    groupLabelsSize = mod->getSettingValue<double>("group-labels-size");

    chroma = mod->getSettingValue<bool>("chroma");
    sayoDeviceSensitivity = mod->getSettingValue<double>("sayo-device-sensitivity");
    cullDistanceMultiplier = mod->getSettingValue<double>("cull-distance-multiplier");
}