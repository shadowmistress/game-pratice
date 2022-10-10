//
//  GameAboutScene.cpp
// example12-1
//
// Created by Baron.Yang on 9-17-2022.
//

#include "GameAboutScene.h"
#include "GameMenuScene.h"

using namespace cocos2d;

Scene* GameAbout::createScene()
{
    auto scene = Scene::create();
    auto layer = GameAbout::create();
    scene->addChild(layer);
    return scene;
}
bool GameAbout::init()
{
    if (!Layer::init())
    {
        return false;
    }

    Size size = Director::getInstance()->getVisibleSize();

    Sprite* bg = Sprite::create("back_1.png");
    bg->setScale(1);
    bg->setPosition(Vec2(size.width / 2, size.height / 2));
    this->addChild(bg, 0, 0);
    Sprite* kuang = Sprite::create("tb.png");
    kuang->setScale(0.5f);
    kuang->setRotation(90);
    kuang->setPosition(Vec2(size.width / 2, size.height / 2));
    this->addChild(kuang, 2, 2);

    char inf[256];
    sprintf(inf, "name:loli run\n\n program:shuoquan man\n\n art design:zuyi li\n\n company:hz books\n\n    powered by cocos2D-x");
    // CCLabelTTF *myjineng = CCLabelTTF::create(inf,CCSizeMake(400,400),kCCTextAlignmentLeft, "Marker Felt", 20);
    auto myjineng = Label::createWithTTF(inf, "fonts/Marker Felt.ttf", 24);
    //auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    //myjineng->setAnchorPoint(Vec2(0, 1));
    myjineng->setColor(Color3B(0,0,0));
    myjineng->setPosition(Vec2(470, 380));
    myjineng->setAlignment(TextHAlignment::LEFT);
    this->addChild(myjineng);
    //关于标签
    Sprite* abouttitle = Sprite::create("about.png");
    abouttitle->setScale(0.5);
    abouttitle->setPosition(Vec2(size.width / 2, size.height - 20));
    this->addChild(abouttitle, 3, 3);
    //返回
    auto back = MenuItemImage::create("backA.png", "backB.png", CC_CALLBACK_1(GameAbout::menuBackCallback, this));
    back->setScale(1);
    back->setPosition(Vec2(size.width - 20, size.height - 20));
    //back->setEnabled(false);
    Menu* mainmenu = Menu::create(back, NULL);
    mainmenu->setPosition(Vec2::ZERO);
    this->addChild(mainmenu, 3, 4);
    return true;
}
void GameAbout::menuBackCallback(Ref* pSender) {
    //CCDirector::sharedDirector()->setDepthTest(true);
    Director::getInstance()->replaceScene(TransitionPageTurn::create(0.5, GameMenu::createScene(), true));
}

void GameAbout::onExit() {
    Layer::onExit();
}
void GameAbout::onEnter() {
    Layer::onEnter();
    Node* mainmenu = this->getChildByTag(4);
    Vector<Node*> temp = mainmenu->getChildren();
    MenuItemImage* a = (MenuItemImage*)temp.at(0);
    a->setEnabled(true);
}

void GameAbout::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
    //CCDirector::sharedDirector()->setDepthTest(false);
}

void GameAbout::onExitTransitionDidStart()
{
    Layer::onExitTransitionDidStart();
}