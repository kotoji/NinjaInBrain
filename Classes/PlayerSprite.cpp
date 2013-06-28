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
    speedY = -gravity;
    noIntersectCount = 0;
    
    return true;
}

// 毎フレームごとの処理
void PlayerSprite::update(float dt) {
    
    CCPoint pos = getPosition();
    // 重力で落下する
    if (mState == StateJump) {
        setPosition(ccp(pos.x, pos.y + speedY));
        speedY -= gravity;
        noIntersectCount = 0;
    } else if (mState == StateRun) {
        speedY = gravity * 0.15f; // ちょっとだけ落とす
        setPosition(ccp(pos.x, pos.y + speedY));
        
    } else if (mState == StateFall) {
        setPosition(ccp(pos.x, pos.y + speedY));
        speedY -= gravity;
    }
    
}

// タッチイベントを取得した時の処理
void PlayerSprite::touched() {
    if (mState == StateRun || mState == StateFall) {
        speedY = JUMP_SPEED_COEF * mBackgroundSize.height;
        mState = StateJump;
    }
}

// ジャンプ中でかつ上昇しているときtrue
bool PlayerSprite::isJumpAndUp() const {
    if (mState == StateJump && speedY > 0) {
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
// Run状態でずっと衝突を起こさない場合Fallに状態遷移する
void PlayerSprite::noIntersection() {
    // ジャンプ中は無視
    if (mState == StateJump) {
        noIntersectCount = 0;
        return;
    }
    
    if (noIntersectCount > 5) {
        mState = StateFall;
    }
    noIntersectCount++;
}