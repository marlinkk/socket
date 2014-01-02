#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h> 
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#define MYPORT 3490
#define BACKLOG 5
main()
{
int sockfd, new_fd;
struct sockaddr_in srvaddr;
struct sockaddr_in cliaddr;
int sin_size;
if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
{
	perror("socket error");
	exit(1);
}
bzero(&srvaddr, sizeof(srvaddr));
srvaddr.sin_family = AF_INET;
srvaddr.sin_port = htons(MYPORT);
if(bind(sockfd, (struct sockaddr *)&srvaddr, sizeof(struct sockaddr)) == -1)
{
	perror("bind error");
	exit(1);
}
if(listen(sockfd, BACKLOG) == -1)
{
	perror("listen error");
	exit(1);
}
for(;;)
{
	sin_size = sizeof(struct sockaddr_in);
	if((new_fd = accept(sockfd, (struct sockaddr *)&cliaddr, &sin_size)) == -1)
	{
		perror("accept error");
		continue;
	}
	printf("server: got connection from %s\n", inet_ntoa(cliaddr.sin_addr));
	if(write(new_fd, "Hello, Network!\n", 14) == -1)
		perror("write error!");
	close(new_fd);
}
	close(sockfd);
}
