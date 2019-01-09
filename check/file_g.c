#include<stdio.h>
#include<stdlib.h>

int main()
{
	int x,y,i;
	FILE *p,*p1;
	x=2;
	p=fopen("verify.bin","wb");
	for(i=7;i>=1;i--)
	{
		x=rand();
		fwrite(&x,sizeof(int),1,p);
	}
	fclose(p);
	p=fopen("verify.bin","rb");
	p1=fopen("verify.txt","w");
	while(fread(&y,sizeof(int),1,p)==1)
	{
		fprintf(p1,"%d\n",y);
	}
	fclose(p);
	return 0;
}
