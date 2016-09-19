#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<math.h>
#define Layers 2
#define learning_rate 0.005

int neurons_for_layer[10];



struct train{              //for l= dimension of input
	struct nested_train{     //for j= Number of neurons in each layer
			
		float v;   //sigma(input*weight vector)
		float y;   //sigmoid(v)
		float weight[30];  //weight vector
		float e;   //error term
		float del;  //stores (e*derivative of(sigmoid(v)))
			
	}ob2[10];    //for max j = 5
			
}ob1[Layers+1];  //including input layer

struct training{
	
	float input[30]; //input for each training data
	
}classes[30];

struct testing{
	
	int misclass[30];
	float test_input[30];
	float mis_classification;
	
}test;


int bin_search(int rand_num[3000], int loop, int search )
{
	int i, flag=0;
	int first, middle, last;
	first = 1;
   	last = loop;
   	middle = (first+last)/2;
 
   while (first <= last) 
   {
      	if (rand_num[middle] < search)
         	first = middle + 1;    
      	else if (rand_num[middle] == search) 
	  	{
         	flag=1;
         	break;
    	}
      	else
         	last = middle - 1;
 
      	middle = (first + last)/2;
   }
   if (first > last)
		flag=0;
		
	return (flag);
}

	
void set_neurons()
{
	int l;
	
	printf("Neurons_for_layers %d : ",Layers);
	
	for(l=1;l<Layers;l++)
	{
		scanf("%d",&neurons_for_layer[l]);
	}
}

float sigmoid(float sample)
{
	float f;
	f=1/(1+pow(2.303,((-1)*sample)));
	return f;
}

float differentiate(float v1)
{
	return (sigmoid(v1)*(1-sigmoid(v1)));
}

void feed_forward(float x[30],int dimension,int cla)
{
	int j,r,k;
	
	neurons_for_layer[0] = dimension;
	
	for(r=0;r<Layers;r++)
	{
		ob1[r].ob2[0].y = 1.0; //bias term
	}
	
	for(k=1;k<=dimension;k++)
	{
		ob1[0].ob2[k].y = x[k]; //setting equal to a single line of training data
		
		//printf("\ny0:%f",ob1[0].ob2[k].y);
	}
	
	for(r=1;r<=Layers;r++)
	{
		for(j=1;j<=neurons_for_layer[r];j++)
		{
			ob1[r].ob2[j].v = 0.0;
			
			for(k=0;k<=neurons_for_layer[r-1];k++)
			{
				
			//	printf("\nweight : %f r:%d j:%d",ob1[r].ob2[j].weight[k],r,j);
				
				ob1[r].ob2[j].v = ob1[r].ob2[j].v+(ob1[r].ob2[j].weight[k])*(ob1[r-1].ob2[k].y);
				
			}
			
			ob1[r].ob2[j].y = sigmoid(ob1[r].ob2[j].v);
			
		//	printf("\nvv : %f r:%d j:%d",ob1[r].ob2[j].v,r,j);
		//	printf("\nyy : %f r:%d j:%d",ob1[r].ob2[j].y,r,j);
			
		}
	}
	
	if(cla!=0)
	{
	
	for(j=1;j<=neurons_for_layer[Layers];j++)
	{
		if(j==cla)
		{
			ob1[Layers].ob2[j].e = (sigmoid(ob1[Layers].ob2[j].v)-1.0);
		}
		else
		{
			ob1[Layers].ob2[j].e = (sigmoid(ob1[Layers].ob2[j].v)-0.0);
		}
	//	printf("\ne:%f",ob1[Layers].ob2[j].e);
	//	printf("\nv:%f",sigmoid(ob1[Layers].ob2[j].v));
	//	printf("\ny:%f",ob1[Layers].ob2[j].y);	
	}	
	
	}
	
}


