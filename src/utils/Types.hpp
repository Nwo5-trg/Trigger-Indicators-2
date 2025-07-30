#pragma once

// every so slightly more convenient than ccrect
struct CornerRect {
    cocos2d::CCPoint p1;
    cocos2d::CCPoint p2;

    CornerRect() = default;
    
    CornerRect(cocos2d::CCPoint c1, cocos2d::CCPoint c2) {
        p1 = c1; p2 = c2;
    }

    CornerRect& operator+=(cocos2d::CCPoint p) {
        p1 += p; p2 += p;
        return *this;
    }
};