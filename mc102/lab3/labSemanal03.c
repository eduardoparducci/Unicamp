#include<stdio.h>
#include<math.h>
/*  Desenvolvido por: Eduardo Parducci  RA:170272   Turma: S
    Este programa simula a aplicação de um filtro em uma imagem recebida de maneira compactada (metodo RLE). Após descompactada,
    cada camada (RGB) da imagem é processada separadamente para gerar uma imagem em branco e preto atraves do calculo da media aritmetica das intensidades de cada camada.
    Apos calculada a imagem em branco e preto, um filtro é aplicado atraves de uma matriz que modifica o valor dos pixels de acordo com seus pixels adjacentes.
*/
unsigned char foto[360000][5];  //variavel global representando as camadas: RGB(camadas 3, 4 e 5), branco e preto(camada 2) e a foto com filtro aplicado (camada 1) 
void descompressao(int, int);   //funcao utilizada na descompressao da imagem

int main(void){
    short int pixelFiltro=0, dimMatrizFiltro;
    int i, j, k, l, resolucao, altura, comprimento, divisorFiltro, filtro[9][9];
    scanf("%d", &divisorFiltro);
    scanf("%hd", &dimMatrizFiltro);
    for(i=0;i<dimMatrizFiltro;i++){
        for(j=0;j<dimMatrizFiltro;j++){
            scanf("%d", &filtro[i][j]);
        }
    }
    scanf("%d %d", &comprimento, &altura);
    resolucao=altura*comprimento;
    descompressao(resolucao, 2);    //CAMADA R - FOTO[*][2]
    descompressao(resolucao, 3);    //CAMADA G - FOTO[*][3]
    descompressao(resolucao, 4);    //CAMADA B - FOTO[*][4]
    //CALCULA A FOTO EM BRANCO E PRETO
    for(i=0;i<resolucao;i++)
        foto[i][1]=(foto[i][2]+foto[i][3]+foto[i][4])/3;    //FOTO[*][1] CAMADA EM BRANCO E PRETO
    //APLICA O FILTRO NA CAMADA FOTO[*][0]
    for(i=0;i<altura;i++){
        for(j=0;j<comprimento;j++){
            //verifica se o pixel está na extremidade da matriz
            if(i>=dimMatrizFiltro/2 && j>=dimMatrizFiltro/2 && i<altura-dimMatrizFiltro/2 && j<comprimento-dimMatrizFiltro/2){  
                for(k=0;k<dimMatrizFiltro;k++){
                    for(l=0;l<dimMatrizFiltro;l++){
                        pixelFiltro+=foto[(j-(dimMatrizFiltro/2 - l)+(i*comprimento)-(dimMatrizFiltro/2-k)*comprimento)][1]*filtro[k][l];
                    }
                }
                pixelFiltro=pixelFiltro/divisorFiltro;
                if(pixelFiltro<0)   //trunca o numero para 0 caso seja <0
                    pixelFiltro=0;
                if(pixelFiltro>255) //trunca o numero para 255 caso seja >255
                    pixelFiltro=255;
                foto[(comprimento*i)+j][0] = pixelFiltro;
                pixelFiltro=0;
            }
            else
                foto[(comprimento*i)+j][0] = foto[(comprimento*i)+j][1];
        }
    }
    printf("P2\n%hd %hd\n255\n", comprimento, altura);
    for(i=0;i<altura;i++){
        for(j=0;j<comprimento;j++){
            printf("%d ", (int)foto[(comprimento*i)+j][0]); //exibe a foto com filtro aplicado       
        }
        putchar('\n');
    }
    return 0;
}
void descompressao(int resolucao, int camada){
    int frequencia, intensidade, i=0, j=0;
    while(i<resolucao){
        scanf("%d %d ", &frequencia, &intensidade);
        while(j<(frequencia+i)){
            foto[j][camada]=intensidade;
            j++;
        }
        i+=frequencia;
    }
}