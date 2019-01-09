#include<stdio.h>
#include<stdlib.h>

struct Graph
{
	int source;
	int n;
};
struct Graph *g=NULL;

struct Adj
{
	int vertex;
	int weight;
	struct Adj *next;
};

struct Vertices
{
	struct Adj *adj;
	int distance;
	int heapposition;
	int prev;
	int visited;
};
struct Vertices *v=NULL;

struct Min_heap
{
	int vertex;
	int key;
};
struct Min_heap *h=NULL;

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
	int n,temp,i,j,w;
	scanf(" %d",&n);//n=no:of vertices
	g=(struct Graph *)(malloc(1*(sizeof(struct Graph))));
	g->n=n;
	v=(struct Vertices *)(malloc(n*(sizeof(struct Vertices))));
	h=(struct Min_heap *)(malloc(n*(sizeof(struct Min_heap))));
	for(i=0;i<n;i++)
	{
		v[i].distance=100000;
		v[i].heapposition=i;
		v[i].prev=-1;
		v[i].visited=-1;
		v[i].adj=NULL;

		h[i].vertex=i;
		h[i].key=100000;
	}
	scanf(" %d",&temp);//temp=no:of edges
	while(temp>0)
	{
		temp=temp-1;
		scanf(" %d %d %d",&i,&j,&w);
		enqueue(&(v[i].adj),j,w);
		enqueue(&(v[j].adj),i,w);
	}
	scanf(" %d",&i);
	g->source=i;
}

void heapify(int index)
{
	int shortlen,left_index,right_index;
	shortlen=index;
	left_index=2*index+1;
	right_index=2*index+2;
	if(left_index<g->n && h[shortlen].key>h[left_index].key)
	{
		shortlen=left_index;
	}
	if(right_index<g->n && h[shortlen].key>h[right_index].key)
	{
		shortlen=right_index;
	}
	if(shortlen!=index)
	{
		struct Min_heap *temp=(struct Min_heap *)(malloc(1*sizeof(struct Min_heap)));
		temp[0]=h[shortlen];
		h[shortlen]=h[index];
		h[index]=temp[0];
		v[h[shortlen].vertex].heapposition=shortlen;
		v[h[index].vertex].heapposition=index;
		heapify(shortlen);

	}
}


void build_heap()
{
	int i;
	for(i=((g->n-2)/2);i>=0;i--)
	{
		heapify(i);
	}
}

int del_min()
{
	if(g->n==0)return -1;
	int current;
	current=h[0].vertex;
	struct Min_heap *temp=(struct Min_heap *)(malloc(1*sizeof(struct Min_heap)));
	temp[0]=h[0];
	h[0]=h[g->n-1];
	h[g->n-1]=temp[0];
	v[h[0].vertex].heapposition=0;
	v[h[g->n-1].vertex].heapposition=g->n-1;
	g->n=g->n-1;
	heapify(0);
	return current;

}

void decrease_key(int index,int key)
{
	int child_index,parent_index;
	child_index=index;
	h[child_index].key=key;
	parent_index=(child_index-1)/2;
	while(child_index>0)
	{
		if(h[child_index].key<h[parent_index].key)
		{
			struct Min_heap *temp=(struct Min_heap *)(malloc(1*sizeof(struct Min_heap)));
			temp[0]=h[child_index];
			h[child_index]=h[parent_index];
			h[parent_index]=temp[0];
			v[h[child_index].vertex].heapposition=child_index;
			v[h[parent_index].vertex].heapposition=parent_index;
			child_index=parent_index;
			parent_index=(child_index-1)/2;
		}
		else
		{
			break;
		}
	}
}

void dijkstras()
{
	v[g->source].distance=0;
	h[g->source].key=0;
	build_heap();
	int temp_n,current,edge_node,weight;
	temp_n=g->n;
	struct Adj *temp;
	while(1)
	{
		current=del_min();
		if(current==-1)break;
		if(v[current].visited==1)continue;
		temp=v[current].adj;
		while(temp!=NULL)
		{
			edge_node=temp->vertex;
			weight=temp->weight+v[current].distance;
			if(v[edge_node].distance>weight && (v[edge_node].visited!=1))
			{
				v[edge_node].distance=weight;
				v[edge_node].prev=current;
				decrease_key(v[edge_node].heapposition,weight);
			}
			temp=temp->next;
		}
		v[current].visited=1;

	}
	g->n=temp_n;
}

void print()
{
	printf("Vertex\tparent\tShortest Distance\n");
	int temp_n,total=0;
	temp_n=g->n;
	g->n=g->n-1;
	while(g->n>=0)
	{
		if(v[g->n].prev!=-1)
		{
			printf("%d\t%d \t %d\n",g->n,v[g->n].prev,v[g->n].distance);
			total=total+v[g->n].distance;
		}
		g->n=g->n-1;
	}
	//printf("Total weigth is %d\n",total);
	g->n=temp_n;
	
}


int main()
{
	take_input();
	dijkstras();
	print();
	return 0;
}


