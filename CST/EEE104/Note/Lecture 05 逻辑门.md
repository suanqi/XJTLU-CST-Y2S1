---
title: EEE104 Lecture 05 逻辑门
tags: [EEE104, 复习, 期末, Lecture05]
course: EEE104 Digital Electronics (I)
---

# Lecture 05 · 逻辑门
# Logic Gates

> 课件：Lecture05.pdf ｜ 上一讲：[[Lecture 04 有符号数与运算]] ｜ 下一讲：[[Lecture 06 晶体管与数字集成电路]] ｜ 索引：[[00 EEE104 期末复习总览]]

**本节要点 In this session**：门与真值表（Gates & truth tables）、五种基本门 + XOR/XNOR、时序图（Timing diagrams）、布尔表达式（Boolean expressions）。

---

## 1. 基本概念 Basics

- **门 Gate**：执行基本逻辑运算的电路（a circuit that performs a basic logic operation）。
- 五种基本门：反相器 Inverter、与 AND、或 OR、与非 NAND、或非 NOR。
- **XOR / XNOR** 是基本门的组合，但常被当作基本门处理（often treated as basic gates）。
- **真值表 Truth table**：列出每种输入组合对应输出（逻辑电平与 0/1）的表。n 输入 → $N = 2^n$ 种组合。
- **时序图 Timing diagram**：按时间轴显示多个波形关系的图。
- **布尔代数 Boolean algebra**：逻辑电路的数学（variable 取值 0/1）。

## 2. 七种门 The Seven Gates

### 2.1 反相器 Inverter（NOT）
- 输出是输入的取反：输入 HIGH → 输出 LOW；输入 LOW → 输出 HIGH。
- 表达式：$X = \bar A$（读作 "X equals A bar / not A"）。
- **有效电平 Active levels**：线上**没有小圆圈**（气泡 bubble）= 高有效 active-HIGH；**有气泡** = 低有效 active-LOW。

![[EEE104/Note/assets/L05-p04.png|500]]
> ▲ 反相器符号（distinctive shape 与矩形符号）、气泡含义

![[EEE104/Note/assets/L05-p06.png|500]]
> ▲ 反相器时序图：输出脉冲是输入的互补（inverted/complement）

### 2.2 与门 AND
- **全 1 出 1**：所有输入 HIGH → 输出 HIGH；任一输入 LOW → 输出 LOW。
- 表达式：$X = AB$（= 布尔乘法）。
- 真值表（2 输入）：00→0，01→0，10→0，**11→1**。
- 脉冲操作：按电平不变的每个时间区间套真值表。

### 2.3 或门 OR
- **有 1 出 1**：任一输入 HIGH → 输出 HIGH；全 LOW → 输出 LOW。
- 表达式：$X = A + B$（= 布尔加法，注意 $1+1=1$）。
- 真值表：00→0，01→1，10→1，**11→1**。

### 2.4 与非门 NAND（NOT-AND）
- AND 后接反相器。**有 0 出 1，全 1 出 0**。表达式：$X = \overline{AB}$。
- **负或等价形式 negative-OR equivalent**：NAND = 输入全为低有效的 OR 门。

![[EEE104/Note/assets/L05-p16.png|500]]
> ▲ NAND 符号（含负或等价符号）与真值表

### 2.5 或非门 NOR（NOT-OR）
- OR 后接反相器。**全 0 出 1，有 1 出 0**。表达式：$X = \overline{A+B}$。
- **负与等价形式 negative-AND equivalent**：NOR = 输入全为低有效的 AND 门。

### 2.6 异或门 XOR（Exclusive-OR）
- 只有两个输入。**输入不同出 1，相同出 0**。
- 表达式：$X = \bar A B + A \bar B = A \oplus B$。

![[EEE104/Note/assets/L05-p22.png|500]]
> ▲ XOR 符号、真值表与实现电路

### 2.7 异或非门 XNOR（Exclusive-NOR）
- XOR 输出取反。**输入相同出 1，不同出 0**。
- 表达式：$X = \bar A \bar B + AB = (A+B)(\bar A + \bar B) = \overline{A \oplus B}$。

![[EEE104/Note/assets/L05-p25.png|500]]
> ▲ XNOR 符号、真值表与表达式

### 2.8 速查表 Quick Reference

| 门 Gate | 口诀 Rule | 表达式 Expression |
|---|---|---|
| AND | 全 1 出 1 | $X = AB$ |
| OR | 有 1 出 1 | $X = A+B$ |
| NAND | 有 0 出 1（= 负或） | $X = \overline{AB}$ |
| NOR | 全 0 出 1（= 负与） | $X = \overline{A+B}$ |
| XOR | 不同出 1 | $X = A \oplus B$ |
| XNOR | 相同出 1 | $X = \overline{A \oplus B}$ |

---

## 自测 Checklist

- [ ] 七种门的符号（区分有无气泡 active-HIGH/LOW）、真值表默写 Symbols & truth tables
- [ ] 门表达式写法与读法（如 "X equals A bar"）Expressions
- [ ] 会画时序图：逐区间套真值表 Timing/pulsed operation
- [ ] NAND=负或、NOR=负与 的等价形式 Equivalent forms
- [ ] XOR/XNOR 表达式与真值表（两输入、不同/相同出 1）
