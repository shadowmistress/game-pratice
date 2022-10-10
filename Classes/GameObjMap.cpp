//
//  GameObjMap.cpp
//  example12-1
//
//  Created by Baron.Yang on 9-17-2022.

#include "GameObjMap.h"
#include "GameConst.h"
#include "GameObjStar.h"
#include "String.h"
//#include "json/rapidjson.h"
//#include "json/document.h"
#include "fstream"
/*deal with log function which not print string type */
static int log_string(const std::string tmp_string)
{
    char tmp[1024];
    memset(tmp, 0, 1024);
    for (int i = 0; i < tmp_string.size(); i++)
    {
        tmp[i] = tmp_string[i];
    }
    log("%s", tmp);
    return 0;
}

/*constructor*/
GameObjMap::GameObjMap() {

}

/*destructor*/
GameObjMap::~GameObjMap()
{

}

/*layer init create background scene*/
void GameObjMap::onEnter()
{
    Node::onEnter();
    timer = 0;
    count1 = 0;
    count2 = 0;
    this->scheduleUpdate();
    std::string paths = (FileUtils::getInstance()->getSearchPaths().at(0));
    std::vector<std::string> v1 = r1.split(paths,"/");
    new_paths = "";
    for (int i = 0;i<v1.size()-2;i++)
        new_paths = new_paths + v1.at(i).append("//");
    LoadMap();
    bgCreate();
    roadCreateBg1(0, 0);
    roadCreateBg2(1);
    for (int i = 0; i < 5; i++) {
        GameObjStar* obj = new GameObjStar();
        obj->setPosition(Vec2(172 + 192 * i, 200));
        stars1.pushBack(obj);
        bg1->addChild(obj, 3);
        obj = new GameObjStar();
        obj->setPosition(Vec2(172 + 192 * i, 200));
        stars2.pushBack(obj);
        bg2->addChild(obj, 3);
    }
}

/*node destory*/
void GameObjMap::onExit() {
    Node::onExit();
}


void GameObjMap::bgCreate() 
{
    Size size = Director::getInstance()->getVisibleSize();
    this->setContentSize(Size(1024, 768));
    bg1 = Sprite::create("back_1.png");
    bg1->setScale(1);
    bg1->setAnchorPoint(Vec2(0, 1));
    bg1->getTexture()->setAliasTexParameters();
    bg1->setPosition(Vec2(0, size.height));
    this->addChild(bg1, 0, 0);
    Sprite* bgdi1 = Sprite::create("back_5.png");
    bgdi1->setAnchorPoint(Vec2(0, 0));
    bgdi1->setPosition(Vec2(0, size.height / 2 - 650));
    bg1->addChild(bgdi1, 1);
    bg2 = Sprite::create("back_1.png");
    bg2->setScale(1);
    bg2->setAnchorPoint(Vec2(0, 1));
    bg2->getTexture()->setAliasTexParameters();
    bg2->setPosition(Vec2(size.width, size.height));
    this->addChild(bg2, 0, 1);
    Sprite* bgdi2 = Sprite::create("back_5.png");
    bgdi2->setAnchorPoint(Vec2(0, 0));
    bgdi2->setPosition(Vec2(0, size.height / 2 - 650));
    bg2->addChild(bgdi2, 1);
    bgMap.pushBack(bg1);
    bgMap.pushBack(bg2);
}

void GameObjMap::roadCreateBg1(int i,int k)
{
    int m = i;
    for (int i = 0; i < 8; i++)
    {
        if (bg1shu[i] != -1){
            /*log("test break id%d",bg1shu[i]);*/
            switch (bg1shu[i])
            {
            case 0:
                roadmode1(i + m,0);
                break;
            case 1:
                roadmode2(i + m,0);
                break;
            case 2:
                roadmode3(i + m,0);
                break;
            case 3:
                roadmode4(i + m,0);
                break;
            case 4:
                roadmode5(i + m,0);
                break;
            case 5:
                roadmode6(i + m,0);
                break;
            case 6:
                roadmode7(i + m,0);
                break;
            case 7:
                roadmode8(i + m,0);
                break;
                default:
                    break;
                }
            }
    }
}
void GameObjMap::roadCreateBg2(int k)
{
    for (int i = 0; i < 8; i++)
    {
        if (bg2shu[i] != -1) {
            /*log("test break id%d", bg2shu[i]);*/
            switch (bg2shu[i])
            {
            case 0:
                roadmode1(i + 8,1);
                break;
            case 1:
                roadmode2(i + 8,1);
                break;
            case 2:
                roadmode3(i + 8,1);
                break;
            case 3:
                roadmode4(i + 8,1);
                break;
            case 4:
                roadmode5(i + 8,1);
                break;
            case 5:
                roadmode6(i + 8,1);
                break;
            case 6:
                roadmode7(i + 8,1);
                break;
            case 7:
                roadmode8(i + 8,1);
                break;
            default:
                break;
            }
        }
    }
}

