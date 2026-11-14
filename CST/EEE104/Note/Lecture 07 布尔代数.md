---
title: EEE104 Lecture 07 布尔代数
tags: [EEE104, 复习, 期末, Lecture07]
course: EEE104 Digital Electronics (I)
---

# Lecture 07 · 布尔代数
# Boolean Algebra & Logic Simplification

> 课件：EEE104_Lecture_07.pdf ｜ 上一讲：[[Lecture 06 晶体管与数字集成电路]] ｜ 下一讲：[[Lecture 08 组合逻辑与通用门]] ｜ 索引：[[00 EEE104 期末复习总览]]

**本节要点 In this session**：布尔运算（Boolean operations）、定律与 12 条规则（Laws & rules）、德摩根定理（DeMorgan's theorems）、代数化简（Simplification）。

---

## 1. 基本概念 Boolean Operations

- **布尔代数 Boolean algebra**：逻辑函数的数学。
- **变量 Variable**：代表逻辑量的符号，取值 1 或 0。
- **补 Complement**：变量的取反，用上横杠表示（$\bar A$）。
- **字面量 Literal**：变量本身或其补（$A$ 与 $\bar A$ 是同一变量的两个字面量）。

| 运算 Operation | 等价于 | 规则 Rules | 术语 Term |
|---|---|---|---|
| **布尔加法 Boolean addition** | OR | $0+0=0,\ 0+1=1,\ 1+0=1,\ 1+1=\mathbf{1}$ | **和项 Sum term**（如 $A+B+C+D$）——**所有字面量都为 0 时和项才为 0** |
| **布尔乘法 Boolean multiplication** | AND | $0\cdot0=0,\ 0\cdot1=0,\ 1\cdot0=0,\ 1\cdot1=\mathbf{1}$ | **积项 Product term**（如 $ABCD$）——**所有字面量都为 1 时积项才为 1** |

## 2. 定律与 12 条规则 Laws & Rules ⭐ 必背

**定律 Laws**：
- 交换律 Commutative：$A+B=B+A$，$AB=BA$；
- 结合律 Associative：$A+(B+C)=(A+B)+C$，$A(BC)=(AB)C$；
- 分配律 Distributive：$A(B+C)=AB+AC$。

**12 条规则 Rules**（A、B、C 可代表变量或整个表达式）：

| # | 规则 Rule | # | 规则 Rule |
|---|---|---|---|
| 1 | $A+0=A$ | 7 | $A\cdot A=A$ |
| 2 | $A+1=1$ | 8 | $A\cdot\bar A=0$ |
| 3 | $A\cdot0=0$ | 9 | $\bar{\bar A}=A$ |
| 4 | $A\cdot1=A$ | **10** | $A+AB=A$（吸收 Absorption） |
| 5 | $A+A=A$ | **11** | $A+\bar AB=A+B$（补吸收 Complemented absorption） |
| 6 | $A+\bar A=1$ | **12** | $(A+B)(A+C)=A+BC$（和之积 Product of two sums） |

**规则 10–12 推导 Derivation**：
- 规则 10：$A+AB = A(1+B) = A$
- 规则 11：$A+\bar AB = A + AB + \bar AB = A + (A+\bar A)B = A + B$
- 规则 12：$(A+B)(A+C) = AA+AC+AB+BC = A+AC+AB+BC = A+BC$（注意：两括号共享项 $A$ 必须相同）

> 练习：$R + R(S+T)$；$(P+Q)(P+R)+P$（答案：R；P）

## 3. 代数化简 Simplification Using Boolean Algebra

化简目的：**减少实现所需门电路**（reduce the gates needed）。

> 例：$AB + A(B+C) + B(B+C)$
> $= AB+AB+AC+BB+BC = AB+AC+B+BC \xrightarrow{\text{规则10}} AB+AC+B \xrightarrow{\text{规则10}} \mathbf{B + AC}$

## 4. 德摩根定理 DeMorgan's Theorems ⭐

**第一定理 1st**：乘积的补 = 补的和。$\overline{XY} = \bar X + \bar Y$
**第二定理 2nd**：和的补 = 补的积。$\overline{X+Y} = \bar X\,\bar Y$

- 口诀：**Break the bar, change the sign**（拆横杠、变符号）。
- 注意：对**横杠下的整个表达式**操作（each variable may represent a combination of other variables）。

![[EEE104/Note/assets/L07-p13.png|500]]
> ▲ 两条定理的电路形式与练习

![[EEE104/Note/assets/L07-p14.png|520]]
> ▲ 应用例：$\overline{(AB+C)(A+BC)} = \overline{AB+C}+\overline{A+BC} = \overline{AB}\,\bar C + \bar A\,\overline{BC} = (A+\bar B)\bar C + \bar A(\bar B+\bar C)$

> 例：$\overline{A + \overline{BC} + D(\overline{E+F})} = \bar A \cdot BC \cdot \overline{D(\overline{E+F})} = (\bar A + BC)(\bar D + E + F)$

---

## 自测 Checklist

- [ ] 变量/补/字面量/积项/和项的定义及「积项=1 条件」「和项=0 条件」Concepts
- [ ] 布尔加法 OR（1+1=1）与布尔乘法 AND 规则 Boolean operations
- [ ] 12 条规则默写 + 规则 10–12 推导默推 12 rules
- [ ] 化简例题 $AB+A(B+C)+B(B+C)=B+AC$ 重做 Simplification
- [ ] 德摩根两条定理 + 拆杠变号 + 横杠下整体操作 + 两道应用例 DeMorgan's theorems
