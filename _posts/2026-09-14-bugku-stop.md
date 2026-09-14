---
layout: post
title: "Bugku 你必须让他停下 Writeup"
date: 2026-09-14 00:00:00 +0800
tags: [CTF,WEB,Bugku]
---

## 一、题目信息
题目名称：你必须让他停下
题型：WEB
> Bugku在线靶机为临时环境，重启环境后访问IP会变化，闲置超时会自动关闭。

## 二、解题思路
访问题目页面，页面通过 JS 的 `setTimeout` 定时器实现毫秒级自动刷新，页面持续跳转，无法稳定查看源码。服务端每次请求随机返回1~15号图片，仅返回 `10.jpg` 熊猫图片的页面存在 flag。flag 存放于 `display:none` 隐藏标签中，前端页面不可见，但真实存在于网页响应源码内。
考点：**JS自动刷新绕过、HTTP抓包分析、随机页面筛选、隐藏源码读取**。

## 三、解题过程
1. 启动Bugku靶机环境，访问题目地址，页面持续自动刷新，无法肉眼读取有效内容。
2. F12打开开发者工具，进入 Network 网络面板抓包，记录全部网页请求。
3. 过滤静态 jpg 资源，仅保留网页主体源码请求包。
4. 逐一筛查响应内容，定位包含 `10.jpg` 的页面源码。
5. 过滤 `flag is here~` 干扰页面，最终提取隐藏标签内的真实 flag。

## 四、EXP
### 手动解法
无脚本，通过浏览器抓包筛选有效响应源码，绕过自动刷新干扰。

### 自动化脚本解法
```python
import requests
import time

url = "http://160.202.254.160:15093"
while True:
    resp = requests.get(url)
    if "10.jpg" in resp.text:
        print("找到flag！")
        print(resp.text)
        break
    time.sleep(0.8)