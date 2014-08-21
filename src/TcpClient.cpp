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

		int numRecieved = 0;
        timeval time;
        gettimeofday(&time, NULL);
        double current, start = time.tv_sec + (time.tv_usec/1000000.0);

		for (;;)
		{
			tcp::socket socket(ioService);
			boost::asio::connect(socket, endpoint_iterator);

			boost::array<char, 1024> buf;
			boost::system::error_code error;

			size_t len = socket.read_some(boost::asio::buffer(buf), error);

			if (error == boost::asio::error::eof) {
				break; // Connection closed cleanly by peer.
			} else if (error) {
				throw boost::system::system_error(error); // Some other error.
			}

			if (numRecieved++ % 128 == 0) {
				std::cout << "Client " << id << ":  ";
				std::cout << len << " byte packets, Recieving ";
		        gettimeofday(&time, NULL);
		        current = time.tv_sec + (time.tv_usec/1000000.0);
				std::cout << numRecieved/(current - start) << " packets/s";
				std::cout << std::endl;
			}
		}
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
}
