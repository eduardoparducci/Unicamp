#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"tree.h"
 /* Desenvolvido por: Eduardo Parducci RA:170272
    Este programa controi uma arvore binaria a partir de duas cadeias de caracteres
		que representam a impressao desta arvore em pré-ordem e em ordem. Gera como saída
		sua impressao em Pós-ordem e sua impressao em largura*/

int main(void){
	node *tree = NULL;
	char pre_order[100];
	char order[100];
	while(scanf("%s %s", pre_order, order)!=EOF){
		//printf("pre>>%s\nin>>%s\n",pre_order,order);
		tree = create(pre_order,order,0,strlen(order)-1,1);
		p_out_order(tree);
		putchar(' ');
		p_tranversal_order(tree,strlen(order)-1);
		putchar('\n');
		destroy(tree);
		tree = NULL;
	}
	return 0;
}
