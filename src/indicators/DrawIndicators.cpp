#include "DrawIndicators.hpp"
#include "IndicatorVariables.hpp"
#include "../Utils.hpp"

using namespace geode::prelude;

void drawForTrigger(EffectGameObject* trigger, std::vector<GameObject*>& targetObjects, std::vector<GameObject*>& centerObjects, float alpha) {
    auto triggerScale = trigger->getScale();
    auto triggerPos = trigger->getPosition();
    auto triggerBodyPos = ccp(triggerPos.x, triggerPos.y - (5 * triggerScale)); // -5 cuz triggers arent centered
    auto posOffset0 = ccp(triggerBodyPos.x + (10 * triggerScale), triggerBodyPos.y); // no center
    auto posOffset1 = ccp(triggerBodyPos.x + (10 * triggerScale), triggerBodyPos.y + (4.5f * triggerScale)); // target
    auto posOffset2 = ccp(triggerBodyPos.x + (10 * triggerScale), triggerBodyPos.y - (4.5f * triggerScale)); // center
    auto triggerID = trigger->m_objectID;
    if (trigger->m_activateGroup && triggerID == 1049) triggerID = 10001; // toggle triggers, fuck off with stop triggers im not fixing those

    auto hasCenterObjects = !(centerObjects.empty());

    // layer alpha shit
    auto indicatorCol = getTriggerCol(triggerID);
    indicatorCol.a *= alpha;
    auto extrasCol1 = IndicatorVars::extrasCol1;
    extrasCol1.a *= alpha;
    auto extrasCol2 = IndicatorVars::extrasCol2;
    extrasCol2.a *= alpha;

    std::vector<GameObject*>* vectors[] = {&targetObjects, &centerObjects}; // avoids copies or smth
    for (int i = 0; i < 2; i++) {
        if (i == 1 && !hasCenterObjects) break;
        int group = i == 1 ? trigger->m_centerGroupID : trigger->m_targetGroupID;
        auto& vector = *vectors[i];
        auto pos = hasCenterObjects ? (i == 1 ? posOffset2 : posOffset1) : posOffset0;

        switch (IndicatorVars::indicatorType) { // so much easier to read with curly braces im sorry
            case IndicatorType::IndividualLine: {  // individual lines
                drawIndividualLines(vector, pos, indicatorCol, extrasCol1, extrasCol2, false, vector, group);
                break;
            }
            
            case IndicatorType::Rect: {  // rect
                std::vector<GameObject*> objVector;
                drawIndividualLines(vector, pos, indicatorCol, extrasCol1, extrasCol2, true, objVector, group);
                
                drawIndicatorWithRect(pos, objVector, indicatorCol, group);
                break;
            }

            case IndicatorType::Clustered: { // clustered
                std::vector<GameObject*> clusterVector;
                drawIndividualLines(vector, pos, indicatorCol, extrasCol1, extrasCol2, true, clusterVector, group);

                if (clusterVector.size() > IndicatorVars::clusterMaxThreshold) {
                    drawIndicatorWithRect(pos, clusterVector, indicatorCol, group);
                } else {
                    auto clusters = getClusters(clusterVector, IndicatorVars::clusterSize);
                    for (auto& cluster : clusters) drawIndicatorWithRect(pos, cluster, indicatorCol, group);
                }
                break;
            }
        }
    }
    // draw output
    drawExtras(triggerBodyPos, triggerScale, hasCenterObjects ? 2 : 1, extrasCol1, extrasCol2);
}

void drawIndividualLines( // no clue how to even format this properly
    const std::vector<GameObject*>& vector, CCPoint pos, ccColor4F indicatorCol, ccColor4F extrasCol1, ccColor4F extrasCol2,
    bool useClusterVector, std::vector<GameObject*>& clusterVector, int group
) {
    for (auto obj : vector) {
        auto isTrigger = obj->m_isTrigger;
        if (useClusterVector && !isTrigger) {
            clusterVector.push_back(obj);
            continue;
        }
        auto objPos = obj->getPosition();
        auto objScale = obj->getScale();
        auto offsetObjPos = ccp(objPos.x - (isTrigger ? (10 * objScale) : 0), objPos.y - (5 * objScale));

        drawIndicator(pos, offsetObjPos, indicatorCol, group);

        if (isTrigger) drawExtras(objPos, objScale, 0, extrasCol1, extrasCol2);
    }
}

