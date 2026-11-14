---
title: EEE104 Lecture 09 SOP与POS标准形式
tags: [EEE104, 复习, 期末, Lecture09]
course: EEE104 Digital Electronics (I)
---

# Lecture 09 · SOP 与 POS 标准形式
# Standard SOP & POS Forms

> 课件：EEE104_Lecture_09.pdf ｜ 上一讲：[[Lecture 08 组合逻辑与通用门]] ｜ 下一讲：[[Lecture 10 卡诺图化简]] ｜ 索引：[[00 EEE104 期末复习总览]]

**本节要点 In this session**：SOP/POS 的定义与标准形式（Definitions & standard forms）、标准项的二进制表示（Binary representation）、表达式与真值表互转（Expressions ↔ truth tables）、标准 SOP ↔ POS 转换（Conversion）。

---

## 1. SOP 与 POS 的定义 Definitions

- **SOP（Sum of Products，积之和）**：积项经布尔加法求和。例：$AB + BCD$。用 **AND-OR** 逻辑实现。
- **POS（Product of Sums，和之积）**：和项经布尔乘法求积。例：$(A+B)(B+\bar C+D)$。用 **OR-AND** 逻辑实现。
- **域 Domain**：表达式中所有变量的集合（如上两例域为 A, B, C, D）。
- **标准形式 Standard form**：**域中每个变量在每一项中出现一次（且仅一次）**。
  - 标准 SOP：$ABCD + \bar A B \bar C \bar D$
  - 标准 POS：$(A+B+C+D)(\bar A + B + \bar C + \bar D)$
  - *Standard SOP/POS describes the structure; "standard" adds the requirement that every term contains every variable in the domain once.*

## 2. 化为标准形式 Converting to Standard Form

### 2.1 SOP 补变量（乘 1：$C+\bar C=1$）
> $\bar A B + ABCD$
> $= \bar A B(C+\bar C) + ABCD$
> $= \bar A B C(D+\bar D) + \bar A \bar B... $ 依次展开：
> $= \bar A B C D + \bar A B C \bar D + \bar A \bar B C D + \bar A \bar B C \bar D + ABCD$（5 项标准 SOP）

### 2.2 POS 补变量（加 0：$C\bar C=0$，再用规则 12）
> $(A+B)(A+B+\bar C)$
> $= (A+B+C\bar C)(A+B+\bar C)$
> $= (A+B+C)(A+B+\bar C)(A+B+\bar C)$

## 3. 标准项的二进制表示 Binary Representation ⭐ 关键

- **标准积项 = 输出为 1 的那一行**：$AB\bar C\bar D = 1010$（该行乘积 $1\cdot1\cdot1\cdot1=1$）。
- **标准和项 = 输出为 0 的那一行**：$A+\bar B+C+\bar D = 0101$（该行和 $0+0+0+0=0$）。
- 写法差异（because the required term values differ）：
  - **积项**中，变量为 0 → 写**补**（如 A=0 写 $\bar A$）；
  - **和项**中，变量为 0 → 写**原变量**（如 A=0 写 $A$）。

![[EEE104/Note/assets/L09-p09.png|520]]
> ▲ 标准项的二进制表示对照

> 练习：域 A,B,C，写出输入 110 对应的两个标准项
> 答案：积项 $AB\bar C$；和项 $\bar A+\bar B+C$

## 4. 表达式 ↔ 真值表 Expressions ↔ Truth Tables

### 4.1 SOP → 真值表
1. 化成标准 SOP；2. 找出每个积项对应的输入行；3. **这些行输出置 1，其余置 0**。

### 4.2 POS → 真值表
1. 化成标准 POS；2. 找出每个和项对应的输入行；3. **这些行输出置 0，其余置 1**。

### 4.3 真值表 → SOP
1. 取**输出为 1**的行；2. 每行写一个积项（0→补、1→原）；3. 各项 OR 起来。

![[EEE104/Note/assets/L09-p12.png|520]]
> ▲ 真值表 → SOP 示例：$X = \bar A BC + A\bar B\bar C + AB\bar C + ABC$

### 4.4 真值表 → POS
1. 取**输出为 0**的行；2. 每行写一个和项（0→原、1→补）；3. 各项 AND 起来。

![[EEE104/Note/assets/L09-p13.png|520]]
> ▲ 真值表 → POS 示例：$X = (A+B+C)(A+B+\bar C)(A+\bar B+C)(\bar A+B+\bar C)$

## 5. 标准 SOP ↔ 标准 POS 转换 Conversion

**SOP → POS**：① 找出 SOP 已覆盖的输入行；② 取域内**剩余的行**；③ 写对应的和项并相乘。
> 例：SOP 覆盖 000,010,011,101,111 → 剩余 001,100,110 →
> POS：$X = (A+B+\bar C)(\bar A+B+C)(\bar A+\bar B+C)$
> 反向同理（POS → SOP：取 0 行的补集写积项）。

![[EEE104/Note/assets/L09-p14.png|520]]
> ▲ 标准 SOP ↔ 标准 POS 转换示例

## 6. SOP vs POS 关键区别 Key Differences

| | SOP | POS |
|---|---|---|
| 项内运算 Inside each term | AND | OR |
| 项间运算 Between terms | OR | AND |
| 识别条件 Condition to identify | 积项 = 1 | 和项 = 0 |
| 该项使输出 Output then equals | 1 | 0 |
| 取自真值表哪些行 Rows used | 输出为 1 的行 | 输出为 0 的行 |

![[EEE104/Note/assets/L09-p15.png|500]]
> ▲ 课件对比表

> 练习（域 A,B,C）：真值表 H=1 于 001,010,110,111。
> SOP：$H = \bar A\bar B C + \bar A B\bar C + AB\bar C + ABC$；
> POS（0 行 000,011,100,101）：$H = (A+B+C)(A+\bar B+\bar C)(\bar A+B+C)(\bar A+\bar B+\bar C)$

---

## 自测 Checklist

- [ ] SOP/POS、域、标准形式的定义 Definitions & standard forms
- [ ] SOP 乘 1（$C+\bar C$）/ POS 加 0（$C\bar C$+规则12）化标准形式 Expansion
- [ ] 标准积项 = 1 的行、标准和项 = 0 的行；0→补/0→原 写法 Binary representation
- [ ] 表达式 → 真值表（SOP 置 1 / POS 置 0）两向互转 SOP/POS ↔ truth tables
- [ ] 标准 SOP ↔ 标准 POS（补行法）Conversion
- [ ] SOP vs POS 区别表默写 Key differences table
