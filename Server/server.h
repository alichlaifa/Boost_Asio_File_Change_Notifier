#ifndef SERVER_H
#define SERVER_H

#include <boost/asio.hpp>
#include "session.h"  

using boost::asio::ip::tcp;

class server {
public:
    server(boost::asio::io_context& io_context, short port);
    void do_accept();

private:
    tcp::acceptor m_acceptor;
    tcp::socket m_socket;
};

#endif // SERVER_H
