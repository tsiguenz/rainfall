#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void p(void) {
  char buffer[76];
  fflush(stdin);
  gets(buffer);
  uint32_t *p = (uint32_t *)(buffer + 80);
  // some pointer things
  if (*p == 0xb0000000) {
    printf("(%p)\n", p);
    exit(1);
  }
  puts(buffer);
  strdup(buffer);
}

int main(void) {
  p();
  return 8;
}
