#include<stdio.h>
#include<stdlib.h>
#include"simetricaa.h"

/* Desenvolvido por:Eduardo Parducci RA:170272
 * Este programa cria uma lista duplamente encadeada e possui funcoes
 * de inserção e reversao de um membro ou trecho da lista atraves da
 * manipulacao de ponteiros*/

int main(void){

	list *Lista;
	char opt=0;
	int a, b;
	double c;

	Lista = create();
	while(opt!='t'){

		scanf(" %c",&opt);
		if(opt=='i'){

			scanf("%d %lf", &a, &c);
			insert(Lista,a,c);
		}
		if(opt=='v'){

			scanf("%d %d", &a, &b);
			revert(Lista,a,b);
		}
		if(opt=='p')
			print(Lista);
	}
	destroy(Lista);
	return 0;
}
