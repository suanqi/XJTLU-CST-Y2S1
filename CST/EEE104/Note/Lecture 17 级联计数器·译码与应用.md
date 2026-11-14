---
title: EEE104 Lecture 17 级联计数器·译码与应用
tags: [EEE104, 复习, 期末, Lecture17]
course: EEE104 Digital Electronics (I)
---

# Lecture 17 · 级联计数器、译码与应用
# Cascaded Counters, Decoding & Applications

> 课件：Lecture17g.pdf ｜ 上一讲：[[Lecture 16 同步计数器]] ｜ 下一讲：[[Lecture 18 移位寄存器]] ｜ 索引：[[00 EEE104 期末复习总览]]

**本节要点 In this session**：级联计数器（Cascaded counters）、计数器译码（Counter decoding）、计数器应用（Applications：数字钟）。

---

## 1. 级联计数器 Cascaded Counters

- **级联 Cascading**：一个计数器的输出驱动下一个计数器的输入，以获得**更高模数**的计数。
- **总模数 = 各级模数的乘积**（overall modulus = product of the individual moduli）。

### 1.1 同步 IC 级联（TC → CTEN）
- 计数器 1 的**使能 CTEN 接 HIGH**（始终计数）；
- 计数器 1 的**终值 TC** 接到计数器 2 的**使能 CTEN**：
  1. 起初 TC=LOW，只有计数器 1 计数；
  2. 计数器 1 计到终值 9 → **TC=HIGH**，下一时钟上升沿计数器 2 加 1；
  3. 计数器 1 清零，TC 变回 LOW。

![[EEE104/Note/assets/L17-p05.png|520]]
> ▲ 两个 decade 计数器级联（TC→CTEN，实现模 100）

- 用途：更高模数计数；**分频器**（产生更低频率且同步的时钟）。

### 1.2 截断序列 Truncated Sequences ⭐
**方法一 · 译码终态后清零 Decode the terminal count, then clear**：
- ÷6 计数器：计数到 6（0110）时译码并清零。
  - 用 **CTR DIV 10**：/SR 是**异步**输入（清零立即生效）；
  - 用 **CTR DIV 16**：/SR 是**同步**输入（清零在下一时钟沿生效）。

![[EEE104/Note/assets/L17-p09.png|520]]
> ▲ 译码清零实现截断序列（÷6）

**方法二 · 终态装载初值 Load an initial count at the terminal count**：
- **÷40,000 计数器**：终值 65,535（16 位最大）时输出 HIGH → 装载初值 **25,536 = 63C0₁₆**。
- $65{,}535 - 25{,}536 + 1 = 40{,}000$（正好 40,000 个状态）。

![[EEE104/Note/assets/L17-p11.png|520]]
> ▲ 装载初值实现 ÷40,000

## 2. 计数器译码 Counter Decoding

- **译码**：判断计数序列中**某个状态是否出现**（如译码状态 6 = 110 → 与门接 $Q_2Q_1\bar Q_0$）。

![[EEE104/Note/assets/L17-p12.png|500]]
> ▲ 译码状态 6（110）的与门接法

- **毛刺问题 Glitches**：**异步计数器**的传播延迟产生**过渡状态（transitional states）** → 译码输出出现**毛刺 glitch**。
- **解决方法**：在过渡状态结束后再**选通（strobe/gate）**译码输出。

![[EEE104/Note/assets/L17-p13.png|520]]
> ▲ 传播延迟造成的过渡状态与毛刺

## 3. 应用：数字钟 Digital Clock

![[EEE104/Note/assets/L17-p16.png|520]]
> ▲ 数字钟整体框图

- **秒、分计数器**：**÷60（模 60）计数器**（divide-by-60 counters）；
- **小时计数器**：00 → 01 → … → 12 → 01 …（**到 12 后预置回 1**：状态 12 时 $J=0,\ K=1,\ \overline{PE}=0$ → 预置 01）。

---

## 自测 Checklist

- [ ] 级联：总模数 = 各模数之积；TC→CTEN 工作过程（3 步）Cascading & TC/CTEN
- [ ] 级联用途：更高模数、分频 Applications
- [ ] 截断序列：译码终态清零（异步 /SR vs 同步 /SR 区别）Truncation by clearing
- [ ] 截断序列：终态装载初值（÷40,000：65535→63C0₁₆）Truncation by loading
- [ ] 译码状态 6（Q2Q1Q̄0）；异步计数器毛刺成因与选通消除 Glitches & strobe
- [ ] 数字钟：÷60 秒/分、小时 1–12（12 时预置 1）Digital clock
