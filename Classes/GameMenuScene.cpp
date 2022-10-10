//
// GameMenuScene.cpp
// example12-1
//
// Created by Baron.Yang on 9-17-2022.

#include "HelloWorldScene.h"
#include "GameMenuScene.h"
#include "GameAboutScene.h"
#include "cocostudio/SimpleAudioEngine.h"
#include "GameMainScene.h"
//#include ""
//#include ""
using namespace CocosDenshion;

auto audio = SimpleAudioEngine::getInstance();
Scene* GameMenu::createScene()
{
	auto scene = Scene::create();
	auto layer = GameMenu::create();
	scene->addChild(layer);
	return scene;
}

//游戏初始化

bool GameMenu::init()
{
	if (!Layer::init())
	{
		return false;
	}
	audio->stopBackgroundMusic();
	Size size = Director::getInstance()->getVisibleSize();
	//菜单背景
	Sprite* bg = Sprite::create("MainMenu.png");
	bg->setScale(1.2);
	bg->setPosition(Vec2(size.width / 2, size.height / 2));
	this->addChild(bg, 0, 0);
	//按钮
	// 
	//开始按钮
	auto newGameItem = MenuItemImage::create("newGameA.png", "newGameB.png",CC_CALLBACK_1(GameMenu::menuNewGameCallback, this));
	newGameItem->setScale(1);
	newGameItem->setPosition(Vec2(size.width / 2 + 40, size.height / 2));
	newGameItem->setEnabled(false);
	// 继续按钮
	auto continueItem = MenuItemImage::create("continueA.png", "continueB.png",CC_CALLBACK_1(GameMenu::menuNewGameCallback, this));
	continueItem->setScale(1);
	continueItem->setPosition(Vec2(size.width / 2 + 40, size.height / 2 - 60));
	continueItem->setEnabled(false);
	// 关于按钮
	auto aboutItem = MenuItemImage::create("aboutA.png", "aboutB.png",CC_CALLBACK_1(GameMenu::menuAboutCallback, this));
	aboutItem->setScale(1);
	aboutItem->setPosition(Vec2(size.width / 2 + 40, size.height / 2 - 120));
	aboutItem->setEnabled(false);
	//声音按钮
	soundItem = MenuItemImage::create("sound-on-A.png", "sound-on-B.png",CC_CALLBACK_1(GameMenu::menuSoundCallback, this));
	soundItem->setScale(1);
	soundItem->setPosition(Vec2(60, 60));
	soundItem->setEnabled(false);

	Menu* mainmenu = Menu::create(newGameItem, continueItem, aboutItem, soundItem, NULL);
	mainmenu->setPosition(Vec2(0, 0));
	this->addChild(mainmenu, 1, 3);

	issound = true;
	//初始化声音

	audio->playBackgroundMusic("background.mp3", true);
	return true;
}


void GameMenu::menuNewGameCallback(Ref* pSender)
{
	log("123456");
	/*Director::getInstance()->setDepthTest();*/
	Director::getInstance()->replaceScene(TransitionPageTurn::create(0.5,GameMain::createScene(), false));

}

void GameMenu::menuContinueCallback(Ref* pSender)
{

}

void GameMenu::menuAboutCallback(Ref* pSender)
{
	/*Director::getInstance()->setDepthTest();*/
	//Director::getInstance()->replaceScene( HelloWorld::createScene());
	Director::getInstance()->replaceScene(TransitionPageTurn::create(0.5, GameAbout::createScene(), false));
}

void GameMenu::menuSoundCallback(Ref* pSender)
{
	//设置声音
	if (!issound) {
		soundItem->setNormalImage(Sprite::create("sound-on-A.png"));
		soundItem->setDisabledImage(Sprite::create("sound-on-B.png"));
		audio->playBackgroundMusic("background.mp3", true);
		issound = true;
	}
	else {
		soundItem->setNormalImage(Sprite::create("sound-off-A.png"));
		soundItem->setDisabledImage(Sprite::create("sound-off-B.png"));
		audio->stopBackgroundMusic();
		issound = false;
	}
}

void GameMenu::onExit() {
	Layer::onExit();
}
void GameMenu::onEnter() {
	Layer::onEnter();
	Size size = Director::getInstance()->getVisibleSize();
	Node* mainmenu = this->getChildByTag(3);
	mainmenu->setScale(0);
	mainmenu->runAction(Sequence::create(ScaleTo::create(0.5, 1),CallFunc::create(CC_CALLBACK_0(GameMenu::menuEnter,this)),NULL));
}void GameMenu::menuEnter() {
	Node* mainmenu = this->getChildByTag(3);
	Vector<Node*> temp = mainmenu->getChildren();

	for (int i = 0; i < (int)(temp.size()); i++) {
		MenuItemImage* a = (MenuItemImage*)temp.at(i);
		a->setEnabled(true);
	}
}

void GameMenu::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	//CCDirector::sharedDirector()->setDepthTest(false);
}

void GameMenu::onExitTransitionDidStart()
{
	Layer::onExitTransitionDidStart();
}