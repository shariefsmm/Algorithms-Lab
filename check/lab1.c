/*
Program Name:.c
Program Description:dfs of digraph using adjacency list
Programmer's Name:SHARIEF SMM
Roll no:111601022
*/
#include<stdio.h>
#include<stdlib.h>

struct node                        /* declare a structure node */
{
    int data;
    struct node *next;
};

typedef struct node node;

struct graph
{
    struct node **head;
    int vertices;
    int *visited;
    int *start;
    int *close;
    int step;
    FILE *p1;
};
typedef struct graph graph;
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

void dfs(int r,graph *g)
{
	g->start[r]=g->step;//start of vertex r
	g->visited[r]=1;   //visited of vertex r
	while(g->head[r]!=NULL)
	{
		if(g->visited[g->head[r]->data]==-1) //if not visited
		{
			fprintf(g->p1,"%d -> %d [color=green];\n",r,g->head[r]->data);
			g->step=g->step+1;
			dfs(g->head[r]->data,g);
		}
		else 	//if visited
		{
			if(g->close[g->head[r]->data]==0)	//condition for backedge
			{
				fprintf(g->p1,"%d -> %d [color=orange];\n",r,g->head[r]->data);
			}
			else if(g->start[r]>g->close[g->head[r]->data])	//condition for crossedge
			{
				fprintf(g->p1,"%d -> %d [color=blue];\n",r,g->head[r]->data);
			}
			else				//condition for forward edge
			{
				fprintf(g->p1,"%d -> %d [color=red];\n",r,g->head[r]->data);
			}
		}
		g->head[r]=g->head[r]->next;
	}
	g->step=g->step+1;
	g->close[r]=g->step; //close of vertex r
	return ;
}

void create_graph(graph **g,int vertices)
{
  int i;
  struct graph *temp=(struct graph*)(malloc(1*sizeof(struct graph)));
  *g=temp;
  (*g)->vertices=vertices;
  (*g)->head=(struct node**)(malloc(vertices*sizeof(struct node*)));
  (*g)->visited=(int*)(malloc(vertices*sizeof(int)));
  (*g)->start=(int*)(malloc(vertices*sizeof(int)));
  (*g)->close=(int*)(malloc(vertices*sizeof(int)));
  (*g)->step=1;
  for(i=0;i<vertices;i++)
  {
    (*g)->head[i]=NULL;
    (*g)->visited[i]=-1;
    (*g)->start[i]=0;
    (*g)->close[i]=0;
  }
}
int main()
{
	FILE *p;
	FILE *p1;
  graph *g;
	node *temp_n;
	int vertices,i,j,temp,r;
	char vs[50];
	scanf(" %s",vs);
	p=fopen(vs,"r");
	if(p==0)
 	{
    		printf("Error in opening the file ");
    		return -1;
 	}
	fscanf(p," %d",&vertices);
  create_graph(&g,vertices);
	/*for(i=0;i<t;i++)
	{
		head[i]=NULL;
		v[i]=-1;
		s[i]=0;
		c[i]=0;
	}*/
	i=0;
	temp_n=NULL;
	while(i<vertices)
	{
		fscanf(p," %d",&temp);
		if(temp==-1)
		{
			//g->head[i]=temp_n;
			//temp_n=NULL;
			i=i+1;
			continue;
		}
		enqueue(temp,&(g->head[i]));
	}
	fclose(p);
	g->p1=fopen("graph.dot","w");
	fprintf(g->p1,"/* tree edge is green\nbackedge is orange\nforward edge is red\ncrossedge is blue\nunvisitededge is black\n*/\n");
	fprintf(g->p1,"digraph output{\n");
	for(i=0;i<vertices;i++)
	{
		if(g->visited[i]==-1)
		{
			dfs(i,g);
      g->step=g->step+1;
		}
	}
	fprintf(g->p1,"}\n");
	fprintf(g->p1,"/*\n");
	fprintf(g->p1,"vertex prettime posttime\n");
	printf("vertex prettime posttime\n");
	for(i=0;i<vertices;i++)
	{
		fprintf(g->p1,"%d \t %d \t %d\n",i,g->start[i],g->close[i]);
		printf("%d \t %d \t %d\n",i,g->start[i],g->close[i]);
	}
	fprintf(g->p1,"*/\n");
	fclose(g->p1);
}
