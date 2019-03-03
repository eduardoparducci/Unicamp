#include<stdio.h>
#include<string.h>
#include<math.h>

typedef char string[200];
typedef struct{
	short int dia;
	short int mes;
	short int ano;
}data;

typedef struct{
	short int *nota;
	float media; 	//media geometrica da afinidade de duas pessoas
}aresta;

typedef struct{
	string nome;
	data aniversario;
	char sexo;
	char pref;
	short int afinidade[39];
	aresta conexao[40];
	short int qtConexoes;
}vertice;

int main(void){
	vertice aluno[40]; 	//dados referentes a todos os que preencheram o formulario
	data formulario;
	int qtAlunos, i, j;

	for(i=0;i<40;i++){ 	//zera a qtde de conexoes de todas as pessoas
		aluno[i].qtConexoes = 0;
	}

	scanf("%hd/%hd/%hd", &formulario.dia, &formulario.mes, &formulario.ano);
	scanf("%d", &qtAlunos);
	for(i=0;i<qtAlunos;i++){
		scanf("%s", aluno[i].nome);
		scanf("%hd/%hd/%hd %c %c", &aluno[i].aniversario.dia, &aluno[i].aniversario.mes, &aluno[i].aniversario.ano, &aluno[i].sexo, &aluno[i].pref);
		for(j=0;j<(qtAlunos-1);i++){
			scanf(" %hd", &aluno[i].afinidade[j]);
		}

	}

	for(i=0;i<qtAlunos;i++){ 	//pessoa a ser analisada
		for(j=0;j<qtAlunos;j++){ 	//restante das pessoas
			if(j!=i){ 		//desconsidera a combinacao de uma pessoa com ela mesma
				if(i<j){ 	//deslocar a posicao do vetor um a menos
					aluno[i].conexao[j].media = sqrt(aluno[i].afinidade[j-1] * aluno[j].afinidade[i]);
				}
				if(i>j){ 	//posicao do vetor original
					aluno[i].conexao[j].media = sqrt(aluno[i].afinidade[j] * aluno[j].afinidade[i-1]);
				}
			}
		}
	}

	for(i=0;i<qtAlunos;i++){
		for(j=0;j<qtAlunos;j++){
			if(j!=i){
				printf("A media geometrica entre a pessoa %d e %d eh: %f", i, j, aluno[i].conexao[j].media);
			}
		}

	}
	return 0;
}
