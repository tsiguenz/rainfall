#include <stdio.h>
#include <string.h>
#include <unistd.h>

void p(char *buff, char *str) {
  char buff1[4104];
  puts(str);
  read(0, buff1, 4096);
  char *ret = strchr(buff1, '\n');
  *ret = '\0';
  strncpy(buff, buff1, 20);
}

char *pp(char *buff) {
  char buff1[48];
  char *ptr = buff + 20;
  p(buff1, " - ");
  p(ptr, " - ");
  strcpy(buff, buff1);
  buff[strlen(buff) - 1] = ' ';
  return strcat(buff, ptr);
}

int main(void) {
  char buff[42];
  pp(buff);
  puts(buff);
  return 0;
}
