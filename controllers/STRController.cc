#include "STRController.h"

#include "HandlerActivityData.h"
#include "HandlerStatus.h"
#include "HandlerHTTPError.h"

void STRController::submitActivityData(const HttpRequestPtr &req,
                            std::function<void(const HttpResponsePtr &)> &&callback){

    auto json = req->getJsonObject();
    if (!json) {
        HandlerHTTPError err{400, "Invalid JSON"};
        callback(HttpResponse::newHttpJsonResponse(err.toJson()));
        return;
    }


    HandlerActivityData data;
    data.fromJson(*json);



    // TODO: validate and save to DB...
    /*
    *Here you would check rules:
    Is metadata.submissionDate a valid timestamp?
    Are GuestData.unitId and hostId present?
    Then insert into PostgreSQL using Drogon ORM:
    Mapper<ActivityData> mp(app().getDbClient());
    mp.insert(data);
     */

    HandlerStatus s;
    s.m_status = "created";
    auto resp = HttpResponse::newHttpJsonResponse(s.toJson());
    resp->setStatusCode(k201Created);
    callback(resp);

}

void STRController::submitListings(const HttpRequestPtr &req,
                        std::function<void(const HttpResponsePtr &)> &&callback){

}

void STRController::getAreas(const HttpRequestPtr &req,
                  std::function<void(const HttpResponsePtr &)> &&callback){

}

void STRController::downloadArea(const HttpRequestPtr &req,
                      std::function<void(const HttpResponsePtr &)> &&callback,
                      const std::string &id){

}