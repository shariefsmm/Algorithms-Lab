#include<stdio.h>
#include<stdlib.h>
struct node
{
	int data;
	struct node *next;
};
typedef struct node node;
void function(node **p)
{
	struct node *temp=(struct node*)(malloc(1*sizeof(struct node)));
	temp->data=150;
	temp->next=*p;
	*p=temp;
	node *temp1;
	temp1=*p;
	while(temp1!=NULL)
	{
		printf("node in fun %d\n",temp1->data);
		temp1=temp1->next;
	}
}

int main()
{
	int a[100],*p;
	a[5]=90;
	p=a;
	printf("%d\n",p[5]);
}
