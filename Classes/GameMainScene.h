#pragma once
//
//  GameMainScene.h
//  example12-1
//
//  Created by BaronYang on 19-9-22.
//

#ifndef example16_1_GameMainScene_h
#define example16_1_GameMainScene_h
#include "cocos2d.h"
#include "GameObjHero.h"
#include "GameObjMap.h"
#include "GameMark.h"

struct data
{
    int                 id;
    std::string         name;
    int                 level;
    std::string         Instruction;
    data() :id(0), level(0)
    {

    }
};
using namespace cocos2d;
class GameMain : public cocos2d::Layer
{
public:
    GameObjHero* hero;
    virtual bool init();
    bool isover;
    virtual void onEnter();
    virtual void onExit();
    void isherodrop();
    void setover();
    GameObjMap* map;
    GameMark* gamemark;
    Sprite* gameover;
    static Scene* createScene();
    void menuBackCallback(Ref* pSender);
    CREATE_FUNC(GameMain);
    void update(float time);
    void onEnterTransitionDidFinish();
    void onExitTransitionDidStart();
    bool isCollion(Point p1, Point p2, int w1, int h1, int w2, int h2);
    int LoadMapList(std::string filepath);
private:
    std::vector<data> _VecData;
    FileManager filemanager;
    Regx regx;
    int temp;
};


#endif
