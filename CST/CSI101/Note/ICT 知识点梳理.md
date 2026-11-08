---
title: CSI101 In-Class Test 知识点梳理
tags: [CSI101, ICT, 复习]
course: CSI101 Computer Systems
---

# CSI101 In-Class Test 知识点梳理
# CSI101 ICT Knowledge Review

> 📚 配套练习：[[Lab 教学版 汇编练习]]（Lab 1–4 每题 + 答案的教学版，练习汇编必看）｜ 模拟卷：[[CSI101 ICT 模拟卷（填空版）]]

> **考试信息**（源自 L01/L05 讲义与 Module Handbook）：
> - **Class Test（ICT）占 30%**，时间 **Week 10（11 月 20 日，周五）19:00–20:00**
> - 在线测验（Connect 形式），多个机房同时进行，使用 **Safe Exam Browser (SEB)**
> - **范围：Week 1 – Week 9**（L05 明确写明 "Assesses knowledge from week 1 to week 9"）
> - **题型：MCQ + 填空（gap filling）+ 汇编编程（Assembly Programming）**
> - ⚠️ 考试中 **禁止使用 AI/GAI 与在线工具**
> - 期末（70%）：闭卷 2 小时，MCQ + 填空 + 汇编编程

---

## 一、Week 1 · 计算机系统导论 Introduction to Computer Systems

### 1.1 三大组成 Three components
| 组成 | 含义 |
|---|---|
| **Hardware 硬件** | 可触摸的物理机器（处理器、内存、存储、外设），只会执行极简单的操作 |
| **Software 软件** | 指挥硬件的指令（系统软件 + 应用软件） |
| **Data 数据** | 被处理的对象，与程序一样以二进制存放，本身无意义直到被解释 |

> 三者缺一不可（Remove any one and there is no system）。

### 1.2 系统的层次 Hierarchy of systems
计算机是**分层**构建的：每一层**隐藏下一层的复杂性**，向上提供更简单的接口（interface）。

### 1.3 输入-处理-输出模型 Input-Process-Output model
- Input data → Process → Output data，全程由**存储程序（stored program）**控制
- 同一台机器能做不同的事，靠的是换程序（一般用途机器的本质）

### 1.4 机器指令 Machine instructions
- 每条指令只是二进制模式；汇编语言给它起人类可读的名字。同一指令三种视图：
  - 二进制 `1000 1001 1101 1000` = 十六进制 `89 D8` = 汇编 `MOV EAX, EBX`
- 指令集四类：I/O（IN/OUT）、数据传输与运算（MOV/ADD/MUL/AND/OR）、程序控制转移（JMP/JC/CALL/RET）、机器控制（HLT/INT/NOP）

### 1.5 冯·诺依曼模型 von Neumann model（1945 EDVAC 报告）
| 要点                | 说明                                     |
| ----------------- | -------------------------------------- |
| 程序 = 指令列表         | 一步一步指挥机器完成任务                           |
| **程序与数据共享同一内存**   | 都以二进制存放                                |
| 内存可改写             | 换任务不用重造机器 → 通用性                        |
| 处理器是主动部分          | 按顺序取指执行（除非被跳转改变）                       |
| **瓶颈 bottleneck** | 指令和数据走同一条通路，CPU 老在等内存；缓存、宽总线、预取都是为了缓解它 |
|                   |                                        |

### 1.6 哈佛架构 Harvard architecture
- 程序与数据**物理分离**、各有总线 → 取指与取数可同时进行（DSP、PIC/AVR 微控制器）
- 现代处理器 = **modified Harvard**：统一主存之上，指令缓存与数据缓存分离

---

## 二、Week 2 · 处理器 Processors

### 2.1 CPU 五大组件 Five key components
| 组件 | 作用 |
|---|---|
| **Control unit 控制单元** | 理解指令、指挥其它组件、沿控制总线发控制信号 |
| **ALU 算术逻辑单元** | 算术（+−×÷、inc/dec）与逻辑（比较、AND/OR/NOT/XOR） |
| **Clock 时钟** | 每秒周期数（Hz），同步各组件；1 GHz = 每秒 10⁹ 周期 |
| **Buses 总线** | 地址总线（单向 CPU→内存）、数据总线（双向）、控制总线（双向） |
| **Registers 寄存器** | CPU 内部极小的快速存储 |

### 2.2 五个关键寄存器 Five registers（取指-译码-执行用）
| 寄存器 | 作用 |
|---|---|
| PC（program counter） | 下一条指令的地址，随执行递增 |
| MAR（memory address register） | 正要访问的内存地址 |
| MDR（memory data register） | 从内存取回的数据 |
| CIR（current instruction register） | 正在执行的指令 |
| Acc（accumulator） | 运算结果暂存 |

