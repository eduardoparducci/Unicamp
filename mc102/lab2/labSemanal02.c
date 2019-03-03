#include<stdio.h>

int main(void){
	//valores maximos(1000 e -1000) atribuidos as variaveis minimas (xMin e yMin) e vice-versa para calcular as coordenadas de maximo e minimo a partir da 1a entrada
	double xMax=-1000, xMin=1000, yMax=-1000, yMin=1000, x0, x1, x2, y0, y1, y2, areaIlhas,volAgua, det=0, precoGalao, precoTot;
	int i,j,k, qtdeIlhas, qtdeEventos=0, anoFinal, qtdeFornec, diaAniversario, mesAniversario, cpGalao,qtdeDiasMes=31, qtdeDias=0;;
	/*-------------------------------VOLUME-DE-AGUA-DA-MAQUETE--------------------------------------------------*/	
	scanf("%i", &qtdeIlhas);
	for(i=0;i<qtdeIlhas;i++){
		scanf(" (%lf , %lf) ", &x0, &y0);	//primeira coordenada
		scanf(" (%lf , %lf) ", &x1, &y1);	//segunda coordenada
		if(x0>xMax)							//inicio verificação de max e min 
			xMax=x0;
		if(x0<xMin)
			xMin=x0;
		if(y0>yMax)
			yMax=y0;
		if(y0<yMin)
			yMin=y0;
		if(x1>xMax)
			xMax=x1;
		if(x1<xMin)
			xMin=x1;
		if(y1>yMax)
			yMax=y1;
		if(y1<yMin)
			yMin=y1;						//fim da verificação de max e min
		while(1){
			scanf(" (%lf , %lf)", &x2, &y2);//terceira coordenada
			if(x2>xMax)						//inicio verificação de max e min
				xMax=x2;
			if(x2<xMin)
				xMin=x2;
			if(y2>yMax)
				yMax=y2;
			if(y2<yMin)
				yMin=y2;					//fim verificação de max e min
			if(x2==x0 && y2==y0)
				break;
											//calculo da area dividindo o poligono em triangulos
			det = (x0*y1 + x2*y0 + x1*y2 - x2*y1 - x0*y2 - x1*y0);
			if(det<0)						//pega o modulo do determinante
				det = det*(-1);
			areaIlhas=areaIlhas + (det/2.0);	
			x1=x2;
			y1=y2;
		}
	}
	volAgua = ((((xMax-xMin)+1)*((yMax-yMin)+1))-areaIlhas)*500;	//(area total)-(area das ilhas)*0,5m de prof. * 1000 para converter em litros
	/*------------------------------------------QUANTIDADE-DE-EVENTOS-------------------------------------------*/
	scanf("%d/%d", &diaAniversario, &mesAniversario);
	scanf("%d", &anoFinal);
	//calcula a quantidade de eventos baseado no aniversario da cidade
	if(diaAniversario==29 && mesAniversario==2){
		for(i=0;i<(anoFinal-2015);i++){		//conta a qtde de anos bissextos caso o aniversario seja 29/02
			if((((2016+i)%4==0) && ((2016+i)%100!=0)) || ((2016+i)%400==0))
				qtdeEventos++;;			
		}
	}
	else{
		for(i=0;i<(anoFinal-2015);i++){
			qtdeEventos++;
		}
	}
	//calcula a qtde de sextas feiras 13 
	for(i=0;i<(anoFinal-2015);i++){
		for(j=1;j<=12;j++){
			if(j==2){	//FEVEREIRO
				if((((2016+i)%4==0) && ((2016+i)%100!=0)) || ((2016+i)%400==0))	//BISSEXTO
					qtdeDiasMes=29;
				else
					qtdeDiasMes=28;
			}
			else if(j<=7){	//ATE JULHO
				if(j%2==0)
					qtdeDiasMes=30;
				else
					qtdeDiasMes=31;
			}
			else if(j>7){	//A PARTIR DE AGOSTO
				if(j%2==1)	//MES PAR									
					qtdeDiasMes=30;
				else
					qtdeDiasMes=31;
			}
			for(k=1;k<=qtdeDiasMes;k++){
				qtdeDias++;
				if((k)==13 && qtdeDias%7==1){
					qtdeEventos++;
				}
				if(diaAniversario==12 && k==12 && mesAniversario==j && qtdeDias%7==0){
					qtdeEventos--;
				}					
			}
		}
	}
	
	/*--------------------------------------------SELECIONA-FORNECEDOR--------------------------------------------*/
	scanf("%d ", &qtdeFornec);
	scanf("%d $%lf", &cpGalao, &precoGalao);
	if(volAgua>(int)volAgua){		//Arredonda o num. de litros para cima e calcula o preco tot
		precoTot=((int)(((int)volAgua+1)/cpGalao)+1)*precoGalao*qtdeEventos;
	}
	else{
		precoTot=((int)(((int)volAgua)/cpGalao)+1)*precoGalao*qtdeEventos;
	}
	for(i=0;i<(qtdeFornec-1);i++){
		scanf("%d $%lf", &cpGalao, &precoGalao);
		if(volAgua>(int)volAgua){
			if(precoTot>(((int)volAgua+1)/cpGalao)*precoGalao*qtdeEventos)
				precoTot=((int)(((int)volAgua+1)/cpGalao)+1)*precoGalao*qtdeEventos;
		}
		else{
			if(precoTot>(((int)volAgua)/cpGalao)*precoGalao*qtdeEventos)
				precoTot=((int)(((int)volAgua)/cpGalao)+1)*precoGalao*qtdeEventos;
		}	
	}
	printf("A manutencao da maquete custara $%.2lf aos cofres publicos.\n", precoTot);
	return 0;
}
