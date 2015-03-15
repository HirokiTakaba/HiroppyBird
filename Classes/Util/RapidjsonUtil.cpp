//
//  RapidjsonUtil.cpp
//  brainwars
//
//  Created by Kudo Takuma on 6/6/14.
//
//

#include "Utils/RapidjsonUtil.h"

namespace
{
    // エラー時返却用のNull値
    rapidjson::Value nullValue;
}

// ---------- 存在確認
// オブジェクトキーの存在確認
bool RapidjsonUtil::hasMember(const rapidjson::Value& json, const std::string& key)
{
    return json.IsObject() && json.HasMember(key.c_str());
};

// 配列インデックスの存在確認
bool RapidjsonUtil::hasMember(const rapidjson::Value& json, rapidjson::SizeType index)
{
    return json.IsArray() && index < json.Size();
};


// ---------- 配列系
// 配列かどうか
bool RapidjsonUtil::isArray(const rapidjson::Value& json)
{
    return json.IsArray();
}

bool RapidjsonUtil::isArray(const rapidjson::Value& json, const std::string& key)
{
    return RapidjsonUtil::hasMember(json, key) && json[key.c_str()].IsArray();
}

bool RapidjsonUtil::isArray(const rapidjson::Value& json, rapidjson::SizeType index)
{
    return RapidjsonUtil::hasMember(json, index) && json[index].IsArray();
}

// オブジェクトからの配列取得
const rapidjson::Value& RapidjsonUtil::getArray(const rapidjson::Value& json, const std::string& key)
{
    if (!RapidjsonUtil::isArray(json, key)) return nullValue;

    return json[key.c_str()];
}

// 配列からの配列取得
const rapidjson::Value& RapidjsonUtil::getArray(const rapidjson::Value& json, rapidjson::SizeType index)
{
    if (!RapidjsonUtil::isArray(json, index)) return nullValue;

    return json[index];
}


// ---------- オブジェクト系
// 配列かどうか
bool RapidjsonUtil::isObject(const rapidjson::Value& json)
{
    return json.IsObject();
}

bool RapidjsonUtil::isObject(const rapidjson::Value& json, const std::string& key)
{
    return RapidjsonUtil::hasMember(json, key) && json[key.c_str()].IsObject();
}

bool RapidjsonUtil::isObject(const rapidjson::Value& json, rapidjson::SizeType index)
{
    return RapidjsonUtil::hasMember(json, index) && json[index].IsObject();
}

// オブジェクトからのオブジェクト取得
const rapidjson::Value& RapidjsonUtil::getObject(const rapidjson::Value& json, const std::string& key)
{
    if (!RapidjsonUtil::isObject(json, key)) return nullValue;

    return json[key.c_str()];
}

// 配列からのオブジェクト取得
const rapidjson::Value& RapidjsonUtil::getObject(const rapidjson::Value& json, rapidjson::SizeType index)
{
    if (!RapidjsonUtil::isObject(json, index)) return nullValue;

    return json[index];
}


// ---------- int系
// intかどうか
bool RapidjsonUtil::isInt(const rapidjson::Value& json, const std::string& key)
{
    return RapidjsonUtil::hasMember(json, key) && json[key.c_str()].IsInt();
}

bool RapidjsonUtil::isInt(const rapidjson::Value& json, rapidjson::SizeType index)
{
    return RapidjsonUtil::hasMember(json, index) && json[index].IsInt();
}

// オブジェクトからのint取得
int RapidjsonUtil::getIntValue(const rapidjson::Value& json, const std::string& key, int defaultValue)
{
    if (!RapidjsonUtil::isInt(json, key)) return defaultValue;

    return json[key.c_str()].GetInt();
}

// 配列からのint取得
int RapidjsonUtil::getIntValue(const rapidjson::Value& json, rapidjson::SizeType index, int defaultValue)
{
    if (!RapidjsonUtil::isInt(json, index)) return defaultValue;

    return json[index].GetInt();
}


// ---------- uint系
// uintかどうか
bool RapidjsonUtil::isUInt(const rapidjson::Value& json, const std::string& key)
{
    return RapidjsonUtil::hasMember(json, key) && json[key.c_str()].IsUint();
}

