/*
	FLOYD-WARSHAL
	Programmer's Name:SHARIEF SMM
	Roll no:111601022
*/
#include<stdio.h>
#include<stdlib.h>

struct Adj
{
	int vertex;
	int weight;
	struct Adj *next;
};
struct Adj **adj;
int n,m,d[100][100],prev[100][100];

void enqueue(struct Adj **head,int x,int w)
{
	struct Adj *temp1;
	struct Adj *temp=(struct Adj*)(malloc(1*sizeof(struct Adj)));
	temp->vertex=x;
  	temp->weight=w;
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

void take_input()
{
	scanf(" %d",&n);
	scanf(" %d",&m);
	adj=(struct Adj **)(malloc(n*sizeof(struct Adj *)));
	int temp,i,j,w;
	temp=0;
	while(temp<m)
	{
		temp=temp+1;
		scanf(" %d %d %d",&i,&j,&w);
		enqueue(&adj[i],j,w);
	}
}

void floyd_warshall()
{
	int i,j,k;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(i!=j)
			{
				d[i][j]=100000;
				prev[i][j]=-1;
			}
			else
			{
				d[i][i]=0;
				prev[i][i]=i;
			}
		}
	}
	for(i=0;i<n;i++)
	{
		struct Adj *temp;
		temp=adj[i];
		while(temp!=NULL)
		{
			d[i][temp->vertex]=temp->weight;
			prev[i][temp->vertex]=i;
			temp=temp->next;
		}
	}
	for(k=0;k<n;k++)
	{
		for(i=0;i<n;i++)
		{
			for(j=0;j<n;j++)
			{
				if(d[i][j]>(d[i][k]+d[k][j]))
				{
					d[i][j]=d[i][k]+d[k][j];
					prev[i][j]=prev[k][j];
				}
			}
		}
	}
}

void print()
{
	int i,j;
	printf("The distances are :\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(i!=j)printf("%d ",d[i][j]);
			else printf("0 ");
		}
		printf("\n");
	}
}

int main()
{
	take_input();
	floyd_warshall();
	print();
}
