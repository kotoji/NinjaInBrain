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
#include "GameOverSprite.h"
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
    
    // メンバ変数の初期化
    mIsGameOver = false;
    
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
    // すでにゲームオーバーなら処理を行わない
    if (mIsGameOver) {
        return;
    }
    
    PlayerSprite* player = static_cast<PlayerSprite*>(mBackground->getChildByTag(kTagPlayer));
    
    // 消えたPlateのタグを消去する
    while (!mPlateTags.empty()) {
        if (!mBackground->getChildByTag(static_cast<int>(mPlateTags.front()))) {
            mPlateTags.pop_front();
        } else {
            break;
        }
    }
    
    // 衝突応答
    kTag tag = detectCollision();
    if (tag != -1) {
        reactCollision(tag);
    }
    
    // プレイヤーアップデート
    player->update(dt);
    
    // 各プレートアップデート
    for (auto plateTag : mPlateTags) {
        mBackground->getChildByTag(plateTag)->update(dt);
    }
    
    // プレートの自動生成
    autoCreatePlate();
    
    // ゲームオーバー判定
    if (isGameOver()) {
        mIsGameOver = true;
        // ゲームオーバー画面をかぶせる
        showGameOver();
    }
    
}

bool GameScene::ccTouchBegan(CCTouch* touchs , CCEvent* event) {
    return true;
}

// タップされた時
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
    PlateSprite* plate2 = createPlate(static_cast<kTag>(tagPlate1));
    // X座標を決める
    float plate2X = plate1->getPosition().x + (plate1->getContentSize().width + plate2->getContentSize().width) / 2
                    + random(5, 10) * 0.02f * bgSize.width;
    plate2->setPosition(ccp(plate2X, plate2->getPosition().y));
    int tagPlate2 = tagPlate1 + 1;
    mBackground->addChild(plate2, kZOrderPlate, tagPlate2);
    mPlateTags.push_back(static_cast<kTag>(tagPlate2));
    
    // 3つ目
    PlateSprite* plate3 = createPlate(static_cast<kTag>(tagPlate2));
    // X座標を決める
    float plate3X = plate2->getPosition().x + (plate2->getContentSize().width + plate3->getContentSize().width) / 2
                    + random(5, 10) * 0.02f * bgSize.width;
    plate3->setPosition(ccp(plate3X, plate3->getPosition().y));
    int tagPlate3 = tagPlate2 + 1;
    mBackground->addChild(plate3, kZOrderPlate, tagPlate3);
    mPlateTags.push_back(static_cast<kTag>(tagPlate3));
}

// プレートの自動生成
void GameScene::autoCreatePlate() {
    // 最後尾のプレートが画面に半分以上表示されたら新しいプレートを生成する
    kTag lastPlateTag = mPlateTags.back();
    PlateSprite* lastPlate = static_cast<PlateSprite*>(mBackground->getChildByTag(lastPlateTag));
    
    CCSize bgSize = mBackground->getContentSize();
    CCPoint lastPlatePos = lastPlate->getPosition();
    
    if (lastPlatePos.x > bgSize.width) {
        // まだ生成しなくてよいのでリターン
        return;
    }
    
    // 新しいプレートを生成、登録する
    PlateSprite* newPlate = createPlate(lastPlateTag);
    // X座標を決める
    float newPlateX = lastPlatePos.x + (newPlate->getContentSize().width + newPlate->getContentSize().width) / 2
                    + random(5, 10) * 0.025f * bgSize.width;
    newPlate->setPosition(ccp(newPlateX, newPlate->getPosition().y));
    // タグを決める、古くなったタグが使い回せるならそれを使う
    int newPlateTag = kTagBasePlate;
    if (!(lastPlateTag > kTagBasePlate + 10)) {
        newPlateTag = lastPlateTag + 1;
    }
    // 登録
    mBackground->addChild(newPlate, kZOrderPlate, newPlateTag);
    mPlateTags.push_back(static_cast<kTag>(newPlateTag));
}

// ゲームオーバー判定
bool GameScene::isGameOver() {
    CCSprite* player = static_cast<CCSprite*>(mBackground->getChildByTag(kTagPlayer));
    
    if (player->getPosition().y + player->getContentSize().height < 0) {
        return true;
    }
    
    return false;
}

// 衝突判定(プレイヤーと衝突している対象のタグを返す, 衝突していない場合は−1)
GameScene::kTag GameScene::detectCollision() const {
    // CCRectを使って上手いこと実装できるようならそちらに切り替える
    
    
    // プレイヤーの当たり判定矩形を計算
    PlayerSprite* player = static_cast<PlayerSprite*>(mBackground->getChildByTag(kTagPlayer));
    CCPoint playerPos = player->getPosition();
    CCSize playerSize = player->getContentSize();
    // TODO COUTION : MagicNumber
    CCPoint playerPointLT = ccp(playerPos.x - playerSize.width * 0.5, playerPos.y + playerSize.height * 0.5);
    CCPoint playerPointRB = ccp(playerPos.x + playerSize.width * 0.45, playerPos.y - playerSize.height * 0.45);
    
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
            CCPoint objPointLT = ccp(objPos.x - objSize.width / 2, objPos.y + objSize.height / 2);
            CCPoint objPointRB = ccp(objPos.x + objSize.width / 2, objPos.y - objSize.height / 2);
            
            if (isIntersect(playerPointLT, playerPointRB, objPointLT, objPointRB)) {
                return plateTag;
            }
        }
    }
    // ぶつからなかった
    player->noIntersection();
    return static_cast<kTag>(-1);
}

