---
title: ISA104 ICT 模拟卷四（Set D · 20 题 + 答案）
tags: [ISA104, mock, ICT]
course: ISA104 AI Application Design
---

# ISA104 ICT 模拟卷四（Part 1 · 20 题 MCQ）

> **模拟对象**：In-Class Test（Week 10，90 分钟，35%）Part 1（20 题，20%）
> **范围**：W1–W9 讲义 + Week 8 Tutorial + Lab 2–3
> **考点去重**：本卷 20 题与 [[ISA104 ICT 模拟（20题MCQ+写作模板）|卷一]]、[[ISA104 ICT 模拟卷二（Set B 20题+答案）|卷二]]、[[ISA104 ICT 模拟卷三（Set C 20题+答案）|卷三]] **零重复**——四卷合计 80 题，每题考一个不同知识点。
> 建议 25–30 分钟完成；每题 1 分，单选。答案与解析在文末（折叠）。

---

## Part 1 · Multiple Choice（20 题）

**Q1.**（W1）AI 应用开发全生命周期（讲义版）的正确阶段顺序是：

A. Deployment → Ideation → Testing → Design
B. Testing → Ideation → Feasibility → Deployment
C. Ideation → Feasibility Analysis → Concept & Prototyping → Test & Evaluation → Deployment & Maintenance
D. Feasibility → Deployment → Ideation → Prototyping

**Q2.**（W2）Transformer 组件流水线中，MLP 层的作用是：

A. 计算输入序列中元素之间的关系
B. 对每个位置独立做非线性变换（逐位置处理），可能存储模型学到的事实
C. 把文本切成 token
D. 决定输出序列的长度

**Q3.**（W2）top-p（nucleus）采样的定义是：

A. 永远选择概率最高的 token
B. 从全部词表均匀随机采样
C. 只从概率最高的前 k 个 token 中采样
D. 从累计概率达到 p 的最小 token 集合中采样（p 常取 0.9–0.95）

**Q4.**（W3）讲义提到的提示注入防御措施包括：

A. 输入/输出校验、最小权限、高风险动作人工审批、持续监控与红队测试等
B. 删除所有安全护栏
C. 给模型最高权限
D. 完全依赖用户自觉

**Q5.**（W3）GPT-3 在 SuperGLUE 基准上 zero-shot / one-shot / few-shot 的表现（讲义数据）是：

A. few-shot 最低
B. 三种设置得分完全相同
C. zero-shot ≈58%，one-shot ≈70%，few-shot >70%——示例越多表现越好
D. zero-shot 最高

**Q6.**（W4）Transparency / Interpretability / Explainability 三概念的分层对应是：

A. Transparency = 系统级（开发与治理）；Interpretability = 模型级（结构与算法）；Explainability = 用户级（向人解释决策）
B. 三者都属于用户级
C. Transparency 是模型级概念
D. Explainability 是系统级概念

**Q7.**（W4）NIST AI RMF 中 GOVERN 功能的特点是：

A. 只负责识别风险
B. 贯穿并支撑 MAP、MEASURE、MANAGE 所有功能——负责文化、政策、问责等治理基础
C. 只负责度量风险
D. 只负责处置风险

**Q8.**（W5）Embedding（嵌入）的语义特性是：

A. 与语义无关，只表示词频
B. 只能表示整数
C. 维度恒为 1
D. 语义相近的对象向量相近（如 "King − Man + Woman ≈ Queen"）

**Q9.**（W5）RAG 系统的一个已知局限是：

A. 完全不需要基础设施
B. 可以彻底消除幻觉
C. 延迟（latency）：离线索引与在线检索生成都会带来额外时间开销
D. 不需要知识库

**Q10.**（W6）LLM 适合充当 agent 大脑的四个特质是：

A. 只有速度与参数量
B. 只有记忆与算力
C. 只有创造力
D. autonomy（自主性）、reactivity（反应性）、pro-activeness（主动性）、social ability（社交能力）

**Q11.**（W6）五类 agent 风险中，"Action 行动错误"（如说错价格后真的买下不可退机票）的对策是：

A. 最小权限（least privilege）、使用可信工具、执行前检查、记录日志
B. 数据与指令分离
C. 增加训练数据
D. 提高 temperature

**Q12.**（W8）语音对话系统五模块中，DM（对话管理，决定下一步回应/动作）的典型例子是：

A. Google Live Transcribe
B. Vapi、Retell
C. Amazon Alexa
D. ElevenLabs

**Q13.**（W9）semi-structured（半结构化）访谈的特点是：

A. 问题顺序完全固定，便于比较
B. 完全开放、无任何预设
C. 有主题提纲但允许灵活追问，兼顾深度与灵活性
D. 等同于问卷调查

**Q14.**（W9）关于两套可用性指标体系的对应关系，正确的是：

A. Nielsen 五要素：learnability、efficiency、memorability、errors、satisfaction；ISO 9241-11 三要素：effectiveness、efficiency、satisfaction
B. Nielsen 与 ISO 完全相同
C. ISO 9241-11 有五个要素，Nielsen 有三个
D. Nielsen 五要素中没有 errors

**Q15.**（W9）InterLink 研究（12 人、within-subjects、平衡顺序）的主要结论是：

