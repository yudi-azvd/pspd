# Lista 02 MPI: Soma de vetor distribuída

Distributed Array Sum (DAS).

Somar 2 vetores de 16 elementos cada

a) master inicializa os vetores de entrada A e B

b) os workers realizam somas parciais (cada worker soma uma porção do vetor)

c) master recebe as somas parciais e imprime o vetor resultante

## Execução

Execute com 

```sh
make n
mpirun -n <número de workers + 1> ./a.out
# exemplo: se você quiser 4 workers
mpirun -n 5 ./a.out
#  7 workers
mpirun -n 8 ./a.out
```

O `+1` é referente ao processo pai, sempre presente.


## Solução

Solução final em `das-n-workers.c`.

A informação central é o número de workers $W$ desejado para os quais deve-se 
distribuir a quantidade de trabalho $N$. Atualmente $N = 16$, hardcoded no 
código e guardado na variável `ARR_SIZE`. 

Se $W$ é par, a quantidade de trabalho é dividida igualmente entre cada 
trabalhador $w_i$. Cada $w_i$ fica responsável por $N / W$ unidades de trabalho.

Se $W$ é ímpar, a quantidade trabalho é dividida igualmente entre os primeiros
$W-1$ workers, esses continuam com $N/(W)$ unidades de trabalho e ao último
worker $w_{W}$ restam $N/(W) + N \bmod W$.

### Desvantages

Em algumas combinações de $N$ e $W$, as quantidades de trabalho entre workers 
podem ficar desbalanceadas. Tome por exemplo o caso $N=16$ e $W = 6$. Nessa 
situação, 5 
workers ficam com 2 unidades de trabalho enquanto o último worker fica com 6 
unidades: `5 * 2 + 1 * 6 = 16`. 

De fato, a implementação atual da divisão de trabalho de `das-n-workers.c`
é ineficiente.

E agora, o processo principal tem que receber as pedaços de array na ordem em
que foram enviados. Me parece indesejável.

### Possíveis melhorias

- Abstrair lógica de divisão de trabalho com structs e funções.
- Melhorar lógica de divisão de trabalho para que o trabalho fique mais 
balanceado entre workers
  - Ideia: 
    1. Enquanto existem unidades de trabalho. Se acabou: Fim
    2. Dá uma unidade pra um worker, 
    3. vai pro próximo. Ultimo worker?, volta pra 1.
    Existe alguma fórmula matemática pra isso? (hehe 3h da manhã, não tá fácil pensar)
- Generalizar o tamanho do vetor e fornecer os dados do vetor por arquivo ou
entrada padrão. Basicamente, fazer $N$ variável, não hardcoded.
- Fazer processo pai receber tamanho do que vai receber, assim como os worker 
fazem. Assim o processo pai pode receber os resultados em qualquer ordem.