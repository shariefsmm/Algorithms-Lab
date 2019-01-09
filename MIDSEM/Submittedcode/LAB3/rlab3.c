#include<stdio.h>
#include<stdlib.h>

struct Graph
{
	int V;
	int step;
	int DCG;
	int children;
	int backvertex;
	int backvertexvisited;

};
struct Graph *graph;

struct Order
{
	int node;
	struct Order *next;
};
struct Order *order=NULL;

struct Adj
{
  int vertex;
  int type;	//1-tree,2-back,3-cross,4-forward
  struct Adj *next;
};

struct Vertices
{
	struct Adj *adj;
	int visited;
	int start;
	int close;
};
struct Vertices **vertices;

void stack(int data)
{
	struct Order *temp1;
	struct Order *temp=(struct Order *)(malloc(1*sizeof(struct Order)));
	temp->node=data;
	temp->next=NULL;
	if(order==NULL)
	{
		order=temp;
		return;
	}
	temp1=order;
	order=temp;
	temp->next=temp1;
	return;
}

void list(struct Adj **head,int x)
{
	struct Adj *temp1;
	struct Adj *temp=(struct Adj*)(malloc(1*sizeof(struct Adj)));
	temp->vertex=x;
	temp->type=0;
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
	int n,i,temp;
	graph=(struct Graph *)(malloc(1*sizeof(struct Graph)));
	scanf(" %d",&n);
	graph->V=n;
	graph->step=1;
	graph->DCG=0;
	graph->children=-1;
	graph->backvertexvisited=-1;
	graph->backvertex=-1;
	vertices=(struct Vertices **)(malloc(n*sizeof(struct Vertices *)));
	for(i=0;i<n;i++)
	{
		struct Vertices *temp=(struct Vertices *)(malloc(1*sizeof(struct Vertices)));
		temp->adj=NULL;
		temp->visited=-1;
		temp->start=0;
		temp->close=0;
		vertices[i]=temp;
	}
	i=0;
	while(i<n)
	{
		scanf(" %d",&temp);
		if(temp==-1)
		{
			i=i+1;
			continue;
		}
		list( &(vertices[i]->adj),temp);
	}
}


void dfs(int r)
{
	vertices[r]->start=graph->step;
	vertices[r]->visited=1;
	struct Adj *temp;
	temp=vertices[r]->adj;
	while(temp!=NULL && graph->DCG==0)
	{
		int v;
		v=temp->vertex;
		if(vertices[v]->visited==-1)	// tree edge
		{
			graph->step=graph->step+1;
			dfs(v);
		}
		else
		{
			if(vertices[v]->close==0)		//back edge
			{
				printf("A directed cycle is detected\n");
				graph->DCG=1;
				graph->children=r;
				graph->backvertex=v;
				stack(r);
				return;
			}
			
		}
		temp=temp->next;
	}
	if(graph->DCG==1)
	{
		if(graph->backvertexvisited==-1) stack(r);
		if(graph->backvertex==r)graph->backvertexvisited=1;
		return;
	}
	stack(r);
	graph->step=graph->step+1;
	vertices[r]->close=graph->step;
	return;
}

// void print()
// {
// 	int flag=0;
// 	if(graph->DCG==1)
// 	{
// 		printf("The vertices of a cycle in the order of a cycle are\n");
// 	}
// 	else
// 	{
// 		printf("Topological ordering is as follows:\n");
// 	}
// 	while(order!=NULL)
// 	{
// 		printf("%d ",order->node);
// 		order=order->next;
// 	}
// 	printf("\n");
// 	return;
// }

void print_order_not_dag()
{
  int flag=0;
  while(order!=NULL)
  {
    if(order->node==graph->backvertex || flag==1)
    {
      flag=1;
      printf("%d ",order->node);
      if(order->node==graph->children)
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

void print_order()
{
	while(order!=NULL)
  	{
    	printf("%d ",order->node);
    	order=order->next;
  	}
  	printf("\n");
}

int main()
{
	take_input();
	for(int i=0;i<graph->V;i++)
	{
		if(vertices[i]->visited==-1)
		{
			dfs(i);
			graph->step=graph->step+1;
		}
	}
	if(graph->DCG!=1)
  	{
    	printf("Topological ordering is as follows:\n");
    	print_order();
  	}
  	else
  	{
    	printf("Vertices in cycle are:\n");
    	print_order_not_dag();
  	}
}