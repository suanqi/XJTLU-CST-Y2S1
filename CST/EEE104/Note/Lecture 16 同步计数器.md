---
title: EEE104 Lecture 16 同步计数器
tags: [EEE104, 复习, 期末, Lecture16]
course: EEE104 Digital Electronics (I)
---

# Lecture 16 · 同步计数器
# Synchronous Counters

> 课件：Lecture16.pdf ｜ 上一讲：[[Lecture 15 异步计数器]] ｜ 下一讲：[[Lecture 17 级联计数器·译码与应用]] ｜ 索引：[[00 EEE104 期末复习总览]]

**本节要点 In this session**：同步二进制计数器（Synchronous binary counters）、同步十进制计数器（Decade）、加减计数器（Up/down）、IC：74HC163 / 74HC160 / 74LS190。

---

## 1. 同步二进制计数器 Synchronous Binary Counters

- **所有触发器由同一时钟 CLK 触发**（同时翻转，速度快，无累积延迟）。
- **设计方法 Design method**：看每个触发器在哪些状态需要翻转，写出 **J=K 方程**（因为翻转模式要求 J=K=1，所以 J 与 K 接相同逻辑）：

| 触发器 FF | 翻转条件 Toggle condition | J=K 方程 Equation |
|---|---|---|
| Q0 | 每个时钟都翻转 | $J_0 = K_0 = 1$ |
| Q1 | Q0 = 1 时翻转 | $J_1 = K_1 = Q_0$ |
| Q2 | Q0 = Q1 = 1 时翻转（状态 011、111） | $J_2 = K_2 = Q_0 Q_1$ |
| Q3 | Q0=Q1=Q2=1 时翻转（状态 0111、1111） | $J_3 = K_3 = Q_0 Q_1 Q_2$ |

![[EEE104/Note/assets/L16-p06.png|520]]
> ▲ 4 位同步二进制计数器（0–15）的 J=K 方程推导

## 2. 同步十进制计数器 Synchronous Decade Counter ⭐

- 计数 0000 → 1001（0–9）。各触发器翻转状态：
  - Q0 总翻转；
  - Q1 在状态 0001、0011、0101、0111 翻转；
  - Q2 在状态 0011、0111 翻转；
  - Q3 在状态 0111、1001 翻转。
- **J=K 方程**：

$$J_0 = K_0 = 1,\quad J_1 = K_1 = Q_0\bar Q_3,\quad J_2 = K_2 = Q_0Q_1,\quad J_3 = K_3 = Q_0Q_1Q_2 + Q_0Q_3$$

![[EEE104/Note/assets/L16-p07.png|520]]
> ▲ 同步 decade 计数器设计

## 3. IC 同步计数器 IC Synchronous Counters

### 3.1 74HC163 — 4 位同步二进制计数器（0–15）
- **CLR：同步清零**（synchronous clear）；
- **LOAD：同步预置**（synchronous preset）；
- **ENT、ENP：使能**（enable）；
- **RCO：行波时钟输出**（ripple clock output），**计数 15 时为 1**。

![[EEE104/Note/assets/L16-p09.png|500]]
> ▲ 74HC163 逻辑图与引脚功能

### 3.2 74HC160 — 4 位同步十进制计数器（0–9）
- **CLR：异步清零**（asynchronous clear）；
- LOAD：同步预置；ENT、ENP：使能；
- **RCO：计数 9 时为 1**。

### 3.3 74LS190 — 可逆十进制计数器（加减）
- **CTEN：使能**（enable）；
- **D/U：方向**（down/up）；
- **LOAD：同步预置**；
- **MAX/MIN：计数 1001 或 0000 时为 HIGH**；
- **RCO：计数 9 时为 0**（ripple clock output is 0 at count 9）。

![[EEE104/Note/assets/L16-p16.png|500]]
> ▲ 74LS190 逻辑图与引脚功能

## 4. 加减计数器 Up/Down Synchronous Counters

- 可逆计数器：可沿序列两个方向计数（progressing in either direction）。
- **减计数模式**（count-down）：
  - Q0 总翻转：$J_0 = K_0 = 1$；
  - Q1 在状态 110、100、010、000 翻转：**$J_1 = K_1 = \bar Q_0$**；
  - Q2 在状态 100、000 翻转：**$J_2 = K_2 = \bar Q_0 \bar Q_1$**。

![[EEE104/Note/assets/L16-p13.png|520]]
> ▲ 减计数模式的 J=K 方程推导

| 模式 Mode | $J_1 = K_1$ | $J_2 = K_2$ |
|---|---|---|
| 加 Up | $Q_0$ | $Q_0 Q_1$ |
| 减 Down | $\bar Q_0$ | $\bar Q_0 \bar Q_1$ |

---

## 自测 Checklist

- [ ] 同步计数器：共同时钟；由翻转状态写 J=K 方程（$J_0=K_0=1$、$J_1=K_1=Q_0$…）Design method
- [ ] 4 位同步二进制计数器的四个方程 4-bit binary counter
- [ ] 十进制计数器方程：$J_1=K_1=Q_0\bar Q_3$、$J_3=K_3=Q_0Q_1Q_2+Q_0Q_3$ Decade equations
- [ ] 74HC163（同步 CLR/LOAD、RCO@15）/ 74HC160（异步 CLR、RCO@9）IC pins
- [ ] 74LS190（CTEN、D/U、LOAD、MAX/MIN@1001/0000、RCO@9 为 0）
- [ ] 减计数方程（$J_1=K_1=\bar Q_0$、$J_2=K_2=\bar Q_0\bar Q_1$）Up/down counters
