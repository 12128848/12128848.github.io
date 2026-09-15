---
layout: post
title: "Bugku 瑞士军刀 Writeup"
date: 2026-09-15 00:00:00 +0800
tags: [CTF,PWN,Bugku]
---

## 题目信息
题目：瑞士军刀
类型：PWN
靶机连接：`nc 160.202.254.160 15146`

## 解题思路
nc（netcat）被称为Linux瑞士军刀，可以连接远程TCP服务器。
连接远程靶机后，使用Linux基础命令查看文件，读取flag。

## 解题步骤
1. 使用nc连接靶机
```bash
nc 160.202.254.160 15146