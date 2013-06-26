//
//  PlateSprite.h
//  NinjaInBrain
//
//  Created by ktjmba on 2013/06/23.
//
//

#ifndef __NinjaInBrain__PlateSprite__
#define __NinjaInBrain__PlateSprite__

#include "cocos2d.h"
#include "Config.h"

class PlateSprite : public cocos2d::CCSprite {
public:
    enum kPlate {
        kPlateLong,
        kPlateMid,
        kPlateShort,
        kPlateCount,
    };

protected:
    const char* getImageFileName(kPlate plateType) const;
    
public:
    PlateSprite();
    virtual ~PlateSprite();
    
    virtual bool initWithType(kPlate plateType, cocos2d::CCSize backgroundSize);
    static PlateSprite* createWithType(kPlate plateType, cocos2d::CCSize backgroundSize);
    void update(float dt);
    
    CC_SYNTHESIZE_READONLY(kPlate, mPlateType, PlateType);
    
protected:
    cocos2d::CCSize mBackgroundSize;
};

#endif /* defined(__NinjaInBrain__PlateSprite__) */
