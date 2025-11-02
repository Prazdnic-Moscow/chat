#pragma once
#include <drogon/orm/DbClient.h> // Подключение к PostgreSQL
#include <string>
#include <list>
#include "../Models/User.h"
class UserRepository 
{
    public:
        // Конструктор принимает подключение к БД
        UserRepository(const drogon::orm::DbClientPtr &dbClient) : db_(dbClient) {}

        std::list<std::string> getMachineId();

        void clean_allowed_devices();
        
        // Создать пользователя в БД
        bool registerUser(std::string username,
                          std::string passwordHash,
                          std::string email,
                          std::string phone,
                          std::string adress,
                          std::string registration_date);

        bool addAllowDevices(std::list<std::string> hashDevices);

        UserData getUserByLogin(std::string username);

        bool changeRole(int user_id);

        bool updateFileHash(std::string newHash,
                            std::string action,
                            std::string filePath);

        bool verifyFileHash(std::string Hash,
                            std::string file_path);

    private:
        drogon::orm::DbClientPtr db_; // Подключение к PostgreSQL
};