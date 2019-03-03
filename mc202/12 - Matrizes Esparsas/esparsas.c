#include"esparsas.h"
#include<stdio.h>

void conta_elem(esp *A, int tam){

  int inicio=0, fim=0;
  int dado = A[0].i;
  
  organiza_linha(A,0,tam-1);

  while(fim < tam){
    if(A[++fim].i != dado){
      organiza_coluna(A,inicio,fim-1);
      dado = A[fim].i;
      inicio = fim;
    }
  }
  
}

void organiza_linha(esp *A, int min, int max){
  
  int inf = min;
  int sup = max;
  int pivo = A[(min+max)/2].i;
  
  while(inf <= sup){

    while(A[inf].i < pivo && inf < max) inf++;
    while(A[sup].i > pivo && sup > min) sup--;

    if(inf <= sup){
      permuta(A,inf,sup);
      inf++;
      sup--;
    }
  }
  if(sup > min) organiza_linha(A,min,sup);
  if(inf < max) organiza_linha(A,inf,max);  
}

void organiza_coluna(esp *A, int min, int max){
  
  int inf = min;
  int sup = max;
  int pivo = A[(min+max)/2].j;
  
  while(inf <= sup){

    while(A[inf].j < pivo && inf < max) inf++;
    while(A[sup].j > pivo && sup > min) sup--;

    if(inf <= sup){
      permuta(A,inf,sup);
      inf++;
      sup--;
    }
  }
  if(sup > min) organiza_coluna(A,min,sup);
  if(inf < max) organiza_coluna(A,inf,max);  
}

void permuta(esp *A, int pos1, int pos2){

  esp aux;
  
  aux.i     = A[pos1].i;
  aux.j     = A[pos1].j;
  aux.dado  = A[pos1].dado;
  
  A[pos1].i    = A[pos2].i;
  A[pos1].j    = A[pos2].j;
  A[pos1].dado = A[pos2].dado;
  
  A[pos2].i    = aux.i;
  A[pos2].j    = aux.j;
  A[pos2].dado = aux.dado;
}

int busca(esp *A, int tam, int lin, int col){

  int i=0;
  
  while(A[i].i<lin && i<tam) i++;
  while(A[i].j<col && i<tam) i++;
  
  if(A[i].i==lin && A[i].j==col) return A[i].dado;
  
  return 0;
}
