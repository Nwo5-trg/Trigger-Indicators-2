#include "Include.hpp"
#include "../../shared/Cache.hpp"
#include "../../shared/Settings.hpp"
#include "../../utils/Utils.hpp"

using namespace geode::prelude;
using namespace MoveIndicators;

void MoveIndicators::draw(EffectGameObject* trigger) {   
    Cache::MoveIndicators::positions.clear();
    Utils::getSharedObjectGroups(Cache::MoveIndicators::targetObjects, Cache::MoveIndicators::sharedGroups);
    getPositions(trigger, Settings::MoveIndicators::objectGroupingMode);
    if (Cache::MoveIndicators::positions.empty()) return;

    // now so we dont recalculate easing for like clusters and stuff lets just cache the offsets
    auto easingType = Settings::MoveIndicators::previewEasing 
    ? trigger->m_easingType : EasingType::None;
    auto easingFunc = Utils::getEasingFunction(easingType);

    auto distance = trigger->m_moveOffset;
    Cache::MoveIndicators::indicatorSegments.clear();

    if (easingType == EasingType::None || distance.x == 0.0f || distance.y == 0.0f) {
        Cache::MoveIndicators::indicatorSegments.reserve(1);
        Cache::MoveIndicators::indicatorSegments.emplace_back(ccp(0.0f, 0.0f), distance);
    } else {
        float exponent = trigger->m_easingRate;
        Cache::MoveIndicators::indicatorSegments.reserve(Settings::MoveIndicators::easingSteps);
        
        auto start = ccp(0.0f, 0.0f);
        bool visualizeX = distance.x >= distance.y;
        for (int i = 1; i <= Settings::MoveIndicators::easingSteps; ++i) {
            float t = float(i) / Settings::MoveIndicators::easingSteps;
            float eased = easingFunc(t, exponent);
            
            auto current = visualizeX 
            ? ccp(distance.x * t, distance.y * eased) 
            : ccp(distance.x * eased, distance.y * t);

            Cache::MoveIndicators::indicatorSegments.emplace_back(start, current);
            start = current;
        }
    }
    
    for (const auto& pos : Cache::MoveIndicators::positions) {
        drawIndicator(trigger, pos);
    }
}

void MoveIndicators::drawIndicator(EffectGameObject* trigger, const std::pair<CCPoint, CCPoint>& pair) {
    auto endOffset = Cache::MoveIndicators::indicatorSegments.back().second;

    // show preview
    if (trigger->m_isGripSlope) {
        getObjectPreview(endOffset);
        for (const auto& rect : Cache::MoveIndicators::objectPreviews) {
            Cache::dontUpdateGridDraw->drawRect( // so the previews are hopefully less intrusive
                rect.p1, rect.p2, Constants::transparentCCC4F,
                Cache::MoveIndicators::endPreviewThickness,
                Cache::MoveIndicators::endPreviewCol
            );
        }
    }

    Utils::drawLine(
        Cache::dontUpdateGridDraw, pair.first, pair.second, // so there isnt overlapping
        Cache::MoveIndicators::thickness, 
        Cache::MoveIndicators::centerIndicatorCol
    );

    for (const auto& segment : Cache::MoveIndicators::indicatorSegments) {
        Utils::drawLine(
            Cache::dontUpdateObjectDraw, 
            pair.second + segment.first, pair.second + segment.second, 
            Cache::MoveIndicators::thickness, 
            Cache::MoveIndicators::indicatorCol
        );
    }
 
    Cache::dontUpdateObjectDraw->drawCircle(
        pair.second + Cache::MoveIndicators::indicatorSegments.front().first, 
        Cache::MoveIndicators::startRadius,
        Cache::MoveIndicators::startCol, 0.0f, 
        Constants::transparentCCC4F, 
        Constants::moveIndicatorsStartCircleDetail
    );
    Cache::dontUpdateObjectDraw->drawDot(
        pair.second + endOffset, 
        Cache::MoveIndicators::endSize,
        Cache::MoveIndicators::endCol
    );
}