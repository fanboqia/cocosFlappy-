#include "Bird.h"
#include "Definitions.h"

USING_NS_CC;

Bird::Bird(Layer * layer)
{
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    isFalling = true;
    
    flappyBird = Sprite::create("Ball.png");
    flappyBird->setPosition(visibleSize/2);
    
    auto flappyBody = PhysicsBody::createCircle(flappyBird->getContentSize().width);
    flappyBody->setCollisionBitmask(BIRD_COLLISION_BITMASK);
    flappyBody->setContactTestBitmask(true);
    
    flappyBird->setPhysicsBody(flappyBody);
    
    layer->addChild(flappyBird, 100);
    
}

Bird::~Bird()
{
    
}

Bird::Bird()
{
    
}

void Bird::Fly()
{
    flappyBird->getPhysicsBody()->setVelocity(Vec2(0,100));
}