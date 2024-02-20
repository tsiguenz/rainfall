#include <stdio.h>
#include <stdlib.h>

int p(char *buffer) {
  return printf(buffer);
}

void n(void) {
  char buffer[520];
  fgets(buffer, 512, stdin);
  int ret = p(buffer);
  if (ret == 0x1025544)
    system("/bin/sh");
}

int main(void) {
  n();
}
