/*
 * UdpClient.cpp
 *
 *  Created on: Aug 18, 2014
 *      Author: gdeforest
 */

#include "include/UdpClient.h"

UdpClient::UdpClient(int id)
{
	this->id = id;

	loadLength = 100;
	testLoad = new int[loadLength];
	for (int i = 0; i < loadLength; i++) {
		testLoad[i] = i;
	}
	loadLength *= sizeof(int);

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

		int numRecieved = 0;
        timeval time;
        gettimeofday(&time, NULL);
        double current, start = time.tv_sec + (time.tv_usec/1000000.0);

		for (;;)
		{
			const char* px = reinterpret_cast<const char*>(testLoad);
			socket.send_to(boost::asio::buffer(boost::asio::buffer(px, loadLength)), receiver_endpoint);

			boost::array<char, 1024> recv_buf;
			udp::endpoint sender_endpoint;

			size_t len = socket.receive_from(
				boost::asio::buffer(recv_buf),
				sender_endpoint
			);

			// take a sample every 128 ticks
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
