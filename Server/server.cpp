#include "server.h"

server::server(boost::asio::io_context& io_context, short port)
    : m_acceptor(io_context, tcp::endpoint(tcp::v4(), port)), m_socket(io_context) {
    do_accept();
}

void server::do_accept() {
    std::cout << "Waiting for a client to connect..." << std::endl;
    
    m_acceptor.accept(m_socket);
    
    std::cout << "Client connected: "
              << m_socket.remote_endpoint().address().to_string()
              << ":" << m_socket.remote_endpoint().port() << '\n';

    std::make_shared<session>(std::move(m_socket))->run();

}
