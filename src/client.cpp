#include <boost/asio.hpp>
#include <boost/array.hpp>

#include <iostream>
#include <stdexcept>
#include <string>

using boost::asio::ip::tcp;

int main() {
    try {
        boost::asio::io_service io_service;
        tcp::resolver resolver(io_service);
        tcp::resolver::query query("127.0.0.1", "1337");
        tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
        tcp::socket socket(io_service);
        boost::asio::connect(socket, endpoint_iterator);
        size_t L = size_t(32) * 89 * 1000000;
        std::vector<uint8_t> buf(L);
        boost::system::error_code error;

        size_t total = 0;
        for (;;) {
            if (total == L) {
                break;
            }
            size_t len = socket.read_some(boost::asio::buffer(buf.data() + total, L - total), error);
            if (error == boost::asio::error::eof) {
                std::cerr << "Unexpected EOF" << std::endl;
                exit(1);
            }
            else if (error) {
                std::cerr << "Network error" << std::endl;
                exit(1);
            }

            std::cout << "Success" << std::endl;
            std::cout << len << std::endl;
            total += len;
        }
        std::cout << total << std::endl;
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
    return 0;
}
