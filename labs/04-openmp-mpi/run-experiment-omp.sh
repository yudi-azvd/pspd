nworkers=$1
nlines=$2
program=$3
# Se não houber 4° argumento, use 10 como padrão
trials="${4:-10}"

echo "Running ${program} in $trials trials with ${nworkers} workers and ${nlines} lines"

file="report.txt"

> $file

for ((i=1; i<=$trials; i++))
do 
    # Se uma máquina ficar com mais de um processo, dá ruim
    printf "iteration ${i}/${trials} ... "
    ./$program $nlines $nworkers >> $file; 
    printf "done\n"
done

# Só o que importa é o tempo gasto. Ignore todos os outros prints
cat $file | grep "Time elapsed" > tmp
mv tmp $file

cat $file | sed -E 's/^.*Time elapsed\s+(.*)$/\1/g' > runtimes

echo "Executed ${program} in $trials trials with ${nworkers} workers and ${nlines} lines. "
echo "Avg time:"

# Tempo médio de execução
awk '{s+=$1}END{print "",s/NR}' RS=" " runtimes