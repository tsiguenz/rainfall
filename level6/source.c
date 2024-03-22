#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void n(void) { // 0x08048454
  system("/bin/cat /home/user/level7/.pass");
}

void m(void) { // 0x08048468
  puts("Nope");
}

int main(int ac, char **av) {
  void *p1 = malloc(64);
  void (*p2)(void) = malloc(4);
  p2 = m;
  strcpy(p1, av[1]);
  p2 = *p2;
  p2();
}
