#include "boost/asio.hpp"
#include <iostream>
#include <cstdio>
#include <signal.h>

using boost::asio::ip::tcp;

int main() {
    // Игнорируем сигнал ошибки работы с сокетом
    signal(SIGPIPE, SIG_IGN);

    boost::asio::io_service io_service;

    tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 8080));

    for (;;) {
        std::cout << "hello";
        fflush(stdout);
        tcp::socket socket(io_service);
        acceptor.accept(socket);

        while(true) 
        {
            boost::asio::streambuf buf;
            try
            {
                boost::asio::read_until(socket, buf, "\n");
            } catch(...)
            {
                break;
            }
            std::string data = boost::asio::buffer_cast<const char*>(buf.data());
            std::cout << data;
            fflush(stdout);
        }
        // boost::asio::write(socket, boost::asio::buffer(data));
    
    }
    return 0;
}