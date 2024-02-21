#include <stdio.h>
#include <stdlib.h>

int global = 0;

int p(char *buffer) {
  int ret = printf(buffer);
  ret = global;
  return ret;
}

void n(void) {
  char buffer[520];
  fgets(buffer, 512, stdin);
  int ret = p(buffer);
  if (ret == 0x1025544)
    system("/bin/cat /home/user/level5/.pass");
}

int main(void) { n(); }
