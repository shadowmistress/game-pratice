#pragma once
//
//  GameObjMap.h
//  example12-1
//
//  Created by Baron.Yang on 9-17-2022.
//

#ifndef example16_1_GameObjMap_h
#define example16_1_GameObjMap_h
#include "cocos2d.h"
#include "GameObjStar.h"
#include "regx.h"
using namespace cocos2d;

class GameObjMap : public Node
{
public:
    GameObjMap(void);
    short state;
    virtual ~GameObjMap(void);
    virtual void onEnter();
    virtual void onExit();
    void bgCreate();
    int LoadMap();
    void ChangeMap(int k,int count);
    void roadCreateBg1(int i,int k);
    void roadCreateBg2(int k);
    void roadmode1(int i,int k);
    void roadmode2(int i, int k);
    void roadmode3(int i, int k);
    void roadmode4(int i, int k);
    void roadmode5(int i, int k);
    void roadmode6(int i, int k);
    void roadmode7(int i, int k);
    void roadmode8(int i, int k);

    void update(float dt);
    Vector<Sprite*> bgMap;
    Vector<Sprite*> bg1MapList;
    Vector<Sprite*> roadMap1;
    Vector<Sprite*> roadMap2;
    Vector<GameObjStar*> stars1;
    Vector<GameObjStar*> stars2;
    std::string new_paths;
    Regx r1;
    std::vector<short> tbg1;
    std::vector<short> tbg2;

private:
    int timer;
    int count1;
    int count2;
    Sprite* bg1;
    Sprite* bg2;
};


#endif