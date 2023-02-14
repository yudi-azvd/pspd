all: frac fractal-mpi-serial fractal-mpi-io diff

fractal-dbg-diff: fractal/fractal-dbg-diff.c
	@gcc   fractal/fractal-dbg-diff.c -o fractal-dbg-diff -lm -g

frac: fractal/fractal.c
	@gcc   fractal/fractal.c -o frac -lm -g

fractal-mpi-serial: fractal/fractalmpiserial.c
	@mpicc fractal/fractalmpiserial.c -o fractalmpiserial -lm
	
fractal-mpi-serial-mem: fractal/fractalmpiserial-mem.c
	@mpicc fractal/fractalmpiserial-mem.c -o fractalmpiserial-mem -lm
	
fractal-mpi-io: fractal/fractalmpi_io.c
	@mpicc fractal/fractalmpi_io.c -o fractalmpi_io -lm

fractal-mpi-io-mem: fractal/fractalmpi_io-mem.c
	@mpicc fractal/fractalmpi_io-mem.c -o fractalmpi_io-mem -lm

diff: diff.c
	@gcc diff.c -g -Wall -Wextra -pedantic -o diff
	
# fractal-omp:
# 	@mpicc fractal/fractalomp.c -o fractalomp -lm
	
# vetor:
# 	@gcc -o ordena/ordena-vetor ordena_vetor.c -fopenmp

clean:
	@rm -rf frac fractalmpiserial fractalmpi_io fractalomp ordena-vetor fractal-dbg-diff