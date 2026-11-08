---
title: CSI101 Lab 教学版汇编练习
tags: [CSI101, Lab, 汇编, 教学]
course: CSI101 Computer Systems
---

# CSI101 Lab 教学版 · 汇编练习
# CSI101 Lab Teaching Edition — Assembly Practice

> 目标：把 Lab 1–4 的**每一道题 + 答案**整理成一看就懂的教学版，让你能**反复练习、高效上手**写汇编。
> 使用方法：先看「思路（逻辑）」自己想一遍 → 手打代码（不要复制！）→ 对照「答案代码」核对 → 看「易错点」。
> 配套：[[ICT 知识点梳理]] ｜ [[CSI101 ICT 模拟卷（填空版）]]

---

## 〇、上手前 5 分钟：万能套路 Quick Start

### 0.1 环境（每次都要做）
1. VS2022 → 新建 **Console App (C++)** 项目；
2. 工具栏 **Solution Platforms 改为 x86**（默认 x64，`_asm` 会报 C4235）；
3. 顶部 `#include <cstdio>`（printf/scanf_s 都来自它）；
4. **Ctrl + F5** 运行（不带调试器，控制台窗口不关闭）。

### 0.2 分工原则（本课程所有程序的结构）
- **C++ 负责**：声明变量/字符串、输入输出、程序骨架；
- **汇编负责**：载入寄存器、计算、比较跳转、把结果写回变量。
- 内联汇编里**不能定义数据**（没有 DB/DW/DD），一切数据由 C++ 声明，汇编里直接写变量名。

### 0.3 万能三步 The universal pattern
```
载入 Load    →  运算 Operate  →  写回 Store
mov eax, a      add eax, b       mov sum, eax
```

### 0.4 五条黄金规则（每次写代码前默念）
1. **右→左压参，调用方清栈**：`push` 参数（最后一个先压）→ `call` → `add esp, 4×参数个数`；
2. **有符号数据用有符号跳转/移位**（JG/JGE/JL/JLE、SAR）；
3. **EBX/ESI/EDI 用前 push、用完 pop（逆序）**；EBP/ESP 绝不碰；
4. **每个标签后必须跟一条指令**（不能悬空在块尾）；
5. **LEA 取地址，MOV 取内容**——scanf_s/printf 要的是地址。

---

## 一、Lab 1 · 比较两个数 Comparing Numbers

**目标能力**：① 在 `_asm` 里调用 printf/scanf_s；② 用 CMP + JE/JG 做判断；③ 多分支汇聚到单一出口。

### Part A · 读两个数并比较（讲义程序）

**思路（先想逻辑）**：
1. **打印提示**：把字符串地址给 printf → `lea eax, msg` → `push eax` → `call printf` → `add esp, 4`（1 个参数 × 4 字节）。
2. **读数字**：scanf_s 要**写入**变量，所以传**地址**：`lea eax, first` → `push` → `lea eax, format` → `push` → `call scanf_s` → `add esp, 8`（2 个参数）。
3. **比较**：`mov eax, first`；`cmp eax, second`（内部做减法，**只留标志**）→ `je equal`（相等，ZF=1）→ `jg firstBigger`（有符号大于）；两条都不跳 = second 更大。
4. **三路一出口**：每条分支只做一件事——把对应消息的**地址**装进 EAX，然后 `jmp show`；`show:` 处**只有一个** printf。

