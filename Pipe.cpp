#include "Pipe.h"
#include "Definitions.h"

USING_NS_CC;

Pipe::Pipe()
{
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
}

Pipe::~Pipe()
{
    
}

void Pipe::spawnPipe(cocos2d::Layer *layer)
{
    log("SPAWN PIPE!\n");
    
    auto topPipe = Sprite::create("pipe_down.png");
    auto bottomPipe = Sprite::create("pipe_up.png");
    
    auto topPipeBody =PhysicsBody::createBox(topPipe->getContentSize());
    auto bottomPipeBody =PhysicsBody::createBox(bottomPipe->getContentSize());
    
    auto random = CCRANDOM_0_1();
    
    if(random < LOWER_SCREEN_PIPE_THRESHOLD)
    {
        random = LOWER_SCREEN_PIPE_THRESHOLD;
    }
    else if(random > UPPER_SCREEN_PIPE_THRESHOLD)
    {
        random = UPPER_SCREEN_PIPE_THRESHOLD;
    }
    
    auto topPipePosition = (random * visibleSize.height) + (topPipe->getContentSize().height/2);
    
    topPipeBody->setDynamic(false);
    bottomPipeBody->setDynamic(false);
    //collision 
    topPipeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
    bottomPipeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
    topPipeBody->setContactTestBitmask(true);
    bottomPipeBody->setContactTestBitmask(true);
//    topPipeBody->setVelocity(Vec2(-100,0));
//    bottomPipeBody->setVelocity(Vec2(-100,0));
    
    topPipe->setPhysicsBody(topPipeBody);
    bottomPipe->setPhysicsBody(bottomPipeBody);
    
    topPipe->setPosition(Point(visibleSize.width/2 + origin.x + topPipe->getContentSize().width, topPipePosition));
    bottomPipe->setPosition(Point(topPipe->getPositionX(), topPipePosition - (Sprite::create("bird0_0.png")->getContentSize().height * PIPE_GAP) - topPipe->getContentSize().height));
    
//    topPipe->getPhysicsBody()->setVelocity(Vec2(-20,0));
//    bottomPipe->getPhysicsBody()->setVelocity(Vec2(-20,0));
    
    layer->addChild(topPipe);
    layer->addChild(bottomPipe);
    
    auto topPipeAction = MoveBy::create(PIPE_MOVEMENT_SPEED * visibleSize.width,Point(-visibleSize.width*1.5,0));
    
    auto bottomPipeAction = MoveBy::create(PIPE_MOVEMENT_SPEED * visibleSize.width,Point(-visibleSize.width*1.5,0));
    
    topPipe->runAction(topPipeAction);
    bottomPipe->runAction(bottomPipeAction);
    
    auto nodeDection = Node::create();
    nodeDection->setAnchorPoint(Vec2(0.5,0.5));
    auto nodeDectionBody = PhysicsBody::createBox(Size(1,Sprite::create("bird0_0.png")->getContentSize().height * PIPE_GAP));
    
    nodeDectionBody->setDynamic(false);
    nodeDectionBody->setCollisionBitmask(POINT_COLLISION_BITMASK);
    nodeDectionBody->setContactTestBitmask(true);
    
    nodeDection->setPhysicsBody(nodeDectionBody);
    nodeDection->setPosition(Point(topPipe->getPositionX(),topPipe->getPositionY()-(topPipe->getContentSize().height/2) - (Sprite::create("bird0_0.png")->getContentSize().height * PIPE_GAP)/2));
    
    layer->addChild(nodeDection);
    
    auto nodeAction = MoveBy::create(PIPE_MOVEMENT_SPEED * visibleSize.width,Point(-visibleSize.width*1.5,0));
    nodeDection->runAction(nodeAction);
}