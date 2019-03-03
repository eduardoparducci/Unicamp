//Desenvolvido por: Eduardo Parducci RA:170272 Descrição:manipulação de matriz triangular

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main(void){
    
    unsigned short int ordem, qtde, i, j;
    double **matriz=NULL, media=0, sigma=0;  //sigma - desvio padrao
    
    scanf("%hu", &ordem);
    qtde=(pow(ordem,2)+ordem)/2;
    
    /*---aloca-as-linhas-da-jagged-array---*/
    matriz = (double **)malloc(ordem * sizeof(double *));
    
    /*---recebe-dados-e-calculo-da-media---*/
    for(i=0;i<ordem;i++){
        matriz[i] = (double *)malloc((i+1) * sizeof(double)); //aloca-colunas-da-jagged-array
        for(j=0;j<ordem;j++){
            scanf("%lf", &matriz[i][j]);
            media += matriz[i][j];
            if(j==i)
                break;
        }
    }
    media = media/qtde;
    
    /*---calculo-desvio-padrao---*/
    for(i=0;i<ordem;i++){
        for(j=0;j<ordem;j++){
            sigma += pow((matriz[i][j]-media),2);
        if(j==i)
            break;
        }
    }
    sigma = sqrt(sigma/qtde);
    
    /*---exibe-resultados---*/
    for(i=0;i<ordem;i++){
        for(j=0;j<ordem;j++){
            printf("%.12lf ", ((matriz[i][j]-media)/sigma));
            if(j==i)
                break;
        }
        putchar('\n');
    }
    printf("\n%.12lf %.12lf \n",media,sigma);
    free(matriz);
    return 0;
}