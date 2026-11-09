---
title: ISA104 ICT 复习笔记（W1–W9）
tags: [ISA104, ICT, 复习]
course: ISA104 AI Application Design
---

# ISA104 ICT 复习笔记
# ISA104 AI Application Design · In-Class Test Review

> **考试**：Week 10，上课时间，**90 分钟**，占 **35%**（闭卷、独立完成、禁用一切材料与 AI）
> **Part 1**：20 道 MCQ（20%），范围 **W1–W9 讲义** ｜ **Part 2**：反思写作 400–600 词（15%），三段式 What / So What / Now What
> 配套：[[ISA104 ICT 模拟（20题MCQ+写作模板）]] ｜ 任务书：`ISA104/In class test/ISA104_Assessment1_Task_Sheet_and_MarkingScheme.pdf`

---

## W1 · Introduction to AI, GenAI & AI Applications

- **AI 版图**：
  - **Traditional AI**：面向特定任务（分类、推荐、检测）；
  - **GenAI（生成式 AI）**：学习数据分布并**生成新内容**（文本/图像/音频/视频/代码）；
  - **AGI（通用人工智能）**：与人类相当的**通用**智力（尚未实现）；
  - **ASI（超级人工智能）**：全面超越人类智力（理论概念）。
- **语言模型演进五阶段**：句法语法规则 → 专家系统与统计模型 → 神经模型与稠密表示 → 深度学习与 **Transformer** → **LLM**。
- **典型 GenAI 应用**：开发者效率（代码生成/补全）、音乐生成、影视创作、对话助手、文生图（DALL·E/Stable Diffusion/Midjourney）、文生视频（Sora）。
- **LLM 应用典型架构**：User → Application（guardrails 防护层）→ LLM；需要外部知识时挂 **RAG pipeline**（知识库 + 检索 + 生成）。
- **AI 的五个特征**：**概率性 probabilistic**（输出是概率采样，非确定答案）、**数据依赖 data dependent**、**模型漂移 model drift**（世界变化，旧模型变差）、**可解释性 explainability**、**可扩展性 scalability**。
- **开发全生命周期**：Ideation → Feasibility Analysis → Concept & Prototyping → Test & Evaluation → Deployment & Maintenance；分三层：**Application / Model / Infrastructure**。
- **Token 化**：文本先切成 token 再输入模型；约 1 个英文词 ≈ 1.3 token，1 个中文词 ≈ 1.5–2 token；词表大小（BERT 32k、Llama 32k、GPT-NeoX 50k）；也有**免分词模型**（CANINE、ByT5、Charformer，直接吃字节）。
- 风险案例：幻觉（编造事实）、隐私（PII 泄漏）、Air Canada 聊天机器人乱承诺被判担责等——引出后续 W3/W4。

## W2 · Introduction to LLMs

- **历史里程碑（背时间线）**：1888 Cajal 神经元 → 1943 McCulloch-Pitts 神经元数学模型 → 1949 Hebbian 学习 → 1952 Hodgkin-Huxley → 1958 Perceptron → 1982 Hopfield RNN → 1986 反向传播/MLP → 1989 CNN → 2006 Deep Belief Nets → **2017 Transformer（Attention Is All You Need）**。
- **LLM 三种架构**：
  | 类型 | 代表 | 训练目标 | 擅长任务 |
  |---|---|---|---|
  | Encoder-only（MLM） | BERT | 掩码语言建模，双向理解 | 分类、NER |
  | **Decoder-only（自回归）** | GPT、Llama | 从左到右逐词预测 | 生成、对话 |
  | Encoder-Decoder | T5、BART | seq2seq | 翻译、摘要、问答 |
- **LLM 组件流水线**：tokenization（分词）→ embeddings（词向量，数值表示）→ **multi-head self-attention**（Q/K/V，识别序列内元素关系；GPT-3 有 96 头、96 层）→ **MLP**（逐位置独立变换，可能存事实）→ linear output layer（logits）。
- **推理生成**：模型输出 **logits**（相对得分，不归一）→ **softmax** 转成概率 → 采样出词。
- **采样策略与参数**：
  | 参数 | 含义 | 效果 |
  |---|---|---|
  | greedy | 永远选最高概率 | 无创造性，输出固定 |
  | **temperature T** | 对 logits 先除以 T 再 softmax | T 低（<1）→ 更确定/保守；T 高 → 更多样/有创意 |
  | **top-k** | 只在概率前 k 名中采样（k 常 50–500） | k 小 → 可预测但缺乏创意 |
  | **top-p（nucleus）** | 累计概率达到 p 的最小集合中采样（p 常 0.9–0.95） | p 大 → 更多样 |
  | beam search | 保留多条候选路径按概率展开 | 精度与算力折中 |
  > 实践建议：temperature 与 top-p **只调一个**，别同时调。
- **GPT-3 规模参考**：词表 50,257；embedding 维度 12,288；96 头 × 96 层；总参数量约 **175B**。
- **用 LLM 的三条路**：调 API 用现成模型（低成本）＜ 微调开源模型 ＜ 自建基础模型（高成本高技术门槛）。
- **Foundation model（基础模型）**：预训练大模型，通常需在领域数据上**微调**才能胜任专业任务；输入长度有限 → 长文本要**切块**处理。

