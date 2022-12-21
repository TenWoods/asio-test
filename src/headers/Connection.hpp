#ifndef ASIO_TEST_CONNECTION_HPP
#define ASIO_TEST_CONNECTION_HPP
#include <memory>
#include <asio.hpp>

using asio::ip::tcp;

class Connection : public std::enable_shared_from_this<Connection>
{
public:
    Connection(tcp::socket socket) : m_socket(std::move(socket)){}

    void start()
    {
        handleRead();
    }
private:
    void handleRead()
    {
        auto self(shared_from_this());
        m_socket.async_read_some(asio::buffer(m_data, max_length),
            [this, self](std::error_code ec, std::size_t length)
            {
                if (!ec)
                {
                    std::cout << m_data << std::endl;
                    handleWrite(length);
                }
                else
                {
                    std::cout << ec.message() << std::endl;
                }
            });
    }
    void handleWrite(std::size_t length)
    {
        auto self(shared_from_this());
        asio::async_write(m_socket, asio::buffer(m_data, length),
            [this, self](std::error_code ec, std::size_t)
            {
                if (!ec)
                {
                    handleRead();
                }
            });
    }
    tcp::socket m_socket;
    enum {max_length = 1024};
    char m_data[max_length];
};

#endif //ASIO_TEST_CONNECTION_HPP
