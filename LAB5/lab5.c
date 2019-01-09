#include<stdio.h>
#include<stdlib.h>

struct node
{
  int vertix;
  int weight;
  struct node *next;
};
typedef struct node node;

struct Graph
{
  int source;
  struct node **adj;
  int vertices;
  int *distance;
  int *visited;
  int *prev;
  int *heap_position;
  int *vertix_position;
};
typedef struct Graph Graph;

void list(struct node **head,int x,int w)
{
	struct node *temp1;
	struct node *temp=(struct node*)(malloc(1*sizeof(struct node)));
	temp->vertix=x;
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

void create_graph(Graph **g,int vertices)
{
  int i;
  struct Graph *temp=(Graph *)(malloc(1*sizeof(Graph)));
  *g=temp;
  (*g)->vertices=vertices;
  (*g)->adj=(struct node**)(malloc(vertices*sizeof(struct node*)));
  (*g)->distance=(int *)(malloc(vertices*sizeof(int)));
  (*g)->visited=(int *)(malloc(vertices*sizeof(int)));
  (*g)->prev=(int *)(malloc(vertices*sizeof(int)));
  (*g)->heap_position=(int *)(malloc(vertices*sizeof(int)));
  (*g)->vertix_position=(int *)(malloc(vertices*sizeof(int)));
  (*g)->source=-1;
  for(i=0;i<vertices;i++)
  {
    (*g)->adj[i]=NULL;
    (*g)->distance[i]=100000;
    (*g)->visited[i]=-1;
    (*g)->prev[i]=-1;
    (*g)->heap_position[i]=i;
    (*g)->vertix_position[i]=i;
  }

}

void updateedges(Graph *g)
{
  int edges,i,j,w;
  scanf(" %d",&edges);
  while(edges>0)
  {
    edges=edges-1;
    scanf(" %d %d %d",&i,&j,&w);
    list(&(g->adj[i]),j,w);
    list(&(g->adj[j]),i,w);
  }
}

void heapify(Graph *g,int index)
{
  int shortlen_vertix,left_vertix,right_verix,child_index,temp;
  child_index=index;
  shortlen_vertix=g->heap_position[index];
  left_vertix=g->heap_position[2*index+1];
  right_verix=g->heap_position[2*index+2];
  if( (2*index+1)<(g->vertices) && (g->distance[left_vertix])<(g->distance[shortlen_vertix]) )
  {
    shortlen_vertix=left_vertix;
    child_index=2*index+1;
  }
  if( (2*index+2)<(g->vertices) && (g->distance[right_verix])<(g->distance[shortlen_vertix]) )
  {
    shortlen_vertix=right_verix;
    child_index=2*index+2;
  }
  if(child_index!=index)
  {
    g->vertix_position[g->heap_position[index]]=child_index;
    g->vertix_position[g->heap_position[child_index]]=index;
    temp=g->heap_position[index];
    g->heap_position[index]=g->heap_position[child_index];
    g->heap_position[child_index]=temp;
    heapify(g,child_index);
  }
}

void build_heap(Graph *g)
{
  int i;
  for(i=(g->vertices-1);i>=0;i--)
  {
    heapify(g,i);
  }
}

int del_min(Graph *g)
{
  if(g->vertices==0)return -1;
  int current,temp;
  g->vertix_position[g->heap_position[0]]=g->vertices-1;
  g->vertix_position[g->heap_position[g->vertices-1]]=0;
  current=g->heap_position[0];
  temp=g->heap_position[0];
  g->heap_position[0]=g->heap_position[g->vertices-1];
  g->heap_position[g->vertices-1]=temp;
  g->vertices=g->vertices-1;
  heapify(g,0);
  return current;
}

void decrease_key(Graph *g,int child_index,int child_vertix)
{
  int parent_index,parent_vertix,temp;
  parent_index=(child_index-1)/2;
  parent_vertix=g->heap_position[parent_index];
  while(child_index>0)
  {
      if( g->distance[child_vertix]<g->distance[parent_vertix])
      {
        g->vertix_position[parent_vertix]=child_index;
        g->vertix_position[child_vertix]=parent_index;
        g->heap_position[parent_index]=child_vertix;
        g->heap_position[child_index]=parent_vertix;
        child_index=parent_index;
        parent_index=(child_index-1)/2;
        parent_vertix=g->heap_position[parent_index];
        child_vertix=g->heap_position[child_index];
      }
      else
      {
        break;
      }
  }
}

void print(Graph *g)
{
  printf("Vertex \t Shortest Distance\n");
  g->vertices=g->vertices-1;
  while(g->vertices>=0)
  {
    printf("%d \t %d\n",g->vertices,g->distance[g->vertices]);
    g->vertices=g->vertices-1;
  }
}

void dijkstras(Graph *g)
{
  int temp_n,i,edgenode,currentnode_distance,current,weight;
  temp_n=g->vertices;
  g->distance[g->source]=0;
  build_heap(g);
  while(1)
  {
    current=del_min(g);
    if(current==-1)break;
    if(g->visited[current]==1)continue;
    while(g->adj[current]!=NULL)
    {
      edgenode=g->adj[current]->vertix;
      weight=g->adj[current]->weight;
      currentnode_distance=g->distance[current];
      if(g->visited[edgenode]!=1)
      {
        if(g->distance[edgenode]>(currentnode_distance+weight))
        {
          g->distance[edgenode]=(currentnode_distance+weight);
          g->prev[edgenode]=current;
          decrease_key(g,g->vertix_position[edgenode],edgenode);                                                                               //stoped here
        }
      }
      g->adj[current]=g->adj[current]->next;
    }
    g->visited[current]=1;
  }
  g->vertices=temp_n;
  print(g);
}

int main()
{
  int i,j,vertices;
  Graph *g;
  scanf("%d",&vertices);
  create_graph(&g,vertices);
  updateedges(g);
  scanf(" %d",&(g->source));
  dijkstras(g);
}
