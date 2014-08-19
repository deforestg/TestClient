//============================================================================
// Name        : TestClient.cpp
// Author      : Gabriel de Forest
// Version     :
// Copyright   : No copyright
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "include/TcpClient.h"
#include "include/UdpClient.h"

int main() {
	pid_t pid = fork();

    if (pid == 0) {
		pid_t pid2 = fork();
	    if (pid2 == 0) {
	    	UdpClient *client = new UdpClient(1);
			client->Execute((const std::string&)"127.0.1.1");
	    } else {
	    	TcpClient *client = new TcpClient(2);
	        client->Execute((const std::string&)"127.0.1.1");
	    }
    } else {
		pid_t pid3 = fork();
	    if (pid3 == 0) {
        	UdpClient *client = new UdpClient(3);
    		client->Execute((const std::string&)"127.0.1.1");
        } else {
        	TcpClient *client = new TcpClient(4);
            client->Execute((const std::string&)"127.0.1.1");
        }
    }
	return 0;
}
