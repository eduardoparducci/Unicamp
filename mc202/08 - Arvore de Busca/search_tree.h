/*Arquivo de cabecalho com prototipos de funcoes para o laboratorio 08-arvore-busca*/
typedef struct cel{
	int data;
	struct cel *left;
	struct cel *right;
}node;

node *remove_node(node *tree, node *old);
node *biggest(node *tree);
node *smallest(node *tree);
node *search(node *tree, int key);
int count_nodes(node *tree);
node *insert(int key, node *tree);
void p_pre_order(node *tree);
void p_in_order(node *tree);
void p_out_order(node *tree);
void p_tranversal_order(node *tree, int size);
void destroy(node *tree);