**答案代码**（Part A 即完整答案）：
```cpp
#include <cstdio>
char msgFirst[]  = "Enter the first number: ";
char msgSecond[] = "Enter the second number: ";
char msgEqual[]     = "\nThe numbers are equal.\n";
char msgFirstBig[]  = "\nThe first is larger.\n";
char msgSecondBig[] = "\nThe second is larger.\n";
char format[]    = "%d";
int first, second;

void partA()
{
    _asm {
        // ---- 读第一个数 ----
        lea     eax, msgFirst
        push    eax
        call    printf
        add     esp, 4              // 1 参数 × 4 字节

        lea     eax, first          // scanf_s 要写入 → 传地址
        push    eax
        lea     eax, format         // "%d" 最后压
        push    eax
        call    scanf_s
        add     esp, 8              // 2 参数 × 4 字节

        // ---- 读第二个数（同上，改 msgSecond / second）----
        lea     eax, msgSecond
        push    eax
        call    printf
        add     esp, 4
        lea     eax, second
        push    eax
        lea     eax, format
        push    eax
        call    scanf_s
        add     esp, 8

        // ---- 比较 + 三路汇聚 ----
        mov     eax, first
        cmp     eax, second         // 减 second 留标志
        je      equal               // ZF=1 → 相等
        jg      firstBigger         // 有符号大于（JA 是错的！）

        lea     eax, msgSecondBig   // 落到这里 = second 大
        jmp     show

firstBigger:
        lea     eax, msgFirstBig
        jmp     show

equal:
        lea     eax, msgEqual

show:                               // 三条路共用的唯一 printf
        push    eax
        call    printf
        add     esp, 4
    }
}
```

**易错点**：
- `lea` = 取地址；`mov` = 取内容。printf 要字符串**首字符的地址**。
- `jg` 是有符号比较；用 `ja`（无符号）时负数会被当成"更大的数"。
- 忘了 `add esp` → 栈不平衡 → 程序**在块外**才崩溃。

### Task 1 · 三个数找最大（running-maximum 模式）

**思路**：把"目前最大"放在 **EAX**，拿每个新数跟它比，输了就替换。三个数只需**两次同形比较**：
```
eax = first;            // 假设第一个最大
if (eax < second) eax = second;   →  cmp eax, second / jge 跳过 / mov eax, second
if (eax < third)  eax = third;    →  cmp eax, third  / jge 跳过 / mov eax, third
largest = eax;
```

**答案代码**：
```cpp
void task1()
{
    int largest;
    _asm {
        // ---- 读三个数（沿用 Part A 的套路读 first/second/third）----
        // （读法完全同 Part A，只是多一组 prompt + scanf_s）

        // ---- running maximum ----
        mov     eax, first          // 假设第一个最大
        cmp     eax, second
        jge     checkThird          // eax 仍大 → 跳过替换
        mov     eax, second         // 否则 eax = second

checkThird:
        cmp     eax, third
        jge     haveLargest
        mov     eax, third

haveLargest:
        mov     largest, eax        // 标签后必须跟指令！
    }
    printf("\nThe largest of the three is %d.\n", largest);
}
```

**易错点**：
- 用 `jge`（≥）意味着相等时**保留先前的值**——对"最大"没影响，但要知道你保留了谁。
- 最后标签 `haveLargest:` 后必须紧跟 `mov largest, eax`，不能悬空。
- **测试负数**：-5、-20、-1 应得 -1；若得 -20 说明用了无符号跳转。

### Task 2 · 反复询问直到两数相等

**思路**：**循环交给 C++**（`while (equalFlag == 0)`），汇编块只负责：计数、读两个数、比较、把结果写回 `equalFlag`。
- `inc attempts` 直接对内存变量操作（不需要寄存器）；
- 设标志的套路：`xor edx, edx`（先置 0=不相等）→ `jne storeFlag`（不等就跳过）→ `mov edx, 1`（相等）→ `storeFlag: mov equalFlag, edx`。

**答案代码**：
```cpp
void task2()
{
    int equalFlag = 0;      // 0 = 未相等, 1 = 相等
    int attempts  = 0;

    while (equalFlag == 0)
    {
        _asm {
            inc     attempts            // 汇编里计数（INC 直接对内存操作数）

            // ---- 读 first、second（同 Part A 两段套路）----

            xor     edx, edx            // edx = 0 = 不相等
            mov     eax, first
            cmp     eax, second
            jne     storeFlag           // 不等 → 保持 edx = 0
            mov     edx, 1              // 相等 → edx = 1

storeFlag:                              // 标签后必须跟指令
            mov     equalFlag, edx      // 结果通过变量传回 C++
        }

        if (equalFlag == 0)
            printf("\nNot equal yet - try again.\n\n");
    }
    printf("\nMatched after %d attempt(s).\n", attempts);
}
```

