#include <drogon/drogon.h>

int main() {
    //Set HTTP listener address and port
    //drogon::app().addListener("0.0.0.0",5000);
    
    //Load config file
    drogon::app().loadConfigFile("../config.json");
    static std::shared_ptr<drogon::orm::DbClient> newMysqlClient('host=localhost dbname=apl connect_timeout=10 password=password', 1);
    auto clientPtr = drogon::app().getDbClient();
clientPtr->execSqlAsync("select * from users",
                            [](const drogon::orm::Result &result) {
                                std::cout << result.size() << " rows selected!" << std::endl;
                                int i = 0;
                                for (auto row : result)
                                {
                                    std::cout << i++ << ": user name is " << row["name"].as<std::string>() << std::endl;
                                }
                            },
                            [](const std::exception &e) {
                                std::cerr << "error:" << e.what() << std::endl;
                            },
                            "default");
    
    //Run HTTP framework,the method will block in the internal event loop
    drogon::app().run();

    return 0;
}
