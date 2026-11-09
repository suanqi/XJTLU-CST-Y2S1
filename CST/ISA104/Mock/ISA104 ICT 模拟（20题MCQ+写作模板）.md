---
title: ISA104 ICT 模拟（20题MCQ+写作模板）
tags: [ISA104, mock, ICT]
course: ISA104 AI Application Design
---

# ISA104 ICT 模拟卷（Part 1 MCQ 20 题 + Part 2 写作模板）

> **模拟对象**：In-Class Test（Week 10，90 分钟，35%）
> **建议时间**：Part 1 约 30 分钟；Part 2 约 60 分钟
> **范围**：Week 1–9 ｜ 完成后发我批改。
> ⚠️ 本卷暂不提供答案。

---

## Part 1 · Multiple Choice（20 题，每题 1%）

**Q1.**（W1）理论上能像人类一样完成**任何**智力任务、但尚未实现的 AI 称为：
A. Traditional AI　B. Generative AI　C. AGI　D. ASI

**Q2.**（W1/W2）2017 年奠定几乎所有现代 LLM 基础架构的里程碑是：
A. Transformer　B. CNN　C. Perceptron　D. Hopfield Network

**Q3.**（W2）GPT、Llama 这类模型属于：
A. Encoder-only（掩码语言建模，双向理解）　B. Decoder-only（自回归生成）　C. Encoder-Decoder　D. 判别式模型

**Q4.**（W2）Transformer 中 multi-head self-attention（Q/K/V）的主要作用是：
A. 存储模型学到的"事实"　B. 对数据做归一化　C. 识别输入序列中元素之间的关系　D. 决定输出长度

**Q5.**（W2/W3）降低 sampling 的 temperature 会：
A. 使输出更确定、创造性更低　B. 使输出更随机多样　C. 加快推理速度　D. 使输出更长

**Q6.**（W3）zero-shot、one-shot、few-shot learning 都属于：
A. fine-tuning　B. in-context learning　C. RLHF　D. prompt injection

**Q7.**（W3）Chain-of-Thought（CoT）提示的主要作用是：
A. 减少 token 消耗　B. 防止越狱攻击　C. 加速模型训练　D. 提供中间推理步骤、提升复杂推理能力

**Q8.**（W3）攻击者把恶意指令藏在**外部网页**里，等待 AI 应用读取时触发，属于：
A. direct prompt injection　B. indirect prompt injection　C. jailbreaking　D. data poisoning

**Q9.**（W4）复杂 AI 模型的内部决策过程难以被人类理解，这一问题称为：
A. bias　B. variance　C. black-box problem　D. overfitting

**Q10.**（W4）EU AI Act 把 AI 系统分为多少个风险等级：
A. 4 个　B. 2 个　C. 5 个　D. 3 个

**Q11.**（W4）NIST AI RMF 的四个功能中，负责"框定情境、识别与描述风险"的是：
A. GOVERN　B. MAP　C. MEASURE　D. MANAGE

**Q12.**（W5）RAG 主要解决 LLM 的什么问题：
A. 推理速度慢　B. 上下文长度受限　C. 部署成本高　D. 知识截止与私有知识缺失导致的幻觉

**Q13.**（W5）RAG 索引管线中，把长文档切成小块（chunking）的主要目的是：
A. 克服 token 上限并提高检索精度　B. 加密数据　C. 降低存储成本　D. 提高模型创造力

**Q14.**（W5）与余弦相似度（语义检索）不同，BM25 是：
A. 稠密向量语义检索　B. 基于词频与逆文档频率的稀疏关键词检索　C. 一种向量数据库　D. 一种微调方法

**Q15.**（W6）以下哪一项**不是** Agentic AI 系统的核心特征：
A. 追求目标　B. 在环境中选择并执行动作　C. 基于记忆与反馈反思　D. 只生成文本、从不采取行动

**Q16.**（W6）ReAct 框架的循环模式是：
A. Plan → Act　B. Thought → Action → Observation　C. Train → Test　D. Generate → Evaluate

**Q17.**（W8）语音对话系统中，把**语音转成文字**的模块是：
A. ASR　B. NLU　C. NLG　D. TTS

**Q18.**（W8）创意过程的四阶段中，**由人主导**、AI 难以代劳的是：
A. Generating ideas　B. Evaluating ideas　C. Problem identification & framing　D. Implementing ideas

**Q19.**（W9）Double Diamond 四个阶段的正确顺序是：
A. Discover → Define → Develop → Deliver　B. Define → Discover → Develop → Deliver　C. Discover → Develop → Define → Deliver　D. Develop → Discover → Define → Deliver

