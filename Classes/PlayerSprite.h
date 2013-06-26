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
        StateBump,  // おそらく要らない
    };
    
    PlayerSprite();
    virtual ~PlayerSprite();
    
    virtual bool init(cocos2d::CCSize backgroundSize);
    static PlayerSprite* create(cocos2d::CCSize backgrondSize);
    void update(float dt);
    void touched();
    
    CC_SYNTHESIZE(PlayerState, mState, PlayerState);
    void setPlayerStateRun();
    bool isJumpUp() const;
    
protected:
    cocos2d::CCSize mBackgroundSize;
    float gravity;
    bool jumping;
    float speedY;
};

#endif /* defined(__NinjaInBrain__Player__) */
