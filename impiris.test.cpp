#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<math.h>
#define kfold 5 
struct fold
{
	int whichclass[30];
	float datapoints[30];	
struct clas
{
	float m1[30];
	float Sigma[30][30];
	float x[30];
	float accuracy;

}clss[30];
}training[kfold],test[kfold];
float determinant(float a[30][30],float k)
{
	float s=1.0,det=0.0,b[30][30];
	int i,j,m,n,c;
	if(k==1)
	{
		return (a[0][0]);
	}
	else
	{
		det=0;
		for(c=0;c<k;c++)
	{
	m=0;
	n=0;
	for(i=0;i<k;i++)
	{
		for(j=0;j<k;j++)
		{
			b[i][j]=0;
			if(i!=0&&j!=c)
			{
				b[m][n]=a[i][j];
				if(n<(k-2))
				n++;
				else
				{
					n=0;
					m++;	
				}
			}
		}
	}
	det=det+s*(a[0][c]*determinant(b,k-1));
	s=-1*s;
	}
}
return (det);
}

float mahalanobis_distance(float sigmainv[30][30],float mean[30],int k,float x2[30])
{
	int i;
	float dist[1][30];
	float A[30][1];
	for(i=0;i<k;i++)
	{
		A[i][0]=(x2[i]-mean[i]);
	}
	float B[1][30];
	int j;
	int l;
	for(i=0;i<1;i++)
	{
		for(j=0;j<k;j++)
		{
			B[i][j]=A[j][i];
		}
	}
	for(i=0;i<1;i++)
	{
		for(j=0;j<k;j++)
		{
			dist[i][j]=0.0;
		}
	}
	for(i=0;i<1;i++)
	{
		for(j=0;j<k;j++)
		{
			for(l=0;l<k;l++)
			{
				dist[i][j]=dist[i][j]+B[i][l]*sigmainv[l][j];
			}
		}
	}
	float dis=0.0;
	for(i=0;i<1;i++)
	{
		for(j=0;j<1;j++)
		{
			for(l=0;l<k;l++)
			{
				dis=dis+dist[i][l]*A[l][j];
			}
		}
	}
	return dis;
}



float transpose(float num[30][30],float fac[30][30],float mean_1[30],float r,float x_1[30])
{
	int cf=1;
float lx=0.0;
int i,j;
float b[30][30],inverse[30][30],d;
for(i=0;i<r;i++)
{
	for(j=0;j<r;j++)
	{
		b[i][j]=fac[j][i];
	}
	}
d=determinant(num,r);
for(i=0;i<r;i++)
{
	for(j=0;j<r;j++)                      //calculating the inverse 
	{
		inverse[i][j]=b[i][j]/d;
	}
}
/*
printf("\n\n\nThe inverse of matrix is : \n");
for(i=0;i<r;i++)
{
for(j=0;j<r;j++)
{
printf(",%f",inverse[i][j]);
}
printf("\n");
}
*/
//printf("\nmd:%f\n",mahalanobis_distance(inverse,mean_1,r,x_1));

return mahalanobis_distance(inverse,mean_1,r,x_1);
}

int minimumdistancefunc(float distanc[30],int e)
{
	int r1,i1,j,temp;;
	float cpydist[30];
	float minm;
	for(r1=1;r1<=e;r1++)
	{
		cpydist[r1]=distanc[r1];
	}
	for(i1=1;i1<e;i1++)
	{
		for(j=i1+1;j<=e;j++)
		{
			if(cpydist[i1]>cpydist[j])
			{
				temp=cpydist[i1];
				cpydist[i1]=cpydist[j];
				cpydist[j]=temp;
			}
		}
	}
	minm=cpydist[1];
	for(r1=1;r1<=e;r1++)
	{
		if(minm==distanc[r1])
		{
			return r1;
		}
	}
}


