/* Laboratório 12: RubixCaptcha
   Arquivo de Cabeçalho: lab12.h   */

/* Entrada:  Apontador para um vetor (linearizado) de caracteres
             correspondente a uma placa do cubo
   Saida:    Nao ha

   Objetivo: Rotacionar a placa 90 graus no sentido Horario      */
void rotate_board_CW(char* board);



/* Entrada:  Apontador para um vetor (linearizado) de caracteres
             correspondente a uma placa do cubo
   Saida:    Nao ha

   Objetivo: Rotacionar a placa 90 graus no sentido Anti-Horario */
void rotate_board_CCW(char* board);



/* Entrada:  Apontador para um vetor (linearizado) de caracteres
             correspondente ao cubo
   Saida:    Nao ha

   Objetivo: Rotacionar todas as placas 90 graus no sentido
             Horario                                             */
void rotate_all_CW(char* cube);



/* Entrada:  Apontador para um vetor (linearizado) de caracteres
             correspondente ao cubo
   Saida:    Nao ha

   Objetivo: Rotacionar todas as placas 90 graus no sentido
             anti-Horario                                        */
void rotate_all_CCW(char* cube);



/* Entrada:  Apontador para um vetor (linearizado) de caracteres
             correspondente ao cubo
   Saida:    Nao ha

   Objetivo: Receber as entradas como descritas no enunciado      */
void read_cube(char *cube);



/* Entrada:  Apontador para um vetor (linearizado) de caracteres
             correspondente ao cubo
   Saida:    Nao ha

   Objetivo: Exibir o cubo como o exemplo do enunciado            */
void print_cube(char *cube);



/* Entrada:  Apontador para um vetor (linearizado) de caracteres
             correspondente ao cubo
             Apontador para um vetor de caracteres correspondente
             a palavra-passe
   Saida:    Nao ha

   Objetivo: Procurar a palavra-passe no cubo e exibir suas coordenadas
             de início e fim                                              */
void search_password(char *cube, char *password);



/* Entrada:  Apontador para um vetor de caracteres correspondente
             a palavra-passe
   Saida:    Inteiro indicando o tamanho da palavra

   Objetivo: Calcular o tamanho da palavra                                */
int word_size(char *word);



/* Entrada:  Apontador para um vetor (linearizado) de caracteres
             correspondente ao cubo
             Apontador para um vetor de caracteres correspondente
             a palavra-passe
             Inteiro indicando a posição de início da palavra-passe
             Inteiro usado como multiplicador para alternar entre
             buscas Horizontal, Vertical e Profundidade
   Saida:    Inteiro indicando a posição final da palavra-passe no cubo

   Objetivo: Procurar a palavra-passe no cubo a partir da posição inicial */
int last_pos(char *cube, char *password, int begin, int multiplier);
