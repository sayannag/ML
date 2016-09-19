#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
#include<ctype.h>

float lambda;

struct train{  //structure for training data
	
	struct nested_train{
		
		float weight[30];
		float bias;
		float weight_transpose[30];
		float mu;
		float weight_dummy[30];
		float distance;
	//	float sum_lambda;
		
	}inner[10];
	
	float input[30];
		
}training[10]; //considering maximum 10 classes

struct testing{
	
	float test_input[30];
	float mis_classification;
	int misclass[30]; 
	
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

float calculate_bias(float A[30],float B[30],float C[30],int size)
{
	int i;
	float bias_term = 0.0;
	float temp[30];
	for(i=0;i<size;i++)
	{
		temp[i] = A[i]+B[i];
	}
	for(i=0;i<size;i++)
	{
		bias_term = bias_term+C[i]*temp[i];
	}
	return ((-0.5)*bias_term);
}

/*float dist(float a[30],float b[30],int siz)
{
	int i;
	float sum =0.0;
	for(i=0;i<siz;i++)
	{
		sum = sum+pow((a[i] - b[i]),2.0);
	}
	return (sqrt(sum));
}*/

float kernel(float A[30],float B[30],int size)
{
	int i;
	float result;
	float sum = 0.0;
	for(i=0;i<size;i++)
	{
		sum = sum+A[i]*B[i];
	}
	result = 1/(1+pow(2.303,((-1)*sum))); //dset1 = (sum+3.54),1.0 		//dset2 = (sum+2.0),1.0
	return (result);
}





int ass_class(float original_class, int maxclass,int alpha) //to assign class based on minimum Mahalanobis distance
{
	int j;
	int org_class=(int)original_class;
	int i = org_class;
	int cn = 0;
	for (j=1; j<=maxclass; j++)
	{
		if(i!=j)
		{
		//	training[i].inner[j].distance  += training[i].inner[j].bias;
		//	printf("\n sum : %f  i:%d	j:%d",training[i].inner[j].distance,i,j);
			if(i<j)
			{
			training[i].inner[j].distance += (float)alpha; 		//dset1 = 4.5
			} 
			else
			{
			training[i].inner[j].distance -= (float)alpha;
			}      
		}
	}
	
	for(j=1;j<=maxclass;j++)
	{
		if(i!=j)
		{
			if(i<j)
			{
				if(training[i].inner[j].distance<0)
				{
					printf("\n sum : %f  i:%d	j:%d",training[i].inner[j].distance,i,j);
					return j;
					
				}
				else 
				{
				//	printf("\n sum : %f    j : %d",training[i].inner[j].distance,j);
					return 0;
					
				}
			}
			else if(i>j)
			{
				if(training[i].inner[j].distance>0)
				{
					printf("\n sum : %f    j : %d",training[i].inner[j].distance,j);
					return j;
					
				}
				else
				{
				//	printf("\n sum : %f    j : %d",training[i].inner[j].distance,j);
					return 0;
				
				}
			}
		}
	}
	
	/*printf("\norg_class= %d		min_class= %d",org_class,min_class);
	
	if(min_class!=org_class)
	{
		return min_class;
	}
	else
	{
		return 0;
	}*/
}


int main()
{	
	int value_miscls = 0;
	char ch;
	int count=0;
	FILE *fp=fopen("iris2.txt", "r");
	FILE *fp1=fopen("test_data4.txt", "w");
	FILE *fp2=fopen("training_data4.txt", "w");

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
	float variable;
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
	FILE *fp3=fopen("new_test_data4.txt", "w+");
	
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
		

	fp2=fopen("training_data4.txt", "r");
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
		if(q%dim==(dim-1)) //assuming last column indicates class   /////   
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


//setting values of mu

for(i=1;i<=max_class;i++)
{
	for(j=1;j<=max_class;j++)
	{
		if(i!=j)
		{
			//printf("\ncls[i]+cls[j]	:%d",cls[i]+cls[j]);
			training[i].inner[j].mu = 1.0/(float)(cls[i]+cls[j]);
			//printf("\ntraining[i].inner[j].mu	:%f",training[i].inner[j].mu);
		}		
	}
}
int set;
for(i=1;i<=max_class;i++)
{
	for(j=1;j<=max_class;j++)
	{
		set = 0;
		if(i!=j)
		{
			while(set<dim-1)
			{
				training[i].inner[j].weight_dummy[set] = 0.0;
				set++;
			}
			
		}		
	}
}


////////



////////////
	int k;	
	int cn; //iterates from 0 to less than dim-1
	int up;
	rewind(fp);
	rewind(fp2);
	//printf("%d ", ftell(fp2));

for(i=1;i<=max_class;i++)    //max_class
	{
		
		line=1; //iteration variable
			
		while(line<=cls[i]) //in each loop
		{
			cn=0;
			for(j=0; j<dim-1; j++)
			{
				fscanf(fp2,"%f",&var);                             
				training[i].input[cn]=var; //storing in x1, x2, ..xN
				cn++;
			}
			up=cn;    
			
			for(j=1;j<=max_class;j++)
			{
				cn=0;
				if(i!=j)
				{
					lambda = training[i].inner[j].mu;
					
					while(cn<up)
					{
						training[i].inner[j].weight_dummy[cn] += lambda*training[i].input[cn];
					//	printf("training[i].inner[j].weight_dummy[cn]	:%f",training[i].inner[j].weight_dummy[cn]);	
						cn++;
					}
					//printf("\n");
				}
				
			}
			
			fscanf(fp2,"%f",&var); //to scan over the number representing class
			
			line++;
		}
		
		
	}
		
	rewind(fp2);
	
	
	
	for(i=1;i<=max_class;i++)
	{
		for(j=1;j<=max_class;j++)
		{
			if(i!=j)
			{
				cn = 0;
				if(i<j)
				{
					while(cn<dim-1)
					{
						training[i].inner[j].weight[cn] = (1.0)*training[i].inner[j].weight_dummy[cn];
					//	printf("\ni<j	training[i].inner[j].weight[cn]	:%f",training[i].inner[j].weight[cn]);
						cn++;
					}
				}
				else if(i>j)
				{
					while(cn<dim-1)
					{
						training[i].inner[j].weight[cn] = (-1.0)*training[i].inner[j].weight_dummy[cn];
					//	printf("\ni>j	training[i].inner[j].weight[cn]	:%f",training[i].inner[j].weight[cn]);
						cn++;
					}
				}
			}
		}
	}
	
	for(i=1;i<max_class;i++)
	{
		for(j=i+1;j<=max_class;j++)
		{
			cn = 0;
			while(cn<dim-1)
			{
				training[i].inner[j].weight[cn] = training[i].inner[j].weight[cn]+training[j].inner[i].weight[cn];
				training[j].inner[i].weight[cn] = training[i].inner[j].weight[cn];
			//	printf("\ntraining[i].inner[j].weight[cn]	:%f",training[i].inner[j].weight[cn]);
			//	printf("\ntraining[j].inner[i].weight[cn]	:%f",training[j].inner[i].weight[cn]);
				cn++;
			}
		}
	}
	
	
	for(i=1;i<max_class;i++)
	{
		for(j=i+1;j<=max_class;j++)
		{
			training[i].inner[j].bias = calculate_bias(training[i].inner[j].weight_dummy,training[j].inner[i].weight_dummy,training[i].inner[j].weight,dim-1);
			training[j].inner[i].bias = training[i].inner[j].bias;
		//	printf("\ntraining[i].inner[j].bias	:%f",training[i].inner[j].bias);
		//	printf("\ntraining[j].inner[i].bias	:%f",training[j].inner[i].bias);
			
		}
	}
	
	//working on test data
	int newline;
	
	rewind(fp2);
	
	for(i=0;i<=max_class;i++)
	{
		test.misclass[i]=0;
	}
	
	FILE *fk=fopen("new_test_data4.txt","r");
	line=1;
	//rewind(fk);
	
	while(line<=newloop)
	{
		
	for(i=1;i<=max_class;i++)
	{
		for(j=1;j<=max_class;j++)
		{
			if(i!=j)
			{
				training[i].inner[j].distance = 0.0;
			}		
		}
	}	
		cn=0;
		for(j=0; j<dim-1; j++)
		{
			fscanf(fk,"%f",&var);
			test.test_input[cn] = var;
			//printf("\ntest_input:		%f",test.test_input[cn]);
			cn++;
		}
		fscanf(fk,"%f",&variable);
	//	printf("\nvariable:		%f",variable);
	
	for(i=1;i<=max_class;i++)
	{
		newline=1;
		while(newline<=cls[i]) //in each loop
		{	
			cn=0;
			for(j=0; j<dim-1; j++)
			{
				fscanf(fp2,"%f",&var);                             
				training[i].input[cn]=var; //storing in x1, x2, ..xN
			//	printf("\ntraining_input:		%f",training[i].input[cn]);
				cn++;
			}
			up=cn;    
		fscanf(fp2,"%f",&var);	
	//	printf("\nclass:		%f",var);
		for(j=1;j<=max_class;j++)
		{
			if(i!=j)
			{
				lambda = training[i].inner[j].mu;
				if(i<j)
				{
					training[i].inner[j].distance += (1.0)*lambda*kernel(training[i].input,test.test_input,dim-1);
				//	printf("\ni<j	training[i].inner[j].distance	:%f",training[i].inner[j].distance);
				}
				else if(i>j)
				{
					training[i].inner[j].distance += (-1.0)*lambda*kernel(training[i].input,test.test_input,dim-1);
				//	printf("\ni>j	training[i].inner[j].distance	:%f",training[i].inner[j].distance);
				}
			}
		}
		newline++;
		}
	}
	
	
	for(i=1;i<max_class;i++)
	{
		for(j=i+1;j<=max_class;j++)
		{
		//	printf("\ntraining[i].inner[j].distance	:%f",training[i].inner[j].distance);
			training[i].inner[j].distance = training[i].inner[j].distance+training[j].inner[i].distance;
			training[j].inner[i].distance = training[i].inner[j].distance;
		//	printf("\ntraining[i].inner[j].distance	:%f",training[i].inner[j].distance);
		//	printf("\ntraining[j].inner[i].distance	:%f",training[j].inner[i].distance);
		}
	}
	
	
		
		rewind(fp2);
		
		//printf("\nvar:		%f",varr);
		
		value_miscls = ass_class(variable,max_class,test.misclass[value_miscls]);
		
		test.misclass[value_miscls]++;
		
		//printf("\nvalue_miscls  :%d		test.misclass  : %d", value_miscls,test.misclass[value_miscls]);
		
		line++;
		
	}
	
	fclose(fp2);
	fclose(fk);
	
	for (i=1; i<=max_class; i++)
	{
		test.mis_classification+=((float)(test.misclass[i]))/((float)newloop);
	}
	
	
	printf("\nThe misclassification error for the holdout method is: %f", test.mis_classification);
	
	return 0;
}

