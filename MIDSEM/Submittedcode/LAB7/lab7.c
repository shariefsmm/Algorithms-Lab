#include<stdio.h>
#include<stdlib.h>

struct Edges
{
	int u,v;
	int weight;
};
struct Edges *edges;

struct Graph
{
	int V,E;	//V=no:of vertices,E=n:of edges
};
struct Graph *graph;

struct Node
{
	int parent;
	int rank;
};
struct Node *node;

void create_graph(int vertices,int edge)
{
	graph=(struct Graph *)(malloc(1*sizeof(struct Graph)));
	graph->V=vertices;
	graph->E=edge;
}

void update_edges(int edge)
{
	int u,v,weight;
	edges=(struct Edges *)(malloc(edge*sizeof(struct Edges)));
	for(int i=0;i<edge;i++)
	{
		scanf(" %d %d %d",&u,&v,&weight);
		edges[i].u=u;
		edges[i].v=v;
		edges[i].weight=weight;
	}
}

void merge(int start,int middle,int end)
{
	int i,j,l,r,k;
	l=middle-start+1;
	r=end-middle;
	struct Edges L[l+1],R[r+1];
	for(i=0;i<l;i++)
	{
		L[i]=edges[start+i];
	}
	L[l].weight=1000000;
	for(i=0;i<r;i++)
	{
		R[i]=edges[middle+1+i];
	}
	R[r].weight=1000000;
	i=0,j=0;
	for(k=start;k<=end;k++)
	{
		if( (L[i].weight)<=(R[j].weight) )
		{
			edges[k]=L[i];
			i++;
		}
		else
		{
			edges[k]=R[j];
			j++;
		}
	}
}

void mergesort(int start,int end)
{
	if(start>=end)return;
	int middle;
	middle=(start+end)/2;
	mergesort(start,middle);
	mergesort(middle+1,end);
	merge(start,middle,end);
}

void print_edges()
{
	struct Edges *temp;
	temp=edges;
	for(int i=0;i<graph->E;i++)
	{
		printf("source %d dest %d weight %d\n",temp[i].u,temp[i].v,temp[i].weight);
	}

}

void makeset()
{
	int vertices=graph->V;
	node=(struct Node *)(malloc(vertices*sizeof(struct Node)));
	for(int i=0;i<vertices;i++)
	{
		node[i].parent=i;
		node[i].rank=0;
	}
}


int find(int u)
{
	if(node[u].parent!=u)
	{
		node[u].parent=find(node[u].parent);
	}
	return node[u].parent;
}

int unions(int u,int v)
{
	int x,y;
  	x=find(u);
	y=find(v);
	if(x!=y)
	{
		if(node[x].rank==node[y].rank)
		{
			node[y].parent=x;
			node[x].rank=node[x].rank+1;
		}
		else if(node[x].rank>node[y].rank)
		{
			node[y].parent=x;
		}
		else 
		{
			node[x].parent=y;
		}
		return 1;
	}
	else return 0;
}

void print(struct Edges *S)
{
	int total=0;
	printf("Edges in minimum spanning tree are:\n");
	for(int i=0;i<(graph->V-1);i++)
	{
		printf("%d -- %d \t %d\n",S[i].u,S[i].v,S[i].weight);
		total=total+S[i].weight;
	}
	printf("Total edge weight of MST is %d\n",total);

}

int main()
{
	int vertices,edge,i,u,v,e,add;
	scanf(" %d %d",&vertices,&edge);
	create_graph(vertices,edge);
	update_edges(edge);
	mergesort(0,edge-1);
	makeset();
	struct Edges S[vertices];
	i=0;
	e=0;
	while(e<(vertices-1))
	{
		u=edges[i].u;
		v=edges[i].v;
		add=unions(u,v);
		if(add==1)
		{
			S[e]=edges[i];
			e++;
		}
		i++;
	}
	print(S);
}
