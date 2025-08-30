#pragma once
#include <json/json.h>
#include <string>
#include <vector>
#include "Address.h"
#include "Temporal.h"

class GuestData {
public:
    std::string unitId;
    std::string hostId;
    std::string areaId;
    int numberOfGuests{};
    std::vector<std::string> countryOfGuests;
    Address address;
    Temporal temporal;

    Json::Value toJson() const {
        Json::Value json;
        json["unitId"] = unitId;
        if (!hostId.empty()) json["hostId"] = hostId;
        if (!areaId.empty()) json["areaId"] = areaId;
        if (numberOfGuests > 0) json["numberOfGuests"] = numberOfGuests;

        for (const auto &c : countryOfGuests)
            json["countryOfGuests"].append(c);

        json["address"] = address.toJson();
        json["temporal"] = temporal.toJson();

        return json;
    }

    void fromJson(const Json::Value &json) {
        if (json.isMember("unitId"))
            unitId = json["unitId"].asString();
        if (json.isMember("hostId"))
            hostId = json["hostId"].asString();
        if (json.isMember("areaId"))
            areaId = json["areaId"].asString();
        if (json.isMember("numberOfGuests"))
            numberOfGuests = json["numberOfGuests"].asInt();
        if (json.isMember("countryOfGuests")) {
            for (auto &item : json["countryOfGuests"])
                countryOfGuests.push_back(item.asString());
        }
        if (json.isMember("address"))
            address.fromJson(json["address"]);
        if (json.isMember("temporal"))
            temporal.fromJson(json["temporal"]);
    }
};
