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
#include "Regx/regx.h"
#include "FileManager/FileManger.h"


using namespace cocos2d;

class GameObjMap : public Node
{
public:
    GameObjMap(void);
    short state;
    virtual ~GameObjMap(void);
    virtual void onEnter();
    virtual void onExit();
    int LoadMapBackGroung();
    int LoadMapRoad();
    int ReloadMap(Sprite* bg);
    int CreateRoad(Sprite* bg, int mod, int pos);
    int CreatePlant(Sprite* bg, int mod, int pos);
    void update(float dt);
    Vector<GameObjStar*> stars1;
    Vector<GameObjStar*> stars2;

private:
    int _screen_width;
    int _screen_height;
    FileManager filemanager;
    Regx regx;
    std::string filepath;
    std::vector<std::string> map_list;
    std::vector <int>  road_list;
    std::vector <int>  plant_list;
};


#endif