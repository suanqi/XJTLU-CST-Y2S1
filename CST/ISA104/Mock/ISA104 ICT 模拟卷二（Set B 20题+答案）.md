---
title: ISA104 ICT 模拟卷二（Set B · 20 题 + 答案）
tags: [ISA104, mock, ICT]
course: ISA104 AI Application Design
---

# ISA104 ICT 模拟卷二（Part 1 · 20 题 MCQ）

> **模拟对象**：In-Class Test（Week 10，90 分钟，35%）Part 1（20 题，20%）
> **范围**：W1–W9 讲义 + Week 3 Tutorial + Lab 1–2
> **考点去重**：本卷 20 题与 [[ISA104 ICT 模拟（20题MCQ+写作模板）|卷一]]、[[ISA104 ICT 模拟卷三（Set C 20题+答案）|卷三]]、[[ISA104 ICT 模拟卷四（Set D 20题+答案）|卷四]] **零重复**——四卷合计 80 题，每题考一个不同知识点。
> 建议 25–30 分钟完成；每题 1 分，单选。答案与解析在文末（折叠）。

---

## Part 1 · Multiple Choice（20 题）

**Q1.**（W1）与传统 AI（面向分类、推荐、检测等特定任务）相比，生成式 AI（GenAI）的核心特征是：

A. 只能给已有数据打标签
B. 学习数据分布并生成新内容（文本/图像/音频/视频/代码）
C. 完全不需要训练数据
D. 只能处理结构化表格数据

**Q2.**（W1）"模型漂移（model drift）"指的是：

A. 模型部署时从一台服务器迁移到另一台
B. 训练过程中损失函数的正常波动
C. 现实世界随时间变化，导致旧模型的性能逐渐下降
D. 模型架构的升级换代

**Q3.**（W2）BERT 采用的架构与训练目标、擅长任务是：

A. Encoder-only + 掩码语言建模（MLM），擅长分类、命名实体识别等理解任务
B. Decoder-only + 自回归生成，擅长对话
C. Encoder-Decoder + seq2seq，擅长翻译
D. CNN + 图像分类

**Q4.**（W2）T5、BART 这类模型的架构与典型任务组合是：

A. Encoder-Decoder（seq2seq），适合翻译、摘要、问答
B. Encoder-only，适合对话生成
C. Decoder-only，适合命名实体识别
D. 判别式模型，适合文本分类

**Q5.**（W2）关于 logits 与 softmax 的关系，正确的是：

A. logits 是模型输出的未归一化原始得分；softmax 将其转换为和为 1 的概率分布
B. logits 本身就是概率
C. softmax 把概率还原为原始得分
D. 两者没有关系

**Q6.**（W3）"涌现能力（emergent ability）"指的是：

A. 小模型天生具备的能力
B. 模型规模扩大后突然出现的能力，如指令遵循、上下文学习、思维链
C. 只能通过微调获得的能力
D. 只出现在视觉模型中的能力

**Q7.**（W3）与提示注入（把恶意指令藏进输入）不同，越狱（jailbreaking）指的是：

A. 通过角色扮演（如 DAN "Do Anything Now"）等手段绕过模型内置的安全护栏
B. 窃取模型的训练数据
C. 把恶意指令藏在外部网页或文档中
D. 对模型进行分布式训练

**Q8.**（W4）在机器学习中，Bias 与 Variance 的正确解释是：

A. Bias 是预测值与真值之间的系统误差；Variance 是模型对训练数据噪声的敏感性（常导致过拟合）
B. Bias 是过拟合，Variance 是欠拟合
C. Bias 与 Variance 都与数据无关
D. 好的模型应该追求两者都高

**Q9.**（W4）按 EU AI Act 的风险分级，以下哪类属于 "Unacceptable（不可接受）" 级别、被直接禁止：

A. 垃圾邮件过滤器
B. 社会评分、无差别抓取人脸图像建库
C. 聊天机器人（需告知用户其为 AI）
D. 教育领域的 AI 工具

**Q10.**（W5）RAG 离线索引管线（Indexing）的正确顺序是：

A. 加载文档 → 切块（chunking）→ 转换为 embedding → 建索引 → 存入向量数据库
B. 切块 → 加载 → 存储 → 转换 → 索引
C. 建索引 → 加载 → 切块 → 存储 → 转换
D. 存储 → 索引 → 转换 → 切块 → 加载

**Q11.**（W5）切块（chunking）时让相邻块重叠（overlap）的主要目的是：

A. 保持块与块之间的上下文连续，避免语义被切断
B. 压缩文档体积
C. 对文档加密
D. 减少 embedding 的计算量

**Q12.**（W5）RAG 评估中，"证据被正确检索到了，但 LLM 无视、歪曲或编造了答案"，这属于：

A. retrieval failure（检索失败）
B. knowledgebase quality（知识库质量）问题
C. generation failure（生成失败）
D. response failure（应答失败）

**Q13.**（W6）Agentic AI 演进路线中的第一个里程碑 NASA Remote Agent（1999）：

A. 是首个基于 Transformer 的通用 agent
B. 用于航天器自主控制，由 Planner + Executive + Diagnostic 组成，属于反应式、硬编码系统
C. 使用 MCP 协议连接外部工具
D. 是一个多智能体协作系统

**Q14.**（W6）Generative Agents（Smallville）中，长期记忆的打分公式是：