**易错点**：
- 汇编块只写一次，标签只定义一次（循环不会报重复标签）；
- `xor edx, edx` 是清零的惯用法（比 `mov edx, 0` 短，反汇编里最常见）。

---

## 二、Lab 2 · 逻辑与算术移位 Shifts

**目标能力**：① 说清 SHR 与 SAR 对负数的区别；② 移位次数从 CL 取；③ 用进位标志 CF 逐位检查。

### Part A · -32 移位演示

**思路**：右移 = 除以 2 的幂，但**符号位怎么补**是关键：
- `shr`（逻辑右移）：高位**补 0** → -32 变成 1073741816（符号位没了！）
- `sar`（算术右移）：高位**复制原符号位** → -8（= -32 ÷ 4，正确！）
- `shl` 左移 = 乘 2；SHL 与 SAL 是**同一条指令**的两个名字。
- 每次移位都会**毁掉 EAX**，所以每移一次前要 `mov eax, value` 重新载入。

**答案代码**：
```cpp
void partA()
{
    int value = -32;
    int logical, arithmetic, leftShift;

    _asm {
        mov     eax, value
        shr     eax, 2              // 逻辑右移：高位补 0
        mov     logical, eax        // 1073741816（符号位丢失）

        mov     eax, value
        sar     eax, 2              // 算术右移：复制符号位
        mov     arithmetic, eax     // -8（正确）

        mov     eax, value
        shl     eax, 1              // 左移 = 乘 2
        mov     leftShift, eax      // -64
    }
    printf(" shr -> %d\n sar -> %d\n shl -> %d\n", logical, arithmetic, leftShift);
}
```

**口诀**：**SAR 给有符号，SHR 给无符号**。左移不分有符号无符号。

### Task 1 · 移位次数从 CL 取

**思路**：非立即数的移位次数**必须在 CL**（指令编码没有别的选择）。但**不能**写 `mov cl, count`（BYTE ← DWORD，大小冲突报错）——正确姿势：`mov ecx, count` 先装整个 32 位，CL 自然就是它的低字节。

**答案代码**：
```cpp
void task1()
{
    int value, count, logical, arithmetic, leftShift;
    // scanf_s 读 value 和 count；C++ 里先检查 0 ≤ count ≤ 31

    _asm {
        mov     ecx, count          // 整装 32 位；cl = 其低字节

        mov     eax, value
        shr     eax, cl             // 逻辑右移（次数来自 cl）
        mov     logical, eax

        mov     eax, value
        sar     eax, cl
        mov     arithmetic, eax

        mov     eax, value
        shl     eax, cl
        mov     leftShift, eax
    }
    // C++ 打印；若 value < 0 提示 SHR 与 SAR 不同、SAR 才是正确除法
}
```

**易错点**：
- `mov cl, count` → operand size conflict（DWORD 装不进 BYTE）；
- CPU 只用 CL 的**低 5 位**当移位次数，所以 >31 没有意义（C++ 里先拦截）；
- 正数时 SHR 与 SAR 结果相同——所以这个 bug 平时看不出来。

### Task 2 · 数出 32 位里 1 的个数（进位标志的妙用）

**思路**：
1. `shr eax, 1` 会把**最低位挤进进位标志 CF**——等于免费看每一位是 0 还是 1；
2. `jnc noBit`（CF=0 跳过）→ 是 1 就 `inc ebx`；
3. 循环 32 次固定（int 就是 32 位，覆盖 0 和 -1 所有情况）；
4. `loop` 与 `inc` **都不改标志**，所以不会弄坏刚测出来的 CF；
5. EBX 必须保存 → 块首 `push ebx`、块尾 `pop ebx`。

