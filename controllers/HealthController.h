#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class HealthController : public drogon::HttpController<HealthController>
{
  public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(HealthController::ping, "/api/v0/ping", Get);
    METHOD_LIST_END
    void ping(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback);

};
