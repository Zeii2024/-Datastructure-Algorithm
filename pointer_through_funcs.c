#include <stdio.h>
#include <stdlib.h>
/*
����ָ���ں���֮��Ĵ���
��Ҫ�ı�ָ����ָ��ĵ�Ԫ��ֵʱ��ʵ�ʴ��ݵ��ǵ�Ԫ�ĵ�ַ����func(&p); 
���ܴ��ݼ��㺯����ֻҪ��֤����ͬһ����ַ����ÿ�������жԵ�ַ�ڵ����ݲ���
����ı���ֵ��
��Ҫע�⣺�����ú�������ָ������붨��Ϊ����ָ�룬��func(type **p)
�����ں����ڣ��������ݲ�������ʹ��*p 
*/ 
typedef struct BTnode{
	int data;
	struct BTnode *lkid;
	struct BTnode *rkid;
}BTnode, BT;
int func1(BT **p);
int func2(BT **q, int n);

int main(void){
	/* 
	BT *p, *q, *f;
	p = q = f = NULL;
	p = (BTnode *)malloc(sizeof(BTnode));
	q = (BTnode *)malloc(sizeof(BTnode));
	f = (BTnode *)malloc(sizeof(BTnode));
	p->lkid = f;
	int a, b;
	
	a = 5;
	b = 3;
	
	p->data = a;
	q = p;
	printf("p = %d\nq = %d\n", p->data, q->data);
	
	f->data = b;
	printf("p->lkid = f = %d\n", p->lkid->data);
	p = f;
	printf("p = %d\nq = %d\n", p->data, q->data);
	printf("q->lkid  = %d\n", q->lkid->data);
	*/
	 
	BT *p1 = NULL;
	BT *q1 = NULL;
	printf("&p1 = %d\n", &p1);
	
	printf("&q1 = %d\n", &q1);
	func1(&p1);
	printf("p1 = %d\n", p1);
	
	printf("&p1 = %d\n", &p1);
	printf("*p1 = %d\n", *p1);
	printf("p1->data = %d\n", p1->data);
	
	
}
int func1(BT **p){
	int n=3;
	*p = (BT*)malloc(sizeof(BT));
	(*p)->data = 2;
	printf("p = %d\n", p);
	printf("&p = %d\n", &p);
	printf("*p->data = %d\n", (*p)->data);
	
	func2(p, n);
	printf("*p->data = %d\n", (*p)->data);
}

int func2(BT **q, int n){
	*q = (BT*)malloc(sizeof(BT));
	(*q)->data = 5;
	(*q)->data = 5 * n;
	printf("q = %d\n", q);
	printf("&q = %d\n", &q);
	printf("*q->data = %d\n", (*q)->data);
	printf("&(*q->data) = %d\n", &((*q)->data));
	  
}
