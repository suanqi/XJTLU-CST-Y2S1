---
title: EEE104 Lecture 10 卡诺图化简
tags: [EEE104, 复习, 期末, Lecture10]
course: EEE104 Digital Electronics (I)
---

# Lecture 10 · 卡诺图化简
# The Karnaugh Map Minimization ⭐ 重点

> 课件：EEE104_Lecture_10.pdf ｜ 上一讲：[[Lecture 09 SOP与POS标准形式]] ｜ 下一讲：[[Lecture 11 加法器与比较器（教材补充）]] ｜ 索引：[[00 EEE104 期末复习总览]]

**本节要点 In this session**：卡诺图（The Karnaugh map）、SOP 最小化（SOP minimization）、POS 最小化（POS minimization）、无关项（Don't care）。

---

## 1. 卡诺图基础 The Karnaugh Map

- **卡诺图**：化简布尔表达式的**图形工具**；是真值表的**阵列形式**（每格对应真值表一行）。
- 实用范围：**最多 4–5 个变量**（practical only for up to 4–5 variables）。
- **格数 = $2^n$**（n = 变量数）。
- **格序按格雷码 Gray-code order**：$00 \to 01 \to 11 \to 10$（**相邻格只变一个变量**）。

![[EEE104/Note/assets/L10-p04.png|500]]
> ▲ 2/3/4 变量卡诺图的格雷码排列

### 1.1 相邻性 Cell Adjacency
- 每格与其**上下左右**四格相邻；
- **最上行与最下行相邻、最左列与最右列相邻**（wrap-around 环绕）。
- 判断：两格二进制值**只差一位**即相邻（如 0000/0010 ✓；0000/1000 ✓；0000/0011 ✗）。

## 2. SOP 最小化 SOP Minimization

### 2.1 映射 Mapping
- **标准 SOP**：每个积项对应格填 1。
- **非标准 SOP**：先**数值展开**——缺哪个变量，该项就拆成该变量取 0 和取 1 的两格。
  > 例：$\bar A + AB + AB\bar C$ → $\bar A$：000,001,010,011；$AB$：100,101；$AB\bar C$：110。

### 2.2 圈 1 Grouping the 1s
- 每组只能含 **1、2、4、8、16（$2^n$）个相邻格**；
- 目标：**组越大越好**（积项越短）、**组数越少越好**（项数越少）；
- **每个 1 必须被至少一个组覆盖**，可重复圈。

![[EEE104/Note/assets/L10-p08.png|520]]
> ▲ 圈 1 示例（含环绕相邻）

### 2.3 读积项 Determine the Minimum SOP
- 组内**有变化的变量消去**（appears in both complemented & uncomplemented form → eliminated）；
- **不变的变量保留**：全为 **1** → 原变量；全为 **0** → 反变量。
- 3 变量图：4 格组 → 1 变量项；2 格组 → 2 变量项；1 格组 → 3 变量项（**组越大项越短**）。

**四角组示例 Four-corner group**：

![[EEE104/Note/assets/L10-p14.png|520]]
> ▲ 四角 (0000, 0010, 1000, 1010) 全是 1：A、C 变化，B=0、D=0 不变 → $F = \bar B\bar D$

### 2.4 无关项 "Don't Care" ⭐
- 某些输入组合**永远不会出现**（如 BCD 的 1010–1111 六个非法状态），输出记为 **X（don't care）**。
- **X 可以当 1 也可以当 0**：只有当它能帮助组成更大组时才当 1；否则当 0。
- **所有 1 必须覆盖；X 不强制使用**（only used if they simplify the expression）。

![[EEE104/Note/assets/L10-p16.png|520]]
> ▲ BCD 检测例：不用 X：$Y = \bar A B C D + A\bar B\bar C\bar D + A\bar B\bar C D$；用 X：$\mathbf{Y = A + BCD}$

> 选择性使用例：1s 位于 1,3,5,7,9；Xs 位于 6,12,13 → $f = \bar a d + a\bar c d$（只用了 X13；X6、X12 未用）。

## 3. POS 最小化 POS Minimization

- **标准 POS**：每个和项对应格填 **0**；
- **圈 0**（规则同圈 1）；
- 读和项时**方向相反**：不变且为 **0** → **原变量**；不变且为 **1** → **反变量**。

![[EEE104/Note/assets/L10-p20.png|520]]
> ▲ POS 最小化：0 位于 000,001,010,011,110 →
> 4 格组（A=0、B=0 不变）→ $A+B$；单格 110 → $\bar A+\bar B+C$；
> 最小 POS：$X = (A+B)(\bar A+\bar B+C)$

## 4. 化简流程总结 Workflow

1. **填图**：标准项直接填；非标准项数值展开；don't care 填 X；
2. **圈组**：圈 1（SOP）/ 圈 0（POS），组取 2 的幂个相邻格，越大越少越好；
3. **读项**：变量变化→消去；不变→保留（SOP：1→原、0→补；POS：0→原、1→补）；
4. **写表达式**：各组项 OR（SOP）/ AND（POS）。

---

## 自测 Checklist

- [ ] 卡诺图 = 真值表阵列；格数 $2^n$；格雷码格序（00→01→11→10）Gray-code order
- [ ] 相邻性：四边相邻 + 环绕（上下行、左右列）Wrap-around adjacency
- [ ] 非标准 SOP 数值展开映射 Mapping non-standard SOP
- [ ] 圈 1 规则（2 的幂、最大最少、覆盖全部 1）Grouping rules
- [ ] 读项：变化消去、不变保留（1→原、0→补）Determining the minimum SOP
- [ ] 四角组例题（$F=\bar B\bar D$）重做 Four-corner group
- [ ] Don't care：可 1 可 0、只为增大组而用、不必全用（BCD 例 $Y=A+BCD$）
- [ ] POS 圈 0 与读项反向（0→原、1→补）POS minimization
