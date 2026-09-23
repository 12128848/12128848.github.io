---
title: Bugku CTF | Crypto 把猪困在猪圈里
date: 2026-09-23 14:05:00 +0800
categories: [CTF, Crypto]
tags: [Bugku, Pigpen, 猪圈密码, Base64]
---

# Bugku Crypto：把猪困在猪圈里
> 题目来源：Bugku CTF
> 考点：Base64图片编码 + 猪圈密码(Pigpen密码)

## 题目描述
下载附件，解密得到flag。

## 解题思路
题目名字直接提示**猪圈密码**。下载得到txt文件，里面是图片的base64编码。
将base64解码还原图片，图片上是猪圈密码符号，对照密码表解密得到明文。

### 详细步骤
1. 点击页面【下载】按钮，获取txt文件，复制文件内全部base64字符串。
2. 使用在线base64转图片工具，字符串前面添加 `data:image/jpg;base64,`，解码得到猪圈密码图片。
3. 对照猪圈密码表，识别图中符号，解密得到明文：`thisispigpassword`。
4. 套上`flag{}`格式提交。

## Flag
`flag{thisispigpassword}`

## 知识点总结
猪圈密码（Pigpen）：一种图形替换密码，用方格和线条符号代替英文字母，是CTF入门经典密码。