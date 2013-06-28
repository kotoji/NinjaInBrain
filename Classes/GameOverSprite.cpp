//
//  GameOver.cpp
//  NinjaInBrain
//
//  Created by ktjmba on 2013/06/28.
//
//

#include "GameOverSprite.h"

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
    
}