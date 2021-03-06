//
//  StartScene.cpp
//  NinjaInBrain
//
//  Created by ktjmba on 2013/06/28.
//
//

#include "StartScene.h"
#include "GameScene.h"

using namespace cocos2d;

CCScene* StartScene::scene() {
    CCScene* scene = CCScene::create();
    StartScene* layer = StartScene::create();
    scene->addChild(layer);
    return scene;
}

bool StartScene::init() {
    if (!CCLayer::init()) {
        return false;
    }
    
    // バックグラウンドの表示
    showBackground();
    
    // スタートボタンの作成
    showStartButton();
    
    return true;
}

void StartScene::showBackground() {
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    mBackground = CCSprite::create(PNG_START_BG);
    mBackground->setPosition(ccp(winSize.width / 2, winSize.height / 2));
    // この画面に置かれるスプライトは数無いのでマジックナンバーでよい。
    this->addChild(mBackground, 1, 1);
}

void StartScene::showStartButton() {
    CCSize bgSize = mBackground->getContentSize();
    
    // スタートボタン作成
    CCMenuItemImage* startButton = CCMenuItemImage::create(PNG_START_BTN, PNG_START_BTN, this, menu_selector(StartScene::menuStartCallback));
    startButton->setPosition(ccp(bgSize.width / 2, bgSize.height * 0.35));
    
    // 終了ボタン生成
    CCMenuItemImage* quitButton = CCMenuItemImage::create(PNG_QUIT_BTN, PNG_QUIT_BTN, this, menu_selector(StartScene::menuQuitCallback));
    quitButton->setPosition(ccp(bgSize.width / 2, bgSize.height * 0.2));
    
    // メニュー作成
    CCMenu* menu = CCMenu::create(startButton, quitButton, NULL);
    menu->setPosition(CCPointZero);
    mBackground->addChild(menu);
}

void StartScene::menuStartCallback(CCObject* Sender) {
    GameScene* scene = GameScene::create();
    CCDirector::sharedDirector()->replaceScene((CCScene*)scene);

}

void StartScene::menuQuitCallback(CCObject *pSender) {
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}