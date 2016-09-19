/*
Program to find misclassification for a particular dataset using k-fold method
*/
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<math.h>
#define kfold 5        //considering value of folds
struct fold  //structure 
{
	int misclass[30];   //points which are misclassified
	float datapoints[30];	//datapoints 
	float mis_classification;   //misclassification calculated as a ratio between the total no of misclassified points per fold and total no of test data points per fold
struct clas    //nested structure
{
	float m1[30];  //mean
	float Sigma[30][30];  //sigma matrix
	float x[30];  //datapoints
	
	
}clss[30]; //instance of structure clas
}training[kfold],test[kfold];  //instances of structure fold
float determinant(float a[30][30],float k)    //determinant function//recursive function
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
	det=det+s*(a[0][c]*determinant(b,k-1));  //function calling itself
	s=-1*s;
	}
}
return (det);  //returning determinant
}

float mahalanobis_distance(float sigmainv[30][30],float mean[30],int k,float x2[30]) //mahalanobis distance function
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
				dis=dis+dist[i][l]*A[l][j];          //calculating the mahalanobis distances for each class and for a particular data point 
			}
		}
	}
	return dis;    //returning distance
}



float transpose(float num[30][30],float fac[30][30],float mean_1[30],float r,float x_1[30])
{
	int cf=1;
float lx=0.0;                                            //function to calculate transpose of a matrix
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
return mahalanobis_distance(inverse,mean_1,r,x_1);    //returning the mahalanobis distance by calling the mahalanobis_distance() function
}

int assign_class(float d[30],int dim,float original_class_value)
{
	int org_class=(int)original_class_value;      //assigning class based on the mahalanobis distances calculatec
	int i, min_class=1;                          //and sending the class for which the distance is minimum 
	for (i=0; i<dim-1; i++)
	{
		if (d[i+1]<d[i])
			min_class=i+2;
	}
	if(min_class!=org_class)
	{
		return min_class;  
	}
	else
	{
		return 0;
	}

}


float cofactor(float num[30][30],float mea[30],float f,float x_3[30])
{                                      //function for calculating the cofactor of a matrix 
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
	
printf("******PROGRAM FOR CALCULATING AVERAGE MISCLASSIFICATION USING K-FOLD*******\n____________________\n");

int q;

float v;

int i,j,k;

float deter=0.0;

int n=1;

q=0;

char v2='a';

FILE *fb=fopen("DataSet1.txt","r");         //opening a file
while(v2!='\n')
{
	fscanf(fb,"%c",&v2);
	if(v2=='\t' || v2==' ')
	n++;                            //calculating the no. of dimensions
}


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

while(fscanf(fb,"%f",&v3)!=EOF)                           //while end of file is not reached
{
	q++;	
}

qc=q;

rewind(fb);
q=0;

while(q<qc)                           
{
	
		
	fscanf(fb,"%f",&v3);
	if(q%n==(n-1))
	{
		vprev1=v3;
		count[vprev1]++;   //keeping the value of no of datapoints belonging to each class
	}
	q++;	
}
fclose(fb);  //closing the file

for(i=1;i<=30;i++)
cou[i]=count[i];           //storing the value of count[i] in cou[i]

int totalcount=0;

for(i=1;i<=vprev1;i++)
{
	totalcount=totalcount+count[i];   //calculating total count that gives the total no of datapoints
}

int parts=totalcount/kfold;

int kfo=0;

for(kfo=0;kfo<kfold;kfo++)           //iterates till the value of kfold
{
int vprev=1;
q=0;
FILE *fout=fopen("DataSet1.txt","r");
FILE *fil=fopen("trainingset.txt","w+"); //opening a trainingset file
FILE *file=fopen("testset.txt","w+");  //opening a testset file

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
		
	}
	else
	{
		fscanf(fout,"%f",&s1);
		fprintf(fil,"%f\n",s1);
		q++;
		sb++;
		
	}
}
fclose(file);
fclose(fil);
fclose(fout);

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
q++;      
}
rewind(fbb);

