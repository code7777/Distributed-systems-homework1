/*
Author Preston Porter
Class CS404
Homework 1 

References 
https://www.cs.auckland.ac.nz/references/unix/digital/AQTLTBTE/DOCU_056.HTM
https://www.tutorialspoint.com/c_standard_library/c_function_strtod.htm
https://www.tutorialspoint.com/cprogramming/c_multi_dimensional_arrays.htm
http://www.cplusplus.com/reference/clibrary/
https://www.programiz.com/c-programming/c-file-input-output
https://www.geeksforgeeks.org/rand-and-srand-in-ccpp/
https://www.techiedelight.com/find-execution-time-c-program/
https://people.sc.fsu.edu/~jburkardt/c_src/hello_openmp/hello_openmp.c
https://people.sc.fsu.edu/~jburkardt/c_src/hello_openmp/hello_openmp.html
http://pages.tacc.utexas.edu/~eijkhout/pcse/html/omp-loop.html
https://computing.llnl.gov/tutorials/openMP/
*/


#include <stdio.h> //file I/O
#include <stdlib.h>
#include <omp.h>
#include<sys/time.h> //srand drand

int main(int argc, char* argv[])
{	
	/* structure timeval defined in header file uses wall clock time to determine 
	   start and end times of parallelized and serialized matrix multiplication */
	struct timeval start, end;

	
	//printf("argc is %d \n", argc);
	//3 pointers 
	char *ptr1;
	char *ptr2;
	char *ptr3;

	//initialize variables

	int m =0;
	int n =0;
	int p =0;
	// matrix A = m * p and matrix B = p * n
	// if 3 arguments 
	/*m = argv[0];
	p = argv[1];
	n = argv[2];*/

	if(argc == 4){
	printf("3 args after hw1\n");
	
	m = atoi(argv[1]);
        
	p = atoi(argv[2]);
	ptr3 = argv[3];
	n = atoi(argv[3]);
	}
	// if 2 arguments
	/*n = m = argv[0];
	p = argv[1];*/

	else if(argc == 3){
	printf("2 args after hw1\n");
        ptr1 = argv[1];
	m =  n = atoi(argv[1]);
        ptr2 = argv[2];
	p = atoi(argv[2]);
	}

	///if 1 argument
	else if(argc == 2){
	printf("1 args after hw1\n");
	ptr1 = argv[1];
	p = n = m = atoi(argv[1]);
	} 
	
	printf("p is %d ", p );
	printf("n is %d ", n);
	printf("m is %d ", m);
 	printf("\n");
	printf("\n");
	printf("\n");

	
	double  C [ m ][ n ];
	double A [ m ][ p ];
	double  B [ p ][ n ];
	/*initialize matrices using A and B matrices using random numbers*/
	srand(time(0));
	for ( int i = 0; i < m ; i ++) {
	
			for ( int j = 0; j < n ; j ++) {
				for ( int k = 0; k < p ; k ++) {
				A [ i ][ k ] = rand();
				B [ k ][ j ] = rand();
				}
			}
	}
	
	FILE *fptr ;
	fptr = fopen("output.txt","w");
	printf("parallel job commencing\n");
	fprintf(fptr,"parallel job commencing\n");
	gettimeofday(&start, NULL);

	/* in parallel multiply matrices and put result in C matrix  */
	#pragma omp parallel
	{
	
		#pragma omp parallel for lastprivate(C) collapse(3)
		for ( int i = 0; i < m ; i ++) {
	
			for ( int j = 0; j < n ; j ++) {
	
				for ( int k = 0; k < p ; k ++) {
					
					#pragma omp critical
					C [ i ][ j ] += A [ i ][ k ] * B [ k ][ j ];
					
				}
				
			
			}
			
		}
	}
	/*print C matrix to output.txt */
   	for ( int i = 0; i < m ; i ++) {
	
			for ( int j = 0; j < n ; j ++) {
				//printf("%0.0f\t", C[i][j]);
				fprintf(fptr,"%0.0f\t",C[i][j]);
			}
		//printf("\n");
		fprintf(fptr,"\n");
	}
		
	printf("\n");
	fprintf(fptr,"\n");
	

    gettimeofday(&end, NULL);
	long seconds1 = (end.tv_sec - start.tv_sec);
	long micros1 = ((seconds1 * 1000000) + end.tv_usec) - (start.tv_usec);
	

	printf("Time elpased for parallel is %d seconds and %d microseconds\n", seconds1, micros1);
    	/*used to 0 out the matrices */
	for ( int i = 0; i < m ; i ++) {
	
			for ( int j = 0; j < n ; j ++) {
				C[i][j] =0;
				
				/*printf("%0.0f\t", C[i][j]);
				fprintf(fptr,"%0.0f\t",C[i][j]);*/
			}
		//printf("\n");
		fprintf(fptr,"\n");
	}
	
	

	printf("serial job commencing\n");
	fprintf(fptr,"serial job commencing\n");
	printf("\n");
	gettimeofday(&start, NULL);
	
	/* in serial multiply matrices and put result in C matrix  */
	{
		for ( int i = 0; i < m ; i ++) {
	
			for ( int j = 0; j < n ; j ++) {
	
				for ( int k = 0; k < p ; k ++) {
					
					C [ i ][ j ] += A [ i ][ k ] * B [ k ][ j ];
				
				}
			
			
			}
			
		}
	}
	for ( int i = 0; i < m ; i ++) {
	
			for ( int j = 0; j < n ; j ++) {
				//printf("%0.0f\t", C[i][j]);
				fprintf(fptr,"%0.0f\t",C[i][j]);
			}
		//printf("\n");
		fprintf(fptr,"\n");
	}
    fclose(fptr);
    gettimeofday(&end, NULL);
	long seconds2 = (end.tv_sec - start.tv_sec);
	long micros2 = ((seconds2 * 1000000) + end.tv_usec) - (start.tv_usec);

	printf("Time elpased for serial is %d seconds and %d microseconds\n", seconds2, micros2);
	
	long speedUpSeconds = seconds2 - seconds1;
	long speedUpMicros = micros2 -micros1;
	
	printf("\n");
	printf("The speed-up time using OpenMP is %d seconds and %d microseconds\n", speedUpSeconds, speedUpMicros);
	
    return 0;
}

