#include "Include.hpp"
#include "../../shared/Settings.hpp"
#include "../../shared/Cache.hpp"
#include "../../utils/Utils.hpp"

using namespace geode::prelude;

namespace AreaPreviews {
    void create(EffectGameObject* trigger) {
        if (!trigger->m_isIceBlock) return;
        
        if (!Utils::areaTriggers.contains(trigger->m_objectID)) return;

        auto area = static_cast<EnterEffectObject*>(trigger);

        if ( // culling
            !trigger->m_isSelected && 
            Settings::AreaPreviews::onlySelected ? true : ccpDistanceSQ(Cache::View::relativeCenter, trigger->getPosition()) 
            > Cache::View::cullDistanceSQ
        ) return;

        Cache::AreaPreviews::lengthCol.a = Cache::layerAlphaMultiplier;
        Cache::AreaPreviews::lengthCircleCol.a = Cache::layerAlphaMultiplier;
        Cache::AreaPreviews::deadzoneCol.a = Cache::layerAlphaMultiplier;
        Cache::AreaPreviews::offsetXCol.a = Cache::layerAlphaMultiplier;
        Cache::AreaPreviews::offsetYCol.a = Cache::layerAlphaMultiplier;

        draw(area);
    }

    // i dont even give a shit anymore vro fuck refactoring ts is so dumb
    void draw(EnterEffectObject* trigger) {
        int length = trigger->m_length;
        int lengthVar = trigger->m_lengthVariance;

        if ((length + lengthVar) == 0) return;

        bool twoDir = trigger->m_twoDirections;
        bool inbound = trigger->m_inbound;

        int type = trigger->m_directionType;
        int offsetY = type == 0 ? trigger->m_offsetY : (type == 2 ? -trigger->m_offset : 0.0f); // robert topala what the fuck man
        int offsetX = type == 2 ? 0.0f : trigger->m_offset;

        float deadzone = inbound ? (length * trigger->m_deadzone) : length - (length * trigger->m_deadzone);

        auto center = trigger->getPosition();
        auto pos = center + ccp(offsetX, offsetY);

        switch (trigger->m_directionType) {
            case 0: {
                if (Settings::AreaPreviews::showLengthCircle) {
                    Cache::gridDraw->drawCircle(
                        pos, length + lengthVar, Constants::transparentCCC4F,
                        Cache::AreaPreviews::thickness, Cache::AreaPreviews::lengthCircleCol,
                        Constants::areaPreviewsLengthCircleDetail
                    );
                }
                if (Settings::AreaPreviews::showDeadzone && trigger->m_deadzone >= Constants::areaPreviewsDeadzoneThreshold) {
                    Cache::gridDraw->drawCircle(
                        pos, deadzone, Constants::transparentCCC4F,
                        Cache::AreaPreviews::thickness, Cache::AreaPreviews::deadzoneCol,
                        Constants::areaPreviewsLengthCircleDetail
                    );
                }
                if (Settings::AreaPreviews::showLength) {
                    Utils::drawLine(
                        Cache::gridDraw, {pos.x - length, pos.y}, {pos.x + length, pos.y}, 
                        Cache::AreaPreviews::thickness, Cache::AreaPreviews::lengthCol
                    );
                    Utils::drawLine(
                        Cache::gridDraw, {pos.x, pos.y - length}, {pos.x, pos.y + length}, 
                        Cache::AreaPreviews::thickness, Cache::AreaPreviews::lengthCol
                    );

                    drawArrow({pos.x - length, pos.y}, inbound ? ArrowDirection::Right : ArrowDirection::Left);
                    drawArrow({pos.x + length, pos.y}, inbound ? ArrowDirection::Left : ArrowDirection::Right);
                    drawArrow({pos.x, pos.y - length}, inbound ? ArrowDirection::Up : ArrowDirection::Down);
                    drawArrow({pos.x, pos.y + length}, inbound ? ArrowDirection::Down : ArrowDirection::Up);

                    drawDottedLine({pos.x - (length + lengthVar), pos.y}, {pos.x - length, pos.y}, Cache::AreaPreviews::lengthCol);
                    drawDottedLine({pos.x + length, pos.y}, {pos.x + (length + lengthVar), pos.y}, Cache::AreaPreviews::lengthCol);
                    drawDottedLine({pos.x, pos.y - (length + lengthVar)}, {pos.x, pos.y - length}, Cache::AreaPreviews::lengthCol);
                    drawDottedLine({pos.x, pos.y + length}, {pos.x, pos.y + (length + lengthVar)}, Cache::AreaPreviews::lengthCol);
                }
            break; }
            case 1: {
                if (Settings::AreaPreviews::showLengthCircle) {
                    Utils::drawLine(
                        Cache::gridDraw, {pos.x, pos.y - Constants::areaPreviewsScreenEdgeLineLength}, 
                        {pos.x, pos.y + Constants::areaPreviewsScreenEdgeLineLength},
                        Cache::AreaPreviews::thickness, Cache::AreaPreviews::lengthCircleCol
                    );
                }
                if (Settings::AreaPreviews::showDeadzone && trigger->m_deadzone >= Constants::areaPreviewsDeadzoneThreshold) {
                    Utils::drawLine(
                        Cache::gridDraw, {pos.x + deadzone, pos.y - Constants::areaPreviewsScreenEdgeLineLength}, 
                        {pos.x + deadzone, pos.y + Constants::areaPreviewsScreenEdgeLineLength},
                        Cache::AreaPreviews::thickness, Cache::AreaPreviews::deadzoneCol
                    );
                    if (twoDir) {
                        Utils::drawLine(
                            Cache::gridDraw, {pos.x - deadzone, pos.y - Constants::areaPreviewsScreenEdgeLineLength}, 
                            {pos.x - deadzone, pos.y + Constants::areaPreviewsScreenEdgeLineLength},
                            Cache::AreaPreviews::thickness, Cache::AreaPreviews::deadzoneCol
                        );
                    }
                }
                if (Settings::AreaPreviews::showLength) {
                    Utils::drawLine(
                        Cache::gridDraw, {pos.x - (twoDir ? length : 0.0f), pos.y}, {pos.x + length, pos.y}, 
                        Cache::AreaPreviews::thickness, Cache::AreaPreviews::lengthCol
                    );

                    if (twoDir) {
                        drawArrow({pos.x - length, pos.y}, inbound ? ArrowDirection::Right : ArrowDirection::Left);
                        drawArrow({pos.x + length, pos.y}, inbound ? ArrowDirection::Left : ArrowDirection::Right);

                        drawDottedLine({pos.x - (length + lengthVar), pos.y}, {pos.x - length, pos.y}, Cache::AreaPreviews::lengthCol);
                        drawDottedLine({pos.x + length, pos.y}, {pos.x + (length + lengthVar), pos.y}, Cache::AreaPreviews::lengthCol);
                    }
                    else {
                        drawArrow({pos.x + length, pos.y}, inbound ? ArrowDirection::Left : ArrowDirection::Right);
                        drawDottedLine({pos.x + length, pos.y}, {pos.x + (length + lengthVar), pos.y}, Cache::AreaPreviews::lengthCol);
                    }
                }
            break; }
            case 2: {
                if (Settings::AreaPreviews::showLengthCircle) {
                    Utils::drawLine(
                        Cache::gridDraw, {pos.x - Constants::areaPreviewsScreenEdgeLineLength, pos.y}, 
                        {pos.x + Constants::areaPreviewsScreenEdgeLineLength, pos.y},
                        Cache::AreaPreviews::thickness, Cache::AreaPreviews::lengthCircleCol
                    );
                }
                if (Settings::AreaPreviews::showDeadzone && trigger->m_deadzone >= Constants::areaPreviewsDeadzoneThreshold) {
                    Utils::drawLine(
                        Cache::gridDraw, {pos.x - Constants::areaPreviewsScreenEdgeLineLength, pos.y + deadzone}, 
                        {pos.x + Constants::areaPreviewsScreenEdgeLineLength, pos.y + deadzone},
                        Cache::AreaPreviews::thickness, Cache::AreaPreviews::deadzoneCol
                    );
                    if (twoDir) {
                        Utils::drawLine(
                            Cache::gridDraw, {pos.x - Constants::areaPreviewsScreenEdgeLineLength, pos.y - deadzone}, 
                            {pos.x + Constants::areaPreviewsScreenEdgeLineLength, pos.y - deadzone},
                            Cache::AreaPreviews::thickness, Cache::AreaPreviews::deadzoneCol
                        );
                    }
                }
                if (Settings::AreaPreviews::showLength) {
                    Utils::drawLine(
                        Cache::gridDraw, {pos.x, pos.y - (twoDir ? length : 0.0f)}, {pos.x, pos.y + length}, 
                        Cache::AreaPreviews::thickness, Cache::AreaPreviews::lengthCol
                    );

                    if (twoDir) {
                        drawArrow({pos.x, pos.y - length}, inbound ? ArrowDirection::Up : ArrowDirection::Down);
                        drawArrow({pos.x, pos.y + length}, inbound ? ArrowDirection::Down : ArrowDirection::Up);

                        drawDottedLine({pos.x, pos.y - (length + lengthVar)}, {pos.x, pos.y - length}, Cache::AreaPreviews::lengthCol);
                        drawDottedLine({pos.x, pos.y + length}, {pos.x, pos.y + (length + lengthVar)}, Cache::AreaPreviews::lengthCol);
                    }
                    else {
                        drawArrow({pos.x, pos.y + length}, inbound ? ArrowDirection::Down : ArrowDirection::Up);
                        drawDottedLine({pos.x, pos.y + length}, {pos.x, pos.y + (length + lengthVar)}, Cache::AreaPreviews::lengthCol);
                    }
                }
            break; }
        }

        if (type != 1) {
            int var = type == 2 ? trigger->m_offsetVariance : trigger->m_offsetYVariance;
            if (offsetY < 0) var *= -1;
            Utils::drawLine(
                Cache::gridDraw, {center.x + offsetX, center.y}, pos,
                Cache::AreaPreviews::thickness, Cache::AreaPreviews::offsetYCol
            );
            drawDottedLine(
                pos, {pos.x, pos.y + var},
                Cache::AreaPreviews::offsetYCol
            );
        }
        if (type != 2) {
            int var = offsetX < 0 ? -trigger->m_offsetVariance : trigger->m_offsetVariance;
            Utils::drawLine(
                Cache::gridDraw, center, {center.x + offsetX, center.y},
                Cache::AreaPreviews::thickness, Cache::AreaPreviews::offsetXCol
            );
            drawDottedLine(
                {center.x + offsetX, center.y}, {center.x + offsetX + var, center.y},
                Cache::AreaPreviews::offsetXCol
            );
        }
    }

