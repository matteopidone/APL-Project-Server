#include <drogon/drogon.h>

int main() {
    //Set HTTP listener address and port
    //drogon::app().addListener("0.0.0.0",5000);
    
    //Load config file
    drogon::app().loadConfigFile("../config.json");
    
    //Run HTTP framework,the method will block in the internal event loop
    drogon::app().run();
    auto clientPtr = drogon::app().getDbClient("Matteo");
    return 0;
}
