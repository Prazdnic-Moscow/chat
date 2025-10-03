#pragma once
#include <drogon/drogon.h>
#include <string>

class UserData
{
    std::string username;
    std::string passwordHash;
    std::string email;
    std::string phone;
    std::string adress;
    std::string registration_date;

public:
    void fromDb(const drogon::orm::Row &result) 
        { 
            username = result["username"].as<std::string>();
            passwordHash = result["password"].as<std::string>();
            email = result["email"].as<std::string>();
            phone = result["phone"].as<std::string>();
            adress = result["adress"].as<std::string>();
            registration_date = result["registration_date"].as<std::string>();
        }
    // Гетеры
    const std::string& getUsername() const { return username; }
    const std::string& getPasswordHash() const { return passwordHash; }
    const std::string& getEmail() const { return email; }
    const std::string& getPhone() const { return phone; }
    const std::string& getAdress() const { return adress; }
    const std::string& getRegistrationDate() const { return registration_date; }

    // Сетеры
    void setUsername(const std::string& newUsername) { username = newUsername; }
    void setPasswordHash(const std::string& newPasswordHash) { passwordHash = newPasswordHash; }
    void setEmail(const std::string& newEmail) { email = newEmail; }
    void setPhone(const std::string& newPhone) { phone = newPhone; }
    void setAdress(const std::string& newAdress) { adress = newAdress; }
    void setRegistrationDate(const std::string& newRegistrationDate) { registration_date = newRegistrationDate; }
};