**Q20.**（W9）关于 SUS（System Usability Scale），正确的是：
A. 分数范围 0–10　B. 分数范围 1–5　C. 总分 0–100 的综合量表分（不是百分比）　D. 分数范围 0–1

---

## Part 2 · Reflective Writing 模板与范文（15%，400–600 词）

### 2.1 三段式框架（硬性要求）

| 段落 | 目的 | 要点 |
|---|---|---|
| **What?** | 描述 | 你做了哪个实践环节？你的角色？遇到的挑战？ |
| **So What?** | 分析 | 学到了什么？与课程概念（RAG/伦理/HCD/提示工程…）如何关联？说明了你的什么成长？ |
| **Now What?** | 展望 | 未来工程/设计情境中如何应用？你会做哪些改变？ |

### 2.2 评分对照（各 5 分）
- **Task**：描述清晰 + 分析深入 + 未来应用 + 批判性思考 + 课程知识体现
- **Coherence & Cohesion**：段落主题句清晰、衔接自然、连接词多样
- **Grammar & Vocabulary**：学术词汇、句式多样、错误少

### 2.3 范文 Sample（约 420 词 · 基于一个 RAG 学习助手项目，仅供参考结构，内容勿照抄）

**Reflecting on Building the RAG Pipeline for Our AI Study Assistant**

*What?*
In our group project, I was responsible for building the retrieval-augmented generation (RAG) pipeline for "SmartPrep", an AI study assistant that answers first-year students' questions about module content. My task was to turn a folder of lecture PDFs into a searchable knowledge base: loading the documents, splitting them into chunks, converting them into embeddings, and testing retrieval quality. The main challenge I faced was retrieval failure: when a question spanned two lectures, the system often returned irrelevant chunks. I initially blamed the language model, but through systematic testing our team found that the chunking strategy was at fault — chunks that were too short lost context, while long ones introduced noise.

*So What?*
This experience taught me that the quality of an AI application depends less on the model itself than on the design of the system around it — a key theme from the RAG lecture. I learned to evaluate the system diagnostically: instead of asking "is the answer wrong?", we asked "did the correct evidence reach the model?", "is the knowledge base itself accurate?", and "did the model ignore the evidence?". Adjusting the chunk size and adding overlap measurably improved our test accuracy, showing me that evidence-based engineering decisions, rather than intuition, drive real improvement. I also became more aware of the ethical dimension from the AI safety lecture: an assistant that answers from memory instead of the knowledge base is a misinformation risk, so we added a rule requiring the agent to cite sources and to say "I don't know" when nothing relevant is retrieved.

*Now What?*
In future engineering contexts, I will apply the same diagnostic mindset: before changing the model, examine the data and the pipeline first. For our agent specifically, I plan to add negative-rejection and noise-robustness tests before the final demonstration. More broadly, I now understand that designing AI responsibly means deciding in advance what the AI may do, what evidence it must show, and where a human must approve — a lesson I will carry into any future AI or software project.

### 2.4 句式模板 Sentence Frames（直接套用，替换加粗部分）
- What: *In our group project, I was responsible for **______**. The main challenge I faced was **______**.*
- So What: *This experience taught me that **______**, which connects directly to the lecture on **______**. I learned to **______**.*
- Now What: *In future engineering contexts, I will **______**. For our project, I plan to **______** before the demonstration.*

### 2.5 课程概念连接库（So What 段至少要连 1–2 个）
| 概念 | 可用句式 |
|---|---|
| RAG（W5） | retrieval failure / knowledge-base quality / generation failure / chunking / 引用来源 |
| 伦理（W4） | hallucination → misinformation 风险 / transparency / accountability / guardrails |
| 提示工程（W3） | few-shot 示例、输出格式、迭代改进 prompt |
| Agentic AI（W6） | least privilege、human approval、ReAct 循环 |
| 人本设计（W9） | discover 用户访谈 → define 需求、utility vs usability、用证据支持设计决策 |

### 2.6 60 分钟时间规划
1. **0–5 min**：审题 + 圈出要反思的实践环节（选你**真正负责、有细节**的部分）；
2. **5–10 min**：列提纲——每段 2–3 个要点 + 1 个课程概念连接；
3. **10–40 min**：写作（What 约 1/3，So What 约 1/2，Now What 约 1/6）；
4. **40–50 min**：检查结构（三段标题）、字数（400–600）、衔接词；
5. **50–60 min**：检查语法/拼写 + 通读。

---

## 答题提示
- MCQ 只选一个答案；不确定时先跳过，最后回头。
- Part 2 先写提纲再动笔；**务必**用 What / So What / Now What 三个标题。
- 完成后把答案发我（`Q1C Q2A …` + 作文全文或照片），我会按评分标准帮你批改。
