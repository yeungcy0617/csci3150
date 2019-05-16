#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>
#include<unistd.h>
#include"util.h"

// If you have referenced to any source code that is not written by you
// You have to cite them here.

int num, *result, *count, pdim, *phash, *pBound;
Point *pPoints;

void *checker(void *x){
	//NODE ID = POS +1
	int pos = *(int*)x,isPrevailing,min;
	int i,j,k;
	float *val_target, *val_current;

	min = pos-1 < 0? 0 : pBound[pos-1];

	for(k = min; k < pBound[pos]; k++){
		val_current = pPoints[k].values;
		if (phash[k]==0)
		{
			continue;
			/* code */
		}
		for (i = 0; i < num; i++){ //compute new node, 'target' is prevailing 'current'?
			if(phash[i] == 0) //No point compare those has prevail;
				continue;

			int sum = 0;
			for (int j = 0; j < pdim; j++)
			{
				if (pPoints[k].values[j] < pPoints[i].values[j])
				{
					sum++;/* code */
				}else{break;}
				if(sum==pdim)
					phash[i]=0;
				/* code */
			}		
			int sum2 = 0;
			for (int j = 0; j < pdim; j++)
			{
				if (pPoints[k].values[j] > pPoints[i].values[j])
				{
					sum2++;/* code */
				}else{break;}
				if(sum2==pdim)
					phash[k]=0;
				/* code */
			}						
		}
	}
	
	pthread_exit(NULL);
}

int asgn2_pthread(Point * points, Point ** pPermissiblePoints, int number, int dim, int thread_number)
{
    // points -- input data
    // pPermissiblePoints -- your computed answer
    // number -- number of points in dataset
    // dim -- the dimension of the dataset
    // thread_number -- the number of threads (cores) to use
   	
	int permissiblePointNum = 0, i, j, k, current_pos[number], current_thread = 0;
	Point *permissiblePoints = malloc(sizeof(Point)*number);
	int hash[number]; //HASH: 0->hasPrevail, 1->DONT HAVE
  	void *status;
  	int bound[thread_number], t[thread_number];

  	//Set Global Access
	num = number;
	pdim = dim;
	pBound = bound;
	pPoints = points;
	phash = hash;

	for(i=0; i < number; i++) //initialize
		hash[i] = 1;
	int minpt,minptvalue;
	for(i=0; i < number; i++){
		int sum = 0;
		for (int j = 0; j < dim; j++)
		{
			sum += points[i].values[j];
			/* code */
		}
		if (sum < minptvalue || i == 0)
		{
			minptvalue = sum;
			minpt = i;/* code */
		}
	}
	for (int i = 0; i < number; ++i)
	{
		int sum = 0;
		for (int j = 0; j < dim; j++)
		{
			if (points[minpt].values[j] < points[i].values[j])
			{
				sum ++;/* code */
			}
			if(sum==dim)
				hash[i]=0;
			/* code */
		}
	}
	 //initialize

		hash[i] = 1;
	// Start the pthread
	pthread_t threads[thread_number];
  	pthread_attr_t attr;
  	pthread_attr_init(&attr);
  	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    
	//Power House
  	int current_bound = number / thread_number;
    for (i = 0; i < thread_number; i++)
	{	
  		bound[i] = i+1 != thread_number ? current_bound * (i+1) : number; //set Bound
		t[i] = i;
		pthread_create(&threads[current_thread], &attr, checker, &t[i]);
	
    	if((current_thread + 1) == thread_number){
		  	//wait all thread
  			for(j=0; j<thread_number; j++)
	    		pthread_join(threads[j], &status);
	  		current_thread = 0;
		} else {
	  		current_thread++;
		} 
	}

    // pPermissiblePoints -- your computed answer
	for (i = 0; i < number; ++i)
	{
		if(hash[i]){
			permissiblePoints[permissiblePointNum++] = points[i];
		}
	}

	*pPermissiblePoints = realloc(permissiblePoints, sizeof(Point)*permissiblePointNum);
	return permissiblePointNum;
}