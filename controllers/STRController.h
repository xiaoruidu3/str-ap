#pragma once

#include <drogon/HttpController.h>
#include "RotterdamService.h"


class STRController : public drogon::HttpController<STRController>
{
  public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(STRController::submitActivityData, "/api/v0/str/activity-data", drogon::Post);
    ADD_METHOD_TO(STRController::submitListings, "/api/v0/str/listings", drogon::Post);
    ADD_METHOD_TO(STRController::getAreas, "/api/v0/str/area", drogon::Get);
    ADD_METHOD_TO(STRController::downloadArea, "/api/v0/str/area/{id}", drogon::Get);
    ADD_METHOD_TO(STRController::getRotterdamTestInfo, "/api/v0/str/rotterdam/{unitid}", drogon::Get, "JwtAuth0Filter");
    ADD_METHOD_TO(STRController::getAmsterdamTestInfo, "/api/v0/str/amsterdam/{areaid}", drogon::Get, "JwtAuth0Filter");
    METHOD_LIST_END
    

    void submitActivityData(const drogon::HttpRequestPtr &req,
                            std::function<void(const drogon::HttpResponsePtr &)> &&callback);

    void submitListings(const drogon::HttpRequestPtr &req,
                        std::function<void(const drogon::HttpResponsePtr &)> &&callback);

    void getAreas(const drogon::HttpRequestPtr &req,
                  std::function<void(const drogon::HttpResponsePtr &)> &&callback);

    void downloadArea(const drogon::HttpRequestPtr &req,
                      std::function<void(const drogon::HttpResponsePtr &)> &&callback,
                      const std::string &id);

    void getRotterdamTestInfo(const drogon::HttpRequestPtr &req,
                      std::function<void(const drogon::HttpResponsePtr &)> &&callback,
                      const std::string &unitid);


    void getAmsterdamTestInfo(const drogon::HttpRequestPtr &req,
                      std::function<void(const drogon::HttpResponsePtr &)> &&callback,
                      const std::string &unitid);

};
