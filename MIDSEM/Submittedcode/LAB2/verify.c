#include<stdio.h>
#include<stdlib.h>

int main()
{
	char c;
	FILE *p1;
	p1=fopen("output.txt","w");
	while(scanf(" %c",&c)==1)
	{
		fprintf(p1,"%c",c);
	}
}