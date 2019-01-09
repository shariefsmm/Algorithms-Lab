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
    struct node *order;
    int vertices;
    int *visited;
    int *start;
    int *close;
    int step;
    int DCA;
    int backvertex;
    int backvertexvisited;
    int children;
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
void print_order(node *order)
{
  while(order!=NULL)
  {
    printf("%d ",order->data);
    order=order->next;
  }
  printf("\n");
}

void print_order_not_dag(node *order,int backvertex,int children)
{
  int flag=0;
  while(order!=NULL)
  {
    if(order->data==backvertex || flag==1)
    {
      flag=1;
      printf("%d ",order->data);
      if(order->data==children)
      {
        flag=0;
        printf("\n");
        return;
      }
    }
    order=order->next;
  }
  printf("\n");
}
void dfs(int r,graph *g)
{
	g->start[r]=g->step;//start of vertex r
	g->visited[r]=1;   //visited of vertex r
	while(g->head[r]!=NULL && g->DCA==0)
	{
		if(g->visited[g->head[r]->data]==-1) //if not visited
		{
			g->step=g->step+1;
			dfs(g->head[r]->data,g);
		}
		else 	if(g->close[g->head[r]->data]==0)	//condition for backedge
		{
        printf("A directed cycle is detected\n");
        g->DCA=1;
        g->children=r;
        g->backvertex=g->head[r]->data;
        enqueue(r,&(g->order));
        return ;
		}
		g->head[r]=g->head[r]->next;
	}
  if(g->DCA==1)
  {
    if(g->backvertexvisited!=1)enqueue(r,&(g->order));
    if(g->backvertex==r)
    {
      g->backvertexvisited=1;
    }
    return;
  }
  enqueue(r,&(g->order));
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
  (*g)->order=(struct node*)(malloc(1*sizeof(struct node)));
  (*g)->visited=(int*)(malloc(vertices*sizeof(int)));
  (*g)->start=(int*)(malloc(vertices*sizeof(int)));
  (*g)->close=(int*)(malloc(vertices*sizeof(int)));
  (*g)->step=1;
  for(i=0;i<vertices;i++)
  {
    (*g)->head[i]=NULL;
    (*g)->order=NULL;
    (*g)->visited[i]=-1;
    (*g)->start[i]=0;
    (*g)->close[i]=0;
    (*g)->DCA=0;
    (*g)->backvertex=-1;
    (*g)->backvertexvisited=-1;
    (*g)->children=-1;
  }
}
int main()
{
	FILE *p;
  graph *g;
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
	while(i<vertices)
	{
		fscanf(p," %d",&temp);
		if(temp==-1)
		{
			i=i+1;
			continue;
		}
		enqueue(temp,&(g->head[i]));
	}
	fclose(p);
	for(i=0;i<vertices;i++)
	{
    if(g->DCA==1)
    {
      break;
    }
		if(g->visited[i]==-1)
		{
			dfs(i,g);
      g->step=g->step+1;
		}
	}
	if(g->DCA!=1)
  {
    printf("Topological ordering is as follows:\n");
    print_order(g->order);
  }
  else
  {
    printf("Vertices in cycle are:\n");
    print_order_not_dag(g->order,g->backvertex,g->children);
  }
}
