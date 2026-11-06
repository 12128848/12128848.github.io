# Pikachu | 其他-phpmyadmin
## 一、漏洞简介
phpMyAdmin数据库管理工具，弱口令/未授权，可操作数据库。
## 二、环境信息
靶场地址：http://127.0.0.1/pikachu/
关卡路径：/vul/other/phpmyadmin.php
## 三、复现步骤
1. 访问phpmyadmin登录页面
2. 尝试root弱口令登录，登录成功后可以管理数据库、写shell（into outfile）
## 四、Payload
mysql root弱口令
## 五、漏洞原理
数据库设置弱口令，phpmyadmin对外暴露。
## 六、修复方案
强密码，限制访问来源，不要公网暴露phpmyadmin。
## 七、总结
拿到mysql权限可以尝试写webshell拿服务器权限。