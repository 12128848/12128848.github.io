---
layout: post
title: "Bugku POST Writeup"
date: 2026-09-14 00:00:00 +0800
tags: [CTF,WEB,Bugku]
---

## 一、题目信息
题目名称：POST
题型：WEB
> Bugku在线靶机为临时环境，重启环境后访问IP会变化，闲置超时会自动关闭。

## 二、解题思路
访问题目页面，页面展示一段PHP源码。代码使用`$_POST['what']`接收POST请求提交的参数what，当参数值等于`flag`时，页面输出flag。GET方式URL传参无效，需要构造POST请求提交数据。
考点：**POST请求传参、PHP代码审计、HTTP请求方法区分**。

## 三、解题过程
1. 在Bugku平台启动靶机环境，访问靶机地址，页面展示PHP源码。
2. 审计代码，发现需要使用POST方法提交参数`what=flag`，GET传参无法触发判断。
3. 使用curl命令构造POST请求，提交参数。
4. 执行命令，页面返回响应内容，获取flag。

## 四、EXP
curl命令：
```bash
curl -X POST -d "what=flag" http://160.202.254.160:14650