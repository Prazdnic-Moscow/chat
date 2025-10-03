#pragma once
#include "UserController.h"
#include <chrono>
#include <sstream>
#include <iomanip>
#include <bcrypt/BCrypt.hpp>


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
    
    std::time_t now_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    char buffer[11];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", std::localtime(&now_time));
    std::string registration_date = buffer;
    auto dbClient = drogon::app().getDbClient();
    UserService userservice(dbClient);

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
                