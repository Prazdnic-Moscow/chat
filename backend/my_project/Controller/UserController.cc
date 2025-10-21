#pragma once
#include "UserController.h"
#include <chrono>
#include <sstream>
#include <iomanip>
#include <bcrypt/BCrypt.hpp>
#include <string>
#include <regex>
#include <iostream>


void UserController::identification(const HttpRequestPtr& req,
                                    std::function<void(const HttpResponsePtr&)>&& callback)
{
    auto json = req->getJsonObject();
    std::string machine_id = json->get("machine_id", "").asString();
    LOG_DEBUG << "Пришёл machine_id: [" << machine_id << "]";
    auto dbClient = drogon::app().getDbClient();
    UserService userservice(dbClient);

    if (userservice.identification(machine_id) == false)
    {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k400BadRequest);
        callback(resp);
        return; 
    }
    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(k200OK);
    callback(resp);
    return; 
    
}



void UserController::registerUser(const HttpRequestPtr& req,
                                  std::function<void(const HttpResponsePtr&)>&& callback)
{
    auto json = req->getJsonObject();
    std::string username = json->get("username", "").asString();
    std::string password = json->get("password", "").asString();
    std::string email = json->get("email", "").asString();
    std::string phone = json->get("phone", "").asString();
    std::string adress = json->get("adress", "").asString();
    std::string machine_id = json->get("machine_id", "").asString();
    
    std::time_t now_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    char buffer[11];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", std::localtime(&now_time));
    std::string registration_date = buffer;

    // Проверка телефона (11 цифр, начинается с 7 или 8)
    std::regex phone_regex("^[78][0-9]{10}$");
    if (!std::regex_match(phone, phone_regex)) 
    {
        std::cout << "Предупреждение: Телефон должен:\n"
                << "- Состоять из 11 цифр\n"
                << "- Начинаться с 7 или 8\n"
                << "- Содержать только цифры" << std::endl;
        return;
    }

    // Проверка email (должен содержать @ и точку, минимальная длина 6 символов)
    if (email.length() < 6 || 
        email.find('@') == std::string::npos || 
        email.find('.') == std::string::npos || 
        email.find('@') < 1)
    {
        
        std::cout << "Предупреждение: Email должен быть в формате example@domain.com и содержать не менее 6 символов" << std::endl;
        return;
    }

    // Проверка адреса (минимум 5 символов)
    if (adress.length() < 5) 
    {
        std::cout << "Предупреждение: Адрес должен содержать не менее 5 символов" << std::endl;
        return;
    }

    auto dbClient = drogon::app().getDbClient();
    UserService userservice(dbClient);

    if (userservice.identification(machine_id) == false)
    {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k400BadRequest);
        callback(resp);
        return; 
    }
    
    LOG_DEBUG << "Прошел проверку в регистрации: [" << machine_id << "]";

    try
    {
        userservice.registerUser(username, 
                                password, 
                                email, 
                                phone, 
                                adress,
                                registration_date);
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k200OK);
        callback(resp);
        return; 
    }
    catch(const std::exception& e)
    {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k400BadRequest);
        callback(resp);
        return; 
    }
}

bool UserController::loginUser(const HttpRequestPtr& req,
                               std::function<void(const HttpResponsePtr&)>&& callback)
{
    auto json = req->getJsonObject();
    std::string username_ = json->get("username", "").asString();
    std::string password_ = json->get("password", "").asString();
    std::string machine_id = json->get("machine_id", "").asString();

    if (username_.empty() || password_.empty()) 
    {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k400BadRequest);
        resp->setBody("Username or password are NULL");
        callback(resp);
        return false;
    }

    auto dbClient = drogon::app().getDbClient();
    UserService userservice(dbClient);
    UserData userdata = userservice.getUserByLogin(username_);

    if (userservice.identification(machine_id) == false)
    {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k400BadRequest);
        callback(resp);
        return false; 
    }

    LOG_DEBUG << "Прошел проверку в входе: [" << machine_id << "]";
    
    if (username_ == userdata.getUsername() && 
        BCrypt::validatePassword(password_, userdata.getPasswordHash())) 
    {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k200OK);
        callback(resp);
        return true;
    } 
    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(k401Unauthorized);
    callback(resp);
    return false; 
}


bool UserController::changeRole(const HttpRequestPtr& req,
                                std::function<void(const HttpResponsePtr&)>&& callback)
{
    auto json = req->getJsonObject();
    std::string machine_id = json->get("machine_id", "").asString();
    std::string username = json->get("username", "").asString();
    std::string selfusername = json->get("selfusername", "").asString();

    auto dbClient = drogon::app().getDbClient();
    UserService userservice(dbClient);

    if (userservice.identification(machine_id) == false)
    {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k400BadRequest);
        callback(resp);
        return false; 
    }
    LOG_DEBUG << "Прошел проверку при смене роли: [" << machine_id << "]";

    UserData data = userservice.getUserByLogin(username);
    int user_id = data.getId();

    if (selfusername == "creator")
    {
        if (userservice.changeRole(user_id))
        {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k201Created);
        callback(resp);
        return true; 
        }
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k400BadRequest);
        callback(resp);
        return false; 
    }
    else
    {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k400BadRequest);
        callback(resp);
        return false; 
    }

}

bool UserController::checkRole(const HttpRequestPtr& req,
                               std::function<void(const HttpResponsePtr&)>&& callback)
{
    auto json = req->getJsonObject();
    std::string username = json->get("username", "").asString();
    std::string machine_id = json->get("machine_id", "").asString();
    auto dbClient = drogon::app().getDbClient();
    UserService userservice(dbClient);
    
    if (userservice.identification(machine_id) == false)
    {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k400BadRequest);
        callback(resp);
        return false; 
    }
    LOG_DEBUG << "Прошел проверку при проверке роли: [" << machine_id << "]";

    UserData data = userservice.getUserByLogin(username);
    std::string rolename = data.getRole();

    if (rolename == "admin" || rolename == "creator")
    {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k200OK);
        callback(resp);
        return true; 
    }

    auto resp = HttpResponse::newHttpResponse();
    resp->setStatusCode(k400BadRequest);
    callback(resp);
    return false; 
}
                