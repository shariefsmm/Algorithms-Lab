#include<stdio.h>
#include<stdlib.h>

struct Graph
{
	int V;
	int step;
};
struct Graph *graph;

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


void dfs(int r)		// this line is implemented at v times
{
	vertices[r]->start=graph->step;
	vertices[r]->visited=1;
	struct Adj *temp;
	temp=vertices[r]->adj;
	while(temp!=NULL)	// total edges 
	{
		int v;
		v=temp->vertex;
		if(vertices[v]->visited==-1)	// tree edge
		{
			temp->type=1;
			graph->step=graph->step+1;
			dfs(v);
		}
		else
		{
			if(vertices[v]->close==0)		//back edge
			{
				temp->type=2;
			}
			else if( (vertices[r]->start)>(vertices[v]->close) ) //cross edge
			{
				temp->type=3;
			}
			else 	//forward edge
			{
				temp->type=4;
			}
		}
		temp=temp->next;
	}
	graph->step=graph->step+1;
	vertices[r]->close=graph->step;
	return;
}

void print()
{
	int i;
	FILE *p;
	p=fopen("graph.dot","w");
	printf("vertex prettime posttime\n");
	fprintf(p,"/* tree edge is green\nbackedge is orange\nforward edge is red\ncrossedge is blue\nunvisitededge is black\n*/\n");
    for(i=0;i<graph->V;i++)
    {
		//fprintf(p1,"%d \t %d \t %d\n",i,vertices[i]->start,vertices[i]->close);
		printf("%d \t %d \t %d\n",i,vertices[i]->start,vertices[i]->close);
	}
	fprintf(p,"digraph output{\n");
	for(i=0;i<graph->V;i++)
	{
		struct Adj *temp;
		temp=vertices[i]->adj;
		while(temp!=NULL)
		{
			int v;
			v=temp->vertex;
			if(temp->type==1)
			{
				fprintf(p,"%d -> %d [color=green];\n",i,v);
			}
			if(temp->type==2)
			{
				fprintf(p,"%d -> %d [color=orange];\n",i,v);
			}
			if(temp->type==3)
			{
				fprintf(p,"%d -> %d [color=blue];\n",i,v);
			}
			if(temp->type==4)
			{
				fprintf(p,"%d -> %d [color=red];\n",i,v);
			}
			if(temp->type==0)
			{
				fprintf(p,"%d -> %d [color=black];\n",i,v);
			}
			temp=temp->next;
		}
	}
	fprintf(p,"}\n");
	fclose(p);
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
	print();
}