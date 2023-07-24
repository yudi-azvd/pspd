# << 'COMMENT'
# - Upload para chococino de todos o códigos C e do Makefile
# - Compila
# - Executa

# Seria bom um download.sh para baixar os atefatos (csv?, imagens)

# em um plot.py pra plotar os csv
# COMMENT

final_dir="/pspd/04-openmp-mpi"

files="Makefile fractal/ ordena/ diff.c *.h run-experiment.sh run-experiment-omp.sh scripts/*.py"
scp -P 13508 -r ${files}  a160149410@chococino.naquadah.com.br:~${final_dir}
