#include <stdio.h>

void run(void) { // 0x08048444
  fwrite("Good... Wait what?\n", 19, 1, stdout);
  system("/bin/sh");
}

int main(void) {
  char buffer[64];
  gets(buffer);
}

