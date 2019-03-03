#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"funcoes.h"

extern int Mchave[2][2];    //matriz chave para a cifra de Hill (declarada em labSemanal07.c)
extern consultas *primeiraConsulta;
char *cifraHill(char *nome,int op){

    int chave[2][2]
    int *numPalavra=NULL;   //ponteiro do nome convertido em numeros
    int i,j,fator,aux,opc;  //fator-usado para descriptografar | aux-usado para troca de pos da matriz
    int par[2];             //vetor coluna gerado por um par de letras do nome
    int result[2];          //vetor coluna gerado apos processar par[2][2]
    
    /*--faz uma copia de Mchave---*/
    for(i=0;i<2;i){
        for(j=0;j<2;j++){
            chave[i][j]=Mchave[i][j];
        }
    }
    
    if(op==0){ //1-criptografa 0-descriptografa
        /*para descriptografar, é necessario calcular (matriz inversa de Mchave[2][2] * mod(26))*/
        fator=(chave[0][0]*chave[1][1]) - (chave[0][1]*chave[1][0]);
        fator= (fator%26 - 26) * (-1);
        aux=chave[1][1];
        chave[1][1]=chave[0][0];
        chave[0][0]=aux;
        chave[1][0]=chave[1][0]*(-1);
        chave[0][1]=chave[0][1]*(-1);
        for(i=0;i<2;i++){
            for(j=0;j<2;j++){
                chave[i][j]=(fator*chave[i][j]) % 26;
                if(chave[i][j]<0){chave[i][j]+=26;}
            }
        }
    }
    numPalavra=(int *)malloc(strlen(nome) * sizeof(int)); //aloca o espaco necessario para criar o vetor
    for(i=0;i<strlen(nome);i++){
        numPalavra[i]=(int)nome[i]-65;//converte string em numeros
        par[i%2]=numPalavra[i]; //separa os numeros em pares verificando se a posicao é par ou ímpar
        if(i%2==1){ //preencheu o vetor par[2]
            for(j=0;j<2;j++) //j representa linha da matriz chave
                result[j]=chave[j][0]*par[0] + chave[j][1]*par[1];
            if(result[0]>25 || result[1]>25){
                result[0] = result[0]%26;
                result[1] = result[1]%26;
            }
            nome[i-1] = (char)(result[0]+65);
            nome[i] = (char)(result[1]+65);
        }
    }
    return nome;
}

consultas *procuraConsulta(string nome,consultas *inicioBusca){
    consultas *consultaBuscada;
    /*---ponto de partida para busca---*/
    consultaBuscada=inicioBusca;
    while(strcmp(consultaBuscada->paciente,nome)!=0){ //executa até encontrar o nome procurado
        consultaBuscada=consultaBuscada->proximo;     //percorre a lista
    }
    return consultaBuscada;
}

void altData(consultas *ultimaConsulta){
    consultas *consultaAlteracao;
    string nomePaciente;
    int nDia,nMes,nAno; //novo dia, novo mes, novo ano
    
    /*---recebe dados para remocao---*/
    scanf("%s %d/%d/%d", nomePaciente, &nDia,&nMes,&nAno);
    
    /*---criptografa o nome para busca-lo---*/
    nomePaciente=cifraHill(nomePaciente,1);
    
    /*---busca consulta---*/
    consultaAlteracao=procuraConsulta(nomePaciente,ultimaConsulta);
    
    /*---altera a data---*/
    consultaAlteracao->dia=nDia;
    consultaAlteracao->mes=nMes;
    consultaAlteracao->ano=nAno;
    
    return;
}

