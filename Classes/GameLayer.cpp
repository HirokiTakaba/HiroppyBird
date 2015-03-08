//
//  GameLayer.cpp
//  HiroppyBird
//
//  Created by Hiroki Takaba on 2015/03/05.
//
//

#include "GameLayer.h"

USING_NS_CC;

#define WINSIZE Director::getInstance()->getWinSize() // 画面サイズ
#define INIT_BLOCK_TIME 3.0 // ブロックが最初に出現する時間
#define INTERVAL_BLOCK_TIME 1.5 // ブロックが出現するタイミング
#define MOVING_TIME 3 // ブロックが消えるまでの時間
#define JUMP_V0 5 // ジャンプの初速度
#define GRAVITY 9.8 // 重力
#define POSITION_RATE 70 // ゲーム倍率

// シーン生成
Scene* GameLayer::createScene()
{
    auto scene = Scene::create(); // シーンを生成する
    auto layer = GameLayer::create(); // GameLayerクラスのレイヤーを生成する
    scene->addChild(layer); // シーンに対してレイヤーを追加する
    
    return scene; // シーンを返す
}

// 初期化
bool GameLayer::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    // 乱数の初期化
    std::random_device rd;
    _mt = std::mt19937(rd());
    _height = std::uniform_real_distribution<double>(-200.0, 200.0);
    
    // 画面サイズ取得
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    // 背景の設定
    auto sprite = Sprite::create("ui/background.png");
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(sprite, 0);
    
    // タップイベントの取得
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(GameLayer::onTouchesBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

// レイヤー表示処理
void GameLayer::onEnter()
{
    Layer::onEnter();
    
    // キャラクター
    _bird = Sprite::create("bird/penguin_1.png");
    _bird->setPosition(WINSIZE.width/2 *0.6, WINSIZE.height/2);
    _bird->setName("bird");
    this->addChild(_bird);
    
    // スタートボタン
    auto startButton = Sprite::create("ui/getready.png");
    startButton->setPosition(WINSIZE.width/2, WINSIZE.height/2);
    startButton->setName("start_button");
    this->addChild(startButton);
    
}

// update関数（毎フレーム処理）
void GameLayer::update(float dt)
{
    // ゲーム時間の積算
    _totalTime += dt;
    
    // ゲームオーバーの判定
    if(_bird->getPositionY() < 0 || _bird->getPositionY() > WINSIZE.height || contactBlock())
    {
        // 画面から消えようとする、またはブロックと衝突
        // update関数を停止
        unscheduleUpdate();
        
        // 全ブロックの動きを停止
        for (auto node : this->getChildren())
        {
            if (node->getTag() == static_cast<int>(Tag::T_Block))
            {
                node->stopAllActions();
            }
            
        }
        
        // ゲームオーバー画面
        auto gameOver = Sprite::create("ui/gameover.png");
        gameOver->setTag(100);
        gameOver->setName("game_over");
        gameOver->setPosition(WINSIZE.width/2, WINSIZE.height/2 + 100);
        this->addChild(gameOver);
        
        // 戻るボタン
        auto backButtonImage = MenuItemImage::create("ui/back_normal.png", "ui/back_normal.png", CC_CALLBACK_1(GameLayer::backCallback, this));
        auto backButtonMenu = Menu::create(backButtonImage, NULL);
        backButtonMenu->setPosition(WINSIZE.width/2, WINSIZE.height/2 - 100);
        backButtonMenu->setTag(101);
        backButtonMenu->setName("back_button");
        this->addChild(backButtonMenu);
        
        // ステータスを変更
        _state = State::GameOver;
        
    }
    else
    {
        // キャラの位置を変更
        float time = _totalTime - _jumpingTime;
        float newY = (JUMP_V0 * time - GRAVITY * time * time / 2) * POSITION_RATE + _jumpPointY;
        _bird->setPositionY(newY);
    
        // 次ブロックの表示
        if (_totalTime > _nextBlockTime)
        {
            // 上ブロック
            auto upperBlock = Sprite::create("ui/block.png");
            upperBlock->setRotation(180);
            upperBlock->setPosition(Vec2(WINSIZE.width, WINSIZE.height/2 +600 ));
            upperBlock->setTag(static_cast<int>(Tag::T_Block));
            upperBlock->setName("UpperBlock");
            this->addChild(upperBlock);
            
            // 下ブロック
            auto lowerBlock = Sprite::create("ui/block.png");
            lowerBlock->setPosition(Vec2(WINSIZE.width, WINSIZE.height/2 -600 ));
            lowerBlock->setTag(static_cast<int>(Tag::T_Block));
            lowerBlock->setName("LowerBlock");
            this->addChild(lowerBlock);
            
            // ブロックを移動させる
            auto upperBlockMove = MoveBy::create(MOVING_TIME, Point((upperBlock->getContentSize().width + WINSIZE.width) * -1, 0));
            auto lowerBlockMove = MoveBy::create(MOVING_TIME, Point((lowerBlock->getContentSize().width + WINSIZE.width) * -1, 0));
            auto remove = RemoveSelf::create();
            auto upperBlockSeq = Sequence::create(upperBlockMove, remove, nullptr);
            auto lowerBlockSeq = Sequence::create(lowerBlockMove, remove, nullptr);
            upperBlock->runAction(upperBlockSeq);
            lowerBlock->runAction(lowerBlockSeq);
        
            // 次ブロックの時間を設定
            _nextBlockTime += INTERVAL_BLOCK_TIME;
        }
        
    }
}

// スタートボタンがタップされた時
void GameLayer::onTouchesBegan(const std::vector<Touch*>& touches, Event *event)
{
    if (_state == State::GameStart)
    {
        // スタート画面フレームアウト
        this->removeChildByName("start_button");
        
        // ステータスを変更する
        _state = State::Gaming;
        
        // 時間の初期化
        _totalTime = 0;
        _jumpingTime = 0;
        _nextBlockTime = INIT_BLOCK_TIME;
        
        // キャラクターの位置を保持
        _jumpPointY = _bird->getPositionY();
        
        // update関数を毎フレーム呼び出す
        scheduleUpdate();
    }
    else if (_state == State::Gaming)
    {
        // ペンギンの位置を保持
        _jumpPointY = _bird->getPositionY();
        
        // ジャンプ開始時間を保持
        _jumpingTime = _totalTime;
        
        // ジャンプアニメーションを行う
        auto jumpUp = RotateTo::create(0.3, -75);
        auto jumpDown = RotateTo::create(0.9, 75);
        auto seq = Sequence::create(jumpUp, jumpDown, nullptr);
        _bird->runAction(seq);
    }
}


// ブロック衝突チェック
bool GameLayer::contactBlock()
{
    // キャラクターの当たり判定
    auto birdRect = _bird->boundingBox();
    
    // ブロックとの衝突チェック
    for (auto node : this->getChildren())
    {
        if (node->getTag() == static_cast<int>(Tag::T_Block))
        {
            // ブロックの取得
            auto block = node;
            
            // ブロックのRectを取得
            auto blockRect = block->boundingBox();
            
            // 衝突チェック
            if (birdRect.intersectsRect(blockRect))
            {
                // 衝突
                return true;
            }
            
        }
    }
    
    return false;
}

// 戻るボタンタップイベント
void GameLayer::backCallback(cocos2d::Ref* sender)
{
    CCLOG("back");
    
    // 全ブロックを削除する
    while (true)
    {
        auto block = this->getChildByTag(static_cast<int>(Tag::T_Block));
        
        if (block)
        {
            block->removeFromParent();
        }
        else
        {
            break;
        }
    }
    
    // キャラクターを初期位置へ移動
    _bird->setPosition(WINSIZE.width/2 *0.6, WINSIZE.height/2);
    
    // キャラクターの角度を戻す
    _bird->setRotation(0);
    
    // ゲームオーバーと戻るボタンを消す
    // NOTICE: とりあえず
    this->removeChildByTag(100);
    this->removeChildByTag(101);
    
    // ステータスの変更
    _state = State::GameStart;
}