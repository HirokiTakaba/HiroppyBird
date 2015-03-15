//
//  SocketIOManager.cpp
//  HiroppyBird
//
//  Created by Hiroki Takaba on 2015/03/08.
//
//

#include "SocketIOManager.h"

// 定数
const std::string SocketIOManager::HOST = "ws://socket-dev.brainwarsapp.com:443";

// クラスメソッド
// マネージャ取得
SocketIOManager* SocketIOManager::getInstance()
{
//    SocketIOManager manager = SocketIO::getInstance();;
//
    return nullptr;
}

SocketIOManager::SocketIOManager()
: socketIOClient(nullptr)
, delegate(nullptr)
{}

// Socket Connecrt
bool SocketIOManager::connect()
{
    if(this->isConnect())
    {
        return false;
    }
    
    // Socket接続
    SocketIO::connect(HOST, *this);
    
    return true;
}

void SocketIOManager::disconnect()
{
    if (this->isConnect())
    {
        this->socketIOClient->disconnect();
    }
}

bool SocketIOManager::isConnect()
{
    return this->socketIOClient != nullptr;
}

// デリゲート設定
void SocketIOManager::setDelegate(SocketIODelegate* delegate)
{
    this->delegate = delegate;
}

// デリゲート解除
void SocketIOManager::clearDelegate()
{
    this->delegate = nullptr;
}