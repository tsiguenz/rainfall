#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

int language = 0;

void greetuser(char *var) {
  char str[72];
  if (language == 1)
    strcpy(str, "Hyvää päivää ");
  else if (language == 2)
    strcpy(str, "Goedemiddag! ");
  else if (language == 0)
    strcpy(str, "Hello ");
  strcat(str, var);
  puts(str);
}

int main(int ac, char **av) {
  if (ac != 3)
    return 1;
  char *lang;
  char buff[76];
  bzero(buff, 10);
  strncpy(buff, av[1], 40);
  strncpy(buff + 40, av[2], 32);
  lang = getenv("LANG");
  if (lang != NULL) {
    if (memcmp(lang, "fi", 2) == 0)
      language = 1;
    else if (memcmp(lang, "nl", 2) == 0)
      language = 2;
  }
  char var[19];
  strncpy(var, buff, 19);
  greetuser(var);
}
