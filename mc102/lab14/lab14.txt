#include<stdio.h>
#include<string.h>

/* Definição da estrutura dada no enunciado */
typedef struct tagmembro{
  char nome[64];
  int idade;
  char antecessor_nome[64];
  int vivo_ou_morto;
  int antecessor_indice;
  int primeiro_filho;
  int segundo_filho;
  int terceiro_filho;
}membro;

/* Protótipo das funções utilizadas */
void preenche_filhos(membro *linha_sucessoria);
void preenche_antecessor(membro *linha_sucessoria, int qtde_sucessores, int i, int j);
void imprime_linha_sucessoria(membro *linha_sucessoria, int qtde_sucessores);
void inicia_linha_sucessoria(membro *linha_sucessoria, int qtde_sucessores, int i);
void organiza_filhos(membro *linha_sucessoria, int qtde_sucessores, int i);
void imprime_sucessao(membro *linha_sucessoria, int sucessor);

/* Função main */
int main(void){

  membro linha_sucessoria[101];
  int qtde_sucessores;

  /* Recebe qtde_sucessores e carrega vetor linha_sucessoria */
  scanf("%d", &qtde_sucessores);
  inicia_linha_sucessoria(linha_sucessoria,qtde_sucessores,0);
  preenche_antecessor(linha_sucessoria,qtde_sucessores,0,0);
  organiza_filhos(linha_sucessoria,qtde_sucessores,0);
  imprime_sucessao(linha_sucessoria,0);
  
  return 0;
}

void imprime_linha_sucessoria(membro *linha_sucessoria, int qtde_sucessores){

  int i;
  membro *pessoa;

  for(i=0 ; i<qtde_sucessores ; i++){
    pessoa = linha_sucessoria + i;
    printf("Nome:%s\nIdade:%d\nAntecessor:%s (%s) [%d]\nFilhos:[%d][%d][%d]\n\n",pessoa->nome,pessoa->idade,pessoa->antecessor_nome,(!pessoa->vivo_ou_morto)? "vivo" : "morto",pessoa->antecessor_indice,pessoa->primeiro_filho,pessoa->segundo_filho,pessoa->terceiro_filho);
  }
  
}

void inicia_linha_sucessoria(membro *linha_sucessoria, int qtde_sucessores, int i){

  membro *pessoa = linha_sucessoria + i;
  
  /* Condição de parada para a recursão */
  if(i==qtde_sucessores)
    return;

  scanf(" %[^;];%d;%[^;];%d\n", pessoa->nome, &pessoa->idade, pessoa->antecessor_nome, &pessoa->vivo_ou_morto);
  pessoa->antecessor_indice = -1;
  pessoa->primeiro_filho = -1;
  pessoa->segundo_filho = -1;
  pessoa->terceiro_filho = -1;

  inicia_linha_sucessoria(linha_sucessoria,qtde_sucessores,i+1);
  
}

void preenche_antecessor(membro *linha_sucessoria, int qtde_sucessores, int i, int j){

  /* Define pai e filho */
  membro *pai = linha_sucessoria + i;
  membro *filho = linha_sucessoria + j;

  /* Condições de parada para a função recursiva */
  if(i==qtde_sucessores)
    return;
  if(j==qtde_sucessores){
    preenche_antecessor(linha_sucessoria,qtde_sucessores,i+1,0);
    return;
  }

  /* Preenche dados do pai e filho quando encontra */
  if(!strcmp(pai->nome,filho->antecessor_nome)){
    filho->antecessor_indice = i;

    if(pai->primeiro_filho==-1)
      pai->primeiro_filho = j;
    else if(pai->segundo_filho==-1){
      pai->segundo_filho = j;
    }
    else{
      pai->terceiro_filho = j;
    }
  }

  preenche_antecessor(linha_sucessoria,qtde_sucessores,i,j+1);
  
}

void organiza_filhos(membro *linha_sucessoria, int qtde_sucessores, int i){

  membro *pai = linha_sucessoria + i;
  int p_filho, s_filho, t_filho, aux;
  
  /* Criterio de parada da recursão */
  if(i==qtde_sucessores)
    return;

  p_filho = pai->primeiro_filho;
  s_filho = pai->segundo_filho;
  t_filho = pai->terceiro_filho;

  if(linha_sucessoria[p_filho].idade < linha_sucessoria[s_filho].idade){
    aux = pai->primeiro_filho;
    pai->primeiro_filho = pai->segundo_filho;
    pai->segundo_filho = aux;
    p_filho = pai->primeiro_filho;
    s_filho = pai->segundo_filho;
    t_filho = pai->terceiro_filho;
  }
  if(linha_sucessoria[p_filho].idade < linha_sucessoria[t_filho].idade){
    aux = pai->primeiro_filho;
    pai->primeiro_filho = pai->terceiro_filho;
    pai->terceiro_filho = aux;
    p_filho = pai->primeiro_filho;
    s_filho = pai->segundo_filho;
    t_filho = pai->terceiro_filho;
  }
  if(linha_sucessoria[s_filho].idade < linha_sucessoria[t_filho].idade){
    aux = pai->segundo_filho;
    pai->segundo_filho = pai->terceiro_filho;
    pai->terceiro_filho = aux;
    p_filho = pai->primeiro_filho;
    s_filho = pai->segundo_filho;
    t_filho = pai->terceiro_filho;
  }
  
  organiza_filhos(linha_sucessoria,qtde_sucessores,i+1);
  
}

void imprime_sucessao(membro *linha_sucessoria, int sucessor){

  static int posicao = 1;
  membro *pessoa = linha_sucessoria + sucessor;
  
  if(sucessor && !pessoa->vivo_ou_morto)
    printf("%d) %s\n", posicao++, pessoa->nome);
  if(pessoa->primeiro_filho!=-1)
    imprime_sucessao(linha_sucessoria,pessoa->primeiro_filho);
  if(pessoa->segundo_filho!=-1)
    imprime_sucessao(linha_sucessoria,pessoa->segundo_filho);
  if(pessoa->terceiro_filho!=-1)
    imprime_sucessao(linha_sucessoria,pessoa->terceiro_filho);
  
}
