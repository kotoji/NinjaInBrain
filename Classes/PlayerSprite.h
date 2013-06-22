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
    PlayerSprite();
    virtual ~PlayerSprite();
    
    virtual bool init();
    static PlayerSprite* create();
    void update(float dt);
};

#endif /* defined(__NinjaInBrain__Player__) */
