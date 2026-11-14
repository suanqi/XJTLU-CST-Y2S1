---
title: EEE104 Lecture 01 模拟量与数字量
tags: [EEE104, 复习, 期末, Lecture01]
course: EEE104 Digital Electronics (I)
---

# Lecture 01 · 模拟量与数字量
# Analog & Digital Quantities

> 课件：L01 未收录于 vault（按课程绪论内容整理）
> 上一讲：— ｜ 下一讲：[[Lecture 02 二进制数与转换运算]] ｜ 索引：[[00 EEE104 期末复习总览]]

**本节要点 In this session**：模拟量/数字量、二进制位与逻辑电平、数字波形与脉冲、周期/频率/占空比、数字电路的优势。

---

## 1. 模拟量与数字量 Analog & Digital Quantities

- **模拟量 Analog quantity**：连续取值，随时间连续变化（如温度、声音波形、电压）。
  > *An analog quantity is continuous in value, e.g. temperature, sound.*
- **数字量 Digital quantity**：离散取值（分级/分档），如一天中的小时数、电子表显示。
  > *A digital quantity has a discrete set of values.*
- **数字表示 Digital representation**：把模拟量采样、量化成一组数字（如温度计按 1°C 档显示 28、29…）。
- 数字技术的优势 Advantages of digital systems：
  - **抗噪性强 Noise immunity**（电平容差大，干扰不易翻转 0/1）；
  - **易存储 Store & retrieve**（信息可复制而不损失）；
  - **可编程 Programmable**（处理器、软件）；
  - **精确 Accurate**（数字位数越多精度越高）。

## 2. 二进制位与逻辑电平 Bits & Logic Levels

- **位 Bit**：二进制的一个数字位，只有 0 和 1 两种取值（Binary digIT 缩写）。
- **逻辑电平 Logic levels**：用电压表示 0/1——**HIGH（高电平）= 逻辑 1**，**LOW（低电平）= 逻辑 0**。
- 实际电路中 HIGH/LOW 是一个电压区间（如 TTL：HIGH ≈ 2–5 V，LOW ≈ 0–0.8 V），中间是不确定的过渡区。

## 3. 数字波形与脉冲 Digital Waveforms & Pulses

- **数字波形 Digital waveform**：高低电平随时间切换的波形（方波类）。
- **脉冲 Pulse**：一次由 LOW→HIGH→LOW 的变化称为**正脉冲 positive pulse**；HIGH→LOW→HIGH 为**负脉冲 negative pulse**。
- **边沿 Edges**：
  - **上升沿 Rising edge（leading edge）**：LOW→HIGH 的跳变；
  - **下降沿 Falling edge（trailing edge）**：HIGH→LOW 的跳变。

```
         ┌────┐         正脉冲（宽度 tW）
         │    │
─────────┘    └────────────────  上升沿↑  下降沿↓
   ←—————— T ——————→
```

- **波形参数 Waveform parameters**：
  - **周期 Period $T$**：一个完整波形重复所需的时间；
  - **频率 Frequency $f = 1/T$**（单位 Hz）；
  - **占空比 Duty cycle** = 正脉冲宽度 / 周期 = $t_W / T$（常以 % 表示）。

> 例：$T = 10\ \text{ms}$，$t_W = 2\ \text{ms}$ → $f = 100\ \text{Hz}$，占空比 $= 20\%$。

---

## 自测 Checklist

- [ ] 能区分模拟量与数字量并各举例 Analog vs digital with examples
- [ ] 逻辑电平 HIGH/LOW 与 1/0 对应关系 Logic levels
- [ ] 会画正/负脉冲并标出上升沿、下降沿、宽度 Pulse & edges
- [ ] 周期 $T$、频率 $f=1/T$、占空比 $t_W/T$ 的计算 Period, frequency, duty cycle
- [ ] 说出数字电路的至少 3 个优势 Advantages of digital systems
