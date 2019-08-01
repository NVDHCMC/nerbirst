#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

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

  if (connect(sockfd, (struct sockaddr *) &isock, sizeof(isock)) < 0)
  {
    std::string e("ERROR on binding");
    error(e.data());
  }

  std::cout << "Listening on port 2000 for clients ..." << std::endl;
  if (argc > 1)
  {
    int rc = send(sockfd, argv[1], strlen(argv[1]), 0);
    if (rc < 0)
    {
      std::string e("ERROR on send");
      error(e.data());
    }
  }
  close(sockfd);
  std::cout << "hello, world" << std::endl;

  return 0;
}