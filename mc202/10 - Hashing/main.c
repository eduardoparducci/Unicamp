/*Desenvolvido por: Eduardo Parducci RA:170272*/
#include<stdio.h>
#include<stdlib.h>
#include"hashing.h"
#ifndef MAX
#define MAX 5023
#endif

int main(void){

	int valor,i;
	unsigned int ch;
	celula **tabela = malloc(MAX * sizeof(celula));
	char opcao;
	do{
		scanf(" %c", &opcao);

		if(opcao=='i'){
			scanf("%u %d", &ch, &valor);
			insere(ch, valor, tabela);
		}
		if(opcao=='b'){
			scanf("%u", &ch);
			celula *p = busca(ch,tabela);
			if(p) printf("valor para %u: %d\n", p->chave, p->valor);
			else printf("%u nao existe\n", ch);
		}
		if(opcao=='r'){
			scanf("%u", &ch);
			remover(ch,tabela);
		}
	}while(opcao!='f');
	/*for(i=0 ; i<MAX ; i++)
		while(tabela[i]){
			celula *p = tabela[i];
			tabela[i] = p->prox;
			free(p);
		}*/
	free(tabela);
	return 0;
}
