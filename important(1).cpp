#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int main ()
{
	int kx;
int a,b;
int q;
float x1[1000];
float y1[1000];
float x2[1000];
float y2[1000];
float v;
q=0;
a=0;
b=0;
int c=0,d=0;
int i,j,k;
float mx1=0.0,mx2=0.0,my1=0.0,my2=0.0;
printf("Euclidean distance classifier\n");

FILE *fp=fopen("DataSet2.txt","r");
while(q<3000)
{
	fscanf(fp,"%f",&v);
	if(q%3==0)
	{
	x1[a]=v;
//	printf ("%f\n",x1[a]);
	a++;
}
	else if(q%3==1)
	{
	y1[b]=v;
//	printf ("%f\n",y1[b]);
	b++;
}
/*	else  
	{
	z=i;
	printf("%f\n",z);
}*/
	
	q++;
	//	printf("%d\n",j);//
	//	if(z==2)
	//	break;
}
q=0;
while(q<3000)
{
	fscanf(fp,"%f",&v);
	if(q%3==0)
	{
	x2[c]=v;
//	printf ("%f\n",x2[c]);
	c++;
}
	else if(q%3==1)
	{
	y2[d]=v;
//	printf ("%f\n",y2[d]);
	d++;
//	printf("%d\n",d);
}
/*	else  
	{
	z=i;
	printf("%f\n",z);
}*/
	
	q++;
//		printf("%d\n",q);//
	//	if(z==2)
	//	break;
}
// printf("\nenter no of data points u want to give for class1:");
// scanf("%d",&n1);
// printf("\nClass1:\n");


 for(i=0;i<a;i++)
 {
                // printf("x coordinate:    ");
                // scanf("%f",&x1[i]);
                 mx1=mx1+(x1[i]/a);
                // printf("%f\n",(mx1));
                 //scanf("%f",&y1[i]);
                 my1=my1+y1[i]/a;
 }
 
 
// printf("\nenter no of data points u want to give for class2:");
// scanf("%d",&n2);
// printf("\nClass2:\n");
for(i=0;i<c;i++)
 {
                // printf("x coordinate:    ");
                 //scanf("%f",&x2[i]);
                 mx2=mx2+x2[i]/c;
                // printf("y coordinate:    ");
                // scanf("%f",&y2[i]);
                 my2=my2+y2[i]/c;
 }
 printf("\nmeans\n");
 printf("%f\n",mx1);
 printf("%f\n",my1);
 printf("%f\n",mx2);
 printf("%f\n",my2);
 float we[2][1],wte[1][2],xo[2][1],E1[2][2],E2[2][2];
 float wm[2][1],wtm[1][2];
 float Einv1[2][2],Einv2[2][2];
 we[0][0]=mx2-mx1;
 we[1][0]=my2-my1;
 xo[0][0]=(mx1+mx2)/2.0;
 xo[1][0]=(my1+my2)/2.0;
 printf("wt vector:\n(");    //euclidean
 for(i=0;i<1;i++)
 {
                 for(j=0;j<2;j++)
                 {
                                 wte[i][j]=we[j][i];
                                 printf("%f",wte[i][j]);
                                 printf("\t");
                                 
                 }
 }
 printf(")\nconstant term:\t");
 float re=0.0;
 for(i=0;i<1;i++)
{
                  for(j=0;j<1;j++)
                  {
                                  for(k=0;k<2;k++)
                                  {
                                                  re=re-wte[i][k]*xo[k][j];
                                                
                                  }
                  }
}
  printf("%f",re);
printf("\n");
 for(i=0;i<2;i++)
 {
                 for(j=0;j<2;j++)
                 {
                 	E1[i][j]=0.0;
                 	E2[i][j]=0.0;
                 	Einv1[i][j]=0.0;
                 	Einv2[i][j]=0.0;
                 }
 }

  for(j=0;j<a;j++)
  {
	
	    E1[0][0]=E1[0][0]+pow((x1[j]-mx1),2)/a;
	    
  }
  for(j=0;j<a;j++)
  {
	
	    E1[0][1]=E1[0][1]+((x1[j]-mx1)*(y1[j]-my1))/a;
	    
  }
  for(j=0;j<a;j++)
  {
	
	    E1[1][1]=E1[1][0]+pow((y1[j]-my1),2)/a;
	    
  }
  E1[1][0]=E1[0][1];
  	printf("%f\n",E1[0][0]);
  		printf("%f\n",E1[0][1]);
  			printf("%f\n",E1[1][0]);
  				printf("%f\n",E1[1][1]);
  
  //
  for(j=0;j<c;j++)
  {
	
	    E2[0][0]=E2[0][0]+pow((x2[j]-mx2),2)/c;
  }
  for(j=0;j<c;j++)
  {
	
	    E2[0][1]=E2[0][1]+((x2[j]-mx2)*(y2[j]-my2))/c;
  }
  for(j=0;j<c;j++)
  {
	
	    E2[1][1]=E2[1][0]+pow((y2[j]-my2),2)/c;
  }
  E2[1][0]=E2[0][1];
  
  printf("%f\n",E2[0][0]);
  		printf("%f\n",E2[0][1]);
  			printf("%f\n",E2[1][0]);
  				printf("%f\n",E2[1][1]);
//
  float det1=0.0;
  det1=(E1[1][1]*E1[0][0])-(E1[0][1]*E1[1][0]);
  printf("%f\n",det1);
   float det2=0.0;
  det2=(E2[1][1]*E2[0][0])-(E2[0][1]*E2[1][0]);
  printf("%f\n",det2);
  
 printf("____\n"); 
 for(i=0;i<2;i++)
 {
                 for(j=0;j<2;j++)
                 {
                 	printf("%f\n",(E1[i][j]-E2[i][j]));
                 }
 }
 
 
 printf("____\n"); 
  Einv1[0][0]=(E1[1][1]/det1);
  Einv1[1][1]=(E1[0][0]/det1);
  Einv1[0][1]=(-E1[0][1]/det1);
  Einv1[1][0]=(-E1[1][0]/det1);
  
  	printf("%f\n",Einv1[0][0]);
  		printf("%f\n",Einv1[0][1]);
  			printf("%f\n",Einv1[1][0]);
  				printf("%f\n",Einv1[1][1]);
  				
  				
 printf("____\n"); 
  

  Einv2[0][0]=(E2[1][1]/det2);
  Einv2[1][1]=(E2[0][0]/det2);
  Einv2[0][1]=(-E2[0][1]/det2);
  Einv2[1][0]=(-E2[1][0]/det2);
  
   printf("%f\n",Einv2[0][0]);
  		printf("%f\n",Einv2[0][1]);
  			printf("%f\n",Einv2[1][0]);
  				printf("%f\n",Einv2[1][1]);
  	 printf("____\n"); 			
  				
  for(i=0;i<2;i++)
  for(j=0;j<1;j++)
  wm[i][j]=0.0;
  //
  for(i=0;i<2;i++)
{
                  for(j=0;j<1;j++)
                  {
                                  for(k=0;k<2;k++)
                                  {
                                                  wm[i][j]=wm[i][j]+Einv1[i][k]*we[k][j];
                                                 // printf("%f\n",ce[i][j]);
                                  }
                  }
}
  //
  
   	printf("%f\n",wm[0][0]);
	   	printf("%f\n",wm[1][0]);
		    printf("____\nMahalanobis distance classifier\n");
			//
			 printf("wt vector:\n(");  
			
			for(i=0;i<1;i++)
 {
                 for(j=0;j<2;j++)
                 {
                                 wtm[i][j]=wm[j][i];
                                 printf("%f",wtm[i][j]);
                                 printf("\t");
                                 
                 }
 }				
  	
	  
	   printf(")\nconstant term:\t");
float pu=0.0;
 for(i=0;i<1;i++)
{
                  for(j=0;j<1;j++)
                  {
                                  for(k=0;k<2;k++)
                                  {
                                                  pu=pu-wtm[i][k]*xo[k][j];
                                                 
                                  }
                  }
}

printf("%f",pu);
printf("\n");
//			
				  
 //perceptron
 printf("\n______\nperceptron classifier\n");
 
 float po[3][1];
 float pot[1][3];
 for(i=0;i<3;i++)
 for(j=0;j<1;j++)
 po[i][j]=1.0;
 for(i=0;i<1;i++)
 for(j=0;j<3;j++)
 pot[i][j]=1.0;
 
 float rho=0.7;
 float X[3][1];
 int l;
 float pro;
 int flag;
do
 {
 	//flag=0;
 //for class1
 for(l=0;l<a;l++){
                   flag=0;
                   X[0][0]=x1[l];
                   X[1][0]=y1[l];
                   X[2][0]=1.0;
 pro=0.0;                    
                   
for(i=0;i<1;i++)
{
                  for(j=0;j<1;j++)
                  {
                                  for(k=0;k<3;k++)
                                  {
                                                  pro=pro+pot[i][k]*X[k][j];
                                  }
                  }
}
if(pro<=0.0)
{
flag=1;
for(i=0;i<3;i++)
{
                  for(j=0;j<1;j++)
                  {
                   po[i][j]=po[i][j]+rho*X[i][j];
                  }
}
}
 for(i=0;i<1;i++)
 for(j=0;j<3;j++)
 pot[i][j]=po[j][i];
                 
               
 
}
                   
 //for class2
 for(l=0;l<c;l++){
                   flag=0;
                   X[0][0]=x2[l];
                   X[1][0]=y2[l];
                   X[2][0]=1.0;
 pro=0.0;                    
                   
for(i=0;i<1;i++)
{
                  for(j=0;j<1;j++)
                  {
                                  for(k=0;k<3;k++)
                                  {
                                                  pro=pro+pot[i][k]*X[k][j];
                                  }
                  }
}
if(pro>=0.0)
{
flag=1;           
for(i=0;i<3;i++)
{
                  for(j=0;j<1;j++)
                  {
                   po[i][j]=po[i][j]-rho*X[i][j];
                  }
}
}
 for(i=0;i<1;i++)
 for(j=0;j<3;j++)
 pot[i][j]=po[j][i];
                 
               
 
}
}while(flag!=0);
for(i=0;i<3;i++)
{for(j=0;j<1;j++)
{printf("%f",po[i][j]);}
printf("\n");
}
fclose(fp);
scanf("%d",&kx);
return 0;
}
