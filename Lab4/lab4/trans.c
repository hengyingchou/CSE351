/*
CSE 351 Lab 4, Part 2 - Matrix Transposes
Name: Chou, Heng-Ying
ID: hengying@uw.edu
*/

/* 
 * trans.c - Natrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[M][N], int B[N][M]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1 KiB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "support/cachelab.h"

int is_transpose(int M, int N, int A[M][N], int B[N][M]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part I of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[M][N], int B[N][M]) {

    int row, col;
    int i , j;
    int temp = 0, diagonal  = 0;
    int p0, p1, p2, p3, p4;

    if(N == 32){

        for(col = 0 ; col < N ; col += 8){
            for(row = 0 ; row < N ; row += 8){


                for(i = row ; i < row + 8 ; i ++){
                    for(j = col; j < col + 8 ; j++){

                        if(i != j){
                            B[j][i] = A[i][j];

                        }else{
                            temp = A[i][j];
                            diagonal = i;

                        }
                    }
                    if (row == col)	
					{
						B[diagonal][diagonal] = temp;
					}

                }
            }
        }
    }

	if (N == 64)
	{	
		for(row = 0; row < N; row += 4)
		{
			for(col = 0; col < M; col += 4)
			{
				p0 = A[row][col];
				p1 = A[row+1][col];
				p2 = A[row+2][col];
				p3 = A[row+2][col+1];
				p4 = A[row+2][col+2]; 
				B[col+3][row] = A[row][col+3];
				B[col+3][row+1] = A[row+1][col+3];
				B[col+3][row+2] = A[row+2][col+3];
				B[col+2][row] = A[row][col+2];
				B[col+2][row+1] = A[row+1][col+2];
				B[col+2][row+2] =  p4;
				p4 = A[row+1][col+1];
				B[col+1][row] = A[row][col+1];
				B[col+1][row+1] =  p4;
				B[col+1][row+2] = p3;
				B[col][row] = p0;
				B[col][row+1] = p1;
				B[col][row+2] = p2;
				B[col][row+3] = A[row+3][col];
				B[col+1][row+3] = A[row+3][col+1];
				B[col+2][row+3] = A[row+3][col+2];
				p0 = A[row+3][col+3];
				B[col+3][row+3] = p0;
			}
		}
	}

  
}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[M][N], int B[N][M]) {
    int i, j, tmp;

    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions() {
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc);

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc);

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[M][N], int B[N][M]) {
    int i, j;

    for (i = 0; i < M; i++) {
        for (j = 0; j < N; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

