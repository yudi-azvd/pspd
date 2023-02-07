all: fractal-mpi-serial
# all: fractal-mpi-serial fractal-mpi-io fractal-omp

fractal-mpi-serial:
	@mpicc fractalmpiserial.c -o fractalmpiserial -lm
	
# fractal-mpi-io:
# 	@mpicc fractalmpi_io.c -o fractalmpiio -lm
	
# fractal-omp:
# 	@mpicc fractalomp.c -o fractalomp -lm
	
# vetor:
# 	@gcc -o ordena-vetor ordena_vetor.c -fopenmp

clean:
	@rm -rf fractalmpiserial fractalmpiio fractalomp ordena-vetor