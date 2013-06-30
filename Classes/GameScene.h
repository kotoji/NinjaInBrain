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
#include "Config.h"
#include <list>

class PlateSprite;

class GameScene : public cocos2d::CCLayer {
protected:
    enum kTag {
        kTagBackground = 1,
        kTagScoreLabel,
        kTagHighScoreLabel,
        kTagGameover,
        kTagPlayer,
        kTagBasePlate = 10000,
    };
    
    enum kZOrder {
        kZOrderBackground,
        kZOrderPlate,
        kZOrderCharacter,
        kZOrderScoreLabel,
        kZOrderGameover,
    };
    
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(GameScene);
    
    virtual void update(float dt);
    
    virtual bool ccTouchBegan(cocos2d::CCTouch* touches, cocos2d::CCEvent* event);
    virtual void ccTouchEnded(cocos2d::CCTouch* touches, cocos2d::CCEvent* event);
    
    int random(int min, int max) const {
        return (rand() % (max - min)) + min;
    }
    
protected:
    void createBackground();
    void createPlayer();
    void createInitialPlates();
    void autoCreatePlate();
    bool isGameOver();
    void reactCollision(kTag objTag);
    kTag detectCollision() const;
    bool isIntersect(const cocos2d::CCPoint aLT, const cocos2d::CCPoint aRB,
                     const cocos2d::CCPoint bLT, const cocos2d::CCPoint bRB) const;
    PlateSprite* createPlate(const kTag plateTag);
    void showGameOver();
    void showScoreLabel();
    void showHighScoreLabel();
    void saveHighScore();
    void scoreUp();
    
protected:
    cocos2d::CCSprite* mBackground;
    std::list<kTag> mPlateTags;
    bool mIsGameOver;
    int mScore;
    int mPlateCount;
};

#endif /* defined(__NinjaInBrain__GameScene__) */
