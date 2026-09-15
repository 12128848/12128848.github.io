---
layout: post
title: "Bugku [+-<>] Brainfuck Writeup"
date: 2026-09-15 00:00:00 +0800
tags: [CTF,Crypto,Bugku,Brainfuck]
---

## 题目信息
题目：[+-<>]
类型：Crypto密码学
描述：一串由`+ - < > [ ] . ,`组成的Brainfuck指令

## 解题思路
题目字符是Brainfuck语言，一共只有8种指令符号。使用在线Brainfuck解释器运行代码，直接输出flag。

## 解题步骤
1. 复制题目描述里全部Brainfuck代码。
2. 打开splitbrain在线Ook/Brainfuck工具。
3. 清空输入框，粘贴密文。
4. 点击 `Brainfuck to Text` 执行解密。
5. 得到flag：`flag{0d86208ac54fbf12}`

## 知识点总结
- Brainfuck：极简的8指令编程语言，常被拿来做CTF密码题。
- 8个指令：`+`、`-`、`<`、`>`、`[`、`]`、`.`、`,`。