---
title: Cookie伪造
date: 2026-09-29
categories: CTF
tags: Web Cookie
---

## 题目描述
页面输出 `hello guest. only admin can get flag.`，提示只有admin管理员才可以获取flag。

## 解题思路
观察响应头`Set‑Cookie: admin=0`，cookie中`admin=0`代表普通访客，把值修改为`admin=1`，伪装管理员身份拿到flag。Cookie由客户端可控，可以直接篡改。

## 解题步骤
1. 浏览器直接访问页面，身份为guest，无法获取flag。
2. 使用curl携带伪造Cookie请求头，设置`admin=1`：
```bash
curl -i -H "Cookie: admin=1" challenge-fe6a0bc88a40558e.sandbox.ctfhub.com:10800
3. 服务器识别为管理员身份，返回flag。

Flag

ctfhub{1c396660f07214168e9da46a}