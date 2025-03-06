#include "session.h"
#include <iostream>

session::session(tcp::socket socket) : m_socket(std::move(socket)) {}

void session::run() {
    wait_for_request();
}

void session::wait_for_request() {
    auto self(shared_from_this());
    boost::asio::async_read_until(m_socket, m_buffer, "\0", 
    [this, self](boost::system::error_code ec, std::size_t) {
        if (!ec) {
            std::string data{
                std::istreambuf_iterator<char>(&m_buffer),
                std::istreambuf_iterator<char>()
            };

            std::cout << "Client: " << data << std::endl;

            if (data == "exit") {
                std::cout << "Shutdown command received. Stopping server..." << std::endl;
                m_socket.close();
                return;
            }
            
            std::string response = "Message received successfully.\0";
            boost::asio::write(m_socket, boost::asio::buffer(response));
            
            wait_for_request();
        } else {
            if (ec == boost::asio::error::eof) {
                std::cout << "Client disconnected gracefully." << std::endl;
            } else {
                std::cout << "Failed to read message from client. Error: " << ec.message() << std::endl;
            }
        }
    });
}
