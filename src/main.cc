#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#include <pthread.h>

#include "message.h"

void error(const char *msg)
{
	perror(msg);
	exit(1);
}

int main(int argc, char const *argv[])
{
	int sockfd;
	int port;

	char buffer[1024];
	memset(buffer, 0, 1024);

	sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

	if (sockfd < 0)
	{
		std::string e("ERROR opening socket.");
		error(e.data());
	}
	
	struct sockaddr_un isock;
	memset((char *) &isock, 0, sizeof(isock));
	
	port = 2000;
	isock.sun_family = AF_UNIX;
	strcpy(isock.sun_path, "/tmp/controller");

	if (bind(sockfd, (struct sockaddr *) &isock, sizeof(isock)) < 0)
	{
		std::string e("ERROR on binding");
		error(e.data());
	}

	if (listen(sockfd, 10) < 0)
	{
		std::string e("ERROR on listening");
		error(e.data());
	}

	std::cout << "Listening on /tmp/controller for clients ..." << std::endl;
	gateway_init();
	bool ok = true;
	while (ok)
	{
		struct sockaddr caddr;
		unsigned int len = sizeof(caddr);

		int clientfd = accept(sockfd, &caddr, &len);

		if (clientfd < 0)
		{
			std::string e("ERROR client address not understood");
			error(e.data());
		}

		int rc = recv(clientfd, buffer, sizeof(buffer), 0);
		if (rc < 0)
		{
			std::string e("ERROR receive error");
			error(e.data());
		}
		else if (rc != 0)
		{
			std::cout << "Buffer received. Parsing ..." << std::endl;
			gateway_payload_parse(buffer);

			std::cout << "Done parsing. Replying ..." << std::endl;
			int rc = send(clientfd, gateway_payload_reply(), gateway_payload_get_len(), 0);
			if (rc < 0)
			{
				ok = false;
			}
		}
		else 
		{
			continue;
		}
	}
	close(sockfd);
	unlink("/tmp/controller");
	std::cout << "hello, world" << std::endl;

	return 0;
}