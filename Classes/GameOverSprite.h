//
//  GameOver.h
//  NinjaInBrain
//
//  Created by ktjmba on 2013/06/28.
//
//

#ifndef __NinjaInBrain__GameOver__
#define __NinjaInBrain__GameOver__

#include "cocos2d.h"

#define PNG_GAMEOVER "gameover.png"

class GameOverSprite : cocos2d::CCSprite {
public:
    GameOverSprite();
    virtual ~GameOverSprite();
    
    bool init(cocos2d::CCSize bgSize);
    GameOverSprite* create(cocos2d::CCSize bgSize);
    
protected:
    void createMenu();
    
private:
    cocos2d::CCSize mBackgroundSize;
};

#endif /* defined(__NinjaInBrain__GameOver__) */