    void drawArrow(CCPoint pos, ArrowDirection type) {
        CCPoint off1, off2;

        switch (type) { // ts so fucked vro
            case ArrowDirection::Up: {
                off1 = ccp(-Settings::AreaPreviews::arrowSize, -Settings::AreaPreviews::arrowSize);
                off2 = ccp(Settings::AreaPreviews::arrowSize, -Settings::AreaPreviews::arrowSize);
            break; }
            case ArrowDirection::Down: {
                off1 = ccp(-Settings::AreaPreviews::arrowSize, Settings::AreaPreviews::arrowSize);
                off2 = ccp(Settings::AreaPreviews::arrowSize, Settings::AreaPreviews::arrowSize);
            break; }
            case ArrowDirection::Left: {
                off1 = ccp(Settings::AreaPreviews::arrowSize, -Settings::AreaPreviews::arrowSize);
                off2 = ccp(Settings::AreaPreviews::arrowSize, Settings::AreaPreviews::arrowSize);
            break; }
            case ArrowDirection::Right: {
                off1 = ccp(-Settings::AreaPreviews::arrowSize, -Settings::AreaPreviews::arrowSize);
                off2 = ccp(-Settings::AreaPreviews::arrowSize, Settings::AreaPreviews::arrowSize);
            break; }
        }

        Utils::drawLine(
            Cache::gridDraw, pos + off1, pos, Cache::AreaPreviews::thickness,
            Cache::AreaPreviews::lengthCol
        );
        Utils::drawLine(
            Cache::gridDraw, pos + off2, pos, Cache::AreaPreviews::thickness,
            Cache::AreaPreviews::lengthCol
        );
    }

    void drawDottedLine(CCPoint p1, CCPoint p2, const ccColor4F& col) {
        if (p1 == p2) return;
        auto dir = p2 - p1;
        float length = dir.getLength();
        dir = ccpNormalize(dir);

        for (float dist = 0.0f; dist < length; dist += Constants::areaPreviewsDottedLineSegmentSize) {
            Utils::drawLine(
                Cache::gridDraw, (p1 + dir * dist),
                (p1 + dir * std::min(dist + Constants::areaPreviewsDottedLineDotSize, length)),
                Cache::AreaPreviews::thickness, col
            );
        }
    }
}