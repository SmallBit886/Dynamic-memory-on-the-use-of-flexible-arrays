#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
//6. 柔性数组
// 6.1 柔性数组的特点：
//结构中的柔性数组成员前面必须至少一个其他成员。
//sizeof 返回的这种结构大小不包括柔性数组的内存。
//包含柔性数组成员的结构用malloc()函数进行内存的动态分配，并且分配的内存应该大于结构的大
//小，以适应柔性数组的预期大小。
// 
//typedef struct st_type
//{
//	int i;
//	int a[];//柔性数组成员//数组的大小是可以调整大小的
//}type_a;
//
//int main()
//{
//	type_a s = { 1,{1,2,3} };
//	printf("%d\n", sizeof(type_a));//4字节
//
//	type_a* ps = (type_a*)malloc(sizeof(type_a) + 5 * sizeof(int));//动态开辟内存大小  4字节 +20字节
//	ps->i = 100;
//	int i = 0;
//	for (i = 0; i < 5; i++)
//	{
//		ps->a[i] = i;//0,1,2,3,4
//	}
//
//	//在开辟更大内存
//	type_a* ptr = realloc(ps, 44);//11字节
//	if (ptr != NULL)
//	{
//		ps = ptr;
//	}
//	for (i = 5; i < 10; i++)
//	{
//		ps->a[i] = i;
//	}
//	for (i = 0; i < 10; i++)
//	{
//		printf("%d ", ps->a[i]);//0 1 2 3 4 5 6 7 8 9
//	}
//	//释放内存
//	free(ps);
//	ps = NULL;
//	return 0;
//}

struct S
{
	int n;
	int* arr;
};

int main()
{
	printf("%d\n", sizeof(struct S));//8字节
	struct S* ps = (struct S*)malloc(sizeof(struct S));
	ps->arr = malloc(5 * sizeof(int));
	int i = 0;
	for (i = 0; i < 5; i++)
	{
		ps->arr[i] = i;
	}
	//调整大小
	int* ptr = realloc(ps->arr, 10 * sizeof(int));
	if (ptr != NULL)
	{
		ps->arr = ptr;
	}
	for (i = 5; i < 10; i++)
	{
		ps->arr[i] = i;
	}
	for (i = 0; i < 10; i++)
	{
		printf("%d ", ps->arr[i]);//0 1 2 3 4 5 6 7 8 9
	}
	free(ps->arr);
	ps->arr = NULL;
	free(ps);
	ps = NULL;
	return 0;
}

/*
上述 代码1 和 代码2 可以完成同样的功能，但是 方法1 的实现有两个好处：
第一个好处是：方便内存释放
如果我们的代码是在一个给别人用的函数中，你在里面做了二次内存分配，并把整个结构体返回给
用户。用户调用free可以释放结构体，但是用户并不知道这个结构体内的成员也需要free，所以你
不能指望用户来发现这个事。所以，如果我们把结构体的内存以及其成员要的内存一次性分配好
了，并返回给用户一个结构体指针，用户做一次free就可以把所有的内存也给释放掉。
第二个好处是：这样有利于访问速度.
连续的内存有益于提高访问速度，也有益于减少内存碎片。（其实，我个人觉得也没多高了，反正
你跑不了要用做偏移量的加法来寻址）
*/