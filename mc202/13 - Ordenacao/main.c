#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

int  compara(const void *a, const void *b);
void cria_csv(double dados[4][6], int tam);
void sort_bubble(int *A, int tam);
void sort_insert(int *A, int tam);
void sort_merge(int *A, int inicio, int fim);
void permuta(int *A, int pos1, int pos2);

int main(void){

  clock_t time;
  double tempo;
  double dados[4][6]; //tempo de ordenacao dos 4 algoritmos
  char i;
  unsigned int tam;

  srand(15);
  
  for(i=0 ; i<6 ; i++){

    int *valores,*copia,j;
    
    tam = 5*pow(10,i);
    valores = malloc(tam * sizeof(int));
    copia   = malloc(tam * sizeof(int));
    
    for(j=0 ; j<tam ; j++) valores[j] = rand();

    printf("Testando algoritmos com tamanho %d...\n\n", tam);
    if(i<5){

      printf("Bubble Sort.........................");
      for(j=0 ; j<tam ; j++) copia[j] = valores[j];
      time = clock();
      sort_bubble(copia,tam);
      time = clock() - time;
      printf("OK\n");
      tempo =((double)time) / CLOCKS_PER_SEC;
      dados[0][i] = tempo;
      printf("Resumo:\n\tTempo gasto:%lfs\n\n",tempo);

      printf("Insertion Sort......................");
      for(j=0 ; j<tam ; j++) copia[j] = valores[j];
      time = clock();
      sort_insert(copia,tam);
      time = clock() - time;
      printf("OK\n");
      tempo =((double)time) / CLOCKS_PER_SEC;
      dados[1][i] = tempo;
      printf("Resumo:\n\tTempo gasto:%lfs\n\n",tempo);
    }
    
    printf("Merge Sort......................");
    for(j=0 ; j<tam ; j++) copia[j] = valores[j];
    time = clock();
    sort_merge(copia,0,tam-1);
    time = clock() - time;
    printf("OK\n");
    tempo =((double)time) / CLOCKS_PER_SEC;
    dados[2][i] = tempo;
    printf("Resumo:\n\tTempo gasto:%lfs\n\n",tempo);

    printf("Quick Sort......................");
    for(j=0 ; j<tam ; j++) copia[j] = valores[j];
    time = clock();
    qsort(copia,tam,sizeof(int),compara);
    time = clock() - time;
    printf("OK\n");
    tempo =((double)time) / CLOCKS_PER_SEC;
    dados[3][i] = tempo;
    printf("Resumo:\n\tTempo gasto:%lfs\n\n",tempo);
    
    free(copia);
    free(valores);
  }
  
  cria_csv(dados,6);
  return 0;

}

void cria_csv(double dados[4][6], int tam){

  printf("Carregando dados em arquivo csv...\n\n");

  FILE *arq;
  int i;
  
  arq = fopen("sort.csv","w+");

  fprintf(arq,"Tamanho,Bubble Sort,Insetrion Sort,Merge Sort,Quick Sort");
  
  for(i=0 ; i<tam ; i++){
    
    fprintf(arq,"\n%d,%lf,%lf,%lf,%lf",i,dados[0][i],dados[1][i],dados[2][i],dados[3][i]);
  }
  
  fclose(arq);
  printf("Arquivo criado!\n");
}

void sort_bubble(int *A,int tam){

  int i,j;
  
  for(i=0 ; i<tam ; i++){
    for(j=(tam-1) ; j>i ; j--){
      if(A[j] < A[j-1]) permuta(A,j,(j-1));
    }
  }
}

void sort_merge(int *A, int inicio, int fim){
  /*INACABADO*/
  int meio = (inicio+fim)/2;

  if(inicio==fim) return;
  
  sort_merge(A, inicio, meio);
  sort_merge(A, meio+1, fim );

  int *B = malloc((fim+1) * sizeof(int));
  int i,j,k;

  for(i=inicio ; i<=meio ; i++) B[i] = A[i];
  for(j=meio+1 ; j<=fim  ; j++) B[fim+meio+1-j] = A[j];

  i = inicio;
  j = fim;

  for(k=inicio ; k<=fim ; k++){
    if(B[i]<=B[j]){
      A[k] = B[i];
      i++;
    }
    else{
      A[k] = B[j];
      j--;
    }
  }
}

void sort_insert(int *A, int tam){

  int i,j,aux;

  for(i=0 ; i<tam ; i++){
    aux = A[i];
    j = i-1;
    while(j>=0 && A[j]>aux){
      A[j+1] = A[j];
      j--;
    }
    A[j+1] = aux;
  }
}

void permuta(int *A, int pos1, int pos2){

  int aux;

  aux = A[pos1];
  A[pos1] = A[pos2];
  A[pos2] = aux;
}

int  compara(const void *a, const void *b){
  return ( *(int *)a - *(int *)b );
}
