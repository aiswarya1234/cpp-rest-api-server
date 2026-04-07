#pragma once
#include "user_model.h"
#include <vector>
#include <mutex>
#include <optional>

class UserService {
private:
    std::vector<User> users;
    std::mutex mtx;
    int nextId = 1;

public:
    User createUser(const std::string& name);
    std::vector<User> getAllUsers();
    bool deleteUser(int id);
    std::optional<User> getUserById(int id);
};
