---
title: Bugku 归档
date: 2026-09-24 23:16:00 +0800
categories: [Bugku, Crypto]
tags: [python, md5, 单字符哈希]
---

# 归档
## 题目信息
平台：Bugku CTF
类型：Crypto
考点：Python脚本分析，单字符MD5哈希逆向

## 解题思路
解压附件得到 flag.py 和 output。
阅读flag.py源码可知：程序读取flag字符串，**对flag里每一个单独字符分别计算MD5值**，按顺序写入output文件，一行一个md5。
解题思路：读取output中的每一条md5，遍历所有可打印字符，比对md5，还原出原始字符，拼接得到完整flag。

## 解题步骤
1. 解压归档.zip，得到flag.py与output文件。
2. 分析Python源码，理解加密逻辑：逐字符md5。
3. 编写解密脚本，遍历字符，匹配每一行md5。
4. 运行脚本，拼接字符得到flag。

## 解密EXP
```python
import hashlib

def get_char(hash_str):
    # 可打印字符范围
    for c in '0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ{}_':
        if hashlib.md5(c.encode()).hexdigest() == hash_str.strip():
            return c
    return ""

with open("output","r",encoding="utf-8") as f:
    lines = f.readlines()

res = ""
for line in lines:
    ch = get_char(line)
    res += ch
print(res)