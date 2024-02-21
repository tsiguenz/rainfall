#include <stdio.h>
#include <stdlib.h>

int global = 0;

void v() {
  char buffer[520];

  char *fgetsRet = fgets(buffer, 512, stdin);
  int ret = printf(buffer);
  ret = global;
  if (ret == 64) {
    fwrite("Wait what?!\n", 12, 1, stdout);
    system("/bin/bash");
  }
}

int main(int ac, char *av[]) { v(); }
