#!/bin/bash
echo "Digite o nome da atividade (Ex:LabSala00c):"
read NomeAtv
echo "Digite o nome do programa (Ex:Atividade1.c)":
read NomeProg
echo "Digite o diretorio onde serao salvos os arquivos (Ex:/home/ra123456/...), caso seja o diretorio atual digite pwd:"
read Diretorio
if [ "$Diretorio" = "pwd" ]; then
	Diretorio=$(pwd)
fi

mkdir $Diretorio/TesteSuSy
gcc $NomeProg -o $NomeAtv
mv $NomeAtv $Diretorio/TesteSuSy
cd $Diretorio/TesteSuSy


#Faz o download dos arquivos do SuSy
for i in `seq 1 6`
do
	curl -k https://susy.ic.unicamp.br:9999/mc102abcd/$NomeAtv/dados/arq0$i.in >> arq0$i.in
	curl -k https://susy.ic.unicamp.br:9999/mc102abcd/$NomeAtv/dados/arq0$i.res >> arq0$i.res
done


#Testa o programa com as entradas do SuSy
Teste=("1" "2" "3" "4" "5" "6")
Resultado=("VERIFICAR1" "VERIFICAR2" "VERIFICAR3" "VERIFICAR4" "VERIFICAR5" "VERIFICAR6")

for i in `seq 1 6`
do
	./$NomeAtv < "arq0$i.in" > "arq0$i.out"
	Teste[(($i - 1))]=$(diff arq01.out arq01.res)
done


echo "+----------------------------------------+"
for i in `seq 1 6`
do
	echo "| Teste $i .....................${Resultado[(($i - 1))]}   |"
done
echo "+----------------------------------------+"
