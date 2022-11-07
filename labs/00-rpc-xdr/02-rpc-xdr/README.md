1) Proceda as seguintes alterações no programa acima:

a. Altere o número e versão do programa e os números das funções no arquivo 
calcula.x, execute o rpcgen
para que novos arquivos sejam gerados e veja que modificações ocorreram nos nomes das funções em cada um dos
arquivos. Gere novos binários e coloque o módulo servidor para executar. Verifique com o comando rpcinfo –p se novo
número de program e versão estão registrados no rpcgen

b. Altere o programa acima inserindo as funções MULT e DIV, responsáveis por retornar, respectivamente o
produto e a divisão entre os dois números informados pelo usuário. Obs.: Considerar N1 e N2 > 0.

2) Verifique o procedimento ulookup.c e altere-o para que funcione de acordo com a arquitetura RPC Cliente/Servidor.
Verifique a localização desse arquivo com o professor. Monte um relatório contendo o código do cliente e do servidor e as
modificações feitas, incluindo o arquivo IDF usado para o rpcgen (.x)

3) Faça um procedimento RPC Cliente/Servidor no qual o cliente passe para o servidor uma frase a ser apresentada
na tela pelo servidor. Verifique o arquivo hello.x para referência. Monte um relatório contendo o código original, a interface
IDF justificando o tipo de dados, e os códigos do cliente e servidor alterado.