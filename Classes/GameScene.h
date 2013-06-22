//
//  GameScene.h
//  NinjaInBrain
//
//  Created by ktjmba on 2013/06/22.
//
//

#ifndef __NinjaInBrain__GameScene__
#define __NinjaInBrain__GameScene__

#include "cocos2d.h"

#define PNG_BACKGROUND "background.png"

class GameScene : public cocos2d::CCLayer {
protected:
    enum kTag {
        kTagBackground = 1,
        kTagPlayer,
    };
    
    enum kZOrder {
        kZOrderBackground,
        kZOrderCharacter,
    };
    
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(GameScene);
    
    virtual void update(float dt);

    
protected:
    void createBackground();
    void createPlayer();
    void createInitialPlates();
    
protected:
    cocos2d::CCSprite* mBackground;
};

#endif /* defined(__NinjaInBrain__GameScene__) */
