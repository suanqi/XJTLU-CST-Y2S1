# SOE104 API Reference 与 Engine Rules Spec 速查

> 两份官方文档的完整总结。实现时对照这里查即可。

---

# Part A · API Reference（接口合同）

## A1 提交规范

- 1–20 个 `.java` 文件（或单个 zip），**无 package 声明**（默认包）；
- 每个文件开头 `import edu.soe104.oregon.api.*;`（用 List 再加 `import java.util.List;`）；
- 一个文件一个 public 类，UTF-8；
- **恰好一个** `PartyFactory` 实现；
- `createMembers()` 必须返回 **3–5 人**，其他数量直接判失败；
- classpath 只有 `oregon-api`——本文档没有的类都不能用；禁用 API（文件/网络/反射/线程/Random/环境变量…）在运行前就被字节码扫描拒收。

## A2 调用时序（设计的一半都在这）⭐

```
出发前:   createMembers()         组建队伍（3–5 人）
          buySupplies()           一次性采购（null = 经典购物篮）

每回合（1..120，直到 2000 英里）:
  ① strategy.decide(state)    ← 全队策略：速度、口粮      最先
  ② 马车行进 + 队伍吃饭
  ③ resolver.resolve(event)   ← 只有本回合触发事件才调用  中间
  ④ m.act(situation)          ← 每个活着的成员一次，按名单顺序  最后
  ⑤ 记账 + 存活检查
```

三个值得刻进设计的时序事实：

- **decide 在一切发生之前**；成员在行进、吃饭、事件**之后**行动。`situation.getCurrentEvent()` 是当回合已结算的事件，可以事后反应——DEFEND 就是为此存在的。
- **resolver 夹在中间**：它学到的东西，成员当回合就能用上。
- 都可以返回 null：decide null → 默认 NORMAL+FULL；act null → 该成员发呆；buySupplies null → 经典购物篮。合法但通常浪费回合。

**Shared-context 模式（官方推荐）**：三个接口看到的视图不同（§A4/A7/A8），要共享记忆或下指令，就在工厂里创建**一个自己的普通对象**分发给所有人：

```java
public class MyFactory implements PartyFactory {
    private final Plans plans = new Plans();   // 自己的类：字段+方法
    public List<Member> createMembers() {
        return List.of(new MyHunter("Wren", plans), new MyDoctor("Anna", plans));
    }
    public PartyStrategy strategy() { return new MyStrategy(plans); }
    public Resolver resolver()    { return new MyResolver(plans); }
}
```

策略可以设 `plans.mode = CONSERVE`，成员稍后行动时同回合就能读到——这就是**组合（composition）**，官方给的"类之间怎么通信"的标准答案。

## A3 六种行动 Action（精确效果）

构造：`Action.of(Action.Type.HUNT)`（推荐）或 `new Action(Action.Type.HUNT)`。
行动是**二元的**：成员只选"做什么"，力度、收益、代价全部由引擎按固定规则结算。只有 null 类型会抛异常（→ 总分封顶 40）。

| 行动 | 精确效果 |
|---|---|
| **HUNT** | 耗 1 弹药 → +7 食物（Hunter：10）。超出马车 500 容量部分**腐烂**（弹药照扣）——满仓别打猎 |
| **HEAL** | 自己 +10 HP；**Doctor** 改为治疗全队最虚弱的活人 +15（自己最虚就治自己）。**饥饿回合无效** |
| **REST** | 自己 +3 HP。**饥饿回合无效** |
| **SCOUT** | 本回合 +3 英里（Scout：+6）。无血量代价 |
| **MOVE** | 本回合 +5 英里，自己 −1 HP——**对所有人如此，Driver 也不例外** |
| **DEFEND** | 若本回合发生了威胁事件：每个活人 +3 HP。**每回合最多生效一次**，几个人防守都一样——一人防守足够，五人防守浪费四个回合 |

成员按名单顺序行动；SCOUT/MOVE 的里程全队累加。

