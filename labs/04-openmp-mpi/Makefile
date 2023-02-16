all: f fractal-mpi-serial fractal-mpi-serial-slow fractal-mpi-io fractal-mpi-io-slow fractal-omp diff

fractal-dbg-diff: fractal/fractal-dbg-diff.c
	@gcc   fractal/fractal-dbg-diff.c -o fractal-dbg-diff -lm -g

f: fractal/fractal.c
	@gcc   fractal/fractal.c -o f -lm -g

fractal-mpi-serial: fractal/fractalmpiserial.c
	@mpicc fractal/fractalmpiserial.c -o fractalmpiserial -lm

fractal-mpi-serial-slow: fractal/fractalmpiserial-slow.c
	@mpicc fractal/fractalmpiserial-slow.c -o fractalmpiserial-slow -lm
		
fractal-mpi-io: fractal/fractalmpi_io.c
	@mpicc fractal/fractalmpi_io.c -o fractalmpi_io -lm

fractal-mpi-io-slow: fractal/fractalmpi_io-slow.c
	@mpicc fractal/fractalmpi_io-slow.c -o fractalmpi_io-slow -lm

fractal-omp: fractal/fractalomp.c
	@gcc -g fractal/fractalomp.c -o fractalomp -lm -fopenmp

diff: diff.c
	@gcc diff.c -g -Wall -Wextra -pedantic -o diff
	
# ordena: ordena/ordena_vetor.c ordena/ordena_vetor_omp.c
# 	@gcc -o ordena_vetor ordena/ordena_vetor.c -fopenmp
# 	@gcc -o ordena_vetor_omp ordena/ordena_vetor_omp.c -fopenmp

clean:
	@rm -rf f \
		fractalmpiserial \
		fractalmpiserial-slow \
		fractalmpi_io\
		fractalmpi_io-slow\
		fractalomp \
		ordena_vetor \
		ordena_vetor-omp \
		diff fractal-dbg-diff