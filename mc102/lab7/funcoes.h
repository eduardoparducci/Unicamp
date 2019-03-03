/*Definindo tipo de dados utilizados no programa*/
typedef char string[101];
typedef struct dadosDoenca doencas;
typedef struct dadosMedico medicos;
typedef struct dadosConsulta consultas;

/*Definindo as estruturas utilizadas no programa*/
struct dadosDoenca{
    char codigo[4];
    string nome;
};
struct dadosMedico{
    char registro[7];
    string nome;
};
struct dadosConsulta{
    string paciente;
    int dia,mes,ano;
    char diag[4];       //diagnóstigo-código da doença
    char atend[7];      //atendente-registro do medico
    consultas *proximo; //aponta p proxima consulta, ordenando a lista
};

/*Criptografa ou descriptografa uma palavra, recebida no parametro nome, de acordo com a matriz chave[2][2]. Retorna a string nome processada de acordo com a operacao, parametro op (1-criptografa 0-descriptografa).*/
char *cifraHill(char *nome,int chave[2][2],int op);

/*Adiciona um registro a lista passando como argumento a ultima consulta registrada*/
void inserir(consultas *ultimaConsulta);

/*Remove um registro da lista passando como argumento a ultima consulta registrada, utilizada na funcao como ponto de partida para percorrer os elementos da lista*/
void remover(consultas *ultimaConsulta);

/*Procura uma consulta a partir de um nome dado (descriptografado) e um ponteiro inicial, retornando um ponteiro para a consulta que possui o nome dado como paciente*/
consultas *procuraConsulta(string nome,consultas *inicioBusca);
