#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/select.h>
#include<string.h>
#include<sys/time.h>
#include<assert.h>

#define MAX 10
int create_socket()
{
	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1)
	{
		return -1;
	}

	struct sockaddr_in saddr;
	memset(&saddr,0,sizeof(saddr));

	saddr.sin_family=AF_INET;
	saddr.sin_port=htons(6000);
	saddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    
	bind(sockfd,(struct sockaddr *)&saddr,sizeof(saddr));
   
	listen(sockfd,5);

	return sockfd;
}

int fds_init(int fds[])
{
	 int i=0;
	 for(;i<MAX;i++)
	 {
	 	fds[i]=-1;   // nagtive num reperent invlued
	 }
}

void fds_add(int fds[],int fd)
{
	int i=0;
	for(;i<MAX;i++)
	{
		if(fds[i]==-1)
		{
			fds[i]=fd;
			break;
		}
	}
}

void fds_del(int fds[],int fd)
{
	int i=0;
	for(;i<MAX;i++)
    {
		if(fds[i]==fd)
		{
			fds[i]=-1;
			break;
		}
	}

}
int main()
{
   		int sockfd=create_socket();

		int fds[MAX ];

		fds_init(fds);
        fds_add(fds,sockfd);

		fd_set fdset;
		while(1)
		{
			FD_ZERO(&fdset);
			
			int maxfd=-1;
			int i=0;

			for(;i<MAX;i++)
			{
				if(fds[i]!=-1)   // ???
				{
					FD_SET(fds[i],&fdset);
					if(maxfd<fds[i])
					{
						maxfd=fds[i];
					}
				}
			}

			struct timeval tv={5,0};
			int n=select(maxfd+1,&fdset,NULL,NULL,&tv);
			if(n==-1)
			{
				perror("select error");
				break;
			}
			else if(n==0)
			{
				printf("timeout\n");
				continue;
			}
			else
			{
				int i=0;
				for(;i<MAX;i++)
				{
					if(fds[i]==-1)
					{
						continue;
					}
					if(FD_ISSET(fds[i],&fdset))
					{
						if(fds[i]==sockfd)  //监听套接字？
						{
							struct sockaddr_in caddr;
							int len=sizeof(caddr);
							int c=accept(sockfd,(struct sockaddr*)&caddr,&len);
							if(c<0)
							{
								continue;
							}
         
							printf("accept :%d\n",c);
							fds_add(fds,c);
						}	
						else
						{  //连接套接字
							char  buffer[128]={0};
							if((recv(fds[i],buffer,127,0))<=0)
							{
	    						close(fds[i]);   //close file descriptor
								fds_del(fds,fds[i]);
								printf("CLient over\n");
							}
							printf("buffer %d  =%s\n",fds[i],buffer);
							send(fds[i],"ok",2,0);
						}
					}
				}
			}
		}
}
