#pragma once

#include <json/json.h>

class HandlerStatus
{
public:
    std::string m_status;

    // Serialize to JSON
    Json::Value toJson() const
    {
        Json::Value json;
        json["status"] = m_status;
        return json;
    }

    // Populate from JSON
    void fromJson(const Json::Value& json)
    {
        if (json.isMember("status"))
        {
            m_status = json["status"].asString();
        }
    }
};
