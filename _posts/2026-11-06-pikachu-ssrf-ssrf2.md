# Pikachu | SSRF 2
## 一、漏洞简介
SSRF，简单过滤，可使用一些协议、域名解析绕过限制访问内网资源。
## 二、环境信息
靶场地址：http://127.0.0.1/pikachu/
关卡路径：/vul/ssrf/ssrf2.php
## 三、复现步骤
1. 尝试http协议访问内网，被过滤时可以尝试其他协议
2. file://读取本地文件：`file:///etc/passwd`（Linux） `file:///C:/Windows/win.ini`（Windows）
## 四、Payload
`file:///etc/passwd`
## 五、漏洞原理
只简单过滤http，没有禁用其他协议，导致可以读取本地文件。
## 六、修复方案
禁止非必要协议（file://、gopher://、dict://），内网地址黑名单。
## 七、总结
SSRF不只是http，多种协议会拓展攻击面。