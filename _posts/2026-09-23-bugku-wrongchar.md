---
title: Bugku CTF | Crypto 抄错的字符
date: 2026-09-23 15:31:00 +0800
categories: [CTF, Crypto]
tags: [Bugku, 字符替换, 字母数字混淆]
---

# Bugku Crypto：抄错的字符
> 题目来源：Bugku CTF
> 考点：数字字母形近替换（0/O，1/I，5/S等），字符还原

## 题目描述
老师让小明抄写一段话，结果粗心的小明把部分数字抄成了字母，还因为强迫症把所有字母都换成大写。帮小明恢复并解开密码：`QWIHBLGZZXJSXZNV BZW`

## 解题思路
题目提示：数字被抄写成外观相似大写字母。
常见混淆：I=1，O=0，S=5，Z=2。
密文：QWIHBLGZZXJSXZNV BZW
把I替换成数字1，Z替换成数字2，还原后解密得到明文。

### 详细步骤
1. 观察密文 `QWIHBLGZZXJSXZNV BZW`，根据提示，字母I实际是数字1，字母Z实际是数字2。
2. 替换字符：I→1，Z→2，得到 `QW1HBLG22XJSX2NV B2W`。
3. 进行凯撒解密，偏移量17，得到明文 `Aman_very_cool`。
4. 套上flag格式提交。

## Flag
`flag{Aman_very_cool}`

## 知识点总结
形近字符替换：手写抄写时，数字和形状相近大写字母容易弄混，是CTF密码学小题常见套路，常搭配凯撒密码。