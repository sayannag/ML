#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

int main()
{
	char ch;
	float sc;
	int len=0;
	int count=0;
	FILE *fp=fopen("DataSet1.txt", "r");
	FILE *fp1=fopen("dummyxxxxx.txt", "w");

	int cha=0;
	if (fp==NULL)
		printf("Error");
	
	while (fscanf(fp, "%c", &ch)!=EOF)
	{
		if (ch=='\n')
			count++;
	}
	
	rewind(fp);
//	printf("%d", ftell(fp));
		printf("count%d\n",count);
	while (fscanf(fp, "%c", &ch)!=EOF)
	{	
//		printf("%c", ch);
		cha++;
		if (ch=='\n')
		{
			cha++;
			break;
		}
	}

	rewind(fp);
//	printf ("%d", ftell(fp));
		printf("cha%d\n",cha);
	
	int dim=0;
	while(fscanf(fp, "%c", &ch)!=EOF)
	{
		if(ch=='\t')
			dim++;
	}
	dim=dim/count;
	printf("dim%d\n",dim);
	

	float thirty_per;
	thirty_per= 0.001*count;
	//printf(" %f", thirty_per);
	
	
	//fseek(fp, 0, SEEK_SET);
//	fseek(fp, 0, SEEK_SET);
	//randomize();
	int i, j=0, r;
	float var;
	char xd='\n';
	for (i=0; i<thirty_per; i++)
	{
		r=rand()%count;
		printf("r %d\n", r);
		//printf("%d ", r*cha);
		fseek(fp, r*cha, SEEK_SET);
		//printf(" %d", ftell(fp));
		for (j=0; j<dim; j++)
		{
			fscanf(fp, "%f", &var);
			fprintf(fp1, "%f ", var);
			printf("var %f\n", var);

		}
		//fprintf(fp1, "%c", xd);
		//rewind(fp);	
	}
	

	//printf("%d", ftell(fp));
	fclose(fp);
	fclose(fp1);
	
	return 0;
}
