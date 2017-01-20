/*
Shiqi Wang
UID: 304582601 
*/

#include "func.h"
#include "util.h"

void func0(double *weights, double *arrayX, double *arrayY, int xr, int yr, int n)
{
	int i;
	double dn = (double)n;

#pragma omp parallel for num_threads(20) firstprivate(arrayX, arrayY, weights, xr, yr, n, dn) private(i)
	for(i = 0; i < n; i++){
		weights[i] = 1/dn;
		arrayX[i] = xr;
		arrayY[i] = yr;
	}
}

void func1(int *seed, int *array, double *arrayX, double *arrayY,
			double *probability, double *objxy, int *index,
			int Ones, int iter, int X, int Y, int Z, int n)
{
	int i, j;
   	int index_X, index_Y;
	int max_size = X*Y*Z;
    
	int arr, arrindex;
	double prob;
	double one = (double) Ones;
    
#pragma omp parallel for num_threads(20) firstprivate (arrayX, arrayY, n, seed) private(i)
   	for(i = 0; i < n; i++){
	  arrayX[i] += 1 + 5*rand2(seed, i);
	  arrayY[i] += -2 + 2*rand2(seed, i);
   	}

#pragma omp parallel for num_threads(20) firstprivate(arrayX,arrayY,array,probability,objxy,index,Ones,one,iter, Y, Z, n, max_size) private(i, j, index_X, index_Y, arr, arrindex) reduction(+:prob)
   	for(i = 0; i<n; i++){
	  for(j = 0; j < Ones; j++){
	    index_X = round(arrayX[i]) + objxy[j*2 + 1];
   	    index_Y = round(arrayY[i]) + objxy[j*2];
	    arrindex = i*Ones + j;
   	    index[arrindex] = fabs(index_X*Y*Z + index_Y*Z + iter);
   	    if(index[arrindex] >= max_size)
	      index[arrindex] = 0;
   	    }
	    prob  = 0;
   	    for(j = 0; j < Ones; j++) {
	      arr = array[index[i*Ones + j]];
	      prob += (pow((arr - 100),2) - pow((arr - 228),2))/50.0;
   	    }
   	    probability[i] = prob/one;
   	}
}

void func2(double *weights, double *probability, int n)
{
	int i;
	double sumWeights=0;
	double wgt;
	
#pragma omp parallel for num_threads(20) firstprivate(weights, probability, n) private(i) reduction(+:sumWeights)
	for(i = 0; i < n; i++){
	  weights[i] *= exp(probability[i]);
	  sumWeights += weights[i];
	}

#pragma omp parallel for num_threads(20) firstprivate(weights, sumWeights, n) private (i)
 	for(i = 0; i < n; i++)
   	   weights[i] = weights[i]/sumWeights;
}

void func3(double *arrayX, double *arrayY, double *weights, double *x_e, double *y_e, int n)
{
	double estimate_x=0.0;
	double estimate_y=0.0;
	int i;

#pragma omp parallel for num_threads(20) firstprivate(arrayX, arrayY, weights, n) private(i) reduction(+:estimate_x, estimate_y)
	for(i = 0; i < n; i++){
	  estimate_x += arrayX[i] * weights[i];
   	  estimate_y += arrayY[i] * weights[i];
   	}

	*x_e = estimate_x;
	*y_e = estimate_y;

}

void func4(double *u, double u1, int n)
{
	int i;
	double dn = (double)n;

#pragma omp parallel for num_threads(20) firstprivate(u, u1, n, dn) private(i)
	for(i = 0; i < n; i++){
   		u[i] = u1 + i/dn;
   	}
}

void func5(double *x_j, double *y_j, double *arrayX, double *arrayY, double *weights, double *cfd, double *u, int n)
{
	int i, j;
	double dn = (double)n;

#pragma omp parallel for num_threads(20) firstprivate(x_j, y_j, arrayX, arrayY, u, n) private(i, j)
	for(j = 0; j < n; j++){
   		//i = findIndex(cfd, n, u[j]);
   		i = findIndexBin(cfd, 0, n, u[j]);
   		if(i == -1)
   			i = n-1;
   		x_j[j] = arrayX[i];
   		y_j[j] = arrayY[i];
   	}

#pragma omp parallel for num_threads(20) firstprivate(x_j, y_j, arrayX, arrayY, n, dn, weights) private(i)
	for(i = 0; i < n; i++){
		arrayX[i] = x_j[i];
		arrayY[i] = y_j[i];
		weights[i] = 1/dn;
	}
}
