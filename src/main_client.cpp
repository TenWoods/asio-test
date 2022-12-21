#include <iostream>
#include <memory>
#include <utility>
#include <asio.hpp>
#include <vector>

using asio::ip::tcp;

const int max_length = 1024;
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

        std::cout << "Enter message: ";
        char request[max_length];
        std::cin.getline(request, max_length);
        size_t request_length = std::strlen(request);
        asio::write(socket, asio::buffer(request, request_length));
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(2000ms);
        char reply[max_length];
        size_t reply_length = asio::read(socket, asio::buffer(reply, request_length));
        std::cout << "Reply is: ";
        std::cout.write(reply, reply_length);
        std::cout << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
