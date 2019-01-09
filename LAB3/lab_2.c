/*
Program Name:lab_2.c
Program Description:merge sort of binaryfile.
Programmer's Name:SHARIEF SMM
Roll no:111601022
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int sort;
char s[20],h[20];


void write_f()	/* Function for writing output */
{
	char swap[20];
	FILE *popen,*pclose;
	int t;
	if(strcmp(s,"output.txt")==0)	/* Checks if bin is in input file or output file */
	{
		popen=fopen(s,"rb");
		pclose=fopen(h,"wb");
		while(fread(&t,sizeof(t),1,popen)==1)
		{
			fwrite(&t,sizeof(int),1,pclose);
		}
		fclose(popen);
		fclose(pclose);
		strcpy(swap,s);	/* swap files for pointers */
	 	strcpy(s,h);
		strcpy(h,swap);
	}
	popen=fopen(s,"rb");
	pclose=fopen("output.txt","w");
	while(fread(&t,sizeof(int),1,popen)==1)
	{
		fprintf(pclose,"%d\n",t);
	}
	fclose(popen);
	fclose(pclose);
}

void merge()
{
	int po1,po2,c1,c2,flag,flag1,t,t1,i=0,temp,f1=1;
	FILE *popen,*popen1,*pclose;
	char swap[20];
	while(1)	 /* this line is executed log(n)[base=2] times*/
	{
		c1=1;	/* Condition for fread of p */
		c2=1;	/* Condition for fread of p1 */
		temp=0;
		flag=0;
		flag1=0;
		po1=0;	/* po1 corresponds to position of pointer popen */
		po2=0;	/* po2 corresponds to position of pointer popen1 */
		popen=fopen(s,"rb");
		popen1=fopen(s,"rb");
		fseek(popen1,sort*sizeof(int),SEEK_SET);
		if(fread(&t1,sizeof(int),1,popen1)!=1)	/* Checks if end of file is reached */
		{
			fclose(popen);
			write_f();			/* Function call for writing output */
			break;
		}
		pclose=fopen(h,"wb");
		while(1)	/* Each time this line is executed n times */
		{
			if(po1>=sort && c1==1)	/* pointer p moved sort positions and all values are written in p2 */
			{
				fwrite(&t1,sizeof(t),1,pclose);
				while(po2<sort)
				{
					if(fread(&t1,sizeof(t),1,popen1)!=1)
					{
						break;
					}
					fwrite(&t1,sizeof(t),1,pclose);
					po2=po2+1;
				}
				fseek(popen,sort*sizeof(int),SEEK_CUR);
				fseek(popen1,sort*sizeof(int),SEEK_CUR);
				po1=0;
				po2=0;
				c1=c2=1;
			}
			else if(po2>=sort && c2==1)	/* pointer p1 moved sort positions and all values are written in p2 */
			{
				fwrite(&t,sizeof(t),1,pclose);
				while(po1<sort)
				{
					if(fread(&t,sizeof(t),1,popen)!=1)
					{
						break;
					}
					fwrite(&t,sizeof(t),1,pclose);
					po1=po1+1;
				}
				fseek(popen,sort*sizeof(int),SEEK_CUR);
				fseek(popen1,sort*sizeof(int),SEEK_CUR);
				po1=0;
				po2=0;
				c1=c2=1;
			}
			if(c1==1 && po1<sort)	/* Condtion for p to read */
			{
				if(fread(&t,sizeof(int),1,popen)!=1)
				{
					break;
				}
				po1=po1+1;
			}
			if(c2==1 && po2<sort && temp!=0)	/*Condition for p1 to read */
			{
				if(fread(&t1,sizeof(int),1,popen1)!=1)
				{
					flag1=1;
					break;
				}
				po2=po2+1;
			}
			if(temp==0)
			{
				po2=1;
			}
			temp=1;
			if(t<t1)
			{
				fwrite(&t,sizeof(t),1,pclose);
				c1=1;
				c2=0;
			}
			else
			{
				fwrite(&t1,sizeof(t),1,pclose);
				c2=1;
				c1=0;
			}
		}
		if(flag1==1)	/* p1 reached eof so write all p values */
		{
			fwrite(&t,sizeof(t),1,pclose);
			while(fread(&t,sizeof(t),1,popen)==1 && po1<sort)
			{
				fwrite(&t,sizeof(t),1,pclose);
				po1=po1+1;
			}
			flag=0;
			flag1=0;
		}
		sort=sort*2;	/* represents sorted no:of elements and ensures for nlogn times */
		strcpy(swap,s);	/* swap files for pointers */
	 	strcpy(s,h);
		strcpy(h,swap);
		fclose(popen);
		fclose(popen1);
		fclose(pclose);
	}

}

int main()
{
	scanf(" %s",s);
	strcpy(h, "output.txt");
	sort=1;
	merge();
	printf("output.txt is created\n");
}
