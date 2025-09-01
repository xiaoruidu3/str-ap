#pragma once

#include <drogon/plugins/Plugin.h>
#include <drogon/orm/DbClient.h>
#include <drogon/drogon.h>

class AmsterdamService : public drogon::Plugin<AmsterdamService>
{
public:
    AmsterdamService() = default;
    /// This method must be called by drogon to initialize and start the plugin.
    /// It must be implemented by the user.
    void initAndStart(const Json::Value& config) override;

    /// This method must be called by drogon to shutdown the plugin.
    /// It must be implemented by the user.
    void shutdown() override;

    // Example helper
    void getUserByAreaId(std::string areaid, std::function<void(Json::Value)> callback,
                         std::function<void(const drogon::orm::DrogonDbException&)> errCallback);

private:
    std::string dbName_;
    drogon::orm::DbClientPtr db_;
};
