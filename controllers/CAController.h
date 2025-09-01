#pragma once

#include <drogon/HttpController.h>


class CAController : public drogon::HttpController<CAController>
{
public:
    METHOD_LIST_BEGIN
        ADD_METHOD_TO(CAController::getActivityData, "/api/v0/ca/activity-data", drogon::Get);
        ADD_METHOD_TO(CAController::getListings, "/api/v0/ca/listings", drogon::Get);
        ADD_METHOD_TO(CAController::uploadShapefile, "/api/v0/str/area", drogon::Post); // tagged ca in swagger
    METHOD_LIST_END


    void getActivityData(const drogon::HttpRequestPtr& req,
                         std::function<void(const drogon::HttpResponsePtr&)>&& callback);

    void getListings(const drogon::HttpRequestPtr& req,
                     std::function<void(const drogon::HttpResponsePtr&)>&& callback);

    void uploadShapefile(const drogon::HttpRequestPtr& req,
                         std::function<void(const drogon::HttpResponsePtr&)>&& callback);
};
