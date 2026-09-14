---
layout: post
title: "Bugku source Writeup"
date: 2026-09-14 00:00:00 +0800
tags: [CTF,WEB,Bugku]
---

## 一、题目信息
题目名称：source
题型：WEB
> Bugku在线靶机为临时环境，重启环境后IP会变化，超时会关闭。

## 二、解题思路
访问题目页面，页面只显示两行文字。Ctrl+U查看网页源代码，HTML注释中存在一段Base64字符串，解码后得到假flag；注释中的`tig`是`git`反转，提示存在.git源码泄露。网站git仓库可被下载，git会保存所有历史提交版本，开发者曾经写过flag的文件虽然现在删除了，但还保存在旧提交记录中，可以找回真实flag。
考点：**网页源码查看、git源码泄露、git reflog历史版本查看、Base64陷阱**。

## 三、解题过程
1. 在Bugku平台启动靶机，访问页面，页面输出Hello,world! This is my friend :。
2. 使用Ctrl+U查看网页源代码，注释内找到Base64字符串`ZmxhZ19ub3RfaGvyZSEHIQ==`，解码得到假flag，意识到是陷阱。
3. 根据`tig`提示，访问`/.git/HEAD`确认存在git源码泄露。
4. 使用git-dumper工具下载网站.git仓库到本地文件夹。
5. 在仓库目录执行`git reflog`查看所有历史提交记录。
6. 使用`git show 40c6d51`查看旧提交内容，获取被删除的真实flag。

## 四、EXP
下载git仓库：
```bash
python git_dumper.py http://160.202.254.160:10808/.git/ source_folder