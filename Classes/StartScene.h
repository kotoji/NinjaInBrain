//
//  StartScene.h
//  NinjaInBrain
//
//  Created by ktjmba on 2013/06/28.
//
//

#ifndef __NinjaInBrain__StartScene__
#define __NinjaInBrain__StartScene__

#include "cocos2d.h"

#define PNG_START_BG "start_bg.png"
#define PNG_START_BTN "start_btn.png"
#define PNG_QUIT_BTN "quit_btn.png"

class StartScene : public cocos2d::CCLayer {
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(StartScene);
    
protected:
    void showBackground();
    void showStartButton();
    void menuStartCallback(CCObject* pSender);
    void menuQuitCallback(CCObject* pSender);

protected:
    cocos2d::CCSprite* mBackground;
};

#endif /* defined(__NinjaInBrain__StartScene__) */