A. 时间差异显著而正确率不显著
B. 两者都显著
C. 研究没有发现任何差异
D. 正确率 92% vs 81%（差异显著 p<.05），而时间 122s vs 128s（差异不显著）——正确率证据更强

**Q16.**（Lab 2）self-consistency（自洽性）的实现方式是：

A. 只运行一次模型
B. 在较高 temperature 下采样多条推理路径，对最终答案投票、取多数一致的结果
C. 把 temperature 设为 0
D. 删除所有示例

**Q17.**（Lab 2）提示注入攻击之所以常常奏效，根本原因是：

A. 模型把 system prompt 与用户消息当作同一文本流处理，恶意指令可以"覆盖"系统指令
B. 模型有两个互相独立的大脑
C. 系统提示是加密存储的
D. 用户消息根本不会被发送给模型

**Q18.**（Lab 3）Skill / Tool / MCP 三者的区分是：

A. 三者是完全相同的概念
B. MCP 是一种 Skill
C. Skill = 可复用的程序化指令/流程；Tool = 可调用的能力（生成、计算、搜索等）；MCP = agent 接入外部工具/资源的标准连接
D. Tool 只能用来画图

**Q19.**（Lab 3）为什么使用固定的评估集（evaluation set，含 input 与 reference_output）比"看到输出后再改测试题"更可靠：

A. 随机出题更科学
B. 固定的输入与预期输出避免了针对已知输出修改题目的过拟合，结果可复现、更客观
C. 评估根本不需要预期输出
D. 只是为了节省时间

**Q20.**（Tutorial W8）Week 8 Tutorial 给出的设计提醒是：

A. 功能越多，agent 一定越好
B. 先选定 AI 功能，再去找用户
C. 不需要考虑不同用户的差异
D. 从用户需求出发，只有当 AI 能让真实任务变得更好时才加入；更简单的设计可能是更好的选择

---

## 知识点分布

| 来源 | 题号 | 来源 | 题号 |
|---|---|---|---|
| W1 | 1 | W8 | 12 |
| W2 | 2–3 | W9 | 13–15 |
| W3 | 4–5 | Lab 2 | 16–17 |
| W4 | 6–7 | Lab 3 | 18–19 |
| W5 | 8–9 | Tutorial W8 | 20 |
| W6 | 10–11 | | |

## Part 2 · Reflective Writing（选做，15%，400–600 词）

> **题目（人本设计向）**：*Reflect on how your team applied human-centred design ideas when creating your AI agent — for example, understanding your users, defining their needs, or testing with users. Use the "What? So What? Now What?" structure.*
>
> 写作框架、评分标准与范文模板见 [[ISA104 ICT 模拟（20题MCQ+写作模板）|卷一 Part 2]]。可连接课程概念：Double Diamond / 用户访谈 / formative evaluation（W9）、从用户需求出发而非"为用 AI 而用 AI"（W8）、utility vs usability。

---

> [!tip]- 答案速查与解析（点击展开）
> | 题号 | 答案 | 解析 |
> |---|---|---|
> | 1 | C | 生命周期：Ideation → Feasibility → Concept & Prototyping → Test & Evaluation → Deployment & Maintenance |
> | 2 | B | MLP 逐位置独立变换，可能存事实；"关系"是 multi-head attention 的职责 |
> | 3 | D | top-p：累计概率达到 p 的最小集合；A=greedy，C=top-k |
> | 4 | A | 防御：输入/输出校验、最小权限、人工审批、监控与红队测试等 |
> | 5 | C | SuperGLUE：zero 58% → one 70% → few >70% |
> | 6 | A | 黑盒三概念：Transparency（系统）/ Interpretability（模型）/ Explainability（用户） |
> | 7 | B | GOVERN 贯穿所有功能；MAP=识别，MEASURE=度量，MANAGE=处置 |
> | 8 | D | Embedding 语义相近 → 向量相近（King−Man+Woman≈Queen） |
> | 9 | C | RAG 局限：延迟（索引 + 在线检索生成额外耗时） |
> | 10 | D | 四特质：autonomy、reactivity、pro-activeness、social ability |
> | 11 | A | Action 风险 → 最小权限、可信工具、执行前检查、日志；B 对应 Perception 注入 |
> | 12 | B | DM 例子：Vapi、Retell；A=ASR，C=NLU，D=TTS |
> | 13 | C | 半结构化：主题 + 追问，深度与灵活兼顾 |
> | 14 | A | Nielsen 五要素 vs ISO 9241-11 三要素（effectiveness/efficiency/satisfaction） |
> | 15 | D | 正确率 92% vs 81% 显著；时间 122s vs 128s 不显著 |
> | 16 | B | Self-consistency：高温多路径采样 + 多数投票（Lab 2 Task 5.4） |
> | 17 | A | system prompt 与用户消息是同一文本流 → 注入可"覆盖"指令（Lab 2 Task 7.1） |
> | 18 | C | Skill=可复用流程；Tool=可调用能力；MCP=标准连接 |
> | 19 | B | 固定评估集避免"看输出改题"的过拟合，更可靠 |
> | 20 | D | 用户需求优先，AI 让真实任务更好才加；简单设计可能是更好选择 |
