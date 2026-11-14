---
title: EEE104 Lecture 04 有符号数与运算
tags: [EEE104, 复习, 期末, Lecture04]
course: EEE104 Digital Electronics (I)
---

# Lecture 04 · 有符号数与运算
# Signed Numbers & Arithmetic Operations

> 课件：Lecture04.pdf ｜ 上一讲：[[Lecture 03 反码补码·十六进制与BCD]] ｜ 下一讲：[[Lecture 05 逻辑门]] ｜ 索引：[[00 EEE104 期末复习总览]]

**本节要点 In this session**：有符号数表示（Signed numbers）、有符号加减乘除与溢出（Arithmetic operations & overflow）。

---

## 1. 补码表示有符号数 Signed Numbers in 2's Complement

- **符号位 Sign bit**：有符号二进制数的**最左位**，0 = 正、1 = 负。
  - *The left-most bit is the sign bit: 0 positive, 1 negative.*
- 计算机等数字系统普遍使用 **2's complement（补码）系统**：
  - **正数** = 0 符号位 + 真值幅度位，如 $+25 = 00011001$；
  - **负数** = 对应正数的补码，如 $-25 = 11100111$（取反 11100110 → +1）。

```text
original        00011001 (+25)
1's complement  11100110
2's complement  11100111 (−25)
```

- **补码的补码回到原数**：$-(-25) = +25$（对 11100111 再取补码得 00011001）。
- **符号扩展 Sign extension**：值不变。
  - 正数左侧**补 0**：$011\ (+3) = 00011\ (+3)$；
  - 负数左侧**补 1**：$101\ (-3) = 11101\ (-3)$。

### 1.1 有符号数的十进制值 Decimal value
按位权求和，其中**符号位的权值为负**：
$101_2 = -1\cdot2^2 + 0\cdot2^1 + 1\cdot2^0 = \mathbf{-3}$

### 1.2 取值范围 Range
- n 位共有 $2^n$ 种组合（8 位 → 256 个数）；
- 范围：$-2^{n-1} \sim +2^{n-1}-1$（8 位 → **−128 ～ +127**）。

## 2. 有符号运算 Operations with Signed Numbers

### 2.1 加法 Addition
- 两数直接相加，**丢弃最终进位**（discard any final carry bit）。
- **溢出 Overflow**：两数之和需要的位数超过两数的位数。
  - *Overflow occurs only when both numbers are positive or both are negative.*
  - **只有同号相加（正+正、负+负）才可能溢出**；正+负永不溢出。

![[EEE104/Note/assets/L04-p12.png|520]]
> ▲ 溢出示例：$0111(+7)+0001(+1)=1000$（4 位应表示 −8 ❌）

### 2.2 减法 Subtraction
- 减法通过**加法**实现：**把减数取补码后与被减数相加**。
  - *Change the sign of the subtrahend and add: subtracting +6 equals adding −6.*
- 改变符号 = 对该数取 2's complement。

### 2.3 乘法 Multiplication — 部分积法 Partial Products Method
1. 按**正数**计算两个幅值的乘积；
2. 加上符号位 0；若两数**异号**（乘积为负），对结果**取补码**。

![[EEE104/Note/assets/L04-p16.png|520]]
> ▲ 例：$+83\ (01010011)\times -59\ (11000101)$ → 幅值乘积 4897 → 异号 → **−4897**

### 2.4 除法 Division — 反复减法 Repeated Subtraction
1. 商初始化为 0；
2. 用被除数（或部分余数）减去除数：
   - 余数为**正** → 商 +1，重复；
   - 余数为**0** → 商 +1，结束；
   - 余数为**负** → 结束；
3. 商的符号由被除数与除数的符号决定。

---

## 自测 Checklist

- [ ] 补码表示正/负数（符号位 0/1、负数 = 正数的补码）2's complement representation
- [ ] 补码的补码回到原数；符号扩展（补 0/补 1）Sign extension
- [ ] 有符号值计算（符号位权值为负）；范围 $-2^{n-1}\sim 2^{n-1}-1$ Range
- [ ] 加法丢弃最终进位；**溢出判定：同号相加才可能溢出** Overflow rule
- [ ] 减法 = 减数取补码后相加；乘法部分积法（异号取补）；除法反复减法
