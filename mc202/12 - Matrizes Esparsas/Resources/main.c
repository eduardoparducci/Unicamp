#include"esparsas.h"
#include<stdio.h>
#include<stdlib.h>

int main(void){

  int n_nulos, i, qt_lin=0, qt_col=0;
  int *A, *B, *C;
  esp *aux;
  scanf("%d", &n_nulos);
  aux = malloc(n_nulos * sizeof(int));

  /*Recebe dados da matriz*/
  for(i=0 ; i<n_nulos ; i++){
    scanf("%d %d %d", &aux[i].i, &aux[i].j, &aux[i].data);
    if(aux[i].i > qt_lin) qt_lin = aux[i].i;
    if(aux[i].j > qt_col) qt_col = aux[i].j;
  }

  A = quick_sort(A,0,qt_lin,l);
  A = quick_sort(A,)
  
  do{
    scanf("%d %d", &lin, &col);

  }while(lin!=-1 && col!=-1);
  
  /*Exibe vetor A*/
  for(i=0 ; i<n_nulos ; i++)
    printf("%d %d %dzn", A[i].i, A[i].j, A[i].dado);
  return 0;
}
