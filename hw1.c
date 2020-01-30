/*
Author Preston Porter
Class CS404
Homework 1 

References 
https://www.cs.auckland.ac.nz/references/unix/digital/AQTLTBTE/DOCU_056.HTM
https://www.tutorialspoint.com/c_standard_library/c_function_strtod.htm
https://www.tutorialspoint.com/cprogramming/c_multi_dimensional_arrays.htm
*/


#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char* argv[])
{	
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
	if(argc == 3){
	
	//ptr1 = argv[1];
	m = atoi(argv[1]);
        //ptr2 = argv[2];
	p = atoi(argv[2]);
	ptr3 = argv[3];
	n = atoi(argv[3]);
	}
	// if 2 arguments
	/*n = m = argv[0];
	p = argv[1];*/

	else if(argc == 2){
	
        ptr1 = argv[1];
	m =  n = atoi(argv[1]);
        ptr2 = argv[2];
	p = atoi(argv[2]);
	}
	///if 1 argument
	else if(argc == 1){
	ptr1 = argv[1];
	p = n = m = atoi(argv[1]);
	} 

	printf("p is %d ", p );
	printf("n is %d ", n);
	printf("m is %d ", m);
	//#pragma omp parallel
	double  C [ m ][ n ];
	double A [ m ][ p ];
	double  B [ p ][ n ];
	for ( int i = 0; i < m ; i ++) {
		for ( int j = 0; j < n ; j ++) {
			for ( int k = 0; k < p ; k ++) {
				A [ i ][ k ] =1.5;
				B [ k ][ j ] =1.5;
				C [ i ][ j ] += A [ i ][ k ] * B [ k ][ j ];
				printf("0.0f\t", C[i][j]);
			}
		}
	}
    
    //printf("Hello, world.\n");
    return 0;
}

