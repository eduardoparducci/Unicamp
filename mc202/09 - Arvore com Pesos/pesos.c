#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pesos.h"

node *build(){

  char c;
  char v[33];//cada nó pode conter ate 32 chars
  node *tree=NULL;

  scanf("%c", &c);
  if (c == ')') return tree;

  tree = malloc(sizeof(node));
	tree->lv = 0;
	tree->rv = 0;
  tree->left = build();

  scanf("%[^(]s", v);
  scanf("%c", &c);
  tree->right = build();

  if(tree->right != NULL && tree->left != NULL) sscanf(v, "%f:%d:%f", &tree->lv, &tree->data, &tree->rv);
  else if(tree->right != NULL) sscanf(v, "%d:%f", &tree->data, &tree->rv);
  else if(tree->left != NULL) sscanf(v, "%f:%d", &tree->lv,&tree->data);
	else sscanf(v, "%d", &tree->data);

  scanf("%c", &c);
  return tree;
}

float summ(node *tree){

	if(!tree) return 0;

  float left_summ = tree->lv + summ(tree->left);
  float right_summ = tree->rv + summ(tree->right);

  if(left_summ > right_summ) return left_summ;
  else return right_summ;
}

void destroy(node *tree){

	if(tree->left) destroy(tree->left);
	if(tree->right) destroy(tree->right);
	if(tree) free(tree);

}
