#include<stdio.h>
#include<stdlib.h>

struct Adj
{
  int vertex;
  int weight;
  struct Adj *next;
};

struct Vertex
{
  struct Adj *adj;
  int heap_position;
  int distance;
  int prev;
  int visited;
};
struct Vertex **vertex;

struct Graph
{
  int source;
  int total_vertices;
};
struct Graph *graph;

struct Min_heap
{
  int vertex;
  int key;
};
struct Min_heap **min_heap;

void list(struct Adj **head,int x,int w)
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

void create_graph()
{
  int vertices,i;
  scanf(" %d",&vertices);
  graph=(struct Graph *)(malloc(1*sizeof(struct Graph)));
  graph->total_vertices=vertices;
  vertex=(struct Vertex **)(malloc(vertices*sizeof(struct Vertex *)));
  min_heap=(struct Min_heap **)(malloc(vertices*sizeof(struct Min_heap *)));
  for(i=0;i<vertices;i++)
  {
    struct Vertex *temp=(struct Vertex *)(malloc(1*sizeof(struct Vertex)));
    temp->heap_position=i;
    temp->distance=100000;
    temp->prev=-1;
    temp->visited=-1;
    vertex[i]=temp;

    struct Min_heap *temp1=(struct Min_heap *)(malloc(1*sizeof(struct Min_heap)));
    temp1->vertex=i;
    temp1->key=100000;
    min_heap[i]=temp1;
  }
}

void updateedges()
{
  int edges,i,j,w;
  scanf(" %d",&edges);
  while(edges>0)
  {
    edges=edges-1;
    scanf(" %d %d %d",&i,&j,&w);
    list(&(vertex[i]->adj),j,w);
    list(&(vertex[j]->adj),i,w);
  }
}

void heapify(int index)
{
  int left_index,right_index,li_distance,ri_distance;
  left_index=2*index+1;
  right_index=2*index+2;
  int shortin;
  shortin=index;
  if(left_index<graph->total_vertices)
  {
    li_distance=min_heap[left_index]->key;
    if(li_distance<min_heap[shortin]->key)
    {
      shortin=left_index;
    }
  }
  if(right_index<graph->total_vertices)
  {
    ri_distance=min_heap[right_index]->key;
    if(ri_distance<min_heap[shortin]->key)
    {
      shortin=right_index;
    }
  }
  if(shortin!=index)
  {
    int shortin_vertex,in_vertex;
    shortin_vertex=min_heap[shortin]->vertex;
    in_vertex=min_heap[index]->vertex;

    vertex[shortin_vertex]->heap_position=index;
    vertex[in_vertex]->heap_position=shortin;
    int temp_key;
    temp_key=min_heap[index]->key;
    min_heap[index]->vertex=shortin_vertex;
    min_heap[index]->key=min_heap[shortin]->key;
    min_heap[shortin]->vertex=in_vertex;
    min_heap[shortin]->key=temp_key;
    heapify(shortin);
  }

}

void build_heap()
{
  int i;
  for(i=(graph->total_vertices-2)/2;i>=0;i--)
  {
    heapify(i);
  }
}

int del_min()
{
  int t_vertex;
  t_vertex=graph->total_vertices;
  if(t_vertex==0)return -1;

  t_vertex=t_vertex-1;
  int current,temp_d,last_v;
  current=min_heap[0]->vertex;
  last_v=min_heap[t_vertex]->vertex;

  min_heap[0]->vertex=last_v;
  min_heap[t_vertex]->vertex=current;

  temp_d=min_heap[0]->key;
  min_heap[0]->key=min_heap[t_vertex]->key;
  min_heap[t_vertex]->key=temp_d;

  vertex[current]->heap_position=t_vertex;
  vertex[last_v]->heap_position=0;
  graph->total_vertices=graph->total_vertices-1;
  heapify(0);
  return current;
}

void decrease_key(int child_index,int key)
{
  min_heap[child_index]->key=key;
  if(child_index<=0)return;
  int parent_index,child_distance,parent_distance;
  int parent_vertix,child_vertix,temp_vertex,temp_distance;
  parent_index=(child_index-1)/2;
  parent_distance=min_heap[parent_index]->key;
  child_distance=key;
  while(child_index>0)
  {
    if(parent_distance>child_distance)
    {
      parent_vertix=min_heap[parent_index]->vertex;
      child_vertix=min_heap[child_index]->vertex;

      vertex[parent_vertix]->heap_position=child_index;
      vertex[child_vertix]->heap_position=parent_index;

      min_heap[parent_index]->vertex=child_vertix;
      min_heap[child_index]->vertex=parent_vertix;

      temp_distance=min_heap[parent_index]->key;
      min_heap[parent_index]->key=min_heap[child_index]->key;
      min_heap[child_index]->key=temp_distance;

      child_index=parent_index;
      parent_index=(child_index-1)/2;

      child_distance=min_heap[child_index]->key;
      parent_distance=min_heap[parent_index]->key;
    }
    else
    {
      break;
    }
  }
}

void dijkstras()
{
  int temp_n,current,edgenode,weight,currentnode_distance,temp_distance;
  struct Adj *temp;
  temp_n=graph->total_vertices;
  vertex[graph->source]->distance=0;
  min_heap[graph->source]->key=0;
  build_heap();
  while(1)
  {
    current=del_min();
    if(current==-1)break;
    if(vertex[current]->visited==1)continue;
    temp=vertex[current]->adj;
    while(temp!=NULL)
    {
        edgenode=temp->vertex;
        weight=temp->weight;
        currentnode_distance=vertex[current]->distance;
        temp_distance=currentnode_distance+weight;
        if(vertex[edgenode]->distance>(temp_distance) && vertex[edgenode]->visited!=1)
        {
          vertex[edgenode]->distance=temp_distance;
          vertex[edgenode]->prev=current;
          decrease_key(vertex[edgenode]->heap_position,temp_distance);
        }
        temp=temp->next;
    }
    vertex[current]->visited=1;
  }
  graph->total_vertices=temp_n;
}

void print()
{
  int temp;
  temp=graph->total_vertices;
  printf("Vertex \t Shortest Distance\n");
  graph->total_vertices=graph->total_vertices-1;
  while(graph->total_vertices>=0)
  {
    printf("%d \t %d\n",graph->total_vertices,vertex[graph->total_vertices]->distance);
    graph->total_vertices=graph->total_vertices-1;
  }
  graph->total_vertices=temp;
}

int main()
{
  create_graph();
  updateedges();
  scanf(" %d",&(graph->source));
  dijkstras();
  print();
}
