// Eduardo Parducci RA:170272
// LabSemanal07 - relatorio de consultas

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"funcoes.h"

int Mchave[2][2];   //matriz chave para a cifra de Hill
consultas *primeiraConsulta=NULL;
int main(void){
    /*---------entradas-----------*/
    int qtDoencas,qtMedicos;
    char inicio;     //letra que inicia a impressao do relatorio
    char operacao[8];
    doencas *doenca=NULL;
    medicos *medico=NULL;
    consultas *consulta=NULL;
    /*---variaveis auxiliares-----*/
    int i,j;
    /*-------recebe doencas-------*/
    scanf(" %d", &qtDoencas);
    doenca = (doencas *) calloc(qtDoencas,sizeof(doencas)); //aloca espaco necessario para as doencas
    for(i=0;i<qtDoencas;i++){
        scanf(" %s %s", doenca[i].codigo, doenca[i].nome);
    }
    /*-------recebe medicos-------*/
    scanf(" %d", &qtMedicos);
    medico = (medicos *) calloc(qtMedicos,sizeof(medicos)); //aloca espaco necessario para os medicos
    for(i=0;i<qtMedicos;i++){
        scanf("%s %[^\n]s", medico[i].registro, medico[i].nome);
    }
    /*----recebe matriz chave-----*/
    for(i=0;i<2;i++){
        for(j=0;j<2;j++){
            scanf("%d", &chave[i][j]);
        }
    }
    /*---recebe letra de inicio---*/
    scanf(" %c", &inicio);
    do{
        scanf(" %s", operacao);
        if(!strcmp(operacao,"add"))     //insere ordenado
            inserir(consulta);
        if(!strcmp(operacao,"rm"))      //remove consulta
            remover(consulta);
        if(!strcmp(operacao,"altdiag")) //altera diagnostico
            altDiag(consulta,qtDoencas,doenca);
        if(!strcmp(operacao,"altdata")) //altera data consulta
            printf("Altera data!\n");
        if(!strcmp(operacao,"altmed"))  //altera medico
            altMed(consulta,qtMedicos,medico);
    }while(operacao[0]!='0');    
    /*---exibe relatorio---*/
    printf("Exibir relatorio!\n");
    return 0;
}
