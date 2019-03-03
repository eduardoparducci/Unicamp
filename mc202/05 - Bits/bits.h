/*funcoes para lab de vetor de bits*/
typedef struct groups{
  unsigned char *array;
  int last; //contem o maior elemento
  int amount_elem;
} group;
/*cria um subconjunto vazio com suporte a n elementos retornando um ponteiro para o conjunto*/
group *create(group  *S, int n);
/*adiciona o elemento data no conjunto S retornando 1-sucesso 0-insucesso*/
int add(group *S, int data) ;
/*remove o elemento data do conjunto S retornando 1-sucesso 0-insucesso*/
int rem(group *S, int data);
/*verifica se data está ou nao no conjunto S retornando 1-sucesso 0-insucesso*/
int in(group *S, int data);
/*conta a quantidade de elementos do conjunto S que sao menores ou iguais a data retornando o numero de elementos*/
void rank(group *S, int data);
/*encontra o elemento de S da posicao pos ordenado de maneira crescente, retornando-o*/
void find(group *S, int pos);
/*conta a quantidade de elementos do conjunto S entre begin e end*/
void range_count(group *S, int begin, int end);
/*imprime o conjunto S em ordem crescente*/
void print(group *S);
/*destroi o subconjunto S*/
group *finish(group *S);
