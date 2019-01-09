#include<stdio.h>
#include<stdlib.h>

struct node
{
  int data;
};
struct node **head;

void fun()
{
  head=(struct node **)(malloc(5*sizeof(struct node *)));
  for(int i=0;i<=4;i++)
  {
    struct node *temp=(struct node *)(malloc(1*sizeof(struct node)));
    temp->data=i;
    head[i]=temp;
  }
}

// void print_vertex()
// {
//   printf("edges:\n");
//   for(int i=0;i<graph->total_vertices;i++)
//   {
//     printf("%d vertex\n",i);
//     while(vertex[i]->adj!=NULL)
//     {
//       printf("%d ",vertex[i]->adj->vertex);
//       vertex[i]->adj=vertex[i]->adj->next;
//     }
//     printf("\n");
//     printf("heap_position is %d\n",vertex[i]->heap_position);
//     printf("distance is %d\n",vertex[i]->distance);
//   }
// }

void fun1()
{
  head[3]->data=30;
}

int main()
{
  struct node *temp;
//  temp=(struct node *)(malloc(1))
  fun();
  for(int i=0;i<=4;i++)
  {
    printf("data is %d\n",head[i]->data);
    head[i]->data=100;
  }
  for(int i=0;i<=4;i++)
  {
    printf("data is %d\n",head[i]->data);
    //head[i]->data=100;
  }
  fun1();
  for(int i=0;i<=4;i++)
  {
    printf("data is %d\n",head[i]->data);
    head[i]->data=100;
  }

}
