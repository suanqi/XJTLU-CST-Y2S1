---
title: EEE104 Lecture 19 双向移位寄存器与移位计数器
tags: [EEE104, 复习, 期末, Lecture19, 新增]
course: EEE104 Digital Electronics (I)
---

# Lecture 19 · 双向移位寄存器与移位寄存器计数器
# Bidirectional Shift Registers & Shift Register Counters ⭐ 新增

> 课件：Lecture19.pdf（2026-11-14 更新）｜ 上一讲：[[Lecture 18 移位寄存器]] ｜ 索引：[[00 EEE104 期末复习总览]]
> 本讲是 Lecture 18 移位寄存器的延续：**双向移位寄存器**与**移位寄存器计数器（Johnson / Ring）**。

**本节要点 In this session**：
- 双向移位寄存器 Bidirectional shift registers（74HC194 universal shift register）
- 移位寄存器计数器 Shift register counters：Johnson counter、Ring counter

---

## 1. 双向移位寄存器 Bidirectional Shift Registers

在普通移位寄存器基础上增加**方向控制 R/L**（right/left），数据可左移也可右移：

- **R/L = HIGH**：使能 G1–G4 → 每级的输出接到**下一级**的 D 输入（数据**右移 shift right**）。
- **R/L = LOW**：使能 G5–G8 → 每级的输出接到**前一级**的 D 输入（数据**左移 shift left**）。

![[EEE104/Note/assets/L19-p05.png|520]]
> ▲ 双向移位寄存器逻辑图（G1–G4：右移；G5–G8：左移）

### 1.1 IC 74HC194 — 4 位通用移位寄存器 ⭐
**4-bit universal shift register**（集右移、左移、装载、保持于一体）：

| 模式选择 Mode Selection | 模式 Mode |
|---|---|
| S1 S0 = 0 0 | **Inhibit（保持）** |
| S1 S0 = 0 1 | **Shift right（右移）** |
| S1 S0 = 1 0 | **Shift left（左移）** |
| S1 S0 = 1 1 | **Load（并行装载）** |

- **SR SER**：右移串行数据输入（shift-right serial data in）；
- **SL SER**：左移串行数据输入（shift-left serial data in）；
- **CLR**：**异步清零**（asynchronous clear）。

![[EEE104/Note/assets/L19-p06.png|520]]
> ▲ 74HC194：4 位通用移位寄存器与模式选择表

## 2. 移位寄存器计数器 Shift Register Counters

- **定义**：把移位寄存器的**串行输出接回串行输入**（serial output connected back to the serial input）→ 周期性产生**指定状态序列**，故名"计数器"。
- 两种最常见类型：**Johnson 计数器**与**环形计数器 Ring counter**。

### 2.1 Johnson 计数器 Johnson Counter ⭐

- **接法**：**最后一级的互补输出（Q̄）接回**串行输入。
- 工作过程：计数器**先被 1 填满，再被 0 填满**（fills up with 1s first, then with 0s）。

![[EEE104/Note/assets/L19-p09.png|520]]
> ▲ Johnson 计数器电路（Q̄ 反馈）

- **状态数**：n 级 Johnson 计数器有 **2n 个状态**（an n-stage Johnson counter has 2n states）。
  - 4 位 → **8 个状态**；5 位 → **10 个状态**。

![[EEE104/Note/assets/L19-p11.png|520]]
> ▲ 4 位 Johnson 计数器的 8 个状态序列（1000 型循环）

![[EEE104/Note/assets/L19-p12.png|520]]
> ▲ 5 位 Johnson 计数器的 10 个状态

- ⚠️ **初值问题**：若初始状态不在合法序列中，计数器会**在另外 8 个（非法）状态里循环**——因此**必须先把计数器强制置入合法状态**（initially forced into a valid state）。

### 2.2 环形计数器 Ring Counter

- **接法**：**最后一级的输出（Q）直接接回**串行输入。
- 状态：n 级 → **n 个状态**（单个 1 在各寄存器间循环移动）。

![[EEE104/Note/assets/L19-p14.png|520]]
> ▲ Ring 计数器电路（Q 反馈）

![[EEE104/Note/assets/L19-p15.png|520]]
> ▲ Ring 计数器状态序列

## 3. 小结与对比 Summary & Comparison

| | Johnson 计数器 | Ring 计数器 |
|---|---|---|
| 反馈 Feedback | 末级 **Q̄** → 串行输入 | 末级 **Q** → 串行输入 |
| 状态数 States | **2n** | **n** |
| 状态利用率 Utilization | $2n/2^n$ | $n/2^n$ |

**要点 Key points（课件总结）**：
1. **缺点 Disadvantage**：最大可用状态**未被充分利用**（maximum available states are not fully utilized）；
2. **必须强制初始状态**：Ring 与 Johnson 都只使用全部状态的一个**子集**，否则不会按理想序列运行（must initially be forced into a valid state）；
3. **优点 Advantage**：与二进制计数器相比**不需要额外的译码电路**（no extra decoding circuit is needed）——状态本身就是"译码好"的（如 Ring 是 one-hot 编码）。

---

## 自测 Checklist

- [ ] 双向移位：R/L=HIGH 右移（G1–G4）/ LOW 左移（G5–G8）Bidirectional shifting
- [ ] 74HC194 模式表 S1S0：00 保持 / 01 右移 / 10 左移 / 11 装载；SR SER、SL SER、CLR 异步清零 74HC194
- [ ] 移位寄存器计数器 = 串行输出接回串行输入 Definition
- [ ] Johnson：Q̄ 反馈、先填 1 再填 0、n 级 = 2n 状态（4 位 8 状态、5 位 10 状态）Johnson counter
- [ ] Johnson 非法初值 → 在另一组 8 状态循环（必须强制置入合法状态）
- [ ] Ring：Q 反馈、n 级 = n 状态 Ring counter
- [ ] 优缺点：状态利用率低（Ring n/2ⁿ、Johnson 2n/2ⁿ）；无需译码电路；必须初始化
