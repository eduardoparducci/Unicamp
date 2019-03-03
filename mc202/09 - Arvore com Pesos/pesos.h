typedef struct cel{
  int data;
  struct cel *left;
  struct cel *right;
  float lv;
  float rv;
} node;

node *build(void);
void destroy(node *tree);
float summ(node *tree);
