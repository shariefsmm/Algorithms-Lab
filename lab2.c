#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int main()
{
	FILE *p,*p1;
	int i,b,j,t=0;
	char c;
	p=fopen("random.txt","w");
	for(i=0;i<=100;i++)
	{
		fprintf(p,"%d",rand()%2);
	}
	fclose(p);
	p=fopen("random.txt","r");
	//fseek(p,2,SEEK_CUR);
	for(i=0;i<=100;i++)
	{
		j=3;
		t=0;
		while(j>=0)
		{
			fscanf(p," %c",&c);
			t=t+(c-'0')*pow(2,j);
			j=j-1;
		}
		printf("%d ",t);
	}
	printf("\n");
	fclose(p);
}

