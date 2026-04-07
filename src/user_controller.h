#pragma once
#include "crow.h"
#include "user_service.h"

class UserController {
private:
    UserService& service;

public:
    UserController(UserService& svc);
    void registerRoutes(crow::SimpleApp& app);
};
