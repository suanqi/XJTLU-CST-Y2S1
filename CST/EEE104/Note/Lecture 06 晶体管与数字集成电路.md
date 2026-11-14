---
title: EEE104 Lecture 06 晶体管与数字集成电路
tags: [EEE104, 复习, 期末, Lecture06]
course: EEE104 Digital Electronics (I)
---

# Lecture 06 · 晶体管与数字集成电路
# Transistors in Gates & Digital Integrated Circuits

> 课件：Lecture06.pdf ｜ 上一讲：[[Lecture 05 逻辑门]] ｜ 下一讲：[[Lecture 07 布尔代数]] ｜ 索引：[[00 EEE104 期末复习总览]]

**本节要点 In this session**：门内的晶体管（Transistors in a gate）、数字 IC（Digital ICs）、IC 逻辑门的类型/系列/特性参数（Types, series & characteristics）。

---

## 1. 门内的晶体管 Transistors in a Gate

- **BJT 作开关**：工作在**截止 cutoff** 与**饱和 saturation** 之间：
  1. $v_I \approx 0$（接地）→ BJT **截止** → $v_O = V_{CC}$（逻辑 1）；
  2. $v_I \approx V_{CC}$ → BJT **饱和** → $v_O = V_{CE(sat)} \approx 0.2\,\text{V}$（逻辑 0）；
  3. 输入输出相反 → **这就是一个反相器（logic inverter）**。

![[EEE104/Note/assets/L06-p03.png|520]]
> ▲ BJT 开关电路与反相器符号/真值表

- 多个晶体管组合可构成其它门，例如两个 BJT（并联下拉）构成 **NOR 门**（$Z = \overline{X+Y}$）。
- 晶体管开关就是逻辑门的物理实现基础。

## 2. 数字集成电路 Digital Integrated Circuits

### 2.1 集成电路 IC 与 DIP 封装
- **IC**：整个电路做在**单块硅片**上；引脚（pins）连接内部电路实现输入输出。
- **DIP（dual-in-line package，双列直插）**：小/中规模 IC 的常见封装。
- **引脚编号 Pin numbering**：pin 1 由**小圆点或缺口**指示；缺口朝上时，编号**向下、转到另一列、再向上**递增，**最大编号 = 右上角引脚**。

![[EEE104/Note/assets/L06-p06.png|480]]
> ▲ DIP 引脚编号规则

### 2.2 复杂度分类 Complexity Classification

| 类别 Class | 门数 Gates | 用途 Used for |
|---|---|---|
| **SSI** 小规模 | 1–12 | 基本门、触发器 basic gates & flip-flops |
| **MSI** 中规模 | 13–99 | 编码器、计数器、寄存器、多路复用器 encoders, counters, registers, multiplexers |
| **LSI** 大规模 | 100–9,999 | 存储器 memories |
| **VLSI** 超大规模 | 10,000–99,999 | — |
| **ULSI** 甚大规模 | ≥100,000 | 微处理器、大容量存储器 microprocessors & large memories |

### 2.3 工艺 Technologies
- 双极型 Bipolar：**TTL**（晶体管-晶体管逻辑）、ECL（射极耦合逻辑）。
- MOS 型：**CMOS**（互补 MOS）、NMOS。
- SSI/MSI 两种工艺都有；**LSI/VLSI/ULSI 用 CMOS/NMOS**（更紧凑、功耗更低）。

### 2.4 型号命名 Designation
**前缀 Prefix + 系列 Series + 类型 Type**，如 **74LS04**：
- 前缀：**74** = 商用级 commercial，**54** = 军用级 military；
- 系列：表示工艺技术（如 LS）；
- 类型：逻辑器件种类（如 04 = 六反相器 hex inverter）。

常见类型 Types：Quad 2-Input NAND / NOR / AND / OR / XOR、Hex Inverter。

### 2.5 系列 Series

| 工艺 | 系列 | 含义 |
|---|---|---|
| TTL | **74LS** | 低功耗肖特基 Low-power Schottky |
| TTL | 74AS | 先进肖特基 Advanced Schottky |
| TTL | 74F | 快速 Fast |
| CMOS | **74HC** | 高速 CMOS High-speed CMOS |
| CMOS | 74HCT | 高速 CMOS，TTL 兼容 TTL compatible |
| CMOS | 74AC | 先进 CMOS Advanced CMOS |
| CMOS | 74LVC | 低压 CMOS Low-voltage CMOS |

### 2.6 特性参数 Characteristics ⭐（背数据）

**① 传播延迟 Propagation delay $t_P$**：输入变化到输出变化的时间间隔（$t_{PHL}$ 高→低、$t_{PLH}$ 低→高）；**越短速度越快**。

![[EEE104/Note/assets/L06-p12.png|520]]
> ▲ 传播延迟定义与波形

| 系列 | $t_P$ |
|---|---|
| 74LS | 11 ns |
| 74F | 3.3 ns |
| 74HCT | 7 ns |
| 74AC | 5 ns |

**② 电源电压 DC Supply Voltage $V_{CC}$**：

| 类别 | 最小 Min | 典型 Typ | 最大 Max |
|---|---|---|---|
| TTL | 4.5 V | 5.0 V | 5.5 V |
| 5V CMOS | 2.0 V | 5.0 V | 6.0 V |
| 3.3V CMOS | 2.0 V | 3.3 V | 3.6 V |

- CMOS 的电源电压范围比 TTL **更宽**（can vary over a wider range）；3.3V CMOS 功耗更低。

**③ 扇出 Fan-out**：一个输出能带动的**最大输入数**。
- 多数 TTL（如 74LS）可驱动 **20 个负载门**；CMOS 的扇出**非常高**。

---

## 自测 Checklist

- [ ] BJT 开关：截止→$v_O=V_{CC}$（1）、饱和→$v_O=0.2\text{V}$（0）→ 反相器 BJT as a switch
- [ ] DIP 引脚编号规则（缺口朝上、左上为 1、右上最大）Pin numbering
- [ ] SSI/MSI/LSI/VLSI/ULSI 门数与用途 Complexity classes
- [ ] TTL vs CMOS 工艺；型号 = 前缀+系列+类型（74LS04）Designation
- [ ] 系列缩写含义（74LS/74AS/74F/74HC/74HCT/74AC/74LVC）
- [ ] $t_P$ 定义与 4 组数据；$V_{CC}$ 表；扇出（74LS=20、CMOS 高）
