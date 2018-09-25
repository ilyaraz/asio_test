#include <boost/asio.hpp>

#include <iostream>
#include <stdexcept>
#include <string>

using boost::asio::ip::tcp;

int main() {
    try {
        boost::asio::io_service io_service;
        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 1337));
        size_t L = size_t(32) * 89 * 1000000;
        std::vector<uint8_t> buf(L);
        for (size_t i = 0; i < L; ++i) {
            buf[i] = i % 256;
        }
        std::cout << "Try" << std::endl;
        tcp::socket socket(io_service);
        acceptor.accept(socket);
        boost::system::error_code ignored_error;
        boost::asio::write(socket, boost::asio::buffer(buf.data(), L), ignored_error);
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
    return 0;
}
