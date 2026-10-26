## 题目信息
- 平台：CTFHub
- 题目：Stash
- 分类：Web - Git源码泄露
- 靶机地址：http://challenge-22c02d0a5b4278cb.sandbox.ctfhub.com:10808
- 页面回显：Where is flag?

## 考点
Git源码泄露、git stash暂存恢复

## 解题思路
开发人员写好flag后，没有commit提交，使用git stash将改动暂存，之后删除页面上的flag。上线未删除.git目录，造成Git仓库泄露。
本题flag不在commit提交记录中，需要读取stash暂存内容。

## 复现步骤
1. 访问主页，页面仅输出 Where is flag?，源码无flag。
2. 拼接.git路径：http://challenge-22c02d0a5b4278cb.sandbox.ctfhub.com:10808/.git/
3. 使用git-dumper下载Git仓库：
```bash
git-dumper http://challenge-22c02d0a5b4278cb.sandbox.ctfhub.com:10808/.git/ ./stashtest
4. 进入仓库目录，查看暂存列表：
bash
cd stashtest
git stash list
5. 查看暂存详情，获取flag：
bash
git stash show -p stash@{0}
6. 得到flag：
ctfhub{f19911a281bd16f8cea7145b}
漏洞原理

.git目录存放版本信息与stash暂存堆栈，stash用于临时保存未提交的代码变更。上线时未清理.git目录，导致敏感内容被获取。

修复建议

1. 上线前删除.git版本控制目录；

2. Web服务器配置规则，拦截访问/.git/；

3. 上线前清空本地stash缓存。