**答案代码**：
```cpp
void task2()
{
    int value, ones = 0;
    // scanf_s 读 value

    _asm {
        push    ebx                 // EBX 是必须保存的寄存器

        mov     eax, value
        xor     ebx, ebx            // ebx = 1 的个数（清零）
        mov     ecx, 32             // 固定 32 轮

countLoop:
        shr     eax, 1              // 最低位被挤进 CF
        jnc     noBit               // CF = 0 → 那一位是 0，跳过
        inc     ebx                 // CF = 1 → 计数（INC 不改 CF）
noBit:
        loop    countLoop           // LOOP 也不改标志

        mov     ones, ebx
        pop     ebx                 // 还原
    }
    printf("\n%d has %d bit(s) set to 1 out of 32.\n", value, ones);
}
```

**验证值**：-1 → 32；0 → 0；255 → 8；-32 → 27。
**拓展**：`adc ebx, 0`（带进位加）可把 jnc+inc 两行合成一行无分支写法——练熟后可尝试。

---

## 三、Lab 3 · ECX 自动循环计数 LOOP

**目标能力**：① 用 LOOP 免去"比较+减一+跳转"三件套；② 数组遍历（指针步进 +4）；③ TEST 测位、一趟找最大最小。

### Part A · 1..10 求和 + 数组求和

**思路**：
- `loop 标号` = 自动 `dec ecx` + `ecx≠0 则跳`，两条指令合一；**ECX 不可换**；
- 求和 1..10：直接把计数器当加数 `add eax, ecx`；
- 数组遍历：`lea esi, data` 取首地址 → `add eax, [esi]`（方括号 = 去那个地址取数）→ `add esi, 4`（int 是 4 字节）；
- `#define SIZE 5` 而不是 `const int`：宏展开成数字 5，`mov ecx, SIZE` 才能当立即数。

**答案代码**：
```cpp
#include <cstdio>
#define SIZE 5
int data[SIZE] = { 4, 8, 15, 16, 23 };

void partA()
{
    int total = 0, arrayTotal = 0;

    _asm {                          // —— 1 到 10 求和 ——
        xor     eax, eax            // 清零（比 mov eax,0 更快）
        mov     ecx, 10
sumLoop:
        add     eax, ecx            // 加的是计数器本身的值
        loop    sumLoop             // dec ecx; ecx≠0 则跳回
        mov     total, eax          // 10+9+...+1 = 55
    }

    _asm {                          // —— 数组求和 ——
        push    esi                 // ESI 必须保存
        lea     esi, data
        xor     eax, eax
        mov     ecx, SIZE           // 5 轮
nextItem:
        add     eax, [esi]          // 加 esi 所指的 int
        add     esi, 4              // 步进一个 int
        loop    nextItem
        mov     arrayTotal, eax     // 4+8+15+16+23 = 66
        pop     esi
    }
}
```

**易错点**：
- **ECX=0 陷阱**：LOOP 先减后判，ECX 为 0 进入会 wrap 成 4,294,967,295 → 死循环 42 亿次；
- LOOP 是**短跳转**（目标 128 字节内），循环体太长会编译报错；
- 忘了 `push esi`/`pop esi` → 程序在块外崩溃。

### Task 1 · 只累加偶数（TEST 测位）

**思路**：偶数的**最低位是 0**。`test edx, 1` 做按位与但**只留标志**；`jnz` = 最低位是 1 = 奇数。
**寄存器分工**（写代码前先写下来）：ESI=指针，EAX=偶数和，EBX=偶数个数，EDX=当前元素，ECX=计数器。

