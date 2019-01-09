#include<stdio.h>
#include<stdlib.h>

struct Graph
{
	int source;
	int n; // total vertices  
	int m; //total edges,heaps 
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
	int rank;
};
struct Vertices *v=NULL;

struct Min_heap
{
	int u;
	int v;
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
	for(i=0;i<n;i++)
	{
		v[i].distance=100000;
		v[i].heapposition=i;
		v[i].prev=-1;
		v[i].visited=-1;
		v[i].rank=0;
		v[i].adj=NULL;
	}
	scanf(" %d",&temp);//temp=no:of edges
	g->m=temp;
	h=(struct Min_heap *)(malloc(temp*(sizeof(struct Min_heap))));
	int k=0;
	while(temp>0)
	{
		temp=temp-1;
		scanf(" %d %d %d",&i,&j,&w);
		enqueue(&(v[i].adj),j,w);
		enqueue(&(v[j].adj),i,w);
		h[k].u=i;
		h[k].v=j;
		h[k].key=w;
		k=k+1;
	}
	g->source=0;
}

void heapify(int index)
{
	int shortlen,left_index,right_index;
	shortlen=index;
	left_index=2*index+1;
	right_index=2*index+2;
	if(left_index<g->m && h[shortlen].key>h[left_index].key)
	{
		shortlen=left_index;
	}
	if(right_index<g->m && h[shortlen].key>h[right_index].key)
	{
		shortlen=right_index;
	}
	if(shortlen!=index)
	{
		struct Min_heap *temp=(struct Min_heap *)(malloc(1*sizeof(struct Min_heap)));
		temp[0]=h[shortlen];
		h[shortlen]=h[index];
		h[index]=temp[0];
		// v[h[shortlen].vertex].heapposition=shortlen;
		// v[h[index].vertex].heapposition=index;
		heapify(shortlen);

	}
}


void build_heap()
{
	int i;
	for(i=((g->m-2)/2);i>=0;i--)
	{
		heapify(i);
	}
}

int del_min()
{
	if(g->m==0)return -1;
	int current;
	current=h[0].v;
	struct Min_heap *temp=(struct Min_heap *)(malloc(1*sizeof(struct Min_heap)));
	temp[0]=h[0];
	h[0]=h[g->m-1];
	h[g->m-1]=temp[0];
	// v[h[0].vertex].heapposition=0;
	// v[h[g->m-1].vertex].heapposition=g->m-1;
	g->m=g->m-1;
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
			// v[h[child_index].vertex].heapposition=child_index;
			// v[h[parent_index].vertex].heapposition=parent_index;
			child_index=parent_index;
			parent_index=(child_index-1)/2;
		}
		else
		{
			break;
		}
	}
}

void heap_sort()
{
	int temp_m,i=0,flag;
	temp_m=g->m;
	while(i<temp_m)
	{
		flag=del_min();
		i++;
	}
	g->m=temp_m;
}

void sort()
{
	build_heap();
	heap_sort();
}

void makeset()
{
	int i;
	for(i=0;i<g->n;i++)
	{
		v[i].prev=i;
		v[i].rank=0;
	}
}

int find(int u)
{
	if(v[u].prev!=u)
	{
		v[u].prev=find(v[u].prev);
	}
	return v[u].prev;
}

int unions(int U,int V)
{
	int x,y;
  	x=find(U);
	y=find(V);
	if(x!=y)
	{
		if(v[x].rank==v[y].rank)
		{
			v[y].prev=x;
			v[x].rank=v[x].rank+1;
		}
		else if(v[x].rank>v[y].rank)
		{
			v[y].prev=x;
		}
		else 
		{
			v[x].prev=y;
		}
		return 1;
	}
	else return 0;
}
void print(struct Min_heap *S)
{
	int total=0;
	printf("Edges in minimum spanning tree are:\n");
	for(int i=0;i<(g->n-1);i++)
	{
		printf("%d -- %d \t %d\n",S[i].u,S[i].v,S[i].key);
		total=total+S[i].key;
	}
	printf("Total edge weight of MST is %d\n",total);

}

// void printh()
// {
// 	for(int i=0;i<g->m;i++)
// 	{
// 		printf("%d--%d  %d  ",h[i].u,h[i].v,h[i].key);
// 	}
// 	printf("\n");
// }

int main()
{
	take_input();
	sort();
	struct Min_heap S[g->n];
	makeset();
	int i,e,add=0,u,v;
	i=0;
	e=0;
	while(e<(g->n-1))
	{
		u=h[g->m-1-i].u;
		v=h[g->m-1-i].v;
		add=unions(u,v);
		if(add==1)
		{
			S[e]=h[g->m-1-i];
			e=e+1;
		}
		i=i+1;
	}
	//printh();
	print(S);
	return 0;
}


