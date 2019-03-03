typedef struct cel{
	char data;
	struct cel *left;
	struct cel *right;
}node;

node *create(char *pre, char *in, int begin, int end, int reset);
//void p_pre_order(node *tree);
//void p_in_order(node *tree);
void p_out_order(node *tree);
void p_tranversal_order(node *tree, int size);
void destroy(node *tree);
