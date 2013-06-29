//
//  GameOver.cpp
//  NinjaInBrain
//
//  Created by ktjmba on 2013/06/28.
//
//

#include "GameOverSprite.h"
#include "GameScene.h"
#include "StartScene.h"

using namespace cocos2d;

GameOverSprite::GameOverSprite() {
    
}

GameOverSprite::~GameOverSprite() {
    
}

GameOverSprite* GameOverSprite::create(CCSize bgSize) {
    GameOverSprite* pRet = new GameOverSprite();
    if (pRet && pRet->init(bgSize)) {
        pRet->autorelease();
        return pRet;
    } else {
        CC_SAFE_DELETE(pRet);
        return nullptr;
    }
    
}

bool GameOverSprite::init(CCSize bgSize) {
    if (!CCSprite::initWithFile(PNG_GAMEOVER)) {
        return false;
    }
    
    // メンバ変数初期化
    mBackgroundSize = bgSize;
    
    // メニューの生成･表示
    createMenu();
    
    return true;
}

// メニューをつくる（Restart, GoToTitle）
void GameOverSprite::createMenu() {
    CCSize bgSize = mBackgroundSize;
    
    // リトライボタン作成
    CCMenuItemImage* retryButton = CCMenuItemImage::create(PNG_RETRY_BTN, PNG_RETRY_BTN, this, menu_selector(GameOverSprite::menuRetryCallback));
    retryButton->setPosition(ccp(bgSize.width / 2, bgSize.height * 0.35));
    
    // タイトルに戻るボタン作成
    CCMenuItemImage* titleButton = CCMenuItemImage::create(PNG_TITLE_BTN, PNG_TITLE_BTN, this, menu_selector(GameOverSprite::menuTitleCallback));
    titleButton->setPosition(ccp(bgSize.width / 2, bgSize.height * 0.20));
    
    // メニュー作成
    CCMenu* menu = CCMenu::create(retryButton, titleButton, NULL);
    menu->setPosition(CCPointZero);
    this->addChild(menu);
}

void GameOverSprite::menuRetryCallback(CCObject* pSender) {
    GameScene* scene = GameScene::create();
    CCDirector::sharedDirector()->replaceScene((CCScene*)scene);
}

void GameOverSprite::menuTitleCallback(CCObject* pSender) {
    StartScene* scene = StartScene::create();
    CCDirector::sharedDirector()->replaceScene((CCScene*)scene);
}

