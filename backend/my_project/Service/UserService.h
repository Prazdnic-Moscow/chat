#include <drogon/drogon.h>
#include <drogon/orm/DbClient.h>
#include <json/json.h>
#include <drogon/HttpController.h>
#include "../Repository/UserRepository.h"
#include "../Models/User.h"
#include <list>
using namespace drogon;

class UserService
{
    public:
        // Конструктор
        explicit UserService(const drogon::orm::DbClientPtr& dbClient);
        
        bool identification(std::string machine_id);

        void clean_allowed_devices();

        bool registerUser(std::string username,
                          std::string password,
                          std::string email,
                          std::string phone,
                          std::string adress,
                          std::string registration_date);


        UserData getUserByLogin(std::string username);

        std::string hashing(const std::string& password);

        void allow_devices(std::list<std::string> devices);

    private:
        std::shared_ptr<UserRepository> repository; // Доступ к БД
};