## A4 Situation（act() 拿到的"晨间简报"）

不可变对象，每个 act() 调用都收到一份。全部是 getter：

| getter | 含义 |
|---|---|
| `getTurn()` | 当前回合 1..120 |
| `getDistanceSoFar()` / `getTotalDistance()` | 已走英里 / 2000 |
| `isThreatened()` | 本回合是否有事件 |
| `getThreatLevel()` | 事件严重度 1–10（无事件为 0） |
| `getPartyHealthAverage()` | 活人平均血量 0–100 |
| `getFoodLevel()` / `getAmmoLevel()` / `getOxenCount()` | 食物 / 弹药 / 牛数（0=抛锚，4+=全速） |
| `getPartySize()` | 本回合活着的人数 |
| `getCurrentEvent()` / `hasEvent()` | 本回合（已结算的）事件 |

**食物跑道计算**（每个策略都想要的那个数）：

```java
int perTurn = 2 * situation.getPartySize() + 2 * situation.getOxenCount();
int runway  = situation.getFoodLevel() / Math.max(1, perTurn);  // 还能吃几回合
if (runway < 3) return Action.of(Action.Type.HUNT);             // 全员打猎
```

## A5 Member 与五个角色类

```java
public abstract class Member implements Actable {
    public static final int MAX_HEALTH = 100;
    protected Member(String name);            // 满血
    protected Member(String name, int hp);    // 0..100，越界抛异常
    public abstract Action act(Situation situation);  // ← 你们的行为
    public final String getName();
    public final int getHealth();
    public final boolean isAlive();
}
```

必须 override `act`，其余都是 final。血量只能通过你返回的行动改变——直接改引擎状态是禁止的。**只能加 private 字段**（阈值、历史记忆）；public 字段扣 OOP 分。

| 角色 | 天赋（精确） |
|---|---|
| **Hunter** | 自己的 HUNT 每发弹药产 10 食物（基础 7） |
| **Doctor** | 自己的 HEAL 基础 +15（不是 +10），且治疗全队最虚弱者而非只治自己 |
| **Mechanic** | **光环**：只要有 Mechanic 活着，BREAKDOWN 的 SAFE 修理不消耗零件 |
| **Scout** | 自己的 SCOUT +6 英里（基础 +3） |
| **Driver** | **光环**：只要有 Driver 活着，GRUELING 每人只扣 2 HP（不是 4）、死牛概率 7%（不是 15%） |

- 直接继承 `Member` 合法：所有行动可用但无天赋。
- 重复角色没问题：自身天赋各自生效（两个 Hunter 各自 10 食物/发，互不加成）；**光环不叠加**——一个活 Mechanic/Driver 就够。

## A6 PartyFactory（唯一入口）

```java
public interface PartyFactory {
    List<Member> createMembers();                    // 3–5 人（必须）
    default List<Purchase> buySupplies() { … }       // null = 经典购物篮
    default PartyStrategy strategy() { … }           // null = NORMAL/FULL
    default Resolver resolver() { … }                // null = 永远 SAFE
}
```

**杂货铺**：每队固定钱包 **$2,000**（与人数无关）。购买按列表顺序执行，每项裁剪到钱包还买得起的数量（食物还受 500 容量裁剪）；没花完的钱就是出发现金。null/空列表 → 引擎买**经典购物篮**：500 食物、80 弹药、5 牛、2 零件，找零 $300。

| 商品 | 价格 |
|---|---|
| 食物 | $2 |
| 弹药 | $3 |
| 零件 | $30 |
| 牛 | $80 |

`new Purchase(ResourceType.OXEN, 5)`；钱不能买；负数数量抛异常。

## A7 PartyStrategy / PartyState / Directive

```java
public interface PartyStrategy { Directive decide(PartyState state); }
```

`PartyState` 是全队视图（比 Situation 信息更全）：

