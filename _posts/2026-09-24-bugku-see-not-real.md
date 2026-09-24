---
title: Bugku 眼见非实
date: 2026-09-24 22:58:00 +0800
categories: [Bugku, Misc]
tags: [docx, 文件隐写]
---

# 眼见非实
## 题目信息
平台：Bugku CTF
类型：Misc
考点：docx文件本质是zip压缩包，xml文档隐藏内容

## 解题思路
下载附件，看似是docx文档，无法正常打开。docx底层是zip压缩包，修改后缀为zip解压，进入word目录读取document.xml，搜索flag。

## 解题步骤
1. 将附件后缀docx改为zip，解压。
2. 打开解压目录中的word文件夹。
3. 使用记事本打开 document.xml。
4. Ctrl+F搜索flag字符串，得到flag。

## Flag
flag{F1@g}

## 知识点
docx新版Word文档本质是zip压缩包，里面存放多个xml配置文件，文档文字内容保存在word/document.xml。