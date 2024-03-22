#include <stdio.h>
#include <stdlib.h>

int global = 0;

void p(char *buffer) {
  printf(buffer);
}

void n(void) {
  char buffer[520];
  fgets(buffer, 512, stdin);

  p(buffer);
  if (global == 0x1025544)
    system("/bin/cat /home/user/level5/.pass");
}

int main(void) { n(); }
