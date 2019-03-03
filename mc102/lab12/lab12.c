#include<stdio.h>
#include"lab12.h"
#define SIZE 10
int main(void){

  char cube[SIZE * SIZE * SIZE];
  char op[5];
  char password[11];
  int board;
  int rot_num;
  int i;

  /* Recebe cubo e qtde de rotações */
  read_cube(cube);
  scanf(" %d", &rot_num);

  /* Recebe e processa operações */
  for(i=0 ; i<rot_num ; i++){

    scanf(" %s", op);
    if(*(op) == 'P'){
      scanf(" %d", &board);
    }
    else{
      board = -1;
    }

    /* Determina a rotação de acordo com a operação e realiza o processamento */
    if((*(op+2) == 'C') && (board == -1)){
      rotate_all_CCW(cube);
    }
    if((*(op+2) == 'C') && (board != -1)){
      rotate_board_CCW(cube+(board*SIZE*SIZE));
    }
    if((*(op+2) == 'W') && (board == -1)){
      rotate_all_CW(cube);
    }
    if((*(op+2) == 'W') && (board != -1)){
      rotate_board_CW(cube+(board*SIZE*SIZE));
    }
  }

  /* Recebe palavra-passe */
  scanf(" %s", password);

  /* Busca e exibe a palavra com suas coordenadas de início e fim */
  search_password(cube, password);

  return 0;
}
void rotate_board_CW(char* board){
    char aux_board[SIZE * SIZE]; /* Cópia do board original*/
    int i,j;

    for(i=0 ; i<SIZE ; i++){
      for(j=0 ; j<SIZE ; j++){
        /* Salva a matriz rotacionada em aux_board*/
        *(aux_board+(SIZE*j+SIZE-i-1)) = *(board+(SIZE*i+j));
      }
    }

    for(i=0 ; i<(SIZE*SIZE) ; i++){
      /* Escreve aux_board na board original*/
      *(board+i) = *(aux_board+i);
    }
}
void rotate_board_CCW(char* board){
  char aux_board[SIZE * SIZE];
  int i,j;

  for(i=0 ; i<SIZE ; i++){
    for(j=0 ; j<SIZE ; j++){
      /* Salva a matriz rotacionada em aux_board*/
      *(aux_board+(SIZE*(SIZE-1-j)+i)) = *(board+(SIZE*i+j));
    }
  }

  for(i=0 ; i<(SIZE*SIZE) ; i++){
    /* Escreve aux_board na board original*/
    *(board+i) = *(aux_board+i);
  }
}
void rotate_all_CW(char* cube){
  int i;

  for(i=0 ; i<SIZE ; i++){
    rotate_board_CW(cube+i*SIZE*SIZE);
  }
}
void rotate_all_CCW(char* cube){
  int i;

  for(i=0 ; i<SIZE ; i++){
    rotate_board_CCW(cube+i*SIZE*SIZE);
  }
}
void read_cube(char *cube){
  char aux;
  int i=0;

  /* Lê a entrada eliminando os espaços */
  while(i<(SIZE*SIZE*SIZE)){
    scanf(" %c", &aux);
    if(aux != ' '){
      *(cube+i) = aux;
      i++;
    }
  }
}
void print_cube(char *cube){
  int i, j, k;

  for(k=0 ; k<SIZE ; k++){
    for(i=0 ; i<SIZE ; i++){
      for(j=0 ; j<SIZE ; j++){
        printf("%c", *(cube + k*SIZE*SIZE + i*SIZE + j));
      }
      putchar(' ');
    }
    putchar('\n');
  }

}
void search_password(char *cube, char *password){
  int begin, end, l;

  /* Percorre o cubo */
  for(l=0 ; l<SIZE*SIZE*SIZE ; l++){

    /* Procura pela correspondencia com a primeira letra da palavra-passe */
    if(*(cube+l) == *password){

      begin = l;

      /* Busca horizontal */
      end = last_pos(cube,password,begin,1);

      /* Busca vertical */
      if(!end){
        end = last_pos(cube,password,begin,SIZE);
      }

      /* Busca em profundidade */
      if(!end){
        end = last_pos(cube,password,begin,SIZE*SIZE);
      }

      /* Encerra o laço se encontrou toda a palavra */
      if(end){
        l = SIZE*SIZE*SIZE;
      }
    }
  }

  /* Exibe a saída esperada */
  printf("%s entre (%d,%d,%d) e (%d,%d,%d)\n", password, (begin%1000)/100, (begin%100)/10, (begin%10), (end%1000)/100, (end%100)/10, (end%10));
}
int last_pos(char *cube, char *password, int begin, int multiplier){
  int length, i, end = 0;

  length = word_size(password);

  for(i=0 ; i<length ; i++){

    /* Não encontrou a  i-esima letra */
    if(*(cube+begin+(i*multiplier)) != *(password+i)){
      end = 0;
      i = length;
    }
    /* Encontrou i-esima letra */
    else{
      end = 1;
    }
  }

  /* Verifica se encontrou toda a palavra e calcula a ultima posicao */
  if(end){
    end = begin+(length-1)*multiplier;
  }

  return end;
}
int word_size(char *word){
  int i=0;

  while(*(word+i) != '\0'){
    i++;
  }

  return i;
}
