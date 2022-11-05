//
//  GameMark.cpp
//  example12-1
//
//  Created by BaronYang on 21-9-22.
//

#include "GameMark.h"
GameMark::GameMark(void)
{
}

GameMark::~GameMark(void)
{
}
void GameMark::onExit()
{
    bits.clear();
    Node::onExit();
}
void GameMark::onEnter()
{
    Node::onEnter();
    Size size = Director::getInstance()->getVisibleSize();
    this->setContentSize(size);
    Sprite* title = Sprite::createWithSpriteFrameName("score.png");
    title->setPosition(Vec2(size.width / 2 + 280, size.height - 15));
    addChild(title);
    for (int i = 0; i < 5; i++) {
        Sprite* shu = Sprite::create("mark//shu.png");
        ui = shu->getTexture();
        /*234 對應零的位置 每隔26數字減小*/
        shu->setTextureRect(Rect(234, 0, 26, 31));
        shu->setPosition(Vec2(size.width - 15 - i * 30, size.height - 15));
        bits.pushBack(shu);
        addChild(shu);
    }
    mark = 0;
}
void GameMark::addnumber(int var) {
    mark += var;
    int temp = mark % 10;
    if (temp > 0) {
        ((Sprite*)bits.at(0))->setTexture(ui);
        ((Sprite*)bits.at(0))->setTextureRect(Rect((temp - 1) * 26, 0, 26, 31));
    }
    else {
        ((Sprite*)bits.at(0))->setTexture(ui);
        ((Sprite*)bits.at(0))->setTextureRect(Rect(234, 0, 26, 31));
    }
    temp = (mark % 100) / 10;
    if (temp > 0) {
        ((Sprite*)bits.at(1))->setTexture(ui);
        ((Sprite*)bits.at(1))->setTextureRect(Rect((temp - 1)*26, 0, 26, 31));
    }
    else {
        ((Sprite*)bits.at(1))->setTexture(ui);
        ((Sprite*)bits.at(1))->setTextureRect(Rect(234, 0, 26, 31));
    }
    temp = (mark % 1000) / 100;
    if (temp > 0) {
        ((Sprite*)bits.at(2))->setTexture(ui);
        ((Sprite*)bits.at(2))->setTextureRect(Rect((temp - 1) * 26, 0, 26, 31));
    }
    else {
        ((Sprite*)bits.at(2))->setTexture(ui);
        ((Sprite*)bits.at(2))->setTextureRect(Rect(234, 0, 26, 31));
    }
    temp = (mark % 10000) / 1000;
    if (temp > 0) {
        ((Sprite*)bits.at(3))->setTexture(ui);
        ((Sprite*)bits.at(3))->setTextureRect(Rect((temp - 1) * 26, 0, 26, 31));
    }
    else {
        ((Sprite*)bits.at(3))->setTexture(ui);
        ((Sprite*)bits.at(3))->setTextureRect(Rect(234, 0, 26, 31));
    }
    temp = mark / 10000;
    if (temp > 0) {
        ((Sprite*)bits.at(4))->setTexture(ui);
        ((Sprite*)bits.at(4))->setTextureRect(Rect((temp - 1)*26, 0, 26, 31));
    }
    else {
        ((Sprite*)bits.at(4))->setTexture(ui);
        ((Sprite*)bits.at(4))->setTextureRect(Rect(234, 0, 26, 31));
    }
}