void GameObjMap::roadmode1(int i,int k) 
{
    Sprite* plant = Sprite::create("back_2.png");
    plant->setAnchorPoint(Vec2(0.5, 0));
   //117
    plant->setPosition(Vec2(128 * i + 64, 200));
    this -> addChild(plant, 1);
    Sprite* road = Sprite::create("road_2.png");
    road->setAnchorPoint(Vec2(0, 0));
    road->setPosition(Vec2(128 * i, 120));
    Sprite* roaddi = Sprite::create("road_3.png");
    roaddi->setAnchorPoint(Vec2(0, 1));
    roaddi->setPosition(Vec2(0 , 0));
    road->addChild(roaddi);
    this->addChild(road);
    if (k == 0)
    {
        roadMap1.pushBack(plant);
        roadMap1.pushBack(road);
    }
    else
    {
        roadMap2.pushBack(plant);
        roadMap2.pushBack(road);

    }
}
void GameObjMap::roadmode2(int i, int k)
{
    Sprite* road = Sprite::create("road_1.png");
    road->setAnchorPoint(Vec2(0, 0));
    road->setPosition(Vec2(26 + 128 * i, 120));
    Sprite* roaddi = Sprite::create("road_4.png");
    roaddi->setAnchorPoint(Vec2(0, 1));
    roaddi->setPosition(Vec2(0, 0));
    road->addChild(roaddi);
    this->addChild(road);
    if (k == 0)
    {
        roadMap1.pushBack(road);
    }
    else
    {
        roadMap2.pushBack(road);

    }
}
void GameObjMap::roadmode3(int i, int k)
{
    Sprite* plant = Sprite::create("enemy.png");
    plant->setAnchorPoint(Vec2(0.5, 0));
    plant->setPosition(Vec2(128 * i + 64, 210));
    this->addChild(plant, 2);
    Sprite* road = Sprite::create("road_1.png");
    road->setFlippedX(true);
    road->setAnchorPoint(Vec2(0, 0));
    road->setPosition(Vec2(128 * i, 120));
    Sprite* roaddi = Sprite::create("road_4.png");
    roaddi->setFlippedX(true);
    roaddi->setAnchorPoint(Vec2(0, 1));
    roaddi->setPosition(Vec2(0, 0));
    road->addChild(roaddi);
    this->addChild(road, 1);
    if (k == 0)
    {
        roadMap1.pushBack(plant);
        roadMap1.pushBack(road);
    }
    else
    {
        roadMap2.pushBack(plant);
        roadMap2.pushBack(road);

    }
}
void GameObjMap::roadmode4(int i, int k)
{
    Sprite* road = Sprite::create("road_5.png");
    road->setAnchorPoint(Vec2(0, 0));
    road->setPosition(Vec2(128 * i, 120));
    this->addChild(road);
    if (k == 0)
    {
        roadMap1.pushBack(road);
    }
    else
    {
        roadMap2.pushBack(road);
    }
}

