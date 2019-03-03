#include "montador.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* protótipos das funções implementadas */
int validaDiretiva(char *palavra);
int validaDefRotulo(char *palavra);
int validaNum(char *palavra);
int validaNome(char *palavra);
int validaInstrucao(char *palavra);
int processaLinha(char *linha, unsigned indice);
int numerico(char c);
int alfanumerico(char letra);
int strtoken(char *linha, char tokens[][64]);

/* processarEntrada
 * Argumentos:
 *  entrada: cadeia de caracteres com o conteudo do arquivo de entrada.
 *  tamanho: tamanho da cadeia.
 * Retorno:
 *  1 - erro na montagem.
 *  0 - caso contrario.
 */
int processarEntrada(char* entrada, unsigned tamanho) {
  char linha[100+1];
  unsigned i,j,k;
  int erro;

  // contador de caracteres e linhas do arquivo de entrada, respectivamente
  j = k = 0;

  while(j<tamanho) {

    // recebe uma linha de entrada
    for(i=0 ; i<(tamanho-j) ; i++) {
      if(entrada[j+i]=='\n') {
        linha[i] = '\0';
        k++;
        break;
      }
      linha[i] = entrada[j+i];
    }
    j += (i+1);

    // remove comentarios
    for(i=0 ; i<strlen(linha) ; i++) {
      if(linha[i]=='#')
        linha[i] = '\0';
    }

    // ignora linhas em branco (somente espacos)
    for(i=0 ; i<strlen(linha) ; i++) {
      if(linha[i]!=' ')
        break;
    }

    // verifica se a linha possui conteudo a ser processado
    if(i!=strlen(linha)) {
      erro = processaLinha(linha,k);

      if(erro==1){
        fprintf(stderr,"ERRO GRAMATICAL: palavra na linha %d!\n", k);
        return 1;
      }
      if(erro==-1){
        fprintf(stderr,"ERRO LEXICO: palavra inválida na linha %d!\n", k);
        return 1;
      }
    }
  }
  //imprimeListaTokens();
  return 0;
}
/* processaLinha
 * Argumentos:
 *  entrada: cadeia de caracteres com o conteudo de uma linha de programação Assembly.
 *  indice: numero da linha a ser examinada.
 * Retorno:
 *  1 - erro gramatical.
 *  0 - erro lexico.
 */
