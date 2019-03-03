#include<stdio.h>
#include<stdlib.h>
#include"simetricaa.h"

list *create(void){

	list *new_list = (list *) malloc(sizeof(list));

	if(!new_list) return NULL;

	new_list->tail = NULL;
	new_list->head = new_list->tail;
	new_list->size = 0;
	//printf("\nCriou!\n");
	return new_list;

}

void destroy(list *L){

	node *p = L->head;
	int i;
		for(i=0;i< L->size;i++){

			node *aux = p;
			if(p->a) p = p->a;
			else p = p->b;
			free(aux);

		}

	free(L);
        //printf("\nDestruiu!\n");

}

int insert(list *L, int pos, double value){

	node *n_node = (node *)malloc(sizeof(node));
	node *p = L->head;
	node *prev = NULL; /*preview: anterior à node *p */
	int i;

	if(!n_node) return 0;
	L->size++;
	n_node->data = value;
	n_node->a = NULL;
	n_node->b = NULL;

	/*primeiro elemento*/
	if(!L->head){
		L->head = n_node;
		L->tail = n_node;
		return L->size;
	}
	/*procura posicao*/
	for(i=0;i<pos;i++){

		if(!p) break;
		else if(p->a==prev){
			prev = p;
			p = p->b;/*avanca em b*/
		}
		else{
			prev = p;
			p = p->a;/*avanca em a*/
		}

	}
	/*inclui n_node antes de p*/
        if(p==L->head){ /*inicio da lista*/

		L->head->a = n_node;
                n_node->b = L->head;
                L->head = n_node;

        }
	else if(!p){ /*fim da lista*/

		n_node->a = L->tail;
		L->tail->b = n_node;
		L->tail = n_node;

	}
	else { /*meio da lista*/

		if(p->a==prev){ /*a é anterior*/
			n_node->a = p->a;
			p->a = n_node;
		}
		else{ /*b é anterior*/
			n_node->a = p->b;
			p->b = n_node;
		}
		/*verifica o proximo de prev*/
		if(prev->a==p) prev->a = n_node;
		else prev->b = n_node;
		n_node->b = p;
	}

	return L->size;

}

void print(list *L){

	node *p = L->head;
	node *prev = NULL;
	while(p){
		printf("%.4lf ", p->data);
		if(p->a==prev){
			prev = p;
			p = p->b;
		}
		else{
			prev = p;
			p = p->a;
		}
	}
	putchar('\n');
}

void revert(list *L, int begin, int end){

	node *b = L->head; /*begin*/
	node *e = L->tail; /*end*/
	node *prevB=NULL;
	node *nextE=NULL;
	int posB=0,posE=L->size-1; /*posicoes de inicio e fim*/

	/*procura as posicoes da reversao*/
	while(posB!=begin || posE>end){
		if(posB<begin){
			if(b->a==prevB){ /*avanca em b*/
				prevB = b;
				b = b->b;
			}
			else{ /*avanca em a*/
				prevB = b;
				b = b->a;
			}
			posB++;
		}

		if(posE>end){
			if(e->a==nextE){ /*retrocede em b*/
				nextE = e;
				e = e->b;
			}
			else{
				nextE = e;
				e = e->a;
			}
			posE--;
		}
	}

	/*reverte o trecho da lista*/
	if(b==L->head && e==L->tail){
		L->head = e;
		L->tail = b;
		b->a = b->b;
		e->b = e->a;
		b->b = NULL;
		e->a = NULL;
		return;

	}
	if(b->a==prevB){
		if(e->a==nextE){
			b->a = nextE;
			e->a = prevB;
		}
		else{
			nextE = e->b;
			b->a = nextE;
			e->b = prevB;
		}
	}
	else{
		prevB = b->b;
		if(e->a==nextE){
			b->b = nextE;
			e->a = prevB;
		}
		else{
			nextE = e->b;
			b->b = nextE;
			e->b = prevB;
		}
	}
	if(prevB && prevB->a==b) prevB->a = e;
	else if(prevB) prevB->b = e;

	if(nextE && nextE->a==e) nextE->a = b;
	else if(nextE) nextE->b = b;

}
