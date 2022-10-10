
//
//  GameMark.h
//  example12-1
//
//  Created by BaronYang on 21-9-22.
//


#ifndef example15_1_GameMark_h
#define example15_1_GameMark_h

#include "cocos2d.h"
using namespace cocos2d;

class GameMark : public Node
{
public:
    GameMark(void);
    virtual ~GameMark(void);
    virtual void onEnter();
    virtual void onExit();
    Vector<Sprite*> bits;
    int mark;
    void addnumber(int var);
    Texture2D* ui;
};

#endif