int processaLinha(char *linha, unsigned indice) {
  char tokens[4][64];
  int ret,i;
  Token novoToken;

  // inicia com strings vazias
  for(i=0 ; i<4 ; i++){
    tokens[i][0] = '\0';
  }

  // erro gramatical - argumentos excessivos por linha (strtoken retornou NULL)
  if(!strtoken(linha,tokens))
    return 1;

  i = 0;
  while(tokens[i][0]!='\0') {
    novoToken.linha = indice;
    novoToken.palavra = (char *) malloc(strlen(tokens[i])*sizeof(char));
    strcpy(novoToken.palavra,tokens[i]);

    // ROTULO
    ret = validaDefRotulo(tokens[i]);
    if(ret==1) {
      if(i!=0) {
        // erro gramatical - nao esta no inicio da linha
        free(novoToken.palavra);
        return 1;
      }
      // rotulo valido
      novoToken.tipo = DefRotulo;
      adicionarToken(novoToken);
      i++;
      continue;
    } else if(ret==-1){
      // erro lexico - rotulo invalido
      free(novoToken.palavra);
      return -1;
    }

    // DIRETIVA
    ret = validaDiretiva(tokens[i]);
    if(ret==1) {
      if(i>1) {
        //erro gramatical - nao esta em uma posicao valida da linha
        free(novoToken.palavra);
        return 1;
      }
      if(!strcmp(tokens[i],".set") && validaNome(tokens[i+1]) && validaNum(tokens[i+2])) {
        //diretiva valida
        novoToken.tipo = Diretiva;
        adicionarToken(novoToken);
        i++;
        continue;
      }
      else if(!strcmp(tokens[i],".org") && validaNum(tokens[i+1])) {
        //diretiva valida
        novoToken.tipo = Diretiva;
        adicionarToken(novoToken);
        i++;
        continue;
      }
      else if(!(strcmp(tokens[i],".align") && strcmp(tokens[i],".wfill")) && validaNum(tokens[i+1])==1) {
        //diretiva valida
        novoToken.tipo = Diretiva;
        adicionarToken(novoToken);
        i++;
        continue;
      }
      else if( !strcmp(tokens[i],".word") && (validaNum(tokens[i+1])||validaNome(tokens[i+1])) ) {
        //diretiva valida
        novoToken.tipo = Diretiva;
        adicionarToken(novoToken);
        i++;
        continue;
      }
      else {
        //erro gramatical - parametros invalidos
        free(novoToken.palavra);
        return 1;
      }
    } else if(ret==-1) {
      //erro lexico - diretiva invalida

      free(novoToken.palavra);
      return -1;
    }

    // INSTRUÇÃO
    ret = validaInstrucao(tokens[i]);
    if(ret==1) {

      // remove aspas do parametro
      strtok(tokens[i+1],"\"");
      for(int a=0 ; a<strlen(tokens[i+1]) ; a++) tokens[i+1][a]=tokens[i+1][a+1];

      if(i>1) {
        //erro gramatical - nao esta em uma posicao valida da linha
        free(novoToken.palavra);
        return 1;
      }
      if( !(strcmp(tokens[i],"LOADMQ") && strcmp(tokens[i],"RSH") && strcmp(tokens[i],"LSH")) ) {
        if( tokens[i+1][0]!='\0' ) {
          //erro gramatical - parametros excessivos p/ instrucoes
          free(novoToken.palavra);

          return 1;
        }
        else {
          // instrucao valida
          novoToken.tipo = Instrucao;
          adicionarToken(novoToken);
          i++;
          continue;
        }

      } else if( !((tokens[i][0]!='J') && strcmp(tokens[i],"STORA")) ) {
        // instrucao valida
        novoToken.tipo = Instrucao;
        adicionarToken(novoToken);
        i++;
        continue;
      } else if(validaNum(tokens[i+1]) || validaNome(tokens[i+1])) {
        // instrucao valida
        novoToken.tipo = Instrucao;
        adicionarToken(novoToken);
        i++;
        continue;
      } else {
        //erro gramatical - parametros invalidos
        free(novoToken.palavra);
        return 1;
      }
    } else if(ret==-1) {
      //erro lexico - instrucao invalida

      free(novoToken.palavra);
      return -1;
    }

    // NOME
    ret = validaNome(tokens[i]);
    if(ret==1) {
      if(i==0) {
        //erro gramatical - posicao invalida na linha
        free(novoToken.palavra);
        return 1;
      }
      // nome valido
      novoToken.tipo = Nome;
      adicionarToken(novoToken);
      i++;
      continue;
    } else if(ret==-1) {
      //erro lexico - nome invalido

      free(novoToken.palavra);
      return -1;
    }

    // NUMERAL
    ret = validaNum(tokens[i]);
    if(ret==1) {
      if(i==0) {
        //erro gramatical - posicao invalida na linha
        free(novoToken.palavra);
        return 1;
      }
      //decimal valido
      novoToken.tipo = Decimal;
      adicionarToken(novoToken);
      i++;
      continue;
    } else if(ret==-1) {
      if(i==0) {
        //erro gramatical - posicao invalida na linha
        free(novoToken.palavra);
        return 1;
      }
      // hexadecimal valido
      novoToken.tipo = Hexadecimal;
      adicionarToken(novoToken);
      i++;
      continue;
    }

    else {
      //erro lexico - nao foi reconhecido como um tipo de toke
      free(novoToken.palavra);
      return -1;
    }
  }
  return 0;
}
/* validaNum: Verifica se uma string contém um numero e o classifica como HEX ou DEC
 * Argumentos:
 *  palavra: string a ser analisada
 * Retorno:
 *   1 - Decimal
 *   0 - Erro (não numerico)
 *  -1 - Hexadecimal
 */
