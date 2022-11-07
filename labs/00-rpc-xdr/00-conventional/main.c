#include <stdio.h>
#include <stdlib.h>

int add(int x, int y) {
  printf("Request add(%d, %d)\n", x, y);
  return x + y;
}

int sub(int x, int y) {
  printf("Request sub(%d, %d)\n", x, y);
  return x - y;
}

int main(int argc, char *argv[]) {
  int x, y;

  if (argc != 3) {
    fprintf(stderr, "Usage: %s x y\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  x = atoi(argv[1]);
  y = atoi(argv[2]);

  printf("%d + %d = %d\n", x, y, add(x, y));
  printf("%d - %d = %d\n", x, y, sub(x, y));

  return 0;
}