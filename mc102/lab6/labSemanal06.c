/* Desenvolvido por: Eduardo Parducci
   RA: 170272
   Este programa calcula o indice de qualidade de funcionarios de uma empresa, mostrando como saída, o
   funcionario que obteve melhor índice.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef char string[31];
typedef struct dadosFuncionario dados;
struct dadosFuncionario{
    string nome;    //nome funcionario
    dados *chefe;   //ponteiro para a estrutura de dados do chefe
    int prodAbs;    //produtividade absoluta
    int qtSub;      //quantidade de subordinados
    int nivel;      //nivel hierarquico na empresa
    float prodRel;  //produtividade relativa
    float qualidade;//indice de qualidade
    double  salario;//salario
};

/*-----funcoes-----*/
void calcSalario(dados *, int , float); //calcula o salario dos funcionarios
void calcQualidade(dados *, int, int);  //calcula o indice de qualidade dos funcionarios
double salarioRel(dados *, int);        //calcula o salario relativo de um funcionario
float logB2(float);                     //calcula o log na base 2 de um determinado numero
int logEstrela(int);                    //calcula o log*
int nivel(dados *);                     //calcula o nivel hierarquico de um funcionario
float prodRel(dados *,dados *, int);    //calcula a produtividade relativa de um funcionario
int main(void)
{
    float somaSalario;              //gasto total da empresa com salarios
    int qtFunc;                     //quantidade de funcionarios
    int fatReg;                     //fator de regularizacao
    /*-----variaveis auxiliares-----*/
    int i,j,k;
    string nomeFunc, nomeChefe;
    dados *melhorFunc=NULL;         //ponteiro para o melhor funcionario

    scanf("%f", &somaSalario);
    scanf("%d", &fatReg);
    scanf("%d", &qtFunc);
    dados *funcionario = malloc(qtFunc * sizeof(dados));  //dados de todos os funcionarios
    for(i=0;i<qtFunc;i++){
        scanf("%s %d", funcionario[i].nome, &funcionario[i].prodAbs);
        funcionario[i].chefe = NULL;     //zera as strings com o nome chefe
        funcionario[i].qtSub = 0;           //zera a qtde de subordinados
    }
    /*----Registra os chefes dos funcionarios----*/
    for(i=0;i<(qtFunc-1);i++){
        scanf("%s %s", nomeFunc, nomeChefe);
        for(j=0;j<qtFunc;j++)
            if(!strcmp(nomeFunc,funcionario[j].nome))   //encontrou nome funcionario no indice j
                for(k=0;k<qtFunc;k++)
                    if(!strcmp(nomeChefe,funcionario[k].nome)) //encontrou nome chefe no indice k
                        funcionario[j].chefe = &funcionario[k];
    }
    /*--------Calcula qtde subordinados----------*/
    for(i=0;i<qtFunc;i++)
        for(j=0;j<qtFunc;j++)
            if(&funcionario[i]==funcionario[j].chefe) //funcionario possui subordinado
                funcionario[i].qtSub++;
    /*-------Calcula o salario relativo, produtividade relativa e nivel de tds os func-----*/
    for(i=0;i<qtFunc;i++){
        funcionario[i].salario = salarioRel(&funcionario[i], qtFunc);
        funcionario[i].prodRel = prodRel(&funcionario[0], &funcionario[i], qtFunc);
        funcionario[i].nivel = nivel(&funcionario[i]);
    }
    /*-------Calcula o salario real e indice de qualidade dos funcionarios-----*/
    calcSalario(&funcionario[0],qtFunc,somaSalario);
    calcQualidade(&funcionario[0],qtFunc,fatReg);
    /*-------Calcula o melhor funcionario------------------*/
    melhorFunc = &funcionario[0];
    for(i=0;i<qtFunc;i++)
        if(funcionario[i].qualidade>melhorFunc->qualidade)
            melhorFunc = &funcionario[i];
    printf("%s %.2f\n", melhorFunc->nome, melhorFunc->qualidade);
    return 0;
}
float prodRel(dados *inicio,dados *funcionario, int qtFunc){
    int i;
    float somaProd=0;
    if(funcionario->qtSub==0) //funcionario nao possui subordinado
        return (float)funcionario->prodAbs;
    else{
        for(i=0;i<qtFunc;i++)                               
            if(funcionario==inicio[i].chefe) //achou um subordinado ao funcionario
                somaProd=somaProd+prodRel(&inicio[0], &inicio[i], qtFunc); //calcula a soma das prodRel dos subordinados
        funcionario->prodRel=0.5*(funcionario->prodAbs+(float)(1.0/funcionario->qtSub)*somaProd); //calcula a prodRel do funcionario
        return funcionario->prodRel;
    }
}
//salario relativo indica a relacao entre o salario de todos os funcionarios em relacao ao presidente, que possui salario relativo=1
double salarioRel(dados *funcionario, int qtFunc){
    if(funcionario->chefe==NULL)
        funcionario->salario = 1;
    else{
        funcionario->salario = (funcionario->chefe->qtSub/(funcionario->chefe->qtSub+1.0))*salarioRel(funcionario->chefe,qtFunc);
    }
    return funcionario->salario;
}
void calcSalario(dados *inicio, int qtFunc, float somaSalario){
    int i;
    double somaSalRel=0;  //soma dos salarios relativos
    double fator=0;       //fator de conversao de salario relativo para salario real

    for(i=0;i<qtFunc;i++){
        somaSalRel +=  inicio[i].salario;
    }
    fator = (double)somaSalario/somaSalRel;
    for(i=0;i<qtFunc;i++){
        inicio[i].salario = inicio[i].salario*fator;
    }
}
float logB2(float numero){
    float result;
    result=log10(numero)/log10(2); //conversao de base de logaritmos
    return result;
}
int logEstrela(int nivel){
    int result=0;
    if(nivel<=1){
        return 0;
    }
    else{
        result=1+logEstrela(ceil(logB2(nivel))); //ceil trunca o log na base dois para cima
        return result;
    }
}

void calcQualidade(dados *inicio, int qtFunc, int fatReg){
    int i;
    for(i=0;i<qtFunc;i++){
        inicio[i].qualidade =fatReg*(logEstrela(inicio[i].nivel)+1)*(inicio[i].prodRel/logB2(inicio[i].salario));
    }
}
//nivel de um funcionario é calculado a partir do nivel de seu chefe 
int nivel(dados *funcionario){
    int n=1;
    if(funcionario->chefe==NULL){
        return 1;
    }
    else{
        n = n + nivel(funcionario->chefe);
        return n;
    }
}
