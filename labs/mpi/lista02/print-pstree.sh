# Imprime a árvore de processos a partir de a.out
# com os PIDs decada processo.

# ps -x --forest | grep a.out | grep -v 'grep' | sed -E 's/^([\s]+?[0-9]+)(.*)/\1/'
# se estiver rodando em watch, é só salvar e comando é atualizado.

# executar com watch -d -n 0.5 ./print-process-tree.c
ps -x --forest | grep "a.out\|main.out" | grep -v 'grep' |
  sed -E "s/^(\s+?[0-9]+)(.*\s+\|)(.*)/\1 ->\3/"