bool RapidjsonUtil::isUInt(const rapidjson::Value& json, rapidjson::SizeType index)
{
    return RapidjsonUtil::hasMember(json, index) && json[index].IsUint();
}

// オブジェクトからのuint取得
unsigned RapidjsonUtil::getUIntValue(const rapidjson::Value& json, const std::string& key, unsigned defaultValue)
{
    if (!RapidjsonUtil::isUInt(json, key)) return defaultValue;

    return json[key.c_str()].GetUint();
}

// 配列からのuint取得
unsigned RapidjsonUtil::getUIntValue(const rapidjson::Value& json, rapidjson::SizeType index, unsigned defaultValue)
{
    if (!RapidjsonUtil::isUInt(json, index)) return defaultValue;

    return json[index].GetUint();
}


// ---------- bool系
// boolかどうか
bool RapidjsonUtil::isBool(const rapidjson::Value& json, const std::string& key)
{
    return RapidjsonUtil::hasMember(json, key) && json[key.c_str()].IsBool();
}

bool RapidjsonUtil::isBool(const rapidjson::Value& json, rapidjson::SizeType index)
{
    return RapidjsonUtil::hasMember(json, index) && json[index].IsBool();
}

// オブジェクトからのbool取得
bool RapidjsonUtil::getBoolValue(const rapidjson::Value& json, const std::string& key, bool defaultValue)
{
    if (!RapidjsonUtil::isBool(json, key)) return defaultValue;

    return json[key.c_str()].GetBool();
}

// 配列からのbool取得
bool RapidjsonUtil::getBoolValue(const rapidjson::Value& json, rapidjson::SizeType index, bool defaultValue)
{
    if (!RapidjsonUtil::isBool(json, index)) return defaultValue;

    return json[index].GetBool();
}


// ---------- double系
// doubleかどうか
bool RapidjsonUtil::isDouble(const rapidjson::Value& json, const std::string& key)
{

    // 値のキリがよくて、jsonの値が整数で来てしまった場合を考慮してintもOKとする
    return RapidjsonUtil::hasMember(json, key) && (json[key.c_str()].IsDouble() || json[key.c_str()].IsInt());
}

bool RapidjsonUtil::isDouble(const rapidjson::Value& json, rapidjson::SizeType index)
{

    // 値のキリがよくて、jsonの値が整数で来てしまった場合を考慮してintもOKとする
    return RapidjsonUtil::hasMember(json, index) && (json[index].IsDouble() || json[index].IsInt());
}

// オブジェクトからのdouble取得
double RapidjsonUtil::getDoubleValue(const rapidjson::Value& json, const std::string& key, double defaultValue)
{
    if (!RapidjsonUtil::isDouble(json, key)) return defaultValue;

    // 値のキリが良くてdoubleとして取得できない時はintとして取得する
    return (json[key.c_str()].IsDouble())?json[key.c_str()].GetDouble():json[key.c_str()].GetInt();
}

// 配列からのdouble取得
double RapidjsonUtil::getDoubleValue(const rapidjson::Value& json, rapidjson::SizeType index, double defaultValue)
{
    if (!RapidjsonUtil::isDouble(json, index)) return defaultValue;

    // 値のキリが良くてdoubleとして取得できない時はintとして取得する
    return (json[index].IsDouble())?json[index].GetDouble():json[index].GetInt();
}


// ---------- string系
// stringかどうか
bool RapidjsonUtil::isString(const rapidjson::Value& json, const std::string& key)
{
    return RapidjsonUtil::hasMember(json, key) && json[key.c_str()].IsString();
}

bool RapidjsonUtil::isString(const rapidjson::Value& json, rapidjson::SizeType index)
{
    return RapidjsonUtil::hasMember(json, index) && json[index].IsString();
}

// オブジェクトからのstring取得
std::string RapidjsonUtil::getStringValue(const rapidjson::Value& json, const std::string& key, const std::string& defaultValue)
{
    if (!RapidjsonUtil::isString(json, key)) return defaultValue;

    return json[key.c_str()].GetString();
}

// 配列からのstring取得
std::string RapidjsonUtil::getStringValue(const rapidjson::Value& json, rapidjson::SizeType index, const std::string& defaultValue)
{
    if (!RapidjsonUtil::isString(json, index)) return defaultValue;

    return json[index].GetString();
}