| getter | 含义 |
|---|---|
| `getTurn()` / `getDistanceSoFar()` / `getTotalDistance()` | 同 Situation |
| `getMembers()` | List\<Member\>：读每个人的名字和血量 |
| `getResources()` | 马车 Inventory **快照**：`amountOf(type)`、`totalUnits()`——你改它不影响马车（只读副本） |
| `getLastDirective()` | 上一回合实际生效的指令 |
| `aliveMembers()` | 活人数 |

单方法接口，lambda 即可：`return state -> new Directive(…);`

**Directive**：

| 维度 | 选项（精确） |
|---|---|
| **Pace** | SLOW 12 / NORMAL 20 / GRUELING 28 英里/回合（4+ 牛时；牛少按比例缩减，0 牛不走）。GRUELING：每人 −4 HP/回合 + 15% 概率死一头牛；Driver 活着时减半（−2 HP、7%） |
| **Rations** | BARE 1（每人每回合 −1 HP 慢性失血）/ MEAGER 2 / FULL 5 食物每人每回合。FULL 且吃饱 → 每人 +2 HP |

null 或抛异常 → 该回合用默认 NORMAL+FULL。FULL 舒适但昂贵——默认策略最终会饿死。

## A8 Resolver / Event / Resolution（应对事件）

```java
public interface Resolver { Resolution resolve(Event event); }
```

**Event 能读到的**：`kind()`（"RIVER"/"STORM"/"BREAKDOWN"/"ILLNESS"/"ATTACK"/"TRADER"/"HUNT_OPP"/"BAD_TRAIL"/"THEFT"）、`severity()`（1–10，随进度上升；市场事件里就是价格档位）、`getTurn()`、`getDescription()`、`isMarket()`、`buyPrice(good)`/`sellPrice(good)`。

⚠️ **resolver 看不到马车库存**——采购要保守，或通过 shared-context（§A2）与策略协调。

**Resolution 能回答的**：

```java
Resolution.of(Resolution.Choice.SAFE);      // 稳妥：通常花钱/物资
Resolution.of(Resolution.Choice.RISKY);     // 赌博：可能大赚、可能受伤甚至死牛
Resolution.of(Resolution.Choice.AVOID);     // 绕开：通常损失里程
Resolution.buy(ResourceType.FOOD, 50);      // 按标价买
Resolution.sell(ResourceType.AMMO, 30);     // 按买入价 70% 卖
Resolution.haggleBuy(ResourceType.FOOD, 50);// 砍价：成功率 0.5+(s−5)×0.04，clamp [0.2, 0.9]
Resolution.haggleSell(ResourceType.AMMO, 30);
Resolution.decline();                       // 逛完就走
```

## A9 ResourceType 与 Inventory

```java
public enum ResourceType { FOOD, OXEN, AMMO, SPARE_PARTS, MONEY }
```

`Inventory`（策略里拿到的只读副本）：`amountOf(type)`、`totalUnits()`（除钱外总和，粗略财富指标）。成员不直接拿库存，通过 Situation 看食物/弹药/牛。

## A10 坑清单（官方原版）

- null 行动类型会抛异常 → 整场封顶 40 分——永远不要用未校验的值构造行动。
- 两个 PartyFactory → 不评分；1–2 人或 6+ 人 → 运行失败；0 或 21+ 文件 → 拒收。
- **DEFEND 不叠加**——每回合一个人防守就够，其他人做别的。
- **饥饿回合 HEAL/REST 无效**（HUNT 仍有效）。
- 马车最多 500 食物——满仓打猎纯浪费弹药。
- 策略里的 `getResources()` 是快照：改它不会改变现实。
- 禁用 `java.util.Random`、文件/网络/反射/线程 API——提交前字节码扫描。

## A11 常用数字表（官方速查）

