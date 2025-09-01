#include "STRController.h"

#include <AmsterdamService.h>

#include "HandlerActivityData.h"
#include "HandlerStatus.h"
#include "HandlerHTTPError.h"

void STRController::submitActivityData(const drogon::HttpRequestPtr& req,
                                       std::function<void(
                                           const drogon::HttpResponsePtr&)>&&
                                       callback) {
  auto json = req->getJsonObject();
  if (!json) {
    HandlerHTTPError err{400, "Invalid JSON"};
    callback(drogon::HttpResponse::newHttpJsonResponse(err.toJson()));
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
  auto resp = drogon::HttpResponse::newHttpJsonResponse(s.toJson());
  resp->setStatusCode(drogon::k201Created);
  callback(resp);
}

void STRController::submitListings(const drogon::HttpRequestPtr& req,
                                   std::function<void(
                                       const drogon::HttpResponsePtr&)>&&
                                   callback) {}

void STRController::getAreas(const drogon::HttpRequestPtr& req,
                             std::function<void(const drogon::HttpResponsePtr&)>
                             && callback) {}

void STRController::downloadArea(const drogon::HttpRequestPtr& req,
                                 std::function<void(
                                     const drogon::HttpResponsePtr&)>&&
                                 callback,
                                 const std::string& id) {}


void STRController::getRotterdamTestInfo(const drogon::HttpRequestPtr& req,
                                         std::function<void(
                                             const drogon::HttpResponsePtr&)>&&
                                         callback,
                                         const std::string& unitid) {
  auto db = drogon::app().getPlugin<RotterdamService>();

  db->getUserById(unitid, [callback](Json::Value user) {
                    std::cout << "SUCCESS handler" << std::endl;
                    auto res = drogon::HttpResponse::newHttpJsonResponse(user);
                    callback(res);
                  },

                  [callback](const drogon::orm::DrogonDbException& e) {
                    std::cout << "ERROR handler: " << e.base().what() <<
                        std::endl;
                    auto res = drogon::HttpResponse::newHttpResponse();
                    res->setStatusCode(drogon::k500InternalServerError);
                    res->setBody(std::string("DB Error: ") + e.base().what());
                    callback(res);
                  }
      );
}


void STRController::getAmsterdamTestInfo(const drogon::HttpRequestPtr& req,
                                         std::function<void(
                                             const drogon::HttpResponsePtr&)>&&
                                         callback,
                                         const std::string& areaid) {
  auto db = drogon::app().getPlugin<AmsterdamService>();

  db->getUserByAreaId(areaid, [callback](Json::Value user) {
                        std::cout << "SUCCESS handler" << std::endl;
                        auto res = drogon::HttpResponse::newHttpJsonResponse(
                            user);
                        callback(res);
                      },

                      [callback](const drogon::orm::DrogonDbException& e) {
                        std::cout << "ERROR handler: " << e.base().what() <<
                            std::endl;
                        auto res = drogon::HttpResponse::newHttpResponse();
                        res->setStatusCode(drogon::k500InternalServerError);
                        res->setBody(
                            std::string("DB Error: ") + e.base().what());
                        callback(res);
                      }
      );
}