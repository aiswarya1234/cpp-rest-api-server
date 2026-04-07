#include "user_controller.h"

UserController::UserController(UserService& svc) : service(svc) {}

void UserController::registerRoutes(crow::SimpleApp& app) {

    CROW_ROUTE(app, "/users").methods("POST"_method)
    ([this](const crow::request& req) {
        auto body = crow::json::load(req.body);

        if (!body || !body.has("name")) {
            return crow::response(400, "Invalid JSON");
        }

        auto user = service.createUser(body["name"].s());

        crow::json::wvalue res;
        res["id"] = user.id;
        res["name"] = user.name;

        return crow::response(201, res);
    });

    CROW_ROUTE(app, "/users")
    ([this]() {
        auto users = service.getAllUsers();

        crow::json::wvalue res;
        int i = 0;

        for (const auto& u : users) {
            res[i]["id"] = u.id;
            res[i]["name"] = u.name;
            i++;
        }

        return crow::response(res);
    });

    CROW_ROUTE(app, "/users/<int>")
    ([this](int id) {
        auto user = service.getUserById(id);

        if (!user.has_value()) {
            return crow::response(404, "User not found");
        }

        crow::json::wvalue res;
        res["id"] = user->id;
        res["name"] = user->name;

        return crow::response(res);
    });

    CROW_ROUTE(app, "/users/<int>").methods("DELETE"_method)
    ([this](int id) {
        bool deleted = service.deleteUser(id);

        if (!deleted) {
            return crow::response(404, "User not found");
        }

        return crow::response(200, "Deleted");
    });
}
