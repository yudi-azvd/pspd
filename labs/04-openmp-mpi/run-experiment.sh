nprocs=$1
nlines=$2
program=$3

echo "Running ${program} with ${nprocs} processes and ${nlines} lines"

file="report.txt"

> $file

for i in {1..30}; do 
    echo "iteration ${i}/30"
    mpirun -n $nprocs --host cm1,cm2,c3,cm4 ./$program $nlines >> $file; 
done

# Só o que importa é o tempo gasto. Ignore todos os outros prints
cat $file | grep "Time elapsed" > tmp
mv tmp $file

cat $file | sed -E 's/^.*Time elapsed\s+(.*)$/\1/g' > runtimes


echo "Executed ${program} with ${nprocs} processes and ${nlines} lines"

# Tempo médio de execução
awk '{s+=$1}END{print "",s/NR}' RS=" " runtimes