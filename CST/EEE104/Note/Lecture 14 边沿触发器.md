---
title: EEE104 Lecture 14 边沿触发器
tags: [EEE104, 复习, 期末, Lecture14]
course: EEE104 Digital Electronics (I)
---

# Lecture 14 · 边沿触发器
# Edge-Triggered Flip-Flops ⭐ 重点

> 课件：Lecture 14.pdf ｜ 上一讲：[[Lecture 13 锁存器]] ｜ 下一讲：[[Lecture 15 异步计数器]] ｜ 索引：[[00 EEE104 期末复习总览]]

**本节要点 In this session**：边沿触发 S-R / D / J-K 触发器（Edge-triggered FFs）、异步预置与清零（Asynchronous PRE/CLR）、触发器应用（Applications）。

---

## 1. 锁存器 vs 触发器 Latches vs Flip-Flops

| 器件 Device | Q 何时更新 When can Q update? | 其余时间 Otherwise |
|---|---|---|
| 门控 D 锁存器 Gated D latch | EN 为 HIGH **期间**（电平敏感 level-sensitive） | 保持 |
| 边沿触发 D 触发器 Edge-triggered D FF | **时钟有效沿瞬间**（edge-sensitive） | 保持 |

- 边沿触发：**上升沿 positive edge** 或**下降沿 negative edge**；符号上时钟输入 C 处有**小三角 ▲**（带小圆圈 = 下降沿触发）。
- 只在时钟跳变瞬间对输入敏感（sensitive to its inputs only at this transition）。

## 2. 三种边沿触发器 Truth Tables ⭐ 背

### 2.1 边沿触发 S-R（上升沿 ↑）
| S | R | CLK | Q | 说明 |
|---|---|-----|---|------|
| 0 | 0 | × | $Q_0$ | 保持 No change |
| 0 | 1 | ↑ | 0 | RESET |
| 1 | 0 | ↑ | 1 | SET |
| 1 | 1 | ↑ | ? | 无效 Invalid |

### 2.2 边沿触发 D（上升沿）
- **Q 在时钟沿跟随 D**（Q follows D at the triggering edge）。
- D=1 + ↑ → SET（存 1）；D=0 + ↑ → RESET（存 0）。

![[EEE104/Note/assets/L14-p08.png|500]]
> ▲ D 触发器符号与真值表

### 2.3 边沿触发 J-K（上升沿，无无效态！）⭐
| J | K | CLK | Q | 说明 |
|---|---|-----|---|------|
| 0 | 0 | ↑ | $Q_0$ | 保持 No change |
| 0 | 1 | ↑ | 0 | RESET |
| 1 | 0 | ↑ | 1 | SET |
| 1 | 1 | ↑ | $\bar Q_0$ | **翻转 Toggle**（Q*=Q̄₀） |

![[EEE104/Note/assets/L14-p09.png|520]]
> ▲ J-K 触发器符号、真值表与波形示例

### 2.4 J-K 与 S-R 的电路区别（为什么无无效态）
- **Q 输出反馈到门 G₂ 的输入，Q̄ 反馈到门 G₁ 的输入**（S̄ 与 R̄ 为内部低有效锁存输入）：
  - $S = J\bar Q,\ R = KQ$；
  - J=1、K=0：$\bar S = \overline{J\bar Q \cdot CLK}$… 在触发沿：若 Q=0 → SET（Q*=1）；若 Q=1 → 不变；
  - J=0、K=1：若 Q=1 → RESET；若 Q=0 → 不变；
  - J=K=0：S=R=1 → 不改变；
  - **J=K=1：Q 充当 R̄ 信号、Q̄ 充当 S̄ 信号** → 状态翻转（Q*=Q̄），每时钟翻转一次。

![[EEE104/Note/assets/L14-p11.png|520]]
> ▲ J-K 触发器内部结构（Q、Q̄ 反馈）

## 3. 异步预置与清零 Asynchronous PRE / CLR

- **同步输入**（J、K、D、S、R）只在时钟触发沿起作用；
- **异步输入**（PRE、CLR）**与时钟无关**，立即生效：
  - $\overline{PRE}=0$ → 立即**置位**（Q=1）；$\overline{CLR}=0$ → 立即**清零**（Q=0）；
  - **正常同步操作时 PRE = CLR = 1**；两者同时为 0 **禁止**（Invalid）。
- 低有效（active-LOW），符号上带气泡。

## 4. 触发器应用 Applications ⭐

### 4.1 并行数据存储 Parallel Data Storage
- 4 个 D 触发器**时钟并联** → 一个时钟沿同时存入 4 位（如 0110）。
- 操作顺序：先清零（clear first），再在时钟沿一次存入全部位。

![[EEE104/Note/assets/L14-p18.png|520]]
> ▲ 4 位并行存储（D3D2D1D0 = 0110）

### 4.2 分频 Frequency Division
- J=K=1（翻转模式）级联：**n 级 → 频率 ÷ $2^n$**（$f_A = f_{CLK}/2,\ f_B = f_{CLK}/4$）。
- 原理：翻转两次才完成一个输出周期（two toggles make one complete output cycle）。

![[EEE104/Note/assets/L14-p20.png|520]]
> ▲ 分频器级联

> 练习：CLK=12 kHz，一级输出 6 kHz；二级（由 Q 驱动）输出 3 kHz。

### 4.3 计数 Counting
- **负沿触发 J-K（J=K=1）级联** → 2 位二进制序列 00 → 01 → 10 → 11 → 00（QA 为 LSB，读作 QBQA）。

![[EEE104/Note/assets/L14-p22.png|520]]
> ▲ 2 位二进制计数器

---

## 自测 Checklist

- [ ] 门控 D 锁存器（电平敏感）vs 边沿 D 触发器（边沿敏感）区别 Latches vs FFs
- [ ] 上升/下降沿符号（小三角 ▲、气泡）Edge symbols
- [ ] 边沿 S-R / D / J-K 真值表默写（尤其 J=K=1 翻转）FF truth tables
- [ ] J-K 内部反馈原理（S=JQ̄、R=KQ；Q/Q̄ 反馈消除无效态）J-K feedback
- [ ] 异步 PRE/CLR：低有效、立即生效、正常操作 PRE=CLR=1、同 0 禁止 Asynchronous inputs
- [ ] 三应用：并行存储（共时钟）、分频（f/2ⁿ）、计数（负沿 J-K 级联）Applications
