#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/select.h>
#include<sys/time.h>
#define STDIN 0

int main()
{
	int fd=STDIN;
	fd_set fdset;

	while(1)
	{
		FD_ZERO(&fdset);
		FD_SET(fd,&fdset);


		struct timeval tv={5,0};
		int n=select(fd+1,&fdset,NULL,NULL,&tv);
		if(n==-1)
		{
			perror("select error");
			break;
		}
	   else	if(n==0)
		{
			printf("time out\n");
		}
		else
		{
			if(FD_ISSET(fd,&fdset))
			{
				printf("have data\n");
				char buffer[128]={0};
				read(fd,buffer,127);
				printf("buffer %s\n");
			}
		}
	}
}
