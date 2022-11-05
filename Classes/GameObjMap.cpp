//
//  GameObjMap.cpp
//  example12-1
//
//  Created by Baron.Yang on 9-17-2022.

#include "GameObjMap.h"
#include "GameConst.h"
#include "GameObjStar.h"
#include "String.h"
#include "fstream"
/*constructor*/
GameObjMap::GameObjMap() {

}

/*destructor*/
GameObjMap::~GameObjMap()
{

}


/***********************************************************************
Name : onEnter()
Function : Get visiable size width and height,Load Map Background and road. 
Args:
return type : void.
************************************************************************/
void GameObjMap::onEnter()
{
    Node::onEnter();
    Size size = Director::getInstance()->getVisibleSize();
    _screen_width = size.width;
    _screen_height = size.height;
    map_count = 0;
    filepath = filemanager.getFileMapPath();
    LoadMapBackGroung();
    LoadMapRoad();

    this->scheduleUpdate();
}

/*node destory*/
void GameObjMap::onExit() {
    Node::onExit();
}


/***********************************************************************
Name : update()
Function : Execute this function model per fps update.
Args:
return type : void.
************************************************************************/
void GameObjMap::update(float dt)
{
    Sprite* bg1 = (Sprite*)this->getChildByTag(0);
    Sprite* bgi1 = (Sprite*)this->getChildByTag(1);
    Sprite* bg2 = (Sprite*)this->getChildByTag(2);
    Sprite* bgi2 = (Sprite*)this->getChildByTag(3);
    bg1->setPosition(bg1->getPositionX() - 4, bg1->getPositionY());
    bgi1->setPosition(bgi1->getPositionX()- 4,bgi1->getPositionY());
    bg2->setPosition(bg2->getPositionX() - 4, bg2->getPositionY());
    bgi2->setPosition(bgi2->getPositionX() - 4, bgi2->getPositionY());
    if (bg1->getPositionX() <= -_screen_width)
        bg1->setPosition(_screen_width   , _screen_height / 2);
    if (bg2->getPositionX() <= -_screen_width)
        bg2->setPosition(_screen_width   , _screen_height / 2);
    if (bgi1->getPositionX() <= -_screen_width) 
    {
        for (int i = 0; i < 5; i++)
        {
            stars1.at(i)->set_visable(true);
        }
        ReloadMap(bgi1);
        bgi1->setPosition(_screen_width , 0);
        map_count++;
    }
    if (bgi2->getPositionX() <= -_screen_width)
    {
        for (int i = 0; i < 5; i++)
        {
            stars2.at(i)->set_visable(true);
        }
        ReloadMap(bgi2);
        bgi2->setPosition(_screen_width , 0);
        map_count++;
    }
}


/***********************************************************************
Name : LoadMapBackGroung()
Function : Create backgroung sprite and star sprite. 
Args:
return type : int, value : 0(success) -1(fail)
************************************************************************/
int GameObjMap::LoadMapBackGroung()
{
    //Create backgroung.
    std::string bg1_name = regx.getJsonData(filepath, "background", 0, "Sprite1");
    std::string bgi1_name = regx.getJsonData(filepath, "background", 0, "Sprite2");
    this->setContentSize(Size(_screen_width,_screen_height));
    Sprite* bg1 = Sprite::createWithSpriteFrameName(bg1_name);
    Sprite* bgi1 = Sprite::createWithSpriteFrameName(bgi1_name);
    Sprite* bg2 = Sprite::createWithSpriteFrameName(bg1_name);
    Sprite* bgi2 = Sprite::createWithSpriteFrameName(bgi1_name);
    if (bg1 == nullptr || bgi1 == nullptr || bg2 == nullptr || bgi2 == nullptr)
    {
        log("error,sprite create error.");
        return -1;
    }
    bg1->setAnchorPoint(Vec2(0,0));
    bg1->setPosition(Vec2(0, _screen_height / 2));
    this->addChild(bg1,0, 0);
    bgi1->setAnchorPoint(Vec2(0, 0));
    bgi1->setPosition(Vec2(0, 0));
    this->addChild(bgi1, 1, 1);
    bg2->setAnchorPoint(Vec2(0, 0));
    bg2->setPosition(Vec2(_screen_width, _screen_height / 2));
    this->addChild(bg2,0, 2);
    bgi2->setAnchorPoint(Vec2(0, 0));
    bgi2->setPosition(Vec2(_screen_width, 0));
    this->addChild(bgi2, 0,3);
    //Create star.
    for (int i = 0; i < 5; i++)
    {
        GameObjStar* obj = new GameObjStar();
        if (obj == nullptr)
        {
            log("error,sprite create error.");
            return -1;
        }
        obj->setPosition(Vec2(172 + 192 * i, 100));
        stars1.pushBack(obj);
        bg1->addChild(obj, 2);
        obj = new GameObjStar();
        obj->setPosition(Vec2(172 + 192 * i, 100));
        stars2.pushBack(obj);
        bg2->addChild(obj, 2);
    }
    return 0;
}


