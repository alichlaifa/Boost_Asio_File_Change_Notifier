#include <iostream>
#include <boost/asio.hpp>
#include "server.h"
#include "config.h"

int main() {
    try {
        boost::asio::io_context io_context;

        server srv(io_context, Config::server_port);

        io_context.run();

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
