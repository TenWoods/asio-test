#include <iostream>
#include "common.h"
#include <asio.hpp>
#include <string>
#include <ctime>


using asio::ip::tcp;

std::string make_daytime_string()
{
    using namespace std; // For time_t, time and ctime;
    time_t now = time(0);
    return ctime(&now);
}

int main(int argc, char* argv[])
{
    std::cout << "Here is server!" << std::endl;
    try
    {
        asio::io_context io_context;
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 8080));
        while (true)
        {
            //std::cout << '?' << std::endl;
            tcp::socket socket(io_context);
            acceptor.accept(socket);
            std::string message = make_daytime_string();
            asio::error_code ignored_error;
            asio::write(socket, asio::buffer(message), ignored_error);
            asio::read(socket, asio::buffer(message), ignored_error);
            std::cout << message << std::endl;
        }
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
