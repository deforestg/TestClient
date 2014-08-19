/*
 * UdpClient.h
 *
 *  Created on: Aug 18, 2014
 *      Author: gdeforest
 */

#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;
using boost::asio::ip::udp;

#ifndef UDPCLIENT_H_
#define UDPCLIENT_H_

class UdpClient
{
	private:
		boost::asio::io_service ioService;
		udp::resolver *resolver;
		int id;
	public:
		UdpClient();
		UdpClient(int id);
		void Execute(const std::string& endpoint);
};


#endif /* UDPCLIENT_H_ */
