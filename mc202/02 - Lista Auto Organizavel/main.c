#include<stdio.h>
#include<stdlib.h>

/*
	Lista Auto-organizável - Desenvolvido por:Eduardo Parducci RA:170272
	Este programa manipula os dados de uma lista encadeada de forma a calcular a quantidade de acessos necessarios para encontrar um membro
	da lista utilizando as estrategias de organizacao: move-to-front, transpose e count.
*/

typedef struct nos{
	int dado;
	int acessos;
	struct nos *prox;
} no;

typedef struct listas{
	no *cabeca;
	no *atual;
	int custo;
} lista;

void busca(lista *,int);
void mtf(lista *,int);
void tr(lista *,int);
void count(lista *,int);

int main(void){
	int qt_elem,qt_acessos,i;
	int *acessos;
	lista *lista_n=NULL;

	scanf("%d %d", &qt_elem,&qt_acessos);

	/*---cria-lista---*/
	lista_n=(lista *)malloc(sizeof(lista));
	lista_n->cabeca=NULL;
	lista_n->atual=NULL;

	/*---insere-elementos---*/
	for(i=1;i<=qt_elem;i++){
		no *aux=(no *)malloc(sizeof(no));
		aux->dado=i;
		aux->prox=NULL;
		if(!lista_n->cabeca){
			lista_n->cabeca=aux;
			lista_n->atual=aux;
		}else{
			lista_n->atual->prox=aux;
			lista_n->atual=lista_n->atual->prox;
		}
	}

	/*---aloca-acessos---*/
	acessos=(int *)calloc(qt_acessos,sizeof(int));

	/*---recebe-acessos---*/
	for(i=0;i<qt_acessos;i++){
		scanf("%d",&acessos[i]);
	}

	/*---move-to-front---*/
	lista_n->custo=0;
	for(i=0;i<qt_acessos;i++){
		busca(lista_n, acessos[i]);
		mtf(lista_n, acessos[i]);
	}
	printf("%d ",lista_n->custo);

	/*---retorna-lista-no-valor-original---*/
	lista_n->atual=lista_n->cabeca;
	for(i=1;i<=qt_elem;i++){
		lista_n->atual->dado=i;
		if(i<qt_elem)
			lista_n->atual=lista_n->atual->prox;
	}
	lista_n->atual->prox=NULL;

	/*---transpose---*/
	lista_n->custo=0;
	for(i=0;i<qt_acessos;i++){
		busca(lista_n, acessos[i]);
		tr(lista_n, acessos[i]);
	}
	printf("%d ",lista_n->custo);

	/*---retorna-lista-no-valor-original---*/
	lista_n->atual=lista_n->cabeca;
	for(i=1;i<=qt_elem;i++){
		lista_n->atual->dado=i;
		lista_n->atual->acessos=0;
		if(i<qt_elem)
			lista_n->atual=lista_n->atual->prox;
	}
	lista_n->atual->prox=NULL;

	/*---count---*/
	lista_n->custo=0;
	for(i=0;i<qt_acessos;i++){
		busca(lista_n, acessos[i]);
		count(lista_n, acessos[i]);
	}
	printf("%d\n",lista_n->custo);
	
	return 0;
}

void busca(lista *lista_n,int no_buscado){
	
	no *aux=lista_n->cabeca;
	
	while(aux){
		lista_n->custo++;
		if(no_buscado==aux->dado){
			lista_n->atual=aux; //atual recebe o no buscado
			break;
		}
		else
			aux=aux->prox;
	}
	return;
}

void mtf(lista *lista_n,int no_permuta){
	no *anterior=lista_n->cabeca;
	
	if(lista_n->cabeca->dado==no_permuta)	
		return;
	else{
		while(anterior){
			if(no_permuta==anterior->prox->dado) //encontrou o no anterior
				break;
			else
				anterior=anterior->prox;
		}
		lista_n->atual=lista_n->cabeca; //salva o inicio da lista em lista_n->atual
		lista_n->cabeca=anterior->prox; //cabeca recebe o novo no
		anterior->prox=lista_n->cabeca->prox; //anterior->prox aponta para cabeca->prox
		lista_n->cabeca->prox=lista_n->atual; //cabeca->prox aponta para a antiga cabeca da lista
	}
}

void tr(lista *lista_n, int no_permuta){
	no *aux=lista_n->cabeca;
	no *anterior=NULL;

	if(lista_n->cabeca->dado==no_permuta)	
		return;
	else{
		if(aux->prox->dado==no_permuta){
			lista_n->cabeca=aux->prox;
			anterior=aux;
		}
		else{
			while(aux){
				if(no_permuta==aux->prox->prox->dado) //encontrou o 2º no antecedente ao procurado
					break;
				else{
					aux=aux->prox;
				}
			}
			anterior=aux->prox;
			aux->prox=lista_n->atual;
		}		
		anterior->prox=lista_n->atual->prox;
		lista_n->atual->prox=anterior;
	}
}

void count(lista *lista_n,int no_permuta){
	no *aux, *anterior, *anterior_1;
	int maior, tmp;

	anterior_1=NULL;
	anterior=lista_n->cabeca; //primeiro no da lista
	lista_n->atual=lista_n->cabeca; //primeiro no da lista
	maior=lista_n->cabeca->acessos; //quantidade de acessos do primeiro no

	if(lista_n->cabeca->dado==no_permuta){
		lista_n->cabeca->acessos++;	
		return;
	}
	else{
		while(anterior){
			aux=anterior->prox;
			if(no_permuta==aux->dado){ //encontrou o no procurado, salvo em aux
				aux->acessos++;
				while(lista_n->atual){
					if(lista_n->atual->acessos <= aux->acessos){ //troca as posicoes de aux e lista_n->atual
						anterior->prox=aux->prox;
						aux->prox=lista_n->atual;
						if(!anterior_1)
							lista_n->cabeca=aux;
						else
							anterior_1->prox=aux;
						break;
					}
					else{
						anterior_1=lista_n->atual;
						lista_n->atual=lista_n->atual->prox;
					}
				}
				break;
			}
			else
				anterior=anterior->prox;
		}
	}
}

/*
//---exibe-lista---
	no *aux=lista_n->cabeca;
	while(aux){
		printf("%d->", aux->dado);
		aux=aux->prox;		
	}
//---imprime-lisca-acessos---
	for(i=0;i<qt_acessos;i++){
		printf(" %d",acessos[i]);
	}
*/
