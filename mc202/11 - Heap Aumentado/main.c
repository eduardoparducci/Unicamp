#include <stdio.h>
#include <stdlib.h>
#include "teste.h"
/*documentacao no header "teste.h"*/

int main(void){

  int custo, valor, tamanho=0, maximo, *existe;
  elem *heap;
  char op;
  
  //printf("Maximo:");
  scanf(" %d", &maximo);
  heap = malloc(maximo * sizeof(elem));
  existe = inicia_vetor(existe,maximo);
  
  do{

    scanf(" %c", &op);

    if(op=='i'){
      //printf("Adiciona:");
      scanf(" %d %d", &valor, &custo);
      tamanho = inserir(heap, existe, custo, valor, tamanho);
    }

    else if(op=='m'){
      //printf("Remove minimo\n");
      exibe(heap, tamanho);
      tamanho = remove_min(heap, existe, tamanho);
    }
    
    else if(op=='d'){
      //printf("Valores: ");
      scanf(" %d %d", &valor, &custo);
      atualiza_custo(heap, existe, valor, custo, tamanho);
    }
    
  }while(op!='t');

  //printf("Termina\n");
  free(heap);
  free(existe);
  
  return 0;
}
