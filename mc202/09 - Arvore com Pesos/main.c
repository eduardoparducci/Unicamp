/*Desenvolvido por: Eduardo Parducci RA:170272
 *Este programa tem como objetivo construir uma arvore com pesos a partir de uma string
 *dada como entrada, no formato (L[peso:]T[:peso]R) onde T é o valor do nó L o filho
 *da esquerda e R a sub-arvore direita, calcula o maior valor do caminho da raiz até
 *a folha da arvore */

#include <stdio.h>
#include <stdlib.h>
#include "pesos.h"

int main(void){

	while(getchar()!=EOF){
		node *tree = build();
		printf("%.3f\n", summ(tree));
		destroy(tree);
		getchar();
	}
  return 0;
}
