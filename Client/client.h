#ifndef CLIENT_H
#define CLIENT_H

#include <boost/asio.hpp>
#include <string>

using boost::asio::ip::tcp;

class client {
public:
    client(boost::asio::io_context& io_context, const std::string& host, short port);
    void send_message(const std::string& filename, const std::string& action);

private:
    tcp::socket m_socket;
};

#endif // CLIENT_H
