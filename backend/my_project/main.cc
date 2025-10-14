#include <drogon/drogon.h>
#include "Service/UserService.h"

int main() 
{
    // Настройка сервера ПЕРВОЙ
    drogon::app()
        .addListener("0.0.0.0", 6666)
        .loadConfigFile("../config.json");

    // Инициализация устройств после загрузки конфига
    drogon::app().registerBeginningAdvice([]() 
    {
        try 
        {
            auto dbClient = drogon::app().getDbClient();
            UserService userservice(dbClient);
            
            std::list<std::string> devices = {
                "9CC28570-30B9-0000-0000-000000000000",
                "device002", 
                "20220526-B48C-9DCA-727A-B48C9DCA727B"
            };
            userservice.clean_allowed_devices();
            userservice.allow_devices(devices);
            LOG_INFO << "Allowed devices initialized successfully";
        } 
        catch (const std::exception& e) 
        {
            LOG_ERROR << "Failed to initialize devices: " << e.what();
        }
    });
    
    drogon::app().run();
    return 0;
}