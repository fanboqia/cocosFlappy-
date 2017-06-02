#include "GameScene.h"
#include "MainMenuScene.h"
#include "Definitions.h"
#include "GameOverScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();
    layer->setPhysicsWorld(scene->getPhysicsWorld());

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto backGroundSprite = Sprite::create("supernova.jpg");
    backGroundSprite->setPosition(visibleSize/2);
    addChild(backGroundSprite);
    
    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize,PHYSICSBODY_MATERIAL_DEFAULT,3);
    edgeBody->setContactTestBitmask(true);
    edgeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
    
    auto edgeNode = Node::create();
    edgeNode->setPosition(visibleSize/2);
   
    edgeNode->setPhysicsBody(edgeBody);
    
    addChild(edgeNode);
    
    log("pixel: %f  %f",visibleSize.width,visibleSize.height);
    
    schedule(schedule_selector(GameScene::spawnPipe),PIPE_SPAWN_FREQUENCY*visibleSize.width);
    
    bird = new Bird(this);
    
    //set up for contact listener
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    //set up for touch listener
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true); //???????
    touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    scheduleUpdate();
    
    score = 0;
    
    //***********print the score on upper left corner********************
    __String *tempScore = __String::createWithFormat("%i",score);
    
    scoreLabel = Label::createWithTTF(tempScore->getCString(),"fonts/Marker Felt.ttf",visibleSize.height * SCORE_FONT_SIZE);
    
    scoreLabel->setColor(Color3B::WHITE);
    scoreLabel->setPosition(scoreLabel->getContentSize().width/2 + 30,visibleSize.height-scoreLabel->getContentSize().height/2 - 30);
    
    addChild(scoreLabel,100000);
    
    return true;
}

void GameScene::spawnPipe(float dt)
{
    pipe.spawnPipe(this);
}

bool GameScene::onContactBegin(cocos2d::PhysicsContact & contact)
{
    PhysicsBody * a = contact.getShapeA()->getBody();
    PhysicsBody * b = contact.getShapeB()->getBody();
    
    if((BIRD_COLLISION_BITMASK == a->getCollisionBitmask() && OBSTACLE_COLLISION_BITMASK == b->getCollisionBitmask())||(BIRD_COLLISION_BITMASK == b->getCollisionBitmask() && OBSTACLE_COLLISION_BITMASK == a->getCollisionBitmask()))
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Hit.mp3");
        
        auto scene = GameOverScene::createScene(/*score*/);
        
        Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME,scene));
        
    }
    else if((BIRD_COLLISION_BITMASK == a->getCollisionBitmask() && POINT_COLLISION_BITMASK == b->getCollisionBitmask())||(BIRD_COLLISION_BITMASK == b->getCollisionBitmask() && POINT_COLLISION_BITMASK == a->getCollisionBitmask()))
    {
        log("Score: %d\n", score++);
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Point.mp3");
    
        __String *tempScore = __String::createWithFormat("%i",score);
    
        scoreLabel->setString(tempScore->getCString());    
    }
    
    return true;
}

bool GameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    log("screen cliked!\n");
    
    bird->Fly();
    
    //music
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Wing.mp3");
    
    return true;
}

void GameScene::update(float dt)
{
    
}
