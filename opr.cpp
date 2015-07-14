
#include"calculate.h"


KX copyKX(KX p0)
{
	KX *p=new KX;
	KX *q=&p0;
	KX *ans=p;

	while (q!=NULL)
	{
		*p=*q;
		q=q->next;
		if (q==NULL) break;
		p->next=new KX;
		p=p->next;
	}
	p->next=NULL;

	return *ans;
}

KX add(KX p1,KX p2)
{
	KX *q1=p1.next;
	KX *q2=p2.next;
	
	KX p;
	KX *q=&p;

	p.k=p1.k+p2.k; 


	while (true)
	{
		if (q1==NULL && q2==NULL) break;
		if (q1==NULL) {	q->next=q2;	break; }
		if (q2==NULL) {	q->next=q1;	break; }
		if (q1->xx < q2->xx) {
			q->next=q1;
			q=q1;
			q1=q1->next;
			q->next=NULL;
			continue;
		}
		if (q1->xx > q2->xx) {
			q->next=q2;
			q=q2;
			q2=q2->next;
			q->next=NULL;
			continue;
		}
		if (q1->xx==q2->xx) {
			q1->k+=q2->k;
			KX *t=q2->next;
			delete q2; 
			q2=t;
			q->next=q1;
			q=q1;
			q1=q1->next;
			q->next=NULL;
			continue;
		}
	}
	return p;
}
KX dec(KX p1,KX p2)
{
	KX *q=&p2;
	while (q!=NULL)
	{
		q->k=-q->k;
		q=q->next;
	}
	return add(p1,p2);
}
KX mlt(KX p1,KX p2)
{
	KX p0;
	KX d;
	KX ans;

	if (p2.k!=0) {
		p0=copyKX(p1);
		KX *q=&p0;
		while (q!=NULL) {
			q->k*=p2.k;
			q=q->next;
		}
		ans=add(ans,p0);
	}

	if (p2.next==NULL) return ans;
	d=p2;

	do
	{
		d=*d.next;
		if (d.k!=0)
		{
			p0=copyKX(p1);
			if (p0.k!=0) {
				KX *t=new KX;
				*t=p0;
				p0.k=0;p0.xx=0;p0.next=t;
			}
			KX *q=p0.next;
			while (q!=NULL) {
				q->k*=d.k;
				q->xx+=d.xx;
				q=q->next;
			}
			ans=add(ans,p0);
		}
	} while (d.next!=NULL);

	return ans;
}
KX div(KX p1,KX p2)
{
	if (p2.next!=NULL) { printf("\n Warning: divide x.\n"); p2=*p2.next; }
	if (p2.k==0) { printf("\n Error: Can't divide 0. \n");  }
	
	KX *q=&p1;
	while (q!=NULL) {
		q->k/=p2.k;
		q->xx-=p2.xx;
		q=q->next;
	}

	return p1;
}
KX xxx(KX p1,KX p2)
{
	if (p2.next!=NULL) { printf("\n Error: power x. \n"); }
	if (!beInt(p2.k)) { printf("\n Warning: power fractions. \n");  }
	if (p2.k<0) { printf("\n Warning: power negatives. \n");  }
	
	KX ans;

	if (p1.next==NULL) {
		p1.k=pow(p1.k,p2.k); return p1;
	}
	else if (p1.k==0  && p1.next->next==NULL) {
		p1.next->k=pow(p1.next->k,p2.k);
		p1.next->xx*=p2.k; return p1;
	}


	int x=(int)floor(p2.k+0.5);
	if (x==0) ans.k=1;
	else
	{
		ans=copyKX(p1);
		for (int i=0;i<x-1;++i) ans=mlt(ans,p1);
	}

	return ans;
}

OPR GetOpr(char c)
{
	switch (c)
	{
	case '+':return add;
	case '-':return dec;
	case '*':return mlt;
	case '/':return div;
	case '^':return xxx;
	}
	
	printf("\n Error: '%c' unknown operation...\n",c);	
	return add;

}
