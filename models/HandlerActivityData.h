#pragma once
#include <json/json.h>
#include "Metadata.h"
#include "GuestData.h"


class HandlerActivityData {
public:
    std::vector<GuestData> data;
    Metadata metadata;

    Json::Value toJson() const {
        Json::Value json;
        for (auto &g : data) {
            json["data"].append(g.toJson());
        }
        json["metadata"] = metadata.toJson();
        return json;
    }

    void fromJson(const Json::Value &json) {
        if (json.isMember("data")) {
            for (auto &item : json["data"]) {
                GuestData g;
                g.fromJson(item);
                data.push_back(g);
            }
        }
        if (json.isMember("metadata")) {
            metadata.fromJson(json["metadata"]);
        }
    }

};




