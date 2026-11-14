---
title: EEE104 Lecture 13 锁存器
tags: [EEE104, 复习, 期末, Lecture13]
course: EEE104 Digital Electronics (I)
---

# Lecture 13 · 锁存器
# Latches

> 课件：EEE104_Lecture_13.pdf ｜ 上一讲：[[Lecture 12 译码编码与数据选择（教材补充）]] ｜ 下一讲：[[Lecture 14 边沿触发器]] ｜ 索引：[[00 EEE104 期末复习总览]]

**本节要点 In this session**：基本 S-R 锁存器（basic S-R latch）、门控 S-R / D 锁存器（gated S-R & gated D latches）。

---

## 1. 基本概念 The S-R Latch

- **锁存器 Latch**：存储 1 位的**双稳态 bistable** 电路——两个稳定状态 Q=0 或 Q=1；**一个门的输出反馈到另一个门的输入**。
- 本节内容：基本 S-R、门控 S-R、门控 D（edge-triggered 见下一讲）。

## 2. 低有效 S-R 锁存器（NAND 实现）Active-Low S-R Latch ⭐

- **NAND 门等价于负或门** → 两个 NAND 交叉反馈构成 S-R 锁存器。
- 输入 $\bar S, \bar R$（active-LOW：**低电平脉冲起作用**）。

![[EEE104/Note/assets/L13-p04.png|520]]
> ▲ NAND 实现与负或等价形式

| S̄ | R̄ | Q | Q̄ | 说明 Comments |
|---|---|---|---|------|
| 1 | 1 | NC | NC | **保持 Hold**（no change，维持现态） |
| 0 | 1 | 1 | 0 | **置位 SET**（Q=1） |
| 1 | 0 | 0 | 1 | **复位 RESET**（Q=0） |
| 0 | 0 | 1 | 1 | **无效 Invalid**（同时回到 1 时状态不可预测） |

**原理 How it works**：
- S̄ 加**负脉冲**（S̄=0）→ Q=1、Q̄=0（SET）；脉冲结束（S̄=1）→ 反馈保持 Q 不变；
- R̄ 加负脉冲 → Q=0、Q̄=1（RESET）；
- S̄=R̄=1 → 不改变（HOLD：$Q = \overline{1\cdot Q} = Q$）；
- S̄=R̄=0 → **Q=Q̄=1**（两个输出同时为高），释放后因门延迟差异**状态不可预测**。

### 2.1 高有效 S-R 锁存器（NOR 实现）Active-High S-R Latch
- 两个 NOR 交叉反馈；输入 S、R（active-HIGH）。

![[EEE104/Note/assets/L13-p13.png|520]]
> ▲ NOR 实现与真值表

| S | R | Q | Q̄ | 说明 |
|---|---|---|---|-----|
| 0 | 0 | NC | NC | 保持 |
| 1 | 0 | 1 | 0 | SET |
| 0 | 1 | 0 | 1 | RESET |
| 1 | 1 | 0 | 0 | 无效 |

> ⚠️ **用真值表前先看输入极性**（Check input polarity before using a truth table）——NAND 版低有效、NOR 版高有效，两表相反！

### 2.2 波形练习 Waveform Example
低有效 S-R，初始 Q=0，依次施加 (S̄,R̄) = (1,1)→(0,1)→(1,1)→(1,0)→(1,1)：
**Q = 0 → 1 → 1 → 0 → 0**（SET 后保持、RESET 后保持）。

### 2.3 应用：触点抖动消除 Contact-Bounce Eliminator
- 机械开关切换时触点反复弹跳（bounce）；锁存器只在**第一次**触碰时改变状态：
  - 开关 1→2：S̄=0 → **Q=1 (SET)**；开关 2→1：R̄=0 → **Q=0 (RESET)**；中间悬空：S̄=R̄=1 → **保持**。
- 输出无抖动。

![[EEE104/Note/assets/L13-p15.png|520]]
> ▲ 触点消抖电路

## 3. 门控锁存器 Gated Latches

- 增加**使能输入 EN**：EN=LOW → 锁存器不改变；EN=HIGH → 输出由 S、R 控制。
- **门控锁存器是电平敏感器件**（level-sensitive device）。
- 内部（NAND 核心）：$S_{int} = \overline{S\cdot EN}$，$R_{int} = \overline{R\cdot EN}$。

![[EEE104/Note/assets/L13-p16.png|520]]
> ▲ 门控 S-R 锁存器结构

### 3.1 门控 S-R Gated S-R
- EN=0：任何 S、R 都**保持**（S_int=R_int=1）；
- EN=1：S=1→SET；R=1→RESET；S=R=1→**无效**（外部 S、R 高有效）。

### 3.2 门控 D 锁存器 Gated D Latch
- 只有一个数据输入 D：$S = D,\ R = \bar D$（永远互补 → **无无效态**）。
- EN=HIGH：**Q 跟随 D**（Q = D）；EN=LOW：**保持**（D 不影响状态）。

![[EEE104/Note/assets/L13-p20.png|520]]
> ▲ 门控 D 波形：EN HIGH 时 Q 跟随 D，EN LOW 时保持

> 波形练习：门控 D，初始 Q=0，施加 (EN,D) = (0,1)→(1,1)→(1,0)→(0,1)→(1,1)：
> **Q = 0 → 1 → 0 → 0 → 1**

---

## 自测 Checklist

- [ ] 锁存器 = 双稳态 + 交叉反馈；存储 1 位 Bistable latch
- [ ] NAND 低有效 S-R 真值表（11 保持/01 SET/10 RESET/00 无效）默写 Active-LOW table
- [ ] NOR 高有效 S-R 真值表（00 保持/10 SET/01 RESET/11 无效）Active-HIGH table
- [ ] 先看输入极性再查表！NAND=负或 的等价理解 Check polarity first
- [ ] 波形绘制（SET/RESET/HOLD 序列）Waveform practice
- [ ] 触点消抖应用（第一次触碰改变状态）Contact-bounce eliminator
- [ ] 门控 S-R（EN=0 保持；EN=1 时 S/R 高有效）与门控 D（EN=1 跟随 D）Gated latches
