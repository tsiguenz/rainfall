#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char *flag;
char *str = "~~";

void m(void) { // 0x080484f4
  printf("%s - %d\n", flag, (int)time(NULL));
}

int main(int argc, char **argv) {
  int *p1 = malloc(8); // 0x804a008
  // to inspect: x/8xw 0x0804a008
  p1[0] = 1;
  p1[1] = (int)malloc(8); // 0x804a018
  // to inspect: x/8xw 0x0804a018
  int *p2 = malloc(8); // 0x804a028
  // to inspect: x/8xw 0x0804a028
  p2[0] = 2;
  p2[1] = (int)malloc(8); //  0x0804a038
  // to inspect: x/8xw 0x0804a038
  strcpy((char *)p1[1], argv[1]);
  strcpy((char *)p2[1], argv[2]);
  fgets(flag, 68, fopen("/home/user/level8/.pass", "r"));
  puts(str);
  return 0;
}
