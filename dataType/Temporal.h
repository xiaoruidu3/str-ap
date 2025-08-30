#pragma once
#include <json/json.h>
#include <string>

class Temporal {
public:
    std::string startDateTime;
    std::string endDateTime;

    Json::Value toJson() const {
        Json::Value json;
        if (!startDateTime.empty()) json["startDateTime"] = startDateTime;
        if (!endDateTime.empty()) json["endDateTime"] = endDateTime;
        return json;
    }

    void fromJson(const Json::Value &json) {
        if (json.isMember("startDateTime"))
            startDateTime = json["startDateTime"].asString();
        if (json.isMember("endDateTime"))
            endDateTime = json["endDateTime"].asString();
    }
};
