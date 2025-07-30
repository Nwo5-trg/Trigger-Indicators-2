#include "Include.hpp"
#include "../../shared/Cache.hpp"
#include "../../shared/Settings.hpp"
#include "../../utils/Utils.hpp"

using namespace geode::prelude;
using namespace BetterParticles;

void BetterParticles::create(ParticleGameObject* particle) {
    if (Settings::BetterParticles::hideOnDifferentLayer && Cache::layerAlphaMultiplier != 1.0f) return;

    Cache::BetterParticles::primaryCol.a = Cache::layerAlphaMultiplier;
    Cache::BetterParticles::secondaryCol.a = Cache::layerAlphaMultiplier;
    Cache::BetterParticles::centerLineCol.a = Cache::layerAlphaMultiplier;
    Cache::BetterParticles::primaryColFill.a = Cache::BetterParticles::primaryCol.a * Settings::BetterParticles::fillOpacity;
    Cache::BetterParticles::secondaryColFill.a = Cache::BetterParticles::secondaryCol.a * Settings::BetterParticles::fillOpacity;

    auto pos = particle->getPosition();
    if ( // culling
        !particle->m_isSelected && 
        ccpDistanceSQ(Cache::View::relativeCenter, pos) 
        > Cache::View::cullDistance
    ) return;

    auto scale = CCSize(particle->m_scaleX, particle->m_scaleY);
    float maxScale = std::max(scale.width, scale.height);

    ParticleStruct particleData; // fuck you im not caching
    GameToolbox::particleStringToStruct(particle->m_particleData, particleData);

    if (particleData.EmitterMode == 1) { // radial mode
        drawRadial(particleData, pos, maxScale);
    } else {
        drawRect(particleData, pos, scale, particle->getRotation());
    }
}

void BetterParticles::drawRadial(const ParticleStruct& particleData, CCPoint pos, float scale) {
    drawRadialSegment(particleData, pos, scale, true);
    drawRadialSegment(particleData, pos, scale, false);

    if (!Settings::BetterParticles::linesToCenter) return;

    // lines to center cuz we do those differently for circle
    float distance = std::max(
        particleData.StartRadius + particleData.StartRadiusVar, 
        particleData.EndRadius + particleData.EndRadiusVar
    ) * Constants::sqrt2Over2;

    for (auto corner : {
        ccp(pos.x + distance, pos.y + distance), 
        ccp(pos.x - distance, pos.y + distance), 
        ccp(pos.x - distance, pos.y - distance), 
        ccp(pos.x + distance, pos.y - distance)
    }) {
        Utils::drawLine(
            Cache::objectDraw, pos, corner, 
            Cache::BetterParticles::centerLineThickness, 
            Cache::BetterParticles::centerLineCol
        );
    }
}

void BetterParticles::drawRadialSegment(const ParticleStruct& particleData, CCPoint pos, float scale, bool start) {
    float rad = start ? particleData.StartRadius : particleData.EndRadius; rad *= scale;
    float var = start ? particleData.StartRadiusVar : particleData.EndRadiusVar; var *= scale;

    auto col = start ? Cache::BetterParticles::primaryCol : Cache::BetterParticles::secondaryCol;
    auto fillCol = start ? Cache::BetterParticles::primaryColFill : Cache::BetterParticles::secondaryColFill;

    if (rad == 0.0f && var != 0.0f) { // no offset
        Cache::objectDraw->drawCircle(
            pos, var, fillCol,
            Cache::BetterParticles::thickness, col, 
            Constants::betterParticlesRadialDetail
        );
    } else if (rad != 0.0f) { // offset
        Cache::objectDraw->drawCircle(
            pos, rad, Constants::transparentCCC4F, 
            var != 0.0f ? var : Cache::BetterParticles::thickness, 
            fillCol, Constants::betterParticlesRadialDetail
        );

        if (var == 0.0f) return; // if theres no variation no need to draw multiple circles

        for (float radius : {rad + var, rad - var}) {
            Cache::objectDraw->drawCircle(
                pos, radius, Constants::transparentCCC4F, 
                Cache::BetterParticles::thickness, col, 
                Constants::betterParticlesRadialDetail
            );
        }       
    } else { // fallback
        Cache::objectDraw->drawCircle(
            pos, Constants::betterParticlesRadial0FallbackSize, 
            col, 0.0f, Constants::transparentCCC4F, 
            Constants::betterParticlesRadial0FallbackDetail
        );
    }
}

void BetterParticles::drawRect(const ParticleStruct& particleData, cocos2d::CCPoint pos, cocos2d::CCSize scale, float rotation) {
    // operators being fucked gets even worse :wilted_flower:
    scale.width *= particleData.PosVarX; scale.height *= particleData.PosVarY;

    CCPoint v[] = { // still pissed off about cocos2ds bullshit operators
        ccp(pos.x + scale.width, pos.y + scale.height),
        ccp(pos.x - scale.width, pos.y + scale.height),
        ccp(pos.x - scale.width, pos.y - scale.height),
        ccp(pos.x + scale.width, pos.y - scale.height)
    };

    if (rotation != 0.0f) {
        float rad = -rotation * Constants::degToRad;
        v[0] = Utils::rotatePoint(v[0], pos, rad);
        v[1] = Utils::rotatePoint(v[1], pos, rad);
        v[2] = Utils::rotatePoint(v[2], pos, rad);
        v[3] = Utils::rotatePoint(v[3], pos, rad);
    }

    Cache::objectDraw->drawPolygon(
        v, 4, Cache::BetterParticles::primaryColFill, 
        Cache::BetterParticles::thickness,
        Cache::BetterParticles::primaryCol
    );

    for (int i = 0; i < 4; i++) {
        Utils::drawLine(
            Cache::objectDraw, pos, v[i], 
            Cache::BetterParticles::centerLineThickness, 
            Cache::BetterParticles::centerLineCol
        );
    }
}