//
//  SocketIOManager.h
//  HiroppyBird
//
//  Created by Hiroki Takaba on 2015/03/08.
//
//

#ifndef __HiroppyBird__SocketIOManager__
#define __HiroppyBird__SocketIOManager__

#include <stdio.h>
#include "network/SocketIO.h"

using namespace cocos2d::network;

// SocketIOの通信を管理するマネージャー
class SocketIOManager : public SocketIO::SIODelegate
{
// ---------- クラス内クラス・デリゲート
public:
    // SocketIOデリゲート
    class SocketIODelegate
    {
    public:
        virtual void sioConnect() = 0; // 接続
        virtual void sioClose()   = 0; // クローズ
        virtual void sioError()   = 0; // エラー
    };
    
private:
    static const std::string HOST;

public:
    static SocketIOManager* getInstance(); // マネージャー取得
    static void destroySocketIOInstance(); // インスタンスの削除
    
private:
    SIOClient* socketIOClient; // クライアント
    SocketIODelegate* delegate; // デリゲート

public:
    ~SocketIOManager(); // デストラクタ
    
    bool connect(); // Socket接続
    void disconnect(); // Socket切断
    bool isConnect(); // 接続中か
    void setDelegate(SocketIODelegate* delegate); // デリゲートを設定
    void clearDelegate(); // デリゲート解除

private:
    SocketIOManager(); // コンストラクタ
    SocketIOManager(const SocketIOManager &rhs);              // コピーコンストラクタ
    SocketIOManager& operator = (const SocketIOManager& rhs); // 代入演算子
};

#endif /* defined(__HiroppyBird__SocketIOManager__) */
