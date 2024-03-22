#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int ac, char **av) {
  int size = atoi(av[1]);
  if (size > 9)
      return 1;
  char buff[40];
  memcpy(buff, av[2], size * 4);
  if (size == 0x574f4c46)
    execl("/bin/sh", "sh", NULL);
  return 0;
}
