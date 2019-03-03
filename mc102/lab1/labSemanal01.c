#include <stdio.h>
#include<stdlib.h>
#include<math.h>

/*	Desenvolvido por: Eduardo Parducci		RA:170272		Turma:S
	Este programa recebe uma data, dois numeros inteiros que expressam um modelo de calendario personalizado, modificando a quantidade de dias contidas em um mes e a quantidade de meses contidos em um ano. Por fim, recebe um ultimo numero (x), expresso na base 6.
	O programa calcula, a soma da data inserida com o o numero x, no formato de calendario personalizado definido pelo usuario anteriormente. 
*/

int main(void)
{
	 int diaAcesso, mesAcesso, anoAcesso, diaEvento, mesEvento, anoEvento, qtdeDiasMes, qtdeMesesAno, diasRestantes, acrescimoDias, acrescimoMeses, acrescimoAnos;

	scanf("%i/%i/%i %i %i %i", &diaAcesso, &mesAcesso, &anoAcesso, &qtdeDiasMes, &qtdeMesesAno, &diasRestantes);

	//converte da base 6 para a base 10
	diasRestantes=
		(diasRestantes%10)*pow(6,0)+
		(((diasRestantes%100)-(diasRestantes%10))/10)*pow(6,1)+
		(((diasRestantes%1000)-(diasRestantes%100))/100)*pow(6,2)+
		(((diasRestantes%10000)-(diasRestantes%1000))/1000)*pow(6,3)+
		(((diasRestantes%100000)-(diasRestantes%10000))/10000)*pow(6,4)+
		(((diasRestantes%1000000)-(diasRestantes%100000))/100000)*pow(6,5)+
		(((diasRestantes%10000000)-(diasRestantes%1000000))/1000000)*pow(6,6)+
		(((diasRestantes%100000000)-(diasRestantes%10000000))/10000000)*pow(6,7);
	
	//Remove o bug de inicio de contagem de mes e ano com 0 (zero)
	diaAcesso--;
	mesAcesso--;
	//verifica a quantidade de dias, meses e anos de acordo com o novo modelo de calendario
	acrescimoDias=(diasRestantes%qtdeDiasMes);
	acrescimoMeses=(diasRestantes/qtdeDiasMes)%qtdeMesesAno;
	acrescimoAnos=(diasRestantes/qtdeDiasMes)/qtdeMesesAno;

	//soma o dia, mes e ano da data de entrada com os respectivos dias, meses e anos do numero x  
	diaEvento=acrescimoDias+diaAcesso;
	mesEvento=acrescimoMeses+mesAcesso;
	anoEvento=acrescimoAnos+anoAcesso;
	//verifica se a qtde de dias e meses excedeu o limite imposto pelo formato de calendario fornecido e realiza o ajuste necessario
	acrescimoMeses=diaEvento/qtdeDiasMes;
	mesEvento=mesEvento+acrescimoMeses;
	acrescimoAnos=mesEvento/qtdeMesesAno;
	anoEvento=anoEvento+acrescimoAnos;
	diaEvento=diaEvento%qtdeDiasMes;
	mesEvento=mesEvento%qtdeMesesAno;
	
	//Remove o bug de inicio de contagem de mes e ano com 0 (zero)
	diaEvento++;
	mesEvento++;
	printf("%i/%i/%i\n",diaEvento,mesEvento,anoEvento);
	return 0;
}
