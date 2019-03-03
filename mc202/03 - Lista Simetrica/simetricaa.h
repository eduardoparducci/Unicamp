/*header para funcoes da lista simetrica*/

typedef struct nodes{

	double data;
	struct nodes *a;
	struct nodes *b;

} node;

typedef struct lists{

	node *head;
	node *tail;
	unsigned size;

} list;

list *create(void); /*cria uma lista*/
void destroy(list *L); /*destroi uma lista*/
int insert(list *L, int pos, double value); /*insere um elemento na posicao pos com valor value*/
void revert(list *L, int begin, int end); /*inverte os membros entre as posicoes begin e end da lista L*/ 
void print(list *L); /*imprime todos os elementos da lista L*/
