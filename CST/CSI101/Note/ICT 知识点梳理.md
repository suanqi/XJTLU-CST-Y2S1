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
| 寄存器                               | 作用             |
| --------------------------------- | -------------- |
| PC（program counter）               | 下一条指令的地址，随执行递增 |
| MAR（memory address register）      | 正要访问的内存地址      |
| MDR（memory data register）         | 从内存取回的数据       |
| CIR（current instruction register） | 正在执行的指令        |
| Acc（accumulator）                  | 运算结果暂存         |

> 寄存器 vs 内存：寄存器在 CPU 内部、几十个、<1 ns；内存在主板上、上亿单元、50–100 ns（约慢百倍）。
>
> **❓ 为什么这里不是 EAX、EBX、ECX？**（易混淆点）
> 这是**两套不同层次的寄存器**：
> - 本节的 PC/MAR/MDR/CIR/Acc 是 **CPU 内部概念模型**的寄存器（L02 讲「指令如何被执行」时用）；
> - 3.2 节的 **EAX/EBX/ECX/EDX/ESI/EDI/EBP/ESP** 是 **x86 程序员可见**的通用寄存器（L03–04 写汇编时用）。
> - 对应关系：PC 在 x86 上的真名是 **EIP**（指令指针）；**Acc 的角色由 EAX 承担**；而 **MAR、MDR、CIR 是 CPU 内部硬件寄存器，程序员看不见也写不了**。
> - 考试：L02 考 PC/MAR/MDR/CIR 概念；L03–04 考 EAX/EBX 等编程寄存器。

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

### 3.2 通用寄存器 General-purpose registers
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

## 七、Week 9 · Cache、磁盘与虚拟内存（L09 已补全 ✅）

### 7.1 缓存 Cache

**目的**：把一部分数据放在**离 CPU 更近**的地方以加速访问。缓存远小于主存，但访问时间只是主存的零头。
**按内容访问**：主存按**地址**访问；缓存按**内容**访问，故称 **content addressable memory（内容可寻址存储器）**。

**局部性原理 Localisation of Memory Access**（缓存能工作的根本）：
- **时间局部性 Temporal locality**：最近用过的数据，马上很可能再用（循环、重复调用）；
- **空间局部性 Spatial locality**：刚用过的数据附近的数据，马上很可能被用（数组、顺序代码）；
- 成因：程序员把相关数据聚成数组/记录、程序中的循环、编译器对代码的优化排布。
> 局部性差的例子：`myarray[0]`、`myarray[100000]`、`myarray[200000]` 这样大步跳跃访问大数组（对比顺序访问 `[0]`、`[1]`、`[2]`）。**局部性差时缓存反而降低性能**。

**缓存块的字段**：
- **tag 标签**：区分映射到同一缓存块的不同内存块；
- **valid bit 有效位**：该缓存块是否正在使用；
- **offset 偏移**：指向块内所需的数据。

**直接映射 Direct mapped cache**：N 个缓存块时，内存块 X 映射到缓存块 **Y = X mod N**。
> 例：10 个缓存块时，缓存块 7 只能装内存块 7、17、27、37…（相距 N 的块共享同一缓存块，会发生替换）。

**替换策略 Replacement policy**：
| 策略 | 做法 | 特点 |
|---|---|---|
| Optimal（最优） | 淘汰**未来最久不被使用**的块 | 需预知未来——只能当**基准 benchmark** |
| **LRU**（最近最少使用） | 淘汰**最久没被访问**的块 | 效果好但复杂（要维护每块访问历史，拖慢缓存） |
| **FIFO**（先进先出） | 淘汰**在缓存里待得最久**的块 | 简单常用 |
| Random（随机） | 随机选块替换 | 可能误伤常用块，但**永远不会 thrash**（抖动） |

**写策略 Write policy**（缓存被改、主存未改时的处理）：
- **Write-through（写直达）**：每次写**同时更新缓存和主存**（简单，但每次写都要访问主存）；
- **Write-back（写回）**：更新暂缓，直到**脏块 dirty block** 被替换时才写回主存（快，但要 dirty 位）。

**结构**：
- **Unified（统一缓存）**：指令和数据共用一个缓存；**Harvard cache**：指令缓存与数据缓存分开（局部性更好，复杂度更高）——即 L01 讲的 modified Harvard。
- **多级缓存**：L1（8–64 KB，在处理器上，约 4 ns）→ L2（64 KB–2 MB，在主板或处理器上，15–20 ns）→ … → RAM。
- **Inclusive（包含式）**：小缓存的数据保证也在下一级（可多级同时存在）；**Exclusive（独占式）**：数据只允许存在一份。权衡：访问时间 vs 存储空间 vs 电路复杂度。

### 7.2 磁盘 Disk（大容量存储 Mass Storage）

**特性**：与主存不同，**断电后数据仍然保留**（非易失）。
**种类**：HDD 机械硬盘、SSD 固态硬盘、光盘（CD-ROM、DVD）、U 盘等。

