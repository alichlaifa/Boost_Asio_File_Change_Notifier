#include <iostream>
#include <thread>
#include "client.h"
#include "config.h"
#include "watcher.h"

int main() {
    try {
        boost::asio::io_context io_context;
        client c(io_context, Config::server_ip, Config::server_port);  

        Watcher watcher(Config::watched_folder, [&c](const std::string& eventType, const std::string& filePath) {
            c.send_message(eventType, filePath);
        });

        std::thread watcherThread([&]() {
            watcher.startWatching();
        });

        std::string input;
        while (true) {
            std::cout << "Type 'exit' to stop the client: ";
            std::getline(std::cin, input);
            if (input == "exit") {
                std::cout << "Stopping client and watcher..." << std::endl;
                watcher.stopWatching(); 
                break;
            }
        }

        watcherThread.join();

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}

