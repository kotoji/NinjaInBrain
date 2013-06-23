//
//  Player.cpp
//  NinjaInBrain
//
//  Created by ktjmba on 2013/06/23.
//
//

#include "PlayerSprite.h"
#include "GameScene.h"
#include "Config.h"

using namespace cocos2d;

PlayerSprite::PlayerSprite() {

}

PlayerSprite::~PlayerSprite() {
    
}

PlayerSprite* PlayerSprite::create(CCSize backgraoundSize) {
    PlayerSprite* pRet = new PlayerSprite();
    if (pRet && pRet->init(backgraoundSize)) {
        pRet->autorelease();
        return pRet;
    } else {
        CC_SAFE_DELETE(pRet);
        return nullptr;
    }
}

bool PlayerSprite::init(CCSize backgroundSize) {
    if (!CCSprite::initWithFile(PNG_PLAYER)) {
        return false;
    }
    
    mBackgroundSize = backgroundSize;
    
    gravity = G * mBackgroundSize.height;
    jumping = true;
    speedY = -gravity;
    
    return true;
}

// 毎フレームごとの処理
void PlayerSprite::update(float dt) {
    CCPoint pos = getPosition();
    // 重力で落下する
    if (jumping) {
        setPosition(ccp(pos.x, pos.y - speedY));
        speedY += gravity;
    }
    
}

// タッチイベントを取得した時の処理
void PlayerSprite::touched() {
    
}