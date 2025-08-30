#include "HealthController.h"


void HealthController::ping(const HttpRequestPtr &req,
                            std::function<void(const HttpResponsePtr &)> &&callback) {
    Json::Value result;
    result["status"] = "ok";
    auto resp = HttpResponse::newHttpJsonResponse(result);
    callback(resp);
}