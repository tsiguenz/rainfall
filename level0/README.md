# Walkthrough level0

First of all we look at the files:

```bash
level0@RainFall:~$ ls -la
(...)
-rwsr-x---+ 1 level1 users  747441 Mar  6  2016 level0
```

We can see the [SUID](https://www.redhat.com/sysadmin/suid-sgid-sticky-bit)
bit is on and the owner is level1. So the file will be executed by level1.

Try to run the file:

```bash
level0@RainFall:~$ ./level0
Segmentation fault (core dumped)
level0@RainFall:~$ ./level0 toto
No !
```

With the disassembly code we write the c code:

```c
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
```

To exploit the binary and spawn a shell with the level1 permissions we need to
pass this condition:

```c
if (n == 423)
```

Lets do it:

```bash
level0@RainFall:~$ ./level0 423
$ cat /home/user/level1/.pass
1fe8a524fa4bec01ca4ea2a869af2a02260d4a7d5fe7e7c24d8617e6dca12d3a
$ exit
level0@RainFall:~$ su level1
Password: 1fe8a524fa4bec01ca4ea2a869af2a02260d4a7d5fe7e7c24d8617e6dca12d3a
RELRO           STACK CANARY      NX            PIE             RPATH      RUNPATH      FILE
No RELRO        No canary found   NX disabled   No PIE          No RPATH   No RUNPATH   /home/user/level1/level1
level1@RainFall:~$
```
