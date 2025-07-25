#pragma once

namespace BetterParticles {
    void create(ParticleGameObject* particle);

    void drawRadial(const cocos2d::ParticleStruct& particleData, cocos2d::CCPoint pos, float scale);
    void drawRadialSegment(const cocos2d::ParticleStruct& particleData, cocos2d::CCPoint pos, float scale, bool start);
    void drawRect(const cocos2d::ParticleStruct& particleData, cocos2d::CCPoint pos, cocos2d::CCSize scale, float rotation);
}