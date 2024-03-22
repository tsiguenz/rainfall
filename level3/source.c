#include <stdio.h>
#include <stdlib.h>

int global = 0;

void v() {
  char buffer[520];

  fgets(buffer, 512, stdin);
  printf(buffer);

  if (global == 64) {
    fwrite("Wait what?!\n", 12, 1, stdout);
    system("/bin/bash");
  }
}

int main(int ac, char *av[]) { v(); }
