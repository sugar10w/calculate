#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct node
{
	double k,xx;	//其中k为系数，xx为次数
	node* next;
	node() { k=0; xx=0; next=NULL; }
} KX;	//定义KX为多项式，利用链表存储；

typedef KX (*OPR)(KX,KX);	//定义OPR为二元多项式运算符

OPR GetOpr(char c);

void show(KX poly[],char opr[],int braket[],int top);

bool beInt(double x);