// 衝突判定補助関数
bool GameScene::isIntersect(const CCPoint aLT, const CCPoint aRB, const CCPoint bLT, const CCPoint bRB) const {
    if ((aLT.x < bRB.x) && (aRB.x > bLT.x)) {
        if ((aLT.y > bRB.y) && (aRB.y < bLT.y)) {
            return true;
        }
    }
    return false;
}

// 衝突応答(衝突があった場合の処理)
void GameScene::reactCollision(GameScene::kTag objTag) {
    PlayerSprite* player = static_cast<PlayerSprite*>(mBackground->getChildByTag(kTagPlayer));
    CCSprite* obj = static_cast<CCSprite*>(mBackground->getChildByTag(objTag));
    
    // プレイヤーの当たり判定矩形を計算
    CCPoint playerPos = player->getPosition();
    CCSize playerSize = player->getContentSize();
    // TODO COUTION : MagicNumber
    CCPoint playerPointLT = ccp(playerPos.x + playerSize.width * 0.4f, playerPos.y + playerSize.height * 0.45f);
    CCPoint playerPointRB = ccp(playerPos.x - playerSize.width * 0.4f, playerPos.y - playerSize.height * 0.45f);
    
    // 衝突したオブジェクトの当たり判定矩形の計算
    CCPoint objPos = obj->getPosition();
    CCSize objSize = obj->getContentSize();
    CCPoint objPointLT = ccp(objPos.x + objSize.width / 2, objPos.y + objSize.height / 2);
    CCPoint objPointRB = ccp(objPos.x - objSize.width / 2, objPos.y - objSize.height / 2);
    
    // 衝突したオブジェクトがプレートだった場合
    if (objTag >= kTag::kTagBasePlate) {
        
        
        // プレイヤーが(速度的な意味で)落下中の場合
        if (!player->isUp()) {
            float diff = objPointLT.y - playerPointRB.y;
            player->setPlayerStateRun();
            player->setPosition(ccp(playerPos.x, playerPos.y + diff));
            
        } // プレーヤーが上昇中
        else {
            float diff = playerPointLT.y - objPointRB.y;
            player->setPosition(ccp(playerPos.x, playerPos.y - diff));
            player->setSpeedZero();
        }
    }
}

// プレート生成補助メソッド
// 前にあるプレートの情報を元に新しいプレートをつくる
PlateSprite* GameScene::createPlate(const kTag frontPlateTag) {
    CCSize bgSize = mBackground->getContentSize();
    PlateSprite* frontPlate = static_cast<PlateSprite*>(mBackground->getChildByTag(frontPlateTag));
    
    // プレートの種類をランダムで決定して作成する
    PlateSprite::kPlate plateType = static_cast<PlateSprite::kPlate>(random(0, 100) % PlateSprite::kPlateCount);
    PlateSprite* newPlate = PlateSprite::createWithType(plateType, bgSize);
    
    // Y座標の位置決め
    float hightRatio = mBackground->getContentSize().height;
    // Y座標があまり変わらない(25%)、ある程度変わる(50%)、大幅に変わる(25%)の3パターンで分ける
    int rnd = random(0, 100);
    if (rnd < 25) {
        hightRatio *= 0.2f;
    } else if (rnd < 80) {
        hightRatio *= 0.5f;
    } else {
        hightRatio *= 0.35f;
    }
    // 範囲を定める
    float rangeDown = frontPlate->getPosition().y - hightRatio / 2;
    float rangeUp = frontPlate->getPosition().y + hightRatio / 2;
    
    // 画面外に出ないように調整
    if (rangeDown < bgSize.height * 0.05) {
        rangeDown = bgSize.height * 0.05;
    }
    if (rangeUp > bgSize.height * 0.8) {
        rangeUp = bgSize.height * 0.8;
    }
    
    // ランダムでY座標を確定
    float newPlateY = static_cast<float>(random(static_cast<int>(rangeDown), static_cast<int>(rangeUp)));
    
    // 位置を確定する（X座標はとりあえずギリギリ画面外にでるように設定）
    newPlate->setPosition(ccp(bgSize.width + newPlate->getContentSize().width / 2, newPlateY));
    
    return newPlate;
}


// ゲームオーバー画面を被せる
void GameScene::showGameOver() {
    CCSize bgSize = mBackground->getContentSize();
    
    GameOverSprite* sprite = GameOverSprite::create(bgSize);
    sprite->setPosition(ccp(bgSize.width / 2, bgSize.height / 2));
    mBackground->addChild(sprite, kZOrderGameover, kTagGameover);
}