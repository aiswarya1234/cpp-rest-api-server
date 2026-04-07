#include <iostream>
#include <vector>
#include <string>

// NOTE:
// This is a simplified REST-like simulation
// (since we are not installing Crow locally)

struct User {
    int id;
    std::string name;
};

std::vector<User> users;
int nextId = 1;

void createUser(const std::string& name) {
    users.push_back({nextId++, name});
    std::cout << "User created\n";
}

void getUsers() {
    for (const auto& u : users) {
        std::cout << u.id << " : " << u.name << "\n";
    }
}

void deleteUser(int id) {
    for (auto it = users.begin(); it != users.end(); ++it) {
        if (it->id == id) {
            users.erase(it);
            std::cout << "Deleted\n";
            return;
        }
    }
    std::cout << "User not found\n";
}

int main() {
    createUser("Alice");
    createUser("Bob");

    getUsers();

    deleteUser(1);

    getUsers();

    return 0;
}
