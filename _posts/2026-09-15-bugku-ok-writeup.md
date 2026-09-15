---
layout: post
title: "Bugku ok Writeup"
date: 2026-09-15 00:00:00 +0800
tags: [CTF,Crypto,Bugku,Ook,Brainfuck]
---

## 题目信息
题目：ok
类型：Crypto密码学
描述：Ook.
附件：下载得到包含Ook指令的文本文件

## 解题思路
题目提示Ook，这是Ook!编程语言，是Brainfuck的变体，只有`Ook.`、`Ook?`、`Ook!`三种符号。将全部Ook文本复制到Ook在线解释器运行，输出flag。

## 解题步骤
1. 下载题目附件，记事本打开，复制全部Ook代码。
2. 打开Ook在线解码网站。
3. 粘贴代码，执行解码。
4. 输出结果：`flag{ok-c2tf-3389-admin}`

## 知识点总结
- Ook!：Brainfuck衍生语言，用Ook组合替代bf符号。
- Brainfuck：极简的8符号编程语言，CTF密码题很常见。