## W3 · Prompt Engineering & Critical Engagement ⭐

- **模型规模三维度**：参数量（PaLM 540B、Llama 3 405B、DeepSeek V3 671B）、训练数据量（数百 B tokens）、训练 FLOPs（浮点运算总量；FLOPS = 每秒浮点运算，性能指标）。
- **涌现能力 Emergent ability**：小模型没有、规模扩大后**突然出现**的能力（指令遵循、上下文学习、思维链）——"量变引起质变"。
- **In-context learning（上下文学习）**：不更新参数，仅靠提示中的示例学会新任务：
  - zero-shot（无示例）、one-shot（1 个示例）、**few-shot**（少量示例）；GPT-3 在 SuperGLUE：zero 58% → one 70% → few >70%。
- **LLM 四大局限**：**幻觉 Hallucination**（自信地编造）、**知识过时**（训练截止日期 cut-off）、**推理受限**（多步逻辑弱）、**继承偏见**（放大训练数据偏见）。
- **优化精度的六步流程**（OpenAI 官方）：prompt → few-shot → **RAG** → fine-tuning → RAG + 事实核查 → 重训。
- **Prompt 四要素**：**Instruction**（任务）、**Context**（背景）、**Input Data**（输入）、**Output Indicator**（期望格式）。
- **Prompt engineering 实践**：简洁具体；给**格式匹配**的示例；指定输出结构；迭代改进；了解模型局限；用最新模型；用模板。
- **高级提示技巧**：
  | 技巧 | 要点 |
  |---|---|
  | **CoT 思维链** | 给中间推理步骤，提升复杂推理（>100B 参数涌现） |
  | **Zero-shot CoT** | 加一句 "Let's think step by step" |
  | **Self-consistency** | 高温采样多条推理路径，选**最一致**的答案 |
  | **ToT 思维树** | 在 CoT 上探索多条"思想"分支 |
  | **ReAct** | 推理（Thought）+ 行动（调用工具/查询数据库）+ 观察，交替进行 |
- **安全攻击**：
  - **Prompt injection（提示注入）**：把恶意指令藏进输入——**直接**（用户输入框）或**间接**（外部网页/文档）；
  - **Jailbreaking（越狱）**：绕过内置安全护栏（如 DAN "Do Anything Now" 角色扮演）；
  - 防御：输入输出校验、最小权限、人工审批高风险动作、持续监控与红队测试、RLHF 训练识别恶意提示、安全意识教育。

## W4 · AI Safety & Ethical Considerations ⭐

- **AI 里程碑**：AlexNet（2012 深度学习爆发）→ AlphaGo 4:1 胜李世石（2016）→ Transformer（2017）→ GPT（2018）→ AlphaFold（2018，2024 获诺贝尔化学奖）→ GPT-3 上下文学习（2020）→ ChatGPT（2022）→ 文生图爆发（DALL·E 2/SD/Midjourney 2022）→ Sora（2024）。
- **AI Safety**：狭义（Helen Toner）= 保证系统**安全可靠运行**的技术方案；广义 = 跨学科领域，预防事故、滥用与有害后果，含机器伦理、AI 对齐（alignment）、风险监测、制度规范。
- **Bias vs Variance**：Bias = 预测与真值的系统误差；Variance = 对训练数据噪声的敏感性（过拟合）；**bias-variance trade-off** 追求两者都低。
- **黑盒问题 Black-box problem**：复杂模型内部决策难以理解。三概念分层对比（必考）：
  | 概念 | 层面 | 关键问题 |
  |---|---|---|
  | **Transparency 透明度** | 系统级（开发与治理） | 能否看到并理解系统内部在做什么？ |
  | **Interpretability 可解释性** | 模型级（结构与算法） | 能否直接理解模型如何做决策？ |
  | **Explainability 可解释说明** | 用户级（结果与影响） | 能否向人解释为什么做这个决策？ |
