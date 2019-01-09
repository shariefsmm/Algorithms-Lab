
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

void boruvka()
{
  makeset();
  int cheapest[graph->V],i,num_tree,u,v,x,y,add,total=0;
  for(i=0;i<graph->V;i++)
  {
    cheapest[i]=-1;
  }
  num_tree=graph->V;
  printf("Edges in minimum spanning tree are:\n");
  while(num_tree>1)
  {
    for(i=0;i<graph->E;i++)
    {
      u=edges[i].u;
  		v=edges[i].v;
      x=find(u);
      y=find(v);
      if(x==y)
      {
        continue;
      }
      else
      {
        if(cheapest[x]==-1 || ( (edges[cheapest[x]].weight) > (edges[i].weight) ) )
        {
          cheapest[x]=i;
        }
        if(cheapest[y]==-1 || ( (edges[cheapest[y]].weight) > (edges[i].weight) ) )
        {
          cheapest[y]=i;
        }
      }
    }
    for(i=0;i<graph->V;i++)
    {
			//printf("cheapest[%d] is %d\n",i,cheapest[i]);
      if(cheapest[i]!=-1)
      {
        add=unions(edges[cheapest[i]].u,edges[cheapest[i]].v);
        if(add==1)
        {
          printf("%d -- %d \t %d\n",edges[cheapest[i]].u,edges[cheapest[i]].v,edges[cheapest[i]].weight);
      		total=total+edges[cheapest[i]].weight;
          num_tree=num_tree-1;
        }
      }
			cheapest[i]=-1;
    }
  }
  printf("Total edge weight of MST is %d\n",total);
}

int main()
{
	int vertices,edge;
	scanf(" %d %d",&vertices,&edge);
	create_graph(vertices,edge);
	update_edges(edge);
	boruvka();
	return 0;
}
