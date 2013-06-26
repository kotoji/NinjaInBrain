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
    mState = StateJump;
    speedY = -gravity;
    
    return true;
}

// 毎フレームごとの処理
void PlayerSprite::update(float dt) {
    CCPoint pos = getPosition();
    // 重力で落下する
    if (mState == StateJump) {
        setPosition(ccp(pos.x, pos.y + speedY));
        speedY -= gravity;
    } else if (mState == StateRun) {
        speedY = 0;
    }
    
}

// タッチイベントを取得した時の処理
void PlayerSprite::touched() {
    if (mState == StateRun) {
        speedY = JUMP_SPEED_COEF * mBackgroundSize.height;
        mState = StateJump;
    }
}

// ジャンプ中でかつ上昇しているときtrue
bool PlayerSprite::isJumpUp() const {
    if (mState == StateJump && speedY > 0) {
        return true;
    }
    return false;
}

// プレイヤーをRun状態にする
void PlayerSprite::setPlayerStateRun() {
    mState = StateRun;
}