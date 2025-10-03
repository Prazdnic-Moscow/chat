#include <drogon/drogon.h>
#include <drogon/orm/DbClient.h>
#include <json/json.h>
#include <drogon/HttpController.h>
#include "../Service/UserService.h"
using namespace drogon;

class UserController : public HttpController<UserController>
{
    public:
        METHOD_LIST_BEGIN
        ADD_METHOD_TO(UserController::identification, "/identification", Post);
        ADD_METHOD_TO(UserController::registerUser, "/register", Post);
        ADD_METHOD_TO(UserController::loginUser, "/login", Post);
        METHOD_LIST_END
        
        void identification(const HttpRequestPtr& req,
                            std::function<void(const HttpResponsePtr&)>&& callback);

        void registerUser(const HttpRequestPtr& req,
                          std::function<void(const HttpResponsePtr&)>&& callback);

        bool loginUser(const HttpRequestPtr& req,
                       std::function<void(const HttpResponsePtr&)>&& callback);
};