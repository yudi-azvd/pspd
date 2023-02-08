all: frac fractal-mpi-serial
# all: fractal-mpi-serial fractal-mpi-io fractal-omp

frac: fractal/fractal.c
	@gcc   fractal/fractal.c -o frac -lm -g

fractal-mpi-serial: fractal/fractalmpiserial.c
	@mpicc fractal/fractalmpiserial.c -o fractalmpiserial -lm
	
# fractal-mpi-io:
# 	@mpicc fractal/fractalmpi_io.c -o fractalmpiio -lm
	
# fractal-omp:
# 	@mpicc fractal/fractalomp.c -o fractalomp -lm
	
# vetor:
# 	@gcc -o ordena/ordena-vetor ordena_vetor.c -fopenmp

clean:
	@rm -rf frac fractalmpiserial fractalmpiio fractalomp ordena-vetor