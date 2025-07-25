#pragma once

// idk this is prolly better than misusing ccrect
struct CornerRect {
    cocos2d::CCPoint p1;
    cocos2d::CCPoint p2;

    CornerRect() = default;
    
    CornerRect(cocos2d::CCPoint c1, cocos2d::CCPoint c2) {
        p1 = c1; p2 = c2;
    }
};