#include "montador.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 64

typedef struct Item {
  char nome[SIZE];
  char tipo; //  r:defRotulo  s:simbolo
  int  valor;
  struct Item *prox;

} Item;

// Lista ligada para rotulos e simbolos
Item *cabeca=NULL;

// Funcoes de manipulacao da lista
void adicionarItem(Item item);
void removerItem(Item item);
int  recuperaValorItem(char *nome);
char recuperaTipoItem(char *nome);
void imprimeMapa(char mapa[1024][14]);
void imprimeItens();

// Funcoes auxiliares

/* Retorna:
 *  1 caso haja erro na montagem;
 *  0 caso não haja erro.
 */
int emitirMapaDeMemoria() {
  Token tok;
  Item aux;
  char mapa[1024][14];
  char *posicao;
  int i,j,jmp, mp=0;

  for(i=0;i<1024;i++){
    strcpy(mapa[i],"G000000000000");
  }
  /* <<< 1A PASSAGEM >>>
   * percorre tokens alimentando lista de itens */
  for(i=0;i<getNumberOfTokens();i++) {

    tok = recuperaToken(i);
    switch(tok.tipo) {

    case Diretiva:
      //printf("Diretiva!\n");

      if(!strcmp(tok.palavra,".set")) {
        // carrega Novo Simbolo e o adiciona na lista
        strcpy(aux.nome,recuperaToken(++i).palavra);
        aux.valor = (int)strtol(recuperaToken(++i).palavra,NULL,10);
        aux.tipo = 's';
        adicionarItem(aux);
      }
      else if(!strcmp(tok.palavra,".wfill")) {
        // erro palavra desalinhada
        if(mp%2) {
          fprintf(stderr,"Impossível montar código!\n");
          return 1;
        }
        // pula o numero de linhas contido no token seguinte
        mp += 2*(int)strtol(recuperaToken(++i).palavra,NULL,10);
        i++; //ignora o valor do token seguinte
      }
      else if(!strcmp(tok.palavra,".word")) {
        // erro palavra desalinhada
        if(mp%2)
          return 1;
        //pula uma palavra de memoria e ignora o token seguinte
        mp+=2;
        i++;
      }
      else if(!strcmp(tok.palavra,".align")) {

        jmp = (int)strtol(recuperaToken(++i).palavra,NULL,10);
        if(mp%2)
          mp++;
        if((mp/2)%jmp)
          mp+=2*( (mp/2)+jmp - (mp/2)%jmp );
      }
      else if(!strcmp(tok.palavra,".org"))
        mp = (int)strtol(recuperaToken(++i).palavra,NULL,10);
      break;

    case Instrucao:
      if(!strcmp(tok.palavra,("LSH")) || !strcmp(tok.palavra,("RSH")) || !strcmp(tok.palavra,("LOADmq")))
        break;
      else {
        i++;
        mp++;
      }
      break;

    case DefRotulo:
      // carrega novo item com as definicoes do rotulo
      strcpy(aux.nome,tok.palavra);
      // remove ':' ao final da string
      aux.nome[strlen(aux.nome)-1] = '\0';
      aux.tipo = 'r';
      aux.valor = mp;
      adicionarItem(aux);
      break;

    default:
      mp++;
      break;
    }
  }
  // imprimeItens();

  //   <<< 2A PASSAGEM >>>
  mp=0;
  for(i=0;i<getNumberOfTokens();i++) {

    tok = recuperaToken(i);
    // posicao de escrita no mapa
    posicao =mapa[mp/2];
    switch(tok.tipo) {
      case Diretiva:
        // ORG
        if(!strcmp(tok.palavra,".org")){
          if(recuperaToken(i+i).tipo==Decimal)
            mp = 2*(int)strtol(recuperaToken(++i).palavra,NULL,10);
          else
            mp = 2*(int)strtol(recuperaToken(++i).palavra,NULL,16);
        }
        // WORD
        else if(!strcmp(tok.palavra,".word")) {
          if(mapa[mp/2][0]!='G') {
            fprintf(stderr,"Impossível montar o código!\n");
            return 1;
          }
          if(recuperaToken(i+1).tipo==Nome){
            if(recuperaValorItem(recuperaToken(i+1).palavra)==-1) {
              fprintf(stderr,"USADO MAS NÃO DEFINIDO: %s!\n", recuperaToken(i+1).palavra);
              return 1;
            }
            if(recuperaTipoItem(recuperaToken(i+1).palavra)=='r')
              sprintf(posicao,"%3X%10X",(mp/2),(recuperaValorItem(recuperaToken(++i).palavra))/2);
            else
              sprintf(posicao,"%3X%10X",(mp/2),recuperaValorItem(recuperaToken(++i).palavra));
          }
          else if(recuperaToken(i+1).tipo==Decimal){
            sprintf(posicao,"%3X%10X",(mp/2),strtol(recuperaToken(++i).palavra,NULL,10));
          }
          else if(recuperaToken(i+1).tipo==Hexadecimal){
            sprintf(posicao,"%3X%10X",(mp/2),strtol(recuperaToken(++i).palavra,NULL,16));
          }
          mp+=2;
        }
        // WFILL
        else if(!strcmp(tok.palavra,".wfill")) {
          if(mapa[mp/2][0]!='G') {
            fprintf(stderr,"Impossível montar o código!\n");
            return 1;
          }
          for(j=0;j<strtol(recuperaToken(i+1).palavra,NULL,10);j++) {
            posicao = mapa[mp/2];
            if(recuperaToken(i+2).tipo==Nome){
              if(recuperaValorItem(recuperaToken(i+2).palavra)==-1) {
                fprintf(stderr,"USADO MAS NÃO DEFINIDO: %s!\n", recuperaToken(i+2).palavra);
                return 1;
              }
              if(recuperaTipoItem(recuperaToken(i+2).palavra)=='r')
                sprintf(posicao,"%3X%10X",(mp/2),(recuperaValorItem(recuperaToken(i+2).palavra))/2);
              else
                sprintf(posicao,"%3X%10X",(mp/2),recuperaValorItem(recuperaToken(i+2).palavra));
            }
            else if(recuperaToken(i+2).tipo==Decimal)
              sprintf(posicao,"%3X%10X",(mp/2),strtol(recuperaToken(i+2).palavra,NULL,10));
            else
              sprintf(posicao,"%3X%10X",(mp/2),strtol(recuperaToken(i+2).palavra,NULL,16));
            mp+=2;
          }
          i+=2;
        }
        // ALIGN
        else if(!strcmp(tok.palavra,".align")) {
          if(recuperaToken(i+1).tipo==Decimal)
            jmp = (int)strtol(recuperaToken(++i).palavra,NULL,10);
          else if(recuperaToken(i+1).tipo==Hexadecimal)
            jmp = (int)strtol(recuperaToken(++i).palavra,NULL,16);
          if(mp%2) {
            strcpy(posicao+8,"00000");
            mp++;
          }
          if((mp/2)%jmp)
            mp+=2*( (mp/2)+jmp - (mp/2)%jmp );
        }
      break;

      case Instrucao:
        if(!(mp%2)) {
          if(mapa[mp/2][0]!='G') {
            fprintf(stderr,"Impossível montar o código!\n");
            return 1;
          }
          sprintf(posicao,"%3X",(mp/2));
          posicao+=3;
        }
        else
          posicao+=8;

        const char *mnemonicos[11] = {"LOAD","LOAD-","LOAD|","LOADmq_mx","STOR","ADD","ADD|","SUB","SUB|","MUL","DIV"};
        const char *codigos[11] = {"01","02","03","09","21","05","07","06","08","0B","0C"};
        // procura em vetor 'mnemonicos'
        for(j=0;j<11;j++) {
          if(!strcmp(tok.palavra,mnemonicos[j])) {
            // verifica se argumento é um nome
            if(recuperaToken(i+1).tipo==Nome) {
              // verifica se o nome existe
              if(!recuperaValorItem(recuperaToken(i+1).palavra)==-1) {
                fprintf(stderr,"USADO MAS NÃO DEFINIDO: %s!\n",recuperaToken(i+1).palavra);
                return 1;
              }
              sprintf(posicao,"%s%3X",codigos[j],recuperaValorItem(recuperaToken(++i).palavra));
            }
            else if(recuperaToken(i+1).tipo==Decimal)
              sprintf(posicao,"%s%3X",codigos[j],strtol(recuperaToken(++i).palavra,NULL,10));
            else
              sprintf(posicao,"%s%3X",codigos[j],strtol(recuperaToken(++i).palavra,NULL,16));
            mp++;
            break;
          }
        }
        // nao encontrou ocorrencia de 'instrucao' em 'mnemonicos'
        if(j==11) {
          if(!strcmp(tok.palavra,"LSH")){
            strcpy(posicao,"14000");
            mp++;
          }
          else if(!strcmp(tok.palavra,"RSH")) {
            strcpy(posicao,"15000");
            mp++;
          }
          else if(!strcmp(tok.palavra,"JUMP")) {
            if(recuperaToken(i+1).tipo==Nome) {
              if(recuperaValorItem(recuperaToken(i+1).palavra)==-1) {
                fprintf(stderr,"USADO MAS NÃO DEFINIDO: %s!\n",recuperaToken(i+1).palavra);
                return 1;
              }
              else {
                if(recuperaValorItem(recuperaToken(i+1).palavra)%2) //JUMP A DIREITA
                  sprintf(posicao,"0E%3x",recuperaValorItem(recuperaToken(++i).palavra));
                else // JUMP A ESQUERDA
                  sprintf(posicao,"0D%3x",recuperaValorItem(recuperaToken(++i).palavra));
              }
            }
            else if(recuperaToken(i+1).tipo==Decimal)
              sprintf(posicao,"0D%3x",strtol(recuperaToken(++i).palavra,NULL,10));
            else
              sprintf(posicao,"0D%3x",strtol(recuperaToken(++i).palavra,NULL,16));
            mp++;
          }
          else if(!strcmp(tok.palavra,"JMP+")) {
            if(recuperaToken(i+1).tipo==Nome) {
              if(recuperaValorItem(recuperaToken(i+1).palavra)==-1) {
                fprintf(stderr,"USADO MAS NÃO DEFINIDO: %s!\n",recuperaToken(i+1).palavra);
                return 1;
              }
              else {
                if(recuperaValorItem(recuperaToken(i+1).palavra)%2) //JUMP A DIREITA
                  sprintf(posicao,"10%3X",recuperaValorItem(recuperaToken(++i).palavra));
                else // JUMP A ESQUERDA
                  sprintf(posicao,"0F%3X",recuperaValorItem(recuperaToken(++i).palavra));
              }
            }
            else if(recuperaToken(i+1).tipo==Decimal)
              sprintf(posicao,"0F%3x",strtol(recuperaToken(++i).palavra,NULL,10));
            else
              sprintf(posicao,"0F%3x",strtol(recuperaToken(++i).palavra,NULL,16));
            mp++;
          }
          else if(!strcmp(tok.palavra,"STORA")) {
            if(recuperaToken(i+1).tipo==Nome) {
              if(recuperaValorItem(recuperaToken(i+1).palavra)==-1) {
                fprintf(stderr,"USADO MAS NÃO DEFINIDO: %s!\n",recuperaToken(i+1).palavra);
                return 1;
              }
              else {
                if(recuperaValorItem(recuperaToken(i+1).palavra)%2) // INSTRUCAO A DIREITA
                  sprintf(posicao,"13%3X",recuperaValorItem(recuperaToken(++i).palavra));
                else // INSTRUCAO A ESQUERDA
                  sprintf(posicao,"12%3X",recuperaValorItem(recuperaToken(++i).palavra));
              }
            }
            else if(recuperaToken(i+1).tipo==Decimal)
              sprintf(posicao,"12%3x",strtol(recuperaToken(++i).palavra,NULL,10));
            else
              sprintf(posicao,"12%3x",strtol(recuperaToken(++i).palavra,NULL,16));
            mp++;
        }
      }
      break;
    }
  }
  if(mp%2)
    strcpy(mapa[mp/2]+8,"00000");
  imprimeMapa(mapa);
  return 0;
}

