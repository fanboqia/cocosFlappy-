#include "SplashScene.h"
#include "MainMenuScene.h"
#include "Definitions.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* SplashScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SplashScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SplashScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    //preload three music mp3 
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Point.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Hit.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Wing.mp3");
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //0.5 second to transit to next scene
    scheduleOnce(schedule_selector(SplashScene::GoToMainMenu), DISPLAY_TIME_SPLASH_SCENE);
    
    //first scene picture
    auto backGroundSprite = Sprite::create("Ball.png");
    backGroundSprite->setPosition(visibleSize/2);
    addChild(backGroundSprite);
    
    return true;
}

void SplashScene::GoToMainMenu(float dt)
{
    auto scene = MainMenuScene::createScene();
    
    //professional transition effect
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
    
}
