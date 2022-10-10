#pragma once

//
// GameMenuScene.h
// example12-1
//
// created by Baron.Yang on 9-17-2022
//

#ifndef example15_1_GameMenuScene_h
#define example15_1_GameMenuScene_h
#include "cocos2d.h"
using namespace cocos2d;
class GameMenu : public cocos2d::Layer
{
public:
	bool issound;

	MenuItemImage* soundItem;

	virtual bool init();

	virtual void onEnter();
	virtual void onExit();

	//static cocos2d::Scene* scene();
	static Scene* createScene();

	void menuEnter();

    void menuNewGameCallback(Ref* pSender);

    void menuContinueCallback(Ref* pSender);

    void menuAboutCallback(Ref* pSender);

	void menuSoundCallback(Ref* pSender);

    CREATE_FUNC(GameMenu);

    void onEnterTransitionDidFinish();

    void onExitTransitionDidStart();
};
#endif // !example15_1_GameMenuScene_h
