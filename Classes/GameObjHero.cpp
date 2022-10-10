//
//  GameObjHero.cpp
// 
//  example12-1
//
//  Created by BaronYang on 21-9-22.
//
#include "GameObjHero.h"
#include "GameMainScene.h"
GameObjHero::GameObjHero(void)
{
}

GameObjHero::~GameObjHero(void)
{
}
Rect GameObjHero::rect()
{
    Size s = Size(100, 125);
    return Rect(-s.width / 2, -s.height / 2, s.width, s.height);
}

void GameObjHero::onEnter()
{
    Node::onEnter();
    auto listener1 = EventListenerTouchOneByOne::create();
    /*auto* dispatcher = Director::getInstance()->getEventDispatcher();*/
    auto* keyListener = EventListenerKeyboard::create();
    keyListener->onKeyPressed = CC_CALLBACK_2(GameObjHero::onKeyPressed, this);
    keyListener->onKeyReleased = CC_CALLBACK_2(GameObjHero::onKeyReleased, this);
    //dispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);
    listener1->onTouchBegan = CC_CALLBACK_2(GameObjHero::TouchBegan,this);
    listener1->onTouchMoved = CC_CALLBACK_2(GameObjHero::TouchMoved, this);
    listener1->onTouchEnded = CC_CALLBACK_2(GameObjHero::TouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1,this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);
    this->setContentSize(Size(85, 90));

    Sprite* obj = Sprite::create("s_hurt.png");
    hurt = obj->getTexture();
    obj = Sprite::create("s_jump.png");
    jump = obj->getTexture();
    mainsprite = Sprite::create("s_1.png");
    ////动画
    Animation* animation = Animation::create();
    animation->addSpriteFrameWithFile("s_1.png");
    animation->addSpriteFrameWithFile("s_2.png");
    animation->addSpriteFrameWithFile("s_3.png");
    animation->addSpriteFrameWithFile("s_4.png");
    animation->addSpriteFrameWithFile("s_5.png");
    animation->addSpriteFrameWithFile("s_6.png");
    animation->setDelayPerUnit(0.1f);
    animation->setRestoreOriginalFrame(true);
    ////运行奔跑动画
    mainsprite->runAction(RepeatForever::create(Animate::create(animation)));
    state = 0;
    addChild(mainsprite);
}
void GameObjHero::setState(short var) {
    if (state == var)
        return;
    state = var;
    switch (state) {
    case 1://跳跃
        this->stopAllActions();
        mainsprite->stopAllActions();
        mainsprite->setTexture(jump);
        this->runAction(Sequence::create(JumpBy::create(1.5, Vec2(0, 0), 150, 1), CallFunc::create(CC_CALLBACK_0(GameObjHero::jumpend,this)), NULL));
        break;
    case 2://受伤
        this->stopAllActions();
        mainsprite->stopAllActions();
        mainsprite->setTexture(hurt);
        /*this->runAction(Blink::create(3, 10));*/
        this->runAction(Sequence::create(MoveBy ::create(1.0f,Vec2(0,-500)), CallFunc::create(CC_CALLBACK_0(GameObjHero::hurtend, this)), NULL));
        ((GameMain*)this->getParent())->setover();
        break;
    case 0://奔跑动画
        this->stopAllActions();
        mainsprite->stopAllActions();
        Animation* animation = Animation::create();
        animation->addSpriteFrameWithFile("s_1.png");
        animation->addSpriteFrameWithFile("s_2.png");
        animation->addSpriteFrameWithFile("s_3.png");
        animation->addSpriteFrameWithFile("s_4.png");
        animation->addSpriteFrameWithFile("s_5.png");
        animation->addSpriteFrameWithFile("s_6.png");
        animation->setDelayPerUnit(0.1f);
        animation->setRestoreOriginalFrame(true);
        mainsprite->runAction(RepeatForever::create(Animate::create(animation)));
        break;
    }
}
void GameObjHero::jumpend() {
    setState(0);
}
void GameObjHero::hurtend() {
    setState(2);
}
void GameObjHero::onExit()
{
    /*_eventDispatcher->removeAllEventListeners();*/
    Node::onExit();
}
//bool GameObjHero::containsTouchLocation(CCTouch* touch)
//{
//    //return CCRect::CCRectContainsPoint(rect(), convertTouchToNodeSpaceAR(touch));
//    return rect().containsPoint(convertTouchToNodeSpaceAR(touch));
//}
bool GameObjHero::TouchBegan(Touch* touch, Event* event)
{
    log("touch event start!!!!!!!!!!!!!");
    if (((GameMain*)this->getParent())->isover)
        return false;
    //设置运动状态
    setState(1);
    return true;
}
void GameObjHero::TouchMoved(Touch* touch, Event* event)
{
}
void GameObjHero::TouchEnded(Touch* touch, Event* event)
{
}
bool GameObjHero::onKeyPressed(EventKeyboard::KeyCode keycode, Event* event)
{
    if (keycode == EventKeyboard::KeyCode::KEY_SPACE) {
        if (((GameMain*)this->getParent())->isover)
            return false;
        //设置运动状态
        setState(1);
        return true;
    }
    return false;
}
void GameObjHero::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event) 
{

}