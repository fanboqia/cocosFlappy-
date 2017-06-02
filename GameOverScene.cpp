#include "GameOverScene.h"
#include "MainMenuScene.h"
#include "Definitions.h"
#include "GameScene.h"

USING_NS_CC;

Scene* GameOverScene::createScene(/*unsigned tempScore*/)
{
    //score1 = tempScore;
    
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameOverScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameOverScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //very tranditional way of changing the game scene
    auto mainMenuItem = MenuItemImage::create("Menu Button.png", "Menu Button Clicked.png", CC_CALLBACK_1(GameOverScene::GoToMainMenuScene, this));
    mainMenuItem->setPosition(Point(mainMenuItem->getContentSize().width/2 + 30,mainMenuItem->getContentSize().height/2 + 30));
    
    auto retryItem = MenuItemImage::create("Play Button.png", "Play Button Clicked.png", CC_CALLBACK_1(GameOverScene::GoToGameScene, this));
    retryItem->setPosition(Point(visibleSize.width - retryItem->getContentSize().width/2 - 30,retryItem->getContentSize().height/2 + 30));
    
    auto menu = Menu::create(retryItem,mainMenuItem,NULL);
    menu->setPosition(Point::ZERO);
    
    addChild(menu);
    
//    __String *tempScore1 = __String::createWithFormat("%i",score1);
//    
//    auto currentScore = LabelTTF::create(tempScore1->getCString(), "fonts/Marker Felt.ttf", visibleSize.height* SCORE_FONT_SIZE);
//    
//    currentScore->setPosition(visibleSize/2);
//    
//    addChild(currentScore);
    
    //****************saving the highest score in history*******************//
    
//    UserDefault *def = UserDefault::getInstance();
//    auto highestScore = def->getIntegerForKey("HIGHSCORE", 0);
//    
//    if(score > highestScore)
//    {
//        highestScore = score;
//        def->setIntegerForKey("HIGHSCORE", highestScore);
//    }
//      def->flush();
//    
//    __String *tempScore2 = __String::createWithFormat("%i",score);
//    auto highLabel = LabelTTF::create(tempScore2->getCString(), "fonts/Marker Felt.ttf", visibleSize.height* SCORE_FONT_SIZE);
//    highLabel->setPosition(visibleSize/2);
//    addChild(highLabel);
    
    return true;
}

void GameOverScene::GoToMainMenuScene(cocos2d::Ref *sender)
{
    auto scene = MainMenuScene::createScene();
    
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME,scene));
}

void GameOverScene::GoToGameScene(cocos2d::Ref *sender)
{
    auto scene = GameScene::createScene();
    
    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME,scene));
}