#include<stdio.h>
#include<assert.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
void sigfun(int a)
{
   wait(NULL);
}

int main()
{
  int sockfd=socket(AF_INET,SOCK_STREAM,0);
	assert(sockfd!=-1);
	
	struct sockaddr_in saddr,caddr;
  memset(&saddr,0,sizeof(saddr));  
	saddr.sin_family=AF_INET;
	saddr.sin_port=htons(6000);//1024,1024-4096,the next shi tmp port
  saddr.sin_addr.s_addr=inet_addr("127.0.0.1");

	int res=bind(sockfd,(struct sockaddr *)&saddr,sizeof(saddr));
  assert(res!=-1);
  
	pid_t ppid=getpid();
	listen(sockfd,5);  // 本身不阻塞

	 // signal(SIGCHLD,sigfun);
	while(1){
		int len =sizeof(caddr);
		int c=accept(sockfd,(struct sockaddr*)&caddr,&len);
		if(c<0)
		{
						continue;
		}
		printf("accept c= %d ,ip : %s\n",c,inet_ntoa(caddr.sin_addr),ntohs(caddr.sin_port));
	 
	  pid_t id=fork();
	/*	if(getpid()==ppid)
		{
		  close(c);
		}*/
	//	assert(id!=-1);
		if(id==0)
		{
      while(1)
			{
				char buffer[128]={0};
	    	//int n=recv(c,buffer,128,0);
				if(recv(c,buffer,127,0)<=0)
				{
				   continue;
				}
				printf("%s",buffer);
				send(c,"ok",2,0);
			}
			close(c);//关闭子进程的c
			
		//	kill(getpid(),SIGCHLD);
			exit(0);
			
		//	kill(ppid,SIGCHLD);
//		  signal(SIGCHLD,sigfun);
			}
			close(c);
		}
	exit(0);
}
