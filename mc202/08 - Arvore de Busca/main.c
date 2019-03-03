/* Desenvolvido por: Eduardo Parducci RA:170272
 * Este programa tem como objetivo manipular uma arvore de busca atraves das funcoes de insercao,
 * exclusao, busca, encontrar os valores minimos e maximos da arvore, imprimi-la utilizando as regras de
 * pre, pos, ordem e largura e destruição da arvore.*/
#include<stdio.h>
#include<string.h>
#include"search_tree.h"

int main(void){
  char op[20];
  int key;
  node *tree = NULL;
  do{
    scanf(" %s", op);
    if(!strcmp(op,"inserir")){
      scanf("%d", &key);
      tree = insert(key,tree);
      //printf("tree>>%p\n", tree);
    }
    if(!strcmp(op,"excluir")){
      scanf("%d", &key);
      tree = remove_node(tree,search(tree,key));
    }
    if(!strcmp(op,"buscar")){
      scanf("%d", &key);
      if(search(tree,key)) printf("pertence\n");
      else printf("nao pertence\n");
    }
    if(!strcmp(op,"minimo")){
      if(!smallest(tree)) printf("vazia\n");
    }
    if(!strcmp(op,"maximo")){
      if(!biggest(tree)) printf("vazia\n");
    }
    if(!strcmp(op,"pos-ordem")){
      if(!tree) printf("vazia");
      else p_out_order(tree);
      putchar('\n');
    }
    if(!strcmp(op,"em-ordem")){
      if(!tree) printf("vazia");
      else p_in_order(tree);
      putchar('\n');
    }
    if(!strcmp(op,"pre-ordem")){
      if(!tree) printf("vazia");
      else p_pre_order(tree);
      putchar('\n');
    }
    if(!strcmp(op,"largura")){
      if(!tree) printf("vazia");
      else p_tranversal_order(tree,count_nodes(tree));
      putchar('\n');
    }
    if(!strcmp(op,"terminar")){
      destroy(tree);
    }
  }while(strcmp(op,"terminar"));
  return 0;
}
