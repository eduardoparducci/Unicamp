/*Desenvolvido por: Eduardo Parducci RA:170272
 *Este programa manipula um conjunto de numeros armazenados em um vetor de bits*/
#include "bits.h"
#include <stdio.h>
#include <stdlib.h>

int main(void){
  char opcao[20];
  int a,b;
  group *S=NULL;
  do{
    scanf(" %s", opcao);
    if(!strcmp(opcao,"create")){
      scanf("%d", &a);
      S=create(S,a);
    }
    if(!strcmp(opcao,"add")){
      scanf("%d", &a);
      add(S,a);
    }
    if(!strcmp(opcao,"remove")){
      scanf("%d", &a);
      rem(S,a);
    }
    if(!strcmp(opcao,"in")){
      scanf("%d", &a);
      in(S,a);
    }
    if(!strcmp(opcao,"rank")){
      scanf("%d", &a);
      rank(S,a);
    }
    if(!strcmp(opcao,"select")){
      scanf("%d", &a);
      find(S,a);
    }
    if(!strcmp(opcao,"rangecount")){
      scanf("%d %d", &a,&b);
      range_count(S,a,b);
    }
    if(!strcmp(opcao,"print")){
      print(S);
    }
  }while(strcmp(opcao,"exit"));
  S=finish(S);
  return 0;
}
