//
//  RapidjsonUtil.h
//  brainwars
//
//  Created by Kudo Takuma on 6/6/14.
//
//

#ifndef __RAPIDJSON_UTIL_H__
#define __RAPIDJSON_UTIL_H__

#include <iostream>
#include "document.h"
#include "stringbuffer.h"
#include "writer.h"

// rapidjsonに関するユーティリティ
namespace RapidjsonUtil
{
// ---------- メソッド

    // 存在確認
    bool hasMember(const rapidjson::Value& json, const std::string& key);
    bool hasMember(const rapidjson::Value& json, rapidjson::SizeType index);

    // 配列系
    bool                    isArray(const rapidjson::Value& json);
    bool                    isArray(const rapidjson::Value& json, const std::string& key);
    bool                    isArray(const rapidjson::Value& json, rapidjson::SizeType index);
    const rapidjson::Value& getArray(const rapidjson::Value& json, const std::string& key);
    const rapidjson::Value& getArray(const rapidjson::Value& json, rapidjson::SizeType index);

    // オブジェクト系
    bool                    isObject(const rapidjson::Value& json);
    bool                    isObject(const rapidjson::Value& json, const std::string& key);
    bool                    isObject(const rapidjson::Value& json, rapidjson::SizeType index);
    const rapidjson::Value& getObject(const rapidjson::Value& json, const std::string& key);
    const rapidjson::Value& getObject(const rapidjson::Value& json, rapidjson::SizeType index);

    // int系
    bool isInt(const rapidjson::Value& json, const std::string& key);
    bool isInt(const rapidjson::Value& json, rapidjson::SizeType index);
    int  getIntValue(const rapidjson::Value& json, const std::string& key, int defaultValue=0);
    int  getIntValue(const rapidjson::Value& json, rapidjson::SizeType index, int defaultValue=0);

    // uint系
    bool     isUInt(const rapidjson::Value& json, const std::string& key);
    bool     isUInt(const rapidjson::Value& json, rapidjson::SizeType index);
    unsigned getUIntValue(const rapidjson::Value& json, const std::string& key, unsigned defaultValue=0);
    unsigned getUIntValue(const rapidjson::Value& json, rapidjson::SizeType index, unsigned defaultValue=0);

    // bool系
    bool isBool(const rapidjson::Value& json, const std::string& key);
    bool isBool(const rapidjson::Value& json, rapidjson::SizeType index);
    bool getBoolValue(const rapidjson::Value& json, const std::string& key, bool defaultValue=false);
    bool getBoolValue(const rapidjson::Value& json, rapidjson::SizeType index, bool defaultValue=false);

    // double系
    bool   isDouble(const rapidjson::Value& json, const std::string& key);
    bool   isDouble(const rapidjson::Value& json, rapidjson::SizeType index);
    double getDoubleValue(const rapidjson::Value& json, const std::string& key, double defaultValue=0);
    double getDoubleValue(const rapidjson::Value& json, rapidjson::SizeType index, double defaultValue=0);

    // 文字列系
    bool        isString(const rapidjson::Value& json, const std::string& key);
    bool        isString(const rapidjson::Value& json, rapidjson::SizeType index);
    std::string getStringValue(const rapidjson::Value& json, const std::string& key, const std::string& defaultValue="");
    std::string getStringValue(const rapidjson::Value& json, rapidjson::SizeType index, const std::string& defaultValue="");
};

#endif // __RAPIDJSON_UTIL_H__
