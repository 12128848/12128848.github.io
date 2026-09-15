---
layout: post
title: "Bugku 入门逆向 Writeup"
date: 2026-09-15 00:00:00 +0800
tags: [CTF,Reverse,Bugku,IDA]
---

## 题目信息
题目：入门逆向
类型：Reverse逆向工程
来源：XJNU
附件：Windows可执行程序exe

## 解题思路
基础逆向入门题，flag直接硬编码在程序栈中，没有做加密处理。使用IDA32位加载程序，查看main函数汇编代码，mov指令依次把flag每个字节存入栈，提取字符拼接即可。

## 解题步骤
1. 下载题目附件exe文件。
2. 使用IDA Pro 32位打开程序，进入main函数。
3. 观察汇编代码，连续mov指令向栈写入flag的每个ASCII字符。
4. 按顺序提取字符，拼接得到flag。
5. flag：`flag{Re_1s_S0_C0OL}`

## 知识点总结
- 硬编码：数据直接写在程序二进制内，逆向可以直接读取。
- IDA：逆向常用静态反汇编工具。
- mov指令：汇编中用于数据传递。