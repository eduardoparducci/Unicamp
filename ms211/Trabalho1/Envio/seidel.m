% Arquivo: seidel.m
% Descrição:Esta função tem como objetivo resolver um sistema linear da forma
%           AX=B exibindo o resultado X e o número de iterações k através do
%           método a seguir:
% Método: Gauss-Seidel
% Parâmetros de entrada: (Matriz A, Vetor B)
% Saída: [Vetor X, número de iterações k]
% Escrito por: Eduardo Parducci, Lucas Koiti
% RAs: 170272, 182579
% Última edição: 27/04/2017

function [X,k] = seidel(A,B)

  % Variáveis de saída
  X = zeros(columns(A),1); % Inicia com uma solução nula
  k = 0;

  % Variáveis auxiliares
  e = 0.0001; % Erro utilizado como critério de parada
  continua = true;

  while(continua)

    % Cria uma cópia com o estado anterior de X (para ver as iterações basta remover o ';' da linha seguinte)
    ant = X;

    % Itera sobre a matriz dos coeficientes (A)
    for(i = 1:rows(A))
      X(i) = 0;
      for(j = 1:columns(A))
        if(i!=j)
          X(i) -= A(i,j)*X(j);
        endif
      end
      X(i) = (X(i)+B(i)) / A(i,i);
    end

    % Verifica se o resultado ja convergiu
    if(max(abs(X-ant))/max(abs(X)) <= e)
      continua = false;
    else
      continua = true;
    endif

    % Incrementa contador de iterações
    k += 1;

  end

  % Remova o comentario abaixo para exibir o resultado de maneira formatada
  %{
  clc;
  printf("Solucao do sistema AX=B com precisao de %0.0e:\n", e);
  printf("X={%.2f",X(1));
  for(i = 2:rows(X))
    printf(" ; %.2f", X(i));
  end
  printf("}\nNumero de iteracoes: %i\n", k);
  %}

endfunction
