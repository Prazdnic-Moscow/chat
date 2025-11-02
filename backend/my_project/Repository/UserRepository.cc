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
        "VALUES ($1, $2, $3, $4, $5, $6) RETURNING id",
        username, passwordHash, email, phone, adress, registration_date
    );

    if (!result.empty())
    {
        int userId = result[0]["id"].as<int>();
        
        // Используем полученный ID для вставки в user_role
        auto result2 = db_->execSqlSync
        (
            "INSERT INTO user_roles (user_id, role_id) "
            "VALUES ($1, 2)",
            userId
        );

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


    auto result_2 = db_->execSqlSync
        (
            "SELECT r.name FROM users u " 
            "JOIN user_roles u_r ON u.id = u_r.user_id "
            "JOIN roles r ON u_r.role_id = r.id "
            "WHERE u.username = $1", 
            username
        );
    std::string role_type = (result_2[0]["name"].as<std::string>());

    if (result.empty()) 
    {
        throw std::runtime_error("User not found");
    }

    UserData userdata;
    userdata.setRole(role_type);
    userdata.fromDb(result[0]);
    return userdata;
}

bool UserRepository::changeRole(int user_id)
{
    auto currentRole = db_->execSqlSync
    (
        "SELECT role_id FROM user_roles WHERE user_id = $1",
        user_id
    );

    if (currentRole.empty()) 
    {
        return false;
    }

    int currentRoleId = currentRole[0]["role_id"].as<int>();
    int newRoleId;

    if (currentRoleId == 1) 
    {
        newRoleId = 2;
    } 
    else if (currentRoleId == 2) 
    {
        newRoleId = 1;
    } 
    else 
    {
        return false;
    }
    auto result = db_->execSqlSync
    (
        "UPDATE user_roles "
        "SET role_id = $1 "
        "WHERE user_id = $2",
        newRoleId, user_id
    );

    return true;
}

bool UserRepository::updateFileHash(std::string newHash,
                                    std::string action,
                                    std::string filePath)
{
    try
    {
        if (action == "create")
        {
            auto result = db_->execSqlSync
            (
                "INSERT INTO hashfile (name, filepath) "
                "VALUES ($1, $2) ", 
                newHash, filePath
            );
            return true;
        }
        else
        {
            auto result = db_->execSqlSync
            (
                "UPDATE hashfile "
                "SET name = $1 WHERE filepath = $2", 
                newHash, filePath
            );
            return true;
        }
    }
    catch(const std::exception& e)
    {
        return false;
    }
    
}

bool UserRepository::verifyFileHash(std::string Hash,
                                    std::string file_path)
{
    auto result = db_->execSqlSync
    (
        "SELECT * FROM hashfile "
        "WHERE name = $1 AND filepath = $2 ", 
        Hash, file_path
    );
    if (result.empty())
    {
        return false;
    }
    return true;
}