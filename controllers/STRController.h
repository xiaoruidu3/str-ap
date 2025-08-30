#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class STRController : public drogon::HttpController<STRController>
{
  public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(STRController::submitActivityData, "/api/v0/str/activity-data", Post);
    ADD_METHOD_TO(STRController::submitListings, "/api/v0/str/listings", Post);
    ADD_METHOD_TO(STRController::getAreas, "/api/v0/str/area", Get);
    ADD_METHOD_TO(STRController::downloadArea, "/api/v0/str/area/{id}", Get);
    METHOD_LIST_END
    

    void submitActivityData(const HttpRequestPtr &req,
                            std::function<void(const HttpResponsePtr &)> &&callback);

    void submitListings(const HttpRequestPtr &req,
                        std::function<void(const HttpResponsePtr &)> &&callback);

    void getAreas(const HttpRequestPtr &req,
                  std::function<void(const HttpResponsePtr &)> &&callback);

    void downloadArea(const HttpRequestPtr &req,
                      std::function<void(const HttpResponsePtr &)> &&callback,
                      const std::string &id);
};
