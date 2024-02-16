#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main(int ac, char *av[]) {
  int n = atoi(av[1]);
  (void)ac;

  if (n == 423) {
    char *name = strdup("/bin/sh");
    char *arg[2] = {name, NULL};

    gid_t gid = getegid();
    uid_t uid = geteuid();

    setresgid(gid, gid, gid);
    setresuid(uid, uid, uid);

    execv(name, arg);
  } else {
    printf("No !");
  }
  return 0;
}
