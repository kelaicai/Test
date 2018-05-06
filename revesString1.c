#include<stdio.h>
#include<string.h>
#include<ctype.h>
// 将字符串循环右移一格
char *recvseString1(char *str,int n)
{
  int i=1;
	char tmp;

    tmp=str[0];
		for(i;i<n;i++)
		{
		 str[i-1]=str[i];
		}
		str[n-1]=tmp;
	return str;
}
//将字符串循环移动moveC格
char *revserString2(char *str,int moveC,int n)
{
   int i;
	 int j;
	 char tmp;
	 for(i=0;i<moveC;i++)
	 {
		tmp=str[0];
	  for(j=1;j<n;j++)
		{
	     str[j-1]=str[j];
		}
		str[n-1]=tmp;
	 }
	 return str;
}
//句子倒转
void reverseString_of(char *str,int from,int to)
{ 
    char tmp;
		int i=from;
		int j=to;
		for(;i<j;i++,j--)
		{
		   tmp=str[i];
			 str[i]=str[j];
			 str[j]=tmp;
		}
}

void LeftRoString(char *str,int m,int n)
{
	 m=m%n;//if you want move right m step ,%n is the same effect			
   reverseString_of(str,0,m-1);
	 reverseString_of(str,m,n-1);
	 reverseString_of(str,0,n-1);
}
void SolveStudent(char *str)
{
	char* flag=str;
	
	int count=0;
	int start=0;
	reverseString_of(str,0,strlen(str)-1);
	printf("test str first reverse is  :  %s\n",str);
	while(*str!='\0' && count<strlen(flag))
  {
	if(isspace(*str))
	{
	 str++;
	 count++;
	 start=count;
	}
	else{
    	while(!isspace(*str))
    	{
	         count++;
	        	str++;
    	}
	  reverseString_of(flag,start,count); 
   }
	}
}
int main()
{
#if 0
  char str[10]="abc def";
	printf("%s",recvseString1(str,strlen(str)));
  printf("%s",revserString2(str,2,strlen(str)));
  LeftRoString(str,3,strlen(str));
	printf("%s",str);
#endif
  char str2[20]="i am a student";
	SolveStudent(str2);
	printf("%s\n",str2);
}
