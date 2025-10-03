#include "UserRepository.h"

void UserRepository::clean_allowed_devices()
{
    db_->execSqlSync("DELETE FROM allowed_devices");
}

bool UserRepository::addAllowDevices(std::list<std::string> hashDevices)
{
    auto tran = db_->newTransaction();
    for (auto device : hashDevices)
    {
        auto result = tran->execSqlSync
        (
            "INSERT INTO allowed_devices(device_id) "
            "VALUES ($1) ", device
        );
    }
    return true;
}



std::list<std::string> UserRepository::getMachineId()
{
    std::list<std::string> devices;
    auto result = db_->execSqlSync
    (
        "SELECT device_id from allowed_devices "
    );

    for (auto device : result)
    {
        devices.push_back(device["device_id"].as<std::string>());
    }
    return devices;
}


bool UserRepository::registerUser(std::string username,
                                  std::string passwordHash,
                                  std::string email,
                                  std::string phone,
                                  std::string adress,
                                  std::string registration_date)
{
    auto result = db_->execSqlSync
    (
        "INSERT INTO users (username, password, email, phone, adress, registration_date) "
        "VALUES ($1, $2, $3, $4, $5, $6) ",
        username, passwordHash, email, phone, adress, registration_date
        
    );

    if (!result.empty())
    {
        return true;
    }
    return false;
}


UserData UserRepository::getUserByLogin(std::string username)
{
    auto result = db_->execSqlSync
    (
        "SELECT * FROM users "
        "WHERE username = $1 ",
        username
    );

    if (result.empty()) 
    {
        throw std::runtime_error("User not found");
    }

    UserData userdata;
    userdata.fromDb(result[0]);
    return userdata;
}