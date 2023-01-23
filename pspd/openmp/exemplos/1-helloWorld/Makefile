COMPILER = gcc
FLAGS = -fopenmp -Wall -Wextra

all: 1-hello.exec 1.1-hello.exec 1.2-hello-single.exec 1.3-hello-wrong.exec
	@echo "Compiled!"

%.exec: %.o
	$(COMPILER) -o $@ $+ $(FLAGS)

%.o: %.c
	$(COMPILER) -o $@ -c $< $(FLAGS)

clean:
	rm -f *.o *.exec