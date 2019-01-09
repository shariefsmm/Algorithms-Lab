#include<stdio.h>
#include<stdlib.h>

struct Edges
{
	int u,v;
	int weight;
};
struct Edges *edges=NULL;

struct Graph
{
	int V,E;	//V=no:of vertices,E=n:of edges
	int S;		//source
	int *distances;	//shortest distance from source
};
struct Graph *g=NULL;

struct Vertices
{
	int distances;
	int prev;
};
struct Vertices *v=NULL;

void take_input()
{
	int n,m,i,U,V,weight;
	scanf(" %d",&n);
	scanf(" %d",&m);
	g=(struct Graph *)(malloc(1*sizeof(struct Graph)));
	g->V=n;
	g->E=m;
	edges=(struct Edges *)(malloc(m*sizeof(struct Edges)));
	v=(struct Vertices *)(malloc(n*sizeof(struct Vertices)));
	for(i=0;i<m;i++)
	{
		scanf(" %d",&U);
		scanf(" %d",&V);
		scanf(" %d",&weight);
		edges[i].u=U;
		edges[i].v=V;
		edges[i].weight=weight;
	}
	for(i=0;i<n;i++)
	{
		v[i].distances=1000000;
		v[i].prev=-1;
	}
	scanf(" %d",&i);
	g->S=i;
}
void print_distances()
{
	int i;
	printf("Vertex  Parent  Shortest distance\n");
	for(i=0;i<g->V;i++)
	{
		if(v[i].prev!=-1)
		{
			printf("%d \t %d \t %d\n",i,v[i].prev,v[i].distances);
		}
		else
		{
			if(i!=g->S)printf("%d is NOT REACHABLE form %d\n",i,g->S);
		}
	}
}
void print_cycle(int k)
{
	printf("The vertices in -ve cycle are\n");
	int visited[g->V],i,child,parent,path[g->V],len=0;;
	for(i=0;i<g->V;i++)
	{
		visited[i]=-1;
	}
	visited[k]=1;
	child=k;
	parent=v[k].prev;
	path[len]=k;
	len=len+1;
	while(visited[parent]!=1)
	{
		visited[parent]=1;
		path[len]=parent;
		len=len+1;
		child=parent;
		parent=v[child].prev;
	}
	len=len-1;
	for(i=0;i<=len;i++)
	{
		printf("%d ",path[len-i]);
	}
	printf("\n");
}
void bellmann_ford()
{
	int i,j,flag,edge_weight,U,V;
	v[g->S].distances=0;
	for(i=0;i<((g->V)-1);i++)
	{
		flag=0;
		for(j=0;j<((g->E));j++)
		{
			U=edges[j].u;
			V=edges[j].v;
			edge_weight=edges[j].weight;
			if(v[U].distances!=1000000)
			{
				if(v[V].distances>edge_weight+v[U].distances)
				{
					v[V].distances=edge_weight+v[U].distances;
					v[V].prev=U;
					flag=1;
				}
			}

		}
		if(flag==0)
		{
			print_distances();
			return;
		}

	}
	for(j=0;j<((g->E));j++)
	{
		U=edges[j].u;
		V=edges[j].v;
		edge_weight=edges[j].weight;
		if(v[U].distances!=1000000)
		{
			if(v[V].distances>edge_weight+v[U].distances)
			{
				v[edges[j].v].distances=edge_weight+v[U].distances;
				print_cycle(V);
				return;
			}
		}
	}
	print_distances();
	return;
}

int main()
{
	take_input();
	bellmann_ford();
}