void adicionarItem(Item item) {

  Item *novoItem = malloc(sizeof(Item));
  novoItem->tipo  = item.tipo;
  novoItem->valor = item.valor;
  strcpy(novoItem->nome,item.nome);
  novoItem->prox = cabeca;
  cabeca = novoItem;
}
void imprimeItens() {
  Item *aux = cabeca;
  //if(!cabeca) printf("Lista vazia!\n");
  while(aux) {
    printf("Tipo:%c\nNome:%s\nValor:%d\n\n", aux->tipo, aux->nome, aux->valor);
    aux = aux->prox;
  }
}
int recuperaValorItem(char *nome) {
  Item *aux = cabeca;

  while(aux) {
    if(!strcmp(nome,aux->nome))
      return aux->valor;
    aux = aux->prox;
  }
  return -1;
}
char recuperaTipoItem(char *nome){
  Item *aux = cabeca;

  while(aux) {
    if(!strcmp(nome,aux->nome))
      return aux->tipo;
    aux = aux->prox;
  }
  return -1;

}
void imprimeMapa(char mapa[1024][14]){
  int i,j;
  for(i=0;i<1024;i++){
    if(mapa[i][0]!='G'){
      for(j=0;j<13;j++){
        if(j==3 || j==5 || j==8 || j==10)
          printf(" ");
        if(mapa[i][j]==' ')
          printf("0");
        else
          printf("%c",mapa[i][j]);
      }
      printf("\n");
    }
  }
}