- **四类风险**：恶意使用（网络犯罪/虚假信息/武器化）、AI 军备竞赛、组织风险（重速度利润轻安全）、失控 AI（rogue AI）。
- **虚假信息与深度伪造**：hallucination → 被传播即成 misinformation；deepfake 使造假成本极低；**检测跟不上生成** → 转向**溯源 provenance**（水印、C2PA Content Credentials）；EU AI Act 要求披露 AI 生成内容。实践：回答要**基于知识库并引用来源**，找不到就说找不到。
- **MIT AI Risk Database**：1600+ 风险，可查证；两种分类法：**因果分类**（实体 Entity：人/AI；意图 Intent；时间 Timing）+ **域分类**（7 大域 24 子域）。
- **三大失败案例（会归类）**：Amazon 招聘工具（训练数据性别歧视——Discrimination 域）；荷兰 SyRI 福利欺诈检测（法院判违反隐私权，不够透明——Privacy/Transparency）；Air Canada 聊天机器人（乱承诺票价折扣，公司需担责——Misinformation/Accountability）。
- **EU AI Act 风险分级**：① **Unacceptable**（禁止：社会评分、无差别抓取人脸建库等 9 类）② **High**（高风险重义务：教育、就业、关键基础设施、执法司法等）③ **Transparency**（披露：聊天机器人要告知用户、AI 生成内容要标记）④ **Minimal**（无新规，如垃圾邮件过滤）。
- **Responsible AI 五支柱**：Explainability、Fairness、Robustness、Transparency、**Privacy & Security**；Governance 是让五支柱落地的机制而非第六支柱。
- **治理框架**：**NIST AI RMF**（GOVERN 贯穿 / MAP 识别风险 / MEASURE 度量 / MANAGE 处置——三问：会出什么问题、我怎么知道、我怎么办）；**ISO/IEC 42001**（首个 AI 管理体系标准）；**EU HLEG 可信 AI 七要求**（human agency、robustness、privacy、transparency、fairness、societal well-being、accountability）。
- **模型生产者 vs 使用者**：生产者——数据清理、**价值对齐（RLHF/DPO）**、提供 model card；使用者——选型、微调、设计提示模板、**加外部护栏 guardrails**（输入/输出校验，如 Amazon Bedrock 词过滤/内容过滤）。
- **应用评估**：**model cards**（用途/局限文档）、**red teaming**（自己攻击自己）、**OWASP Top 10 for LLM**、AI 事故数据库（incidentdatabase.ai）。
- 行业案例：医疗（诊断辅助）、招聘（全流程保证机制）、教育（自适应学习、评分）。

## W5 · Retrieval-Augmented Generation (RAG) ⭐

- **为什么需要 RAG**：LLM 训练目标是**预测下一个词**，不是核对事实！三个问题：**知识截止日期**（训练数据过时）、**知识范围**（不含私有/内部文档）、**幻觉**（"自信地撒谎"）。
- **RAG 的价值**：注入最新/专有信息 + 给出**引用来源**；避免昂贵重训与复杂提示；应用：医疗、金融、法律、机器人（医疗 fitness 评估：RAG 96% 准确 vs 人类 87%）。
- **两大管线**：**Indexing（离线）**建知识库 + **Generation（在线）**生成回答。
- **Indexing 五步**：加载（多格式多来源：PDF/DOCX/CSV、S3/SQL/GitHub）→ **切块 chunking** → 转换（embedding）→ 索引 → 存储（**向量数据库**，如 FAISS）。
- **Chunking 要点**：
  - 目的：克服 token 上限、只传相关内容提高精度、提高检索效率；
  - **相邻块要重叠（overlap）**保持上下文连续；块长统一、可调；
  - 短块 → 精确 Q&A；长块 → 适合摘要但检索精度下降；
  - 结构感知切分（Markdown 按标题、代码按函数、HTML 按段落）；
  - 语义切分（按 embedding 相似度合并句子组）；策略可混合。
- **Embeddings**：把数据变成 n 维向量，语义相近 → 向量相近（"King − Man + Woman = Queen"）。
- **Generation 三组件**：**Retriever**（检索）→ **Augmenter**（把检索结果拼进 prompt）→ **Generator**（LLM 生成）。
- **检索算法**：
  - **BM25**（稀疏/关键词检索）：基于词频 tf 与逆文档频率 IDF，**对文档长度归一化**，多词查询逐词求和；快，常用于初筛；
  - **余弦相似度**（稠密/语义检索）：$cos = \frac{u^T v}{\|u\|\|v\|}$；捕捉语义，但计算量大。
  - 实用流程：先 BM25/embedding 宽召回 top 20–50 → 贵模型**重排 rerank** → 取 **top-k（3–5）**给 LLM；k 太小漏证据、太大引入噪声。
- **Augmentation 提示策略**：**contextual prompting**（指令聚焦给定上下文，通用查询）；**controlled generation**（没有信息就说 "I don't know"，降幻觉）；**CoT**（复杂推理任务）。
- **选 LLM 的考量**：开源/闭源（隐私）、API 成本 vs 本地算力、推理速度/延迟、安全与对齐、领域适应（微调）、推理能力。
- **评估四类失败**：response failure（答案没错但没回答问题）、retrieval failure（证据没检索到）、knowledgebase quality（库里信息本身错/旧）、generation failure（检索对了但 LLM 无视/歪曲/编造）。
- **四项评估能力**：noise robustness（抗噪声文档）、**negative rejection**（库里没答案时拒绝回答）、information integration（整合多文档）、counterfactual robustness（能拒绝库里已知错误的说法）。
- 局限：**延迟**（索引 + 在线检索生成都额外耗时）。

## W6 · Agentic AI ⭐