void GameObjMap::roadmode5(int i, int k)
{
    Sprite*  road1 = Sprite::create("road_2.png");
    road1->setAnchorPoint(Vec2(0, 0));
    road1->setPosition(Vec2(128 * i, 120));
    Sprite* roaddi = Sprite::create("road_3.png");
    roaddi->setAnchorPoint(Vec2(0, 1));
    roaddi->setPosition(Vec2(0,0));
    road1->addChild(roaddi);
    this->addChild(road1, 1);
    if (k == 0)
    {
        roadMap1.pushBack(road1);
    }
    else
    {
        roadMap2.pushBack(road1);

    }
}
void GameObjMap::roadmode6(int i, int k)
{
    Sprite* plant = Sprite::create("back_3.png");
    plant->setAnchorPoint(Vec2(0.5, 0));
    plant->setPosition(Vec2(128 * i + 128, 230));
    this->addChild(plant, 1);
    Sprite* road1 = Sprite::create("road_1.png");
    road1->setAnchorPoint(Vec2(0, 0));
    road1->setPosition(Vec2(26 + 128 * i, 120));
    Sprite* roaddi = Sprite::create("road_4.png");
    roaddi->setAnchorPoint(Vec2(0, 1));
    roaddi->setPosition(Vec2(0, 0));
    road1->addChild(roaddi);
    this->addChild(road1, 1);
    if (k == 0)
    {
        roadMap1.pushBack(road1);
        roadMap1.pushBack(plant);
    }
    else
    {
        roadMap2.pushBack(road1);
        roadMap2.pushBack(plant);

    }
}
void GameObjMap::roadmode7(int i, int k)
{
    Sprite* road1 = Sprite::create("road_1.png");
    road1->setFlippedX(true);
    road1->setAnchorPoint(Vec2(0, 0));
    road1->setPosition(Vec2(128 * i, 120));
    Sprite* roaddi = Sprite::create("road_4.png");
    roaddi->setFlippedX(true);
    roaddi->setAnchorPoint(Vec2(0, 1));
    roaddi->setPosition(Vec2(0, 0));
    road1->addChild(roaddi);
    this->addChild(road1, 1);
    if (k == 0)
    {
        roadMap1.pushBack(road1);
    }
    else
    {
        roadMap2.pushBack(road1);
    }
}
void GameObjMap::roadmode8(int i, int k)
{
    Sprite* road1 = Sprite::create("road_5.png");
    road1->setAnchorPoint(Vec2(0, 0));
    road1->setPosition(Vec2(128 * i, 120));
    road1->setFlippedX(true);
    this->addChild(road1);
    if (k == 0)
    {
        roadMap1.pushBack(road1);
    }
    else
    {
        roadMap2.pushBack(road1);
    }
}




void GameObjMap::update(float dt)
{
    if(timer++ % 1 == 0)
    {
        timer = 1;
        if (bgMap.at(0)->getPositionX() <= -1024)
        {
            Size size = Director::getInstance()->getVisibleSize();
            bgMap.at(0)->setPosition(size.width, size.height);
            roadMap1.clear();
            if (count1 < tbg1.size() / 8)
            {
                for (int i = 0; i < 8; i++) {
                    bg1shu[i] = tbg1.at(i + 8 * count1);
                    log("shu:%d",bg1shu[i]);
                }
   
                count1++;
            }
            roadCreateBg1(8,0);

            for (int i = 0; i < 5; i++) 
            {
                stars1.at(i)->set_visable(true);
            }
        }
        if (bgMap.at(1)->getPositionX() <= -1024)
        {
            Size size = Director::getInstance()->getVisibleSize();
            bgMap.at(1)->setPosition(size.width, size.height);
            roadMap2.clear();
            if (count2 < tbg2.size() / 8)
            {
                for (int i = 0; i < 8; i++) {
                    bg2shu[i] = tbg2.at(i + 8 * count2);
                    log("shu2:%d", bg2shu[i]);
                }
              
                count2++;
            }
            roadCreateBg2(1);
            for (int i = 0; i < 5; i++)
            {
                stars2.at(i)->set_visable(true);
            }
        }
        bgMap.at(0)->setPosition(bgMap.at(0)->getPositionX() - 4,bgMap.at(0)->getPositionY());
        bgMap.at(1)->setPosition(bgMap.at(1)->getPositionX() - 4, bgMap.at(1)->getPositionY());
        for (int i = 0; i < roadMap1.size(); i++)
        {
            roadMap1.at(i)->setPosition(roadMap1.at(i)->getPositionX() - 4, roadMap1.at(i)->getPositionY());
        }
        for (int i = 0; i < roadMap2.size(); i++)
        {
            roadMap2.at(i)->setPosition(roadMap2.at(i)->getPositionX() - 4, roadMap2.at(i)->getPositionY());
        }
    }
}

int GameObjMap::LoadMap()
{
    std::ifstream infile;
    std::string mapPath = new_paths.append("Map//map.txt");
    infile.open(mapPath, std::ios::in);
    if (infile.is_open() == false)
    {	// 文件打开失败
        log("open file fail");
        return -1;
    }
    std::string s;
    while (getline(infile, s))
    {
        std::vector<std::string> map = r1.split(s, ";");
        log_string(map[0]);
        log_string(map[1]);
        std::vector<std::string> map1 = r1.split(map[0], ",");
        for (int i = 0; i < map1.size(); i++)
            tbg1.push_back((short)atoi(map1[i].c_str()));
        std::vector<std::string> map2 = r1.split(map[1], ",");
        for (int i = 0; i < map2.size(); i++)
            tbg2.push_back((short)atoi(map2[i].c_str()));
    }
    infile.close();
    return 0;
}
void GameObjMap::ChangeMap(int k,int count)
{

}