#include <boost/asio.hpp>
#include <boost/array.hpp>

#include <gmp.h>

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
	const int32_t L = 128000000;
        uint8_t *buf = new uint8_t[L];
        boost::system::error_code error;

        size_t total = 0;
        for (;;) {
            if (total == L) {
                break;
            }
            size_t len = socket.read_some(boost::asio::buffer(buf + total, L - total), error);
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
	int32_t N = 1000000;
	mpz_t *data = new mpz_t[N];
	for (int32_t i = 0; i < N; ++i) {
		mpz_init(data[i]);
		mpz_import(data[i], 128, -1, sizeof(uint8_t), 0, 0, buf + 128 * i);
	}
	FILE *output = fopen("data_client.txt", "w");
	for (int32_t i = 0; i < N; ++i) {
		mpz_out_str(output, 10, data[i]);
		fprintf(output, "\n");
	}
	fclose(output);
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
    return 0;
}
