#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

class score : public drogon::HttpController<score>
{
  public:
    METHOD_LIST_BEGIN
    // use METHOD_ADD to add your custom processing function here;
    // METHOD_ADD(score::get, "/{2}/{1}", Get); // path is /score/{arg2}/{arg1}
    // METHOD_ADD(score::your_method_name, "/{1}/{2}/list", Get); // path is /score/{arg1}/{arg2}/list
    // ADD_METHOD_TO(score::your_method_name, "/absolute/path/{1}/{2}/list", Get); // path is /absolute/path/{arg1}/{arg2}/list
    METHOD_ADD(score::add, "/add", Post);
    METHOD_ADD(score::lanking, "/lanking/{1}", Get);

    METHOD_LIST_END
    // your declaration of processing function maybe like this:
    // void get(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, int p1, std::string p2);
    // void your_method_name(const HttpRequestPtr& req, std::function<void (const HttpResponsePtr &)> &&callback, double p1, int p2) const;
    void add( const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback ) const;
    void lanking( const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback, int version_id ) const;
};
