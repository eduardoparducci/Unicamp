#include<stdio.h>
#include<stdlib.h>

typedef struct vert{
  int val;
  struct vert *prox;
}vert;

typedef struct{
  int tam;
  vert *V;
}graf;


int main(void){

  graf G;
  int i;
  
  scanf("%d", &G.tam);

  G.V = malloc(tam * sizeof(vert));
  return 0;
}
