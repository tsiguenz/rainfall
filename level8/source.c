#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int32_t *auth = NULL;    // 0x8049aac
int32_t *service = NULL; // 0x8049ab0

int main(void) {
  while (1) {
    printf("%p, %p \n", auth, service);
    char buffer[128]; // esp+0x20
    char *input = fgets(buffer, 128, stdin);
    if (input != NULL) {
      if (strncmp(input, "auth ", 5) == 0) {
        auth = malloc(4);
        char *tmp = buffer + 5;
        size_t size = strlen(tmp);
        if (size <= 30)
          strcpy(auth, tmp);
      }
      if (strncmp(input, "reset", 5) == 0) {
        free(auth);
      }
      if (strncmp(input, "service", 6) == 0) {
        service = strdup(buffer + 7);
      }
      if (strncmp(input, "login", 5) == 0) {
        if (auth[32] == 0)
          fwrite("Password:\n", 10, 1, stdout);
        else
          system("/bin/sh");
      }
    }
  }
}
