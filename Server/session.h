#ifndef SESSION_H
#define SESSION_H

#include <boost/asio.hpp>
#include <iostream>

using boost::asio::ip::tcp;

class session : public std::enable_shared_from_this<session> {
public:
    session(tcp::socket socket); 
    void run();

private:
    void wait_for_request();

private:
    tcp::socket m_socket;
    boost::asio::streambuf m_buffer;
};

#endif // SESSION_H