void backprop()
{
	int r;
	int k;
	int j;
	for(j=1;j<=neurons_for_layer[Layers];j++)
	{
		ob1[Layers].ob2[j].del = (ob1[Layers].ob2[j].e)*(differentiate(ob1[Layers].ob2[j].v));
	}
	
	for(r=Layers;r>=2;r--)
	{
		for(j=1;j<=neurons_for_layer[r-1];j++)
		{
			ob1[r-1].ob2[j].del = 0.0;
			for(k=1;k<=neurons_for_layer[r];k++)
			{
				ob1[r-1].ob2[j].del+=(ob1[r].ob2[k].del)*(ob1[r].ob2[k].weight[j]);
			}
			ob1[r-1].ob2[j].del=(ob1[r-1].ob2[j].del)*differentiate(ob1[r-1].ob2[j].v);
		//	printf("\ndel :%f",ob1[Layers].ob2[j].del);
		}
		
	}
	//update weights
	for(r=1;r<=Layers;r++)
	{
		for(j=1;j<=neurons_for_layer[r];j++)
		{
			//printf("r :%d	j :%d	weight:",r,j);
			for(k=0;k<=neurons_for_layer[r-1];k++)
			{
				ob1[r].ob2[j].weight[k]+=(-1.0)*(learning_rate)*(ob1[r].ob2[j].del)*(ob1[r-1].ob2[k].y);
				//printf("\n%f",ob1[r].ob2[j].weight[k]);
			}
		}
	}
	
}

int ass_class(float d[30], int dim, float original_class) //to assign class based on minimum Mahalanobis distance
{
	int i = 0, min_class=0;
	int org_class=(int)original_class;
	for (i=0; i<dim-1; i++)
	{
		printf("\nd[%d] =	%f",i,d[i]);
		printf("\td[%d] =	%f",i+1,d[i+1]);
		if (d[i+1]>d[i])
		{
	//		printf("\n%d ",i+2);
			min_class = i+2;
		}
		else if (d[i]>d[i+1])
		{
		//	printf("\n%d ",i+1);
			min_class = i+1;
		}
	}
	
	//printf("\norg_class= %d		min_class= %d",org_class,min_class);
	
	if(min_class!=org_class)
	{
		return min_class;
	}
	else
	{
		return 0;
	}
}



