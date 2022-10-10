//
//  GameObjMap.h
//  example12-1
//
//  Created by BaronYang on 21-9-22.
//

#ifndef example16_1_GameObjStar_h
#define example16_1_GameObjStar_h
#include "cocos2d.h"
using namespace cocos2d;

class GameObjStar : public Node
{
public:
    GameObjStar(void);
    short state;
    virtual ~GameObjStar(void);
    virtual void onEnter();
    virtual void onExit();
    bool _visable;
    void set_visable(bool var);
    bool get_visable();
};

#endif