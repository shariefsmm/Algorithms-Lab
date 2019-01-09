#include<stdio.h>
int a[150],n,heapsize;
void print_heap(int root,int space)
{
		if(root>=n)return;
		space+=10;
		print_heap(2*root+2,space);
		printf("\n");
		for(int i=10;i<space;i++)
		{
			printf(" ");
		}
		printf("%d\n",a[root]);
		print_heap(2*root+1,space);
}

void heapify(int index)
{
	int shortlen,left,right,temp;
	shortlen=index;
	left=2*index+1;
	right=2*index+2;
	if(left<n && a[left]<a[shortlen])
	{
		shortlen=left;
	}
	if(right<n && a[right]<a[shortlen])
	{
		shortlen=right;
	}
	if(shortlen!=index)
	{
		temp=a[index];
		a[index]=a[shortlen];
		a[shortlen]=temp;
		heapify(shortlen);
	}
}

void build_heap()
{
	int i;
	printf("Enter no:of elements: ");
	scanf(" %d",&n);
	for(i=0;i<n;i++)
	{
		a[i]=-1;
	}
	printf("Enter elements: ");
	for(i=0;i<n;i++)
	{
		scanf(" %d",&a[i]);
	}
	for(i=n-1;i>=0;i--)
	{
		heapify(i);
	}
}

void insert()
{
	int data,i,parent,child,temp;
	printf("Enter data to insert: ");
	scanf(" %d",&data);
	n=n+1;
	a[n-1]=data;
	child=n-1;
	parent=(child-1)/2;
	while(child>0)
	{
		if(a[parent]>a[child])
		{
			temp=a[parent];
			a[parent]=a[child];
			a[child]=temp;
			child=parent;
			parent=(child-1)/2;
		}
		else break;
	}
}

void del_min()
{
	if(n==0)
	{
		printf("\tNothing there to delete\n");
		return;
	}
	int temp;
	temp=a[0];
	a[0]=a[n-1];
	a[n-1]=temp;
	n=n-1;
	heapify(0);
	printf("Minimum element %d is deleted\n",temp);
}

void heapsort()
{
	if(n==0)
	{
		printf("\tNothing there to sort\n");
		return;
	}
	int temp,temp_n,i=0;
	temp_n=n;
	while(i<temp_n)
	{
		temp=a[0];
		a[0]=a[n-1];
		a[n-1]=temp;
		n=n-1;
		heapify(0);
		i++;
	}
	n=temp_n;
	printf("\tSorted list is:\n");
	for(i=n-1;i>=0;i--)
	{
		printf("%d ",a[i]);
	}
	printf("\n");
	printf("\tHeap is as follows:\n");
	print_heap(0,0);
}

int main()
{
	int flag,option,flag1=0;
	flag=1;
  	while(flag==1)
  	{
  		printf("MENU:\n");
  		printf("\t1.)BUILD A HEAP\n");
  		printf("\t2.)INSERT AN ELEMENT\n");
  		printf("\t3.)DELETE MINIMUM ELEMENT\n");
  		printf("\t4.)HEAPSORT\n");
		printf("\t5.)Display Heap\n");
  		printf("\t6.)EXIT\n");
  		printf("Enter your choice: ");
  		scanf(" %d",&option);
		switch(option)
		{
			case 1:
				build_heap();
				flag1=1;
				break;
			case 2:
				if(flag1==1)insert();
				else 
				{
					n=0;
					insert();
					flag1=1;
				}
				break;
			case 3:
				if(flag1==1)del_min();
				else printf("\tFirst build a heap\n");
				break;
			case 4:
				if(flag1==1)
				{
					heapsort();
					flag1=0;
				}
				else printf("\tFirst build a heap\n");
				break;
			case 5:
				if(flag1==1)print_heap(0,0);
				else printf("\tNo heap to display\n");
				break;
			case 6:
				flag=0;
				break;
			default:
				printf("\tEnter valid option\n");
		}
	}
}
