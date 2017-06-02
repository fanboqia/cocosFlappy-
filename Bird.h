#ifndef __BIRD_H__
#define __BIRD_H__

#include "cocos2d.h"

USING_NS_CC;

class Bird
{
public:
    Bird(Layer * layer);
    
    void Fall(float dt);
    
    void Fly();
    
    void StopFly(float dt){isFalling = true;};
    
    bool isFalling;
    
    Bird();
    ~Bird();
    
    
private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    
    cocos2d::Sprite *flappyBird;
};

#endif // __BIRD_H__
