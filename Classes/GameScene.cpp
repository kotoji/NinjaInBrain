//
//  GameScene.cpp
//  NinjaInBrain
//
//  Created by ktjmba on 2013/06/22.
//
//

#include "GameScene.h"
#include "PlayerSprite.h"
#include "PlateSprite.h"
#include "Config.h"
#include <list>

using namespace cocos2d;

CCScene* GameScene::scene() {
    CCScene* scene = CCScene::create();
    GameScene* layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

// 初期化
bool GameScene::init() {
    if (!CCLayer::init()) {
        return false;
    }
    
    // 乱数の種まき
    srand(static_cast<unsigned>(time(nullptr)));
    
    // タップを有効にする
    setTouchEnabled(true);
    setTouchMode(cocos2d::kCCTouchesOneByOne);
    
    // 背景表示
    createBackground();
    
    // プレイヤー表示
    createPlayer();
    
    // 最初の地形を生成
    createInitialPlates();
    
    // フレーム毎の処理を開始する
    scheduleUpdate();
    
    return true;
}

// 更新処理
void GameScene::update(float dt) {
    // 消えたPlateのタグを消去する
    while (!mPlateTags.empty()) {
        if (!mBackground->getChildByTag(static_cast<int>(mPlateTags.front()))) {
            mPlateTags.pop_front();
        } else {
            break;
        }
    }
    
    // プレイヤーアップデート
    mBackground->getChildByTag(kTagPlayer)->update(dt);
    
    // 各プレートアップデート
    for (auto plateTag : mPlateTags) {
        mBackground->getChildByTag(plateTag)->update(dt);
    }
    
}

bool GameScene::ccTouchBegan(CCTouch* touchs , CCEvent* event) {
    return true;
}

void GameScene::ccTouchEnded(CCTouch* touches, CCEvent* event) {
    static_cast<PlayerSprite*>(mBackground->getChildByTag(kTagPlayer))->touched();
}


// 背景生成
void GameScene::createBackground() {
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    mBackground = CCSprite::create(PNG_BACKGROUND);
    mBackground->setPosition(ccp(winSize.width / 2, winSize.height / 2));
    this->addChild(mBackground, kZOrderBackground, kTagBackground);
}

// プレイヤー生成
void GameScene::createPlayer() {
    CCSize bgSize = mBackground->getContentSize();
    
    PlayerSprite* player = PlayerSprite::create(mBackground->getContentSize());
    player->setPosition(ccp(bgSize.width * INIT_POS_X, bgSize.height * 0.75));
    mBackground->addChild(player, kZOrderCharacter, kTagPlayer);
}

// 初期地形を生成
void GameScene::createInitialPlates() {
    // TODO COUTION : 地形のタグはユニークである必要があるが使いまわせる(10個も必要ないだろう)
    CCSize bgSize = mBackground->getContentSize();
    CCPoint playerPos = mBackground->getChildByTag(kTagPlayer)->getPosition();
    
    // 1つ目、プレイヤーの下に作らないと死ぬ
    PlateSprite* plate1 = PlateSprite::createWithType(PlateSprite::kPlateLong, mBackground->getContentSize());
    int tagPlate1 = static_cast<int>(kTagBasePlate);
    float offsetY = bgSize.height * 0.25;
    float offsetX = bgSize.width * (random(4, 10) * 0.01f);
    float posX = playerPos.x + offsetX;
    float posY = bgSize.height * (random(2, 4) * 0.1f) + offsetY;
    plate1->setPosition(ccp(posX, posY));
    mBackground->addChild(plate1, kZOrderPlate, tagPlate1);
    mPlateTags.push_back(static_cast<kTag>(tagPlate1));
    
    // 2つ目
    
}

// 衝突判定(プレイヤーと衝突している対象のタグを返す, 衝突していない場合は−1)
GameScene::kTag GameScene::detectIntersect() const {
    
    // プレイヤーの当たり判定矩形を計算
    CCSprite* player = static_cast<CCSprite*>(mBackground->getChildByTag(kTagPlayer));
    CCPoint playerPos = player->getPosition();
    CCSize playerSize = player->getContentSize();
    // TODO COUTION : MagicNumber
    CCPoint playerPointLT = ccp(playerPos.x + playerSize.width * 0.9, playerPos.y + playerSize.height * 0.9);
    CCPoint playerPointRB = ccp(playerPos.x - playerSize.width * 0.9, playerPos.y - playerSize.height * 0.9);
    
    // プレートとの衝突を判定
    for (auto plateTag : mPlateTags) {
        CCSprite* obj = static_cast<CCSprite*>(mBackground->getChildByTag(plateTag));
        // 確実にぶつからないものは無視
        if (obj->getPosition().x > (mBackground->getPosition().x / 2)) {
            continue;
        } else {
            // プレートの当たり判定矩形の計算
            CCPoint objPos = obj->getPosition();
            CCSize objSize = obj->getContentSize();
            CCPoint objPointLT = ccp(objPos.x + objSize.width, objPos.y + objSize.height);
            CCPoint objPointRB = ccp(objPos.x - objSize.width, objPos.y - objSize.height);
            
            
        }
    }
    return static_cast<kTag>(-1);
}

// 衝突判定補助関数
bool GameScene::isIntersect(const CCPoint aLT, const CCPoint aRB, const CCPoint bLT, const CCPoint bRB) const {
    
}