/*Desenvolvido por: Eduardo Parducci RA:170272*/

typedef struct{
  int i;
  int j;
  int dado;
}esp;

void organiza_linha(esp *A, int inicio, int fim);
void organiza_coluna(esp *A, int inicio, int fim);
void permuta(esp *A, int pos1, int pos2);
void conta_elem(esp *A, int tam);
int busca(esp *A, int tam, int lin, int col);
