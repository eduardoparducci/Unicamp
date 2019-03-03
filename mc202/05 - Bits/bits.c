#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"bits.h"
#define CHAR_BIT  8

group *create(group  *S, int n){
  if(S) free(S->array); //elimina a array se existir
  else S = malloc(sizeof(group)); //cria o conjunto se este não existir
  S->array = calloc((n/CHAR_BIT + 1),sizeof(unsigned char));
  S->last = n;
  S->amount_elem = 0;
  return S;
}

int add(group *S, int data) {
  if(!S) return 0;
  S->array[data/CHAR_BIT] += 1 << (data % CHAR_BIT);
  S->amount_elem++;
  return 1;
}

int rem(group *S, int data){
  if(!S) return 0;
  S->array[data/CHAR_BIT] -= 1 << (data % CHAR_BIT);
  S->amount_elem--;
  return 1;
}

int in(group *S, int data){
  if(!S) return 0;
  printf("belongs(%d) = ", data);
  if(S->array[data/CHAR_BIT] & 1 << (data % CHAR_BIT)){
    printf("true\n");
    return 1;
  }
  printf("false\n");
  return 0;
}

void rank(group *S, int data){
  int i,amount=0;
  if(!S) return;
  printf("rank(%d) = ", data);
  if(data>S->last){
    printf("0\n");
    return;
  }
  for(i=data;i>=0;i--){
    if(S->array[i/CHAR_BIT] & 1 << (i % CHAR_BIT)) amount++;
  }
  printf("%d\n", amount);
}

void find(group *S, int pos){
  int i,aux=0;
  if(!S) return;
  printf("select(%d) = ", pos);
  if(pos>S->amount_elem){
    printf("0\n");
    return;
  }
  for(i=0;i<=S->last;i++){
    if(S->array[i/CHAR_BIT] & 1 << (i % CHAR_BIT)) aux++;
    if (aux==pos){
      printf("%d\n",i);
      return;
    }
  }
}

void range_count(group *S, int begin, int end){
  int i,amount=0;
  if(!S) return;
  printf("rangecount(%d,%d) = ", begin, end);
  for(i=end;i>=begin;i--){
    if(S->array[i/CHAR_BIT] & 1 << (i % CHAR_BIT)) amount++;
  }
  printf("%d\n", amount);
}

void print(group *S){
  int i,j,amount=0;
  printf("S = {");
  if(S)
    for(i=0;i<=S->last;i++){
      if(S->array[i/CHAR_BIT] & 1 << (i%CHAR_BIT)){
        printf("%d",i);
        amount++;
        if(amount!=S->amount_elem) putchar(',');
      }
    }
  printf("}\n");
  return;
}

group *finish(group *S){
  if(!S) return NULL;
  free(S->array);
  free(S);
  return NULL;
}
