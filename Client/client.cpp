#include "client.h"
#include <iostream>

client::client(boost::asio::io_context& io_context, const std::string& host, short port)
    : m_socket(io_context) {
    tcp::resolver resolver(io_context);
    auto endpoints = resolver.resolve(host, std::to_string(port));
    boost::asio::connect(m_socket, endpoints);
}

void client::send_message(const std::string& filename, const std::string& action) {
    std::string message = "File " + filename + " was " + action;
    boost::asio::write(m_socket, boost::asio::buffer(message + "\0"));

    std::cout << "Sent: " << message << std::endl;

    char response[256];
    boost::system::error_code error;
    size_t len = m_socket.read_some(boost::asio::buffer(response), error);

    if (!error) {
        std::cout << "Server: " << std::string(response, len) << std::endl;
    } else {
        std::cout << "The server failed to read the message." << std::endl;
    }
}
