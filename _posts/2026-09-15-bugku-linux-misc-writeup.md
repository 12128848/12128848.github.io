---
layout: post
title: "Bugku linux MISC Writeup"
date: 2026-09-15
categories: CTF
tags: [Bugku,MISC,Linux]
---

## 题目信息
题目：linux
类型：MISC杂项
描述：linux基础问题
提示：key{}
附件：1.tar.gz

## 解题思路
下载得到tar.gz压缩包，解压后得到flag二进制文件。文件中包含大量二进制乱码，明文key藏在文件中。可以使用Linux下strings/grep命令提取字符串；Windows下可用Notepad++打开文件，搜索key关键字定位flag。

## 解题步骤
1. 下载附件1.tar.gz。
2. Linux环境使用 `tar -zxvf 1.tar.gz` 解压。
3. 使用 `strings flag | grep key` 提取包含key的字符串。
4. 得到flag：`key{feb81d3834e2423c9903f4755464060b}`

## 知识点总结
- tar命令：`-zxvf` 解压tar.gz压缩包
- strings：提取二进制文件内可读字符串
- grep：文本关键词过滤查找