/***********************************************************************
Name : LoadMapRoad()
Function : Load road sprite and plant sprite from map list and create it.
Args:
return type : int, value : 0(success) -1(fail)
************************************************************************/
int GameObjMap::LoadMapRoad()
{
    int result = 0;
    Sprite* bgi1 = (Sprite*)this->getChildByTag(1);
    Sprite* bgi2 = (Sprite*)this->getChildByTag(3);
    for (int i = 0; i < road_list_init_i.size(); i++)
    {
        int R_i = road_list_init_i[i];
        int P_i = plant_list_init_i[i];
        if (R_i != -1)
        {
            if (i < 8)
            {
                result =CreateRoad(bgi1, R_i,i);
                if(P_i != -1)
                    CreatePlant(bgi1, P_i, i);
            }
            else
            {
                result =CreateRoad(bgi2, R_i, (i - 8));
                if(P_i != -1)
                    result = CreatePlant(bgi2, P_i, i - 8);
            }
        }
    }
    return result;
}


/***********************************************************************
Name : ReloadMap()
Function : Reload road sprite and plant sprite from json map list.
Args: 
    Sprite* bg : background sprite. 
return type : int, value : 0(success) -1(fail)
************************************************************************/
int GameObjMap::ReloadMap(Sprite* bg)
{
    int result = 0;
    if (road_list_i.size() / 8 <= map_count)
    {
        log("index over!!!!!!!!!!!!!!!!!!!");
        return -1;
    }
    
    bg->removeAllChildren();
    for (int i = 0; i < 8; i++)
    {
        if (road_list_i[i + 8 * map_count] != -1)
        {
            result = CreateRoad(bg, road_list_i[i + 8 * map_count], i);
            if((plant_list_i[i + 8 * map_count] != -1) && (road_list_i[i + 8 * map_count] != 3) && (road_list_i[i + 8 * map_count] != 4))
                result = CreatePlant(bg, plant_list_i[i + 8 * map_count], i);
        }
    }
    return result;
}


/***********************************************************************
Name : CreateRoad()
Function : Create road sprite from json map list.
Args:
    Sprite* bg : background sprite.
    int mod : Select create road model for map.json 
    int pos : Create road pos on screen.
return type : int, value : 0(success) -1(fail)
************************************************************************/
int GameObjMap::CreateRoad(Sprite* bg, int mod, int pos)
{
    //road
    Sprite* road = Sprite::createWithSpriteFrameName(regx.getJsonData(filepath, "road", mod, "Sprite1"));
    std::string Sprite2 = regx.getJsonData(filepath, "road", mod, "Sprite2");
    if (road == nullptr)
    {
        log("CreateRoad error");
        return -1;
    }
    road->setContentSize(Size(128, 128));
    road->setAnchorPoint(Vec2(0, 0));
    road->setPosition(128 * pos, 130);
    road->setFlippedX(atoi(regx.getJsonData(filepath, "road", mod, "SetFix").c_str()));
    bg->addChild(road, 1);

    if (Sprite2 != std::string("error"))
    {
        Sprite* roadi = Sprite::createWithSpriteFrameName(regx.getJsonData(filepath, "road", mod, "Sprite2"));
        if (roadi == nullptr)
        {
            log("CreateRoad error");
            return -1;
        }
        roadi->setContentSize(Size(128, 128));
        roadi->setAnchorPoint(Vec2(0, 1));
        roadi->setFlippedX(atoi(regx.getJsonData(filepath, "road", mod, "SetFix").c_str()));
        roadi->setPosition(0, 0);
        road->addChild(roadi,1);
    }
    return 0;
}


/***********************************************************************
Name : CreatePlant()
Function : Create plant sprite from json map list.
Args:
    Sprite* bg : background sprite.
    int mod : Select create plant model for map.json
    int pos : Create plant pos on screen.
return type : int, value : 0(success) -1(fail)
************************************************************************/
int GameObjMap::CreatePlant(Sprite* bg, int mod, int pos)
{
    Sprite* plant = Sprite::createWithSpriteFrameName(regx.getJsonData(filepath, "plant", mod, "Sprite1"));
    if (plant == nullptr)
    {
        log("CreatePlant error");
        return -1;
    }
    plant->setAnchorPoint(Vec2(0, 0));
    plant->setPosition(128 * pos, 240);
    plant->setFlippedX(atoi(regx.getJsonData(filepath, "road", mod, "SetFix").c_str()));
    bg->addChild(plant, 1);
    return 0;
}