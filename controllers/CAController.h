#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class CAController : public drogon::HttpController<CAController>
{
  public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(CAController::getActivityData, "/api/v0/ca/activity-data", Get);
    ADD_METHOD_TO(CAController::getListings, "/api/v0/ca/listings", Get);
    ADD_METHOD_TO(CAController::uploadShapefile, "/api/v0/str/area", Post); // tagged ca in swagger
    METHOD_LIST_END


    void getActivityData(const HttpRequestPtr &req,
                     std::function<void(const HttpResponsePtr &)> &&callback);

    void getListings(const HttpRequestPtr &req,
                     std::function<void(const HttpResponsePtr &)> &&callback);

    void uploadShapefile(const HttpRequestPtr &req,
                         std::function<void(const HttpResponsePtr &)> &&callback);
};
