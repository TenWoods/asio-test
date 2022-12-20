#include <iostream>
#include "common.h"
#include <asio.hpp>
#include <vector>

using asio::ip::tcp;
int main(int argc, char* argv[])
{
    try
    {
        if (argc != 3)
        {
            std::cerr << "Usage: client <host> <port>" << std::endl;
            return 1;
        }

        std::cout << "Here is client!" << std::endl;
        asio::io_context context;
        tcp::resolver resolver(context);
        tcp::resolver::results_type endpoints = resolver.resolve(argv[1], argv[2]);
        tcp::socket socket(context);
        asio::connect(socket, endpoints);
        while (true)
        {
            //std::cout << '?' << std::endl;
            std::vector<char> buffer(128);
            asio::error_code errorCode;
            size_t length = socket.read_some(asio::buffer(buffer), errorCode);
            if (errorCode == asio::error::eof)
                break;
            else if (errorCode)
                throw asio::system_error(errorCode);
            std::cout.write(buffer.data(), buffer.size());
            std::string return_string("Success read byte: ");
            return_string += std::to_string(buffer.size());
            asio::write(socket, asio::buffer(return_string));
        }
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
