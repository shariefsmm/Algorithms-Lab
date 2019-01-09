/*
	BTREE-SEARCH,INSERT,DELETE
	programmer's Name:SHARIEF SMM
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
void del(struct node *x,int k);
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
int t=3;				//t=minimum degree
int path[1000],len;

struct node* create_new_node(int leaf)
{
	struct node *temp=(struct node *)(malloc(1*sizeof(struct node)));
	(temp)->n=0;
	(temp)->leaf=leaf;
	(temp)->key=(int*)(malloc((2*t-1)*sizeof(int)));
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

void del_leaf(struct node *x,int k)
{
	int i;
	i=0;
	while(i<x->n && k>x->key[i])
	{
		i=i+1;
	}
	if(x->key[i]==k)
	{
		while(i<(x->n-1))
		{
			x->key[i]=x->key[i+1];
			i=i+1;
		}
		x->n=x->n-1;
		return ;
	}
	else return;
}
// merge left child with right child and x->key[i]
// left child and right child are minimun
void merge(struct node *x,int i)
{
	int key;
	struct node *left=NULL;
	struct node *right=NULL;
	left=x->c[i];
	right=x->c[i+1];
	left->n=2*t-1;
	key=x->key[i];
	left->key[t-1]=key;
	int n;
	for(n=0;n<=(t-2);n++)
	{
		left->key[t+n]=right->key[n];
	}
	if(left->leaf==0)
	{
		for(n=0;n<=(t-1);n++)
		{
			left->c[t+n]=right->c[n];
		}
	}
	for(n=i;n<=(x->n-2);n++)
	{
		x->key[n]=x->key[n+1];
	}
	for(n=i+1;n<=(x->n-1);n++)
	{
		x->c[n]=x->c[n+1];
	}
	x->n=x->n-1;
	return ;
}

void del_internal(struct node *x,int k,int i)
{
	struct node *left=NULL;
	struct node *right=NULL;
	int key;
	left=x->c[i];
	right=x->c[i+1];
	if(left->n>(t-1))
	{
		key=left->key[left->n-1];
		del(left,key);
		x->key[i]=key;
		return ;
	}
	else if(right->n>(t-1))
	{
		key=right->key[0];
		del(right,key);
		x->key[i]=key;
		return ;
	}
	else
	{
		merge(x,i);
		left=x->c[i];
		del(left,k);
		return;
	}

}

void shift_left(struct node *x,int i)
{
	struct node *y;//child
	struct node *z;//neighbour to left of child
	y=x->c[i+1];
	z=x->c[i];
	int key1,key2,n;
	key1=z->key[z->n-1];
	key2=x->key[i];
	n=y->n;
	while(n>=1)
	{
		y->key[n]=y->key[n-1];
		n=n-1;
	}
	n=y->n+1;
	if(y->leaf!=1)
	{
		while(n>=1)
		{
			y->c[n]=y->c[n-1];
			n=n-1;
		}
	}
	y->key[0]=key2;
	y->n=y->n+1;
	if(y->leaf!=1)y->c[0]=z->c[z->n];
	x->key[i]=key1;
	z->n=z->n-1;
	return;
}

void shift_right(struct node *x,int i)
{
	struct node *y;//child
	struct node *z;//neighbour to right of child
	y=x->c[i];
	z=x->c[i+1];
	int key1,key2,n;
	key1=z->key[0];
	key2=x->key[i];
	y->key[y->n]=key2;
	x->key[i]=key1;
	if(z->leaf!=1)y->c[y->n+1]=z->c[0];
	y->n=y->n+1;
	n=0;
	while(n<=(z->n-2))
	{
		z->key[n]=z->key[n+1];
		n=n+1;
	}
	n=0;
	if(z->leaf!=1)
	{
		while(n<=(z->n-1))
		{
			z->c[n]=z->c[n+1];
			n=n+1;
		}
	}
	z->n=z->n-1;
	return;
}

int del_non_internal(struct node *x,int i)
{
	struct node *left=NULL;
	struct node *right=NULL;
	struct node *child=NULL;
	int key;
	child=x->c[i];
	if(i!=0)left=x->c[i-1];
	if(i!=x->n)right=x->c[i+1];
	if(left!=NULL && left->n>(t-1))
	{
		shift_left(x,i-1);
		return 1;
	}
	else if(right!=NULL && right->n>(t-1))
	{
		shift_right(x,i);
		return 1;
	}
	else
	{
		if(left!=NULL)
		{
			merge(x,i-1);
			return 2;
		}
		else if(right!=NULL)
		{
			merge(x,i);
			return 1;
		}
	}
}

void del(struct node *x,int k)
{
	int i;
	i=0;
	if(x->leaf==1)
	{
		del_leaf(x,k);
		return ;
	}
	while(i<x->n && k>x->key[i])
	{
		i=i+1;
	}
	if(k==x->key[i])
	{
		del_internal(x,k,i);
	}
	else
	{
		struct node *child;
		child=x->c[i];
		if(child->n>(t-1))
		{
			del(child,k);
		}
		else
		{
			int flag;
			flag=del_non_internal(x,i);
			if(flag==2)
			{
				child=x->c[i-1];
			}
			else
			{
				child=x->c[i];
			}
			del(child,k);
		}
	}
	return ;
}

int main()
{
	root=create_new_node(1);
	int total,k,flag,option,flag1;
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
	// while(1)
	// {
	// 	printf("Enter key to search(-1 to exit):\n");
	// 	scanf(" %d",&k);
	// 	if(k==-1)
	// 	{
	// 		break;
	// 	}
	// 	len=0;
	// 	temp=root;
	// 	flag=search(temp,k);
	// 	if(flag==0)printf("key %d is not found\n",k);
	// 	else print_path();

	// }
	flag1=1;
	while(flag1==1)
	{
		printf("MENU:\n");
		printf("\t1: Insert\n");
		printf("\t2: Delete\n");
		printf("\t3: Search\n");
		printf("\t4: Display\n");
		printf("\t5:Exit\n");
		scanf(" %d",&option);
		switch(option)
		{
			case 1:
					printf("Enter key to be inserted\n");
					scanf(" %d",&k);
					insert(k);
					printf("\nThe tree is as follows:\n");
					temp=root;
					print(temp,0);
					printf("\n\n");
					break;
			case 2:
					printf("Enter key to be deleted\n");
					scanf(" %d",&k);
					temp=root;
					del(temp,k);
					if(root->n==0)
					{
						if(root->leaf!=1)root=root->c[0];
						else
						{
							root=create_new_node(1);
						}
					}
					printf("\nThe tree is as follows:\n");
					temp=root;
					print(temp,0);
					printf("\n\n");
					break;
			case 3:
					printf("Enter key to search\n");
					scanf(" %d",&k);
					len=0;
					temp=root;
					flag=search(temp,k);
					if(flag==0)printf("key %d is not found\n",k);
					else print_path();
					break;
			case 4:
					temp=root;
					printf("\nThe tree is as follows:\n");
					print(temp,0);
					printf("\n\n");
					break;
			case 5:
					flag1=0;
					break;
			default:
					printf("Enter valid option\n");
  					break;
		}
	}
	return 0;
}
