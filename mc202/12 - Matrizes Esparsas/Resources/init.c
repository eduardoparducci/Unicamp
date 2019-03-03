#include<stdlib.h>
#include<stdio.h>
#define DIM 10

int main(void){

  int i, j, qt, lin, col,valor;
  int M[DIM][DIM];

  for(i=0 ; i<DIM ; i++){
    for(j=0 ; j<DIM ; j++){
      M[i][j] = 0;
    }
  }
  
  scanf("%d", &qt);
  for(i=0 ; i<qt ; i++){
    scanf("%d %d %d", &lin, &col, &valor);
    M[lin][col] = valor;
  }
  
  for(i=0 ; i<DIM ; i++){
    for(j=0 ; j<DIM ; j++){
      printf(" %d ",M[i][j]);
    }
    putchar('\n');
  }

  int *A = malloc(qt * sizeof(int));
  int *B = malloc(qt * sizeof(int));
  int *C = malloc((DIM+1) * sizeof(int));
  int k=0;
  for(i=0 ; i<DIM ; i++){
    C[i] = k;
    for(j=0 ; j<DIM ; j++){
      if(M[i][j]){
	A[k] = M[i][j];
	B[k] = j;
	k++;
      }
    }
  }

  printf("\nA={");
  for(i=0 ; i<qt ; i++){
    printf(" %d |",A[i]); 
  }
  printf("}\nB={");
  for(i=0 ; i<qt ; i++){
    printf(" %d |",B[i]); 
  }
  printf("}\nC={");
  for(i=0 ; i<=DIM ; i++){
    printf(" %d |",C[i]); 
  }
  return 0;
}
