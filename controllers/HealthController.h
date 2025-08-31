#pragma once

#include <drogon/HttpController.h>


class HealthController : public drogon::HttpController<HealthController>
{
  public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(HealthController::ping, "/api/v0/ping", drogon::Get);
    METHOD_LIST_END
    void ping(const drogon::HttpRequestPtr& req, std::function<void (const drogon::HttpResponsePtr &)> &&callback);

};
