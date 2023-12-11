#include "score.h"
#include <cstdlib>

// Add definition of your processing function here
void score::add( const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) const {
    auto pass = req->getHeader("pass");
    auto server_pass = std::getenv("HEADER_PASS");
    if(not (server_pass == pass)){
        Json::Value output;
        output["state"] = "error";
        callback(HttpResponse::newHttpJsonResponse(output));
    }
    
    Json::Reader reader;
    Json::Value ret;
    
    reader.parse(std::string(req->getBody()), ret);

    std::string sql = "INSERT into score (version_id, name, score) values ($1, $2, $3)";
    try{
        int version_id = ret["version_id"].asInt();
        std::string name = ret["name"].asString();
        int score = ret["score"].asInt();
        auto futureObject = 
            drogon::app()
                .getDbClient("default")
                ->execSqlAsyncFuture(sql, version_id, name, score);

        if(std::future_status::timeout == futureObject.wait_for(std::chrono::seconds(3))){
            Json::Value output;
            output["state"] = "timeout";
            callback(HttpResponse::newHttpJsonResponse(output));
        }
        else{
            Json::Value output;
            output["state"] = "ok";
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

void score::lanking( const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback, int version_id) const {
    Json::Reader reader;
    Json::Value ret;
    
    reader.parse(std::string(req->getBody()), ret);

    std::string sql = "SELECT name, score FROM score WHERE version_id = $1 ORDER BY score DESC LIMIT 20;";
    try{
        auto futureObject = 
            drogon::app()
                .getDbClient("default")
                ->execSqlAsyncFuture(sql, version_id);

        if(std::future_status::timeout == futureObject.wait_for(std::chrono::seconds(3))){
            Json::Value output;
            output["state"] = "timeout";
            callback(HttpResponse::newHttpJsonResponse(output));
        }
        else{
            auto result = futureObject.get();


            Json::Value output;
            output["state"] = "ok";
            if(0 >= result.size()){
                output["lanking"] = Json::nullValue;
            }
            else{
                for(int i = 0; i < result.size(); i++){
                    Json::Value ret;
                    ret["name"] = result[i]["name"].as<std::string>();
                    ret["score"] = result[i]["score"].as<int>();
                    output["lanking"][i] = ret;
                }
            }
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