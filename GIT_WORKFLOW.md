# 算法竞赛项目 Git 工作流指南

## 简化版 GitHub Flow

这是一个为个人算法竞赛项目优化的简化版 GitHub Flow。

### 核心原则
1. **main 分支**：包含所有完整、正确的解法
2. **功能分支**：每个新题目在独立分支开发
3. **直接合并**：完成题目后直接合并到 main（跳过 PR）
4. **清晰提交**：规范的提交信息记录解题思路

## 工作流程示例

### 1. 开始新题目
```bash
# 创建功能分支（分支名格式：feature/平台-题目）
git new leetcode-two-sum
# 或手动：git checkout -b feature/leetcode-two-sum
```

### 2. 解题并提交
```bash
# 在对应目录创建文件并解题
# leetcode/two_sum.cpp
# codeforces/CF1791A.cpp
# luogu/P1001.cpp

# 添加并提交（使用别名）
git save "add LeetCode two sum solution"

# 或手动提交
git add .
git commit -m "feat: add LeetCode two sum solution"
```

### 3. 完成题目并合并
```bash
# 切换回 main 分支并合并
git done leetcode-two-sum
# 或手动：
# git checkout main
# git merge --no-ff feature/leetcode-two-sum
# git branch -d feature/leetcode-two-sum
```

## Git 别名速查表

### 基本命令
```bash
git st      # 状态
git co      # 切换分支/检出
git br      # 分支管理
git ci      # 提交
git lg      # 图形化日志
```

### 工作流命令
```bash
git new <name>          # 创建功能分支 feature/<name>
git done <name>         # 合并并删除分支 feature/<name>
git save "message"      # 添加所有文件并提交 feat: message
git fix "message"       # 添加所有文件并提交 fix: message
git ref "message"       # 添加所有文件并提交 refactor: message
```

### 查看和清理
```bash
git changes             # 查看更改的文件
git staged              # 查看暂存区的更改
git cleanup             # 清理已合并的分支
```

### 撤销操作
```bash
git unstage             # 取消暂存
git undo                # 撤销上次提交（保留更改）
git redo 1              # 重置到前1个提交（丢弃更改）
```

## 提交信息规范

### 格式
```
<type>: <subject>

<body>
```

### 类型说明
- `feat`: 新算法解法或功能
- `fix`: 修复现有解法中的错误
- `refactor`: 代码重构，不改变功能
- `docs`: 仅文档更改
- `style`: 代码风格更改（格式化等）
- `chore`: 维护任务，构建配置等

### 示例
```
feat: add binary search solution for rotated array

- Implement binary search with O(log n) time complexity
- Handle edge cases: empty array, single element
- Add test cases for rotation scenarios
```

## 分支命名规范

### 功能分支
```
feature/leetcode-two-sum
feature/codeforces-1791A
feature/luogu-P1001
```

### 修复分支
```
bugfix/leetcode-off-by-one
```

## 里程碑标记

标记重要节点（如完成一定数量的题目）：
```bash
git milestone 1.0 "Completed 50 LeetCode problems"
git milestone 2.0 "Added Codeforces contest solutions"
```

## 最佳实践

1. **一题一分支**：每个题目在独立分支开发
2. **及时合并**：完成题目后及时合并到 main
3. **清晰提交**：提交信息说明算法思路和复杂度
4. **定期清理**：使用 `git cleanup` 删除已合并的分支
5. **标签里程碑**：使用标签标记学习进度

## 快速开始模板

```bash
# 1. 开始新题目
git new leetcode-example

# 2. 复制模板
cp templates/template.cpp leetcode/example.cpp

# 3. 解题并提交
git save "add LeetCode example solution"

# 4. 完成
git done leetcode-example