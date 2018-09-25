#include <boost/asio.hpp>

#include <gmp.h>

#include <iostream>
#include <stdexcept>
#include <string>

using boost::asio::ip::tcp;

int main() {
    try {
	const int32_t N = 1000000;
	mpz_t *data = new mpz_t[N];
	gmp_randstate_t state;
	gmp_randinit_default(state);
	for (int32_t i = 0; i < N; ++i) {
		mpz_init(data[i]);
		mpz_urandomb(data[i], state, 1024);
	}
	uint8_t *buf = new uint8_t[128000000];
	memset(buf, 0, sizeof(buf));
	for (int32_t i = 0; i < N; ++i) {
		size_t countp;
		mpz_export(buf + 128 * i, &countp, -1, sizeof(uint8_t), 0, 0, data[i]);
	}
        boost::asio::io_service io_service;
        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 1337));
        std::cout << "Try" << std::endl;
        tcp::socket socket(io_service);
        acceptor.accept(socket);
        boost::system::error_code ignored_error;
        boost::asio::write(socket, boost::asio::buffer(buf, 128000000), ignored_error);
	FILE *output = fopen("data_server.txt", "w");
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
