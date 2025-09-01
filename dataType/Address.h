#pragma once
#include <json/json.h>
#include <string>

class Address
{
public:
    std::string city;
    std::string country;
    std::string postalCode;
    std::string street;

    Json::Value toJson() const
    {
        Json::Value json;
        if (!city.empty()) json["city"] = city;
        if (!country.empty()) json["country"] = country;
        if (!postalCode.empty()) json["postalCode"] = postalCode;
        if (!street.empty()) json["street"] = street;
        return json;
    }

    void fromJson(const Json::Value& json)
    {
        if (json.isMember("city")) city = json["city"].asString();
        if (json.isMember("country")) country = json["country"].asString();
        if (json.isMember("postalCode")) postalCode = json["postalCode"].asString();
        if (json.isMember("street")) street = json["street"].asString();
    }
};