int validaNum(char *palavra) {
  int i;
  for(i=0 ; i<strlen(palavra) ; i++)
  {
    if(numerico(palavra[i]))
      continue;

    else if( (palavra[1]=='x' || palavra[1]=='X') ){
      if(i==1)
        continue;
      else if(i>1 && ((palavra[i]>='a' && palavra[i]<='f') || (palavra[i]>='A' && palavra[i]<='F')) )
        continue;
    }
    return 0;
  }
  if(palavra[1]=='x' || palavra[1]=='X')
    return -1;
  else
    return 1;
}
/* validaDefRotulo: Verifica a sintaxe de uma definicao de rotulo: alfanumerico não iniciado com numeral. Exceto ultimo caractere ':'
 * Retorno:
 * 1 - Definicao de Rotulo válido
 * 0 - Definicao de Rotulo inválido
 */
int validaDefRotulo(char *palavra) {
  int i;
  if(palavra[strlen(palavra)-1]==':'){
    // erro lexico - numeral no inicio
    if(numerico(palavra[0]))
      return -1;

    for(i=0 ; i<(strlen(palavra)-1) ; i++){
      // erro lexico - nao possui caracteres alfanumericos
      if(!alfanumerico(palavra[i]))
        return -1;
    }
    return 1;
  }
  return 0;
}
/* validaDiretiva: verifica se 'palavra' contem uma diretiva sintaticamente valida
 * Retorno:
 * 0 - Diretiva inválida
 * 1 - Diretiva válida
 */
int validaDiretiva(char *palavra) {
  const char *diretivas[5] = {".set",".org",".align",".wfill",".word"};
  int i;

  // procura ocorrencia de 'diretiva' em 'diretivas'
  for(i=0 ; i<5 ; i++) {
    if(!strcmp(diretivas[i],palavra))
      return 1;
  }
  return 0;
}
/* validaNome: verifica se 'palavra' contem uma definicao de nome válida: alfanumerico nao inicado com numeral
 * Retorno:
 * 0 - Nome inválido
 * 1 - Nome válido
 */
int validaNome(char *palavra) {
  int i;

  if(numerico(palavra[0]))
    return 0;

  for(i=0 ; i<strlen(palavra) ; i++)
    if(!alfanumerico(palavra[i]))
      return 0;

  return 1;
}
/* validaInstrucao: verifica se palavra é um mnemonico válido
 * Retorno:
 * 0 - mnemonico inválida
 * 1 - mnemonico válida
 */
int validaInstrucao(char *palavra) {
  const char *mnemonicos[17] = {"LOAD","LOAD-","LOAD|","LOADMQ","LOADmq_mx","STOR","JUMP","JMP+","ADD","ADD|","SUB","SUB|","MUL","DIV","LSH","RSH","STORA"};
  int i;

  // procura ocorrencia de 'palavra' em 'mnemonicos'
  for(i=0 ; i<17 ; i++)
    if(!strcmp(mnemonicos[i],palavra))
	     return 1;
  return 0;
}
/* numerico: Verifica se char 'c' é numeral
 * Retorno:
 * 0 - não numeral
 * 1 - caso contrario
 */
int numerico(char c) {
  if( (((int)c)>=48) && (((int)c)<=57) )
    return 1;

  return 0;
}
/* alfanumerico: Verifica se 'letra' contem um valor alfanumerico ou '_'
 * Retorno:
 *  0 - Erro (nao alfanumerico)
 *  1 - Caso contrario
 */
int alfanumerico(char letra) {
  if(numerico(letra))
    return 1;
  if( ((int)letra>=65) && ((int)letra<=90) ) //{a-z}
    return 1;
  if( ((int)letra>=97) && ((int)letra<=122) ) //{A-Z}
    return 1;
  if(letra=='_')
    return 1;
  return 0;
}
/* strtoken: recebe uma linha de instrucao Assembly e a divide em tokens, separados por ' 's ou '\t'
 * Argumentos:
 * linha: linha de instrucao a ser processada
 * tokens: matriz que será carregada con os tokens contidos em 'linha'
 * Retorno:
 * 1 - Caso 'linha' contenha uma quantidade válida de tokens
 * 0 - Caso contrário
 */
int strtoken(char *linha,char tokens[][64]) {
  int i=0;
  char *aux = strtok(linha," \"\t");

  while( aux && i<4 ) {
      strcpy(tokens[i],aux);
      i++;
      aux = strtok(NULL," \t");
  }
  if(i>=4)
    return 0;
  return 1;
}