void inserir(consultas *ultimaConsulta){
    /*---variaveis da nova consulta---*/
    consultas *novaConsulta;
    consultas *consultaAnterior;//consulta que possui como ->proximo a ultimaConsulta
    string paciente;
    int dia,mes,ano;
    char diag[4],atend[7];
    int i=0;
    /*---recebe dados da nova consulta---*/
    scanf("%s",paciente);
    scanf("%d/%d/%d ",&dia,&mes,&ano);
    scanf("%s %s",diag,atend);

    /*---aloca a memoria necessaria para uma inclusao---*/
    novaConsulta=(consultas *) malloc(sizeof(consultas));
    
    /*---salva os dados na nova consulta---*/
    novaConsulta->paciente = paciente;
    novaConsulta->dia   = dia;
    novaConsulta->mes   = mes;
    novaConsulta->ano   = ano;
    novaConsulta->diag  = diag;
    novaConsulta->atend = atend;
    
    /*---ordena a lista---*/
    if(ultimaConsulta==NULL){//primeiro registro
        ultimaConsulta=novaConsulta;
        primeiraConsulta=novaConsulta;
    }
    else{
        while(i==0){
            /*---verifica se o nome da novaConsulta é anterior à da ultimaConsulta---*/
            if(strcmp(cifraHill(ultimaConsulta->paciente,0), cifraHill(novaConsulta->paciente,0)) > 0){
                /*---busca a consulta anterior---*/
                consultaAnterior=ultimaConsulta; //ponto de partida para busca
                while(consultaAnterior->proximo!=ultimaConsulta){
                    consultaAnterior=consultaAnterior->proximo; //percorre a lista
                }
                consultaAnterior->proximo=novaConsulta;
                novaConsulta->proximo=ultimaConsulta;
                ultimaConsulta->proximo=primeiraConsulta;
            }
            else{
                ultimaConsulta->proximo=novaConsulta;
                novaConsulta->proximo=primeiraConsulta;
                i=1;
            }
        }
    }
    return;
}

void remover(consultas *ultimaConsulta){
    string nomeRemocao; //nome do paciente a ser removido
    consultas *consultaRemocao; //consulta a ser removida
    consultas *consultaAnterior;//consulta que possui como ->proximo a consultaRemocao
    /*---recebe dados para remocao---*/
    scanf("%s", nomeRemocao);
    
    /*---criptografa o nome para busca-lo---*/
    nomeRemocao=cifraHill(nomeRemocao,1);
    
    /*---busca a consulta do nomeRemocao---*/
    consultaRemocao=procuraConsulta(nomeRemocao,ultimaConsulta);
    /*---busca a consulta anterior---*/
    consultaAnterior=ultimaConsulta; //ponto de partida para busca
    while(consultaAnterior->proximo!=consultaRemocao){
        consultaAnterior=consultaAnterior->proximo; //percorre a lista
    }
    consultaAnterior->proximo = consultaRemocao->proximo; //remove consultaRemocao dos ponteiros
    free(consultaRemocao); //elimina consultaRemocao
    return;
}

void altDiag(consultas *ultimaConsulta, int qtDoencas, doencas *doenca){
    consultas *consultaAlteracao;
    string nomePaciente;
    string novoDiag; //novo diagnostico
    int i;
    
    /*---recebe dados para remocao---*/
    scanf("%s %s", nomePaciente, novoDiag);
    
    /*---criptografa o nome para busca-lo---*/
    nomePaciente=cifraHill(nomePaciente,1);
    
    /*---busca consulta---*/
    consultaAlteracao=procuraConsulta(nomePaciente,ultimaConsulta);
    
    /*---busca o codigo do diagnostico---*/
    for(i=0;i<qtDoencas;i++){
        if(!strcmp(doenca[i].nome,novoDiag)){ //encontrou a doenca no vetor
            strcpy(consultaAlteracao->diag,doenca[i].codigo); //altera diagnostico
            break;
        }
    }
    return;
}

void altMed(consultas *ultimaConsulta, int qtMedicos, medicos *medico){
    consultas *consultaAlteracao;
    string nomePaciente;
    string novoMed; //novo medico
    int i;
    
    /*---recebe dados para remocao---*/
    scanf("%s %s", nomePaciente, novoMed);
    
    /*---criptografa o nome para busca-lo---*/
    nomePaciente=cifraHill(nomePaciente,1);
    
    /*---busca consulta---*/
    consultaAlteracao=procuraConsulta(nomePaciente,ultimaConsulta);
    
    /*---busca o codigo do diagnostico---*/
    for(i=0;i<qtMedicos;i++){
        if(!strcmp(medico[i].nome,novoMed)){ //encontrou o medico no vetor
            strcpy(consultaAlteracao->atend,medico[i].registro); //altera diagnostico
            break;
        }
    }
    return;
}

void gerarRelatorio(consultas *ultimaConsulta, char inicio){
    consultas *auxiliar; //ponteiro auxiliar para ordenar a lista
    int i=0;
    auxiliar=ultimaConsulta; //seta como primeiro da lista
    if(((int)auxiliar->paciente[i]-(int)inicio)>=0) //PAREI AQUI!
}