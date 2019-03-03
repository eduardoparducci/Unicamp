#include"esparsas.h"
#include<stdio.h>
#include<stdlib.h>

int main(void){

  esp *A;
  int i,qt_elem,lin,col;

  scanf("%d", &qt_elem);

  A = malloc(qt_elem * sizeof(esp));
  
  for(i=0 ; i<qt_elem ; i++){
    scanf("%d %d %d", &A[i].i, &A[i].j, &A[i].dado);
  }

  conta_elem(A,qt_elem);
  /*
  printf("---organiza---\n");
  
  for(i=0 ; i<qt_elem ; i++){
    printf("%d %d %d\n", A[i].i, A[i].j, A[i].dado);
  }
  */
  /*busca elementos*/
  do{
    
    scanf("%d %d", &lin, &col);
    if(lin!=-1) printf("(%d,%d) = %d\n",lin,col,busca(A,qt_elem,lin,col));
    
  }while(lin!=-1);
  
  free(A);
  return 0;
}
