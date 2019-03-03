function [Sol_jacobi,k_jacobi,Sol_seidel,k_seidel] = resolve(A,B)

  % Variáveis de saída
  Sol_jacobi = zeros(columns(A),1); % Inicia com uma solução nula
  k_jacobi = 0;
  Sol_seidel = zeros(columns(A),1); % Inicia com uma solução nula
  k_seidel = 0;

  % Variáveis auxiliares
  e = 0.0001; % Erro utilizado como critério de parada
  aux = Sol_jacobi;    % Vetor auxiliar para registro do estado anterior
  continua = true;

  % Resolve com o método de jacobi
  while(continua)

    % Inicia vetor auxiliar nulo
    aux = zeros(columns(A),1);

    % Percorre a matriz dos coeficientes (A)
    for(i = 1:rows(A))
      for(j = 1:columns(A))
        if(i!=j)
          aux(i) -= A(i,j)*Sol_jacobi(j);
        endif
      end
      aux(i) = (aux(i)+B(i)) / A(i,i);
    end

    % Verifica se o resultado ja convergiu
    if(max(abs(aux-Sol_jacobi))/max(abs(aux)) <= e)
      continua = false;
    else
      continua = true;
    endif

    %Atualiza o vetor Sol_jacobi (para ver as iterações remova o ';' da linha seguinte)
    Sol_jacobi = aux;

    % Incrementa contador de iterações
    k_jacobi += 1;

  end

  % Remova o comentário abaixo para exibir o resultado de maneira formatada
  %{
  clc;
  printf("Jacobi:\nSolucao do sistema AX=B com uma precisao de %.0e:\n", e);
  printf("Sol_jacobi={%.2f",Sol_jacobi(1));
  for(i = 2:rows(Sol_jacobi))
    printf(" ; %.2f", Sol_jacobi(i));
  end
  printf("}\nNumero de iteracoes: %i\n", k);
  %}

  % Resolve com o método de seidel
  while(continua)

    % Cria uma cópia com o estado anterior de Sol_seidel (para ver as iterações basta remover o ';' da linha seguinte)
    ant = Sol_seidel;

    % Itera sobre a matriz dos coeficientes (A)
    for(i = 1:rows(A))
      Sol_seidel(i) = 0;
      for(j = 1:columns(A))
        if(i!=j)
          Sol_seidel(i) -= A(i,j)*Sol_seidel(j);
        endif
      end
      Sol_seidel(i) = (Sol_seidel(i)+B(i)) / A(i,i);
    end

    % Verifica se o resultado ja convergiu
    if(max(abs(Sol_seidel-ant))/max(abs(Sol_seidel)) <= e)
      continua = false;
    else
      continua = true;
    endif

    % Incrementa contador de iterações
    k_seidel += 1;

  end

  % Remova o comentario abaixo para exibir o resultado de maneira formatada
  %{
  clc;
  printf("Seidel:\nSolucao do sistema ASol_seidel=B com precisao de %0.0e:\n", e);
  printf("Sol_seidel={%.2f",Sol_seidel(1));
  for(i = 2:rows(Sol_seidel))
    printf(" ; %.2f", Sol_seidel(i));
  end
  printf("}\nNumero de iteracoes: %i\n", k_seidel);
  %}

endfunction
