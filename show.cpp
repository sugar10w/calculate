
#include"calculate.h"

#define TF 5

bool beInt(double x) { return fabs(x-floor(x+0.5))<10e-6;  }
bool equal(double x,double y) { return fabs(x-y)<10e-6; }
void prt(double x)
{
	if (beInt(x)) printf("%d",(int)x);
	else 
	{
		double y;
		for (int i=1;i<TF;++i) 
		{
			y=x*pow(10.0,i);
			if (beInt(y)) { printf("%.*lf",i,x); return; }
		}
		printf("%.*lf",TF,x);
	}

}
void printKX(KX p)
{
	if (equal(p.k,0)) return;
	if (equal(p.xx,0)) { prt(p.k); return; }

	if (!equal(p.k,1)) prt(p.k); 
	printf("x");
	if (!equal(p.xx,1)) { printf("^"); prt(p.xx); }
}

void show(KX poly[],char opr[],int braket[],int top)
{
	for (int i=0;i<=top;++i)
	{
		if (poly[i].next==NULL) printKX(poly[i]);
		else
		{
			printf("[");

			KX *p=&poly[i];

			if (p->k!=0) printKX(*p);
			else { printKX(*p->next); p=p->next; }
			
			if (p!=NULL) p=p->next;
			while (p!=NULL)
			{
				if (p->k > 0) printf("+");
				printKX(*p);
				p=p->next;
			}

			printf("]");
		}
	
		if (i!=top) putchar(opr[i]);
		for (int j=0;j<braket[i];++i) printf("(");
	}
	printf("\n");
}