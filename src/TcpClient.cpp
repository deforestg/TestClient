/*
 * TcpClient.cpp
 *
 *  Created on: Aug 18, 2014
 *      Author: gdeforest
 */

#include "include/TcpClient.h"

TcpClient::TcpClient(int id)
{
	this->id = id;
	resolver = new tcp::resolver(ioService);
}

void TcpClient::Execute(const std::string& endpoint)
{
	try
	{
		tcp::resolver::query query(endpoint, "18206");
		tcp::resolver::iterator endpoint_iterator = resolver->resolve(query);

		for (;;)
		{
			tcp::socket socket(ioService);
			boost::asio::connect(socket, endpoint_iterator);

			boost::array<char, 128> buf;
			boost::system::error_code error;

			size_t len = socket.read_some(boost::asio::buffer(buf), error);

			if (error == boost::asio::error::eof) {
				break; // Connection closed cleanly by peer.
			} else if (error) {
				throw boost::system::system_error(error); // Some other error.
			}

			std::cout << "Client " << id << ":  ";
			int* x = (int*)buf.data();
			for (int i = 0; i < (int)(len/sizeof(int)); i++) {
				std::cout << x[i] << ", ";
			}
			std::cout << endl;
		}
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
}
