---
title: EEE104 Lecture 18 移位寄存器
tags: [EEE104, 复习, 期末, Lecture18]
course: EEE104 Digital Electronics (I)
---

# Lecture 18 · 移位寄存器
# Shift Registers

> 课件：Lecture18_new.pdf ｜ 上一讲：[[Lecture 17 级联计数器·译码与应用]] ｜ 下一讲：[[Lecture 19 双向移位寄存器与移位计数器]] ｜ 索引：[[00 EEE104 期末复习总览]]

**本节要点 In this session**：移位寄存器（Shift registers）、四种类型（SISO/SIPO/PISO/PIPO）、应用（Applications）、IC：74HC164 / 74HC165。

---

## 1. 基本概念 Shift Registers

- **移位寄存器** = 一组**级联的触发器**，存储并移动数据；
- 每级触发器（stage）存 **1 位**；
- 数据在**时钟触发沿**逐级移动（moves from stage to stage at the triggering edges of a clock signal）。

### 1.1 四种类型 Types

| 类型 Type | 全称 | 数据方式 Data flow | 典型用途 Use |
|---|---|---|---|
| **SISO** | Serial In / Serial Out | 串行入、串行出 | 时间延迟 time delay |
| **SIPO** | Serial In / Parallel Out | 串行入、并行出 | **串 → 并转换** serial-to-parallel |
| **PISO** | Parallel In / Serial Out | 并行入、串行出 | **并 → 串转换** parallel-to-serial |
| **PIPO** | Parallel In / Parallel Out | 并行入、并行出 | 快速并行存取 fast parallel access |

### 1.2 应用 Applications
1. **串行 ↔ 并行转换**：计算机内部要求并行数据，而外部设备（如 USB、串口）常收发串行数据；
2. **时间延迟**：SISO 可作延迟器件，延迟量由**级数**和**时钟频率**控制；
3. **硬件乘 2 / 除 2**：数据**右移一位 = ÷2**、**左移一位 = ×2**。
   > 例：$0000\,1100\ (12) \to 0000\,0110\ (6) \to 0000\,0011\ (3)$

## 2. 各类型电路 Circuits

### 2.1 SISO（串入串出）
![[EEE104/Note/assets/L18-p07.png|520]]
> ▲ SISO 的数据移动与逻辑符号

![[EEE104/Note/assets/L18-p08.png|520]]
> ▲ 数据 1101 经 **4 个时钟周期**全部存入（注意传播延迟的作用）

### 2.2 SIPO（串入并出）
- 电路与 SISO 相同，只是**每级输出都可用**（output of each stage is available）。
- IC **74HC164**（8 位 SIPO）：**A、B 输入都为 HIGH → 第一级置位，否则复位**；数据逐位移入。

![[EEE104/Note/assets/L18-p13.png|520]]
> ▲ 74HC164（8 位串入并出）

### 2.3 PISO（并入串出）
- **SH/LD = LOW**：使能 G1–G3 → **装载**并行数据（load）；
- **SH/LD = HIGH**：使能 G4–G6 → **移位**（shift）。
- IC **74HC165**（8 位并入串出）：
  - SH/LD 低 → 装载：D=0 → S=1、R=0 → Q=0；D=1 → S=0、R=1 → Q=1；
  - SH/LD 高 → S、R 均为高 → 移位；
  - 引脚：**CLK INH** 时钟禁止（clock inhibit）、**SER** 串行数据入（serial data in）、**SH/LD** 移位/装载（shift/load）。

![[EEE104/Note/assets/L18-p17.png|520]]
> ▲ 74HC165（8 位并入串出）

### 2.4 PIPO（并入并出）
- 并行装载 + 并行读出，用作快速并行数据存取（register 功能）。

---

## 自测 Checklist

- [ ] 移位寄存器 = 级联触发器逐级移数据（时钟沿移动）Definition
- [ ] 四类型 SISO/SIPO/PISO/PIPO 的含义与用途 Types table
- [ ] 三应用：串并转换、时间延迟、右移 ÷2 / 左移 ×2 Applications
- [ ] SISO 例题：1101 经 4 个时钟周期存入 SISO timing example
- [ ] 74HC164（A、B 同 HIGH 置位第一级）74HC164
- [ ] 74HC165（SH/LD 低装载/高移位；CLK INH、SER）74HC165
