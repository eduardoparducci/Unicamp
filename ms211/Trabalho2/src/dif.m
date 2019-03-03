% Arquivo: dif.m
% Parametro de entrada: real h representando o tamanho intervalo
% Saída: Matriz S contendo as seguintes colunas, em ordem [x , y]
% Escrito por: Eduardo Parducci, Lucas Koiti
% RA: 170272, 182579
% Última edição: 20/06/2017

function [S] = dif(h)

  % Variáveis auxiliares
  n = 1/h;
  M = zeros((n-1),(n-1));
  B = zeros((n-1),1);
  X = zeros((n-1),1);
    
  % Variável de saída
  S = zeros((n-1),2);

  % Constrói a matriz de coeficientes (M) e vetor solução (B)
  for(i = 1:rows(M))

    S(i,1) = i*h;
    M(i,i) = (h^2) - 2;

    if(i==1)
      B(i) = 2*(h^3) + (h^2)/2 - 1;
    else
      B(i) = 2*i*(h^3);
      M(i,i-1) = (1 - (i*h^2)/2);
    endif

    if(i < n-1)
      M(i,i+1) = (1 + (i*h^2)/2);
    endif
  
  end

  % Resolve o sistema linear
  X = M\B;

  for(i = 1:rows(S))
    S(i,2) = X(i);
  end

endfunction
