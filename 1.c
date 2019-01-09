/*
Program Name:.c
Program Description:dfs of digraph using adjacency list
programmer's Name:SHARIEF SMM
Roll no:111601022
*/
#include<stdio.h>
#include<stdlib.h>

struct node                        /* declare a structure node */
{
    int data;
    struct node *next;
};


//tree edge is green
//backedge is orange
//forward edge is red
//crossedge is blue
//unvisitededge is black

void enqueue(int x,struct node **head)
{
	struct node *temp1;
	struct node *temp=(struct node*)(malloc(1*sizeof(struct node)));
	temp->data=x;
	temp->next=NULL;
	temp1=*head;
	if(*head==NULL)
	{
		*head=temp;
		return;
	}
	*head=temp;
	temp->next=temp1;
}

int dfs(int r,int s[],int c[],struct node *head[],int step,int v[],FILE *p1)
{
	s[r]=step;//start of vertex r
	v[r]=1;   //visited of vertex r
	while(head[r]!=NULL)
	{
		if(v[head[r]->data]==-1) //if not visited
		{
			fprintf(p1,"%d -> %d [color=green];\n",r,head[r]->data);
			step=step+1;
			step=dfs(head[r]->data,s,c,head,step,v,p1);
		}
		else 	//if visited
		{
			if(c[head[r]->data]==0)	//condition for backedge
			{
				fprintf(p1,"%d -> %d [color=orange];\n",r,head[r]->data);
			}
			else if(s[r]>c[head[r]->data])	//condition for crossedge
			{
				fprintf(p1,"%d -> %d [color=blue];\n",r,head[r]->data);
			}
			else				//condition for forward edge
			{
				fprintf(p1,"%d -> %d [color=red];\n",r,head[r]->data);
			}
		}
		head[r]=head[r]->next;
	}
	step=step+1;
	c[r]=step; //close of vertex r
	return step;
}

int main()
{	
	FILE *p;
	FILE *p1;
	int t,i,j,temp=0,s[100],c[100],r,step=1,v[100];
	char vs[50];
	struct node *head[100];
	printf("Enter input file name: ");
	scanf(" %s",vs);
	p=fopen(vs,"r");
	if(p==0) 
 	{ 
    		printf("Error in opening the file ");
    		return -1;
 	}
	fscanf(p," %d",&t);
	for(i=0;i<t;i++)
	{
		head[i]=NULL;
		v[i]=-1;
		s[i]=0;
		c[i]=0;
	}
	i=0;
	while(i<t)
	{
		fscanf(p," %d",&temp);
		if(temp==-1)
		{
			i=i+1;
			continue;
		}
		enqueue(temp,&head[i]);
	}
	fclose(p);
	printf("Enter root node: ");
	scanf(" %d",&r);
	p1=fopen("graph.dot","w");
	fprintf(p1,"/* tree edge is green\nbackedge is orange\nforward edge is red\ncrossedge is blue\nunvisitededge is black\n*/\n");
	fprintf(p1,"digraph output{\n");
	temp=dfs(r,s,c,head,step,v,p1);

	for(i=0;i<t;i++)
	{
		if(v[i]==-1)
		{
			while(head[i]!=NULL)
			{
				fprintf(p1,"%d -> %d ;\n",i,head[i]->data);
				head[i]=head[i]->next;
			}
		}
	}
	fprintf(p1,"}\n");
	fprintf(p1,"/*\n");
	fprintf(p1,"vertex prettime posttime\n");
	printf("vertex prettime posttime\n");
	for(i=0;i<t;i++)
	{
		fprintf(p1,"%d \t %d \t %d\n",i,s[i],c[i]);
		printf("%d \t %d \t %d\n",i,s[i],c[i]);
	}
	fprintf(p1,"*/\n");
	fclose(p1);
}
