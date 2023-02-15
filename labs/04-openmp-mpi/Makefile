all: f fractal-mpi-serial fractal-mpi-io fractal-omp diff 

fractal-dbg-diff: fractal/fractal-dbg-diff.c
	@gcc   fractal/fractal-dbg-diff.c -o fractal-dbg-diff -lm -g

f: fractal/fractal.c
	@gcc   fractal/fractal.c -o f -lm -g

fractal-mpi-serial: fractal/fractalmpiserial.c
	@mpicc fractal/fractalmpiserial.c -o fractalmpiserial -lm
	
fractal-mpi-serial-mem: fractal/fractalmpiserial-mem.c
	@mpicc fractal/fractalmpiserial-mem.c -o fractalmpiserial-mem -lm
	
fractal-mpi-io: fractal/fractalmpi_io.c
	@mpicc fractal/fractalmpi_io.c -o fractalmpi_io -lm

fractal-mpi-io-mem: fractal/fractalmpi_io-mem.c
	@mpicc fractal/fractalmpi_io-mem.c -o fractalmpi_io-mem -lm

fractal-omp: fractal/fractalomp.c
	@gcc -g fractal/fractalomp.c -o fractalomp -lm -fopenmp

diff: diff.c
	@gcc diff.c -g -Wall -Wextra -pedantic -o diff
	
# vetor:
# 	@gcc -o ordena/ordena-vetor ordena_vetor.c -fopenmp

clean:
	@rm -rf f fractalmpiserial fractalmpi_io fractalomp ordena-vetor fractal-dbg-diff *-mem