---
title: CSI101 ICT 完整模拟卷（W1–W9）
tags: [CSI101, mock, ICT, 完整]
course: CSI101 Computer Systems
---

# CSI101 In-Class Test 完整模拟卷
# CSI101 ICT Full Mock (Week 1 – Week 9)

> **模拟对象**：Class Test（30%，Week 10 周五 19:00–20:00，SEB 在线测验）
> **题型**：MCQ + 填空（gap filling）+ 汇编编程（Assembly Programming）——与真实 ICT 题型一致
> **满分 100 分，建议 60 分钟**
> **说明**：完成后把答案发我批改（选择题写 `A1 A2 …`；填空按题号写；汇编写指令）。
> ⚠️ 本卷暂不提供答案。

---

## Section A · 选择题 MCQ（20 题 × 3 分 = 60 分）

**A1.**（W1）A computer system consists of three components working together:
A. hardware, software and data　B. CPU, memory and disk　C. input, output and processing　D. compiler, assembler and interpreter

**A2.**（W1）In the von Neumann model, programs and data are stored:
A. in separate memories　B. in the same memory　C. programs in ROM, data in RAM　D. inside the CPU

**A3.**（W1）The "von Neumann bottleneck" refers to:
A. the limited capacity of main memory　B. the limited clock frequency　C. instructions and data competing for the same path between CPU and memory　D. the CPU being too fast

**A4.**（W2）Which component understands instructions and tells the other components what to do?
A. ALU　B. clock　C. registers　D. control unit

**A5.**（W2）In the fetch step of the fetch-decode-execute cycle, the address in the PC is copied into:
A. the MDR　B. the MAR　C. the CIR　D. the accumulator

**A6.**（W2/L08）A 32-bit address bus can address up to:
A. 2 GB　B. 4 MB　C. 16 GB　D. 4 GB

**A7.**（W2）The x86 architecture is an example of:
A. RISC　B. CISC　C. both RISC and CISC　D. neither RISC nor CISC

**A8.**（W5）Which translator converts the whole program into machine code BEFORE execution?
A. compiler　B. interpreter　C. assembler　D. linker

**A9.**（W5）The byte code produced by the Java compiler is executed by:
A. the CPU directly　B. the assembler　C. the linker　D. the JVM (an interpreter / virtual machine)

**A10.**（W5）The job of the linker is to:
A. translate assembly into machine code　B. execute statements one at a time　C. join the object code of all modules and resolve external references　D. optimise the source code

**A11.**（W6）In 4-bit two's complement, −5 is:
A. 1101　B. 1010　C. 1011　D. 1111

**A12.**（W6）In two's complement, overflow can occur when:
A. a positive and a negative number are added　B. two numbers of the same sign are added and the result has the opposite sign　C. any carry is produced　D. two numbers are subtracted

**A13.**（W6）In IEEE 754 single precision, the exponent field has:
A. 8 bits　B. 23 bits　C. 31 bits　D. 4 bits

**A14.**（W8）When the x86 stores 0x12345678 in memory, the byte at the LOWEST address is:
A. 12　B. 34　C. 56　D. 78

**A15.**（W8）Which type of memory needs periodic refreshing?
A. SRAM　B. ROM　C. DRAM　D. Flash

**A16.**（W8）1 KB equals:
A. 1024 bytes　B. 1000 bytes　C. 2048 bytes　D. 8192 bytes

**A17.**（W9）In a direct-mapped cache with 10 blocks, main-memory block 37 maps to cache block:
A. 7　B. 3　C. 37　D. 10

**A18.**（W9）The replacement policy that evicts the block unused for the longest time is:
A. FIFO　B. LRU　C. random　D. optimal

**A19.**（W9）Virtual memory is a technique that:
A. uses main memory to expand the disk　B. uses cache to expand main memory　C. uses the hard disk to expand main memory　D. uses registers to expand the cache

**A20.**（W3–4）The LOOP instruction always uses which register as its counter?
A. EAX　B. ECX　C. EBX　D. EDX

---

## Section B · 填空 Gap Filling（10 题 × 2 分 = 20 分）

**B1.**（W2）The five key components of a CPU are: control unit, ________, clock, buses and registers.

**B2.**（W2）After fetching, the instruction is copied from the MDR into the ________ register, and the control unit splits it into the ________ and the operand.

**B3.**（W6）The rule for negating a two's complement number: ________ all the bits, then add 1.

**B4.**（W4）The range of an 8-bit two's complement number is ________ to ________.

**B5.**（W6）The IEEE 754 single-precision exponent is stored with an excess of ________.

**B6.**（W9）The smallest unit that can be read from or written to a disk is a ________.

**B7.**（W9）In a direct-mapped cache with 16 blocks, main-memory block 50 maps to cache block ________.

**B8.**（W9）For a disk spinning at 7200 RPM, the average rotational latency is about ________ ms.

**B9.**（W9）The write policy that updates the cache AND main memory on every write is called ________.

**B10.**（W9）The area of the disk reserved for virtual memory is called the ________.

---

## Section C · 汇编编程 Assembly Programming（20 分）

### C1.（8 分）指令序列表格填空：数组求和
Complete the sequence to sum the elements of `data` and store the result in `sum` (final answer: 66). The pre-filled lines are marked 「given」.

```cpp
#define N 5
int data[N] = { 4, 8, 15, 16, 23 };
int sum;
_asm {
    push   esi              ; given
    lea    esi, data        ; given
    ______________          ; ① 累加器清零
    mov    ecx, N           ; given
next:
    ______________          ; ② 累加当前元素
    ______________          ; ③ 指针步进一个 int
    loop   next             ; given
    mov    sum, eax         ; given
    ______________          ; ④ 还原 ESI
}
```

### C2.（6 分）代码补全：两数之和的函数
Fill the two blanks (one complete instruction each).

```cpp
int addTwo(int a, int b)
{
    int result;
    _asm {
        mov    eax, a
        ______________      ; ① 加上参数 b
        mov    result, eax
    }
    return result;
}

void main()
{
    int answer;
    _asm {
        push   5            ; given
        push   7            ; given
        call   addTwo       ; given
        ______________      ; ② 清理两个参数（__cdecl）
        mov    answer, eax  ; given
    }
}
```

### C3.（6 分）概念填空（每题 3 分）
**C3-1.** 对负数做右移（除以 2）必须用 ________ 指令，因为它复制符号位；用 SHR 会破坏符号。
**C3-2.** 如果进入 LOOP 循环时 ECX 已经是 0，会发生 ________。

---

## 答题提示 Hints

- Section A：每题 3 分钟以内；先写公式/画状态再选。
- Section B：直接写词或数字（如 `ALU`、`1011`、`4.17`）。
- Section C：每个空 = 一条完整 x86 指令；注意 push/pop 配对与 `add esp, 4×参数个数`。
- 完成后上传答案（如 `A1A A2B …`、`B1: ALU`、`C1①: xor eax, eax`），我会逐题批改并出复盘练习。
