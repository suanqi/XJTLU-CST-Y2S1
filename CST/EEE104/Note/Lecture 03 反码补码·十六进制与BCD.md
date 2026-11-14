---
title: EEE104 Lecture 03 反码补码·十六进制与BCD
tags: [EEE104, 复习, 期末, Lecture03]
course: EEE104 Digital Electronics (I)
---

# Lecture 03 · 反码补码 · 十六进制 · BCD
# Complements, Hexadecimal Numbers & BCD

> 课件：Lecture03.pdf ｜ 上一讲：[[Lecture 02 二进制数与转换运算]] ｜ 下一讲：[[Lecture 04 有符号数与运算]] ｜ 索引：[[00 EEE104 期末复习总览]]

**本节要点 In this session**：1's/2's 补码（Complements）、十六进制（Hexadecimal）、BCD 码（Binary Coded Decimal）。

---

## 1. 反码与补码 Complements

- **1's complement（反码）**：把二进制数所有位取反（1→0、0→1）。
  - *Change all 1s to 0s and all 0s to 1s.*
- **2's complement（补码）**：反码 **+ 1**。
  - *Add 1 to the 1's complement.*
- 两者都用于**负数的表示**（important for representing negative numbers）。

> 例：$10110010 \xrightarrow{\text{取反}} 01001101 \xrightarrow{+1} \mathbf{01001110}$（2's complement）

## 2. 十六进制 Hexadecimal Numbers

### 2.1 为什么要用十六进制 Why hex?
- 长二进制串难读难写 → 十六进制是二进制的**紧凑写法**，广泛用于计算机与微处理器。
- **16 个数字**：0–9 + A–F（A=10 … F=15）；**每位代表 4 位二进制**。
- 可加下标 16 或后缀 h 标注：$2A_{16}$ 或 $2Ah$。
- 计数：0,1,…,9,A,B,…,F → 10,11,…,1F → … → FF → 100 …

### 2.2 转换 Conversions

| 转换 Conversion | 方法 Method | 例 Example |
|---|---|---|
| 二进制 → 十六进制 Binary→Hex | 从**最右端**开始每 **4 位一组**，换成对应十六进制符号 | $1100\,1011_2 = \mathbf{CB}_{16}$ |
| 十六进制 → 二进制 Hex→Binary | 每位符号换成对应 4 位；最左的 0 可去掉 | $EA_{16} = \mathbf{1110\ 1010}_2$ |
| 十六进制 → 十进制 Hex→Decimal | 按 **16 的幂作权值**加权求和 | $28A_{16}=2\cdot16^2+8\cdot16+10=\mathbf{650}$ |
| 十进制 → 十六进制 Decimal→Hex | **除 16 取余**（第一个余数为最低位 LSD），直到商为 0 | $650\to$ 余 A、8、2 → **28A₁₆** |
| 十六进制加法 Hex addition | 和 < 16：直接落位；和 ≥ 16：**留下超出 16 的部分，向高位进 1** | 见课件示例 |

## 3. BCD 码 Binary Coded Decimal

- **BCD**：用 4 位二进制码表示**一个十进制位**，只有 **10 个码组**（0000–1001）。
- **8421 码**是 BCD 的一种：4 位权值分别为 8、4、2、1。
- 用途：用户接口（键盘 keypads、数字显示 digital displays）。

### 3.1 转换 Conversion
- 十进制 → BCD：**逐位**换成 4 位。例：$68_{10} = 0110\ 1000_{\text{BCD}}$
- BCD → 十进制：从最右端每 4 位一组，各组写出十进制数字。

### 3.2 BCD 加法 BCD Addition ⭐
规则 Rule：
1. 先按**二进制加法**相加；
2. 若某 4 位组之和 **< 10** → 合法 BCD，保留；
3. 若某 4 位组之和 **≥ 10，或产生了组间进位**（非法）→ 该组**加 6（0110）修正**——跳过 6 个非法状态。
   - *If a 4-bit sum ≥ 10 or a carry is generated, add 6 (0110) to skip the six invalid states.*

![[EEE104/Note/assets/L03-p16.png|520]]
> ▲ BCD 加法示例（含 +6 修正）

> 例：$45+27$：$0100\ 0101 + 0010\ 0111 = 0110\ 1100$。
> 低 4 位 $1100$（=12 ≥ 10，非法）→ 加 6：$1100+0110=1\,0010$ → 本组取 0010，向高组进 1；
> 高 4 位 $0100+0010+1=0111$（合法）。结果 **0111 0010 = 72** ✓

---

## 自测 Checklist

- [ ] 1's/2's complement 计算（取反 / 取反+1）Complements
- [ ] 二进制 ↔ 十六进制（4 位一组）；十六进制计数（0–F、10–1F）Hex conversion & counting
- [ ] 十进制 ↔ 十六进制（16 的权值 / 除 16 取余）；十六进制加法进位 Hex addition
- [ ] BCD 编码（8421 权值、10 个码组）与十进制 ↔ BCD
- [ ] **BCD 加法：≥10 或产生进位时 +6 修正** BCD addition with +6 correction
