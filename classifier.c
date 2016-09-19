#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<math.h>
struct clas
{
	float m1[30];
	float Sigma[30][30];
	float x[30];
	float weight[30][1];
	float weightTranspose[1][30];
	float constant[30][1];
}qew[30];
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

void transpose(float num[30][30],float fac[30][30],float r,float u[30][1],float tq[30][1])
{
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
printf("\t%f",inverse[i][j]);
}
printf("\n");
}
*/
	float wm[30][1];
	int k;
	for(i=0;i<r;i++)
	{
		for(j=0;j<1;j++)
		{
			wm[i][j]=0.0;
		}
	}

  for(i=0;i<r;i++)
{
                  for(j=0;j<1;j++)
                  {
                                  for(k=0;k<r;k++)
                                  {
                                                  wm[i][j]=wm[i][j]+inverse[i][k]*u[k][j];    //calculating weight vector
                                                 
                                  }
                  }
}
for(i=0;i<r;i++)
for(j=0;j<1;j++)
printf("%f\n",wm[i][j]);

float wmt[1][30];

for(i=0;i<1;i++)
for(j=0;j<r;j++)
wmt[i][j]=wm[j][i];


for(i=0;i<1;i++)
{
                  for(j=0;j<1;j++)
                  {
                                  for(k=0;k<r;k++)
                                  {
                                                  lx=lx-wmt[i][k]*tq[k][j];    //calculating constant
                                                 
                                  }
                  }
}
printf("%f\n",lx);
}
void cofactor(float num[30][30],float f,float u1[30][1],float wq[30][1])
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
	transpose(num,fac,f,u1,wq);
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
FILE *fa=fopen("DataSet1.txt","r");
while(v2!='\n')
{
	fscanf(fa,"%c",&v2);
	if(v2==',')
	n++;
}

fclose(fa);
q=0;
int vprev=1;
int count[30];
for(i=1;i<=30;i++)
count[i]=0; 
float v3;

FILE *fb=fopen("DataSet1.txt","r");
for(q=0;q<6000;q++)
{
	
		
		fscanf(fb,"%f",&v3);
		if(q%n==0)
	{
	vprev=v3;
	count[vprev]++;
	}
		
}
fclose(fb);
int cn=0;
q=0;
float v1;
int g;
for(i=1;i<=vprev;i++)
{
	for(j=0;j<n-1;j++)
	{
		qew[i].m1[j]=0.0;
	}
	for(j=0;j<n-1;j++)
	{
		for(k=0;k<n-1;k++)
		{
			qew[i].Sigma[j][k]=0.0;
		}
	}
}
float v5;
i=1;
q=0;
int up=0;
FILE *fo=fopen("DataSet1.txt","r");
for(i=1;i<=vprev;i++)
{
	q=0;
while(q<(n*count[i]))
{
	
	fscanf(fo,"%f",&v1);
	q=q+1;
	cn=0;
	while(cn<n-1)
	{
		fscanf(fo,"%f",&v1);
		qew[i].x[cn]=v1;
		cn++;
		q++;
	}
	up=cn;
	for(cn=0;cn<up;cn++)
	{
		qew[i].m1[cn]=qew[i].m1[cn]+qew[i].x[cn]/count[i];
	}

}
}
fclose(fo);
i=1;
q=0;
FILE *fl=fopen("DataSet1.txt","r");
for(i=1;i<=vprev;i++)
{
	q=0;
while(q<(n*count[i]))
{
	
	fscanf(fl,"%f",&v1);
	q=q+1;
	cn=0;
	while(cn<n-1)
	{
		fscanf(fl,"%f",&v1);
		qew[i].x[cn]=v1;
		cn++;
		q++;
	}
	
	for(j=0;j<cn;j++)
	{
		for(k=0;k<cn;k++)
		{
			qew[i].Sigma[j][k]=qew[i].Sigma[j][k]+((qew[i].x[j]-qew[i].m1[j])*(qew[i].x[k]-qew[i].m1[k])/count[i]);
			//printf("%f\t",qew[i].Sigma[j][k]);
		}
		//printf("\n----\n");
	}
//	printf("%d\n",q);
}
}
for(i=1;i<vprev;i++)
{
	for(j=i+1;j<=vprev;j++)
	{
		for(k=0;k<n-1;k++)
		{
			qew[i].weight[k][0]=qew[i].m1[k]-qew[j].m1[k];
			//printf("%f\t",qew[i].weight[k][0]);
		}
	}	
}
for(i=1;i<vprev;i++)
{
	for(j=i+1;j<=vprev;j++)
	{
		for(k=0;k<n-1;k++)
		{
			qew[i].constant[k][0]=(qew[i].m1[k]+qew[j].m1[k])/2;
			//printf("%f\t",qew[i].constant[k][0]);
		}
	}	
}
int row;
int col;
for(i=1;i<vprev;i++)
{
	for(row=0;row<1;row++)
	{
		for(col=0;col<n-1;col++)
		{
			qew[i].weightTranspose[row][col]=qew[i].weight[col][row];
		}
	}
}
int er;
float lx[30];
for(er=1;er<vprev;er++)
lx[er]=0.0;
for(er=1;er<vprev;er++)
{
for(i=0;i<1;i++)
{
                  for(j=0;j<1;j++)
                  {
                                  for(k=0;k<n-1;k++)
                                  {
                                                  lx[er]=lx[er]-qew[er].weightTranspose[i][k]*qew[er].constant[k][j];
                                                 
                                  }
                  }
}
}
for(er=1;er<vprev;er++)
{
printf("Minimum distance classifier of the format ax+by+c=0 where a,b,c are shown vertically downwards between class%d and %d:\n",er,er+1);
for(k=0;k<n-1;k++)
		{
			printf("%f\n",qew[er].weight[k][0]);
		}
printf("%f\n",lx[er]);
}
/*
printf("\n----\n");
*/
j=1;
while(j<vprev)
{
	
for(i=1;i<=vprev;i++)
{
deter=determinant(qew[i].Sigma,n-1);
//printf("Determinant of the Matrix = %f",deter);
if(deter==0)
printf("\nInverse of Matrix is not possible\n");
else
{
printf("Mahalanobis classifier of the format ax+by+c=0 where a,b,c are shown vertically downwards taking sigma matrix for class%d:\n",i);
cofactor(qew[i].Sigma,n-1,qew[j].weight,qew[j].constant);
}
}
j++;
}
fclose(fl);
getch();
return 0;
}

