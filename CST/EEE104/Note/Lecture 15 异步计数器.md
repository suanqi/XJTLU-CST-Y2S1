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

- 所有触发器 **J=K=1**；FF0 由 CLK 触发，FF1 由 Q0 触发，FF2 由 Q1 触发……
- n 级 → **模 $2^n$**（计 0 ~ $2^n-1$）；负沿触发为加法计数。

![[EEE104/Note/assets/L15-p05.png|520]]
> ▲ 2 位异步二进制计数器（Q0 驱动 FF1 的时钟）

- 2 位：00→01→10→11→00；3 位、4 位同理（4 位：0–15）。

## 3. 截断序列与模数 Truncated Sequences & Modulus

- n 个触发器最多 $2^n$ 个状态；计数器可以设计成只经历**更少的状态（截断序列 truncated sequence）**。
- **模数 Modulus**：计数器经历的**唯一状态数**（the number of unique states a counter will sequence through）。

### 3.1 异步十进制计数器 Asynchronous Decade Counter
- 计数 **0000 → 1001（0–9）**；一旦状态 **1010** 出现，译码器**立即复位**计数器。
- **部分译码 Partial decoding**：复位只检测 **Q1 = Q3 = 1**（即 1010 时 Q1、Q3 都为 1），不用检测全部位。

![[EEE104/Note/assets/L15-p09.png|520]]
> ▲ Decade 计数器与部分译码（Q1·Q3 → 清零）

### 3.2 异步模 12 计数器 Modulus-12 Counter
- 计数 0000 → 1011（0–11）；到 **1100** 复位（部分译码检测 Q2·Q3）。

## 4. 累积延迟 Cumulative Delay ⭐

- **传播延迟**：输入作用后输出发生变化的时间间隔。
- 异步计数器各级延迟**相加（累积）**，限制最高时钟频率、造成译码问题（毛刺）。

| IC | $t_{PHL}$ | $t_{PLH}$ |
|---|---|---|
| 74HC74A | 17 ns | 17 ns |
| 74LS74A | 40 ns | 25 ns |

![[EEE104/Note/assets/L15-p12.png|520]]
> ▲ 累积传播延迟示意

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
- [ ] 累积延迟：74HC74A/74LS74A 数据、限制时钟频率、译码毛刺 Cumulative delay
- [ ] 74LS93A：Q0→CLKB、NAND 译码复位、模 16/十进制/模 12 三种接法 74LS93A
