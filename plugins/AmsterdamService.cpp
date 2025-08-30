#include "AmsterdamService.h"


void AmsterdamService::initAndStart(const Json::Value &config)
{
    dbName_ = config.get("dbClientName", "strapCA2DB").asString();
    db_ = drogon::app().getDbClient(dbName_);
    LOG_INFO << "UserService started with db=" << dbName_;

}


void AmsterdamService::shutdown(){
   LOG_INFO << "AmsterdamService shutting down";
}


void AmsterdamService::getUserByAreaId(std::string areaid, std::function<void(Json::Value)> callback, std::function<void(const drogon::orm::DrogonDbException&)> errCallback)
{

    try {
        auto r = db_->execSqlSync(
            "SELECT unitid, street, city, postalcode, country, startdatetime, enddatetime, numberofguests, countryofguests, areaid FROM amsterdam_bookings WHERE areaid=$1",
            areaid);

        Json::Value results(Json::arrayValue);
        for(std::size_t i = 0; i < r.size(); ++i)
        {
            Json::Value row;
            row["unitid"] = r[0]["unitid"].as<std::string>();
            row["street"] = r[0]["street"].as<std::string>();
            row["city"]   = r[0]["city"].as<std::string>();
            row["postalcode"] = r[0]["postalcode"].as<std::string>();
            row["country"] = r[0]["country"].as<std::string>();
            row["startdatetime"]   = r[0]["startdatetime"].as<std::string>();
            row["enddatetime"] = r[0]["enddatetime"].as<std::string>();
            row["numberofguests"] = r[0]["numberofguests"].as<int>();
            row["countryofguests"]   = r[0]["countryofguests"].as<std::string>();
            row["areaid"] = r[0]["areaid"].as<std::string>();
            results.append(row);
        }

        callback(results);
    }
    catch (const drogon::orm::DrogonDbException &e) {
        errCallback(e);
        std::cout << "err: " << e.base().what() << std::endl;
    }

}
