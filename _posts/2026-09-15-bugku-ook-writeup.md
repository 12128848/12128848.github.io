---
layout: post
title: "Bugku .!? Crypto Writeup"
date: 2026-09-15
categories: CTF
tags: [Bugku,Crypto,Ook,Brainfuck]
---

## 题目信息
题目：.!?
类型：Crypto密码学
描述：详见附件file.txt
附件内容：大量 Ook! / Ook. / Ook? 符号

## 解题思路
本题是Ook!编码，Ook是Brainfuck语言的变种，使用 Ook. Ook! Ook? 三种符号替换bf指令。使用在线Ook解密工具，粘贴密文一键解密。

## 解题步骤
1. 下载附件 file.txt，复制里面全部密文。
2. 打开Bugku Brainfuck在线工具。
3. 将密文粘贴输入框，选择Ook解密。
4. 解密得到flag：`flag{bugku_jiami}`

## 知识点总结
- Ook!：Brainfuck的趣味变种编码，使用Ook符号代替bf指令。
- Brainfuck：极简的8指令编程语言，CTF常见密码题型。