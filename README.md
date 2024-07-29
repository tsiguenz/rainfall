# rainfall

<!--toc:start-->
- [rainfall](#rainfall)
  - [Introduction](#introduction)
  - [Usefull commands](#usefull-commands)
    - [GDB](#gdb)
    - [Get binary informations](#get-binary-informations)
    - [Misc](#misc)
  - [Usefull link](#usefull-link)
<!--toc:end-->

## Introduction

The goal of this project is to increase our privileges with a vulnerable binary to go to the next level.  
For each level we need to write a pseudo code of the binary in `source.c` but they are only a representation of the asm code, they may not compile.   
To improve our understanding of assembly language we decide to not use any decompiler like ghidra or IDA and only use vanilla gdb.

## Usefull commands

### GDB
t
Use intel syntax:

```bash
set disassembly-flavor intel
```

Print saved EBP and saved EIP:

```bash
x/2xw $ebp
```

Edit register:

```bash
set $eip=0x0
```

Get infos about beginning of stack or heap:

```bash
info proc mapping
```

Run program with command in stdin:

```bash
r < <(python -c "print('B' * 150)")
```

---

### Get binary informations

Print disasembled binary:

```bash
objdump --no-show-raw-insn -M intel -d <binary>
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
