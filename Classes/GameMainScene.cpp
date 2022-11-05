//
//  GameMainScene.cpp
//  example12-1
//
//   Created by BaronYang on 19-9-22.
//

#include "GameMainScene.h"
#include "GameMenuScene.h"
#include "GameConst.h"
#include "GameObjStar.h"
#include "json/rapidjson.h"
#include "json/document.h"

using namespace cocos2d;

Scene* GameMain::createScene()
{
    Scene* scene = Scene::create();

    GameMain* layer = GameMain::create();

    scene->addChild(layer);

    return scene;
}
bool GameMain::init()
{
    if (!Layer::init())
    {
        return false;
    }

    Size size = Director::getInstance()->getVisibleSize();
    if (LoadMapList(filemanager.getFileMapPath()) == -1)
        return false;
    temp = 0;
    map = new GameObjMap();
    map->setAnchorPoint(Vec2(0, 0));
    map->setPosition(Vec2(0, 0));
    addChild(map, 0);
    hero = new GameObjHero();
    hero->setScale(0.5f);
    hero->setPosition(Vec2(100, 280));
    addChild(hero, 1);
    gamemark = new GameMark();
    addChild(gamemark, 4);
    gameover = Sprite::createWithSpriteFrameName("gameover.png");
    gameover->setAnchorPoint(Vec2(0.5, 0.5));
    gameover->setPosition(Vec2(0, 0));
    gameover->setPosition(Vec2(size.width / 2, size.height / 2 + 70));
    gameover->setVisible(false);
    gameover->setScale(0.5);
    addChild(gameover, 5);
    MenuItemImage* pCloseItem = MenuItemImage::create("button//back.png", "button//back.png", CC_CALLBACK_1(GameMain::menuBackCallback,this));
    pCloseItem->setPosition(Vec2(size.width / 2, size.height / 2 - 50));
    pCloseItem->setScale(0.5);
    Menu* pMenu = Menu::create(pCloseItem, NULL);
    pMenu->setPosition(Vec2::ZERO);
    this->addChild(pMenu, 5, 25);
    pMenu->setVisible(false);
    pMenu->setEnabled(false);
    isover = false;
    scheduleUpdate();
    return true;
}


/***********************************************************************
Name : setover()
Function : Set game over state.
Args:
return type : void.
************************************************************************/
void GameMain::setover() {
    Menu* pMenu = (Menu*)this->getChildByTag(25);
    pMenu->setVisible(true);
    pMenu->setEnabled(true);
    gameover->setVisible(true);
    gameover->setScale(0);
    pMenu->setScale(0);
    pMenu->runAction(ScaleTo::create(0.5, 1));
    gameover->runAction(ScaleTo::create(0.5, 0.5));
    isover = true;
}


/***********************************************************************
Name : isherodrop()
Function : Check hero position,if hero position on vector road_All_list_i
           vaule is -1,hero is dead.
Args:
return type : void.
************************************************************************/
void GameMain::isherodrop() {
    Point p1 = (map->getChildByTag(1))->getPosition();
    Point p2 = (map->getChildByTag(3))->getPosition();
    if (temp < road_All_list_i.size())
    {
        if ((int)p1.x <= 0 && (int)p1.x >= -1024)
        {
            int count = -((int)p1.x-110) / 128;
            temp = count + map_count * 8;
            if (road_All_list_i[temp] == -1 && hero->getPositionY() >=280)
                hero->setState(2);
        }
        if ((int)p2.x <= 0 && (int)p2.x >= -1024)
        {
            int count = -((int)p2.x-110) / 128;
            temp = count + map_count * 8;
            if (road_All_list_i[temp] == -1 && hero->getPositionY() >= 280)
                hero->setState(2);
        }
    }
    else
    {
        log("map over");
    }
}


/***********************************************************************
Name : isCollion()
Function : Collision detection, judged between sprite1 and sprite2 position
           is contact.
Args:
    Point p1 : The x axis and y axis distance from Screen to sprite1 node .
    Point p2 : The x axis and y axis distance from Screen to sprite2 node .
    int w1 : Draw rect x axis on node sprite1
    int h1 : Draw rect y axis on node sprite1
    int w2 : Draw rect x axis on node sprite2
    int h2 : Draw rect y axis on node sprite2
return type : bool, value : true(sprite1 and sprite2 is contact)
                            ,-1(sprite1 and sprite2 is not contact);
************************************************************************/
bool GameMain::isCollion(Point p1, Point p2, int w1, int h1, int w2, int h2) {
    if (abs(p1.x - p2.x) < w1 + w2 && abs(p1.y - p2.y) < h1 + h2) {
        return true;
    }
    return false;
};


