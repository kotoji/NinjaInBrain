//
//  Player.h
//  NinjaInBrain
//
//  Created by ktjmba on 2013/06/23.
//
//

#ifndef __NinjaInBrain__Player__
#define __NinjaInBrain__Player__

#include "cocos2d.h"

class PlayerSprite : public cocos2d::CCSprite {
public:
    enum PlayerState {
        StateJump,
        StateRun,
        StateFall,
    };
    
    PlayerSprite();
    virtual ~PlayerSprite();
    
    virtual bool init(cocos2d::CCSize backgroundSize);
    static PlayerSprite* create(cocos2d::CCSize backgrondSize);
    void update(float dt);
    void touched();
    
    CC_SYNTHESIZE(PlayerState, mState, PlayerState);
    void setPlayerStateRun();
    bool isUp() const;
    void setSpeedZero();
    void noIntersection();
    
protected:
    cocos2d::CCSize mBackgroundSize;
    float gravity;
    bool jumping;
    float speedY;
    PlayerState mOldState;
};

#endif /* defined(__NinjaInBrain__Player__) */