| 常量 | 值 |
|---|---|
| 旅程 | 2000 英里、120 回合 |
| 钱包 | $2,000；价格：食物 2 / 弹药 3 / 零件 30 / 牛 80 |
| 经典购物篮 | 500 食物、80 弹药、5 牛、2 零件，找零 $300 |
| 容量 | 500 食物 |
| 市场 | 每商品每次最多买 50；卖出 = 买入价 70%；价格带 ×0.7 / ×1.0 / ×1.4 |
| 打猎 | 1 弹药 → 7 食物（Hunter 10） |
| 治疗 | 自己 +10（Doctor +15 治最虚者） |
| 休息 | 自己 +3 |
| 探路/推进 | +3 / +5 英里；MOVE 自己 −1 HP（人人如此）；Scout 的 SCOUT +6 |
| 防守 | 有威胁事件回合：全员 +3，每回合一次 |
| 速度 | 12 / 20 / 28 英里（GRUELING：每人 −4 HP、15% 死牛） |
| 口粮 | BARE 1（−1 HP 损耗）/ MEAGER 2 / FULL 5（吃饱 +2 HP） |
| 牛 | 每头每回合吃 2 食物；4+ = 全速；0 = 抛锚 |
| 饥饿 | 连续饥饿伤害 5、8、12、17、之后 23/回合；期间不能治疗 |
| 事件 | 早期约 15% → 后期约 43%；严重度 1–10 上升 |

---

# Part B · Engine Rules Spec（引擎的每个数字）

## B1 旅程框架

| 参数 | 值 |
|---|---|
| 总里程 | 2,000 英里 |
| 回合上限 | 120 回合 |
| 共享种子 | 3 个（每队完全相同，默认 {1, 2, 3}） |
| 难度系数 | 1.0（固定，所有严重度计算按此缩放） |

**结束条件**：到达 2,000 英里 / 用完 120 回合 / 全员死亡（立即失败）。**牛为 0 不结束**——马车抛锚（不走），但回合和饥饿继续。

**每回合固定 7 阶段**：

1. Strategy — `decide(PartyState)` → Directive
2. Travel — 按速度走英里（需 ≥1 牛）；GRUELING 的疲劳和死牛风险
3. Feeding — 成员先吃，牛后吃；饥饿结算
4. Event — 可能触发一个随机事件；`resolve(Event)` 应对
5. Member acts — 每个活着的成员执行一个行动
6. Bookkeeping — 资源结算、回放快照
7. Survival check — 全灭即结束

## B2 出发商店与马车容量

- 一次性采购（第 1 回合前），钱包固定 **$2,000**（= 经典购物篮价格 + $300）。
- 购买按列表顺序执行：每项裁剪到钱包余额；买不起 1 单位的商品直接跳过；余钱 = 出发现金。
- 只能买：不能卖、不能砍价；食物购买也受容量裁剪。
- null/空列表 → 经典购物篮（500 食物、80 弹药、5 牛、2 零件）。
- **容量 500 食物**：所有来源（商店、HUNT、狩猎机会、市场）都裁剪到容量，超出腐烂（弹药照扣）。囤货不可能，**即时采购（just-in-time）才是技巧**。
- 商店回调与 act() 在同一沙箱、同样的步数预算内运行。

## B3 队伍与角色

- `createMembers()` 必须返回 3–5 人，否则运行失败（功能门槛）。
- 构造：`super(name)`（满血）或 `super(name, hp)`（0–100，越界抛异常）。
- `act()` 可返回 null = 该回合发呆（回放里会记录）。
- 五个角色天赋与 A5 完全一致：Hunter/Doctor/Scout 改自身行动；Mechanic/Driver 是光环（活着就生效，无需代码）。重复角色：自身天赋各自生效、互不加成；**光环不叠加**。

## B4 成员行动

与 A3 完全一致（引擎侧描述）：HUNT 1 弹药→7 食物（Hunter 10，裁剪到容量）；HEAL 自己+10（Doctor 治最虚者+15，饥饿回合无效）；REST 自己+3（同饥饿规则）；SCOUT +3（Scout +6）无代价；MOVE +5 自己−1（含 Driver）；DEFEND 有威胁事件时全员+3、每回合最多一次。`new Action(null)` 抛异常 → 运行失败，必须防御式编程。

