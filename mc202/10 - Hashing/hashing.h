typedef struct cel{
	unsigned int chave;
	int valor;
	struct cel *prox;
} celula;

unsigned int hash(unsigned int ch);
void insere(unsigned int ch, int valor, celula **tabela);
celula *busca(unsigned int ch, celula **tabela);
int remover(unsigned int ch, celula **tabela);
