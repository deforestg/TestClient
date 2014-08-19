/*
 * UdpClient.cpp
 *
 *  Created on: Aug 18, 2014
 *      Author: gdeforest
 */

#include "include/UdpClient.h"

UdpClient::UdpClient()
{
	id = -1;
	resolver = new udp::resolver(ioService);
}

UdpClient::UdpClient(int id)
{
	this->id = id;
	resolver = new udp::resolver(ioService);
}

void UdpClient::Execute(const std::string& endpoint)
{
	try
	{
		udp::resolver::query query(endpoint, "18206");
		udp::endpoint receiver_endpoint = *resolver->resolve(query);

		udp::socket socket(ioService);
		socket.open(udp::v4());

		for (;;)
		{
			boost::array<char, 1> send_buf  = {{ 0 }};
			socket.send_to(boost::asio::buffer(send_buf), receiver_endpoint);

			boost::array<char, 128> recv_buf;
			udp::endpoint sender_endpoint;

			size_t len = socket.receive_from(
				boost::asio::buffer(recv_buf),
				sender_endpoint
			);

			std::cout << "Client " << id << ":  ";
			int* x = (int*)recv_buf.data();
			for (int i = 0; i < (int)(len/sizeof(int)); i++) {
				std::cout << x[i] << ", ";
			}
			std::cout << endl;
		}
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
}
