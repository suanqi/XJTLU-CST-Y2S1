---
title: EEE104 Lecture 08 组合逻辑与通用门
tags: [EEE104, 复习, 期末, Lecture08]
course: EEE104 Digital Electronics (I)
---

# Lecture 08 · 组合逻辑与通用门
# Combinational Logic & Universal NAND/NOR Gates

> 课件：EEE104_Lecture_08.pdf ｜ 上一讲：[[Lecture 07 布尔代数]] ｜ 下一讲：[[Lecture 09 SOP与POS标准形式]] ｜ 索引：[[00 EEE104 期末复习总览]]

**本节要点 In this session**：组合逻辑电路（Combinational logic）、表达式 → 电路实现（Implementation）、通用门 NAND/NOR（Universal gates）、等价符号（Equivalent symbols）。

---

## 1. 组合逻辑电路 Basic Combinational Logic

- **组合逻辑 Combinational logic**：门互连实现某功能；**没有存储**（区别于时序电路）。
  - *No storage involved; the settled output depends on the current inputs.*
- 例子：XOR/XNOR 电路；实现 SOP 的 AND-OR 逻辑。

### 1.1 AND-OR 与 AND-OR-Invert
- **AND-OR 逻辑**实现 **SOP（积之和）**：$X = AB + CD$；
- **AND-OR-Invert 逻辑**实现 **POS（和之积）**：
  $\overline{AB+CD} = \overline{AB}\,\overline{CD} = (A+\bar B)(\bar C+\bar D)$

![[EEE104/Note/assets/L08-p05.png|520]]
> ▲ AND-OR（SOP）与 AND-OR-Invert（POS）结构

### 1.2 由表达式画电路 From Expression to Circuit
> 例：$X = AB(CD + EF)$。设 $P=CD$、$Q=EF$，则 $X = AB(P+Q)$：
> 两个 AND 生成 P、Q → OR 合成 → 与 AB 相与（三层结构）。

![[EEE104/Note/assets/L08-p06.png|520]]
> ▲ $X=AB(CD+EF)$ 的电路实现

> 练习：$A=B=C=D=F=1,\ E=0$ 时求 X（答案：$P=1,\ Q=0,\ P+Q=1,\ AB=1 \Rightarrow X=1$）

## 2. 通用门 NAND 与 NOR Universal Gates

- **NAND 与 NOR 是通用门**：能实现任何其它逻辑功能（NOT、AND、OR 足以实现任何布尔函数）。

| 目标功能 | 用 NAND | 用 NOR |
|---|---|---|
| 非门 NOT | 1 个（两输入短接） | 1 个（两输入短接） |
| 与门 AND | 2 个（NAND+反相） | 3 个 |
| 或门 OR | 3 个（$\overline{\bar A\,\bar B}=A+B$） | 2 个（NOR+反相） |
| 或非 NOR | 4 个 | — |
| 与非 NAND | — | 4 个 |

![[EEE104/Note/assets/L08-p08.png|520]]
> ▲ NAND 搭非门、与门（第二个 NAND 消除第一个的反相）

- 口诀：第二个门去掉第一个门的反相（removes the first output inversion）；多加一级反相把 OR 变 NOR、AND 变 NAND。

## 3. 等价符号 Equivalent Symbols ⭐ 读图利器

- **NAND = 负或门**（negative-OR）：输入带气泡的 OR；
- **NOR = 负与门**（negative-AND）：输入带气泡的 AND；
- 选择合适的等价符号使逻辑图更易读；**成对的气泡相互抵消**（paired bubbles cancel）。

![[EEE104/Note/assets/L08-p12.png|500]]
> ▲ NAND/ NOR 的等价符号

**读图方法**：先写出每个门的输出，再应用德摩根定理。
> 例：G1 输出 $\overline{AB}$、G2 输出 $\overline{CD}$ → $X = \overline{\overline{AB}\,\overline{CD}} = \mathbf{AB + CD}$（NAND-NAND = SOP）
> NOR 版：$X = \overline{\overline{A+B}+\overline{C+D}} = \mathbf{(A+B)(C+D)}$（NOR-NOR = POS）

![[EEE104/Note/assets/L08-p13.png|520]]
> ▲ 气泡抵消读图示例

---

## 自测 Checklist

- [ ] 组合逻辑定义（无存储、输出取决于当前输入）Combinational logic definition
- [ ] AND-OR（SOP）/ AND-OR-Invert（POS）结构及德摩根互化 AND-OR vs AOI
- [ ] $X=AB(CD+EF)$ 画电路 + 求值练习 Implementation example
- [ ] NAND/NOR 搭 NOT/AND/OR/NOR/NAND（1/2/3/4 个门）Universal gates
- [ ] 等价符号（负或/负与）与气泡抵消读图法 Equivalent symbols & bubble cancellation
