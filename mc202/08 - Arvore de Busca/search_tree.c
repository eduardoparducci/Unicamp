#include <stdio.h>
#include <stdlib.h>
#include "search_tree.h"

node *insert(int key, node *tree){
  /*verifica se o no ja exixte*/
  if(search(tree,key)) return tree;
  /*aloca o no*/
  node *new_node = (node *)malloc(sizeof(node));
  /*verifica se a alocacao foi bem sucedida*/
  if(!new_node){
    printf("memoria insuficiente\n");
    return tree;
  }
  /*insere dados no nó*/
  new_node->data = key;
  new_node->left = NULL;
  new_node->right = NULL;
  /*percorre a arvore até encontrar a posicao do novo no*/
  if(!tree) return new_node;
  node *root=tree;
  while(root){
    if(root->data > key){
      if(!root->left){
        root->left = new_node;
        break;
      }
      else root = root->left;
    }
    if(root->data < key){
      if(!root->right){
        root->right = new_node;
        break;
      }
      else root = root->right;
    }
    if(root->data == key) break;
  }
  return tree;
}

node *remove_node(node *tree, node *old){
  if(!old) return NULL;
  /*verifica se old é raiz de tree*/
  if(tree->data==old->data){
    node *aux, *aux1;
    if(!old->right){
      aux1 = old->left;
      free(old);
      return aux1;
    }
    /*procura sucessor de old e o pai do sucessor*/
    aux  = old;
    aux1 = old->right;
    while (aux1->left){
       aux  = aux1;
       aux1 = aux1->left;
    }
    /*reorganiza arvore eliminando old*/
    if (aux  != old){
       aux->left = aux1->right;
       aux1->right = old->right;
    }
    aux1->left = old->left;
    free (old);
    return aux1;
  }
  if(tree->data > old->data) tree->right = remove_node(tree->right,old);
  else tree->left = remove_node(tree->left,old);
  return tree;
}

node *biggest(node *tree){
  node *aux = tree;
  if(aux)
    while(aux->right) aux = aux->right;
  return aux;
}

node *smallest(node *tree){
  node *aux = tree;
  if(aux)
    while(aux->left) aux = aux->left;
  return aux;
}

node *search(node *tree, int key){
  if(!tree || tree->data==key) return tree;
  if(key > tree->data) return search(tree->left,key);
  if(key < tree->data) return search(tree->right,key);
}

void p_tranversal_order(node *tree, int size){
	node *aux = tree;
	node **queue = (node **)malloc(size * sizeof(node));
	int begin=0, end=0; //i;
	while(aux){
			printf("%d ", aux->data);
			if(aux->left){
				queue[end] = aux->left;
				end++;
			}
			if(aux->right){
				queue[end] = aux->right;
				end++;
			}
			aux = queue[begin];
			begin++;
	}
	/*libera fila*/
	free(queue);
}

void p_out_order(node *tree){
	if(!tree) return;
	p_out_order(tree->left);
	p_out_order(tree->right);
	printf("%d ", tree->data);
}

void p_in_order(node *tree){
	if(!tree) return;
  p_in_order(tree->left);
  printf("%d ", tree->data);
  p_in_order(tree->right);
}

void p_pre_order(node *tree){
  if(!tree) return;
	printf("%d ", tree->data);
	p_pre_order(tree->left);
	p_pre_order(tree->right);
}

void destroy(node *tree){
	if(!tree) return;
	destroy(tree->left);
	destroy(tree->right);
	free(tree);
	tree = NULL;
}

int count_nodes(node *tree){
  if(tree) return (1 + count_nodes(tree->left) + count_nodes(tree->right));
  return 0;
}