- **定义**：Agentic AI 系统能**追求目标**，在**环境**中**选择并执行动作**，同时**基于记忆与反馈反思**以决定下一步。要素：Goal、Decisions、Actions、Environment、Feedback、Reflection。
- **演进路线（会排序/会举例）**：
  1. **NASA Remote Agent**（1999 航天器自主控制）：Planner + Executive + Diagnostic；反应式、硬编码，无高层决策；
  2. **强化学习（AlphaGo）**：监督学习 + 自我对弈 + MCTS；局限在窄域、训练久；
  3. **Pure LLM**：只问答，无实时数据接地；
  4. **CoT**：静态推理，不接地、会幻觉与错误传播；
  5. **MCP（Model Context Protocol）**：标准化**工具连接**接口（GitHub、文件系统、终端……）；
  6. **Computer use**：直接操作 GUI（点击、键盘）；
  7. **ReAct**：**Thought → Action → Observation** 循环，推理与行动交错；few-shot 提示即可触发；$h_t=(g,o_0,r_0,a_0,o_1,…)$ 历史驱动下一轮；
  8. **AutoGPT**：外层规划循环拆子任务、监督目标；缺陷——幻觉、死循环、分心、记忆弱；
  9. **记忆与反思（Generative Agents / Smallville）**：长期记忆打分 $\text{score}(m)=\alpha\,\text{recency}+\beta\,\text{importance}+\gamma\,\text{relevance}$；涌现社会行为（自发组织派对）；
  10. **多智能体协作（AutoGen）**：专业化 agent 对话分工；人类也可作为 agent 参与；⚠️ **相互认同不等于正确**（可互相强化错误）。
- **LLM 适合当 agent 大脑的四个特质**：自主性 autonomy、反应性 reactivity、主动性 pro-activeness、社交能力 social ability。
- **Agent 评估**：不能只看端到端成功率，要**逐组件**评估——规划/多步推理（能否拆解、跟踪状态、纠错）、工具使用（何时用、选对没、参数对不对）、端到端成功、安全/鲁棒性、效率（时间/token 成本）。
- **五类风险与对策（必考，会配对）**：
  | 风险 | 例子 | 对策 |
  |---|---|---|
  | Action 行动错误 | 说错价格后真的买下不可退机票 | **最小权限**、可信工具、执行前检查、日志 |
  | Goal/constraint 目标欠约束 | "尽快到罗马"→ 买头等舱 | 显式约束、搜索≠购买、高风险需人工批准 |
  | Perception 感知（注入） | 酒店网页藏恶意指令 | **数据与指令分离** |
  | Brain 幻觉/错位 | 记错会议日期导致订错航班 | 显式约束检查、事实交叉验证、human-in/on-the-loop |
  | Memory 记忆投毒 | 长期记忆被篡改"喜欢头等舱" | 记忆可信管理 |

## W8 · AI Applications: Voice, Speech & Creativity

- **AI 应用五段式解剖**：User & Task → Input（语音/文字/图像/视频）→ AI Capability（识别/理解/生成/决策）→ Output/Action → **Human Feedback**（接受/编辑/纠正/拒绝）。AI 只是应用的一部分。
- **以人为本起点**：先搞清 **User（谁用）/ Task（做什么）/ Context（何时何地用）**；找 pain points（延迟、重复劳动、错误、不确定、可访问性障碍）；方法：访谈、观察、问卷、任务分析；框架 **ISO 9241-210**。**从用户需求出发，而不是从"要用 AI"出发**。
- **HCD 四步循环**：Understand context → Specify needs → Design solution → Evaluate with users（用户全程参与，循环迭代）。
- **语音对话系统五模块（必考）**：
  | 模块 | 功能 | 例子 |
  |---|---|---|
  | **ASR** 自动语音识别 | 语音 → 文字 | Google Live Transcribe |
  | **NLU** 自然语言理解 | 文字 → 意图（intent）与槽位（slot） | Amazon Alexa |
  | **DM** 对话管理 | 决定下一步回应/动作 | Vapi、Retell |
  | **NLG** 自然语言生成 | 生成回复 | Duolingo Lily |
  | **TTS** 语音合成 | 文字 → 语音 | Speechify、ElevenLabs |
  > 现代端到端系统会合并/模糊模块；研究系统还可加视觉建议（Visual Captions）、情境感知（AROMA）。
- **语音 AI 的 HCI 价值**：可及性与独立性（Live Transcribe/AROMA）、降低心智负担（StepWrite）、灵活交互（Alexa）、学习与练习（Duolingo/Speechify）。
- **创意 AI 四阶段**（Chompunuch & Lubart，2025）：
  1. **Problem identification & framing**（**人主导**，AI 帮不上核心）
  2. **Generating ideas**（Suno 音乐、Midjourney/Firefly 图像、Canva 设计、CreativeConnect 重组参考）
  3. **Evaluating ideas**（PromptMagician 比较图像）
  4. **Implementing**（Runway/CapCut 视频、Firefly 精修）
  > GenAI 是"**助手**"：辅助人类创造力，不替代人类判断。
- **创意 AI 的 HCI 价值**：降低技能门槛、拓宽探索、判断与掌控、创意表达。
- **会出错的地方**：语音误识别（噪声/口音/术语）、误解意图、错误动作；创意不符简报、风格不一致、原创性/偏见/版权问题。→ 好设计应**让错误可见、给用户回应手段**。
- **生成式 AI 体验六原则**（Weisz et al., CHI 2024）：design responsibly、mental models、appropriate trust、generative variability、co-creation、imperfection。
- **人机协作四模式**（Hu et al., 2025）：**AI supports**（人拍板）/ **AI acts if clear**（低风险自动处理）/ **AI asks for input**（先问清）/ **decide together**（来回协作）。
- **发布前四问**：数据与同意（收集什么、存多久）、权利与溯源（素材权限）、透明度（是否告知 AI 生成）、问责（谁审谁批谁负责）。

