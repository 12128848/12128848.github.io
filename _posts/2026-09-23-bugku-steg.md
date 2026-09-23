---
title: Bugku CTF | MISC 隐写
date: 2026-09-23 15:33:00 +0800
categories: [CTF, MISC]
tags: [Bugku, 图片隐写, strings命令]
---

# Bugku MISC：隐写
> 题目来源：Bugku CTF
> 考点：图片隐写，使用strings读取文件内隐藏字符串

## 题目描述
下载附件图片，找到隐藏在图片中的flag。

## 解题思路
这是基础图片隐写题，flag直接藏在图片文件末尾字符串中，不需要复杂工具，使用strings命令读取文件字符串即可找到flag。

### 详细步骤
1. 点击下载，获取图片附件。
2. 使用 `strings 图片名.jpg` 命令查看图片内所有文本字符串。
3. 在输出内容末尾找到 `BUGKU{xxxxxxxx}` 格式flag。
4. 复制flag提交。

## Flag
`BUGKU{Imag3_St3g4n0graphy}`

## 知识点总结
strings命令：可以提取二进制文件中所有可打印字符。很多简单MISC隐写会直接把文字追加在图片文件尾部，用strings快速读取，是MISC入门常用手段。