> 寄存器 vs 内存：寄存器在 CPU 内部、几十个、<1 ns；内存在主板上、上亿单元、50–100 ns（约慢百倍）。

### 2.3 取指-译码-执行循环 Fetch-Decode-Execute cycle（机器周期）
1. **Fetch**：PC → MAR → 地址总线 → 内存 → 数据总线 → MDR → **CIR**；PC 递增
2. **Decode**：控制单元把 CIR 拆成 **opcode（操作码）+ operand（操作数）**，准备控制信号
3. **Execute**：ALU 计算 / 数据移动 / 跳转改 PC
4. **Store（write-back）**：结果写回累加器或内存，更新**状态标志**（零/负/溢出——if 语句的实现基础）

> 3 GHz = 每秒 30 亿周期；一条指令可能占多个周期，现代 CPU 每周期可完成多条。

### 2.4 性能六因素（时钟频率不是全部）
时钟频率、核心数（core）、缓存大小（cache）、字长与总线宽度、流水线（pipelining）、指令集设计（CISC/RISC）。

- **CISC**（x86）：单条指令做更多事；**RISC**（ARM）：指令简单（LW/ADD/SW），低功耗
- 缓存：L1（每核 32–64 KB，~4 周期）→ L2（~12 周期）→ L3（共享，~40 周期）→ RAM（~200 周期）
- 现代处理器：多核 SoC、SMT（超线程）、分支预测、乱序执行

---

## 三、Week 3–4 · 汇编编程 Assembly Programming（ICT 重头戏！）

### 3.1 环境：MSVC 内联汇编 inline assembly
- `_asm { ... }` 写进 .cpp；**只能在 x86（32 位）平台**编译（x64 报 C4235）
- 数据全部用 C++ 声明（_asm 块内不能定义 DB/DW/DD）；汇编里直接用 C++ 变量名
- 注释用 `;` 或 `//`；不区分大小写；Intel 语法 **dest ← src**（从右往左读）

### 3.2 寄存器 General-purpose registers
| 寄存器 | 角色 |
|---|---|
| EAX | 累加器：运算、返回值 |
| EBX | 基址，使用前必须保存 |
| ECX | 计数器（LOOP 自动用） |
| EDX | 乘除扩展、余数 |
| ESI / EDI | 源/目的索引（必须保存） |
| EBP / ESP | 栈帧基址 / 栈顶指针（**绝不能动**） |

- 32 位 EAX 可拆成 16 位 AX，再拆成 AH / AL（写 AL 只改低字节——常见 bug 源）
- **EFLAGS**：ZF（零）、SF（符号）、CF（无符号进位）、OF（有符号溢出）

### 3.3 栈 The stack
- 向**低地址**增长；ESP 指向栈顶
- PUSH：先 ESP−4 再写入；POP：先读再 ESP+4
- CALL 压返回地址；RET 弹回

### 3.4 操作数类型与寻址方式 Operand types & addressing modes
- 三种操作数：寄存器 / 立即数 / 内存；**两个操作数不能都是内存**
- 五种寻址：直接 `mov eax, total`；寄存器间接 `mov eax, [esi]`；基址+位移 `[esi+8]`；变址比例 `[esi+ecx*4]`；完整 `[esi+ecx*4+8]`（scale 只能 1/2/4/8）
- 大小：BYTE(8)/WORD(16)/DWORD(32)；歧义时加 `DWORD PTR [esi]`
- `mov eax, myarray`（取内容）vs `lea ebx, myarray`（取地址）——**LEA 取地址，MOV 取内容**

### 3.5 常用指令速查 Instruction reference

**数据移动**：`mov`（复制）、`lea`（取地址）、`xchg`（交换）、`push/pop`、`movzx`（零扩展）、`movsx`（符号扩展）

**算术**：`add/sub`、`inc/dec`、`neg`（取负）、`imul`（有符号乘）、除法三件套：
```asm
mov eax, dividend
cdq            ; 有符号：符号扩展到 edx（无符号用 xor edx,edx）
idiv divisor   ; eax = 商, edx = 余数
```

**逻辑与移位**：`and/or/xor/not`（`xor eax,eax` 是清零惯用法）；`shl`（左移=乘）、`shr`（逻辑右移补 0）、`sar`（算术右移补符号位——负数除 2 必须用 SAR）、`rol/ror`
> 例：-32（0xFFFFFFE0）shr 2 = 1073741816（错！）；sar 2 = -8（对）

