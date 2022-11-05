
#include "PreLoadGame.h"
#include "GameMenuScene.h"
#include "cocostudio/SimpleAudioEngine.h"
using namespace CocosDenshion;

Scene* GameLoad::createScene()
{
    auto scene = Scene::create();
    auto layer = GameLoad::create();
    scene->addChild(layer);
    return scene;
}

bool GameLoad::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }
    //Get screen with and height
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //Set progress and use progressUpdate function to update it.
    Sprite* bg = Sprite::create("Map/cocos.png");
    bg->setScale(1.2);
    bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(bg, 0, 0);
    Sprite* poss = Sprite::create("Map/jingdu.png");
    _progress = ProgressTimer::create(poss);
    //set progress bar is zero;  
    _progress->setPercentage(0.0f);
    _progress->setMidpoint(Vec2(0,0));
    _progress->setBarChangeRate(Vec2(1,0));
    _progress->setType(ProgressTimer::Type::BAR);
    _progress->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2-200));
    this->addChild(_progress);
    return true;
}
void GameLoad::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
    //Parse the preload.json file to preload file for spriteSheet and Audio.
    std:: string effects = regx.getJsonData(fmanager.getFilePreLoadPath(), "Sounds");
    log("path effects is:%s",effects.c_str());
    std::string spriteSheets = fmanager.getFileResPath().append(regx.getJsonData(fmanager.getFilePreLoadPath(), "SpriteSheet"));
    log("path spriteSheets is:%s", spriteSheets.c_str());
    //std::string musics = fmanager.getFileResPath().append(regx.getJsonData(fmanager.getFilePreLoadPath(),  "Musics"));
    std::string musics = std::string("Sounds//").append(regx.getJsonData(fmanager.getFilePreLoadPath(), "Musics"));
    log("path musics is:%s", musics.c_str());
    _sourceCount = effects.size() + spriteSheets.size() + musics.size();
    _sourceCount = 2;
    _progressInterval = 100 / _sourceCount;
    loadMusic(musics);
    loadEffect(effects);
    loadSpriteSheets(spriteSheets);
}


/***********************************************************************
Name : loadMusic()
Function : Preload BackgroundMusic 
Args:
    string musicFiles music name
return type : void
************************************************************************/
void GameLoad::loadMusic(std::string musicFiles)
{
    //for (unsigned int i = 0; i != musicFiles.size(); ++i)
    //{
    //    Value v = musicFiles.at(i);
    log("music path:%s", musicFiles.c_str());
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic(musicFiles.c_str());
    //}
        progressUpdate();
}


/***********************************************************************
Name : loadEffect()
Function : Preload BackgroundEffect
Args:
    string musicFiles Effect name
return type : void
************************************************************************/
void GameLoad::loadEffect(std::string efficFiles)
{
    //for (unsigned int i = 0; i != efficFiles.size(); ++i)
    //{
    //    Value v = efficFiles.at(i);
    //    SimpleAudioEngine::getInstance()->preloadEffect(v.asString().c_str());
    //}
    progressUpdate();
}
void GameLoad::loadSpriteSheets(std::string spriteSheets)
{
    //for (unsigned int i = 0; i != spriteSheets.size(); ++i)
    //{
    //    Value v = spriteSheets.at(i);
        log("sheet name is%s",spriteSheets.c_str());
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile(spriteSheets.c_str());



    //}
        progressUpdate();
}

//Able to update progress by setPercentage.
void GameLoad::progressUpdate()
{
    log("break point00%d",(int)_sourceCount);
    if (--_sourceCount)
    {
        log("break point11%d",(int)_sourceCount);
        _progress->setPercentage(100.0f-(_progressInterval* _sourceCount));

    }
    else
    {
        log("break point22%d", (int)_sourceCount);
        auto pft = ProgressFromTo::create(0.5f,_progress->getPercentage(),100);
        auto callFunc = CallFunc::create([=]
            {
                auto delay = DelayTime::create(1.0f);
                auto callFunc = CallFunc::create([]
                    {
                        Director::getInstance()->replaceScene(GameMenu::createScene());
                    });
                auto action = Sequence::create(delay,callFunc,NULL);
                this->runAction(action);
            });
        auto action = Sequence::create(pft,callFunc,NULL);
        _progress->runAction(action);
    }
}