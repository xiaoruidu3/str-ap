#pragma once
#include <json/json.h>


class HandlerHTTPError {

public:
    int code{};
    std::string message;

    Json::Value toJson() const {
        Json::Value json;
        json["code"] = code;
        json["message"] = message;
        return json;
    }

    void fromJson(const Json::Value &json) {
        if (json.isMember("code")) code = json["code"].asInt();
        if (json.isMember("message")) message = json["message"].asString();
    }

};


