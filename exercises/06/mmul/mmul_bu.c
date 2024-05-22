#include <stdio.h>
#include <stdlib.h>

#define S 512
#define N S
#define M S
#define K S

#define MIN(X,Y) ((X)<(Y)?(X):(Y))
#define MAX(X,Y) ((X)>(Y)?(X):(Y))

#define TYPE double
#define MATRIX TYPE**

#define DEBUG
#ifndef TILE_X
  #define TILE_X 64
#endif /* ifndef TILE_X */
#ifndef TILE_Y
  #define TILE_Y 64
#endif /* ifndef TILE_Y */

// A utility function
MATRIX createMatrix(unsigned x, unsigned y) {
	TYPE* data = malloc(x * y * sizeof(TYPE));

	TYPE** index = malloc(x * sizeof(TYPE*));
	index[0] = data;
	for (unsigned i = 1; i < x; ++i) {
		index[i] = &(data[i*y]);
	}
	return index;
}

void freeMatrix(MATRIX matrix) {
	free(matrix[0]);
	free(matrix);
}


int main(void) {

	// create the matrices
	MATRIX A = createMatrix(N, M);
	MATRIX B = createMatrix(M, K);
	MATRIX C = createMatrix(N, K);

	// ###########################################
	// ######### initialize the matrices #########
	// ###########################################

#ifdef TILE_INIT
  /* Tiling of initialization loops. 
   * i gets tiles of size TILE_X, j of TILE_Y. 
   * If tiles don't fit prefectly MIN() takes care. So last tile in row/col is smaller */

	// A contains real values
  for (int ti=0; ti < N/TILE_X; ti++){
    for (int tj=0; tj < M/TILE_Y; tj++){
      for (int i=TILE_X*ti; i < MIN(TILE_X*(ti+1),N); i++) {
        for (int j=TILE_Y*ti; j < MIN(TILE_Y*(tj+1),M); j++) {
          A[i][j] = i*j;
        }
      }
    }
  }


	// B is the identity matrix
  for (int ti=0; ti < N/TILE_X; ti++){
    for (int tj=0; tj < M/TILE_Y; tj++){
      for (int i=TILE_X*ti; i < MIN(TILE_X*(ti+1),N); i++) {
        for (int j=TILE_Y*ti; j < MIN(TILE_Y*(tj+1),M); j++) {
          B[i][j] = (i==j)?1:0;
        }
      }
		}
	}
  #ifdef DEBUG
    printf("init w/ tiling done");
  #endif /* ifdef DEBUG */
#else
  /* NO tiling of initialization loops */

	// A contains real values
	for (int i=0; i<N; i++) {
		for (int j=0; j<M; j++) {
			A[i][j] = i*j;
		}
	}

	// B is the identity matrix
	for (int i=0; i<M; i++) {
		for (int j=0; j<K; j++) {
			B[i][j] = (i==j)?1:0;
		}
	}
  #ifdef DEBUG
    printf("init w/out tiling done");
  #endif /* ifdef DEBUG */
#endif

	// ###########################################
	// ######### conduct multiplication ##########
	// ###########################################
  
#ifdef TILE_MULT
  /* Tiling of multiplication loop. 
   * i gets tiles of size TILE_X, j of TILE_Y. 
   * If tiles don't fit prefectly MIN() takes care. So last tile in row/col is smaller 
   * I don't tile the innermost loop, as that's not easely possible TODO? */

  for (int ti=0; ti < N; ti += TILE_X){
    for (int tj=0; tj < K; tj += TILE_Y){
      for (int i=ti; i < MIN(TILE_X + ti, N); i++) {
        for (int j=ti; j < MIN(TILE_Y + tj, K); j++) {

          TYPE sum = 0;
          for (int k=0; k<M; k++) {
            sum += A[i][k] * B[k][j];
          }
          C[i][j] = sum;

        }
      }
    }
  }

  #ifdef DEBUG
    printf("mult w/ tiling done");
  #endif /* ifdef DEBUG */
#else
  /* NO tiling of multiplication loop. */

	for (int i=0; i<N; i++) {
		for (int j=0; j<K; j++) {
			TYPE sum = 0;
			for (int k=0; k<M; k++) {
				sum += A[i][k] * B[k][j];
			}
			C[i][j] = sum;
		}
	}

  #ifdef DEBUG
    printf("mult w/out tiling done");
  #endif /* ifdef DEBUG */
#endif

	// verify result
	int success = 1;	
	for (int i=0; i<N; i++) {
		for (int j=0; j<MIN(M,K); j++) {
			if (A[i][j] != C[i][j]) {
				success = 0;
			}
		}
		for (int j=MIN(M,K); j<MAX(M,K); j++) {
			if (C[i][j] != 0) {
				success = 0;
			}
		}
	}

	// print verification result
	printf("Verification: %s\n", (success)?"OK":"ERR");
  #ifdef DEBUG
  /*  */
  if(!success){
    printf("Trying multiplication again without titling\n");
    for (int i=0; i<N; i++) {
      for (int j=0; j<K; j++) {
        TYPE sum = 0;
        for (int k=0; k<M; k++) {
          sum += A[i][k] * B[k][j];
        }
        C[i][j] = sum;
      }
    }
    // verify result
    int success = 1;	
    for (int i=0; i<N; i++) {
      for (int j=0; j<MIN(M,K); j++) {
        if (A[i][j] != C[i][j]) {
          success = 0;
        }
      }
      for (int j=MIN(M,K); j<MAX(M,K); j++) {
        if (C[i][j] != 0) {
          success = 0;
        }
      }
    }

    // print verification result
    printf("Verification (2. time): %s\n", (success)?"OK":"ERR");
  }
  #endif /* ifdef DEBUG */

	freeMatrix(A);
	freeMatrix(B);
	freeMatrix(C);

	return success ? EXIT_SUCCESS : EXIT_FAILURE;
}

