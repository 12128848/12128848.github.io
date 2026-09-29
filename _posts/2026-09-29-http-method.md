---
title: HTTP Method 请求方式
date: 2026-09-29
categories: CTF
tags: Web HTTP
---

## 题目描述
HTTP请求方法，页面提示需要使用`CTF**B`的请求方法获取flag，星号隐藏部分字符。

## 解题思路
HTTP协议支持自定义请求方法，不限于GET、POST。
题目星号遮挡，真实请求方法为 **CTFHUB**。

## 解题步骤
1. 打开靶场环境，浏览器默认GET访问，无法拿到flag
2. 使用curl工具，`-X` 指定自定义请求方法 CTFHUB
```bash
curl -X CTFHUB  challenge-a47306bd48980b66.sandbox.ctfhub.com:10800/index.php