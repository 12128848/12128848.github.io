---
title: Bugku CTF | Crypto 黄道十二官
date: 2026-09-23 14:07:00 +0800
categories: [CTF, Crypto]
tags: [Bugku, Zodiac, AZdecrypt, 黄道十二宫密码]
---

# Bugku Crypto：黄道十二官
> 题目来源：Bugku CTF
> 考点：黄道十二宫杀手密码(Zodiac密码)，使用AZdecrypt解密

## 题目描述
下载`黄道十二官.jpg`图片，解密得到flag。

## 解题思路
题目名字提示Zodiac（黄道十二宫杀手密码）。下载图片，图片上是Zodiac的特殊符号，使用AZdecrypt工具进行解密。

### 详细步骤
1. 点击下载，拿到`黄道十二官.jpg`图片。
2. 提取图片中的全部符号，将符号输入AZdecrypt解密工具。
3. 工具解密得到明文：`alphananke`。
4. 套上`flag{}`格式提交。

## Flag
`flag{alphananke}`

## 知识点总结
黄道十二宫密码（Zodiac Killer密码）：美国黄道十二宫杀手使用的替换密码，CTF中一般使用AZdecrypt专用工具解密。