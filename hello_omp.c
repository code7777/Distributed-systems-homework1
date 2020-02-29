/*
Author Preston Porter
Class CS404
Homework 1 

References 
https://www.cs.auckland.ac.nz/references/unix/digital/AQTLTBTE/DOCU_056.HTM
*/


#include <stdio.h>
#include <omp.h>

int main(int argc, char* argv[])
{	
	//initialize variables
	double m =0;
	double n =0;
	double p =0;
	// matrix A = m * p and matrix B = p * n
	// if 3 arguments 
	if(argc == 3){
	m = argv[0];
	p = argv[1];
	n = argv[2];
	}
	// if 2 arguments
	else if(argc == 2){
	n = m = argv[0];
	p = argv[1];
	}
	///if 1 argument
	else if(argc == 1){
	p = n = m = argv[0];
	}
	
	#pragma omp parallel
	double [][] C = new double [ m ][ n ];
	for ( int i = 0; i < m ; i ++) {
		for ( int j = 0; j < n ; j ++) {
			for ( int k = 0; k < p ; k ++) {
				C [ i ][ j ] += A [ i ][ k ] * B [ k ][ j ];
				printf("0.0f\t", C[i][J];
			}
		}
	}
    
    printf("Hello, world.\n");
    return 0;
}