**答案代码**：
```cpp
void task1()
{
    int evenSum = 0, evenCount = 0;
    _asm {
        push    esi
        push    ebx

        lea     esi, data
        xor     eax, eax            // 偶数和
        xor     ebx, ebx            // 偶数个数
        mov     ecx, SIZE

nextItem:
        mov     edx, [esi]          // 当前元素
        test    edx, 1              // 与 1 按位与，只留标志
        jnz     skipOdd             // 最低位=1 → 奇数，跳过

        add     eax, edx            // 偶数：累加
        inc     ebx                 // 并计数（INC 在偶数分支里！）

skipOdd:
        add     esi, 4              // 指针步进必须在公共路径
        loop    nextItem

        mov     evenSum, eax
        mov     evenCount, ebx

        pop     ebx                 // 逆序还原
        pop     esi
    }
}
```
输出：Even values = 3, Sum of evens = 28。

**易错点**：
- `inc ebx` 放在偶数分支里 → 只数加过的；挪出去 = 数了所有元素；
- `add esi, 4` 放在标签后（公共路径）→ 两条路都步进；若放进偶数分支，碰到第一个奇数指针就卡死（同一元素读 5 遍）；
- **TEST 测位、CMP 排序**，别用反。

### Task 2 · 一趟同时找最大与最小

**思路**：元素 0 同时当**两个答案的初猜**，剩余 SIZE−1 个元素各与最大、最小各比一次：
```
eax = data[0] (最大初猜),  ebx = data[0] (最小初猜)
ecx = SIZE; dec ecx        ← 元素 0 已用掉
esi += 4                   ← 从元素 1 开始扫
每轮: edx = [esi]
      if (edx > eax) eax = edx     → cmp edx,eax / jle 跳过 / mov eax,edx
      if (edx < ebx) ebx = edx     → cmp edx,ebx / jge 跳过 / mov ebx,edx
```

**答案代码**：
```cpp
void task2()
{
    int largest = 0, smallest = 0;
    _asm {
        push    esi
        push    ebx

        lea     esi, data
        mov     eax, [esi]          // 元素 0 = 最大初猜
        mov     ebx, eax            // 也 = 最小初猜

        mov     ecx, SIZE
        dec     ecx                 // 元素 0 已算，只剩 SIZE-1 轮
        add     esi, 4              // 从元素 1 开始

scanLoop:
        mov     edx, [esi]          // 候选元素

        cmp     edx, eax
        jle     checkSmallest       // 有符号跳转！
        mov     eax, edx            // 新的最大

checkSmallest:
        cmp     edx, ebx
        jge     nextOne
        mov     ebx, edx            // 新的最小

nextOne:
        add     esi, 4
        loop    scanLoop

        mov     largest, eax
        mov     smallest, ebx

        pop     ebx
        pop     esi
    }
}
```
输出：Largest = 23, Smallest = 4。

**易错点**：
- `dec ecx` 正是 ECX=0 陷阱的现场：若 SIZE=1，ECX 在此变 0，LOOP 会 wrap——想想守卫该加在哪；
- 用 `jle/jge`（有符号）；数组一旦有负数，`jbe/jae` 会静默出错；
- 同一候选 EDX 供两次比较，所以先 `mov edx, [esi]` 再从寄存器比，而不是比内存两次。

---

## 四、Lab 4 · 栈上的函数 Function Using the Stack

**目标能力**：① 看懂栈帧；② 手写 CALL 全流程；③ 用指针参数返回多个结果。

### 先看懂栈帧（一次看懂，终身受用）
CALL 之后、函数内建好帧后，栈从上（高地址）到下是：

| 位置 | 内容 |
|---|---|
| [ebp+12] | 第 2 个参数 b |
| [ebp+8] | 第 1 个参数 a |
| [ebp+4] | 返回地址（CALL 压的） |
| [ebp] | 旧 EBP |
| [ebp−4] | 局部变量 |

**你永远不用写这些偏移**——直接写参数名 `a`、`b`，编译器替你换算成 [ebp+8]、[ebp+12]。

### Part A · absDiff：返回绝对差

