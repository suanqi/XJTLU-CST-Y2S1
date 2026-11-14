---
title: EEE104 Lecture 02 二进制数与转换运算
tags: [EEE104, 复习, 期末, Lecture02]
course: EEE104 Digital Electronics (I)
---

# Lecture 02 · 二进制数与转换运算
# Binary Numbers, Conversions & Arithmetic

> 课件：Lecture02.pdf ｜ 上一讲：[[Lecture 01 模拟量与数字量]] ｜ 下一讲：[[Lecture 03 反码补码·十六进制与BCD]] ｜ 索引：[[00 EEE104 期末复习总览]]

**本节要点 In this session**：二进制数（Binary numbers）、十进制 ↔ 二进制转换（Conversion）、二进制四则运算（Binary arithmetic）。

---

## 1. 二进制数 Binary Numbers

### 1.1 计数 Counting in binary
- 十进制 Decimal：十个数字 0–9，**不同位置赋予 10 的幂作权值**（weights are powers of ten），数值 = 各位加权和。
- 二进制 Binary：只有 0、1，权值是 **2 的幂**。
- 计数过程：0, 1 → 加一位继续：10, 11 → 100, 101, 110, 111 → ……
- **n 位二进制能表示 $2^n$ 个数：0 ～ $2^n-1$**。
  - *With n bits you can count up to $2^n-1$.*
  > 例：2 位 → 0–3；3 位 → 0–7；4 位 → 0–15；8 位 → 0–255。

### 1.2 权值结构与 LSB / MSB
- **LSB（least significant bit，最低有效位）**：最右位，权重 $2^0$；
- **MSB（most significant bit，最高有效位）**：最左位，权重最大。
- 加权展开：$1011_2 = 1\cdot2^3 + 0\cdot2^2 + 1\cdot2^1 + 1\cdot2^0 = 11_{10}$
  - *The value of a binary number is the sum of the weighted bits.*

## 2. 进制转换 Conversions

### 2.1 二进制 → 十进制 Binary-to-Decimal
**把所有为 1 的位的权值相加**（Add the weights of all bits that are 1）。
> 例：$10110_2 = 16+4+2 = 22_{10}$

### 2.2 十进制 → 二进制 Decimal-to-Binary
**方法一 · 凑权值法 Sum-of-weights method**：
1. 找 ≤ 该数的**最大 2 的幂**；
2. 减去它，对余数重复；
3. 直到余数为 0。每个用到的权值位置写 1，其余写 0。

**方法二 · 除 2 取余法 Repeated division by 2**（整数）：
1. 反复除以 2 直到商为 0；
2. 依次取余数，**第一个余数是 LSB**（the first remainder is the LSB）。

![[EEE104/Note/assets/L02-p10.png|480]]
> ▲ 除 2 取余示例：$25 \div 2 = 12 \cdots 1$（LSB）… → $25_{10} = 11001_2$

### 2.3 十进制小数 → 二进制 Fractions
**乘 2 取整法 Repeated multiplication by 2**：
1. 反复乘以 2，每次取出整数部分（carry），对剩余小数部分继续；
2. 直到小数部分为 0 或达到所需精度；
3. **第一个取出的整数是 MSB**（the first carry is the MSB）。

![[EEE104/Note/assets/L02-p12.png|480]]
> ▲ 示例：$0.625 \times 2 = 1.25$（取 1，MSB）→ $0.25\times2=0.5$（取 0）→ $0.5\times2=1.0$（取 1）→ **$0.101_2$**

## 3. 二进制四则运算 Binary Arithmetic

| 运算 Operation | 规则 Rules | 课件示例 |
|---|---|---|
| 加法 Addition | $0+0=0,\ 0+1=1,\ 1+0=1,\ 1+1=10$（本位 0，**进位 carry** 1） | 下图 |
| 减法 Subtraction | $0-0=0,\ 1-1=0,\ 1-0=1,\ 0-1$ 需向高位**借位 borrow**（借 1 当 2） | 下图 |
| 乘法 Multiplication | 同十进制：生成**部分积 partial products**，左移相加 | 下图 |
| 除法 Division | 同十进制：试商、乘、减 | 下图 |

![[EEE104/Note/assets/L02-p13.png|520]]
> ▲ 二进制加法（含进位）

![[EEE104/Note/assets/L02-p14.png|520]]
> ▲ 二进制减法（含借位）

![[EEE104/Note/assets/L02-p15.png|520]]
> ▲ 二进制乘法（部分积）

![[EEE104/Note/assets/L02-p16.png|520]]
> ▲ 二进制除法（同十进制步骤）

---

## 自测 Checklist

- [ ] n 位二进制范围 $0\sim2^n-1$；LSB/MSB 位置 Binary counting & LSB/MSB
- [ ] 二进制 ↔ 十进制互转（凑权值 / 除 2 取余 / 乘 2 取整）All three conversion methods
- [ ] 二进制加（进位）、减（借位）、乘（部分积）、除 Add/subtract/multiply/divide
- [ ] 能独立完成 $1011+110$、$1101-101$、$101\times11$、$1100\div10$
