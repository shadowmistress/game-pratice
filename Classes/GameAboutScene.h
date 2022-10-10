//#pragma once
//#pragma once
//
////
// GameAboutScene.h
// example12-1
//
// Created by Baron.Yang on 9-17-2022.
//

#ifndef example15_1_GameAboutScene_h
#define example15_1_GameAboutScene_h
#include "cocos2d.h"
using namespace cocos2d;
class GameAbout : public cocos2d::Layer
{
public:

	virtual bool init();

	virtual void onEnter();
	virtual void onExit();

	static Scene* createScene();

	void menuBackCallback(Ref* pSender);

	CREATE_FUNC(GameAbout);

	void onEnterTransitionDidFinish();

	void onExitTransitionDidStart();
};
#endif
