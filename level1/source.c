#include <stdio.h>

void run(void) {
  fwrite("Good... Wait what?\n", 19, 1, stdout);
  system("/bin/sh");
}

int main(void) {
  char buffer[64];
  gets(buffer);
}