## B5 队伍指令 Directive

- 速度：`miles = pace × min(1, oxen / 4)`；0 牛 → 不走。
- GRUELING：每人 −4 HP + 15% 死牛；Driver 活着 → −2 HP、7%。
- FULL 且吃饱 → 每人 +2 HP。
- decide() 返回 null 或抛异常 → 默认 NORMAL+FULL（很耗食物的默认，认真做策略会更好）。
- 牛在成员之后吃：每牛 2 食物/回合（养牛是真实代价，牛数是权衡）。食物中途耗尽，牛就饿着。

## B6 吃饭与饥饿

1. 活着的成员吃：口粮 × 活人数；
2. 牛吃：2 × 牛数；
3. 只要有成员没吃饱（部分吃饱也算饥饿，整数语义）→ 全员递增伤害，且本回合 HEAL/REST 失效：

| 连续饥饿回合 | 1 | 2 | 3 | 4 | 5+ |
|---|---|---|---|---|---|
| 每人伤害 | 5 | 8 | 12 | 17 | 23（封顶） |

4. 吃饱一回合 → 计数器重置。

## B7 随机事件 ⭐

- **触发概率**：每回合 `15% + 28% × progress`（progress = 里程/2000）→ 早期 ~15%、后期 ~43%。
- **严重度**：`1..5 均匀 + round(6 × progress)`，clamp 到 [1, 10]。
- **事件池按进度分四段**（当前引擎，原文照抄）：

| 进度 | 事件池 |
|---|---|
| 0–25% | HUNT_OPP ×2、BAD_TRAIL、TRADER、STORM |
| 25–60% | STORM、BREAKDOWN、THEFT、TRADER、HUNT_OPP、BAD_TRAIL |
| 60–90% | RIVER、ILLNESS、ATTACK、BAD_TRAIL、STORM、BREAKDOWN、TRADER |
| 90–100% | RIVER、ATTACK、ILLNESS、STORM、THEFT、BREAKDOWN、TRADER |

- **公平规则**：付不起钱的 SAFE 选项（RIVER 渡船 $25、ATTACK 逃跑 $30）自动降级为 AVOID。
- 所有事件的 HP 伤害都打在**每个活人**身上。

### 九种事件 × 三种姿态完整表（s = 严重度 1–10）

| 事件 | SAFE | RISKY | AVOID |
|---|---|---|---|
| 🌊 **RIVER**（s=水深） | 付渡船费 **−$25**（付不起→按 AVOID 处理） | 涉水：**s/10 概率**全队 −10 HP 且 −20 食物；再 **20%** 概率淹死一头牛 | 岸边等待：**−5 英里** |
| ⛈️ **STORM** | 躲避：全队 **−2 HP** | 硬闯：全队 **−s HP**；**15%** 死牛 | 绕路：**−10 英里** |
| 🛠️ **BREAKDOWN** | 修理：耗 **1 零件**（有 Mechanic 活着则不耗；没零件=AVOID） | 凑合修：**s/10** 全队 −5 HP 且 −1 零件 | 减重：**−15 英里** |
| 🤒 **ILLNESS** | 休养：**−3×活人数** 食物、**−10 英里** | 硬扛：**s/10** 全队 −(s+5) HP，否则完全康复 | 忍耐：全队 **−s HP**（必然发生） |
| 🐺 **ATTACK** | 逃跑：**−$30**（付不起→按 AVOID）且 −10 食物 | 战斗：全队 **−s HP** | 躲藏：**−15 英里** |
| 🤝 **TRADER** | 按标价买卖（裁剪到钱、≤50 单位/种/次、食物受容量限制） | 砍价：成功 → 买 ×0.7 / 卖 ×1.3；失败 → 交易取消 | 走人 |
| 🦌 **HUNT_OPP** | 稳妥猎：**−2 弹药 → +20 食物**（需要弹药） | 大猎：**−4 弹药 → +50 食物**，**s/10** 全队 −5 HP | 放弃 |
| ⛰️ **BAD_TRAIL** | 远路：**−10 英里、−5 食物** | 抄近路：**s/10** 全队 −s HP 且 **15%** 死牛；否则 **+5 英里** | 折返：**−20 英里** |
| 🥷 **THEFT** | 派人看守：**−10 食物** | 追赶：**50/50** —— 全队 −5 HP，或 −20 食物且 −$20 | 交出钱箱：**−$15** |

