
#include "crow.h"
#include <vector>
#include <mutex>

struct User {
    int id;
    std::string name;
};

std::vector<User> users;
std::mutex mtx;
int nextId = 1;

int main() {
    crow::SimpleApp app;

    // CREATE USER
    CROW_ROUTE(app, "/users").methods("POST"_method)
    ([](const crow::request& req) {
        auto body = crow::json::load(req.body);
        if (!body || !body.has("name")) {
            return crow::response(400, "Invalid JSON");
        }

        std::lock_guard<std::mutex> lock(mtx);
        User u{nextId++, body["name"].s()};
        users.push_back(u);

        crow::json::wvalue res;
        res["id"] = u.id;
        res["name"] = u.name;

        return crow::response(201, res);
    });

    // GET USERS
    CROW_ROUTE(app, "/users")
    ([] {
        crow::json::wvalue res;
        int i = 0;

        for (const auto& u : users) {
            res[i]["id"] = u.id;
            res[i]["name"] = u.name;
            i++;
        }
        return res;
    });

    // DELETE USER
    CROW_ROUTE(app, "/users/<int>").methods("DELETE"_method)
    ([](int id) {
        std::lock_guard<std::mutex> lock(mtx);

        for (auto it = users.begin(); it != users.end(); ++it) {
            if (it->id == id) {
                users.erase(it);
                return crow::response(200, "Deleted");
            }
        }
        return crow::response(404, "User not found");
    });

    app.port(18080).multithreaded().run();
}
