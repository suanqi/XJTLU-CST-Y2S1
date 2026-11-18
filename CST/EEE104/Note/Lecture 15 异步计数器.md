---
title: EEE104 Lecture 15 异步计数器
tags: [EEE104, 复习, 期末, Lecture15]
course: EEE104 Digital Electronics (I)
---

# Lecture 15 · 异步计数器
# Asynchronous (Ripple) Counters

> 课件：Lecture15.pdf ｜ 上一讲：[[Lecture 14 边沿触发器]] ｜ 下一讲：[[Lecture 16 同步计数器]] ｜ 索引：[[00 EEE104 期末复习总览]]

**本节要点 In this session**：计数器概述（Counter overview）、异步计数器（Asynchronous counters）、decade 与部分译码（Decade & partial decoding）、累积延迟（Cumulative delay）、IC 74LS93A。

---

## 1. 计数器概述 Counter Overview

- **计数器**：一组触发器级联完成计数操作（a group of flip-flops connected together to perform counting）。
- 分类：
  - **异步（行波 ripple）计数器**：每个触发器由**前一级输出**提供时钟（clocked by the output of the preceding flip-flop）；
  - **同步计数器**：所有触发器共用**同一个时钟**。

> 预备知识：J=K=1 时触发器在时钟沿**翻转**（toggle）。

## 2. 异步二进制计数器 Asynchronous Binary Counters

- 所有触发器 **J=K=1**；FF0  由 CLK 触发，FF1 由 Q0 触发，FF2 由 Q1 触发……
- n 级 → **模 $2^n$**（计 0 ~ $2^n-1$）；负沿触发为加法计数。

![[EEE104/Note/assets/L15-p05.png|520]]
> ▲ 2 位异步二进制计数器（Q0 驱动 FF1 的时钟）

- 2 位：00→01→10→11→00；3 位、4 位同理（4 位：0–15）。

## 3. 截断序列与模数 Truncated Sequences & Modulus

- n 个触发器最多 $2^n$ 个状态；计数器可以设计成只经历**更少的状态（截断序列 truncated sequence）**。
- **模数 Modulus**：计数器经历的**唯一状态数**（the number of unique states a counter will sequence through）。

### 3.1 为什么最多是 $2^n$ 个状态？ Why at most $2^n$ states?

- 每个触发器（flip-flop）存 **1 位**，只有 0/1 两种取值；
- n 个触发器组合起来共有 $2\times2\times\cdots\times2 = \mathbf{2^n}$ 种状态（每种组合是一个状态）。
  > *With n flip-flops, the maximum number of states of a counter is $2^n$.*
- 例：4 个触发器 → $2^4 = 16$ 个状态：0000、0001、…、1111（对应 0–15）。
- 把 **$2^n$ 个状态全部走完**的计数器叫**全模计数器**（full-modulus counter），如 4 位二进制计数器的模数是 16。

### 3.2 模数的含义 What is the modulus?

- **模数 Modulus = 计数序列循环重复前，所经历的"唯一状态"的个数**。
  > *The number of unique states that a counter will sequence through.*
- 强调"**唯一（unique）**"是因为：复位瞬间计数器会**一闪而过**某个状态（如 decade 计数器里的 1010），这个一闪而过的状态**不算**进计数序列（见 3.3）。
- 常见模数举例：

| 计数器 Counter | 序列 Sequence | 模数 Modulus |
|---|---|---|
| 4 位二进制 | 0000–1111（0–15） | **16**（全模） |
| 模 12 | 0000–1011（0–11） | **12** |
| 十进制 decade | 0000–1001（0–9） | **10** |
| ÷6 分频 | 0000–0101（0–5） | **6** |

- 实用含义：计数器作**分频器**时，**输出频率 = 输入频率 ÷ 模数**。
  > 例：模 10 计数器输入 100 Hz → 输出 10 Hz。

### 3.3 截断序列是怎么实现的？ How a truncated sequence works

- **截断 Truncate** = 把完整的 $2^n$ 序列"砍短"：不数到 1111，而是在某个中间状态之后**提前跳回 0000**。
- 类比：两位十进制本能数 0–99，现在规定数到 9 就回到 0——只用到了 100 个值里的 10 个。
- **实现方法**：用译码门（NAND）**检测"本不该出现"的下一个状态**，把译码输出接到计数器的**清零端 CLEAR**，清零信号一到计数器立刻回到 0000。

**以十进制计数器（模 10）为例，逐步走一遍**：
1. 正常计数：0000 → 0001 → 0010 → … → **1001**（即十进制 9）✅ 每个状态都完整停留一个时钟周期；
2. 下一拍计数器进入 **1010**（十进制 10）——**这是"不允许存在"的状态**；
3. 译码门检测到 1010（只需看 **Q1=1 且 Q3=1**：在 0–9 的十个状态里 Q1、Q3 从未同时为 1，所以一旦同为 1 必定是 1010）→ 输出清零信号 → 计数器**立即复位**；
4. 序列变成：0000 → … → 1001 →（1010 一闪而过）→ 0000 → … 循环；
5. 真正停留的状态 = 0000–1001 共 **10 个** → 模数 **10**。

