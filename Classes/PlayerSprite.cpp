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

PlayerSprite* PlayerSprite::create(CCSize bgSize) {
    PlayerSprite* pRet = new PlayerSprite();
    if (pRet && pRet->init(bgSize)) {
        pRet->autorelease();
        return pRet;
    } else {
        CC_SAFE_DELETE(pRet);
        return nullptr;
    }
}

bool PlayerSprite::init(CCSize bgSize) {
    if (!CCSprite::initWithFile(PNG_PLAYER)) {
        return false;
    }
    
    mBackgroundSize = bgSize;
    
    gravity = G * mBackgroundSize.height;
    mState = StateJump;
    mOldState = mState;
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
        speedY = -gravity * 0.5f; // ちょっとだけ落とす
        setPosition(ccp(pos.x, pos.y + speedY));
        
    } else if (mState == StateFall) {
        setPosition(ccp(pos.x, pos.y + speedY));
        speedY -= gravity;
    }
    
    mOldState = mState;
}

// タッチイベントを取得した時の処理
void PlayerSprite::touched() {
    if (mState == StateRun) {
        CCPoint pos = getPosition();
        
        speedY = JUMP_SPEED_COEF * mBackgroundSize.height;
        setPosition(ccp(pos.x, pos.y + speedY / 2));
        mState = StateJump;
    }
}

// 上昇しているときtrue
bool PlayerSprite::isUp() const {
    if (speedY > 0 && mOldState != StateRun) {
        return true;
    }
    return false;
}

// プレイヤーをRun状態にする
void PlayerSprite::setPlayerStateRun() {
    mState = StateRun;
}

// プレイヤーのY方向速度をゼロにする
void PlayerSprite::setSpeedZero() {
    speedY = 0;
}

// 衝突判定で衝突していないとき毎回外部から呼ばれる
// Run状態で衝突を起こさない場合Fallに状態遷移する
void PlayerSprite::noIntersection() {
    // ジャンプ中は無視
    if (mState == StateJump) {
        return;
    }
    
    if (mState == StateRun) {
        mOldState = StateRun;
        mState = StateFall;
    }
}