**控制流**：`cmp`（做减法只留标志）、`test`（做与运算只留标志——测零用 `test eax,eax` + `jz/jnz`）
| 有符号（int） | 无符号 |
|---|---|
| JG/JGE / JL/JLE | JA/JAE / JB/JBE |
| 相等共用 JE/JNE；还有 JMP、JS/JNS、JC/JNC | |

**循环**：`loop 标号` = 自动 `dec ecx; jnz 标号`（不改标志；ECX=0 进入会转圈 42 亿次——先测零！）。嵌套循环要 **push ecx / pop ecx** 保存外层计数。

### 3.6 函数与调用约定 Calling conventions
- 调用七步：压参（右→左）→ CALL 压返回地址 → 建栈帧（push ebp; mov ebp,esp）→ 干活（参数在 [ebp+8]、[ebp+12]…，局部变量在 [ebp−4]…）→ 拆帧（mov esp,ebp; pop ebp）→ RET → 调用方清理（add esp, n）
- `__cdecl`：**调用方**清栈（C++ 默认，printf 必须用）；`__stdcall`：被调方 RET n；`__fastcall`：前两个参数进 ECX/EDX
- 返回值在 **EAX**（64 位结果 EDX:EAX）
- 调库函数：`push` 参数（右→左）→ `call printf` → `add esp, 4×参数个数`；scanf_s 要**地址**（lea）
- 保护规则：可随意用 EAX/ECX/EDX；**EBX/ESI/EDI 用完要还原**（push/pop）；EBP/ESP 不能动

### 3.7 五大示例（每个都是一次 Lab）
11.1 比较两数（cmp + je/jg）；11.2 逻辑/算术移位（SHR vs SAR）；11.3 ECX 循环计数（LOOP 求 1+…+10=55、数组求和）；11.4 栈函数（absDiff：sub + jns + neg）；11.5 选择/冒泡排序（嵌套循环、变址寻址、交换；O(n²)）

### 3.8 调试快捷键
F9 断点 / F5 运行 / F10 单步跳过 / F11 逐指令；Ctrl+Alt+D 反汇编、Ctrl+Alt+G 寄存器窗口。常见错误：x64 平台（切 x86）、操作数大小歧义（加 DWORD PTR）、ECX=0 进入 LOOP（死循环）、栈不平衡或 EBX/ESI/EDI 未还原（**块外崩溃**）、有符号数据用错跳转/移位（**答案悄悄变错**）。

---

## 四、Week 5 · 高级语言与编译器 HLL & Compilers

- **符号 tokens**：词与标点；**语法 grammar**：组词成合法语句的规则；**语义 semantics**：解释语句含义。程序语言严谨、无歧义
- HLL 可移植、易读（C/C++ 系统、Java Web/移动、Python AI）；汇编=机器指令的可读名、与 CPU 家族绑定；机器码=二进制、CPU 直接执行
- 三种翻译器：**编译器 compiler**（运行前整体翻译；C/C++）、**汇编器 assembler**（汇编→机器码）、**解释器 interpreter**（逐句翻译立即执行；交错进行）
- **链接器 linker**：把各模块的目标代码与库**连成整体**、解析外部引用（编译后外部引用仍是符号）
- C：源 → 编译 → 汇编 → 目标码 → 链接/装入 → 执行；Java：源 → 编译成 **byte code** → **JVM** 解释执行（解释器=虚拟机）
- 程序开发流程：问题 → 算法 → 选语言 → 写程序 → 编译 → 调试运行
- **算法**：逐步解决良定义问题的方法，语言无关（自然语言/伪代码）；程序=语言相关实现
- 代码复用三种方式：宏库（源码级展开）、可重定位目标库（预编译、链接）、动态库（内存共享）

---

## 五、Week 6 · 二进制算术 Binary Arithmetic

### 5.1 无符号与 BCD
- 4 位无符号 0–15；8 位 0–255
- **BCD**：每位十进制数单独用 4 位二进制表示（68 → 0110 1000）；一字节存 0–99；与 ASCII 数字末 4 位一致（'5' ASCII=0110101，BCD=0101）；费位但转字符容易

### 5.2 三种负数表示（对比表必背！）
| | 负数表示 | 零的个数 | 硬件 | 溢出处理 |
|---|---|---|---|---|
| **符号-数值** | 最高位取反 | **2 个**（+0/−0） | 加法器+减法器+比较逻辑 | 逻辑复杂 |
| **反码 one's complement** | 各位取反 | 2 个 | 只要加法器，**循环进位**（end-around carry） | 进位绕回 |
| **补码 two's complement** | 各位取反**再加 1** | **1 个** | 只要加法器 | 同号相加结果变号 |

