#include "version.h"

// Add definition of your processing function here
void version::get_name( const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback, int version_id) const {
    std::string sql = "SELECT name FROM version WHERE id = $1;";
    try{
        auto futureObject = 
            drogon::app()
                .getDbClient("default")
                ->execSqlAsyncFuture(sql, version_id);

        if(std::future_status::timeout == futureObject.wait_for(std::chrono::seconds(3))){
            Json::Value output;
            output["state"] = "timeout";
            callback(HttpResponse::newHttpJsonResponse(output));
            return;
        }
        else{
            auto result = futureObject.get();

            if(0 >= result.size()){
                Json::Value output;
                output["state"] = "error";
                callback(HttpResponse::newHttpJsonResponse(output));
            }

            std::string name = result[0]["name"].as<std::string>();
            Json::Value output;
            output["state"] = "ok";
            output["name"] = name;
            callback(HttpResponse::newHttpJsonResponse(output));
        }
    }
    catch(const drogon::orm::DrogonDbException &e){
        std::cerr << e.base().what() << '\n';
        Json::Value output;
        output["state"] = "error";
        callback(HttpResponse::newHttpJsonResponse(output));
    }
}
void version::latest( const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback) const {
    std::string sql = "SELECT id, name FROM version ORDER BY id DESC LIMIT 1;";
    try{
        auto futureObject = 
            drogon::app()
                .getDbClient("default")
                ->execSqlAsyncFuture(sql);

        if(std::future_status::timeout == futureObject.wait_for(std::chrono::seconds(3))){
            Json::Value output;
            output["state"] = "timeout";
            callback(HttpResponse::newHttpJsonResponse(output));
            return;
        }
        else{
            auto result = futureObject.get();

            if(0 >= result.size()){
                Json::Value output;
                output["state"] = "error";
                callback(HttpResponse::newHttpJsonResponse(output));
            }

            int version_id = result[0]["id"].as<int>();
            std::string name = result[0]["name"].as<std::string>();
            Json::Value output;
            output["state"] = "ok";
            output["version_id"] = version_id;
            output["name"] = name;
            callback(HttpResponse::newHttpJsonResponse(output));
        }
    }
    catch(const drogon::orm::DrogonDbException &e){
        std::cerr << e.base().what() << '\n';
        Json::Value output;
        output["state"] = "error";
        callback(HttpResponse::newHttpJsonResponse(output));
    }
}