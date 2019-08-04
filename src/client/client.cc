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

char buf[] = {1, 82, 0, 82, 0, 4, 0, 0, 0, 1, 54, 100, 48, 100, 52, 101, 57, 101, 45, 102, 54, 52, 57, 45, 49, 49, 101, 56, 45, 57, 100, 55, 48, 45, 98, 56, 101, 56, 53, 54, 50, 100, 97, 48, 57, 97, 56, 97, 49, 102, 48, 51, 50, 101, 45, 102, 54, 52, 57, 45, 49, 49, 101, 56, 45, 57, 100, 55, 48, 45, 98, 56, 101, 56, 53, 54, 50, 100, 97, 48, 57, 97, 13};
char rev_buf[1024];

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
    unsigned int buf_len = buf[2] << 8 | buf[3];
    int rc = send(sockfd, buf, buf_len, 0);
    if (rc < 0)
    {
      std::string e("ERROR on send");
      error(e.data());
    }
  }

  memset(rev_buf, 0, 1024);
  int rc = recv(sockfd, rev_buf, 1024, 0);
  if (rc < 0)
  {
    std::string e("ERROR receive error");
    error(e.data());
  }

  for (int i = 0; i < 1024; i++)
  {
    std::cout << (int) rev_buf[i] << " ";
  }
  std::cout << std::endl;

  close(sockfd);
  std::cout << "hello, world" << std::endl;

  return 0;
}