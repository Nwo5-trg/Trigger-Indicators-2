#include "IndicatorVariables.hpp"
#include "../Utils.hpp"

using namespace geode::prelude;
using namespace IndicatorVars;

void IndicatorVars::updateSettings() {
    auto mod = Mod::get();
    onlySelected = mod->getSettingValue<bool>("only-selected");
    onlyTriggers = mod->getSettingValue<bool>("only-triggers");
    
    auto maxDistanceSetting = mod->getSettingValue<double>("max-distance");
    maxDistance = maxDistanceSetting * maxDistanceSetting;

    thickness = mod->getSettingValue<double>("thickness");

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
    
    settingsButtonTexture = "nwo5.trigger_indicators_v2/" + mod->getSettingValue<std::string>("settings-button-texture") + ".png";

    chroma = mod->getSettingValue<bool>("chroma");
    sayoDeviceSensitivity = mod->getSettingValue<double>("sayo-device-sensitivity");
}