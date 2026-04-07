#include "user_service.h"

User UserService::createUser(const std::string& name) {
    std::lock_guard<std::mutex> lock(mtx);
    User u{nextId++, name};
    users.push_back(u);
    return u;
}

std::vector<User> UserService::getAllUsers() {
    std::lock_guard<std::mutex> lock(mtx);
    return users;
}

bool UserService::deleteUser(int id) {
    std::lock_guard<std::mutex> lock(mtx);

    for (auto it = users.begin(); it != users.end(); ++it) {
        if (it->id == id) {
            users.erase(it);
            return true;
        }
    }
    return false;
}

std::optional<User> UserService::getUserById(int id) {
    std::lock_guard<std::mutex> lock(mtx);

    for (const auto& u : users) {
        if (u.id == id) {
            return u;
        }
    }
    return std::nullopt;
}
