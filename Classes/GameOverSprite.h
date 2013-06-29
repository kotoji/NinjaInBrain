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

#define PNG_GAMEOVER "gameover_bg.png"
#define PNG_RETRY_BTN "retry_btn.png"
#define PNG_TITLE_BTN "title_btn.png"

class GameOverSprite : public cocos2d::CCSprite {
public:
    GameOverSprite();
    virtual ~GameOverSprite();
    
    virtual bool init(cocos2d::CCSize bgSize);
    static GameOverSprite* create(cocos2d::CCSize bgSize);
    
protected:
    void createMenu();
    void menuRetryCallback(cocos2d::CCObject* pSender);
    void menuTitleCallback(cocos2d::CCObject* pSender);
    
private:
    cocos2d::CCSize mBackgroundSize;
};

#endif /* defined(__NinjaInBrain__GameOver__) */