- 补码：MSB 权重为负；4 位补码 −5 = 1011；取负：按位取反+1
- **符号扩展 sign extension**：复制符号位（110 → 1110 → 11110 都是 −2）
- 减法 A−B = A + (−B)
- 溢出判定（补码）：**两操作数符号相同，且结果符号不同** → 溢出（如 −5 + −4 = +7 ❌）；正+负不可能溢出
- C/Java 的 byte/short/int 都用补码：int 32 位范围 −2³¹ ~ 2³¹−1

### 5.3 浮点数与 IEEE 754
- 定点数缺点：小数点位置固定，表示范围窄（5.07×10³⁰ 与 9.86×10⁻³² 需 207 位）
- **规格化 normalisation**：去前导零，二进制下小数点前恒为 1（如 10.1×2⁵ → 1.01×2⁶）
- **单精度（float，32 位）**：`s(1) | exponent(8) | fraction(23)`
  - 指数用 **excess-127（偏移 127）**：真实指数 = 存储值 − 127（1~254 有效；0 和 255 保留）
  - 尾数**隐藏前导 1**（hidden bit）
- 特殊值：全 0（指数、尾数全 0）= **零**；指数全 0 + 尾数非 0 = **非规格化数**（指数按 −126、无前导 1）；指数全 1 + 尾数全 0 = **±∞**；指数全 1 + 尾数非 0 = **NaN**（如 √(−1)、∞/∞）
- float 范围约 1.2×10⁻³⁸ ~ 3.4×10³⁸（但范围内不是所有数都能表示）

---

## 六、Week 8 · RAM 与内存层次 RAM & Memory Hierarchy

- 冯·诺依曼机器：主存是 CPU 唯一的工作区；CPU 只能操作主存里的数据
- **字节寻址 byte-addressable**：一个地址指向 8 bit
- **地址宽度**决定最大内存：16 位 → 64 KB；32 位 → 4 GB；64 位 → 天文数字
- **端序 endianness**：0x12345678
  - **Little endian（x86）**：低字节在低地址（78 56 34 12）；跨宽度转换容易
  - Big endian：高字节在低地址；看符号、看字符串更自然
- 单位：1 B = 8 bit；1 KB = 2¹⁰ = 1024 B；MB = 1024 KB；GB = 1024 MB（**二进制前缀**）
- **DRAM**：电容+晶体管，便宜密度高但慢，**需要刷新**（约每 64 ms）；**SRAM**：6 管触发器，快而贵，无需刷新；**两者都易失**（断电丢数据）
- DRAM 做主存；SRAM 做缓存
- 指标：**延迟 latency**（ns，请求到首数据）与**带宽 bandwidth**（GB/s，总吞吐）
- **ROM 非易失**：Mask ROM（出厂固化）、EPROM（紫外线擦除）、EEPROM/Flash（电擦除）；**BIOS/UEFI 固件**存在 ROM 里（开机时主存是空的）
- **内存层次**：越往下——容量越大、访问时间越长、被 CPU 访问频率越低、单位成本越低

---

## 七、Week 9 · Cache、磁盘与虚拟内存（⚠️ 讲义不在库中）

> 本部分讲义（L09）未在你的 vault 里，以下为通用要点，请对照你的 W9 讲义确认。

- **Cache 缓存**：CPU 与主存之间的高速小容量存储器；依赖**局部性原理**（时间局部性 + 空间局部性）
- **磁盘 Disk**：非易失大容量，机械（HDD）或固态（SSD），比 RAM 慢几个数量级
- **虚拟内存 Virtual memory**：把磁盘当作内存的扩展；**分页 paging**（固定大小页）、**MMU** 做地址翻译、缺页（page fault）时从磁盘调入；让每个程序拥有独立的地址空间

---

## 八、备考清单 Checklist（对照题型）

- [ ] **MCQ/填空**：W2 五大组件与寄存器、FDE 循环各步、总线宽度与寻址空间、CISC/RISC、W5 翻译器对比、链接器作用、W6 补码计算/溢出/符号扩展、IEEE 754 字段与特殊值、W8 端序/SRAM-DRAM/单位换算
- [ ] **汇编**：寄存器与标志、寻址方式、LEA vs MOV、SHR vs SAR、LOOP 与嵌套循环、cmp/jcc 有符号与无符号家族、除法 cdq+idiv、printf/scanf_s 调用与清栈、__cdecl 参数与返回值、EBX/ESI/EDI 的保存
- [ ] 五道 Lab 例题（比较两数、移位、循环求和、栈函数、排序）能默写关键片段
- [ ] 模拟卷：[[CSI101 ICT 模拟卷（填空版）]]

> ⚠️ 考试禁用 AI：现在就按「闭卷手写/默写」标准准备。
