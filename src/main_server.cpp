#include <iostream>
#include "common.h"
#include "Connection.hpp"
#include <asio.hpp>
#include <string>
#include <ctime>


using asio::ip::tcp;

class Server
{
public:
    Server(asio::io_context& io_context, short port) : m_acceptor(io_context, tcp::endpoint(tcp::v4(), port))
    {
        handleAccept();
    }
private:
    void handleAccept()
    {
        m_acceptor.async_accept([this](std::error_code ec, tcp::socket socket)
        {
            if (!ec)
            {
                std::cout << "Connect!" << std::endl;
                std::make_shared<Connection>(std::move(socket))->start();
            }
            handleAccept();
        });
    }
    tcp::acceptor m_acceptor;
};

int main(int argc, char* argv[])
{
    std::cout << "Here is server!" << std::endl;
    try
    {
        if (argc != 2)
        {
            std::cerr << "Usage server <port>" << std::endl;
            return 1;
        }
        asio::io_context io_context;
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 8080));
        Server server(io_context, std::atoi(argv[1]));
        io_context.run();
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
