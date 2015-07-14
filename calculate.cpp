
#include"calculate.h"

#define LEN 100

#define SHOW show(poly,opr,braket,top)

#define SETTOP 	{ poly[top].k=0; poly[top].xx=0; poly[top].next=NULL; opr[top]=' '; braket[top]=false;  }

void Free(KX p)
{
	KX *q=p.next,*t;
	p.next=NULL;

	while (q!=NULL) {
		t=q->next;
		delete q;
		q=t;
	}
}

int rank(char c)
{
	switch (c)
	{
	case ')':return -1;
	case '+':case '-':return 1;
	case '*':case '/':return 2;
	case '^':return 3;
	}
	return 0;
}

int main()
{
printf(">>> Calculate 2015/01/19 0:42\n\n");
while (true)
{
	KX poly[LEN];
	char opr[LEN];
	int braket[LEN]={0};  // to count the '('	
	int top=0;
	SETTOP;

	char c;
	printf(">>> ");

	while ((c=getchar())!='\n')
	{
		if (c>='0'&&c<='9') {
			if (poly[top].next!=NULL) {
				opr[top]='^';	// x2 means x^2
				++top;
			}
			poly[top].k*=10; poly[top].k+=c-'0';
			continue;
		}

		if (c=='.')
		{
			double x=1;
			c=getchar();
			while (c>='0'&&c<='9')
			{
				x/=10;
				poly[top].k+=x*(c-'0');
				c=getchar();
			}
			if (c=='\n') break;
		}

		if (c=='x'||c=='X') {
			if (poly[top].k!=0 && opr[top]==' ') {
				opr[top]='*';  // 2x means 2*x
				++top;
			}
			KX *p=new KX;
			p->k=1; p->xx=1; p->next=NULL;
			poly[top].next=p;	
			continue;
		}

		if (c=='(') {
			++braket[top-1];
			continue;
		}


		if (c==')')
		{
			while ( top>0 && !braket[top-1] ) {		
				poly[top-1]=GetOpr(opr[top-1])(poly[top-1],poly[top]);	
				SETTOP;	--top;
			}
			--braket[top-1];
			continue;
		}

		int rankOfC=rank(c);
		while ( top>0 && !braket[top-1] && rank(opr[top-1])>=rankOfC)
		{			
			poly[top-1]=GetOpr(opr[top-1])(poly[top-1],poly[top]);		
			SETTOP;	--top;
		}

		opr[top]=c;
		++top;
		SETTOP;
	}
	
	while ( top>0 ) {
		poly[top-1]=GetOpr(opr[top-1])(poly[top-1],poly[top]);
		SETTOP;	--top;
	}

	printf("\n\t=");
	SHOW;	
	printf("\n");
	
	for (int i=0;i<=top;++i) Free(poly[i]);

}

}