## W9 · Human-Centred Design with AI ⭐

- **双钻模型 Double Diamond**：**Discover → Define → Develop → Deliver**（发散-收敛-发散-收敛；可回溯到早期阶段）。
  | 阶段 | 目的 | 方法 | 产出 |
  |---|---|---|---|
  | Discover | 理解用户与情境 | 观察、访谈、问卷 | 用户与情境证据 |
  | Define | 聚焦问题 | 编码、亲和图、需求分析 | 聚焦的问题与设计需求 |
  | Develop | 探索方案 | 头脑风暴、草图、原型 | 备选方案与选定设计 |
  | Deliver | 测试改进 | 可用性测试、实验、问卷 | 评估证据与修订 |
- **访谈三类型**：structured（固定问题顺序，易比较）/ **semi-structured**（主题+追问，深度与灵活）/ unstructured（开放探索）；**个体访谈**（深挖个人经历、私密话题）vs **焦点小组**（互相激发、看分歧）。
- **界面设计原则**（Nielsen）：**recognition**（展示选项而非让人回忆）、visible status（显示状态）、user control（可查看/接受/驳回/修改）、error recovery（可纠错）。
- **Formative（形成性）vs Summative（总结性）评估**：前者找问题改进设计（纸原型走查），后者评估是否达标（最终表现对比）。
- **Utility vs Usability**：Utility = 功能是否满足需求；Usability = 功能是否好用。两者都要。
- **Nielsen 可用性五要素 + 证据**：learnability（首次任务成功率）、efficiency（任务时间）、memorability（间隔后回访）、errors（错误频率/严重度/可恢复性）、satisfaction（问卷评分）。
- **ISO 9241-11**（另一套，分开记）：effectiveness（准确完整达成目标）、efficiency（资源消耗）、satisfaction（满意度）。
- **问卷工具**：**SUS**（10 项 5 点，总分 **0–100 的综合量表分**，非百分比，不给五个独立分）；**PU/PEOU**（Davis，各 6 项：感知有用性/感知易用性）；**USE**（30 项四类）；**改编问卷要说明改编与解释**（如 VisTellAR 把 USE 改成 10 项 5 点）。
- **实验设计**：**within-subjects**（同一批人体验所有条件——需防学习/疲劳/**carry-over 效应**，用**平衡顺序 counterbalancing**）/ **between-subjects**（不同组不同条件——避免 carry-over 但组间个体差异）。
- **案例**：**InterLink**（12 人、within-subjects、平衡顺序；正确率 **92% vs 81%（显著 p<.05）**，时间 122 s vs 128 s（**不显著**）→ 正确率证据更强；SUS 76.5）；**VisTellAR**（10 人 formative → 4 条需求 → 设计 → 12 人两天研究）。
- **AI 贯穿双钻**（人始终负责证据与决策）：Discover—InsightBridge（访谈信息抽取+可视化核对）；Define—CollabCoder（编码建议）；Develop—AIdeation（概念探索）；Deliver—UXAgent（评估准备与演练）。

---

## 备考清单 Checklist

- [ ] W1：AI 四类（GenAI/AGI/ASI/Traditional）、五阶段演进、五特征、生命周期、token
- [ ] W2：三架构（Encoder/Decoder/Enc-Dec + 代表模型）、流水线组件、logits/softmax、**temperature/top-k/top-p/beam**、GPT-3 数字
- [ ] W3：涌现、zero/one/few-shot、四大局限、prompt 四要素、CoT/zero-shot CoT/self-consistency/ToT/ReAct、**injection vs jailbreak**、防御
- [ ] W4：里程碑时间线、bias/variance、黑盒三概念分层、三大失败案例归类、**EU AI Act 四级**、五支柱、NIST RMF 四功能、guardrails、model card/red teaming
- [ ] W5：RAG 动机、**Indexing 五步**、chunking 原则、BM25 vs 余弦相似度、rerank+top-k、四类失败、四项评估能力
- [ ] W6：agent 定义、十步演进、ReAct 循环、记忆打分公式、多智能体优缺点、**五类风险与对策**
- [ ] W8：应用五段解剖、语音五模块（ASR/NLU/DM/NLG/TTS + 例子）、创意四阶段（人主导 framing）、六原则、协作四模式
- [ ] W9：**双钻四阶段 + 方法与产出**、utility vs usability、Nielsen 五要素 vs ISO 三要素、SUS 特性、within/between、carry-over、InterLink 数字
- [ ] **Part 2 写作**：What/So What/Now What 框架、素材准备（见模拟卷模板）

---

# 附录 · 术语表 Glossary（Lecture + Tutorial 汇总）

> 来源：Week 1–9 讲义 + Week 1/3/5/8 Tutorial 词汇任务。标注 ★ 的为 Tutorial 原词（考试词汇重点）。
> 格式：**术语** ｜ 中文 ｜ 英文解释（English definition）

## G1 · Week 1 AI 基础（含 Tutorial Week 1 九词 ★）

| 术语 Term | 中文 | English Definition |
|---|---|---|
| ★ Artificial Intelligence (AI) | 人工智能 | the simulation of human intelligence processes by machines, particularly computer systems |
| ★ Machine Learning (ML) | 机器学习 | a subset of AI focused on developing algorithms that enable computers to learn from and make predictions based on data |
| ★ Deep Learning (DL) | 深度学习 | an advanced subset of ML using artificial neural networks to analyse complex patterns in large datasets |
| ★ Reinforcement Learning | 强化学习 | a type of learning where an agent makes decisions based on feedback from interactions with an environment, aiming to maximize rewards |
| ★ Neural Network | 神经网络 | a computing system inspired by the human brain, made up of interconnected nodes (neurons) that process information and learn patterns from data |
| ★ Generative AI (GenAI) | 生成式人工智能 | a class of AI models designed to generate new content based on existing data |
| ★ Discriminative Model | 判别式模型 | a model trained to classify or label existing data rather than generate new data |
| ★ Prompting | 提示（技巧） | a technique in generative AI where users provide natural language instructions to guide the output generation |
| ★ Natural Language | 自然语言 | the language humans use for everyday communication, as opposed to formal languages used in programming |
| AGI | 通用人工智能 | AI that can perform any intellectual task at a human level (not yet achieved) |
| ASI | 超级人工智能 | AI that surpasses human intelligence in every respect (theoretical) |
| Token | 词元 | a basic unit of text processed by LLMs (a word or sub-word piece) |
| Hallucination | 幻觉 | a model producing fluent but incorrect or fabricated information |
| Model drift | 模型漂移 | the decline of a model's accuracy as the real world changes over time |
| Foundation model | 基础模型 | a large pre-trained model that can be adapted to many downstream tasks |

## G2 · Week 2 LLM 术语

| 术语 Term | 中文 | English Definition |
|---|---|---|
| LLM | 大语言模型 | a very large deep learning model pre-trained on vast amounts of text |
| Transformer | 变换器架构 | the 2017 neural architecture based on self-attention that underlies nearly all modern LLMs |
| Self-attention | 自注意力 | a mechanism that identifies and analyses relationships between elements in an input sequence |
| Multi-head attention | 多头注意力 | multiple attention heads running in parallel, each with its own Q/K/V weight matrices |
| Embedding | 嵌入（向量） | a numerical (vector) representation of a real-world object that AI systems use to understand complex knowledge domains |
| Logits | 逻辑值 | the raw, unnormalized output values of a model before any probability transformation |
| Softmax | 归一化指数函数 | a function that converts logits into probabilities that sum to 1 |
| Temperature | 温度 | a sampling constant that adjusts logits before softmax; lower values give more deterministic output |
| Top-k sampling | Top-k 采样 | sampling only from the k highest-probability tokens |
| Top-p (nucleus) sampling | Top-p（核）采样 | sampling from the smallest set of tokens whose cumulative probability exceeds p |
| Beam search | 束搜索 | keeping several candidate sequences in parallel to trade accuracy against computational cost |
| Autoregressive | 自回归 | generating text one token at a time, each token conditioned on all previous tokens |
| Masked Language Modeling (MLM) | 掩码语言建模 | a training objective that predicts masked words (used by Encoder models such as BERT) |
| Fine-tuning | 微调 | further training a pre-trained model on a smaller, domain-specific dataset |
| Vocabulary | 词表 | the set of tokens a model can produce |
| Context window | 上下文窗口 | the maximum amount of information that can fit in a single prompt |

## G3 · Week 3 提示工程与批判性审视（含 Tutorial Week 3 十词 ★）

| 术语 Term | 中文 | English Definition |
|---|---|---|
| ★ prompt | 提示词 | an instruction or question given to an AI system |
| ★ generate | 生成 | to produce or create something |
| ★ refine | 改进 | to make something better by changing small parts |
| ★ source | 来源 | information, a text, video, report, or website used as evidence |
| ★ verify | 核实 | to check whether something is accurate or reliable |
| ★ bias | 偏见 | an unfair preference for or against a person, group, or idea |
| ★ evidence | 证据 | facts, examples, statistics, or sources used to support a claim |
| ★ claim | 断言 | a statement that may or may not be fully supported by evidence |
| ★ tone | 语气 | the style or feeling of language, such as formal or friendly |
| ★ iteration | 迭代 | repeating a process in order to improve the result |
| Fact | 事实 | something that can be checked as true or false |
| Opinion | 观点 | a belief, judgement, or interpretation |
| Ethical risk | 伦理风险 | a possible harm or problem for people or society |
| Chain-of-Thought (CoT) | 思维链 | prompting that provides intermediate reasoning steps to improve complex reasoning |
| Emergent ability | 涌现能力 | a capability absent in small models but appearing unexpectedly as models scale up |
| In-context learning | 上下文学习 | learning a new task from examples given in the prompt, without updating model parameters |
| Zero/one/few-shot | 零/单/少样本 | prompting with no / one / a few examples of the task |
| Self-consistency | 自洽性 | generating diverse reasoning paths and selecting the most consistent answer |
| Tree of Thoughts (ToT) | 思维树 | a framework exploring multiple branches of intermediate "thoughts" |
| ReAct | 推理-行动框架 | a technique combining reasoning (thought) and acting (tool calls) with observations |
| Prompt injection | 提示注入 | an attack inserting malicious instructions into a prompt to override a model's intended behaviour |
| Jailbreaking | 越狱 | a technique to remove or bypass an AI system's built-in safeguards |
| System prompt | 系统提示 | a set of instructions given to an LLM before any user input to guide its behaviour |

## G4 · Week 4 安全与伦理

| 术语 Term | 中文 | English Definition |
|---|---|---|
| AI Safety | 人工智能安全 | an interdisciplinary field concerned with preventing accidents, misuse, or other harmful consequences of AI systems |
| AI alignment | 人工智能对齐 | technical work aiming to make AI systems moral and beneficial |
| Bias | 偏差 | the systematic error between predicted values and the true values |
| Variance | 方差 | a model's sensitivity to noise in the training data, often leading to overfitting |
| Black-box problem | 黑盒问题 | the difficulty or impossibility for humans to understand a complex model's internal decision-making |
| Transparency | 透明度 | the openness and accessibility of information about a system (system level) |
| Interpretability | 可解释性 | how directly a model's internal mechanisms can be understood (model level) |
| Explainability | 可解释说明 | how well a model's behaviour can be described or justified to humans (user level) |
| Misinformation | 虚假信息 | false information that spreads when a hallucinated output is repeated |
| Deepfake | 深度伪造 | synthetic image, audio or video content that fabricates evidence |
| Provenance | 溯源 | establishing where content came from (e.g. watermarking, C2PA Content Credentials) |
| Guardrail | 护栏 | a safety layer that validates inputs and outputs (e.g. word filters, content filters) |
| Model card | 模型卡 | a short document stating a model's intended use, out-of-scope use, evaluation data and known limitations |
| Red teaming | 红队测试 | deliberately attacking one's own application to find vulnerabilities before release |
| RLHF | 基于人类反馈的强化学习 | Reinforcement Learning from Human Feedback — training that aligns a model with human values |
| Data poisoning | 数据投毒 | intentionally introducing malicious or biased data into training to distort model outputs |
| Risk-based approach | 基于风险的方法 | regulating AI systems according to their risk level (as in the EU AI Act) |
| Accountability | 问责 | clarity about who reviews, approves, and takes responsibility for AI outcomes |

## G5 · Week 5 RAG（含 Tutorial Week 5 十二词 ★，带音标）

| 术语 Term | 中文 | English Definition |
|---|---|---|
| ★ Retrieval /rɪˈtriːvəl/ | 检索 | the act of accessing information previously encoded and stored in memory |
| ★ Augmented /ɔːɡˈmentɪd/ | 增强的 | enhanced or improved by adding something |
| ★ Latency /ˈleɪ.tən.si/ | 延迟 | the delay between a request and the corresponding response |
| ★ Accuracy /ˈækjərəsi/ | 准确度 | how close a measurement is to the true value |
| ★ Synthesis /ˈsɪnθəsɪs/ | 综合 | the combination of ideas or elements to form a new, more complex theory or system |
| ★ Relevance /ˈreləvəns/ | 相关性 | how closely connected something is to the topic |
| ★ Contextual /kənˈtekstʃuəl/ | 与上下文相关的 | depending on or relating to the circumstances or setting surrounding a piece of information |
| ★ Semantic /sɪˈmæntɪk/ | 语义的 | having to do with the meaning of words or language |
| ★ Query /ˈkwɪəri/ | 查询 | a question or request (to ask a question) |
| ★ Vector /ˈvektə/ | 向量 | a list of numbers representing data in a multi-dimensional space |
| ★ Chunking /ˈtʃʌŋkɪŋ/ | 分块 | breaking down large pieces of data into smaller, more manageable units |
| ★ Ethical /ˈeθɪkəl/ | 伦理的 | having to do with morals, values, right and wrong |
| RAG | 检索增强生成 | Retrieval-Augmented Generation — a method that enhances LLM accuracy by retrieving relevant external information and integrating it into generation |
| Knowledge base | 知识库 | the indexed corpus of documents that RAG retrieves from |
| BM25 | BM25 算法 | a sparse keyword-retrieval scoring function based on term frequency and inverse document frequency, adjusted for document length |
| Cosine similarity | 余弦相似度 | a measure of alignment between vectors used for semantic retrieval |
| Reranker | 重排器 | a (usually more expensive) model that re-scores retrieved candidates for precision |
| Negative rejection | 负向拒绝 | the ability to refuse to answer when the knowledge base contains no relevant information |
| Noise robustness | 抗噪声性 | the ability to separate noisy, irrelevant documents from relevant ones |
| Information integration | 信息整合 | the ability to assimilate information from multiple documents |
| Counterfactual robustness | 反事实鲁棒性 | the ability to reject known inaccuracies in retrieved information |
| Retrieval failure / Generation failure | 检索失败 / 生成失败 | the evidence was not retrieved / the evidence was retrieved but ignored, distorted or invented by the LLM |

## G6 · Week 6 Agentic AI

| 术语 Term | 中文 | English Definition |
|---|---|---|
| Agentic AI | 智能体式人工智能 | an AI-enabled system that pursues a goal by selecting and taking actions in an environment while reflecting on memory and feedback |
| Agent | 智能体 | (philosophy) an entity that possesses desires, beliefs, intentions, and the ability to act |
| Autonomy | 自主性 | operating without direct human intervention and holding a degree of control over one's actions |
| Reactivity | 反应性 | responding rapidly to immediate changes and stimuli in the environment |
| Pro-activeness | 主动性 | taking the initiative in a goal-oriented way |
| Social ability | 社交能力 | interacting with other agents, including humans, through language |
| Tool use | 工具使用 | calling external tools, APIs or functions to act on the world |
| MCP | 模型上下文协议 | Model Context Protocol — a standardized interface for tool access and use |
| Computer use | 计算机使用 | agents directly interacting with real computer interfaces (clicks, typing) |
| Thought-Action-Observation | 思考-行动-观察 | the ReAct loop of reasoning, acting and observing results |
| Long-term memory | 长期记忆 | memories scored by a combination of recency, importance and relevance |
| Reflection | 反思 | asking the LLM for higher-level insights over stored memories |
| Multi-agent cooperation | 多智能体协作 | specialized agents solving complex tasks through natural-language conversation |
| Least privilege | 最小权限 | granting an agent only the permissions necessary for its task |
| Memory poisoning | 记忆投毒 | contaminating an agent's long-term memory with malicious information |
| Human-in/on-the-loop | 人在回路 | keeping humans able to approve or override high-impact decisions |

## G7 · Week 8 语音与创意 AI

| 术语 Term | 中文 | English Definition |
|---|---|---|
| ASR | 自动语音识别 | Automatic Speech Recognition — converting speech into text |
| NLU | 自然语言理解 | Natural Language Understanding — mapping words to intent and information slots |
| DM | 对话管理 | Dialogue Management — choosing the next response or action |
| NLG | 自然语言生成 | Natural Language Generation — generating spoken or written replies |
| TTS | 语音合成 | Text-to-Speech — converting text into spoken audio |
| Intent | 意图 | the goal behind a user's utterance |
| Slot | 槽位 | a piece of information extracted from an utterance |
| Pain point | 痛点 | delays, repeated work, errors, uncertainty or accessibility barriers in a task |
| Human-centred design | 以人为本设计 | design that starts with users, tasks and context (ISO 9241-210) |
| Creative process | 创意过程 | problem framing → generating ideas → evaluating ideas → implementing ideas |
| Co-creation | 共创 | users steering and editing the AI's output |
| Appropriate trust | 恰当信任 | knowing when users should double-check results |
| Generative variability | 生成多样性 | giving people the ability to explore different answers |
| Mental model | 心智模型 | users' understanding of what an AI can and cannot do |

## G8 · Week 9 人本设计与评估

| 术语 Term | 中文 | English Definition |
|---|---|---|
| Double Diamond | 双钻模型 | a design process of four stages: Discover, Define, Develop, Deliver |
| Affinity mapping | 亲和图法 | grouping coded evidence into themes during analysis |
| Formative evaluation | 形成性评估 | finding problems so the design can improve |
| Summative evaluation | 总结性评估 | assessing how well a design meets its goals |
| Utility | 效用 | whether the functionality meets the user's needs |
| Usability | 可用性 | how easy and pleasant the functions are to use |
| Learnability | 可学习性 | how easy first use is |
| Efficiency | 效率 | how fast use is after learning |
| Memorability | 可记忆性 | how easy it is to return to use after a gap |
| Errors | 错误 | what goes wrong and whether users can recover |
| Satisfaction | 满意度 | how pleasant use is |
| Effectiveness | 有效性 | how accurately and completely users achieve their goals (ISO 9241-11) |
| SUS | 系统可用性量表 | System Usability Scale — a 10-item questionnaire with a composite score from 0 to 100 (a scale score, not a percentage) |
| PU / PEOU | 感知有用性 / 感知易用性 | Perceived Usefulness / Perceived Ease of Use — Davis's six-item scales |
| Within-subjects | 组内设计 | the same participants experience all conditions |
| Between-subjects | 组间设计 | different groups experience different conditions |
| Carry-over effect | 遗留效应 | one condition influencing performance on the next |
| Counterbalancing | 平衡设计 | varying the order of conditions across participants to offset order effects |
| Think-aloud | 出声思考 | participants verbalize their thinking while using an interface |
| Paper prototype | 纸面原型 | a low-fidelity prototype used for early testing |
| Focus group | 焦点小组 | a moderated discussion in which participants respond to one another's experiences |

## G9 · 反思写作高频词（Part 2 写作必用）

| 术语 Term | 中文 | English Definition |
|---|---|---|
| Reflection / reflective writing | 反思写作 | writing that critically evaluates personal experience and connects it to broader themes |
| What? / So What? / Now What? | 三段式反思模型 | a framework describing what happened, analysing its significance, and planning future application |
| Challenge | 挑战 | a difficulty or problem faced during a task |
| Insight | 见解 | a new and deeper understanding gained from experience |
| Takeaway | 收获 | a key lesson carried away from an experience |
| Bridge theory and practice | 连接理论与实践 | connecting abstract concepts to concrete, hands-on work |
| Evidence-based decision | 基于证据的决策 | a decision supported by observations, tests or data rather than intuition |