/***********************************************************************
Name : update()
Function : Execute this function model per fps update.
Args: 
return type : void.
************************************************************************/
void GameMain::update(float time) {
    if (hero->state == 0)
        isherodrop();
    Point p1 = (map->getChildByTag(0))->getPosition();
    Point p2 = (map->getChildByTag(2))->getPosition();
    for (int i = 0; i < 5; i++) 
    {
        if ((int)p1.x <= 0 && (int)p1.x >= -1024) {
            GameObjStar* obj = (GameObjStar*)(map->stars1).at(i);
            if (obj->get_visable() && isCollion(Vec2(110, hero->getPosition().y - 300), Vec2((int)obj->getPosition().x + p1.x, 200), 40, 35, 18.25, 17.75)) {
                obj->set_visable(false);
                gamemark->addnumber(200);
            }
        }else if((int)p2.x <= 0 && (int)p2.x >= -1024)
        {
            GameObjStar* obj = (GameObjStar*)(map->stars2).at(i);
            if (obj->get_visable() && isCollion(Vec2(110, hero->getPosition().y - 300), Vec2((int)obj->getPosition().x + p2.x, 200), 40, 35, 18.25, 17.75)) {
                obj->set_visable(false);
                gamemark->addnumber(200);
            }
        }
    }
}


/***********************************************************************
Name : menuBackCallback()
Function :Clear Vector,reset map_conut on GameConst. Replace GameMain scene to  GameMenu scene.
Args:
return type : void.
************************************************************************/
void GameMain::menuBackCallback(Ref* pSender)
{
     road_list_init_i.clear() ;
     plant_list_init_i.clear();
     road_list_i.clear();
     plant_list_i.clear();
     road_All_list_i.clear();
     plant_All_list_i.clear();
     map_count = 0;
    Director::getInstance()->replaceScene(TransitionPageTurn::create(0.5,GameMenu::createScene(),true));
}


/***********************************************************************
Name : LoadMapList()
Function : Read game data from json file and store on map_list
Args:
    String filepath : map.json file path. 
return type : int, value : 0(load map_list success),-1(load map_list fail);
************************************************************************/
int GameMain::LoadMapList(std::string filepath)
{
    log("start load map_list");

    std::string road_list_init = regx.getJsonData(filepath, "map_list", 0, "road_list_init");
    std::string plant_list_init = regx.getJsonData(filepath, "map_list", 0, "plant_list_init");
    std::string road_list = regx.getJsonData(filepath, "map_list", 0, "road_list");
    std::string plant_list = regx.getJsonData(filepath, "map_list", 0, "plant_list");

    std::vector <std::string>  road_list_init_s = regx.split(road_list_init, ",");
    std::vector <std::string>  plant_list_init_s = regx.split(plant_list_init, ",");
    std::vector <std::string>  road_list_s = regx.split(road_list, ",");
    std::vector <std::string>  plant_list_s = regx.split(plant_list, ",");

    if (road_list_init_s.size() != plant_list_init_s.size() || road_list_s.size() != plant_list_s.size())
    {
        log("erro maplist load");
        return -1;
    }
    for (int i = 0; i < road_list_init_s.size(); i++)
    {
        int tmp1 = atoi(road_list_init_s[i].c_str());
        int tmp2 = atoi(plant_list_init_s[i].c_str());
        road_list_init_i.push_back(tmp1);
        plant_list_init_i.push_back(tmp2);
        road_All_list_i.push_back(tmp1);
        plant_All_list_i.push_back(tmp2);
    }
    for (int i = 0; i < road_list_s.size(); i++)
    {
        int tmp1 = atoi(road_list_s[i].c_str());
        int tmp2 = atoi(plant_list_s[i].c_str());
        road_list_i.push_back(atoi(road_list_s[i].c_str()));
        plant_list_i.push_back(atoi(plant_list_s[i].c_str()));
        road_All_list_i.push_back(tmp1);
        plant_All_list_i.push_back(tmp2);
    }
    return 0;
}


void GameMain::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
}

void GameMain::onExitTransitionDidStart()
{
    Layer::onExitTransitionDidStart();
}
void GameMain::onExit() {
    Layer::onExit();
}
void GameMain::onEnter() {
    Layer::onEnter();
}