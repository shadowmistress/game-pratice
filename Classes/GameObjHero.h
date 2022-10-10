//
//  GameObjHero.h
//  example12-1
//
//  Created by BaronYang on 21-9-22.
//

#ifndef example15_1_GameObjHero_h
#define example15_1_GameObjHero_h
#include "cocos2d.h"
using namespace cocos2d;

class GameObjHero : public Node
{
public:
    Sprite* mainsprite;
    Texture2D* hurt;
    Texture2D* jump;
    Point offset;
    short state;//0:’˝≥£ 1£∫Ã¯‘æ 2£∫ ‹…À
    bool iscontrol;
    GameObjHero(void);
    virtual ~GameObjHero(void);
    void setState(short var);
    Rect rect();
    virtual void onEnter();
    virtual void onExit();
    void jumpend();
    void hurtend();
    //bool containsTouchLocation(CCTouch* touch);
    virtual bool TouchBegan(Touch* touch, Event* event);
    virtual void TouchMoved(Touch* touch, Event* event);
    virtual void TouchEnded(Touch* touch, Event* event);
    virtual bool onKeyPressed(EventKeyboard::KeyCode keycode, Event* event);
    virtual void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);

};


#endif
