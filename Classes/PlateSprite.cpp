//
//  PlateSprite.cpp
//  NinjaInBrain
//
//  Created by ktjmba on 2013/06/23.
//
//

#include "PlateSprite.h"

using namespace cocos2d;

PlateSprite::PlateSprite() {
    
}

PlateSprite::~PlateSprite() {
    
}

PlateSprite* PlateSprite::createWithType(kPlate plateType, CCSize backgroundSize) {
    PlateSprite* pRet = new PlateSprite();
    if (pRet && pRet->initWithType(plateType, backgroundSize)) {
        pRet->autorelease();
        return pRet;
    } else {
        CC_SAFE_DELETE(pRet);
        return nullptr;
    }
}

bool PlateSprite::initWithType(kPlate plateType, CCSize backgroundSize) {
    if (!CCSprite::initWithFile(getImageFileName(plateType))) {
        return false;
    }
    
    mPlateType = plateType;
    mBackgroundSize = backgroundSize;
    
    return true;
}

const char* PlateSprite::getImageFileName(kPlate plateType) const {
    switch (plateType) {
        case kPlateLong:
            return PNG_PLATE_LONG;
        case kPlateMid:
            return PNG_PLATE_MID;
        case kPlateShort:
            return PNG_PLATE_SHORT;
            
        default:
            CCAssert(false, "invalid plateType");
            return "";
    }
}

void PlateSprite::update(float dt) {
    CCPoint pos = getPosition();
    
    // 移動する
    float speedX = PLATE_SPEED_COEF * mBackgroundSize.width;
    this->setPosition(ccp(pos.x - speedX, pos.y));
    
    // 画面外に出たら消滅
    if (pos.x <(-getContentSize().width + 50)) {
        this->removeFromParentAndCleanup(true);
    }
}