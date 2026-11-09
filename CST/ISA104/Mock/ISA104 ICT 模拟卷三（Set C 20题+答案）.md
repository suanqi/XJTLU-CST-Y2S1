---
title: ISA104 ICT 模拟卷三（Set C · 20 题 + 答案）
tags: [ISA104, mock, ICT]
course: ISA104 AI Application Design
---

# ISA104 ICT 模拟卷三（Part 1 · 20 题 MCQ）

> **模拟对象**：In-Class Test（Week 10，90 分钟，35%）Part 1（20 题，20%）
> **范围**：W1–W9 讲义 + Week 3 Tutorial + Lab 1–3
> **考点去重**：本卷 20 题与 [[ISA104 ICT 模拟（20题MCQ+写作模板）|卷一]]、[[ISA104 ICT 模拟卷二（Set B 20题+答案）|卷二]]、[[ISA104 ICT 模拟卷四（Set D 20题+答案）|卷四]] **零重复**——四卷合计 80 题，每题考一个不同知识点。
> 建议 25–30 分钟完成；每题 1 分，单选。答案与解析在文末（折叠）。

---

## Part 1 · Multiple Choice（20 题）

**Q1.**（W1）关于 token 化，讲义中的经验数值是：

A. 1 个英文单词 = 10 个 token
B. 约 1 个英文单词 ≈ 1.3 个 token（中文词更多，约 1.5–2 个）
C. 所有语言的每个词都恰好是 1 个 token
D. token 数量与文本长度无关

**Q2.**（W2）GPT-3 的规模参数（讲义参考值）是：

A. 词表 500；总参数 1B
B. 8 头 × 8 层；参数 10M
C. 词表 50,257；embedding 维度 12,288；96 头 × 96 层；总参数约 175B
D. 词表 3 万；参数 1T

**Q3.**（W2）使用 LLM 的三条路径，按成本与技术门槛从低到高排列：

A. 调用现成 API < 微调开源模型 < 自建基础模型
B. 自建基础模型 < 微调开源模型 < 调用 API
C. 三者成本完全相同
D. 微调 < 调用 API < 自建

**Q4.**（W3）Prompt 四要素中，"Output Indicator" 指的是：

A. 任务的背景信息
B. 待处理的输入数据
C. 任务指令本身
D. 对期望输出格式的指示（如"只返回一个词"）

**Q5.**（W3）Zero-shot CoT 的典型做法是：

A. 提供大量带完整推理过程的示例
B. 在问题后追加 "Let's think step by step" 之类语句，引导模型逐步推理
C. 对模型进行微调
D. 把 temperature 调到 2 以上

**Q6.**（W4）三大失败案例的风险域归类，正确的是：

A. 三者都是隐私问题
B. Amazon → 军事滥用；SyRI → 幻觉；Air Canada → 歧视
C. 三者都属于失控 AI（rogue AI）
D. Amazon 招聘工具 → 歧视（Discrimination）；荷兰 SyRI → 隐私/透明度（Privacy/Transparency）；Air Canada 聊天机器人 → 虚假信息/问责（Misinformation/Accountability）

**Q7.**（W4）关于 Responsible AI 五支柱与 Governance 的关系：

A. Governance 是第六支柱
B. 五支柱里没有 Fairness
C. 五支柱是 Explainability、Fairness、Robustness、Transparency、Privacy & Security；Governance 是让五支柱落地的机制，不是第六支柱
D. Governance 与五支柱无关

**Q8.**（W4）模型生产者与模型使用者的安全职责分工：

A. 生产者负责数据清理、价值对齐（RLHF/DPO）、提供 model card；使用者负责选型、微调、设计提示模板并加外部 guardrails
B. 使用者负责 RLHF 与 model card
C. 生产者负责应用层的词过滤与内容过滤
D. 双方都没有安全职责

**Q9.**（W5）RAG 生成阶段的实用检索流程是：

A. 把整个知识库直接塞进 prompt
B. 先宽召回 top 20–50 → 用更贵的模型重排（rerank）→ 取 top-k（3–5）给 LLM
C. 只取相似度最高的 1 条
D. 随机抽取若干条

**Q10.**（W5）"negative rejection（负向拒绝）" 能力指的是：

A. 知识库中没有相关信息时，系统应明确拒绝回答，而不是编造答案
B. 拒绝所有用户请求
C. 过滤不文明用语
D. 拒绝检索任何文档

**Q11.**（W6）MCP（Model Context Protocol）的作用是：

A. 一种新的 LLM 架构
B. 一种采样参数
C. 一种向量数据库
D. 为 agent 提供标准化的"工具连接"接口，统一接入 GitHub、文件系统、终端等外部工具

**Q12.**（W6）多智能体协作（如 AutoGen）的一个关键隐患是：

A. 多 agent 一定比单 agent 更正确
B. 多 agent 系统没有成本
C. 多个 agent 相互认同不等于答案正确——错误可能被互相强化
D. 人类无法参与其中

**Q13.**（W8）Weisz et al.（CHI 2024）提出的生成式 AI 体验六原则之一 "appropriate trust（恰当信任）" 的含义是：

A. 让用户知道何时应该复查、质疑 AI 的结果
B. 无条件信任 AI 的所有输出
C. 隐藏 AI 的不确定性
D. 永远全自动执行

**Q14.**（W8）Hu et al.（2025）提出的人机协作四模式是：

