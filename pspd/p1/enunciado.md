# Prova 1

## Questão 7
Usando OpenMP

Fazer o programa imprimir um vetor de 100 posições em ordem. Inicie o vetor
com `v[i] = i`.

Offset dinâmico para cada thread:

Exemplo: a thread anterior fez a última impressão no item 18, a thread tem um 
offset dinâmico de 3. Então a thread atual deve imprimir os itens 19, 20, 21.

## Questão 8
Usando MPI.

O processo master inicia uma matriz 4x4 e deve orquestrar a soma das matrizes A 
e B com o auxílio de dois processos filhos. O processo filho 1 deve somar as 
colunas 1 e 3 enquanto o processo filho 2 deve somar as colunas 2 e 4.

No final o processo master deve imprimir a matriz em forma de colunas.