int main()
{
	int value_miscls;
	
	set_neurons();
	
	char ch;
	int count=0;
	FILE *fp=fopen("DataSet1.txt", "r");
	FILE *fp1=fopen("test_data1.txt", "w");
	FILE *fp2=fopen("training_data1.txt", "w");

	if (fp==NULL)
		printf("Error");


//Writing test data onto another file
	
	while (fscanf(fp, "%c", &ch)!=EOF) //counting number of lines
	{
		if (ch=='\n')
			count++;
	}
	
	rewind(fp);
//	printf("\ncount : %d",count);
	
	int dim=1;
	while (fscanf(fp, "%c", &ch)!=EOF) //counting number of dimensions
	{	
//		cha++;
		if (ch=='\t' || ch==' ')
			dim++;		
		if (ch=='\n')
		{
//			cha++;
			break;
		}
	}
	rewind(fp);
	
//	int check=0;
//	//printf("%d ", ftell(fp));
//	fseek(fp, 7*cha, SEEK_CUR);
//	while (fscanf(fp, "%c", &ch)!=EOF)
//	{	
//		if (ch=='\n')
//		{
//			check++;
//			break;
//		}
//	}
		
	//printf ("%d ", cha);
	
//	int dim=1;
//	while(fscanf(fp, "%c", &ch)!='\n')
//	{
//		printf("%c", ch);
//		if(ch=='\t')
//		{
//			dim++;
//		}
//	}
//	printf("%d ", dim);
	
//	printf("%d %d ", count, dim);
	
	
	float thirty_per; //selecting percent of data to be used as test data
	thirty_per= 0.3*count;
	
	//printf(" %f", thirty_per);
	
	//fseek(fp, 0, SEEK_SET);
	rewind(fp); //setting file pointer to the beginning

	//printf("%d", ftell(fp));
	
	int line;
	srand(time(NULL));
	int i, j=0, r;
	float var;
	char xd='\n';
	int rand_num[3000];
	int loop=0;
	//rand_num= (int*)malloc(thirty_per*sizeof(int));
	rewind(fp);
	for (i=1; i<=thirty_per; i++)
	{
		r=(rand()%count)+1; //randomly generating line number
		rand_num[i]=r; //storing the line numbers in an array
		loop++; //keeping count of number of random numbers generated
		//printf(" Random: %d\n", r);
		//printf("%d ", r*cha);
		//fseek(fp, r*cha, SEEK_SET);
		//printf(" %d", ftell(fp));
		//fseek(fp, 0, SEEK_SET);
		line=1;
		while (line<=count)
		{
			//printf("Line: %d\n", line);
			if (line==r) //if line number==random number
			{
				for (j=0; j<dim; j++) //copying elements of that line
				{
					fscanf(fp, "%f", &var);
					fprintf(fp1, "%f ", var);
					//printf(" Nos: %f ", var);
				}
				break;
			}
			else
			{
				for (j=0; j<dim; j++) //copying elements of that line
				{
					fscanf(fp, "%f", &var);
				}
			}
			
			//if (sh=='\n')
			line++;
		}
	
		fprintf(fp1, "%c", xd);
		rewind(fp);	
	}
	//printf("%d", loop);
//	
//	for (i=1; i<=loop; i++)
//	{
//		printf("%d ", rand_num[i]);
//	}


//sorting rand_num
	int c, d, t;	
	for (c = 1 ; c <=loop; c++) 
	{
	    d = c;
	 
	    while ( d > 1 && rand_num[d] < rand_num[d-1]) 
		{
	      t = rand_num[d];
	      rand_num[d] = rand_num[d-1];
	      rand_num[d-1] = t;
	 
	      d--;
    }
  }

//	for (i=1; i<=loop; i++)
//	{
//		printf("%d ", rand_num[i]);
//	}
//
//	printf("\n");
//	
	j=1;
	for (i=2; i<=loop; i++) //removing repetitions
	{
		if (rand_num[j]!=rand_num[i])
		{
			j++;
			rand_num[j]=rand_num[i];
		}
	}
	
	int newloop; //size of new rand_num
	newloop=j;
	
//	for (i=1; i<=newloop; i++)
//	{
//		printf("%d ", rand_num[i]);
//	}

//test data without repetitions
	rewind(fp);
	FILE *fp3=fopen("new_test_data1.txt", "w+");
	
	for (i=1; i<=newloop; i++) //copying
	{
		line=1;
		while (line<=count)
		{
			//printf("Line: %d\n", line);
			if (line==rand_num[i]) //if line number==random number
			{
				for (j=0; j<dim; j++) //copying elements of that line
				{
					fscanf(fp, "%f", &var);
					fprintf(fp3, "%f ", var);
					//printf(" Nos: %f ", var);
				}
				break;
			}
			else
			{
				for (j=0; j<dim; j++) //copying elements of that line
				{
					fscanf(fp, "%f", &var);
				}
			}
			line++;
		}
	
		fprintf(fp3, "%c", xd);
		rewind(fp);	
	}

//training data	
	rewind(fp);
	line=1;
	int check;
	while (line<=count)
	{		
		//printf("Line:%d ", line);	
		check= bin_search(rand_num, loop, line); //checking if line number is in rand_num
		//printf("Check:%d ", check);
		
		if (check==0) //if not found, copy to training set
		{
			for (j=0; j<dim; j++) //copying elements of that line
				{
					fscanf(fp, "%f", &var);
					fprintf(fp2, "%f ", var);
				}
			
			//printf("%f ", var);
			line++;
			fprintf(fp2, "%c", xd);
		}
		else //if found
		{
			for (j=0; j<dim; j++) //copying elements of that line
				{
					fscanf(fp, "%f", &var);
				}
			line++;
		}
		
	}



	fclose(fp);
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
		

	fp2=fopen("training_data1.txt", "r");
	int cls[30];
	int num_total=0;
	int q;
	int vprev=1;
	
	rewind(fp2);
	while(fscanf(fp2,"%f", &var)!=EOF)        
	{
		num_total++;	//total number of numbers
	}
	
//	printf("Num-total: %d ", num_total);
	//q=num_total;
	q=0;
	rewind(fp2);
	int max_class=1;
	while (q<num_total)
	{
		fscanf(fp2, "%f", &var);
		if(q%dim==(dim-1)) //assuming last column indicates class 
		{
			vprev=(int)var; //vprev1 denotes the class
			cls[vprev]++; //cls stores number of datas in each class
			if (vprev>max_class)
				max_class=vprev; //max_class stores max value of cls
		}
		q++;
	}
	
//	printf("Max.class: %d\n ", max_class);
//	for (i=1; i<=max_class; i++)
//		printf("class[%d]: %d\n ", i, cls[i]); //total no of data points per class= no od data points in training data

	int k;	
	int cn; //iterates from 0 to less than dim-1
	int up;
	rewind(fp);
	rewind(fp2);
	//printf("%d ", ftell(fp2));
	
	
	neurons_for_layer[0] = dim-1;
	
	neurons_for_layer[Layers] = max_class;
	
	for(int r1=1;r1<=Layers;r1++)
	{
		for(int j1=1;j1<=neurons_for_layer[r1];j1++)
		{
			for(int k1=0;k1<=neurons_for_layer[r1-1];k1++)
			{
				ob1[r1].ob2[j1].weight[k1] = (rand()%3)/3.0;     //(rand()%5 + 1)/(rand()%10 + 5);    //random initialisation
			}
		}
	}
	
	
	
	
	for(i=1;i<=max_class;i++)    //max_class
	{
		line=1; //iteration variable
		while(line<=cls[i]) //in each loop
		{
			
			cn=1;
			for(j=0; j<dim-1; j++)
			{
				fscanf(fp2,"%f",&var);                             
				classes[i].input[cn]=var; //storing in x1, x2, ..xN
				cn++;
			}
			up=cn;    //copies cn 
			//printf("%d ", up);
			
			fscanf(fp2,"%f",&var); //to scan over the number representing class
			
			feed_forward(classes[i].input,dim-1,(int)var);
			
			backprop();
			
			line++;
		}
	}
	
/*	
	for(k=0;k<=neurons_for_layer[Layers-2];k++)
	{
		printf("\nwt vctr1:%f", ob1[1].ob2[1].weight[k]);
	}
	
	for(k=0;k<=neurons_for_layer[Layers-2];k++)
	{
		printf("\nwt vctr1:%f", ob1[1].ob2[2].weight[k]);
	}
*/	
/*	for(k=0;k<=neurons_for_layer[Layers-2];k++)
	{
		printf("\nwt vctr1:%f", ob1[1].ob2[3].weight[k]);
	}
	
	for(k=0;k<=neurons_for_layer[Layers-2];k++)
	{
		printf("\nwt vctr1:%f", ob1[1].ob2[4].weight[k]);
	}
*/	
/*
	for(k=0;k<=neurons_for_layer[Layers-1];k++)
	{
		printf("\nwt vctr2:%f", ob1[2].ob2[1].weight[k]);
	}
	
	for(k=0;k<=neurons_for_layer[Layers-1];k++)
	{
		printf("\nwt vctr2:%f", ob1[2].ob2[2].weight[k]);
	}
*/	
	fclose(fp2);
	
	//working on test data

	for(i=0;i<=max_class;i++)
	{
		test.misclass[i]=0;
	}
	
	FILE *fk=fopen("new_test_data1.txt","r");
	line=1;
//	rewind(fk);
	
	float check_output[30];
	
	while(line<=newloop/2)
	{
		cn=1;
		for(j=0; j<dim-1; j++)
		{
			fscanf(fk,"%f",&var);
			test.test_input[cn] = var;
			cn++;
		}
		
		
		feed_forward(test.test_input,dim-1,0);
		
		for(j=1;j<=neurons_for_layer[Layers];j++)
		{
			
			check_output[j-1] = ob1[Layers].ob2[j].y;
			
		}
		
		fscanf(fk,"%f",&var);
		line++;
		value_miscls = ass_class(check_output,neurons_for_layer[Layers],var);
		
		test.misclass[value_miscls]++;
		
	//	printf("\nasscls:	%d		testmiscls:		%d",value_miscls,test.misclass[value_miscls]);
		
	}
	
	for(r=1;r<=Layers;r++)
	{
		for(j=1;j<=neurons_for_layer[r];j++)
		{
			printf("\n\nr :%d	j :%d	weight:",r,j);
			for(k=0;k<=neurons_for_layer[r-1];k++)
			{
				printf("   %f",ob1[r].ob2[j].weight[k]);
			}
		}
	}
	
	for (i=1; i<=max_class; i++)
	{
		test.mis_classification+=((float)(test.misclass[i]))/((float)newloop);
	}
	
	fclose(fk);
	
	printf("\n\n\nThe misclassification error applying the holdout method for mlp is: %f", test.mis_classification);
	
	
	return 0;

}