**思路**：
1. 函数体：`eax = a − b`（**SUB 直接留标志**，不必再 CMP）；`jns done`（结果非负就跳过）；否则 `neg eax` 取负；
2. `push ebx` / `pop ebx` 要**覆盖每条路径**（pop 放在标签后）；
3. 返回值放 **EAX**（推荐存局部变量再用 C++ return，清晰）；
4. 手写调用：**右→左压参**（`push 3` 再 `push 10`，10 更靠近栈顶 = [ebp+8]）→ `call absDiff` → `add esp, 8`（__cdecl：**调用方**清栈）→ 结果在 EAX。

**答案代码**：
```cpp
int absDiff(int a, int b)
{
    int result;
    _asm {
        push    ebx                 // EBX 是被调用方保存的 → 先保存

        mov     eax, a              // [ebp+8]
        mov     ebx, b              // [ebp+12]
        sub     eax, ebx            // eax = a - b（顺便留下标志）

        jns     done                // SF=0 → 已经 ≥ 0
        neg     eax                 // 否则取负

done:
        mov     result, eax         // [ebp-4]
        pop     ebx                 // 每条路径都要 pop！
    }
    return result;
}

void partA()
{
    int fromCpp, fromAsm;
    fromCpp = absDiff(10, 3);       // C++ 普通调用

    _asm {                          // 手写调用，看清 call 的代价
        push    3                   // 最后一个参数先压
        push    10                  // 第一个参数后压（离栈顶近）
        call    absDiff
        add     esp, 8              // __cdecl：调用方清栈（2×4 字节）
        mov     fromAsm, eax        // 结果在 EAX
    }
    // 两路都输出 7；absDiff(3,10) 也输出 7
}
```

### Task 1 · maxOf3：三个参数的函数

**思路**：函数体沿用 Lab 1 的 **running maximum**（EAX/ECX/EDX 随便用，无需 push）；调用处**右→左压三个参数**（`push c` → `push b` → `push a`），第三个参数在 [ebp+16]（写 `c` 就行）。

**答案代码**：
```cpp
int maxOf3(int a, int b, int c)
{
    int result;
    _asm {
        mov     eax, a              // running max 从 a 开始
        cmp     eax, b
        jge     checkC              // a ≥ b → 保留
        mov     eax, b

checkC:
        cmp     eax, c
        jge     haveMax
        mov     eax, c

haveMax:
        mov     result, eax
    }
    return result;
}

void task1()
{
    int answer;
    int a = 10, b = 3, c = 25;

    _asm {
        push    c                   // 第三个参数先压
        push    b
        push    a                   // 第一个参数最后压
        call    maxOf3
        add     esp, 12             // 三个参数 = 12 字节（本 Lab 头号错误点！）
        mov     answer, eax
    }
    printf(" maxOf3(10, 3, 25) = %d\n", answer);   // 25
    printf(" maxOf3(-5, -20, -1) = %d\n", maxOf3(-5, -20, -1));  // -1
}
```

### Task 2 · minMax：用指针带回两个结果

**思路**：EAX 只能带回**一个**值，第二个结果要走**指针参数**：
1. 指针参数的值**本身就是地址** → `mov ebx, lo`（**MOV 不是 LEA**！）；
2. 写入目标 → `mov [ebx], eax`（**方括号 = 到那个地址去写**；忘括号 = 把指针本身覆盖了）；
3. 排序两数：`cmp eax, edx` + `jle` + **`xchg eax, edx`**（一条指令交换两寄存器，让小的留 EAX）。

**答案代码**：
```cpp
void minMax(int a, int b, int* lo, int* hi)
{
    _asm {
        push    ebx

        mov     eax, a
        mov     edx, b

        cmp     eax, edx
        jle     inOrder             // a ≤ b → eax 已较小
        xchg    eax, edx            // 一条指令交换：eax=较小, edx=较大

inOrder:
        mov     ebx, lo             // ebx = 指针的值（就是地址）
        mov     [ebx], eax          // *lo = 较小（方括号 = 写目标！）

        mov     ebx, hi
        mov     [ebx], edx          // *hi = 较大

        pop     ebx
    }
}

void task2()
{
    int lo = 0, hi = 0;
    minMax(10, 3, &lo, &hi);        // lo = 3, hi = 10
    minMax(-7, 42, &lo, &hi);       // lo = -7, hi = 42
    minMax(5, 5, &lo, &hi);         // lo = 5, hi = 5（走 JLE 路径，两个都 5）
}
```

