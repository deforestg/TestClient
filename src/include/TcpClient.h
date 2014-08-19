/*
 * TcpClient.h
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
using boost::asio::ip::tcp;

#ifndef TCPCLIENT_H_
#define TCPCLIENT_H_

class TcpClient
{
	private:
		boost::asio::io_service ioService;
		tcp::resolver *resolver;
		int id;
	public:
		TcpClient();
		TcpClient(int id);
		void Execute(const std::string& endpoint);
};


#endif /* TCPCLIENT_H_ */
