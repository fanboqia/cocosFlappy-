#include "MainMenuScene.h"
#include "Definitions.h"
#include "GameScene.h"

USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenuScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    
    auto backGroundSprite = Sprite::create("Background.png");
    backGroundSprite->setPosition(Point(visibleSize.width/2 + origin.x,visibleSize.height/2 + origin.y));
    addChild(backGroundSprite);
    
//    auto title = Sprite::create("Title.png");
//    backGroundSprite->setPosition(Point(visibleSize.width/2 + origin.x,visibleSize.height-(title->getContentSize()).height));
//    addChild(title);
//    
    auto playItem = MenuItemImage::create("Play Button.png", "Play Button Clicked.png", CC_CALLBACK_1(MainMenuScene::GoToGameScene,this));
    playItem->setPosition(Point(visibleSize.width/2 + origin.x,visibleSize.height/2 + origin.y));
    
    auto menu = Menu::create(playItem, NULL);
    menu->setPosition(Point::ZERO);
    
    addChild(menu);
    
    return true;
}

void MainMenuScene::GoToGameScene(cocos2d::Ref* sender)
{
    auto scene = GameScene::createScene();
    
    //professional transition effect
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}