食物损失裁剪到存量；花钱的选项遵守上述支付不起规则。

## B8 交易市场（TRADER）规则

- **每次访问限一笔交易**。
- 价格：`标价 = 基础价 × 档位`：severity 1–3 → **×0.7**（便宜）、4–6 → **×1.0**（正常）、7–10 → **×1.4**（贵），四舍五入、最低 $1。**卖出价 = 买入价 × 70%**（四舍五入、最低 $1）。
- 买入：裁剪到钱、每次每种 ≤50 单位、食物受容量限制；买不起 1 单位 → 交易取消。
- 卖出：裁剪到库存；没库存 → 交易取消。
- 砍价：成功率 `clamp(0.5 + (s−5)×0.04, 0.2, 0.9)`；成功 → 买 ×0.7 / 卖 ×1.3；失败 → 交易作废。

## B9 评分 ⭐

```
FINAL = 0.20·OOP + 0.50·Game + 0.15·Naming + 0.15·Efficiency   （3 种子平均）
Game  = 60%·(distance/2000) + 25%·(survivors/initial)
      + 15%·min(1, totalUnits/1000)·(distance/2000)
```

⚠️ **物资分按里程折算**——走不远却囤满物资没有意义。

- **功能门槛**：编译失败 / 崩溃 / 超时 → Game = 0、总分封顶 40；禁用 API → 0 分。
- **效率档**（宽松）：≤8,000 平均步数 → 100 分；≤25,000 → 80；≤60,000 → 60；否则 ≤40。正常决策逻辑只有 100–6,000 步（560 行的参考实现约 5,700）——这个维度抓的是病态计算（失控循环动辄百万级），不是复杂度。
- **OOP 子项**（字节码静态分析）：封装 25、继承 25、多态 25、接口 15、内聚 10。
- **命名**：类 PascalCase、成员 camelCase，禁单字母和含糊名。

## B10 沙箱与确定性

- JDK 21；classpath 只有 `oregon-api`。
- 提交：.java 或一个 zip，文件在压缩包根目录、无包、UTF-8、每文件一个 public 类、1–20 个文件、≤20 MB。**zip 里只提取 .java**，其他内容忽略（没法夹带字节码）。
- **禁用 API**（字节码扫描，命中即拒收、0 分）：

| 类别 | 禁止 |
|---|---|
| 反射 | `java.lang.reflect.*`、`Class.forName`、`java.lang.invoke.*` |
| 子进程 | `Runtime`、`ProcessBuilder` |
| 线程 | Thread 创建/启动、`java.util.concurrent.*` |
| 类加载 | 自定义 ClassLoader |
| 退出 | `System.exit` |
| 随机 | `java.util.Random`（被改写的 `Math.random()` 是确定性的、**允许**） |
| 引擎状态 | 直接修改成员血量/物资/名单——只能通过引擎应用你的行动和选择 |
| 文件 | `java.io.*`、`java.nio.*`——唯一例外：控制台打印（`System.out`/`System.err`） |
| 网络 | `java.net.*` |
| 环境 | `System.getenv`、`System.getProperty` |

- **预算**：每个学生回调 **100,000 计数步**（超了该回合跳过，回放标注）；每个种子 **10 秒墙钟**（子 JVM `-Xmx256m`），超时强杀。
- **确定性**：`Math.random()` 和时间 API 被插桩改写为种子来源；所有队伍跑相同种子；**相同提交永远相同分数**。