//
//  GameScene.cpp
//  NinjaInBrain
//
//  Created by ktjmba on 2013/06/22.
//
//

#include "GameScene.h"
#include "PlayerSprite.h"
#include "Config.h"

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
    CCLog("updated");
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
    
    PlayerSprite* player = PlayerSprite::create();
    player->setPosition(ccp(bgSize.width * INIT_POS_X, bgSize.height * 0.75));
    this->addChild(player, kZOrderCharacter, kTagPlayer);
}

// 初期地形を生成
void GameScene::createInitialPlates() {
    
}