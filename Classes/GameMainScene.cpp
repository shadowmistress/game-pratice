//
//  GameMainScene.cpp
//  example12-1
//
//   Created by BaronYang on 19-9-22.
//

#include "GameMainScene.h"
#include "GameMenuScene.h"
#include "GameObjMap.h"
#include "GameConst.h"
#include "GameObjStar.h"
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
    map = new GameObjMap();
    map->setAnchorPoint(Vec2(0, 1));
    map->setPosition(Vec2(0, size.height));
    addChild(map, 0);
    hero = new GameObjHero();
    hero->setScale(0.5f);
    hero->setPosition(Vec2(100, 260));
    addChild(hero, 1);
    gamemark = new GameMark();
    addChild(gamemark, 4);
    gameover = Sprite::create("gameover.png");
    gameover->setAnchorPoint(Vec2(0.5, 0.5));
    gameover->setPosition(Vec2(0, 0));
    gameover->setPosition(Vec2(size.width / 2, size.height / 2 + 70));
    gameover->setVisible(false);
    gameover->setScale(0.5);
    addChild(gameover, 5);
    MenuItemImage* pCloseItem = MenuItemImage::create("back.png", "back.png", CC_CALLBACK_1(GameMain::menuBackCallback,this));
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
void GameMain::isherodrop() {
    Point p1 = (map->getChildByTag(0))->getPosition();
    Point p2 = (map->getChildByTag(1))->getPosition();
    int temp;
    if ((int)p1.x <= 0 && (int)p1.x>= -1024)
    {
        temp = (-(p1.x + 10) / 128);
        //261
        if (bg1shu[temp + 1] == -1 && hero->getPositionY() < 262)
            hero->setState(2);
    }else
    {
        temp = (-(p2.x + 10) / 128);
        if (bg2shu[temp + 1] == -1 && hero->getPositionY() < 262)
            hero->setState(2);
    }
}
bool GameMain::isCollion(Point p1, Point p2, int w1, int h1, int w2, int h2) {
    if (abs(p1.x - p2.x) < w1 + w2 && abs(p1.y - p2.y) < h1 + h2) {
        return true;
    }
    return false;
};
void GameMain::update(float time) {
    if (hero->state == 0)
        isherodrop();
    Point p1 = (map->getChildByTag(0))->getPosition();
    Point p2 = (map->getChildByTag(1))->getPosition();
    for (int i = 0; i < 5; i++) {
        if ((int)p1.x <= 0 && (int)p1.x >= -1024) {
            GameObjStar* obj = (GameObjStar*)(map->stars1).at(i) ;
            if (obj->get_visable() && isCollion(Vec2(100, hero->getPosition().y - 200), Vec2((int)obj->getPosition().x + p1.x, 200), 40, 35, 18.25, 17.75)) {
                obj->set_visable(false);
                gamemark->addnumber(200);
            }
        }
        else {
            GameObjStar* obj = (GameObjStar*)(map->stars2).at(i);
            if (obj->get_visable() && isCollion(Vec2(100, hero->getPosition().y - 200), Vec2((int)obj->getPosition().x + p2.x, 200), 40, 35, 18.25, 17.75)) {
                obj->set_visable(false);
                gamemark->addnumber(200);
            }
        }
    }
}
void GameMain::menuBackCallback(Ref* pSender)
{
    Director::getInstance()->replaceScene(TransitionPageTurn::create(0.5,GameMenu::createScene(),true));
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
