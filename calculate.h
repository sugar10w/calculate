#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct node
{
	double k,xx;
	node* next;
	node() { k=0; xx=0; next=NULL; }
} KX;

typedef KX (*OPR)(KX,KX);
OPR GetOpr(char c);

void show(KX poly[],char opr[],int braket[],int top);

bool beInt(double x);