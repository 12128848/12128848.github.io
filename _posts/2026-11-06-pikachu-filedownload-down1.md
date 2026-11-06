# Pikachu | 文件下载漏洞1
## 一、漏洞简介
任意文件下载，下载接口参数可控，可以修改路径下载服务器任意文件。
## 二、环境信息
靶场地址：http://127.0.0.1/pikachu/
关卡路径：/vul/filedownload/down1.php
## 三、复现步骤
1. 正常下载链接 ?filename=test.txt
2. 目录跳转payload：`?filename=../../etc/passwd`（Linux） `?filename=../../windows/system32/drivers/etc/hosts`（Windows）
3. 服务器读取并返回文件内容，实现任意下载
## 四、Payload
`?filename=../../etc/passwd`
## 五、漏洞原理
后端直接拼接filename读取文件，没有过滤../，没有白名单。
## 六、修复方案
文件名白名单，限制下载目录，校验文件路径。
## 七、总结
任意文件下载用来拿服务器敏感配置、密码文件。