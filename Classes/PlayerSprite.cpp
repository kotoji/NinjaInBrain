//
//  Player.cpp
//  NinjaInBrain
//
//  Created by ktjmba on 2013/06/23.
//
//

#include "PlayerSprite.h"
#include "Config.h"

PlayerSprite::PlayerSprite() {

}

PlayerSprite::~PlayerSprite() {
    
}

PlayerSprite* PlayerSprite::create() {
    PlayerSprite* pRet = new PlayerSprite();
    if (pRet && pRet->init()) {
        pRet->autorelease();
        return pRet;
    } else {
        CC_SAFE_DELETE(pRet);
        return nullptr;
    }
}

bool PlayerSprite::init() {
    if (!CCSprite::initWithFile(PNG_PLAYER)) {
        return false;
    }
    
    return true;
}

void PlayerSprite::update(float dt) {
    
}