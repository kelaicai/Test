#include<stdio.h>
#include<assert.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>

void *work_thread(void *arg)
{
  int c=(int)arg;
	while(1)
	{
		char buffer[128];
	int	n=recv(c,buffer,127,0);
		printf("c=%d =%s\n",c,buffer);
		send(c,"ok",2,0);
	}
	close(c);
	pthread_exit(0);

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

	listen(sockfd,5);  // 本身不阻塞

	while(1){
		int len =sizeof(caddr);
		int c=accept(sockfd,(struct sockaddr*)&caddr,&len);
		if(c<0)
		{
						continue;
		}
		
			pthread_t id;
			pthread_create(&id,NULL,work_thread,(void *)c);
		}
		
	//	close(c);
	
	exit(0);
}
