#include "UserService.h"
#include <bcrypt/BCrypt.hpp>

bool flag;
// Конструктор — инициализируем репозиторий
UserService::UserService(const drogon::orm::DbClientPtr& dbClient)
{
    repository = std::make_shared<UserRepository>(dbClient);
}

 bool UserService::identification(std::string machine_id)
{
    std::list<std::string> devicesHash = repository->getMachineId();
    
    for (const auto& deviceHash : devicesHash)
    {
        // BCrypt сам хеширует machine_id с солью из deviceHash
        if (BCrypt::validatePassword(machine_id, deviceHash))
        {
            LOG_DEBUG << "Device identified successfully";
            LOG_DEBUG << "Input machine_id: [" << machine_id << "]";
            LOG_DEBUG << "Stored hash: [" << deviceHash << "]";
            return true;
        }
    }
    
    LOG_DEBUG << "No matching device found for machine_id: [" << machine_id << "]";
    return false;
}

void UserService::clean_allowed_devices()
{
    repository->clean_allowed_devices();
}

bool UserService::registerUser(std::string username,
                               std::string password,
                               std::string email,
                               std::string phone,
                               std::string adress,
                               std::string registration_date)
{
    std::string passwordHash = hashing(password);
    
    return repository->registerUser(username,
                             passwordHash,
                             email,
                             phone,
                             adress,
                             registration_date);
}

UserData UserService::getUserByLogin(std::string username)
{
    return repository->getUserByLogin(username);
}




void UserService::allow_devices(std::list<std::string> devices)
{
    std::list<std::string> hashDevices;
    for (auto device : devices)
    {
        hashDevices.push_back(hashing(device));
    }
    repository -> addAllowDevices(hashDevices);
}


std::string UserService::hashing(const std::string& password) 
{
    return BCrypt::generateHash(password, 12);
}