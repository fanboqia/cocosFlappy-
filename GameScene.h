#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Bird.h"
#include "Pipe.h"

class GameScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
    
private:
    cocos2d::PhysicsWorld *sceneWorld;
    
    void setPhysicsWorld(cocos2d::PhysicsWorld * world){sceneWorld = world;};
    
    void spawnPipe(float dt);
    
    bool onContactBegin(cocos2d::PhysicsContact & contact);
    
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    
    Pipe pipe;
    
    Bird *bird;
    
    cocos2d::Label *scoreLabel;
    
    unsigned int score;
    
    void update(float dt);
};

#endif // __GAME_SCENE_H__
