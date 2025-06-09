#include "IndicatorVariables.hpp"
#include "../Utils.hpp"

using namespace geode::prelude;

void IndicatorVars::updateSettings() {
    auto mod = Mod::get();
    IndicatorVars::onlySelected = mod->getSettingValue<bool>("only-selected");
    IndicatorVars::onlyTriggers = mod->getSettingValue<bool>("only-triggers");
    auto maxDistance = mod->getSettingValue<double>("max-distance");
    IndicatorVars::maxDistance = maxDistance * maxDistance;
    IndicatorVars::thickness = mod->getSettingValue<double>("thickness");
    IndicatorVars::clusterSize = mod->getSettingValue<double>("cluster-size");
    IndicatorVars::clusterMaxThreshold = mod->getSettingValue<int64_t>("cluster-max-threshold");
    auto indicatorType = mod->getSettingValue<std::string>("indicator-type");
    if (indicatorType == "Individual Lines") IndicatorVars::indicatorType = IndicatorType::IndividualLine;
    else if (indicatorType == "Rect") IndicatorVars::indicatorType = IndicatorType::Rect;
    else IndicatorVars::indicatorType = IndicatorType::Clustered;
    IndicatorVars::extrasCol1 = ccc4FFromccc4B(mod->getSettingValue<ccColor4B>("extras-col-one"));
    IndicatorVars::extrasCol2 = ccc4FFromccc4B(mod->getSettingValue<ccColor4B>("extras-col-two"));
    IndicatorVars::groupBlacklist = parseIntArray(mod->getSettingValue<std::string>("group-blacklist"));
    IndicatorVars::triggerBlacklist = parseIntArray(mod->getSettingValue<std::string>("trigger-blacklist") 
    + "," + mod->getSettingValue<std::string>("forced-trigger-blacklist")); // saves checking 2 diff sets
    IndicatorVars::settingsButtonTexture = "nwo5.trigger_indicators_v2/" + mod->getSettingValue<std::string>("settings-button-texture") + ".png";

    IndicatorVars::chroma = mod->getSettingValue<bool>("chroma");
    IndicatorVars::sayoDeviceSensitivity = mod->getSettingValue<double>("sayo-device-sensitivity");
}