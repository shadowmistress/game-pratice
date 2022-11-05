//
// GameMenuScene.cpp
// example12-1
//
// Created by Baron.Yang on 9-17-2022.

#include "GameMenuScene.h"
#include "GameAboutScene.h"
#include "cocostudio/SimpleAudioEngine.h"
#include "GameMainScene.h"
#include "PreLoadGame.h"
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

//Game init

bool GameMenu::init()
{
	if (!Layer::init())
	{
		return false;
	}
	audio->stopBackgroundMusic();
	Size size = Director::getInstance()->getVisibleSize();
	//background menu

	Sprite* bg = Sprite::createWithSpriteFrameName("MainMenu.png");
	bg->setScale(1.2);
	bg->setPosition(Vec2(size.width / 2, size.height / 2));
	this->addChild(bg, 0, 0);
	Sprite* run = Sprite::createWithSpriteFrameName("run.png");
	run->setScale(1.2);
	run->setPosition(Vec2(size.width / 2-240, size.height));
	this->addChild(run, 0, 0);
	Sprite* loli = Sprite::createWithSpriteFrameName("loli.png");
	loli->setScale(1.2);
	loli->setPosition(Vec2(size.width / 2 , size.height));
	this->addChild(loli, 0, 0);
	Sprite* run2 = Sprite::createWithSpriteFrameName("run.png");
	run2->setScale(1.2);
	run2->setPosition(Vec2(size.width / 2 + 240, size.height));
	this->addChild(run2, 0, 0);
	//Action create;
	auto mov1 = MoveBy::create(1.0,Vec2(0,-200));
	auto mov2 = MoveBy::create(1.0, Vec2(0, -200));
	auto mov3 = MoveBy::create(1.0, Vec2(0, -120));
	auto rotaTol = RotateTo::create(1,20);
	//Anime create for background.
	run->runAction(mov1);
	run2->runAction(Sequence::create(mov2, rotaTol, NULL));
	loli->runAction(mov3);
	//Start button create.
	auto newGameItem = MenuItemImage::create("button//newGameA.png", "button//newGameB.png",CC_CALLBACK_1(GameMenu::menuNewGameCallback, this));
	newGameItem->setScale(1);
	newGameItem->setPosition(Vec2(size.width / 2 + 40, size.height / 2));
	newGameItem->setEnabled(false);
	//Continue button create.
	auto continueItem = MenuItemImage::create("button//continueA.png", "button//continueB.png",CC_CALLBACK_1(GameMenu::menuNewGameCallback, this));
	continueItem->setScale(1);
	continueItem->setPosition(Vec2(size.width / 2 + 40, size.height / 2 - 60));
	continueItem->setEnabled(false);
	// About button create. 
	auto aboutItem = MenuItemImage::create("button//aboutA.png", "button//aboutB.png",CC_CALLBACK_1(GameMenu::menuAboutCallback, this));
	aboutItem->setScale(1);
	aboutItem->setPosition(Vec2(size.width / 2 + 40, size.height / 2 - 120));
	aboutItem->setEnabled(false);
	// sound button create. 
	soundItem = MenuItemImage::create("button//sound-on-A.png", "button//sound-on-B.png",CC_CALLBACK_1(GameMenu::menuSoundCallback, this));
	soundItem->setScale(1);
	soundItem->setPosition(Vec2(60, 60));
	soundItem->setEnabled(false);

	Menu* mainmenu = Menu::create(newGameItem, continueItem, aboutItem, soundItem, NULL);
	mainmenu->setPosition(Vec2(0, 0));
	this->addChild(mainmenu, 1, 3);

	issound = true;

	audio->playBackgroundMusic("Sound//background.ogg", true);
	return true;
}

//Jump to game main scene.
void GameMenu::menuNewGameCallback(Ref* pSender)
{
	Director::getInstance()->replaceScene(TransitionPageTurn::create(0.5, GameMain::createScene(), false));
}

void GameMenu::menuContinueCallback(Ref* pSender)
{

}
//Jump to about 
void GameMenu::menuAboutCallback(Ref* pSender)
{
	Director::getInstance()->replaceScene(TransitionPageTurn::create(0.5, GameAbout::createScene(), false));
}
// Sound control 
void GameMenu::menuSoundCallback(Ref* pSender)
{
	if (!issound) {
		soundItem->setNormalImage(Sprite::createWithSpriteFrameName("sound-on-A.png"));
		soundItem->setDisabledImage(Sprite::createWithSpriteFrameName("sound-on-B.png"));
		audio->playBackgroundMusic("background.ogg", true);
		issound = true;
	}
	else {
		soundItem->setNormalImage(Sprite::createWithSpriteFrameName("sound-off-A.png"));
		soundItem->setDisabledImage(Sprite::createWithSpriteFrameName("sound-off-B.png"));
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