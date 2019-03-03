% Arquivo:  jacobi.m
% Descrição:Esta função tem como objetivo resolver um sistema linear da forma
%           AX=B exibindo o resultado X e o número de iterações k através do
%           método a seguir:
% Método: Gauss-Jacobi
% Parâmetros de entrada: (Matriz A  ,Vetor B)
% Saída: [Vetor X, número de iterações k]
% Escrito por: Eduardo Parducci, Lucas Koiti
% RA: 170272, 182579
% Última edição: 26/04/2017

function [X,k] = jacobi(A,B)

  % Variáveis de saída
  X = zeros(columns(A),1); % Inicia com uma solução nula
  k = 0;

  % Variáveis auxiliares
  e = 0.0001; % Erro utilizado como critério de parada
  aux = X;    % Vetor auxiliar para registro do estado anterior
  continua = true;

  while(continua)

    % Inicia vetor auxiliar nulo
    aux = zeros(columns(A),1);

    % Percorre a matriz dos coeficientes (A)
    for(i = 1:rows(A))
      for(j = 1:columns(A))
        if(i!=j)
          aux(i) -= A(i,j)*X(j);
        endif
      end
      aux(i) = (aux(i)+B(i)) / A(i,i);
    end

    % Verifica se o resultado ja convergiu
    if(max(abs(aux-X))/max(abs(aux)) <= e)
      continua = false;
    else
      continua = true;
    endif

    %Atualiza o vetor X (para ver as iterações remova o ';' da linha seguinte)
    X = aux;

    % Incrementa contador de iterações
    k += 1;

  end

  % Remova o comentário abaixo para exibir o resultado de maneira formatada
  %{
  clc;
  printf("Solucao do sistema AX=B com uma precisao de %.0e:\n", e);
  printf("X={%.2f",X(1));
  for(i = 2:rows(X))
    printf(" ; %.2f", X(i));
  end
  printf("}\nNumero de iteracoes: %i\n", k);
  %}

endfunction