**易错点**：
- `mov ebx, lo`（取指针值）≠ `lea ebx, lo`（取指针变量自身地址）——这里要 MOV；
- 写目标必须 `mov [ebx], eax`；漏方括号 → 结果一个对、一个是乱数；
- 记得测试相等输入 `minMax(5, 5)`。

---

## 五、全 Lab 指令速查 + 报错速查 Quick Reference

### 5.1 本 Lab 用到的指令一览
| 指令 | 作用 |
|---|---|
| `lea reg, 名字` | 取**地址**（给 printf/scanf_s 用） |
| `mov reg, [esi]` / `mov [ebx], eax` | 内存 ←→ 寄存器（方括号 = 读写地址指向处） |
| `push/pop` | 压栈/弹栈（ESP ∓ 4） |
| `cmp a, b` | 减 b 留标志；配合 `je/jg/jge/jl/jle`（有符号）/ `ja/jb`（无符号） |
| `test a, b` | 与运算留标志（测某位是否为 1：`test edx, 1` + `jnz`） |
| `jmp/jcc` | 跳转；`jns/jnz/jnc` 看 SF/ZF/CF |
| `xor eax, eax` | 寄存器清零（惯用法） |
| `inc/dec` | 加一/减一（**不改 CF**；可直接操作内存 `inc attempts`） |
| `neg` | 取负（补码取反+1） |
| `xchg a, b` | 一条指令交换两操作数 |
| `shr/sar/shl` | 逻辑右移（补 0）/ 算术右移（补符号）/ 左移（=×2）；次数可为立即数或 **CL** |
| `loop 标号` | dec ecx + 非零跳回（**不改标志**；短跳转；ECX=0 会 wrap） |
| `call` / `add esp, n` | 调用 / __cdecl 调用方清栈（n = 4×参数个数） |
| `idiv` | 有符号除法（先 `cdq`；EAX=商 EDX=余） |
| `adc ebx, 0` | 带进位加（Lab 2 的无分支进阶） |

### 5.2 报错/症状速查（背下来能救急）
| 症状 | 原因 |
|---|---|
| `_asm not supported`（C4235） | 平台还是 x64 → 切 x86 |
| improper operand type | 大小歧义 → 加 `DWORD PTR`；或 EAX 与 AL 混用 |
| undeclared identifier | 变量名拼错/不在作用域（_asm 里**大小写敏感**） |
| 块外崩溃 | 栈不平衡，或 EBX/ESI/EDI/EBP 没还原 |
| 答案符号错 | 有符号数据用了无符号跳转，或 SHR 当 SAR 用 |
| 死循环/卡死 | LOOP 进入时 ECX=0（先测零） |
| 一个结果对、一个乱数 | 指针写漏方括号（`mov ebx, eax` 应为 `mov [ebx], eax`） |

### 5.3 高效练习法（重复练习路线）
1. **先默写逻辑**：每道题先用自己的话写 3 步思路（载入→运算→写回 + 分支结构），再看代码；
2. **手打不看答案**（Lab 手册强调 type it, do not paste it）；
3. **改数据验证**：把数组换成含负数/含 0/单元素，看输出是否符合手算（单元素会触发 DEC ECX 陷阱）；
4. **变形练习**：求和 → 求乘积；找最大 → 找第二大；偶数 → 能被 3 整除；两数比较 → 三数排序；
5. **打卡表**：Part A 各 1 遍 + 每个 Task 各 2 遍，考前再整体默写一遍。