float cofactor(float num[30][30],float mea[30],float f,float x_3[30])
{
	float b[30][30],fac[30][30];
	int p,q,m,n,i,j;
	for(q=0;q<f;q++)
	{
	for(p=0;p<f;p++)
	{
		m=0;
		n=0;
	for(i=0;i<f;i++)
	{
	for(j=0;j<f;j++)
	{
		if(i!=q&&j!=p)
		{
			b[m][n]=num[i][j];
			if(n<(f-2))
			n++;
			else
			{
				n=0;
				m++;
			}
		}
	}
	}
	fac[q][p]=pow(-1,q+p)*determinant(b,f-1);
	}
	}
	
	return transpose(num,fac,mea,f,x_3);
}	
int main()
{
int a,b;
int q;
float v;
int i,j,k;
int h1=0;
float deter=0.0;
int n=1;
q=0;
char v2='a';
FILE *fb=fopen("iris.txt","r");
while(v2!='\n')
{
	fscanf(fb,"%c",&v2);
	if(v2==',')
	n++;
}

//fclose(fb);
q=0;

int vprev1=1;
int count[30];
int cou[30];
for(i=1;i<=30;i++)
count[i]=0; 
float v3;
q=0;
int qc;
rewind(fb);
//FILE *fb=fopen("iris.txt","r");
while(fscanf(fb,"%f",&v3)!=EOF)                           //fscanf(fb,"%f",&v3)!=EOF
{
	q++;	
}
//fclose(fb);
qc=q;
//printf("%d\n",qc);
rewind(fb);
q=0;
//FILE *fbbb=fopen("iris.txt","r");
while(q<qc)                           //fscanf(fb,"%f",&v3)!=EOF
{
	
		
		fscanf(fb,"%f",&v3);
		if(q%n==(n-1))
	{
	vprev1=v3;
	count[vprev1]++;
	}
	q++;	
}
//printf("%d\n",q);
fclose(fb);
for(i=1;i<=30;i++)
cou[i]=count[i]; 
int totalcount=0;
for(i=1;i<=vprev1;i++)
{
	totalcount=totalcount+count[i];
}
//printf("count:%d\n",count[1]);
//printf("count:%d\n",count[2]);
//totalcount=totalcount*vprev1;
int parts=totalcount/kfold;
//printf("parts%d\n:",parts);
int kfo=0;
//////

//printf("total count:%d\n",totalcount);
///////
for(kfo=0;kfo<kfold;kfo++)
{
int vprev=1;////////////////////////////
q=0;
FILE *fout=fopen("iris.txt","r");
FILE *fil=fopen("trainingset.txt","w+");
FILE *file=fopen("testset.txt","w+");

int sa=0,sb=0;
float s1;
while(q<(n*totalcount))
{
	if(q>=(kfo*parts*n)&&q<(((kfo+1)*parts*n)))
	{
		fscanf(fout,"%f",&s1);
		fprintf(file,"%f\n",s1);
		q++;
		sa++;
		//printf("test%d\n",q);
	}
	else
	{
		fscanf(fout,"%f",&s1);
		fprintf(fil,"%f\n",s1);
		q++;
		sb++;
		//printf("training%d\n",q);
	}
}
fclose(file);
fclose(fil);
fclose(fout);
//printf("test%d\n",sa);
//printf("training%d\n",sb);
int cn=0;
q=0;
float v1;
int g;
for(i=1;i<=vprev;i++)
{
	for(j=0;j<n-1;j++)
	{
		training[kfo].clss[i].m1[j]=0.0;
	}
	for(j=0;j<n-1;j++)
	{
		for(k=0;k<n-1;k++)
		{
			training[kfo].clss[i].Sigma[j][k]=0.0;
		}
	}
}
float v9;
for(i=1;i<=30;i++)
count[i]=0; 
FILE *fbb=fopen("trainingset.txt","r");
q=0;

while(fscanf(fbb,"%f",&v9)!=EOF)  
{
//printf("\n%f",v9);
q++;
}
rewind(fbb);

int vc=q;
q=0;
vprev=1;
int s=1;
//FILE *fbb=fopen("trainingset.txt","r");
while(q<=vc)  //fscanf(fbb,"%f",&v9)!=EOF
{
	fscanf(fbb,"%f",&v9);
	if(q%n==(n-1))
	{
	vprev=v9;
//	if(v9==1)
//	s++;
	count[vprev]++;
	}
	q++;	
}
rewind(fbb);
//printf("\n%d\n",s);
//printf("%d\n",count[1]*n);
//printf("%d\n",count[2]*n);
//
float v5;
i=1;
q=0;
int up=0;
//FILE *fo=fopen("trainingset.txt","r");
for(i=1;i<=vprev;i++)
{
q=0;
while(q<(n*count[i]))
{
	cn=0;
	while(cn<n-1)
	{
		fscanf(fbb,"%f",&v1);
		training[kfo].clss[i].x[cn]=v1;
		cn++;
		q++;
	}
	up=cn;
	for(cn=0;cn<up;cn++)
	{
		training[kfo].clss[i].m1[cn]=training[kfo].clss[i].m1[cn]+training[kfo].clss[i].x[cn]/count[i];
	}
	q=q+1;
	fscanf(fbb,"%f",&v1);
}
}
rewind(fbb);
i=1;
q=0;
//FILE *fl=fopen("trainingset.txt","r");
for(i=1;i<=vprev;i++)
{
q=0;	
while(q<(n*count[i]))
{
	cn=0;
	while(cn<n-1)
	{
		fscanf(fbb,"%f",&v1);
		training[kfo].clss[i].x[cn]=v1;
		cn++;
		q++;
	}
	
	for(j=0;j<cn;j++)
	{
		for(k=0;k<cn;k++)
		{
			training[kfo].clss[i].Sigma[j][k]=training[kfo].clss[i].Sigma[j][k]+((training[kfo].clss[i].x[j]-training[kfo].clss[i].m1[j])*(training[kfo].clss[i].x[k]-training[kfo].clss[i].m1[k])/count[i]);
			//printf("%f\t",training[kfo].clss[i].Sigma[j][k]);
		}
		//printf("\n----\n");
	}
	q=q+1;
	fscanf(fbb,"%f",&v1);
//	printf("%d\n",q);
}
}


fclose(fbb);
/*
printf("\n______%f\n",training[kfo].clss[1].Sigma[0][0]);
printf("\n______%f\n",training[kfo].clss[1].Sigma[0][1]);
printf("\n______%f\n",training[kfo].clss[1].Sigma[1][0]);
printf("\n______%f\n",training[kfo].clss[1].Sigma[1][1]);
printf("\n__%f\n",training[kfo].clss[2].Sigma[0][0]);
printf("\n__%f\n",training[kfo].clss[2].Sigma[0][1]);
printf("\n__%f\n",training[kfo].clss[2].Sigma[1][0]);
printf("\n__%f\n",training[kfo].clss[2].Sigma[1][1]);
*/
int i2;
for(i2=1;i2<=vprev;i2++)
{
	test[kfo].whichclass[i2]=0;
}

FILE *fk=fopen("testset.txt","r");
q=0;	
while(q<sa)
{
	cn=0;
	while(cn<n-1)
	{
		fscanf(fk,"%f",&v1);
		test[kfo].datapoints[cn]=v1;
		cn++;
		q++;
	}
	

float fku[30];	
for(i=1;i<=vprev;i++)
{	
deter=determinant(training[kfo].clss[i].Sigma,n-1);
//printf("Determinant of the Matrix = %f",deter);
if(deter==0)
printf("\nInverse of Matrix is not possible\n");
else{
	
//	printf("Mahalanobis classifier of the format ax+by+c=0 where a,b,c are shown vertically downwards taking sigma matrix for class%d:\n",i);
	fku[i]=cofactor(training[kfo].clss[i].Sigma,training[kfo].clss[i].m1,n-1,test[kfo].datapoints);
	//printf("dist %d:%f\n",i,fku[i]);
//	printf("%d\n",i);
	
//	printf("%d\n",q);
}
}
//printf("%d\n",minimumdistancefunc(fku,i-1));
test[kfo].whichclass[minimumdistancefunc(fku,i-1)]++;
q=q+1;
fscanf(fk,"%f",&v1);
}
//printf("%d\n%d\n",test[kfo].whichclass[1],cou[1]);
//printf("%d\n%d\n",test[kfo].whichclass[2],cou[2]);
for(i=1;i<=vprev;i++)
{
	test[kfo].clss[i].accuracy=((float)(test[kfo].whichclass[i]+count[i]))/((float)cou[i]);
	//printf("\nacc: %d,%d,%f\n",test[kfo].whichclass[i]+count[i],cou[i],test[kfo].clss[i].accuracy);
}
fclose(fk);
}

float avg[30];
int i3=1;
while(i3<=2)
{
	avg[i3]=0.0;
	for(kfo=0;kfo<kfold;kfo++)
	{
		avg[i3]=avg[i3]+test[kfo].clss[i3].accuracy/kfold;
	}
	printf("avg accuracy for cls %d : %f\n",i3,avg[i3]);
	i3++;
}

getch();
return 0;
}
