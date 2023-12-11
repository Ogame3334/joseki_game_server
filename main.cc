#include <drogon/drogon.h>
#include <chrono>

using namespace std::chrono_literals;

int main() {
    //Set HTTP listener address and port
    drogon::app().addListener("0.0.0.0",49154);
    //Load config file
    drogon::app().loadConfigFile("../config.json");
    //Run HTTP framework,the method will block in the internal event loop
    drogon::app().enableSession(1h).run();
    return 0;
}
