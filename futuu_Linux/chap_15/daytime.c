#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>




static int open_connection(char *host, char *service){
  int sock;
  struct addrinfo hints, *res, *ai;
  int err;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family=AF_UNSPEC;
  hints.ai_socktype=SOCK_STREAM;
  if ((err=getaddrinfo(host, service, &hints, &res))!=0){
    fprintf(stderr, "getaddrinfo(3) error\n");
  }

  for (ai=res; ai; ai=ai->ai_next){
    sock=socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
    if (sock<0){
      fprintf(stderr, "socket error\n");
      continue;
    }
    if ((connect(sock, ai->ai_addr, ai->ai_addrlen))<0){
      close(sock);
      fprintf(stderr, "connect error\n");
      continue;
    }

    freeaddrinfo(res);
    return sock;
  }

  fprintf(stderr, "socket(2)/connect(2) failed\n");
  freeaddrinfo(res);
  exit(1);

}




int main(int argc, char *argv[]){
  int sock;
  sock=open_connection((argc>1 ? argv[1]:"localhost"), "daytime");
  FILE *f;
  f=fdopen(sock, "r");
  char buf[1024];
  fgets(buf, sizeof buf, f);
  fprintf(stdout, "%s\n", buf);
  fclose(f);
  exit(0);
}
