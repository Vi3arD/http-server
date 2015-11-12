#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#define BUFSIZE 1024

int main(int argc, char** argv) {
    	int sd;
    	struct sockaddr_in saddr;
	int read;
    	char buf[BUFSIZE];

	if (argc < 3) {
		puts("Usage: ./httpclient <IP-addres> <filepath>");
		return 1;
	}

	if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		puts("socket create error");
		return 1;
	}

	bzero(&saddr, sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(8080);
	if (inet_addr(argv[1], &saddr.sin_addr.s_addr) == 0) {
		puts("IP addres error");
		return 1;	
	}

	if (connect(sd, (struct sockaddr*)&saddr, sizeof(saddr)) != 0) {
		puts("Connection error");
		return 1;	
	}

	sprintf(buf, "GET %s HTTP/1.0\r\n\r\n", argv[2]);
    	send(sd, buf, strlen(buf), 0);

	do {
		bzero(buf, sizeof(buf));
		read = recv(sd, buf, sizeof(buf), 0);
		if (read > 0) printf("%s", buf);
	}
	while (read > 0);

	close(sd);
	return 0;
}
