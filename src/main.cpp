#include "crow.h"
#include "user_controller.h"
#include "user_service.h"

int main() {
    crow::SimpleApp app;

    UserService service;
    UserController controller(service);

    controller.registerRoutes(app);

    app.port(18080).multithreaded().run();

    return 0;
}
