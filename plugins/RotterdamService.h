#pragma once

#include <drogon/plugins/Plugin.h>
#include <drogon/orm/DbClient.h>
#include <drogon/drogon.h>
#include <drogon/orm/Exception.h>


class RotterdamService : public drogon::Plugin<RotterdamService>
{
public:
    RotterdamService() = default;
    /// This method must be called by drogon to initialize and start the plugin.
    /// It must be implemented by the user.
    void initAndStart(const Json::Value& config) override;
    /// This method must be called by drogon to shutdown the plugin.
    /// It must be implemented by the user.
    void shutdown() override;


    // Example helper
    void getUserById(std::string unitid, std::function<void(Json::Value)> callback,
                     std::function<void(const drogon::orm::DrogonDbException&)> errCallback);

private:
    std::string dbName_;
    drogon::orm::DbClientPtr db_;
};
