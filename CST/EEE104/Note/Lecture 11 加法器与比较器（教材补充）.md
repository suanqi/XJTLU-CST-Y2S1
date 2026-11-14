---
title: EEE104 Lecture 11 加法器与比较器（教材补充）
tags: [EEE104, 复习, 期末, Lecture11]
course: EEE104 Digital Electronics (I)
---

# Lecture 11 · 加法器与比较器（教材补充）
# Adders & Comparators ⚠️

> ⚠️ 本讲课件（L11）未收录于 vault，按 Floyd《Digital Fundamentals》标准内容整理，请对照你的课件确认。
> 上一讲：[[Lecture 10 卡诺图化简]] ｜ 下一讲：[[Lecture 12 译码编码与数据选择（教材补充）]] ｜ 索引：[[00 EEE104 期末复习总览]]

**本节要点 In this session**：半加器/全加器（Half/Full adders）、串行进位加法器（Ripple carry adder）、比较器（Comparators）。

---

## 1. 加法器 Adders

### 1.1 半加器 Half Adder（加两个位）
- 输入 A、B；输出：**和 Sum $\Sigma = A \oplus B$**、**进位 Carry $C_{out} = AB$**。

| A | B | Σ | C_out |
|---|---|---|-------|
| 0 | 0 | 0 | 0 |
| 0 | 1 | 1 | 0 |
| 1 | 0 | 1 | 0 |
| 1 | 1 | 0 | 1 |

### 1.2 全加器 Full Adder（加 A、B 与低位进位 $C_{in}$）
$$\Sigma = A \oplus B \oplus C_{in}, \qquad C_{out} = AB + (A \oplus B)\,C_{in}$$

| A | B | C_in | Σ | C_out |
|---|---|------|---|-------|
| 0 | 0 | 0 | 0 | 0 |
| 0 | 0 | 1 | 1 | 0 |
| 0 | 1 | 0 | 1 | 0 |
| 0 | 1 | 1 | 0 | 1 |
| 1 | 0 | 0 | 1 | 0 |
| 1 | 0 | 1 | 0 | 1 |
| 1 | 1 | 0 | 0 | 1 |
| 1 | 1 | 1 | 1 | 1 |

### 1.3 串行进位加法器 Ripple Carry Adder
- n 个全加器**级联**：低位 $C_{out}$ 接高位 $C_{in}$，进位逐级传递（速度较慢）。
- 例：4 位加法器计算 $1101\ (13) + 0111\ (7) = 10100\ (20)$。

## 2. 比较器 Comparators

### 2.1 1 位比较器 1-Bit Comparator
- 相等 Equal：$A \odot B$（XNOR）；
- 大于 A > B：$A\bar B$；
- 小于 A < B：$\bar A B$。

### 2.2 多位比较器 Multi-Bit Comparator
- **从最高位（MSB）开始逐位比较**，先出现不同的位决定大小。
- 例：比较 1101 与 1100：前三位相同，最低位 1 > 0 → 1101 > 1100。

---

## 自测 Checklist

- [ ] 半加器：$\Sigma = A\oplus B$、$C_{out} = AB$ 及其真值表 Half adder
- [ ] 全加器：$\Sigma = A\oplus B\oplus C_{in}$、$C_{out}=AB+(A\oplus B)C_{in}$ Full adder
- [ ] 串行进位加法器结构（n 个全加器级联、进位传递）Ripple carry adder
- [ ] 比较器：1 位（$\odot$、$A\bar B$、$\bar A B$）；多位从最高位起比较 Comparator
