#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Usage: ./dwc <file path>");
    exit(1);
  }
  printf("%d\n", argc);

  char* file_path = argv[1];
  FILE* file = fopen(file_path, "r");
  

  fclose(file);

  return 0;
}