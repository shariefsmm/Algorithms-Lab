/*
	BST
	Programmer's Name:SHARIEF SMM
	Roll no:111601022
*/
#include<stdio.h>
#include<stdlib.h>

struct node
{
	int key;
	struct node *lptr;
	struct node *rptr;
	struct node *pptr;
};
struct node *root;

struct node* search(struct node *r,int item)
{
	if(r==NULL || r->key==item)
	{
		return r;
	}
	if(item<=r->key)
	{
		return search(r->lptr,item);
	}
	else return search(r->rptr,item);
}

void insert(struct node *r,int item)
{
	struct node *current,*parent;
	current=r;
	if(current==NULL)parent=NULL;
	while(current!=NULL)
	{
		if(item==current->key)
		{
			return;
		}
		if(item<current->key)
		{
			parent=current;
			current=current->lptr;
		}
		else
		{
			parent=current;
			current=current->rptr;
		}
	}
	struct node *temp=(struct node *)(malloc(1*sizeof(struct node)));
	temp->key=item;
	temp->lptr=NULL;
	temp->rptr=NULL;
	temp->pptr=NULL;
	if(parent!=NULL)
	{
		if(item<=parent->key)
		{
			parent->lptr=temp;
		}
		else
		{
			parent->rptr=temp;
		}
		temp->pptr=parent;
	}
	if(root==NULL)root=temp;
}
struct node* find_min(struct node *r)
{
	if(r==NULL)return r;
	struct node *temp;
	temp=r;
	while(temp->lptr!=NULL)
	{
		temp=temp->lptr;
	}
	return temp;
}

struct node* find_max(struct node *r)
{
	if(r==NULL)return r;
	struct node *temp;
	temp=r;
	while(temp->rptr!=NULL)
	{
		temp=temp->rptr;
	}
	return temp;
}

void inorder_traversal(struct node *r)
{
	if(r==NULL)return;
	inorder_traversal(r->lptr);
	printf("%d ",r->key);
	inorder_traversal(r->rptr);
}

void postorder_traversal(struct node *r)
{
	if(r==NULL)return ;
	postorder_traversal(r->lptr);
	postorder_traversal(r->rptr);
	printf("%d ",r->key);
}

struct node* find_preceding_key(struct node *r)
{
	if(r==NULL)return r;
	if(r->lptr!=NULL)
	{
		return find_max(r->lptr);
	}
	struct node *parent;
	parent=r->pptr;
	while(parent!=NULL && r!=parent->rptr)
	{
		r=parent;
		parent=r->pptr;
	}
	return parent;
}

void transplant(struct node *u,struct node *v)
{
	struct node *parent;
	parent=u->pptr;
	if(parent==NULL)
	{
		root=v;
	}
	else if(parent->lptr==u)
	{
		parent->lptr=v;
	}
	else parent->rptr=v;
	if(v!=NULL)
	{
		v->pptr=parent;
	}
}

void del(struct node *r)
{
	if(r==NULL)return;
	struct node *temp;
	if(r->lptr==NULL)
	{
		transplant(r,r->rptr);
	}
	else if(r->rptr==NULL)
	{
		transplant(r,r->lptr);
	}
	else
	{
		temp=find_min(r->rptr);
		if(temp->pptr!=r)
		{
			transplant(temp,temp->rptr);
			temp->rptr=r->rptr;
			r->rptr->pptr=temp;
		}
		transplant(r,temp);
		temp->lptr=r->lptr;
		r->lptr->pptr=temp;
	}
	free(r);
}

void print(struct node * root,int space)
{
		if(root==NULL)return;
		space+=10;
		print(root->rptr,space);
		printf("\n");
		for(int i=10;i<space;i++)
		{
			printf(" ");
		}
		printf("%d\n",root->key);
		print(root->lptr,space);
}

int main()
{
	int option,flag,item;
	flag=1;
	struct node *temp;
	struct node *temp1;
	while(flag==1)
	{
		printf("MENU:\n");
  		printf("\t1.)Search for a key\n");
  		printf("\t2.)Inserting a key\n");
  		printf("\t3.)Findminkey\n");
  		printf("\t4.)InOrderTravelsal\n");
		printf("\t5.)PostOrderTraversal\n");
  		printf("\t6.)FindPrecedingKey\n");
  		printf("\t7.)DeleteKey\n");
  		printf("\t8.)PrintTree \n");
  		printf("\t9.)EXIT \n");
  		printf("Enter your choice: ");
  		scanf(" %d",&option);
  		temp=root;
  		switch(option)
  		{
  			case 1:
  					printf("Enter element to search\n");
  					scanf(" %d",&item);
  					temp1=search(temp,item);
  					if(temp1!=NULL)
  					{
  						printf("FOUND\n");
  					}
  					else printf("NOT FOUND\n");
  					break;
  			case 2:
  					printf("Enter element to insert\n");
  					scanf(" %d",&item);
  					insert(temp,item);
  					break;
  			case 3:
  					temp1=find_min(temp);
  					if(temp1==NULL)printf("First create a BST\n");
  					else printf("Mininum is: %d\n",temp1->key);
  					break;
  			case 4:
  					inorder_traversal(temp);
  					printf("\n");
  					break;
  			case 5:
  					postorder_traversal(temp);
  					printf("\n");
  					break;
  			case 6:
  					printf("Enter element\n");
  					scanf(" %d",&item);
  					temp1=find_preceding_key(search(temp,item));
  					if(temp1==NULL)printf("NO PREDECESSOR\n");
  					else printf("Predecessor is %d\n",temp1->key);
  					break;
  			case 7:
  					printf("Enter key to be deleted\n");
  					scanf(" %d",&item);
  					del(search(temp,item));
  					break;
  			case 8:
  					print(temp,0);
  					break;
  			case 9:
  					flag=0;
  					break;
  			default:
  					printf("Enter valid option\n");
  					break;
  		}
	}

}