> **为什么检测 1010 而不是 1001？** 若在 1001 就复位，1001 刚出现就被清掉，"9"这个数根本数不出来（只存在几纳秒）。所以设计成：让 1001 完整停留一拍，等它数到 1010 的瞬间再复位。被清掉的 1010 只是**过渡状态（transitional state）**，因此不计入模数。

**模 12 计数器同理**：
- 目标序列：0000 → 1011（0–11）共 12 个状态；
- 检测 1100（Q3=Q2=1，0–11 中 Q3、Q2 从未同时为 1）→ 复位；
- 序列：0000 → … → 1011 →（1100 一闪）→ 0000 → …，模数 **12**。

### 3.4 异步十进制计数器 Asynchronous Decade Counter
- 计数 **0000 → 1001（0–9）**；一旦状态 **1010** 出现，译码器**立即复位**计数器。
- **部分译码 Partial decoding**：复位只检测 **Q1 = Q3 = 1**（即 1010 时 Q1、Q3 都为 1），不用检测全部位。

![[EEE104/Note/assets/L15-p09.png|520]]
> ▲ Decade 计数器与部分译码（Q1·Q3 → 清零）

### 3.5 异步模 12 计数器 Modulus-12 Counter
- 计数 0000 → 1011（0–11）；到 **1100** 复位（部分译码检测 Q2·Q3）。

## 4. 累积延迟 Cumulative Delay ⭐

- **传播延迟 Propagation delay**：输入作用后输出发生变化的时间间隔。
  > *The propagation delay time is the time interval for the output to change after an input has been applied.*
- 异步计数器各级延迟**相加（累积）**，限制最高时钟频率、造成译码问题（毛刺）。

| IC | $t_{PHL}$ | $t_{PLH}$ |
|---|---|---|
| 74HC74A | 17 ns | 17 ns |
| 74LS74A | 40 ns | 25 ns |

![[EEE104/Note/assets/L15-p12.png|520]]
> ▲ 累积传播延迟示意

### 4.1 74HC74A vs 74LS74A：区别是什么？ What's the difference? ⭐

> ⚠️ **课件说明范围**：Lecture15 只在上面这一页用两者的传播延迟数值举例，**没有展开 74HC74A 的内部结构**——全部 16 份课件中也仅此一处提及这两个型号。以下为**教材/数据手册补充**（Floyd & datasheet）。

**共同点 Common**：两者都是 **74 系列"双 D 触发器"（dual D flip-flop）**——一个 14 脚封装里含**两个独立的正沿触发 D 触发器**，各带**异步预置 PRE 与异步清零 CLR**。型号解读：**74** = 商用级，**A** = 7474 的改进版。

| 对比项 Item | **74HC74A**（CMOS） | **74LS74A**（TTL） |
|---|---|---|
| 工艺 Technology | 高速 CMOS（High-speed CMOS） | 低功耗肖特基 TTL（Low-power Schottky） |
| 电源电压 VCC | **2–6 V**（范围宽，见 [[Lecture 06 晶体管与数字集成电路\|Lecture 06]] 的 $V_{CC}$ 表） | 5 V（TTL 标准 4.5–5.5 V） |
| $t_{PHL}$（高→低） | **17 ns** ✅ 快 | 40 ns |
| $t_{PLH}$（低→高） | **17 ns**（两向对称 symmetric） | 25 ns（不对称 asymmetric） |
| 功耗 Power | **极低**（静态几乎为零，仅翻转瞬间耗电） | 较高（静态持续耗电） |
| 输入阻抗 Input impedance | 极高（MOS 栅极，几乎不取电流） | 较低（需提供输入电流） |

**在计数器语境下的意义 Meaning in this context**：
- 异步计数器的总延迟 = 各级延迟**逐级相加**（累积），因此每级**越快、越对称**，允许的**最高时钟频率越高**；
- 课件用这两个型号对比正是要说明：CMOS（HC）比 TTL（LS）**更快**，且 HC 的 $t_{PHL} \approx t_{PLH}$（高低跳变等时），更利于高速计数。

## 5. IC 异步计数器 74LS93A

- **Q0 必须与 CLK B 相连**（当作计数器使用时）；
- 可用 **NAND 门作译码器**实现复位，构成：
  - **模 16 计数器**（Modulus-16，Q0 输出接 CLKB）；
  - **十进制计数器**（decade：0000–1001，译码 Q1·Q3 复位）；
  - **模 12 计数器**（Modulus-12：0000–1011，译码 Q2·Q3 复位）。

![[EEE104/Note/assets/L15-p13.png|520]]
> ▲ 74LS93A 内部结构与接线

---

## 自测 Checklist

- [ ] 异步 vs 同步计数器定义（前级输出/共同时钟）Async vs sync definition
- [ ] 异步二进制计数器：J=K=1、级联接法、模 $2^n$ Ripple counter
- [ ] 模数定义；decade（0000–1001、1010 复位）与部分译码（只检测 Q1Q3）Decade & partial decoding
- [ ] 模 12（1100 复位，检测 Q2Q3）Modulus-12
- [ ] 累积延迟：74HC74A vs 74LS74A 区别（CMOS/TTL、2–6V/5V、17/17 vs 40/25 ns、功耗）；累积效应 → 限频、译码毛刺 Cumulative delay
- [ ] 74LS93A：Q0→CLKB、NAND 译码复位、模 16/十进制/模 12 三种接法 74LS93A
