# rainfall

## Usefull commands

### GDB

Use intel syntax:

```gdb
set disassembly-flavor intel
```

Print saved EBP and saved EIP:

```gdb
x/2xw $ebp
```

Edit register:

```gdb
set $eip=0x0
```

---

### Get binary informations

Print disasembled binary:

```bash
objdump -M intel -d <binary>
```

Check if the stack is executable:

```bash
readelf -l <binary> | grep GNU_STACK
```

Check endianess:

```bash
readelf -h <binary> | grep endian
```

---

### Misc

To get an interactive shell ([see why](https://unix.stackexchange.com/questions/203012/why-cant-i-open-a-shell-from-a-pipelined-process)):

```bash
cat payload.txt - | ./<binary>
or
(python -c "print(<payload>)" | cat) | ./<binary>
```

Generate payloads:

```bash
python -c "print('A' * 64...)"
```

## Usefull link

- To find shellcodes: [link](https://shell-storm.org/shellcode/files/shellcode-811.html)