int vc=q;
q=0;
vprev=1;
int s=1;

while(q<=vc)  
{
	fscanf(fbb,"%f",&v9);
	if(q%n==(n-1))
	{
	vprev=v9;
	count[vprev]++;   //keeping the value of no of datapoints belonging to each class
	}
	q++;	
}
rewind(fbb);

float v5;
i=1;
q=0;
int up=0;

for(i=1;i<=vprev;i++)
{
q=0;
while(q<(n*count[i]))
{
	cn=0;
	while(cn<n-1)
	{
		fscanf(fbb,"%f",&v1);
		training[kfo].clss[i].x[cn]=v1;              //storing the value of x1,x2,x3... for a particular datapoint belonging to class i
		cn++;
		q++;
	}
	up=cn;
	for(cn=0;cn<up;cn++)
	{
		training[kfo].clss[i].m1[cn]=training[kfo].clss[i].m1[cn]+training[kfo].clss[i].x[cn]/count[i];
		//calculating the means
	}
	q=q+1;
	fscanf(fbb,"%f",&v1);
}
}
rewind(fbb);
i=1;
q=0;

for(i=1;i<=vprev;i++)
{
q=0;	
while(q<(n*count[i]))
{
	cn=0;
	while(cn<n-1)
	{
		fscanf(fbb,"%f",&v1);
		training[kfo].clss[i].x[cn]=v1;  //storing the value of x1,x2,x3...,xn for a particular datapoint belonging to class i
		cn++;                           //x1,x2,x3......xn are dimensions
		q++;
	}
	
	for(j=0;j<cn;j++)
	{
		for(k=0;k<cn;k++)
		{
			training[kfo].clss[i].Sigma[j][k]=training[kfo].clss[i].Sigma[j][k]+((training[kfo].clss[i].x[j]-training[kfo].clss[i].m1[j])*(training[kfo].clss[i].x[k]-training[kfo].clss[i].m1[k])/count[i]);
			//calculating the sigma matrix
		}
		
	}
	q=q+1;
	fscanf(fbb,"%f",&v1);

}
}


fclose(fbb);

int i2;

for(i2=0;i2<=vprev;i2++)
{
	test[kfo].misclass[i2]=0;
}

FILE *fk=fopen("testset.txt","r");
q=0;	
while(q<sa)
{
	cn=0;
	while(cn<n-1)
	{
		fscanf(fk,"%f",&v1);
		test[kfo].datapoints[cn]=v1;     //storing test data point x1,x2,x3,....,xn values
		cn++;                           //x1,x2,x3......xn are dimensions
		q++;
	}
	

float maha_dists[30];	

for(i=1;i<=vprev;i++)
{
	
deter=determinant(training[kfo].clss[i].Sigma,n-1);  //calculating determinant

if(deter==0)
printf("\nInverse of Matrix is not possible\n");
else{
	maha_dists[i-1]=cofactor(training[kfo].clss[i].Sigma,training[kfo].clss[i].m1,n-1,test[kfo].datapoints);
	//storing mahalanobis distances temporarily for comparison
	}
}
fscanf(fk,"%f",&v1);

test[kfo].misclass[assign_class(maha_dists,i-1,v1)]++;  //assigning class;if misclassified then incremented 

q=q+1;

}

test[kfo].mis_classification=0.0;

for(i=1;i<=vprev;i++)
{
	test[kfo].mis_classification+=((float)(test[kfo].misclass[i]))/((float)(sa/n));  //calculating the misclassification ratio
}

printf("\nMisclassification for fold %d: %f\n",kfo+1,test[kfo].mis_classification); //printing misclassification for each fold

fclose(fk);
}

float avg_miscls; 

avg_miscls=0.0;
	
for(kfo=0;kfo<kfold;kfo++)
{
	avg_miscls=avg_miscls+test[kfo].mis_classification/kfold;  //calculating average misclassificationfor all folds
}
printf("\nAverage misclassification for %d folds: %f\n",kfold,avg_miscls);

getch();
	
return 0;

}
