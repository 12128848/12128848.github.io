# Pikachu | 文件包含 本地文件包含 LFI
## 一、漏洞简介
本地文件包含，后端通过文件路径引入文件，路径可控，可以读取服务器本地任意文件。
## 二、环境信息
靶场地址：http://127.0.0.1/pikachu/
关卡路径：/vul/fileinclude/fi_local.php
## 三、复现步骤
1. url参数 filename=file1.php
2. 使用../向上跳目录读取文件：`?filename=../../phpinfo.php`
3. 读取服务器敏感文件，如windows：`../../windows/system32/drivers/etc/hosts`
## 四、Payload
`?filename=../../etc/passwd`（Linux）
## 五、漏洞原理
`include($_GET['filename'])`，用户可控文件路径，没有过滤../目录跳转符。
## 六、修复方案
路径白名单，限制包含目录，过滤../
## 七、总结
本地包含：读取本机文件；远程包含需要allow_url_include开启。