A. score(m) = α·recency + β·importance + γ·relevance（新近性 + 重要性 + 相关性）
B. 只按记忆的存储时间排序
C. 只按 embedding 相似度排序
D. 随机打分

**Q15.**（W8）AI 应用五段式解剖中，"Human Feedback" 环节的作用是：

A. 用户对输出进行接受、编辑、纠正或拒绝——AI 只是整个应用的一部分
B. 完全自动化，不需要人的参与
C. 只在模型训练阶段存在
D. 等同于 RLHF 预训练

**Q16.**（W8）语音对话系统中，NLU（自然语言理解）模块的功能是：

A. 把语音转成文字
B. 把文字映射为意图（intent）与槽位（slot），典型例子是 Amazon Alexa
C. 把文字转成语音
D. 决定执行哪个外部动作

**Q17.**（W9）Double Diamond 的 Define 阶段常用的方法与产出是：

A. 观察、访谈、问卷 → 用户与情境证据
B. 编码、亲和图（affinity mapping）、需求分析 → 聚焦的问题与设计需求
C. 头脑风暴、草图、原型 → 备选方案
D. 可用性测试 → 评估证据

**Q18.**（W9）Nielsen 界面设计原则中的 recognition（识别优于回忆）意味着：

A. 界面应展示可选项让用户"识别"，而不是让用户凭空"回忆"命令
B. 所有功能都应藏在多层菜单深处
C. 用户必须记住快捷键才能操作
D. 界面只显示系统日志

**Q19.**（Lab 1）关于 Ollama，正确的是：

A. 它是一个云端闭源大模型平台
B. 它是开源的本地 LLM 运行与管理工具；在 Lab 1 架构中，Ollama API 充当 Python UI 与 LLM 后端之间的"中间件"
C. 它是一种编程语言
D. 它是一种向量数据库

**Q20.**（Lab 2）关于 temperature = 0 的可复现性，讲义与实验的结论是：

A. temperature 0 时输出一定逐字节完全一致
B. temperature 0 时输出完全随机
C. 即使 temperature = 0，输出也不保证逐字节完全可复现
D. temperature 0 会让模型拒绝回答

---

## 知识点分布

| 来源 | 题号 | 来源 | 题号 |
|---|---|---|---|
| W1 | 1–2 | W6 | 13–14 |
| W2 | 3–5 | W8 | 15–16 |
| W3 | 6–7 | W9 | 17–18 |
| W4 | 8–9 | Lab 1 | 19 |
| W5 | 10–12 | Lab 2 | 20 |

## Part 2 · Reflective Writing（选做，15%，400–600 词）

> **题目**（Week 7 Tutorial 练习原题）：*Write a 400–600-word reflective essay on what technical skills you and your group developed to create your AI agent. Your reflection should be structured using the "What? So What? Now What?" model and include specific examples from the ISA104 course.*
>
> 写作框架、评分标准与范文模板见 [[ISA104 ICT 模拟（20题MCQ+写作模板）|卷一 Part 2]]。可参考素材：Lab 2 提示工程实验、Lab 3 RAG 与 agent 搭建、[[ISA104 Lab 3 - XIPU AI Agentic AI Tutorial]] 中的评估流程。

---

> [!tip]- 答案速查与解析（点击展开）
> | 题号 | 答案 | 解析 |
> |---|---|---|
> | 1 | B | GenAI 学习数据分布并**生成新内容**；传统 AI 面向特定任务（分类/推荐/检测） |
> | 2 | C | Model drift：世界变化 → 旧模型准确率下降 |
> | 3 | A | BERT = Encoder-only、MLM、双向理解，擅长分类/NER |
> | 4 | A | T5、BART = Encoder-Decoder（seq2seq），翻译/摘要/问答 |
> | 5 | A | logits 未归一；softmax 转为概率（和为 1） |
> | 6 | B | 涌现能力：规模扩大后"量变引起质变" |
> | 7 | A | 越狱 = 绕过内置护栏（DAN 角色扮演）；B/C 属注入，D 无关 |
> | 8 | A | Bias = 系统误差；Variance = 对噪声敏感、过拟合 |
> | 9 | B | Unacceptable 级被禁止，如社会评分、无差别抓脸建库；C 属 Transparency 级 |
> | 10 | A | Indexing：加载 → 切块 → 转换 → 索引 → 存储（向量数据库） |
> | 11 | A | Overlap 保持上下文连续，避免语义断裂 |
> | 12 | C | 检索对了但生成环节无视/歪曲/编造 = generation failure |
> | 13 | B | NASA Remote Agent（1999）：Planner + Executive + Diagnostic，反应式硬编码 |
> | 14 | A | 记忆打分 = α·recency + β·importance + γ·relevance |
> | 15 | A | Human Feedback：接受/编辑/纠正/拒绝；AI 只是应用的一部分 |
> | 16 | B | NLU：文字 → 意图与槽位（Alexa）；A 是 ASR，C 是 TTS，D 是 DM |
> | 17 | B | Define：编码、亲和图、需求分析 → 聚焦的问题与设计需求 |
> | 18 | A | Recognition：展示选项让人识别，而非回忆 |
> | 19 | B | Ollama：开源、本地运行 LLM；架构中 UI → Ollama API（中间件）→ Gemma3 270M |
> | 20 | C | 讲义：temperature 0 也不是完美可复现（Lab 2 Task 4.2） |
