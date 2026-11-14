---
title: EEE104 Lecture 12 译码编码与数据选择（教材补充）
tags: [EEE104, 复习, 期末, Lecture12]
course: EEE104 Digital Electronics (I)
---

# Lecture 12 · 译码器、编码器与数据选择（教材补充）
# Decoders, Encoders, MUX & DEMUX ⚠️

> ⚠️ 本讲课件（L12）未收录于 vault，按 Floyd《Digital Fundamentals》标准内容整理，请对照你的课件确认。
> 上一讲：[[Lecture 11 加法器与比较器（教材补充）]] ｜ 下一讲：[[Lecture 13 锁存器]] ｜ 索引：[[00 EEE104 期末复习总览]]

**本节要点 In this session**：译码器（Decoders）、编码器（Encoders）、多路复用器/多路分配器（MUX / DEMUX）。

---

## 1. 译码器 Decoders（$2^n$ 选 1）

- n 位输入 → $2^n$ 个输出；每个输出对应**一种输入组合**，有效输出为**唯一的 1**（其余为 0）。
- 2–4 译码器输出：$\bar A\bar B,\ \bar A B,\ A\bar B,\ AB$（输入 AB）。
- 常用 IC：**74HC138**（3–8 译码器，带使能端）。
- 应用 Applications：地址译码、七段显示译码器（BCD → 七段码）等。

## 2. 编码器 Encoders（译码器的逆过程）

- $2^n$ 个输入 → n 位编码输出；**同一时刻只允许一个输入有效**。
- 例：8 线–3 线编码器；十进制–BCD 编码器（键盘 keypad）。
- **优先级编码器 Priority encoder**：多个输入同时有效时，对**编号最大（或设定优先级最高）**者编码。

## 3. 多路复用器 MUX（数据选择器）

- **$2^n$ 路数据输入 + n 位选择线 → 1 路输出**：选择线选中哪路，哪路数据送到输出。
- 4 选 1 MUX（选择线 $S_1S_0$）：
$$Y = \bar S_1\bar S_0 D_0 + \bar S_1 S_0 D_1 + S_1\bar S_0 D_2 + S_1 S_0 D_3$$
- 应用：数据选择、实现任意组合逻辑（把真值表接到 $D_i$ 端）。

## 4. 多路分配器 DEMUX

- 1 路数据输入 + n 位选择线 → **$2^n$ 路输出**：数据只送到选中的那一路。
- 实现 = **译码器 + 数据使能**（data input 接译码器的使能端）。

## 5. 对比速查表 Comparison

| 器件 Device | 输入 Input | 输出 Output | 功能 Function |
|---|---|---|---|
| 译码器 Decoder | n 位 | $2^n$ 路（唯一 1） | 选通某一路 Strobe one line |
| 编码器 Encoder | $2^n$ 路（唯一 1） | n 位 | 编出二进制码 Encode to binary |
| MUX | $2^n$ 数据 + n 选择 | 1 路 | 多选一 Many-to-one |
| DEMUX | 1 数据 + n 选择 | $2^n$ 路 | 一分多 One-to-many |

---

## 自测 Checklist

- [ ] 译码器：n→$2^n$、唯一 1 输出；2–4 译码器四个输出表达式 Decoder
- [ ] 编码器：一次一个输入；优先级编码器行为 Encoder & priority encoder
- [ ] 4 选 1 MUX 输出表达式 $Y=\bar S_1\bar S_0D_0+\dots+S_1S_0D_3$ MUX expression
- [ ] DEMUX = 译码器 + 使能；四器件功能对比表 Four devices comparison
