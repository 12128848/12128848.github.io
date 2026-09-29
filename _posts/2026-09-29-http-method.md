---
title: HTTP Method
date: 2026-09-29
categories: CTF
tags: Web HTTP
---

## 题目描述
页面提示当前请求为GET，需要使用指定的CTFB请求方法获取flag。

## 解题思路
修改HTTP请求方法为`CTFB`发送请求。

## 解题步骤
1. 访问环境地址，页面提示HTTP Method is GET
2. 使用HackBar/Burp Suite，将请求方法修改为 `CTFB`
3. 发送请求，页面返回flag

## Flag

## 总结
HTTP请求方法可以自定义，不只有GET、POST。