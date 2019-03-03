#include"hashing.h"
#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#ifndef MAX
#define MAX 5023
#endif

unsigned int hash(unsigned int ch){ return ch % MAX; }

void insere(unsigned int ch, int valor, celula **tabela){

	unsigned int h = hash(ch);
	celula *p = tabela[h];

   	while (p && p->chave!=ch) p = p->prox;

   	if (!p){
		p = malloc (sizeof (celula));
		p->chave = ch;
		p->prox = tabela[h];
		tabela[h] = p;
   	}
	p->valor = valor;

}

celula *busca(unsigned int ch, celula **tabela){

	unsigned int h = hash(ch);
	celula *p = tabela[h];
	while(p && p->chave!=ch) p = p->prox;
	if(!p) return NULL;
	return p;

}

int remover(unsigned int ch, celula **tabela){

	unsigned int h = hash(ch);
	celula *p = tabela[h];
	if(p && p->chave == ch){
		tabela[h] = p->prox;
		free(p);
		return 1;
	}
	celula *ant;
	while(p && p->chave!=ch){
		ant = p;
		p = p->prox;
	}
	if(!p) return 0;
	ant = p->prox;
	free(p);
	return 1;
}