void drawIndicator(CCPoint triggerPos, CCPoint targetPos, ccColor4F col, int group) {
    IndicatorVars::triggerIndicatorDraw->drawSegment(triggerPos, targetPos, IndicatorVars::thickness, col);
    if (IndicatorVars::groupLabels) {
        auto center = ccpMidpoint(triggerPos, targetPos);
        auto label = CCLabelBMFont::create(std::to_string(group).c_str(), "bigFont.fnt"); // could just save the group as a string but like its already unoptimized so idrc
        label->setScale(IndicatorVars::groupLabelsSize);
        label->setPosition(center);
        IndicatorVars::triggerIndicatorGroupLayer->addChild(label);
    }
};

void drawIndicatorWithRect(CCPoint triggerPos, const std::vector<GameObject*>& objs, ccColor4F col, int group) {
    CCPoint p1 = ccp(FLT_MAX, FLT_MAX); // why not in utils? fuck you thats why
    CCPoint p2 = ccp(-FLT_MAX, -FLT_MAX);
    for (auto obj : objs) {
        auto pos = obj->getPosition();
        auto size = obj->getScaledContentSize() / 2;
        float left = pos.x - size.width;
        float right = pos.x + size.width;
        float bottom = pos.y - size.height;
        float top = pos.y + size.height;

        if (left < p1.x) p1.x = left;
        if (bottom < p1.y) p1.y = bottom;
        if (right > p2.x) p2.x = right;
        if (top > p2.y) p2.y = top;
    }

    p1 = ccp(p1.x - IndicatorVars::thickness, p1.y - IndicatorVars::thickness); // so half the line doesnt go in the blocks
    p2 = ccp(p2.x + IndicatorVars::thickness, p2.y + IndicatorVars::thickness); 

    IndicatorVars::triggerIndicatorDraw->drawRect(p1, p2, emptyCCC4F, IndicatorVars::thickness, col);
    drawIndicator(triggerPos, getLineCut(triggerPos, p1, p2), col, group);
};   

void drawExtras(CCPoint objPos, float scale, int type, ccColor4F col1, ccColor4F col2) {
    switch (type) {
        case 0: { // input
            // -5 cuz i dont pass the centered pos to inputs, only for outputs cuz i already calculated that
            auto pos = ccp(objPos.x - (10 * scale), objPos.y - (5 * scale));
            IndicatorVars::triggerExtraDraw->drawCircle(pos, 2 * scale, col1, 0.5f * scale, col2, 32);
            break;
        }

        case 1: { // output with no triggers
            drawExtrasOutput(objPos, scale, col1, col2);
            break;
        }

        case 2: { // output with triggers
            drawExtrasOutput(ccp(objPos.x, objPos.y + (4.5f * scale)), scale, col1, col2); 
            drawExtrasOutput(ccp(objPos.x, objPos.y - (4.5f * scale)), scale, col1, col2);
            break;
        }
    }
}

void drawExtrasOutput(CCPoint pos, float scale, ccColor4F col1, ccColor4F col2) {
    CCPoint polygon[3] = {
        ccp(pos.x + (12.0f * scale), pos.y),
        ccp(pos.x + (8.0f * scale),  pos.y + (3.5f * scale)),
        ccp(pos.x + (8.0f * scale),  pos.y - (3.5f * scale)),
    };
    IndicatorVars::triggerExtraDraw->drawPolygon(polygon, 3, col1, 0.45f * scale, col2);
}

void drawSpawnIndicator(CCPoint objPos, float scale, float zoom) {
    IndicatorVars::triggerExtraDraw->drawCircle(objPos, (25 * scale) / 2, emptyCCC4F, IndicatorVars::spawnIndicatorThickness / zoom, aquaCCC4F, 32);
}