**HDD 结构**：
- 多个**盘片 platters**，两面记录信息；
- 每面 **500–2000 条磁道 tracks**；每磁道 **32–128 个扇区 sectors**；
- **扇区 sector = 最小读写单位**。
- 相同位置的磁道组成**柱面 cylinder**。

**寻址方式**：
- **CHS**（Cylinder-Head-Sector，柱面-磁头-扇区）；
- **LBA**（Logical Block Addressing，扇区的绝对编号）——CHS 可映射到 LBA。

**读写四步**：① 确定地址（CHS 或 LBA）→ ② **寻道 seek**（把磁臂移到目标磁道上方）→ ③ **旋转延迟 rotational latency**（等目标扇区转到磁头下方）→ ④ **传输 transfer**（读写该扇区）。

**访问时间公式（必考计算）**：
$$\text{Access time} = \text{queue} + \text{seek} + \text{rotational} + \text{transfer} + \text{overhead}$$

> **例题**（讲义原题）：磁盘空闲（queue = 0），overhead = 2 ms，平均寻道 12 ms，转速 7200 RPM，传输 8 KB，传输率 4 MB/s。求平均扇区访问时间。
> - 平均旋转延迟 = 半圈时间 = $\dfrac{0.5}{7200/60}=0.5/120\,\mathrm{s}=4.17\,\mathrm{ms}$
> - 传输时间 = $8\,\mathrm{KB}\ /\ 4\,\mathrm{MB/s}=0.002\,\mathrm{s}=2\,\mathrm{ms}$
> - 总时间 = 12 + 4.17 + 2 + 2 = **20.17 ms ≈ 20.2 ms**

**SSD（固态硬盘）**：
- 由 **NAND Flash** 构建（电擦除、非易失、浮栅晶体管 trapped charge）；
- **无机械部件**（没有盘片和读写臂）；
- 随机读延迟 **0.1 ms**（HDD 约 5–10 ms）；吞吐 **~500 MB/s**（HDD 80–100 MB/s）；每 GB 价格约为 HDD 的 **4–6 倍**。

**磁盘缓存 Disk cache**：用一部分主存做缓冲区临时存放磁盘数据——写操作**聚批**执行；刚写出的数据可能马上再被读，从缓存里取远快于从磁盘取。（Java `flush()` 即强制写回。）

**读与写**：把文件从磁盘装入 RAM = **reading**（加载程序、打开文件）；把 RAM 数据复制到外存 = **writing**。

### 7.3 虚拟内存 Virtual Memory

- 思想与缓存**相反**：**用低层存储器（硬盘）来"扩充"高层存储器（主存）**——把数据和代码溢写到磁盘上，相当于扩展了主存。
- 磁盘上为此保留的区域叫 **swap area（交换区）**。
- 例：物理内存上限 4 GB，虚拟内存上限 8 GB。
- 处理器 RAM 不够用时，把暂时不用的数据换出到磁盘；换回时再调入。**灵活性提升，但比直接访问 RAM 慢**。

### 7.4 云存储 Cloud Storage（了解）
- 数据存在不属于你的数据中心，经网络访问（OneDrive、Amazon S3、Google Drive、百度网盘等）；
- 背后是海量磁盘阵列，数据跨盘/机架/地域**多副本**；
- 每 GB 最便宜（冷存储几分钱/月）、延迟高且不稳定 → 用缓存和 CDN 改善；适合备份、归档、大数据、静态内容。

### 7.5 L09 讲义自测题
1. 用 Cache、RAM、Disk 组成合理的内存层次（性价比）→ **Cache → RAM → Disk**。
2. 「时间局部性：最近用过的数据更可能再次被访问。」T / F？→ **T**。
3. 保存到哪类设备，关机后数据仍保留？a. RAM b. 主板 c. **外存（secondary storage）** d. 主存 → **c**。
4. 磁盘上封闭的同心圆环称为：a. grooves b. **tracks（磁道）** c. sectors d. circles → **b**。

---

## 八、备考清单 Checklist（对照题型）

- [ ] **MCQ/填空**：W2 五大组件与寄存器、FDE 循环各步、总线宽度与寻址空间、CISC/RISC、W5 翻译器对比、链接器作用、W6 补码计算/溢出/符号扩展、IEEE 754 字段与特殊值、W8 端序/SRAM-DRAM/单位换算、W9 局部性（时间/空间）、直接映射 Y=X mod N、替换策略（LRU/FIFO/Random）、写策略（write-through/write-back）、**磁盘访问时间计算（queue+seek+rotational+transfer+overhead）**、CHS/LBA、SSD vs HDD、虚拟内存 swap area
- [ ] **汇编**：寄存器与标志、寻址方式、LEA vs MOV、SHR vs SAR、LOOP 与嵌套循环、cmp/jcc 有符号与无符号家族、除法 cdq+idiv、printf/scanf_s 调用与清栈、__cdecl 参数与返回值、EBX/ESI/EDI 的保存
- [ ] 五道 Lab 例题（比较两数、移位、循环求和、栈函数、排序）能默写关键片段
- [ ] 模拟卷：[[CSI101 ICT 模拟卷（填空版）]]

> ⚠️ 考试禁用 AI：现在就按「闭卷手写/默写」标准准备。
