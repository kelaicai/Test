#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>
//将最后一个位删除
/*
直接右移 
*/
int delete_last_bit(int num)
{
	return ((num) >> 1);
}

//在最后一个位加0   /*直接左移，自动补零*/
int add_last_zero(int num)
{
	return ((num) << 1);
}

//在最后一个位加1  /*先左移再或1*/ 
int add_last_one(int num)
{
	return (((num) << 1) | 1);
}

//将最后一位变为1  /*  直接或1  */
int set_last_one(int num)
{
	return ((num) | 1);
}

//将最后一为置为零    /* 将数与1异或   */
int set_last_zero(int num)
{
	return ((num) ^ (1 << 0));
}

//将最后一位取反    /*将数字异或1*/
int set_last_last_con(int num)
{
	return ((num) ^ 1);
}

//将第N位置1    /*由于位是从0（本位）到n-1位  所以下面代码区分了 n=0 和 不等于0的情况*/
int set_n_to_one(int num, int n)
{
	if(n==0)
	{
		return (num | 1);
	 } 
	return (num | 1<<(n-1));
}

//将第N位置为零    /*先将1挪到第第n位*/
int set_n_to_zero(int num, int n)
{
	return ((num)& ~(1<<n));
}

//将右数第N的取反
int set_n_to_con(int num,int n)
{
	if(n==0)
	{
		return num^1;
	 } 
	return  ((num) ^ (1 <<(n-1)));
}

//获得最后三位
int get_last_three(int num)
{
	return num& 7;
}


//获取末尾n位
int get_last_n_bit(int num, int n)
{
	int i=0;
	int tmp=1;
	for(i;i<n;i++)
	{
		tmp=tmp*2;
	}
	return num &(tmp-1);
}
//获取第N位
int get_n_bit(int num, int n)
{
	if(n==0)
	{
		return num&1;
	}
	return (num>>(n-1))&1;
}

//将右起第一个0变为1
int seq_first_zero_to_one(int num)
{
	int tmp=num;
	int i=1;
	while(get_n_bit(num,i))
	{
		i++;
	}
	 num=set_n_to_one(num,i);
	return num;
}

//将右开始的零变为1     
/*num此时必然是偶数，或者说2的n次方，它的前一个是全
一，所以 和它的前一个值 或 便可以轻易将后面的1补上*/ 
int seq_zero_to_one(int num)
{
	return (num | (num-1));
}

#define ENTER printf("\n");

//将连续的1置为0：现将逐个获取判断是否是1，

/*与上面类似的，包含全一的数字，一般都是2的n次方，减一所以，与它的下一个数做与运算即可将后面的1置为0*/
int seq_one_to_zero(int num)
{
    
	return  num=num&(num+1);
}

int display_binary(int src)
{
	if (src == 0)
	{
		printf("0\n");
	}

	int binary[20], i;
	for (i = 0; src; i++)
	{
		binary[i] = src%2;
		src/= 2;
	}
	for (i = i - 1; i >= 0; i--)
	{
		printf("%d", binary[i]);
	}
	return 0;
}




//计算一个数中1的个数
int count(int num)
{
  int count = 0;
  while(num != 0) 
  {
    num = num & (num-1);
    count++;
  }
  return count; 	
} 
void bit_operation( )
{


	printf("功能    | 实例  | 运算\n");
	printf("101101去掉最后一位         ");
	display_binary(delete_last_bit(45));
	ENTER
	
	printf("101101在最后加个0          ");
	display_binary( add_last_zero(45));
	ENTER
	
	printf("101101在最后加个1           ");
	display_binary(add_last_one(45));
	ENTER
	
    printf("101100(44)将最后一个变为1   ");
	display_binary(set_last_one(44));
	ENTER

    printf("101101(45)将最后一个变为0   ");
	display_binary(set_last_zero(45));
	ENTER
	
	printf("101101(45)将最后一位取反    ");
	display_binary(set_last_last_con(45));
	ENTER
	
	printf("101001(41)将右数第k个变为1 k=3    ");
	display_binary(set_n_to_one(41,3));
	ENTER
	
	printf("101001(45)将右数第k个变为0 k=3    ");
	display_binary(set_n_to_zero(45,3));
	ENTER
	
	printf("101001(45)将右数第k个变为0 k=3    ");
	display_binary(set_n_to_zero(45,3));
	ENTER
	
	printf("101001(41)将右数第k个位取反 k=3    ");
	display_binary(set_n_to_con(41,3));
	ENTER
	
	printf("1101101(109)获取最后三位 k=3       ");
	display_binary(get_last_three(109));
	ENTER
	
	printf("1101101(109)取末尾k位 k=5          ");
	display_binary(get_last_n_bit(109,5));
	ENTER
	
	printf("1101101(109)取右数第k位 k=4        ");
	display_binary(get_n_bit(109,4));
	ENTER
	
	printf("100101111(303)将连续的1变为0         ");
	display_binary(seq_one_to_zero(303));
	ENTER
	
	printf("100101111(303)将右数第一个0变为1         ");
	display_binary(seq_first_zero_to_one(303));
	ENTER
	
	printf("11011000(216)将右边连续的0变为1         ");
	display_binary(seq_zero_to_one(216));
	ENTER
	

}
int main()
{
	
	bit_operation();
	
	printf("\n");
	int cou=count(15);
	printf("15 has %d 1\n",cou);
	system("pause");


}
