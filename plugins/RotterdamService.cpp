#include "RotterdamService.h"


void RotterdamService::initAndStart(const Json::Value& config)
{
    dbName_ = config.get("dbClientName", "strapCA1DB").asString();
    db_ = drogon::app().getDbClient(dbName_);
    if (!db_) {
        LOG_ERROR << "db_ is null!";
    } else {
        LOG_INFO << "db_ created for " << dbName_;
    }
    LOG_INFO << "UserService started with db=" << dbName_;
}


void RotterdamService::shutdown()
{
    LOG_INFO << "RotterdamService shutting down";
}

void RotterdamService::getUserById(
    std::string unitid, std::function<void(Json::Value)> callback,
    std::function<void(const drogon::orm::DrogonDbException&)> errCallback)
{

    try {
        auto r = db_->execSqlSync(
            "SELECT unitid, street, city, postalcode, country, startdatetime, enddatetime, numberofguests, countryofguests, areaid FROM rotterdam_bookings WHERE unitid=$1",
            unitid);

        Json::Value result;
        if (!r.empty()) {
            result["unitid"] = r[0]["unitid"].as<std::string>();
            result["street"] = r[0]["street"].as<std::string>();
            result["city"]   = r[0]["city"].as<std::string>();
            result["postalcode"] = r[0]["postalcode"].as<std::string>();
            result["country"] = r[0]["country"].as<std::string>();
            result["startdatetime"]   = r[0]["startdatetime"].as<std::string>();
            result["enddatetime"] = r[0]["enddatetime"].as<std::string>();
            result["numberofguests"] = r[0]["numberofguests"].as<int>();
            result["countryofguests"]   = r[0]["countryofguests"].as<std::string>();
            result["areaid"] = r[0]["areaid"].as<std::string>();
        }

        callback(result);
    }
    catch (const drogon::orm::DrogonDbException &e) {
        errCallback(e);
        std::cout << "err: " << e.base().what() << std::endl;
    }

}
