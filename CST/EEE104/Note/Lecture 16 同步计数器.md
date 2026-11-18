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

> 📌 **读引脚三步法**（考试问"某引脚有效电平/同步异步/优先级"时按此回答）：
> ① **有效电平**：引脚名上有**横杠/气泡 → 低有效 active-LOW**（如 CLR̄、LOAD̄、CTEN̄、RCŌ）；无横杠 → 高有效（如 ENT、ENP、D/U、MAX/MIN）。
> ② **与 CLK 的关系**：**同步 synchronous** = 电平在**时钟上升沿**被采样、边沿才生效（如 163 的 CLR/LOAD）；**异步 asynchronous** = 与时钟无关、**立即生效**（如 160 的 CLR）；**组合输出** = RCO、MAX/MIN 这类输出，随计数器状态**立即变化**，不等时钟沿。
> ③ **优先级**：多个控制端同时有效时谁说了算（一般：清零 > 预置 > 计数 > 保持）。

### 3.1 74HC163 — 4 位同步二进制计数器（0–15）⭐

| 引脚 Pin | 有效电平 Active level | 与 CLK 的关系 Clock relation | 功能 Function |
|---|---|---|---|
| **CLR**（清零） | **低有效** active-LOW | **同步**（上升沿生效） | 在时钟沿把计数清零 Q=0000 |
| **LOAD**（预置） | **低有效** active-LOW | **同步**（上升沿生效） | 在时钟沿装入并行数据 Q←D3D2D1D0 |
| **ENT / ENP**（使能） | **高有效** active-HIGH | 电平信号，**在时钟沿被采样** | 两者都 =1 才计数；**ENT 还控制 RCO**（级联时用，见 Lecture 17） |
| **RCO**（行波输出） | **高有效**（输出） | **组合输出**（随状态立即变，不随边沿） | ENT=1 且计数到 **15** 时 RCO=1 |

**优先级 Priority（同时有效时从高到低）**：
$$\text{CLR（清零）} > \text{LOAD（预置）} > \text{计数（ENP=ENT=1）} > \text{保持（ENP·ENT=0）}$$

- CLR 与 LOAD 都是**同步**输入：两者同时为低时，在同一个上升沿**清零优先**，预置被忽略。
- 时钟为**上升沿触发**。

![[EEE104/Note/assets/L16-p09.png|500]]
> ▲ 74HC163 逻辑图与引脚功能

### 3.2 74HC160 — 4 位同步十进制计数器（0–9）

| 引脚 Pin | 有效电平 | 与 CLK 的关系 | 功能 |
|---|---|---|---|
| **CLR**（清零） | **低有效** | **异步** ⚡（**立即清零，不等时钟！**） | CLR=0 的瞬间 Q=0000 |
| **LOAD**（预置） | **低有效** | **同步**（上升沿生效） | 时钟沿装入并行数据 |
| **ENT / ENP** | **高有效** | 沿采样 | 两者都 =1 才计数 |
| **RCO** | **高有效**（输出） | 组合输出 | ENT=1 且计数到 **9** 时 RCO=1 |

**优先级 Priority**：
$$\text{CLR（异步，随时立即生效）} > \text{LOAD（同步）} > \text{计数} > \text{保持}$$

> ⭐ **考试对比考点**：74HC160 与 74HC163 结构几乎相同，**唯一关键区别就是 CLR**——160 的 CLR 是**异步**（立即清零）、163 的 CLR 是**同步**（边沿清零）。异步清零不需要时钟，所以优先级最高。

### 3.3 74LS190 — 可逆十进制计数器（加减 Up/Down）

| 引脚 Pin | 有效电平 | 与 CLK 的关系 | 功能 |
|---|---|---|---|
| **CTEN**（计数使能） | **低有效** active-LOW | 电平信号，沿采样 | CTEN=0 才计数；CTEN=1 保持（级联时接前级 TC，见 Lecture 17） |
| **D/U**（方向） | **高有效**（1=减） | 电平信号，沿采样 | D/U=**0 加计数（up）**；D/U=**1 减计数（down）** |
| **LOAD**（预置） | **低有效** | 课件标注**同步** ⚠️（见下方注） | 装入并行数据（装载优先于计数） |
| **MAX/MIN** | **高有效**（输出） | 组合输出 | 计到 **1001（加）或 0000（减）**时 = HIGH |
| **RCO**（行波输出） | **低有效**（输出） | 组合输出 | 计数到 **9 时 RCO=0**（用于级联） |

**优先级 Priority**：
$$\text{LOAD（预置）} > \text{计数（CTEN=0）}$$

> ⚠️ **关于 74LS190 的 LOAD**：本课件标注为"同步预置"（synchronous preset），考试按课件口径记忆；但多数数据手册（如 TI）把 74LS190 的 LOAD 列为**异步装载**（低电平立即装载、不等时钟）。若题目出现冲突，以课件为准。

![[EEE104/Note/assets/L16-p16.png|500]]
> ▲ 74LS190 逻辑图与引脚功能

### 3.4 三芯片引脚速查表 Quick Reference ⭐

| 功能 | 74HC163 | 74HC160 | 74LS190 |
|---|---|---|---|
| 清零 Clear | CLR̄：低有效·**同步** | CLR̄：低有效·**异步** ⚡ | —（可 LOAD 0000） |
| 预置 Load | LOAD̄：低有效·同步 | LOAD̄：低有效·同步 | LOAD̄：低有效·课件标同步 |
| 使能 Enable | ENT、ENP：高有效（都=1 才计数） | ENT、ENP：高有效 | CTEN̄：**低有效**（=0 才计数） |
| 方向 Direction | — | — | D/U：高=减、低=加 |
| 终值输出 Terminal | RCO：**高有效**@15 | RCO：**高有效**@9 | MAX/MIN：高有效；RCO：**低有效**@9 |
| 优先级 Priority | CLR > LOAD > 计数 > 保持 | **异步 CLR** > LOAD > 计数 | LOAD > 计数 |

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
- [ ] 74HC163：CLR̄/LOAD̄ 低有效·同步；ENT/ENP 高有效；RCO 高有效@15；优先级 CLR>LOAD>计数>保持
- [ ] 74HC160：CLR̄ 低有效·**异步**（立即清零，优先级最高）；其余同 163；RCO 高有效@9
- [ ] 74LS190：CTEN̄ 低有效；D/U 高=减；LOAD̄ 优先；MAX/MIN 高有效@1001/0000；RCO **低有效**@9
- [ ] 减计数方程（$J_1=K_1=\bar Q_0$、$J_2=K_2=\bar Q_0\bar Q_1$）Up/down counters
