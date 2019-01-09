/*
	BTREE-SEARCH,INSERT
	Programmer's Name:SHARIEF SMM
	Roll no:111601022
*/
#include<stdio.h>
#include<stdlib.h>

struct node
{
	int n;		//total keys
	int leaf;	//wheteher it is leaf or not   1==true,0==false
	int *key;	//array of keys
	struct node **c;	//array of components
};

void print(struct node * x,int space)
{
		int i;
		space+=10;
		if(x->leaf==0)
		{
			for(int i=10;i<space;i++)
				{
					printf(" ");
				}
			printf("[\n");
			for(i=0;i<=x->n-1;i++)
			{
				//space+=10;
				// for(int i=10;i<space;i++)
				// {
				// 	printf(" ");
				// }
				print(x->c[i],space);
				printf("\n");
				for(int i=10;i<space;i++)
				{
					printf(" ");
				}
				printf("%d\n",x->key[i]);
			}
			print(x->c[i],space);
			printf("\n");
			for(int i=10;i<space;i++)
				{
					printf(" ");
				}
			printf("]\n");
		}
		if(x->leaf==1)
		{
			for(int i=10;i<space;i++)
				{
					printf(" ");
				}
			printf("[ ");
			for(i=0;i<=x->n-1;i++)
			{
				printf("%d ",x->key[i]);
			}
			printf("]\n");
		}
}

struct node *root=NULL;	//root node pointer
int t=3;	//t=minimum degree
int path[1000],len;

struct node* create_new_node(int leaf)
{
	struct node *temp=(struct node *)(malloc(1*sizeof(struct node)));
	(temp)->n=0;
	(temp)->leaf=leaf;
	(temp)->key=(int*)(malloc((2*t-1)*sizeof(int)));
	//temp->key=temp1;
	if(leaf==0)
	{
		struct node **temp2=(struct node **)(malloc((2*t)*sizeof(struct node *)));
		(temp)->c=temp2;
	}
	return temp;
}
void split_child(struct node *x,int i)
{
	struct node *y;
	y=x->c[i];
	struct node *z;
	z=create_new_node(0);
	z->leaf=y->leaf;
	z->n=t-1;
	int j;
	for(j=0;j<=t-2;j++)
	{
		z->key[j]=y->key[t+j];
	}
	if(y->leaf!=1)
	{
		for(j=0;j<=(t-1);j++)
		{
			z->c[j]=y->c[t+j];
		}
	}
	y->n=t-1;
	for(j=x->n;j>=i+1;j--)
	{
		x->c[j+1]=x->c[j];
	}
	x->c[i+1]=z;
	for(j=(x->n-1);j>=i;j--)
	{
		x->key[j+1]=x->key[j];
	}
	x->key[i]=y->key[t-1];
	x->n=x->n+1;
}

void insert_nonfull(struct node *x,int k)
{
	int i;
	i=x->n-1;
	if(x->leaf==1)
	{
		while(i>=0 && k<x->key[i])
		{
			x->key[i+1]=x->key[i];
			i=i-1;
		}
		i=i+1;
		x->key[i]=k;
		x->n=x->n+1;
		return;
	}
	else
	{
		while(i>=0 && k<=x->key[i])
		{
			i=i-1;
		}
		i=i+1;
		if(x->c[i]->n==2*t-1)
		{
			split_child(x,i);
			if(k>x->key[i])
			{
				i=i+1;
			}
		}
		insert_nonfull(x->c[i],k);
	}
}

void insert(int k)
{
	if(root->n==2*t-1)
	{
		struct node *s;
		s=create_new_node(0);
		s->c[0]=root;
		split_child(s,0);
		root=s;
	}
	struct node *temp;
	temp=root;
	insert_nonfull(temp,k);
}

int search(struct node *x,int k)
{
	int i=0;
	while(i<=(x->n-1) && k>(x->key[i]))
	{
		i=i+1;
	}
	if(i<=(x->n-1) && k==x->key[i] )
	{
		path[len]=i;
		return 1;
	}
	else if(x->leaf==1)
	{
		return 0;
	}
	else
	{
		path[len]=i;
		len=len+1;
		return search(x->c[i],k);
	}
}

void print_path()
{
	printf("root -> ");
	int i;
	i=0;
	while(i!=len)
	{
		printf("child%d -> ",path[i]);
		i=i+1;
	}
	printf("index%d\n",path[len]);
}

int main()
{
	root=create_new_node(1);
	int total,k,flag;
	struct node *temp;
	scanf(" %d",&total);
	while(total>0)
	{
		total=total-1;
		scanf(" %d",&k);
		insert(k);
		temp=root;
		printf("\nThe tree is as follows:\n");
		print(temp,0);
		printf("\n\n");
	}
	while(1)
	{
		printf("Enter key to search(-1 to exit):\n");
		scanf(" %d",&k);
		if(k==-1)
		{
			return 0;
		}
		len=0;
		temp=root;
		flag=search(temp,k);
		if(flag==0)printf("key %d is not found\n",k);
		else print_path();

	}
}
