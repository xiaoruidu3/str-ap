#pragma once
#include <json/json.h>
#include <string>

class Metadata
{
public:
    std::string platform;
    std::string submissionDate;

    Json::Value additionalProps; // catch-all for any extra object properties

    Json::Value toJson() const
    {
        Json::Value json;
        if (!platform.empty())
            json["platform"] = platform;
        if (!submissionDate.empty())
            json["submissionDate"] = submissionDate;
        if (!additionalProps.isNull())
            json["additionalProp1"] = additionalProps;
        return json;
    }

    void fromJson(const Json::Value& json)
    {
        if (json.isMember("platform"))
            platform = json["platform"].asString();
        if (json.isMember("submissionDate"))
            submissionDate = json["submissionDate"].asString();
        if (json.isMember("additionalProp1"))
            additionalProps = json["additionalProp1"];
    }
};