A. 只有"全自动"一种模式
B. AI supports（AI 辅助，人拍板）/ AI acts if clear（低风险自动处理）/ AI asks for input（先问清）/ decide together（来回协作）
C. 只有"人做一切"一种模式
D. AI 独自决策，人不参与

**Q15.**（W9）Formative（形成性）与 Summative（总结性）评估的区别是：

A. Formative 只看最终分数；Summative 只用于纸原型
B. 两者完全相同
C. Summative 用于找问题、Formative 用于打分
D. Formative 用于发现并改进设计问题；Summative 用于评估设计是否达标

**Q16.**（W9）within-subjects（组内）实验设计的 carry-over 效应及对策：

A. 不同组体验不同条件，因此没有 carry-over 问题
B. 只需测一次，无需对策
C. 同一批参与者体验所有条件，前一条件的表现可能影响后一条件（carry-over）；用 counterbalancing（平衡顺序）来抵消
D. carry-over 效应只出现在 between-subjects 中

**Q17.**（Lab 1）与传统程序实现的计算器相比，Lab 1 中的 AI 计算器：

A. AI 计算器永远正确
B. 传统实现更简单
C. 两者表现完全相同
D. 传统方法能保证结果正确，而 AI 计算器可能给出错误答案——设计 AI 应用需考虑可靠性、准确性等问题

**Q18.**（Lab 2）从 prompt 中删除四要素之一的 context（背景信息）后，通常会发生：

A. 模型失去任务背景，可能在错误的领域或场景下作答
B. 输出没有任何变化
C. 输出变得更长
D. 程序无法运行

**Q19.**（Lab 3）Lab 3 的核心设计思想是：

A. 组件越多，agent 一定越好
B. 永远不要使用 RAG
C. 不要因为 RAG、工具、MCP、技能、多智能体"存在"就全都加上——应从适用场景出发，只添加能可靠完成任务的组件
D. 只允许使用单 agent

**Q20.**（Tutorial W3）Week 3 Tutorial 要求把语句分为 Fact / Opinion / Ethical risk / Evidence 四类。下列哪句话属于 Ethical risk（伦理风险）类？

A. "GPT-3 的参数约为 175B"（可查证真假）
B. "把学生个人信息输入公共 AI 工具可能带来隐私危害"
C. "我觉得 AI 是这十年最重要的技术"（个人信念或判断）
D. "根据调查，80% 的学生使用过 AI"（支持断言的事实/例子/来源）

---

## 知识点分布

| 来源 | 题号 | 来源 | 题号 |
|---|---|---|---|
| W1 | 1 | W8 | 13–14 |
| W2 | 2–3 | W9 | 15–16 |
| W3 | 4–5 | Lab 1 | 17 |
| W4 | 6–8 | Lab 2 | 18 |
| W5 | 9–10 | Lab 3 | 19 |
| W6 | 11–12 | Tutorial W3 | 20 |

## Part 2 · Reflective Writing（选做，15%，400–600 词）

> **题目（安全伦理向）**：*Reflect on one AI safety or ethical challenge your group faced when building or testing your AI agent (for example, hallucination, privacy protection, guardrails, or prompt injection), and how you addressed it. Use the "What? So What? Now What?" structure.*
>
> 写作框架、评分标准与范文模板见 [[ISA104 ICT 模拟（20题MCQ+写作模板）|卷一 Part 2]]。可连接课程概念：幻觉 → misinformation（W4）、guardrails / 最小权限（W4/W6）、注入测试（Lab 2）、negative rejection（W5/Lab 3）。

---

> [!tip]- 答案速查与解析（点击展开）
> | 题号 | 答案 | 解析 |
> |---|---|---|
> | 1 | B | 1 英文词 ≈ 1.3 token；中文词约 1.5–2 token |
> | 2 | C | GPT-3：词表 50,257、维度 12,288、96 头 × 96 层、约 175B 参数 |
> | 3 | A | API 现成模型 < 微调开源模型 < 自建基础模型 |
> | 4 | D | Output Indicator = 期望输出格式；A 是 Context，B 是 Input Data，C 是 Instruction |
> | 5 | B | Zero-shot CoT 只需追加 "Let's think step by step"；A 是 few-shot CoT |
> | 6 | D | Amazon=歧视；SyRI=隐私/透明度；Air Canada=虚假信息/问责 |
> | 7 | C | Governance 是落地机制，不是第六支柱 |
> | 8 | A | 生产者：数据清理、RLHF/DPO 价值对齐、model card；使用者：guardrails 等 |
> | 9 | B | 宽召回 top 20–50 → rerank → top-k（3–5）；k 太小漏证据、太大引入噪声 |
> | 10 | A | Negative rejection：库里没有答案就拒绝回答（而非编造） |
> | 11 | D | MCP = 标准化工具连接接口 |
> | 12 | C | 相互认同 ≠ 正确，可能互相强化错误 |
> | 13 | A | Appropriate trust：知道何时应复查结果 |
> | 14 | B | 四模式：AI supports / AI acts if clear / AI asks for input / decide together |
> | 15 | D | Formative 改进设计；Summative 判断是否达标 |
> | 16 | C | 组内设计的 carry-over 效应用 counterbalancing 抵消 |
> | 17 | D | 传统实现保证正确；AI 计算器可能出错 |
> | 18 | A | 缺 context 时模型失去任务背景（Lab 2 Task 2.1） |
> | 19 | C | 从场景出发，只加能可靠完成任务的组件 |
> | 20 | B | "可能带来隐私危害"= 对人/社会的可能危害 → Ethical risk；A=Fact，C=Opinion，D=Evidence |
