#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"tree.h"

node *insert(char data){
	node *new_node = malloc(sizeof(node));
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->data = data;
	return new_node;
}

void destroy(node *tree){
	if(!tree) return;
	destroy(tree->left);
	destroy(tree->right);
	free(tree);
	tree = NULL;
}

node *create(char *pre, char *in, int begin, int end, int reset){
	static int i=0;
	int pos;
	if(reset) i=0;
	if(begin>end) return NULL;
	node *root = malloc(sizeof(node));
	root->left = NULL;
	root->right = NULL;
	root->data = pre[i];
	for(pos=begin;pos<=end;pos++){
		if(in[pos] == pre[i]) break;
	}
	i++;
	if(begin==end) return root;
	root->left = create(pre,in,begin,pos-1,0);
	root->right = create(pre,in,pos+1,end,0);
	return root;
}

/*void p_in_order(node *tree){
	if (!tree)return;
  p_in_order(tree->left);
  printf("%c", tree->data);
  p_in_order(tree->right);
}

void p_pre_order(node *tree){
	if(!tree) return;
	printf("%c", tree->data);
	p_pre_order(tree->left);
	p_pre_order(tree->right);
}*/

void p_out_order(node *tree){
	if(!tree) return;
	p_out_order(tree->left);
	p_out_order(tree->right);
	printf("%c", tree->data);
}

void p_tranversal_order(node *tree, int size){
	node *aux = tree;
	node **queue = (node **)malloc(size * sizeof(node));
	int begin=0, end=0, i;
	while(aux){
			printf("%c", aux->data);
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
